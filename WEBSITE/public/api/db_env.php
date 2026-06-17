<?php
/**
 * Memuat konfigurasi database dari WEBSITE/.env
 * Default mengikuti GAMEMODE/gamemodes/utils/utils_defines.inc
 */

function load_env_file(string $path): array
{
    if (!file_exists($path)) {
        return [];
    }

    $vars = [];
    $lines = file($path, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
    if ($lines === false) {
        return [];
    }

    foreach ($lines as $line) {
        $line = trim($line);
        if ($line === '' || $line[0] === '#') {
            continue;
        }

        $separator = strpos($line, '=');
        if ($separator === false) {
            continue;
        }

        $key = trim(substr($line, 0, $separator));
        $value = trim(substr($line, $separator + 1));
        $value = trim($value, " \t\n\r\0\x0B\"'");

        if ($key !== '') {
            $vars[$key] = $value;
        }
    }

    return $vars;
}

function env_value(array $env, string $key, string $default = ''): string
{
    if (isset($env[$key]) && $env[$key] !== '') {
        return $env[$key];
    }

    $fromServer = getenv($key);
    if ($fromServer !== false && $fromServer !== '') {
        return $fromServer;
    }

    return $default;
}

function get_db_config(): array
{
    static $config = null;
    if ($config !== null) {
        return $config;
    }

    $envPath = dirname(__DIR__, 2) . DIRECTORY_SEPARATOR . '.env';
    $env = load_env_file($envPath);

    $config = [
        'host' => env_value($env, 'DB_HOST', 'localhost'),
        'port' => env_value($env, 'DB_PORT', '3306'),
        'user' => env_value($env, 'DB_USER', 'root'),
        'pass' => env_value($env, 'DB_PASS', ''),
        'name' => env_value($env, 'DB_NAME', 'arivena'),
    ];

    return $config;
}
