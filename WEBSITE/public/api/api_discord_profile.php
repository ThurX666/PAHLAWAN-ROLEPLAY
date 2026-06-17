<?php
require_once __DIR__ . '/config.php';

$user = ucp_require_user();
$discordId = trim((string)($_GET['id'] ?? ''));
if ($discordId === '' || !preg_match('/^\d{6,25}$/', $discordId)) {
    ucp_json_error('Discord ID tidak valid.', 422);
}

$stmt = $pdo->prepare(
    'SELECT a.discord_id,
            p.discord_avatar_hash,
            p.updated_at AS linked_at
     FROM player_ucp a
     LEFT JOIN ucp_user_profiles p ON p.username = a.UCP
     WHERE a.UCP = ? AND a.discord_id = ?
     LIMIT 1'
);
$stmt->execute([$user['username'], $discordId]);
$profile = $stmt->fetch(PDO::FETCH_ASSOC);
if (!$profile) {
    ucp_json_error('Akun Discord tidak terhubung dengan sesi ini.', 404);
}

$hash = trim((string)($profile['discord_avatar_hash'] ?? ''));
$avatarUrl = $hash !== ''
    ? sprintf('https://cdn.discordapp.com/avatars/%s/%s.%s?size=256', $discordId, $hash, str_starts_with($hash, 'a_') ? 'gif' : 'png')
    : 'https://cdn.discordapp.com/embed/avatars/' . ((int)substr($discordId, -1) % 6) . '.png';

echo json_encode([
    'status' => 'success',
    'id' => $discordId,
    'username' => $user['username'],
    'global_name' => $user['username'],
    'avatar_url' => $avatarUrl,
    'created_at' => null,
    'linked_at' => $profile['linked_at'] ?? null,
    'roles' => [],
]);
