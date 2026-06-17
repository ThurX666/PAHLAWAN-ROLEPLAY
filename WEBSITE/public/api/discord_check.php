<?php
require_once __DIR__ . '/config.php';

$currentUser = ucp_current_user();
$username = $currentUser
    ? ucp_require_username($_GET['username'] ?? null)
    : ucp_require_pending_username($_GET['username'] ?? null);

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
