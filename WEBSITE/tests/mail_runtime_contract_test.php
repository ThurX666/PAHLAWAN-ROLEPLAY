<?php

require_once dirname(__DIR__) . '/public/api/mailer_helper.php';

function mail_runtime_test_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

$localPreview = mailModePolicy('local', 'preview');
mail_runtime_test_assert($localPreview['delivery_mode'] === 'preview', 'Local preview mode should be allowed.');
mail_runtime_test_assert($localPreview['preview_allowed'], 'Local preview mode should report preview as allowed.');

$productionPreview = mailModePolicy('production', 'preview');
mail_runtime_test_assert($productionPreview['failure_category'] === 'preview_forbidden', 'Production preview mode must be forbidden.');

$invalidLocalMode = mailModePolicy('local', 'preview_bypass');
mail_runtime_test_assert($invalidLocalMode['failure_category'] === 'mail_mode_invalid', 'Legacy preview_bypass mode must be rejected.');

$missingCredentials = mailRuntimeStatus(
    mailModePolicy('local', 'smtp'),
    [
        'host' => 'smtp.example.com',
        'port' => '587',
        'encryption' => 'tls',
        'user' => '',
        'pass' => '',
        'from_email' => 'no-reply@example.com',
        'from_name' => 'Pahlawan Roleplay',
    ],
    ['ready' => true, 'selected_loader' => 'composer']
);
mail_runtime_test_assert($missingCredentials['failure_category'] === 'smtp_credentials_missing', 'Missing SMTP credentials should fail with the credential category.');

$invalidConfiguration = mailRuntimeStatus(
    mailModePolicy('local', 'smtp'),
    [
        'host' => 'smtp.example.com',
        'port' => '0',
        'encryption' => 'invalid',
        'user' => 'smtp-user',
        'pass' => 'smtp-pass',
        'from_email' => '',
        'from_name' => 'Pahlawan Roleplay',
    ],
    ['ready' => true, 'selected_loader' => 'composer']
);
mail_runtime_test_assert($invalidConfiguration['failure_category'] === 'smtp_configuration_invalid', 'Invalid SMTP configuration should fail with the configuration category.');

$missingDependency = mailRuntimeStatus(
    mailModePolicy('production', 'smtp'),
    [
        'host' => 'smtp.example.com',
        'port' => '587',
        'encryption' => 'tls',
        'user' => 'smtp-user',
        'pass' => 'smtp-pass',
        'from_email' => 'no-reply@example.com',
        'from_name' => 'Pahlawan Roleplay',
    ],
    ['ready' => false, 'selected_loader' => 'missing']
);
mail_runtime_test_assert($missingDependency['failure_category'] === 'mail_dependency_missing', 'Missing PHPMailer should fail with the dependency category.');

putenv('APP_ENV=production');
putenv('UCP_LOCAL_MAIL_MODE=preview');
mail_runtime_test_assert(!isLocalOtpPreviewMode(), 'Preview must not activate in production.');
mail_runtime_test_assert(!shouldBypassLocalPreviewMail(), 'Production must never bypass mail through preview.');
putenv('APP_ENV');
putenv('UCP_LOCAL_MAIL_MODE');

setLastMailFailureCategory('smtp_transport_failed');
mail_runtime_test_assert(
    localMailTroubleshootingMessage() === 'Local dev OTP email is not configured: SMTP transport failed.',
    'Troubleshooting message should use the sanitized failure category.'
);
setLastMailFailureCategory(null);

echo "mail_runtime_contract_test=passed\n";
