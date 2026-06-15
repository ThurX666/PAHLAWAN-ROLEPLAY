<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $username = $_GET['username'] ?? '';
    if (!$username) {
        echo json_encode(['status' => 'error', 'message' => 'Username required']);
        exit;
    }

    $stmt = $pdo->prepare("SELECT c.pID as id, c.Char_Name as name, c.Char_Level as level, c.Char_Money as money, c.Char_BankMoney as bank, 'Warga Sipil' as faction, 'Offline' as status FROM player_characters c JOIN player_ucp a ON c.Char_UCP = a.UCP WHERE a.UCP = ? ORDER BY c.pID ASC");
    $stmt->execute([$username]);
    $characters = $stmt->fetchAll(PDO::FETCH_ASSOC);

    echo json_encode(['status' => 'success', 'data' => $characters]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = get_sanitized_json();
    $action = $data['action'] ?? '';

    if ($action === 'create') {
        $username = $data['username'] ?? '';
        $name = $data['name'] ?? '';

        if (!$username || !$name) {
            echo json_encode(['status' => 'error', 'message' => 'Username and Character Name required']);
            exit;
        }

        $gender = $data['gender'] ?? 'Tidak Diketahui';
        $age = $data['age'] ?? '-';
        $height = $data['height'] ? $data['height'] . ' cm' : '-';
        $weight = $data['weight'] ? $data['weight'] . ' kg' : '-';
        $origin = $data['origin'] ?? 'Tidak Diketahui';

        // Get UCP ID
        $stmtAccount = $pdo->prepare("SELECT UCP as username FROM player_ucp WHERE UCP = ?");
        $stmtAccount->execute([$username]);
        $account = $stmtAccount->fetch(PDO::FETCH_ASSOC);

        if (!$account) {
            echo json_encode(['status' => 'error', 'message' => 'Account not found']);
            exit;
        }

        // Check slots limit
        $stmtCount = $pdo->prepare("SELECT count(pID) as count FROM player_characters WHERE Char_UCP = ?");
        $stmtCount->execute([$account['username']]);
        $slots = $stmtCount->fetch(PDO::FETCH_ASSOC);

        if ($slots['count'] >= 3) {
            echo json_encode(['status' => 'error', 'message' => 'Character slots full (Max 3)']);
            exit;
        }

        // Create character
        try {
            $stmtInsert = $pdo->prepare("INSERT INTO player_characters (Char_UCP, Char_Name, Char_Level, Char_Money, Char_BankMoney, Char_RegisterDate) VALUES (?, ?, 1, 250, 500, CURRENT_TIMESTAMP)");
            $stmtInsert->execute([$account['username'], $name]);
            $charId = $pdo->lastInsertId();

            // Send notification to inbox
            $stmtInbox = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, ?, ?, 0, 'CharacterCreated', ?)");
            $inboxTitle = "Karakter Dibuat: " . htmlspecialchars($name);
            
            $safeName = htmlspecialchars($name);
            $safeGender = htmlspecialchars($gender);
            $safeAge = htmlspecialchars($age);
            $safeHeight = htmlspecialchars($height);
            $safeWeight = htmlspecialchars($weight);
            $safeOrigin = htmlspecialchars($origin);
            
            $metadataObj = [
                'name' => $safeName,
                'gender' => $safeGender,
                'age' => $safeAge,
                'height' => $safeHeight,
                'weight' => $safeWeight,
                'origin' => $safeOrigin,
            ];
            $metadataJson = json_encode($metadataObj);
            
            $stmtInbox->execute([
                $account['username'], 
                $inboxTitle, 
                'Karakter baru berhasil dibuat.', 
                'System', 
                $metadataJson
            ]);

            echo json_encode(['status' => 'success', 'id' => $charId]);
        } catch (PDOException $e) {
            if ($e->errorInfo[1] == 1062) {
                echo json_encode(['status' => 'error', 'message' => 'Character name already exists']);
            } else {
                echo json_encode(['status' => 'error', 'message' => 'Failed to create character']);
            }
        }
        exit;
    }

    if ($action === 'delete') {
        $charId = $data['id'] ?? null;
        if ($charId) {
            $stmtDel = $pdo->prepare("DELETE FROM player_characters WHERE pID = ?");
            $stmtDel->execute([$charId]);
            echo json_encode(['status' => 'success']);
        } else {
            echo json_encode(['status' => 'error', 'message' => 'Character ID required']);
        }
        exit;
    }

    echo json_encode(['status' => 'error', 'message' => 'Invalid action']);
    exit;
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
