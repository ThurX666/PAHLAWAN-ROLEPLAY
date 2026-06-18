<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/discord_config.php';

$username = ucp_require_pending_username($_GET['username'] ?? null);
$discordConfig = discord_load_config($pdo);
$clientId = (string)$discordConfig['client_id'];
$redirectUri = (string)$discordConfig['redirect_uri'];
if ($clientId === '' || !discord_redirect_uri_is_valid($redirectUri)) {
    ucp_json_error('Konfigurasi Discord OAuth belum tersedia.', 503);
}

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
