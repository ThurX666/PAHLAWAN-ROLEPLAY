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

    if (!$username || !$type || !$content) {
        echo json_encode(["status" => "error", "message" => "Mohon lengkapi semua field yang diperlukan."]);
        exit;
    }

    try {
        $stmt = $pdo->prepare("INSERT INTO ucp_user_requests (username, request_type, content, metadata, status) VALUES (?, ?, ?, ?, 'Pending')");
        $stmt->execute([$username, $type, $content, $metadata]);
        
        echo json_encode(["status" => "success", "message" => "Permohonan Anda berhasil dikirim dan sedang menunggu tinjauan Admin."]);
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal menyimpan permohonan: " . $e->getMessage()]);
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
        echo json_encode(["status" => "error", "message" => "Gagal mengambil data: " . $e->getMessage()]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Aksi tidak valid."]);
}
?>
