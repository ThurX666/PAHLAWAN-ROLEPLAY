<?php
require_once __DIR__ . '/config.php';

// Cek apakah JSON body digunakan
$data = get_sanitized_json();
$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : ($data['action'] ?? ''));

if ($_SERVER['REQUEST_METHOD'] === 'GET' && empty($action)) {
    // Legacy GET behavior
    $username = $_GET['username'] ?? '';
    
    if (empty($username)) {
        echo json_encode(["status" => "error", "message" => "Username is required"]);
        exit;
    }

    $stmt = $pdo->prepare("SELECT * FROM ucp_user_profiles WHERE username = ?");
    $stmt->execute([$username]);
    $profile = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($profile) {
        echo json_encode(["status" => "success", "data" => $profile]);
    } else {
        echo json_encode(["status" => "error", "message" => "Profile not found"]);
    }
} elseif ($_SERVER['REQUEST_METHOD'] === 'POST' && (empty($action) || $action === 'update_profile')) {
    $username = $_POST['username'] ?? ($data['username'] ?? '');
    $ooc_name = htmlspecialchars($_POST['ooc_name'] ?? ($data['ooc_name'] ?? ''));
    $birth_date = htmlspecialchars($_POST['birth_date'] ?? ($data['birth_date'] ?? ''));
    $phone_number = htmlspecialchars($_POST['phone_number'] ?? ($data['phone_number'] ?? ''));
    $address = htmlspecialchars($_POST['address'] ?? ($data['address'] ?? ''));
    $gender = htmlspecialchars($_POST['gender'] ?? ($data['gender'] ?? ''));

    if (empty($username)) {
        echo json_encode(["status" => "error", "message" => "Username is required"]);
        exit;
    }

    // Lock profile when saving
    $is_locked = 1;

    $stmt = $pdo->prepare("SELECT id FROM ucp_user_profiles WHERE username = ?");
    $stmt->execute([$username]);
    $exists = $stmt->fetch();

    if ($exists) {
        $stmt = $pdo->prepare("UPDATE ucp_user_profiles SET ooc_name = ?, birth_date = ?, phone_number = ?, address = ?, gender = ?, is_locked = ? WHERE username = ?");
        $stmt->execute([$ooc_name, $birth_date, $phone_number, $address, $gender, $is_locked, $username]);
    } else {
        $stmt = $pdo->prepare("INSERT INTO ucp_user_profiles (username, ooc_name, birth_date, phone_number, address, gender, is_locked) VALUES (?, ?, ?, ?, ?, ?, ?)");
        $stmt->execute([$username, $ooc_name, $birth_date, $phone_number, $address, $gender, $is_locked]);
    }

    echo json_encode(["status" => "success", "message" => "Profile updated successfully"]);
} elseif ($action === 'change_password') {
    $username = $_POST['username'] ?? ($data['username'] ?? '');
    $oldPassword = $_POST['oldPassword'] ?? ($data['oldPassword'] ?? '');
    $newPassword = $_POST['newPassword'] ?? ($data['newPassword'] ?? '');

    if (empty($username) || empty($oldPassword) || empty($newPassword)) {
        echo json_encode(["status" => "error", "message" => "Data tidak lengkap"]);
        exit;
    }

    $stmt = $pdo->prepare("SELECT ID as id, Password as password FROM player_ucp WHERE UCP = ? LIMIT 1");
    $stmt->execute([$username]);
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user && password_verify($oldPassword, $user['password'])) {
        $hashPass = password_hash($newPassword, PASSWORD_BCRYPT, ['cost' => 12]);
        $upd = $pdo->prepare("UPDATE player_ucp SET Password = ? WHERE ID = ?");
        $upd->execute([$hashPass, $user['id']]);
        
        // --- INBOX NOTIFICATION: PASSWORD CHANGED ---
        $inboxTitle = "Keamanan Akun: Kata Sandi Diubah";
        $login_time = date('d M Y, H:i') . ' WIB'; 
        
        $metadataObj = [
            'time' => $login_time
        ];
        $metadataJson = json_encode($metadataObj);
        
        $stmt_inbox = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, ?, 'System', 0, 'PasswordChanged', ?)");
        $stmt_inbox->execute([
            $username, 
            $inboxTitle, 
            'Kata sandi akun UCP Anda baru saja diperbarui.',
            $metadataJson
        ]);
        // --- END INBOX NOTIFICATION ---

        echo json_encode(["status" => "success", "message" => "Sandi berhasil diubah"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Sandi lama tidak valid"]);
    }
} elseif ($action === 'toggle_2fa') {
    $username = $_POST['username'] ?? ($data['username'] ?? '');
    
    if (empty($username)) {
        echo json_encode(["status" => "error", "message" => "Username is required"]);
        exit;
    }
    
    $stmt = $pdo->prepare("SELECT id, is_2fa_enabled FROM ucp_user_profiles WHERE username = ?");
    $stmt->execute([$username]);
    $exists = $stmt->fetch();
    
    $newToggle = $exists && $exists['is_2fa_enabled'] == 1 ? 0 : 1;
    
    if ($exists) {
        $upd = $pdo->prepare("UPDATE ucp_user_profiles SET is_2fa_enabled = ? WHERE username = ?");
        $upd->execute([$newToggle, $username]);
    } else {
        $stmt = $pdo->prepare("INSERT INTO ucp_user_profiles (username, is_2fa_enabled) VALUES (?, ?)");
        $stmt->execute([$username, $newToggle]);
    }
    echo json_encode(["status" => "success", "is_2fa_enabled" => $newToggle]);
} elseif ($action === 'link_discord') {
    $username = $_POST['username'] ?? ($data['username'] ?? '');
    $discordId = $_POST['discordId'] ?? ($data['discordId'] ?? '');
    
    if (empty($username) || empty($discordId)) {
        echo json_encode(["status" => "error", "message" => "Data tidak lengkap"]);
        exit;
    }
    
    $stmt = $pdo->prepare("SELECT id FROM ucp_user_profiles WHERE username = ?");
    $stmt->execute([$username]);
    $exists = $stmt->fetch();
    
    if ($exists) {
        $upd = $pdo->prepare("UPDATE ucp_user_profiles SET discord_id = ? WHERE username = ?");
        $upd->execute([$discordId, $username]);
    } else {
        $stmt = $pdo->prepare("INSERT INTO ucp_user_profiles (username, discord_id) VALUES (?, ?)");
        $stmt->execute([$username, $discordId]);
    }

    $inboxTitle = "Discord Berhasil Ditautkan 🎉";
    $metadataObj = [
        'discordUsername' => "Simulated User (from Profile)"
    ];
    $metadataJson = json_encode($metadataObj);

    $stmt_inbox = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, ?, 'System', 0, 'DiscordLinked', ?)");
    $stmt_inbox->execute([
        $username, 
        $inboxTitle, 
        'Akun UCP Anda kini telah tertaut dengan akun Discord.',
        $metadataJson
    ]);

    echo json_encode(["status" => "success", "message" => "Discord berhasil ditautkan"]);
} else {
    echo json_encode(["status" => "error", "message" => "Unknown action"]);
}
?>
