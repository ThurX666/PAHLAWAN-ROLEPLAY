<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $username = ucp_require_username($_GET['username'] ?? null);
    
    if ($username) {
        // Ambil ID account
        $stmtAccount = $pdo->prepare("SELECT ID as id FROM player_ucp WHERE UCP = ?");
        $stmtAccount->execute([$username]);
        $account = $stmtAccount->fetch(PDO::FETCH_ASSOC);

        if (!$account) {
            echo json_encode(['status' => 'error', 'message' => 'Account not found']);
            exit;
        }

        // Ambil semua cerita karakter terkait account ini
        $stmtStories = $pdo->prepare("
            SELECT cs.*, c.Char_Name as character_name, c.Char_Skin as skin_id, 'None' as photo_path
            FROM ucp_character_stories cs 
            JOIN player_characters c ON cs.character_id = c.pID 
            WHERE c.Char_UCP = ?
        ");
        $stmtStories->execute([$username]);
        $stories = $stmtStories->fetchAll(PDO::FETCH_ASSOC);

        echo json_encode(['status' => 'success', 'data' => $stories]);
        exit;
    }
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
