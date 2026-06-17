<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $username = ucp_require_username($_GET['username'] ?? null);

    $stmt = $pdo->prepare(
        "SELECT c.pID AS id,
                c.Char_Name AS name,
                c.Char_Level AS level,
                c.Char_Money AS money,
                c.Char_BankMoney AS bank,
                c.Char_LastLogin AS lastLogin,
                c.Char_Skin AS skinId,
                c.Char_Hours AS playingHours,
                c.Char_Warn AS warns,
                c.Char_Job AS jobName,
                c.Char_Hunger AS needsHunger,
                c.Char_Thirst AS needsThirsty,
                c.Char_Stress AS needsMood,
                c.Char_Health AS health,
                c.Char_Armor AS armor,
                c.Char_Faction AS factionId,
                c.Char_FactionRank AS factionRank,
                c.Char_Jailed AS jailed,
                c.Char_GVL1LicTime AS licenseDriveExp,
                c.Char_Air1LicTime AS licenseFlyExp,
                c.Char_BLicTime AS licenseBoatExp,
                c.Char_FirearmLicTime AS licenseGunExp,
                COALESCE(c.story_status, 'None') AS storyStatus,
                c.photo_url AS photoUrl,
                CASE WHEN op.player_id IS NULL THEN 'Offline' ELSE 'Online' END AS status
         FROM player_characters c
         JOIN player_ucp a ON c.Char_UCP = a.UCP
         LEFT JOIN ucp_online_players op ON op.character_name = c.Char_Name
         WHERE a.UCP = ?
         ORDER BY c.pID ASC"
    );
    $stmt->execute([$username]);
    $characters = $stmt->fetchAll(PDO::FETCH_ASSOC);

    echo json_encode(['status' => 'success', 'data' => $characters]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $sessionUser = ucp_require_user();
    $data = get_sanitized_json();
    $action = $data['action'] ?? '';

    if ($action === 'create') {
        $username = ucp_require_username($data['username'] ?? null);
        $name = $data['name'] ?? '';

        if (!$username || !$name) {
            echo json_encode(['status' => 'error', 'message' => 'Username and Character Name required']);
            exit;
        }

        $gender = $data['gender'] ?? '';
        $age = filter_var($data['age'] ?? null, FILTER_VALIDATE_INT);
        $height = filter_var($data['height'] ?? null, FILTER_VALIDATE_INT);
        $weight = filter_var($data['weight'] ?? null, FILTER_VALIDATE_INT);
        $origin = trim((string)($data['origin'] ?? ''));

        if (!preg_match('/^[A-Z][A-Za-z]{2,23}_[A-Z][A-Za-z]{2,23}$/', $name)) {
            ucp_json_error('Format nama karakter harus First_Last.', 422);
        }
        if (!in_array($gender, ['Male', 'Female'], true) || $age < 17 || $age > 60 ||
            $height < 140 || $height > 220 || $weight < 40 || $weight > 150 ||
            $origin === '' || mb_strlen($origin) > 64) {
            ucp_json_error('Data karakter tidak valid.', 422);
        }

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
            $stmtInsert = $pdo->prepare(
                "INSERT INTO player_characters
                    (Char_UCP, Char_Name, Char_Level, Char_Money, Char_BankMoney, Char_RegisterDate,
                     Char_Gender, Char_Age, Char_BodyHeight, Char_BodyWeight, Char_Origin)
                 VALUES (?, ?, 1, 250, 500, CURRENT_TIMESTAMP, ?, ?, ?, ?, ?)"
            );
            $stmtInsert->execute([
                $account['username'],
                $name,
                $gender === 'Male' ? 1 : 2,
                $age,
                $height,
                $weight,
                $origin,
            ]);
            $charId = $pdo->lastInsertId();

            // Send notification to inbox
            $stmtInbox = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, ?, ?, 0, 'CharacterCreated', ?)");
            $inboxTitle = "Karakter Dibuat: " . htmlspecialchars($name);
            
            $safeName = htmlspecialchars($name);
            $safeGender = htmlspecialchars($gender);
            $safeAge = htmlspecialchars($age);
            $safeHeight = htmlspecialchars((string)$height . ' cm');
            $safeWeight = htmlspecialchars((string)$weight . ' kg');
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
            $stmtDel = $pdo->prepare("DELETE FROM player_characters WHERE pID = ? AND Char_UCP = ?");
            $stmtDel->execute([$charId, $sessionUser['username']]);
            if ($stmtDel->rowCount() === 0) {
                ucp_json_error('Karakter tidak ditemukan atau bukan milik Anda.', 404);
            }
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
