<?php
/**
 * Database configuration sourced through the shared Website/UCP bootstrap.
 * Defaults follow GAMEMODE/gamemodes/utils/utils_defines.inc.
 */

require_once __DIR__ . '/app_config.php';

function get_db_config(): array
{
    static $config = null;
    if ($config !== null) {
        return $config;
    }

    $env = get_app_env();
    $config = [
        'host' => env_value($env, 'DB_HOST', 'localhost'),
        'port' => env_value($env, 'DB_PORT', '3306'),
        'user' => env_value($env, 'DB_USER', 'root'),
        'pass' => env_value($env, 'DB_PASS', ''),
        'name' => env_value($env, 'DB_NAME', 'arivena'),
    ];

    return $config;
}
