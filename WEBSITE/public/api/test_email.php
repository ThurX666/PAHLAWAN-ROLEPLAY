<?php
if (!isset($_SERVER['REQUEST_METHOD'])) {
    $_SERVER['REQUEST_METHOD'] = 'GET';
}

require_once __DIR__ . '/config.php';
require_once __DIR__ . '/mailer_helper.php';

header('Content-Type: application/json');

if (!function_exists('app_runtime_is_cli')) {
    function app_runtime_is_cli(): bool
    {
        return PHP_SAPI === 'cli';
    }
}

if (!function_exists('email_runtime_diagnostic_payload')) {
    function email_runtime_diagnostic_payload(): array
    {
        $policy = mailModePolicy();
        $loader = app_mail_loader_status();
        $mailDiagnostics = app_mail_diagnostics();

        return [
            'status' => 'ok',
            'mode' => 'diagnostic_only',
            'authorized' => true,
            'environment' => $policy['environment'],
            'delivery_mode' => $policy['delivery_mode'],
            'preview_allowed' => $policy['preview_allowed'],
            'mail_runtime' => [
                'smtp_ready' => $mailDiagnostics['smtp_ready'],
                'missing_fields' => $mailDiagnostics['missing_fields'],
                'loader_ready' => $mailDiagnostics['loader_ready'],
                'loader_type' => $mailDiagnostics['loader_type'],
                'loader_paths' => [
                    'composer' => [
                        'path' => $loader['composer']['path'],
                        'status' => $loader['composer']['status'],
                    ],
                    'legacy' => [
                        'path' => $loader['legacy']['path'],
                        'status' => $loader['legacy']['status'],
                    ],
                ],
            ],
            'message' => 'Diagnostic only. No email was sent.',
        ];
    }
}

$isCli = app_runtime_is_cli();
$isLocal = isLocalDevEnvironment();

if (!$isCli) {
    ucp_require_admin(10);
}

if (!$isCli && !$isLocal) {
    http_response_code(403);
    echo json_encode([
        'status' => 'error',
        'message' => 'Diagnostic endpoint is available only in local mode or CLI.',
    ]);
    exit;
}

echo json_encode(email_runtime_diagnostic_payload());
