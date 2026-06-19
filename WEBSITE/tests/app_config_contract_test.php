<?php

require_once dirname(__DIR__) . '/public/api/app_config.php';

function app_config_test_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

$separator = DIRECTORY_SEPARATOR;
$testRoot = sys_get_temp_dir() . $separator . 'phrp-app-config-' . bin2hex(random_bytes(4));
$repoApi = $testRoot . $separator . 'WEBSITE' . $separator . 'public' . $separator . 'api';
$flatApi = $testRoot . $separator . 'pahlawan_roleplay' . $separator . 'api';

foreach ([$repoApi, $flatApi] as $directory) {
    if (!mkdir($directory, 0700, true) && !is_dir($directory)) {
        throw new RuntimeException('Could not create configuration test directory.');
    }
}

$repoVendor = dirname(dirname($repoApi)) . $separator . 'vendor';
$flatLegacy = $flatApi . $separator . 'PHPMailer' . $separator . 'src';
if (!mkdir($repoVendor, 0700, true) && !is_dir($repoVendor)) {
    throw new RuntimeException('Could not create repository vendor directory.');
}
if (!mkdir($flatLegacy, 0700, true) && !is_dir($flatLegacy)) {
    throw new RuntimeException('Could not create flattened legacy mail directory.');
}
file_put_contents($repoVendor . $separator . 'autoload.php', "<?php\n");
foreach (['Exception.php', 'PHPMailer.php', 'SMTP.php'] as $legacyFile) {
    file_put_contents($flatLegacy . $separator . $legacyFile, "<?php\n");
}

app_config_test_assert(
    app_detect_runtime_root($repoApi) === dirname(dirname($repoApi)),
    'Repository public/api layout did not resolve to the Website root.'
);
app_config_test_assert(
    app_detect_runtime_root($flatApi) === dirname($flatApi),
    'Flattened api layout did not resolve to the deployment root.'
);
app_config_test_assert(
    app_environment_path($repoApi) === dirname(dirname($repoApi)) . $separator . '.env',
    'Repository environment path is incorrect.'
);
app_config_test_assert(
    app_environment_path($flatApi) === dirname($flatApi) . $separator . '.env',
    'Flattened deployment environment path is incorrect.'
);

$repoLoader = app_mail_loader_status($repoApi);
app_config_test_assert($repoLoader['selected_loader'] === 'composer', 'Repository layout should prefer the Composer loader.');
app_config_test_assert($repoLoader['composer']['status'] === 'ready', 'Repository Composer loader should be ready.');

$flatLoader = app_mail_loader_status($flatApi);
app_config_test_assert($flatLoader['selected_loader'] === 'legacy', 'Flattened layout should detect the legacy fallback loader.');
app_config_test_assert($flatLoader['legacy']['status'] === 'ready', 'Flattened legacy loader should be ready.');

putenv('APP_CONFIG_CONTRACT_VALUE=');
app_config_test_assert(
    app_env('APP_CONFIG_CONTRACT_VALUE', 'unsafe-fallback') === '',
    'An explicit blank process variable must override file/default configuration.'
);
putenv('APP_CONFIG_CONTRACT_VALUE');

$diagnostics = app_config_diagnostics();
app_config_test_assert(
    array_keys($diagnostics) === ['env_loaded', 'env_source_path', 'runtime_root', 'bootstrap_status', 'mail_runtime'],
    'Configuration diagnostics contain unexpected fields.'
);
app_config_test_assert(
    array_keys($diagnostics['mail_runtime']) === ['smtp_ready', 'missing_fields', 'loader_ready', 'loader_type', 'loader_paths'],
    'Mail runtime diagnostics contain unexpected fields.'
);
app_config_test_assert(
    !str_contains(json_encode($diagnostics), 'NVIDIA_NIM_API_KEY'),
    'Configuration diagnostics exposed a secret name.'
);
foreach (['your-smtp-password', 'your-smtp-username'] as $privateValue) {
    app_config_test_assert(
        !str_contains((string) json_encode($diagnostics), $privateValue),
        'Configuration diagnostics exposed a mail runtime value.'
    );
}

foreach ([
    $repoVendor,
    dirname($repoApi),
    dirname($repoApi, 2),
    $flatLegacy,
    dirname($flatLegacy),
    dirname(dirname($flatLegacy)),
    $flatApi,
    dirname($flatApi),
    $testRoot
] as $directory) {
    if (is_dir($directory)) {
        @rmdir($directory);
    }
}

echo "app_config_contract_test=passed\n";
