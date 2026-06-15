<?php
// helpers/discord_helper.php
function getDiscordSettings($conn) {
    $stmt = $conn->query("SELECT setting_key, setting_value FROM ucp_system_settings WHERE setting_key LIKE 'discord_%'");
    $settings = [];
    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
        $settings[$row['setting_key']] = $row['setting_value'];
    }
    return $settings;
}

function callDiscordBotAPI($endpoint, $method = 'GET', $data = null, $botToken) {
    if (empty($botToken)) return ['status' => 'error', 'message' => 'Bot Token not configured.'];
    
    $url = "https://discord.com/api/v10/" . ltrim($endpoint, '/');
    $ch = curl_init($url);
    
    $headers = [
        'Authorization: Bot ' . $botToken,
        'Content-Type: application/json'
    ];
    
    if ($method === 'POST') {
        curl_setopt($ch, CURLOPT_POST, true);
        if ($data) curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    } elseif ($method === 'PUT') {
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'PUT');
        if ($data) curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    } elseif ($method === 'PATCH') {
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'PATCH');
        if ($data) curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    } elseif ($method === 'DELETE') {
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'DELETE');
    }
    
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    
    $response = curl_exec($ch);
    $httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);
    
    return [
        'status' => ($httpCode >= 200 && $httpCode < 300) ? 'success' : 'error',
        'code' => $httpCode,
        'response' => json_decode($response, true)
    ];
}

function setDiscordRole($guildId, $userId, $roleId, $botToken) {
    if (empty($guildId) || empty($roleId) || empty($botToken)) return false;
    $endpoint = "/guilds/{$guildId}/members/{$userId}/roles/{$roleId}";
    $res = callDiscordBotAPI($endpoint, 'PUT', null, $botToken);
    return $res['status'] === 'success';
}

function updateDiscordNickname($guildId, $userId, $nickname, $botToken) {
    if (empty($guildId) || empty($botToken)) return false;
    $endpoint = "/guilds/{$guildId}/members/{$userId}";
    $res = callDiscordBotAPI($endpoint, 'PATCH', ['nick' => substr($nickname, 0, 32)], $botToken);
    return $res['status'] === 'success';
}

function checkGuildMember($guildId, $userId, $botToken) {
    if (empty($guildId) || empty($botToken)) return false;
    $endpoint = "/guilds/{$guildId}/members/{$userId}";
    $res = callDiscordBotAPI($endpoint, 'GET', null, $botToken);
    return $res['status'] === 'success' && isset($res['response']['user']);
}
?>
