<?php

/**
 * Shared Website/UCP configuration bootstrap.
 *
 * Supported layouts:
 * - Repository: <website-root>/public/api
 * - Flattened deployment: <website-root>/api
 */

function app_normalize_path(string $path): string
{
    $resolved = realpath($path);
    $normalized = $resolved !== false ? $resolved : $path;
    return rtrim(str_replace(['/', '\\'], DIRECTORY_SEPARATOR, $normalized), DIRECTORY_SEPARATOR);
}

function app_detect_runtime_root(?string $apiDirectory = null): string
{
    $apiDirectory = app_normalize_path($apiDirectory ?? __DIR__);
    $apiParent = dirname($apiDirectory);

    if (strcasecmp(basename($apiParent), 'public') === 0) {
        return app_normalize_path(dirname($apiParent));
    }

    return app_normalize_path($apiParent);
}

function app_environment_path(?string $apiDirectory = null): string
{
    return app_detect_runtime_root($apiDirectory) . DIRECTORY_SEPARATOR . '.env';
}

function load_env_file(string $path): array
{
    if (!is_file($path) || !is_readable($path)) {
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

function get_app_env(): array
{
    static $env = null;
    if ($env === null) {
        $env = load_env_file(app_environment_path());
    }
    return $env;
}

function app_env(string $key, string $default = ''): string
{
    $serverValue = getenv($key);
    if ($serverValue !== false) {
        return trim((string)$serverValue);
    }

    $env = get_app_env();
    if (array_key_exists($key, $env)) {
        return trim((string)$env[$key]);
    }

    return $default;
}

function env_value(array $env, string $key, string $default = ''): string
{
    $serverValue = getenv($key);
    if ($serverValue !== false) {
        return trim((string)$serverValue);
    }

    if (array_key_exists($key, $env)) {
        return trim((string)$env[$key]);
    }

    return $default;
}

function app_config_diagnostics(): array
{
    $envPath = app_environment_path();
    $envExists = is_file($envPath);
    $envReadable = $envExists && is_readable($envPath);

    return [
        'env_loaded' => $envReadable,
        'env_source_path' => $envPath,
        'runtime_root' => app_detect_runtime_root(),
        'bootstrap_status' => $envReadable ? 'ready' : ($envExists ? 'env_unreadable' : 'env_missing'),
    ];
}
