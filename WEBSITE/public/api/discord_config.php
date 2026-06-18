<?php

require_once __DIR__ . '/app_config.php';

const DISCORD_CONFIG_ENV_MAP = [
    'client_id' => ['env' => 'DISCORD_CLIENT_ID', 'db' => 'discord_client_id'],
    'client_secret' => ['env' => 'DISCORD_CLIENT_SECRET', 'db' => 'discord_client_secret'],
    'bot_token' => ['env' => 'DISCORD_BOT_TOKEN', 'db' => 'discord_bot_token'],
    'guild_id' => ['env' => 'DISCORD_GUILD_ID', 'db' => 'discord_guild_id'],
    'role_warga_id' => ['env' => 'DISCORD_ROLE_WARGA_ID', 'db' => 'discord_role_warga_id'],
    'redirect_uri' => ['env' => 'DISCORD_REDIRECT_URI', 'db' => 'discord_redirect_uri'],
];

function discord_derived_redirect_uri(): string
{
    $isHttps = !empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off';
    $protocol = $isHttps ? 'https' : 'http';
    $host = (string)($_SERVER['HTTP_HOST'] ?? '127.0.0.1:8000');
    $scriptDirectory = str_replace('\\', '/', dirname((string)($_SERVER['PHP_SELF'] ?? '/api/discord_callback.php')));

    return $protocol . '://' . $host . rtrim($scriptDirectory, '/') . '/discord_callback.php';
}

function discord_redirect_uri_is_valid(string $redirectUri): bool
{
    $parts = parse_url($redirectUri);
    return $redirectUri !== ''
        && $parts !== false
        && in_array(strtolower((string)($parts['scheme'] ?? '')), ['http', 'https'], true)
        && !empty($parts['host'])
        && !isset($parts['user'])
        && !isset($parts['pass'])
        && !isset($parts['query'])
        && !isset($parts['fragment'])
        && str_ends_with((string)($parts['path'] ?? ''), '/discord_callback.php');
}

function discord_database_settings(PDO $pdo): array
{
    $databaseKeys = array_column(DISCORD_CONFIG_ENV_MAP, 'db');
    $placeholders = implode(',', array_fill(0, count($databaseKeys), '?'));
    $stmt = $pdo->prepare(
        "SELECT setting_key, setting_value
         FROM ucp_system_settings
         WHERE setting_key IN ({$placeholders})"
    );
    $stmt->execute($databaseKeys);

    return $stmt->fetchAll(PDO::FETCH_KEY_PAIR) ?: [];
}

function discord_environment_settings(): array
{
    $environment = [];
    foreach (DISCORD_CONFIG_ENV_MAP as $mapping) {
        $environment[$mapping['env']] = app_env($mapping['env']);
    }
    return $environment;
}

function discord_build_config(
    array $databaseSettings,
    ?array $environmentSettings = null,
    ?string $derivedRedirectUri = null
): array {
    $environmentSettings ??= discord_environment_settings();
    $derivedRedirectUri ??= discord_derived_redirect_uri();
    $config = [];
    $sources = [];

    foreach (DISCORD_CONFIG_ENV_MAP as $name => $mapping) {
        $environmentValue = trim((string)($environmentSettings[$mapping['env']] ?? ''));
        $databaseValue = trim((string)($databaseSettings[$mapping['db']] ?? ''));

        if ($environmentValue !== '') {
            $config[$name] = $environmentValue;
            $sources[$name] = 'environment';
        } elseif ($databaseValue !== '') {
            $config[$name] = $databaseValue;
            $sources[$name] = 'database';
        } elseif ($name === 'redirect_uri') {
            $config[$name] = $derivedRedirectUri;
            $sources[$name] = 'derived';
        } else {
            $config[$name] = '';
            $sources[$name] = 'missing';
        }
    }

    $config['_sources'] = $sources;
    return $config;
}

function discord_load_config(PDO $pdo): array
{
    return discord_build_config(discord_database_settings($pdo));
}

function discord_config_diagnostics(array $config): array
{
    $fields = [];
    foreach (array_keys(DISCORD_CONFIG_ENV_MAP) as $name) {
        $fields[$name] = [
            'present' => trim((string)($config[$name] ?? '')) !== '',
            'source' => (string)($config['_sources'][$name] ?? 'missing'),
        ];
    }

    $redirectValid = discord_redirect_uri_is_valid((string)($config['redirect_uri'] ?? ''));
    return [
        'fields' => $fields,
        'redirect_uri_valid' => $redirectValid,
        'oauth_ready' => $fields['client_id']['present']
            && $fields['client_secret']['present']
            && $fields['redirect_uri']['present']
            && $redirectValid,
        'guild_sync_ready' => $fields['bot_token']['present']
            && $fields['guild_id']['present']
            && $fields['role_warga_id']['present'],
    ];
}
