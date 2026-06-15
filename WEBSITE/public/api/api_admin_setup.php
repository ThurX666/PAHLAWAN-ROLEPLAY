<?php
require_once __DIR__ . '/config.php';

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) $action = $data['action'];
}

// Role-Based Access Control
$admin_level = isset($_GET['adminLevel']) ? (int)$_GET['adminLevel'] : (isset($_POST['adminLevel']) ? (int)$_POST['adminLevel'] : 0);
if ($admin_level === 0 && isset($data['adminLevel'])) {
    $admin_level = (int)$data['adminLevel'];
}

if ($action === 'get_settings') {
    $stmt = $pdo->query("SELECT setting_key, setting_value FROM ucp_system_settings");
    $results = $stmt->fetchAll(PDO::FETCH_KEY_PAIR);
    echo json_encode(["status" => "success", "settings" => $results ?: []]);
    exit;
}

if ($action === 'save_settings') {
    $settings = isset($_POST['settings']) ? json_decode($_POST['settings'], true) : [];
    
    $data = get_sanitized_json();
    if (isset($data['settings'])) $settings = $data['settings'];
    
    if (is_array($settings)) {
        $stmt = $pdo->prepare("INSERT INTO ucp_system_settings (setting_key, setting_value) VALUES (?, ?) ON DUPLICATE KEY UPDATE setting_value = ?");
        foreach ($settings as $key => $value) {
            $stmt->execute([$key, $value, $value]);
        }
        
        // Log action
        try {
            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, ?, ?, ?)");
            $logStmt->execute(['Admin UCP', 'SYSTEM_UPDATE', 'System', 'UCP Settings Updated']);
        } catch(Exception $e) { }

        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Invalid settings format"]);
    }
    exit;
}

echo json_encode(["status" => "error", "message" => "Unknown action"]);
?>
