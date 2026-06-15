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
        // Mengecek pesan masuk di ucp_inbox_messages dengan title 'Informasi Faction'
        // dan mengambil metadata JSON-nya.
        // Di sistem yang lebih kompleks, ini bisa di-query langsung ke table players atau factions
        $stmt = $pdo->prepare("SELECT * FROM ucp_inbox_messages WHERE username = ? AND title LIKE '%Informasi Faction%' ORDER BY id DESC LIMIT 1");
        $stmt->execute([$username]);
        $result = $stmt->fetch(PDO::FETCH_ASSOC);

        if ($result && isset($result['metadata'])) {
            $metadata = json_decode($result['metadata'], true);
            echo json_encode([
                'status' => 'success',
                'accepted' => true,
                'factionName' => $metadata['factionName'] ?? 'Faksi Anda',
                'characterName' => $metadata['characterName'] ?? 'Karakter Anda',
                'message' => 'Anda telah diterima faksi.'
            ]);
        } else {
            echo json_encode([
                'status' => 'success',
                'accepted' => false,
                'message' => 'Belum ada penerimaan faksi.'
            ]);
        }
    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Database error']);
    }
    exit;
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
