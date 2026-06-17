<?php
require_once __DIR__ . '/config.php';

$data = get_sanitized_json();
$action = $_GET['action'] ?? ($_POST['action'] ?? ($data['action'] ?? ''));
$sessionUser = ucp_require_user();
$username = ucp_require_username(
    $_GET['username'] ?? ($_POST['username'] ?? ($data['username'] ?? null))
);

if ($_SERVER['REQUEST_METHOD'] === 'GET' && $action === '') {
    $stmt = $pdo->prepare("SELECT * FROM ucp_user_profiles WHERE username = ?");
    $stmt->execute([$username]);
    $profile = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$profile) {
        echo json_encode(["status" => "error", "message" => "Profile not found"]);
        exit;
    }

    echo json_encode(["status" => "success", "data" => $profile]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    ucp_json_error('Metode tidak valid.', 405);
}

if ($action === '' || $action === 'update_profile') {
    $oocName = $_POST['ooc_name'] ?? ($data['ooc_name'] ?? '');
    $birthDate = $_POST['birth_date'] ?? ($data['birth_date'] ?? '');
    $phoneNumber = $_POST['phone_number'] ?? ($data['phone_number'] ?? '');
    $address = $_POST['address'] ?? ($data['address'] ?? '');
    $gender = $_POST['gender'] ?? ($data['gender'] ?? '');

    $stmt = $pdo->prepare("
        INSERT INTO ucp_user_profiles
            (username, ooc_name, birth_date, phone_number, address, gender, is_locked)
        VALUES (?, ?, ?, ?, ?, ?, 1)
        ON DUPLICATE KEY UPDATE
            ooc_name = VALUES(ooc_name),
            birth_date = VALUES(birth_date),
            phone_number = VALUES(phone_number),
            address = VALUES(address),
            gender = VALUES(gender),
            is_locked = 1
    ");
    $stmt->execute([$username, $oocName, $birthDate ?: null, $phoneNumber, $address, $gender]);

    echo json_encode(["status" => "success", "message" => "Profile updated successfully"]);
    exit;
}

if ($action === 'change_password') {
    $oldPassword = $_POST['oldPassword'] ?? ($data['oldPassword'] ?? '');
    $newPassword = $_POST['newPassword'] ?? ($data['newPassword'] ?? '');
    if ($oldPassword === '' || strlen($newPassword) < 8) {
        ucp_json_error('Sandi lama diperlukan dan sandi baru minimal 8 karakter.');
    }

    $stmt = $pdo->prepare("SELECT ID as id, Password as password FROM player_ucp WHERE UCP = ? LIMIT 1");
    $stmt->execute([$username]);
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$user || !password_verify($oldPassword, $user['password'])) {
        ucp_json_error('Sandi lama tidak valid.', 403);
    }

    $hashPass = password_hash($newPassword, PASSWORD_BCRYPT, ['cost' => 12]);
    $upd = $pdo->prepare("UPDATE player_ucp SET Password = ? WHERE ID = ?");
    $upd->execute([$hashPass, $user['id']]);

    $metadata = json_encode(['time' => date('d M Y, H:i') . ' WIB']);
    $stmtInbox = $pdo->prepare("
        INSERT INTO ucp_inbox_messages
            (username, title, message, type, is_read, template, metadata)
        VALUES (?, 'Keamanan Akun: Kata Sandi Diubah', ?, 'System', 0, 'PasswordChanged', ?)
    ");
    $stmtInbox->execute([$username, 'Kata sandi akun UCP Anda baru saja diperbarui.', $metadata]);

    ucp_create_session([
        'id' => $sessionUser['id'],
        'username' => $username,
        'admin_level' => $sessionUser['admin_level'],
    ]);
    echo json_encode(["status" => "success", "message" => "Sandi berhasil diubah"]);
    exit;
}

if ($action === 'toggle_2fa') {
    $stmt = $pdo->prepare("SELECT is_2fa_enabled FROM ucp_user_profiles WHERE username = ?");
    $stmt->execute([$username]);
    $enabled = (int)($stmt->fetchColumn() ?: 0);
    $newToggle = $enabled === 1 ? 0 : 1;

    $stmt = $pdo->prepare("
        INSERT INTO ucp_user_profiles (username, is_2fa_enabled)
        VALUES (?, ?)
        ON DUPLICATE KEY UPDATE is_2fa_enabled = VALUES(is_2fa_enabled)
    ");
    $stmt->execute([$username, $newToggle]);

    echo json_encode(["status" => "success", "is_2fa_enabled" => $newToggle]);
    exit;
}

if ($action === 'link_discord') {
    ucp_json_error('Penautan Discord hanya dapat dilakukan melalui OAuth Discord.', 403);
}

ucp_json_error('Aksi tidak dikenal.');
