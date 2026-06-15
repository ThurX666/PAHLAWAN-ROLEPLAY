<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $char_id = $_POST['char_id'] ?? 0;
    $content = $_POST['story_text'] ?? '';
    $username = $_POST['username'] ?? '';
    // $photo = $_FILES['photo'] ?? null; // Not implemented for mock purposes right now. Assuming just text or base64.

    if ($char_id > 0 && !empty($content) && !empty($username)) {
        // Validation length: min 300 words and 3 paragraphs
        $words = str_word_count(strip_tags($content));
        $paragraphs = count(array_filter(preg_split('/\n+/', trim($content))));
        
        if ($words < 300 || $paragraphs < 3) {
            echo json_encode(['status' => 'error', 'message' => 'Cerita harus minimal 300 kata dan 3 paragraf.']);
            exit;
        }

        // Cek apakah karakter milik user ini
        $stmtAccount = $pdo->prepare("SELECT ID as id FROM player_ucp WHERE UCP = ?");
        $stmtAccount->execute([$username]);
        $account = $stmtAccount->fetch(PDO::FETCH_ASSOC);

        if (!$account) {
            echo json_encode(['status' => 'error', 'message' => 'Account not found']);
            exit;
        }

        $stmtChar = $pdo->prepare("SELECT id FROM characters WHERE id = ? AND ucp_id = ?");
        $stmtChar->execute([$char_id, $account['id']]);
        $char = $stmtChar->fetch(PDO::FETCH_ASSOC);

        if (!$char) {
            echo json_encode(['status' => 'error', 'message' => 'Character not found or not owned by you']);
            exit;
        }

        // Cek apakah sudah ada cerita untuk karakter ini
        $stmtCek = $pdo->prepare("SELECT id FROM ucp_character_stories WHERE character_id = ?");
        $stmtCek->execute([$char_id]);
        $existing = $stmtCek->fetch(PDO::FETCH_ASSOC);

        if ($existing) {
            // Update & ubah status kembali ke Pending
            $stmtUpdate = $pdo->prepare("UPDATE ucp_character_stories SET content = ?, status = 'Pending', last_updated = CURRENT_TIMESTAMP WHERE character_id = ?");
            $stmtUpdate->execute([$content, $char_id]);
        } else {
            // Insert baru
            $stmtInsert = $pdo->prepare("INSERT INTO ucp_character_stories (character_id, content, status) VALUES (?, ?, 'Pending')");
            $stmtInsert->execute([$char_id, $content]);
        }

        // Update status di tabel characters juga
        $stmtCharUpdate = $pdo->prepare("UPDATE characters SET story_status = 'Pending' WHERE id = ?");
        $stmtCharUpdate->execute([$char_id]);

        echo json_encode(['status' => 'success', 'message' => 'Story submitted successfully']);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Invalid parameters']);
    }
    exit;
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
