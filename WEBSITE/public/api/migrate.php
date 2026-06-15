<?php
require_once __DIR__ . '/config.php';
try {
    $conn->exec("ALTER TABLE player_ucp ADD COLUMN OTP_Attempts INT DEFAULT 0");
} catch (Exception $e) {}

try {
    $conn->exec("ALTER TABLE player_ucp ADD COLUMN last_device VARCHAR(255) DEFAULT NULL");
} catch (Exception $e) {}

try {
    $conn->exec("ALTER TABLE player_ucp ADD COLUMN last_ip VARCHAR(100) DEFAULT NULL");
} catch (Exception $e) {}

try {
    $conn->exec("ALTER TABLE player_ucp ADD COLUMN last_location VARCHAR(255) DEFAULT NULL");
} catch (Exception $e) {}

// Discord Integration
try {
    $conn->exec("ALTER TABLE player_ucp ADD COLUMN discord_id VARCHAR(50) DEFAULT NULL");
} catch (Exception $e) {}

try {
    $conn->exec("INSERT IGNORE INTO `ucp_system_settings` (`setting_key`, `setting_value`) VALUES 
        ('discord_client_id', ''),
        ('discord_client_secret', ''),
        ('discord_role_warga_id', '')
    ");
} catch (Exception $e) {}

echo "Migration complete";
?>
