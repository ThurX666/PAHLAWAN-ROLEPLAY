<?php
require_once __DIR__ . '/config.php';

$username = $_GET['username'] ?? '';

if (empty($username)) {
    die("Invalid request");
}

$stmt = $conn->prepare("SELECT setting_key, setting_value FROM ucp_system_settings WHERE setting_key IN ('discord_client_id', 'discord_client_secret')");
$stmt->execute();
$settings = [];
while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $settings[$row['setting_key']] = $row['setting_value'];
}

$client_id = $settings['discord_client_id'] ?? '';

if (empty($client_id)) {
    // Mode Simulasi jika belum ada pengaturan Discord
    $update = $conn->prepare("UPDATE player_ucp SET discord_id = 'SIMULATED_DISCORD_ID' WHERE UCP = :username");
    $update->execute(['username' => $username]);
    
    // --- INBOX NOTIFICATION: DISCORD LINK SUCCESS (SIMULATED) ---
    $discord_username = "Simulated User";
    $inboxTitle = "Discord Berhasil Ditautkan 🎉";
    
    $metadataObj = [
        'discordUsername' => $discord_username
    ];
    $metadataJson = json_encode($metadataObj);

    $stmt_inbox = $conn->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (:username, :title, :message, 'System', 0, 'DiscordLinked', :metadata)");
    $stmt_inbox->execute([
        'username' => $username, 
        'title' => $inboxTitle, 
        'message' => 'Akun UCP Anda kini telah tertaut dengan akun Discord.',
        'metadata' => $metadataJson
    ]);
    // --- END INBOX NOTIFICATION ---

    echo "<h1>Simulasi Discord Link Berhasil</h1><p>Discord Client ID belum disetting. Jendela ini akan tertutup otomatis.</p>";
    echo "<script>setTimeout(() => window.close(), 1500);</script>";
    exit;
}

// Redirect ke Discord OAuth
$protocol = isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on' ? "https" : "http";
$base_url = $protocol . "://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']);
$redirect_uri = urlencode(rtrim($base_url, '/') . "/discord_callback.php");

// Simpan username di session agar bisa diambil saat callback
session_start();
$_SESSION['discord_link_username'] = $username;

$discord_url = "https://discord.com/api/oauth2/authorize?client_id={$client_id}&redirect_uri={$redirect_uri}&response_type=code&scope=identify%20guilds.join";
header("Location: $discord_url");
exit;
?>
