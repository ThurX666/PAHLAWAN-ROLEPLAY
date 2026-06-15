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
    $data = get_sanitized_json();
    $username = $data['username'] ?? '';
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
    try {
        $stmt = $pdo->query("SELECT * FROM ucp_data_change_requests ORDER BY created_at ASC");
        echo json_encode(["status" => "success", "data" => $stmt->fetchAll(PDO::FETCH_ASSOC)]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal mengambil data: " . $e->getMessage()]);
    }

} elseif ($action === 'process_request') {
    $data = get_sanitized_json();
    $id = $data['id'] ?? 0;
    $status = $data['status'] ?? ''; // 'Approved' or 'Rejected'
    $adminFeedback = $data['adminFeedback'] ?? '';
    $adminName = 'Admin System'; // You could pass this from frontend if you want

    if (!$id || !$status) {
        echo json_encode(["status" => "error", "message" => "Parameter tidak lengkap."]);
        exit;
    }

    try {
        $stmt = $pdo->prepare("UPDATE ucp_data_change_requests SET status = ?, admin_feedback = ?, reviewed_by = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?");
        $stmt->execute([$status, $adminFeedback, $adminName, $id]);
        
        // Cek data req
        $reqStmt = $pdo->prepare("SELECT username, change_type, new_value FROM ucp_data_change_requests WHERE id = ?");
        $reqStmt->execute([$id]);
        $reqData = $reqStmt->fetch(PDO::FETCH_ASSOC);

        if ($reqData) {
            $targetUser = $reqData['username'];
            $ctype = $reqData['change_type'];
            
            $reqTypeDisplay = htmlspecialchars($ctype);
            $adminFeedbackSafe = htmlspecialchars($adminFeedback ?: 'Tidak ada catatan tambahan.');
            $statusDisplay = $status === 'Approved' ? 'Disetujui' : 'Ditolak';
            
            $inboxTitle = "Pemberitahuan: Hasil Tinjauan Data OOC";
            
            $metadataObj = [
                'type' => $reqTypeDisplay,
                'status' => $status === 'Approved' ? 'Diizinkan' : 'Ditolak',
                'message' => $adminFeedbackSafe
            ];
            $metadataJson = json_encode($metadataObj);

            $stmt_inbox = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, ?, 'System', 0, 'OocProfileReview', ?)");
            $stmt_inbox->execute([
                $targetUser, 
                $inboxTitle, 
                'Permintaan pembaruan profil Anda telah diperiksa oleh tim Admin.',
                $metadataJson
            ]);
        }

        if ($status === 'Approved' && $reqData) {
            // TargetUser dan lain-lain sudah didefinisikan di atas
            $newVal = $reqData['new_value'];

                if ($ctype === 'Ganti Nama Asli (OOC)') {
                    $up = $pdo->prepare("UPDATE ucp_user_profiles SET ooc_name = ? WHERE username = ?");
                    $up->execute([$newVal, $targetUser]);
                } elseif ($ctype === 'Ganti Tanggal Lahir (OOC)') {
                    $up = $pdo->prepare("UPDATE ucp_user_profiles SET birth_date = ? WHERE username = ?");
                    $up->execute([$newVal, $targetUser]);
                } elseif ($ctype === 'Ganti Gender (OOC)') {
                    $up = $pdo->prepare("UPDATE ucp_user_profiles SET gender = ? WHERE username = ?");
                    $up->execute([$newVal, $targetUser]);
                } elseif ($ctype === 'Ganti Alamat (OOC)') {
                    $up = $pdo->prepare("UPDATE ucp_user_profiles SET address = ? WHERE username = ?");
                    $up->execute([$newVal, $targetUser]);
                } elseif ($ctype === 'Ganti Nomor Telepon (OOC)') {
                    $up = $pdo->prepare("UPDATE ucp_user_profiles SET phone_number = ? WHERE username = ?");
                    $up->execute([$newVal, $targetUser]);
                } elseif ($ctype === 'Ganti Discord ID (OOC)') {
                    $up = $pdo->prepare("UPDATE ucp_user_profiles SET discord_id = ? WHERE username = ?");
                    $up->execute([$newVal, $targetUser]);
                }
            }
        }
        
        $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'PROCESS_DATA_REQUEST', 'Request #$id', ?)");
        $logStmt->execute([$adminName, "Status: $status"]);

        echo json_encode(["status" => "success", "message" => "Pengajuan berhasil diproses."]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal memproses pengajuan: " . $e->getMessage()]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Aksi tidak valid."]);
}
?>
