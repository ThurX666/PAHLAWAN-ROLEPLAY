<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/discord_helper.php';
ucp_session_start();

$code = $_GET['code'] ?? '';
$state = $_GET['state'] ?? '';
$username = $_SESSION['discord_link_username'] ?? '';
$expectedState = $_SESSION['discord_oauth_state'] ?? '';

if (empty($code) || empty($username) || empty($state) || empty($expectedState) || !hash_equals($expectedState, $state)) {
    die("Error: Invalid Session or Missing Code.");
}
unset($_SESSION['discord_oauth_state']);

$discordConfig = getDiscordSettings($pdo);
$client_id = (string)$discordConfig['client_id'];
$client_secret = (string)$discordConfig['client_secret'];
$bot_token = (string)$discordConfig['bot_token'];
$guild_id = (string)$discordConfig['guild_id'];
$role_warga_id = (string)$discordConfig['role_warga_id'];
$redirect_uri = (string)$discordConfig['redirect_uri'];

if ($client_id === '' || $client_secret === '' || !discord_redirect_uri_is_valid($redirect_uri)) {
    die('Konfigurasi Discord OAuth belum tersedia.');
}

// Tukar kode dengan Token
$token_url = "https://discord.com/api/oauth2/token";
$post_fields = [
    'client_id' => $client_id,
    'client_secret' => $client_secret,
    'grant_type' => 'authorization_code',
    'code' => $code,
    'redirect_uri' => $redirect_uri
];

$ch = curl_init($token_url);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($post_fields));
$response = curl_exec($ch);
curl_close($ch);

$token_data = json_decode($response, true);

if (isset($token_data['access_token'])) {
    $access_token = $token_data['access_token'];
    
    // Get User Data
    $ch = curl_init("https://discord.com/api/users/@me");
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, ["Authorization: Bearer $access_token"]);
    $user_response = curl_exec($ch);
    curl_close($ch);
    $user_data = json_decode($user_response, true);
    
    if (isset($user_data['id'])) {
        $discord_id = $user_data['id'];
        $discord_username = htmlspecialchars($user_data['username'] ?? 'Discord User');
        
        // --- TRANSAKSI: canonical link + inbox notification ---
        $conn->beginTransaction();
        try {
            // Canonical: update player_ucp.discord_id
            $update = $conn->prepare(
                "UPDATE player_ucp SET discord_id = :discord WHERE UCP = :username"
            );
            $update->execute(['discord' => $discord_id, 'username' => $username]);

            $conn->commit();
        } catch (PDOException $txEx) {
            $conn->rollBack();
            error_log("Discord callback: gagal update player_ucp.discord_id untuk {$username}: " . $txEx->getMessage());
            die("Gagal menyimpan tautan Discord. Silakan coba lagi.");
        }
        // --- END TRANSAKSI ---

        // Ambil session user setelah commit
        $stmtSession = $conn->prepare(
            "SELECT ID as id, UCP as username, admin_level FROM player_ucp WHERE UCP = :username LIMIT 1"
        );
        $stmtSession->execute(['username' => $username]);
        $sessionUser = $stmtSession->fetch(PDO::FETCH_ASSOC);
        if ($sessionUser) {
            ucp_create_session($sessionUser);
        }

        // --- INBOX NOTIFICATION: DISCORD LINK SUCCESS ---
        // Non-critical: failure here tidak boleh menggagalkan link
        $inboxTitle = "Discord Berhasil Ditautkan 🎉";
        $metadataObj = ['discordUsername' => $discord_username];
        $metadataJson = json_encode($metadataObj);

        try {
            $stmt_inbox = $conn->prepare(
                "INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata)
                 VALUES (:username, :title, :message, 'System', 0, 'DiscordLinked', :metadata)"
            );
            $stmt_inbox->execute([
                'username' => $username,
                'title' => $inboxTitle,
                'message' => 'Akun UCP Anda kini telah tertaut dengan akun Discord.',
                'metadata' => $metadataJson,
            ]);
        } catch (PDOException $inboxEx) {
            // jangan gagalkan flow utama; canonical link sudah tersimpan
            error_log("Discord callback: gagal insert inbox untuk {$username}: " . $inboxEx->getMessage());
        }
        // --- END INBOX NOTIFICATION ---

        // Add to Guild (if not already in) using OAuth access token
        if ($guild_id !== '' && $bot_token !== '') {
            $add_guild_url = "https://discord.com/api/guilds/$guild_id/members/$discord_id";
            $ch2 = curl_init($add_guild_url);
            curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, 'PUT');
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_HTTPHEADER, [
                "Authorization: Bot $bot_token",
                "Content-Type: application/json"
            ]);
            $payload = json_encode(['access_token' => $access_token]);
            curl_setopt($ch2, CURLOPT_POSTFIELDS, $payload);
            curl_exec($ch2);
            curl_close($ch2);

            // Update Nickname dan Role Warga menggunakan bot token
            setDiscordRole($guild_id, $discord_id, $role_warga_id, $bot_token);
            updateDiscordNickname($guild_id, $discord_id, $username, $bot_token);
        }
        
        echo "<h1>Autentikasi Discord Berhasil!</h1><p>Akun Discord anda telah terhubung dengan UCP. Anda kini memiliki role Warga di server kami.</p>";
        echo "<script>setTimeout(() => window.close(), 2000);</script>";
        exit;
    } else {
        die("Gagal mengambil data user dari Discord.");
    }
} else {
    die("Gagal menukar token dengan Discord.");
}
?>
