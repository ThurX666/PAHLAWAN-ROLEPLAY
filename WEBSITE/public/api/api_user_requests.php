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
    $type = $data['type'] ?? '';
    $content = $data['content'] ?? '';
    $metadata = isset($data['metadata']) ? json_encode($data['metadata']) : '{}';

    $allowedTypes = ['Feature', 'Unban', 'Namechange', 'Refund'];
    if (!$username || !in_array($type, $allowedTypes, true) || trim($content) === '') {
        echo json_encode(["status" => "error", "message" => "Mohon lengkapi semua field yang diperlukan."]);
        exit;
    }

    try {
        $stmt = $pdo->prepare("INSERT INTO ucp_user_requests (username, request_type, content, metadata, status) VALUES (?, ?, ?, ?, 'Pending')");
        $stmt->execute([$username, $type, $content, $metadata]);
        
        echo json_encode(["status" => "success", "message" => "Permohonan Anda berhasil dikirim dan sedang menunggu tinjauan Admin."]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal menyimpan permohonan."]);
    }
} elseif ($action === 'get_requests') {
    $sessionUser = ucp_require_user();
    $username = isset($_GET['username']) ? $_GET['username'] : '';
    
    try {
        if ($username) {
            $username = ucp_require_username($username);
            $stmt = $pdo->prepare("SELECT * FROM ucp_user_requests WHERE username = ? ORDER BY created_at DESC");
            $stmt->execute([$username]);
        } else {
            ucp_require_admin(5);
            $stmt = $pdo->query("SELECT * FROM ucp_user_requests ORDER BY created_at DESC");
        }
        echo json_encode(["status" => "success", "data" => $stmt->fetchAll(PDO::FETCH_ASSOC)]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal mengambil data."]);
    }
} elseif ($action === 'process_request') {
    $admin = ucp_require_admin(5);
    $data = get_sanitized_json();
    $requestId = (int)($data['id'] ?? 0);
    $status = (string)($data['status'] ?? '');
    $feedback = trim((string)($data['adminFeedback'] ?? ''));

    if ($requestId < 1 || !in_array($status, ['Approved', 'Rejected'], true)) {
        ucp_json_error('Parameter review tidak valid.', 422);
    }
    if ($status === 'Rejected' && $feedback === '') {
        ucp_json_error('Alasan penolakan wajib diisi.', 422);
    }

    try {
        $pdo->beginTransaction();
        $stmt = $pdo->prepare('SELECT * FROM ucp_user_requests WHERE id = ? FOR UPDATE');
        $stmt->execute([$requestId]);
        $request = $stmt->fetch(PDO::FETCH_ASSOC);
        if (!$request || $request['status'] !== 'Pending') {
            throw new RuntimeException('Permohonan tidak ditemukan atau sudah diproses.');
        }

        $metadata = json_decode((string)($request['metadata'] ?? '{}'), true) ?: [];
        if ($status === 'Approved') {
            if ($request['request_type'] === 'Unban') {
                $character = trim((string)($metadata['character'] ?? $metadata['karakterban'] ?? ''));
                if ($character === '') {
                    throw new RuntimeException('Nama karakter untuk unban tidak tersedia.');
                }
                $deleteBan = $pdo->prepare('DELETE FROM player_bans WHERE name = ?');
                $deleteBan->execute([$character]);
            } elseif ($request['request_type'] === 'Namechange') {
                $oldName = trim((string)($metadata['oldName'] ?? $metadata['old_name'] ?? ''));
                $newName = trim((string)($metadata['newName'] ?? $metadata['new_name'] ?? ''));
                if (!preg_match('/^[A-Z][A-Za-z]{2,23}_[A-Z][A-Za-z]{2,23}$/', $newName)) {
                    throw new RuntimeException('Nama karakter baru tidak valid.');
                }
                $rename = $pdo->prepare(
                    'UPDATE player_characters SET Char_Name = ?
                     WHERE Char_Name = ? AND Char_UCP = ?'
                );
                $rename->execute([$newName, $oldName, $request['username']]);
                if ($rename->rowCount() !== 1) {
                    throw new RuntimeException('Karakter lama tidak ditemukan atau nama baru sudah digunakan.');
                }
            }
        }

        $update = $pdo->prepare(
            'UPDATE ucp_user_requests
             SET status = ?, admin_feedback = ?, reviewed_by = ?
             WHERE id = ?'
        );
        $update->execute([$status, $feedback, $admin['username'], $requestId]);

        $templateMap = [
            'Unban' => 'UnbanApproved',
            'Namechange' => 'NamechangeSuccess',
            'Refund' => 'RefundApproved',
            'Feature' => 'RequestReviewed',
        ];
        $inboxMetadata = array_merge($metadata, [
            'adminName' => $admin['username'],
            'feedback' => $feedback,
            'requestType' => $request['request_type'],
            'status' => $status,
        ]);
        $inbox = $pdo->prepare(
            "INSERT INTO ucp_inbox_messages
                (username, title, message, type, is_read, template, metadata)
             VALUES (?, ?, ?, 'System', 0, ?, ?)"
        );
        $inbox->execute([
            $request['username'],
            sprintf('Permohonan %s: %s', $request['request_type'], $status),
            $feedback,
            $status === 'Approved' ? ($templateMap[$request['request_type']] ?? 'RequestReviewed') : 'RequestReviewed',
            json_encode($inboxMetadata),
        ]);

        $log = $pdo->prepare(
            'INSERT INTO ucp_admin_logs (admin_name, action, target_player, details)
             VALUES (?, ?, ?, ?)'
        );
        $log->execute([
            $admin['username'],
            'REVIEW_USER_REQUEST',
            $request['username'],
            sprintf('%s #%d => %s', $request['request_type'], $requestId, $status),
        ]);

        $pdo->commit();
        echo json_encode(['status' => 'success']);
    } catch (Throwable $e) {
        if ($pdo->inTransaction()) {
            $pdo->rollBack();
        }
        ucp_json_error($e instanceof RuntimeException ? $e->getMessage() : 'Gagal memproses permohonan.', 400);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Aksi tidak valid."]);
}
?>
