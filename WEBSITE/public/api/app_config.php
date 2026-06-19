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

function app_mail_config(): array
{
    static $config = null;
    if ($config !== null) {
        return $config;
    }

    $env = get_app_env();
    $config = [
        'host' => env_value($env, 'SMTP_HOST', ''),
        'port' => env_value($env, 'SMTP_PORT', ''),
        'encryption' => strtolower(env_value($env, 'SMTP_ENCRYPTION', '')),
        'user' => env_value($env, 'SMTP_USER', ''),
        'pass' => env_value($env, 'SMTP_PASS', ''),
        'from_email' => env_value($env, 'SMTP_FROM_EMAIL', ''),
        'from_name' => env_value($env, 'SMTP_FROM_NAME', ''),
    ];

    return $config;
}

function app_mail_loader_status(?string $apiDirectory = null): array
{
    $apiDirectory = app_normalize_path($apiDirectory ?? __DIR__);
    $websiteRoot = app_detect_runtime_root($apiDirectory);

    $composerAutoloadPath = $websiteRoot . DIRECTORY_SEPARATOR . 'vendor' . DIRECTORY_SEPARATOR . 'autoload.php';
    $composerReady = is_file($composerAutoloadPath) && is_readable($composerAutoloadPath);

    $legacyDirectory = $apiDirectory . DIRECTORY_SEPARATOR . 'PHPMailer' . DIRECTORY_SEPARATOR . 'src';
    $legacyFiles = [
        $legacyDirectory . DIRECTORY_SEPARATOR . 'Exception.php',
        $legacyDirectory . DIRECTORY_SEPARATOR . 'PHPMailer.php',
        $legacyDirectory . DIRECTORY_SEPARATOR . 'SMTP.php',
    ];
    $legacyReady = true;
    foreach ($legacyFiles as $legacyFile) {
        if (!is_file($legacyFile) || !is_readable($legacyFile)) {
            $legacyReady = false;
            break;
        }
    }

    return [
        'ready' => $composerReady || $legacyReady,
        'selected_loader' => $composerReady ? 'composer' : ($legacyReady ? 'legacy' : 'missing'),
        'composer' => [
            'path' => $composerAutoloadPath,
            'status' => $composerReady ? 'ready' : (is_file($composerAutoloadPath) ? 'unreadable' : 'missing'),
        ],
        'legacy' => [
            'path' => $legacyDirectory,
            'status' => $legacyReady ? 'ready' : (is_dir($legacyDirectory) ? 'incomplete' : 'missing'),
        ],
    ];
}

function app_mail_diagnostics(): array
{
    $mailConfig = app_mail_config();
    $requiredFields = [
        'SMTP_HOST' => $mailConfig['host'],
        'SMTP_PORT' => $mailConfig['port'],
        'SMTP_ENCRYPTION' => $mailConfig['encryption'],
        'SMTP_USER' => $mailConfig['user'],
        'SMTP_PASS' => $mailConfig['pass'],
        'SMTP_FROM_EMAIL' => $mailConfig['from_email'],
        'SMTP_FROM_NAME' => $mailConfig['from_name'],
    ];

    $missingFields = [];
    foreach ($requiredFields as $field => $value) {
        if (trim((string) $value) === '') {
            $missingFields[] = $field;
        }
    }

    $loaderStatus = app_mail_loader_status();

    return [
        'smtp_ready' => count($missingFields) === 0,
        'missing_fields' => $missingFields,
        'loader_ready' => (bool) $loaderStatus['ready'],
        'loader_type' => $loaderStatus['selected_loader'],
        'loader_paths' => [
            'composer' => $loaderStatus['composer'],
            'legacy' => $loaderStatus['legacy'],
        ],
    ];
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
        'mail_runtime' => app_mail_diagnostics(),
    ];
}
