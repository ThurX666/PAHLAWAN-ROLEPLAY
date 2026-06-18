<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/discord_config.php';

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) $action = $data['action'];
}

$adminUser = ucp_require_admin(10);

if ($action === 'get_settings') {
    $stmt = $pdo->query("SELECT setting_key, setting_value FROM ucp_system_settings");
    $results = $stmt->fetchAll(PDO::FETCH_KEY_PAIR);
    foreach (['discord_client_secret', 'discord_bot_token'] as $sensitiveKey) {
        if (!empty($results[$sensitiveKey])) {
            $results[$sensitiveKey] = '__CONFIGURED__';
        }
    }
    echo json_encode([
        "status" => "success",
        "settings" => $results ?: [],
        "discord_config_status" => discord_config_diagnostics(discord_load_config($pdo)),
    ]);
    exit;
}

if ($action === 'get_discord_config_status') {
    echo json_encode([
        "status" => "success",
        "discord_config_status" => discord_config_diagnostics(discord_load_config($pdo)),
    ]);
    exit;
}

if ($action === 'save_settings') {
    $settings = isset($_POST['settings']) ? json_decode($_POST['settings'], true) : [];
    
    $data = get_sanitized_json();
    if (isset($data['settings'])) $settings = $data['settings'];
    
    if (is_array($settings)) {
        $stmt = $pdo->prepare("INSERT INTO ucp_system_settings (setting_key, setting_value) VALUES (?, ?) ON DUPLICATE KEY UPDATE setting_value = ?");
        foreach ($settings as $key => $value) {
            if (in_array($key, ['discord_client_secret', 'discord_bot_token'], true) && ($value === '' || $value === '__CONFIGURED__')) {
                continue;
            }
            $stmt->execute([$key, $value, $value]);
        }
        
        // Log action
        try {
            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, ?, ?, ?)");
            $logStmt->execute([$adminUser['username'], 'SYSTEM_UPDATE', 'System', 'UCP Settings Updated']);
        } catch(Exception $e) { }

        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Invalid settings format"]);
    }
    exit;
}

echo json_encode(["status" => "error", "message" => "Unknown action"]);
?>
