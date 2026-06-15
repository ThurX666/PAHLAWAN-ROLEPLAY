<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $username = $_GET['username'] ?? '';
    if (!$username) {
        echo json_encode(['status' => 'error', 'message' => 'Username required']);
        exit;
    }

    try {
        // Logika untuk XAMPP/Hosting:
        // Cek apakah ada peringatan 'Account Sharing' yang belum berstatus resolved atau belum lama,
        // misalnya kita cek apakah warning text seperti 'Account Sharing' ada pada log pelanggaran (ucp_inbox_messages)
        $stmt = $pdo->prepare("SELECT COUNT(*) as count FROM ucp_inbox_messages WHERE username = ? AND title LIKE '%Account Sharing%'");
        $stmt->execute([$username]);
        $result = $stmt->fetch(PDO::FETCH_ASSOC);

        $isSharingDetected = $result['count'] > 0;

        echo json_encode([
            'status' => 'success',
            'isSharingDetected' => $isSharingDetected,
            'message' => $isSharingDetected ? 'Indikasi Account Sharing terdeteksi' : 'Aman'
        ]);
    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Database error']);
    }
    exit;
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
