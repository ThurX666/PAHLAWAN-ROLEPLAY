<?php
require_once __DIR__ . '/config.php';

$user = ucp_require_user();
$discordId = trim((string)($_GET['id'] ?? ''));
if ($discordId === '' || !preg_match('/^\d{6,25}$/', $discordId)) {
    ucp_json_error('Discord ID tidak valid.', 422);
}

$stmt = $pdo->prepare(
    'SELECT p.discord_id, p.discord_avatar_hash
     FROM ucp_user_profiles p
     WHERE p.username = ? AND p.discord_id = ?
     LIMIT 1'
);
$stmt->execute([$user['username'], $discordId]);
$profile = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$profile) {
    $stmt = $pdo->prepare('SELECT discord_id FROM player_ucp WHERE UCP = ? AND discord_id = ? LIMIT 1');
    $stmt->execute([$user['username'], $discordId]);
    if (!$stmt->fetch(PDO::FETCH_ASSOC)) {
        ucp_json_error('Akun Discord tidak terhubung dengan sesi ini.', 404);
    }
    $profile = ['discord_avatar_hash' => null];
}

$hash = trim((string)($profile['discord_avatar_hash'] ?? ''));
$url = $hash !== ''
    ? sprintf('https://cdn.discordapp.com/avatars/%s/%s.%s?size=128', $discordId, $hash, str_starts_with($hash, 'a_') ? 'gif' : 'png')
    : 'https://cdn.discordapp.com/embed/avatars/' . ((int)substr($discordId, -1) % 6) . '.png';

echo json_encode(['status' => 'success', 'url' => $url]);
