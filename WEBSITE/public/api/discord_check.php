<?php
require_once __DIR__ . '/config.php';

$username = $_GET['username'] ?? '';

if (empty($username)) {
    echo json_encode(['status' => 'error', 'message' => 'Username required']);
    exit;
}

$stmt = $conn->prepare("SELECT discord_id, admin_level, gold FROM player_ucp WHERE UCP = :username LIMIT 1");
$stmt->execute(['username' => $username]);
$user = $stmt->fetch(PDO::FETCH_ASSOC);

if ($user && !empty($user['discord_id'])) {
    echo json_encode([
        'status' => 'success',
        'admin_level' => (int)$user['admin_level'],
        'gold' => (int)$user['gold']
    ]);
} else {
    echo json_encode(['status' => 'pending']);
}
?>
