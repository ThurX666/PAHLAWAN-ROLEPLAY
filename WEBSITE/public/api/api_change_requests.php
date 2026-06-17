<?php
require_once __DIR__ . '/config.php';

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) {
        $action = $data['action'];
    }
}

if ($action === 'submit_request') {
    $sessionUser = ucp_require_user();
    $data = get_sanitized_json();
    $username = ucp_require_username($data['username'] ?? null);
    $changeType = $data['changeType'] ?? '';
    $target = $data['targetInfo'] ?? '';
    $oldValue = $data['oldValue'] ?? '';
    $newValue = $data['newValue'] ?? '';
    $reason = $data['reason'] ?? '';

    if (!$username || !$changeType || !$newValue || !$reason) {
        echo json_encode(["status" => "error", "message" => "Mohon lengkapi semua field yang diperlukan."]);
        exit;
    }

    try {
        $stmt = $pdo->prepare("INSERT INTO ucp_data_change_requests (username, change_type, target_information, old_value, new_value, reason, status) VALUES (?, ?, ?, ?, ?, ?, 'Pending')");
        $stmt->execute([$username, $changeType, $target, $oldValue, $newValue, $reason]);
        
        echo json_encode(["status" => "success", "message" => "Pengajuan perubahan data berhasil dikirim."]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal menyimpan pengajuan: " . $e->getMessage()]);
    }
    
} elseif ($action === 'get_requests') {
    ucp_require_admin(5);
    try {
        $stmt = $pdo->query("SELECT * FROM ucp_data_change_requests ORDER BY created_at ASC");
        echo json_encode(["status" => "success", "data" => $stmt->fetchAll(PDO::FETCH_ASSOC)]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal mengambil data: " . $e->getMessage()]);
    }

} elseif ($action === 'process_request') {
    $adminUser = ucp_require_admin(5);
    $data = get_sanitized_json();
    $id = $data['id'] ?? 0;
    $status = $data['status'] ?? ''; // 'Approved' or 'Rejected'
    $adminFeedback = $data['adminFeedback'] ?? '';
    $adminName = $adminUser['username'];

    if (!$id || !in_array($status, ['Approved', 'Rejected'], true)) {
        ucp_json_error('Parameter tidak lengkap atau status tidak valid.');
    }

    $profileColumns = [
        'Ganti Nama Asli (OOC)' => 'ooc_name',
        'Ganti Tanggal Lahir (OOC)' => 'birth_date',
        'Ganti Gender (OOC)' => 'gender',
        'Ganti Alamat (OOC)' => 'address',
        'Ganti Nomor Telepon (OOC)' => 'phone_number',
    ];

    $pdo->beginTransaction();
    try {
        $reqStmt = $pdo->prepare("
            SELECT username, change_type, new_value
            FROM ucp_data_change_requests
            WHERE id = ? AND status = 'Pending'
            FOR UPDATE
        ");
        $reqStmt->execute([$id]);
        $reqData = $reqStmt->fetch(PDO::FETCH_ASSOC);
        if (!$reqData) {
            throw new RuntimeException('Pengajuan tidak ditemukan atau sudah diproses.');
        }

        $stmt = $pdo->prepare("
            UPDATE ucp_data_change_requests
            SET status = ?, admin_feedback = ?, reviewed_by = ?, updated_at = CURRENT_TIMESTAMP
            WHERE id = ?
        ");
        $stmt->execute([$status, $adminFeedback, $adminName, $id]);

        $targetUser = $reqData['username'];
        $changeType = $reqData['change_type'];
        if ($status === 'Approved') {
            if (isset($profileColumns[$changeType])) {
                $column = $profileColumns[$changeType];
                $up = $pdo->prepare("UPDATE ucp_user_profiles SET `{$column}` = ? WHERE username = ?");
                $up->execute([$reqData['new_value'], $targetUser]);
            } elseif ($changeType === 'Ganti Discord ID (OOC)') {
                throw new RuntimeException('Discord ID hanya dapat diubah melalui OAuth Discord.');
            }
        }

        $metadataJson = json_encode([
            'type' => $changeType,
            'status' => $status === 'Approved' ? 'Diizinkan' : 'Ditolak',
            'message' => $adminFeedback ?: 'Tidak ada catatan tambahan.',
        ]);
        $stmtInbox = $pdo->prepare("
            INSERT INTO ucp_inbox_messages
                (username, title, message, type, is_read, template, metadata)
            VALUES (?, 'Pemberitahuan: Hasil Tinjauan Data OOC', ?, 'System', 0, 'OocProfileReview', ?)
        ");
        $stmtInbox->execute([
            $targetUser,
            'Permintaan pembaruan profil Anda telah diperiksa oleh tim Admin.',
            $metadataJson,
        ]);

        $logStmt = $pdo->prepare("
            INSERT INTO ucp_admin_logs (admin_name, action, target_player, details)
            VALUES (?, 'PROCESS_DATA_REQUEST', ?, ?)
        ");
        $logStmt->execute([$adminName, "Request #{$id}", "Status: {$status}"]);

        $pdo->commit();
        echo json_encode(["status" => "success", "message" => "Pengajuan berhasil diproses."]);
    } catch (Throwable $e) {
        if ($pdo->inTransaction()) {
            $pdo->rollBack();
        }
        ucp_json_error($e instanceof RuntimeException ? $e->getMessage() : 'Gagal memproses pengajuan.', 400);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Aksi tidak valid."]);
}
?>
