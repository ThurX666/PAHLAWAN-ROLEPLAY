<?php
require_once __DIR__ . '/config.php';

$username = ucp_require_pending_username($_GET['username'] ?? null);

$stmt = $conn->prepare("
    SELECT setting_key, setting_value
    FROM ucp_system_settings
    WHERE setting_key IN ('discord_client_id', 'discord_client_secret')
");
$stmt->execute();
$settings = [];
while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $settings[$row['setting_key']] = $row['setting_value'];
}

$clientId = $settings['discord_client_id'] ?? '';
if ($clientId === '') {
    ucp_json_error('Konfigurasi Discord OAuth belum tersedia.', 503);
}

$protocol = isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on' ? 'https' : 'http';
$baseUrl = $protocol . '://' . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']);
$redirectUri = rtrim($baseUrl, '/') . '/discord_callback.php';

ucp_session_start();
$_SESSION['discord_link_username'] = $username;
$oauthState = bin2hex(random_bytes(24));
$_SESSION['discord_oauth_state'] = $oauthState;

$discordUrl = 'https://discord.com/api/oauth2/authorize?' . http_build_query([
    'client_id' => $clientId,
    'redirect_uri' => $redirectUri,
    'response_type' => 'code',
    'scope' => 'identify guilds.join',
    'state' => $oauthState,
]);

header('Location: ' . $discordUrl);
exit;
