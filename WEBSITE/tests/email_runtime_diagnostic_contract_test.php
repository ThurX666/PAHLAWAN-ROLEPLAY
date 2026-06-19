<?php

require_once dirname(__DIR__) . '/public/api/app_config.php';
require_once dirname(__DIR__) . '/public/api/mailer_helper.php';

function email_runtime_diag_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

function email_runtime_diag_source(string $filePath): string
{
    $source = file_get_contents($filePath);
    if ($source === false) {
        throw new RuntimeException('Tidak dapat membaca file diagnostic endpoint.');
    }

    $source = preg_replace('/^\s*<\?php\s*/', '', $source, 1);
    $source = preg_replace('/\?>\s*$/', '', $source, 1);
    $source = preg_replace('/^\s*require_once .*config\.php.*;\R/m', '', $source);
    $source = preg_replace('/^\s*require_once .*mailer_helper\.php.*;\R/m', '', $source);
    $source = preg_replace('/\bexit\s*\([^;]*\)\s*;/', 'return;', $source);
    $source = preg_replace('/\bexit\s*;/', 'return;', $source);

    return (string) $source;
}

function ucp_require_admin(int $level): void
{
    $GLOBALS['__email_diag_required_level'] = $level;
}

function app_runtime_is_cli(): bool
{
    return (bool) ($GLOBALS['__email_diag_is_cli'] ?? false);
}

function run_email_runtime_diagnostic(bool $localMode, bool $cliMode): array
{
    putenv('APP_ENV=' . ($localMode ? 'local' : 'production'));
    putenv('UCP_LOCAL_MAIL_MODE=smtp');

    $GLOBALS['__email_diag_required_level'] = null;
    $GLOBALS['__email_diag_is_cli'] = $cliMode;
    $_SERVER = ['REQUEST_METHOD' => 'GET'];

    ob_start();
    eval(email_runtime_diag_source(dirname(__DIR__) . '/public/api/test_email.php'));
    $raw = ob_get_clean();
    $json = json_decode((string) $raw, true);

    if ($cliMode) {
        email_runtime_diag_assert(is_array($json), 'CLI diagnostic harus mengembalikan JSON.');
    }

    putenv('APP_ENV');
    putenv('UCP_LOCAL_MAIL_MODE');
    unset($GLOBALS['__email_diag_is_cli']);

    return [
        'json' => $json,
        'raw' => (string) $raw,
        'required_level' => $GLOBALS['__email_diag_required_level'],
    ];
}

$source = file_get_contents(dirname(__DIR__) . '/public/api/test_email.php');
email_runtime_diag_assert($source !== false, 'test_email.php tidak dapat dibaca.');
email_runtime_diag_assert(!str_contains($source, 'sendVerificationEmail('), 'Diagnostic endpoint tidak boleh mengirim verification email.');
email_runtime_diag_assert(!str_contains($source, 'sendForgotPasswordEmail('), 'Diagnostic endpoint tidak boleh mengirim forgot email.');

$localCliRun = run_email_runtime_diagnostic(true, true);
email_runtime_diag_assert($localCliRun['json']['mode'] === 'diagnostic_only', 'Diagnostic payload harus menandai mode diagnostic_only.');
email_runtime_diag_assert($localCliRun['json']['message'] === 'Diagnostic only. No email was sent.', 'Diagnostic payload harus menyatakan tidak ada email yang dikirim.');
email_runtime_diag_assert($localCliRun['json']['mail_runtime']['loader_type'] !== '', 'Diagnostic payload harus menyertakan status loader tanpa secret.');
foreach (['your-smtp-password', 'your-smtp-username', 'smtp-pass', 'smtp-user', 'Set-Cookie', 'token'] as $secretToken) {
    email_runtime_diag_assert(!str_contains((string) $localCliRun['raw'], $secretToken), 'Diagnostic payload membocorkan nilai sensitif: ' . $secretToken);
}

$prodRun = run_email_runtime_diagnostic(false, false);
email_runtime_diag_assert($prodRun['required_level'] === 10, 'Diagnostic endpoint harus tetap meminta admin level 10 di mode HTTP.');
email_runtime_diag_assert($prodRun['json']['status'] === 'error', 'Diagnostic endpoint non-local harus ditolak.');
email_runtime_diag_assert($localCliRun['json']['status'] === 'ok', 'Diagnostic endpoint local CLI harus mengembalikan status ok.');

echo "email_runtime_diagnostic_contract_test=passed\n";
