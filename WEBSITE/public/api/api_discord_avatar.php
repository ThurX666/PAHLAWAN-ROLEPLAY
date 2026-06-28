<?php
require_once __DIR__ . '/config.php';

$user = ucp_require_user();
$discordId = trim((string)($_GET['id'] ?? ''));
if ($discordId === '' || !preg_match('/^\d{6,25}$/', $discordId)) {
    ucp_json_error('Discord ID tidak valid.', 422);
}

// 1. Canonical check: player_ucp.discord_id adalah source of truth
$stmt = $pdo->prepare(
    'SELECT discord_id FROM player_ucp WHERE UCP = ? AND discord_id = ? LIMIT 1'
);
$stmt->execute([$user['username'], $discordId]);
if (!$stmt->fetch(PDO::FETCH_ASSOC)) {
    ucp_json_error('Akun Discord tidak terhubung dengan sesi ini.', 404);
}

// 2. Enrich: ambil avatar hash dari cache ucp_user_profiles (boleh kosong)
$stmt = $pdo->prepare(
    'SELECT discord_avatar_hash FROM ucp_user_profiles WHERE username = ? LIMIT 1'
);
$stmt->execute([$user['username']]);
$profile = $stmt->fetch(PDO::FETCH_ASSOC);

$hash = trim((string)($profile['discord_avatar_hash'] ?? ''));
$url = $hash !== ''
    ? sprintf('https://cdn.discordapp.com/avatars/%s/%s.%s?size=128', $discordId, $hash, str_starts_with($hash, 'a_') ? 'gif' : 'png')
    : 'https://cdn.discordapp.com/embed/avatars/' . ((int)substr($discordId, -1) % 6) . '.png';

echo json_encode(['status' => 'success', 'url' => $url]);
