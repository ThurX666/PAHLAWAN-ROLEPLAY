<?php

require_once dirname(__DIR__) . '/public/api/db_env.php';
require_once dirname(__DIR__) . '/public/api/discord_config.php';

function discord_config_test_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

$databaseSettings = [
    'discord_client_id' => 'db-client',
    'discord_client_secret' => 'db-secret',
    'discord_bot_token' => 'db-token',
    'discord_guild_id' => 'db-guild',
    'discord_role_warga_id' => 'db-role',
    'discord_redirect_uri' => 'https://database.example/api/discord_callback.php',
];
$environmentSettings = [
    'DISCORD_CLIENT_ID' => 'env-client',
    'DISCORD_CLIENT_SECRET' => 'env-secret',
    'DISCORD_BOT_TOKEN' => '',
    'DISCORD_GUILD_ID' => 'env-guild',
    'DISCORD_ROLE_WARGA_ID' => '',
    'DISCORD_REDIRECT_URI' => 'http://127.0.0.1:8000/api/discord_callback.php',
];

$config = discord_build_config(
    $databaseSettings,
    $environmentSettings,
    'http://derived.example/api/discord_callback.php'
);
discord_config_test_assert($config['client_id'] === 'env-client', 'Environment client ID did not take priority.');
discord_config_test_assert($config['client_secret'] === 'env-secret', 'Environment client secret did not take priority.');
discord_config_test_assert($config['bot_token'] === 'db-token', 'Database bot-token fallback failed.');
discord_config_test_assert($config['guild_id'] === 'env-guild', 'Environment guild ID did not take priority.');
discord_config_test_assert($config['role_warga_id'] === 'db-role', 'Database role fallback failed.');
discord_config_test_assert(
    $config['redirect_uri'] === 'http://127.0.0.1:8000/api/discord_callback.php',
    'Local redirect URI was not preserved.'
);

$diagnostics = discord_config_diagnostics($config);
discord_config_test_assert($diagnostics['oauth_ready'], 'OAuth diagnostics should report ready.');
discord_config_test_assert($diagnostics['guild_sync_ready'], 'Guild-sync diagnostics should report ready.');
$encodedDiagnostics = json_encode($diagnostics);
foreach (['env-secret', 'db-token', 'env-client', 'env-guild', 'db-role'] as $privateValue) {
    discord_config_test_assert(
        !str_contains((string)$encodedDiagnostics, $privateValue),
        'Diagnostics exposed a Discord configuration value.'
    );
}

echo "discord_config_contract_test=passed\n";
