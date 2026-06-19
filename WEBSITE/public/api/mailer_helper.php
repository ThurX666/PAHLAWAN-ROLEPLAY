<?php

require_once __DIR__ . '/app_config.php';

// Import PHPMailer classes into the global namespace
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

function smtpCredentialsAvailable(): bool {
    $mailConfig = app_mail_config();
    return $mailConfig['user'] !== '' && $mailConfig['pass'] !== '';
}

function isLocalDevEnvironment(): bool {
    $appEnv = strtolower((string) app_env('APP_ENV', 'production'));
    return in_array($appEnv, ['local', 'development', 'dev'], true);
}

function localMailMode(): string {
    return strtolower((string) app_env('UCP_LOCAL_MAIL_MODE', 'smtp'));
}

function setLastMailFailureCategory(?string $category): void {
    $GLOBALS['phrp_mail_last_failure_category'] = $category;
}

function lastMailFailureCategory(): ?string {
    return $GLOBALS['phrp_mail_last_failure_category'] ?? null;
}

function hasMailFailureCategory(): bool {
    return lastMailFailureCategory() !== null;
}

function mailFailureMessage(string $category): string {
    $messages = [
        'mail_mode_invalid' => 'mail mode is invalid for the current environment',
        'preview_forbidden' => 'preview mode is forbidden outside local development',
        'smtp_credentials_missing' => 'SMTP credentials are not configured',
        'smtp_configuration_invalid' => 'SMTP configuration is incomplete or invalid',
        'mail_dependency_missing' => 'PHPMailer dependency is unavailable',
        'smtp_transport_failed' => 'SMTP transport failed',
    ];

    return $messages[$category] ?? 'mail delivery failed';
}

function mailModePolicy(?string $appEnv = null, ?string $mode = null): array {
    $appEnv = strtolower(trim((string) ($appEnv ?? app_env('APP_ENV', 'production'))));
    $mode = strtolower(trim((string) ($mode ?? localMailMode())));
    $isLocal = in_array($appEnv, ['local', 'development', 'dev'], true);

    if ($isLocal) {
        if ($mode === 'preview') {
            return [
                'environment' => $appEnv,
                'requested_mode' => $mode,
                'is_local' => true,
                'delivery_mode' => 'preview',
                'preview_allowed' => true,
                'failure_category' => null,
            ];
        }

        if ($mode === '' || $mode === 'smtp' || $mode === 'error') {
            return [
                'environment' => $appEnv,
                'requested_mode' => $mode === '' ? 'smtp' : $mode,
                'is_local' => true,
                'delivery_mode' => 'smtp',
                'preview_allowed' => false,
                'failure_category' => null,
            ];
        }

        return [
            'environment' => $appEnv,
            'requested_mode' => $mode,
            'is_local' => true,
            'delivery_mode' => 'blocked',
            'preview_allowed' => false,
            'failure_category' => 'mail_mode_invalid',
        ];
    }

    if ($mode === 'preview' || $mode === 'preview_bypass') {
        return [
            'environment' => $appEnv,
            'requested_mode' => $mode,
            'is_local' => false,
            'delivery_mode' => 'blocked',
            'preview_allowed' => false,
            'failure_category' => 'preview_forbidden',
        ];
    }

    if ($mode !== '' && $mode !== 'smtp') {
        return [
            'environment' => $appEnv,
            'requested_mode' => $mode,
            'is_local' => false,
            'delivery_mode' => 'blocked',
            'preview_allowed' => false,
            'failure_category' => 'mail_mode_invalid',
        ];
    }

    return [
        'environment' => $appEnv,
        'requested_mode' => $mode === '' ? 'smtp' : $mode,
        'is_local' => false,
        'delivery_mode' => 'smtp',
        'preview_allowed' => false,
        'failure_category' => null,
    ];
}

function smtpConfigurationStatus(?array $mailConfig = null): array {
    $mailConfig = $mailConfig ?? app_mail_config();
    $missingCredentials = [];
    foreach (['user' => 'SMTP_USER', 'pass' => 'SMTP_PASS'] as $field => $label) {
        if (trim((string) ($mailConfig[$field] ?? '')) === '') {
            $missingCredentials[] = $label;
        }
    }

    if ($missingCredentials !== []) {
        return [
            'ready' => false,
            'failure_category' => 'smtp_credentials_missing',
            'missing' => $missingCredentials,
        ];
    }

    $missingConfiguration = [];
    foreach (['host' => 'SMTP_HOST', 'port' => 'SMTP_PORT', 'encryption' => 'SMTP_ENCRYPTION', 'from_email' => 'SMTP_FROM_EMAIL', 'from_name' => 'SMTP_FROM_NAME'] as $field => $label) {
        if (trim((string) ($mailConfig[$field] ?? '')) === '') {
            $missingConfiguration[] = $label;
        }
    }

    $port = (int) ($mailConfig['port'] ?? 0);
    $encryption = strtolower(trim((string) ($mailConfig['encryption'] ?? '')));
    $validEncryption = in_array($encryption, ['tls', 'starttls', 'ssl', 'smtps', 'none'], true);
    $validPort = $port >= 1 && $port <= 65535;

    if ($missingConfiguration !== [] || !$validPort || !$validEncryption) {
        return [
            'ready' => false,
            'failure_category' => 'smtp_configuration_invalid',
            'missing' => $missingConfiguration,
            'valid_port' => $validPort,
            'valid_encryption' => $validEncryption,
        ];
    }

    return [
        'ready' => true,
        'failure_category' => null,
        'missing' => [],
        'valid_port' => true,
        'valid_encryption' => true,
    ];
}

function mailRuntimeStatus(?array $policy = null, ?array $mailConfig = null, ?array $loaderStatus = null): array {
    $policy = $policy ?? mailModePolicy();
    $loaderStatus = $loaderStatus ?? app_mail_loader_status();
    $configurationStatus = smtpConfigurationStatus($mailConfig);

    if ($policy['failure_category'] !== null) {
        return [
            'ready' => false,
            'delivery_mode' => $policy['delivery_mode'],
            'failure_category' => $policy['failure_category'],
            'loader_type' => $loaderStatus['selected_loader'],
        ];
    }

    if ($policy['delivery_mode'] === 'preview') {
        return [
            'ready' => true,
            'delivery_mode' => 'preview',
            'failure_category' => null,
            'loader_type' => $loaderStatus['selected_loader'],
        ];
    }

    if (!$configurationStatus['ready']) {
        return [
            'ready' => false,
            'delivery_mode' => 'smtp',
            'failure_category' => $configurationStatus['failure_category'],
            'loader_type' => $loaderStatus['selected_loader'],
        ];
    }

    if (!(bool) ($loaderStatus['ready'] ?? false)) {
        return [
            'ready' => false,
            'delivery_mode' => 'smtp',
            'failure_category' => 'mail_dependency_missing',
            'loader_type' => $loaderStatus['selected_loader'],
        ];
    }

    return [
        'ready' => true,
        'delivery_mode' => 'smtp',
        'failure_category' => null,
        'loader_type' => $loaderStatus['selected_loader'],
    ];
}

function isLocalOtpPreviewMode(): bool {
    $policy = mailModePolicy();
    return $policy['delivery_mode'] === 'preview' && $policy['preview_allowed'];
}

function shouldBypassLocalPreviewMail(): bool {
    return isLocalOtpPreviewMode();
}

function phpMailerLibraryAvailable(): bool {
    $loaderStatus = app_mail_loader_status();
    return (bool) $loaderStatus['ready'];
}

function loadPhpMailerLibrary(): bool {
    if (class_exists(PHPMailer::class)) {
        return true;
    }

    $loaderStatus = app_mail_loader_status();

    if ($loaderStatus['selected_loader'] === 'composer') {
        require_once $loaderStatus['composer']['path'];
    } elseif ($loaderStatus['selected_loader'] === 'legacy') {
        $legacyBase = $loaderStatus['legacy']['path'] . DIRECTORY_SEPARATOR;
        require_once $legacyBase . 'Exception.php';
        require_once $legacyBase . 'PHPMailer.php';
        require_once $legacyBase . 'SMTP.php';
    } else {
        return false;
    }

    return class_exists(PHPMailer::class);
}

function smtpTransportConfiguration(): array {
    $mailConfig = app_mail_config();

    return [
        'host' => $mailConfig['host'],
        'port' => (int) $mailConfig['port'],
        'encryption' => $mailConfig['encryption'],
        'user' => $mailConfig['user'],
        'pass' => $mailConfig['pass'],
        'from_email' => $mailConfig['from_email'],
        'from_name' => $mailConfig['from_name'] !== '' ? $mailConfig['from_name'] : 'Pahlawan Roleplay',
    ];
}

function smtpTransportReady(): bool {
    return mailRuntimeStatus()['ready'] && mailRuntimeStatus()['delivery_mode'] === 'smtp';
}

function resolvePhpMailerEncryption(string $encryption): string {
    $normalized = strtolower(trim($encryption));

    if ($normalized === 'ssl' || $normalized === 'smtps') {
        return PHPMailer::ENCRYPTION_SMTPS;
    }

    if ($normalized === 'tls' || $normalized === 'starttls') {
        return PHPMailer::ENCRYPTION_STARTTLS;
    }

    if ($normalized === 'none') {
        return '';
    }

    return $encryption;
}

function buildConfiguredMailer(): ?PHPMailer {
    $runtimeStatus = mailRuntimeStatus();
    if (!$runtimeStatus['ready'] || $runtimeStatus['delivery_mode'] !== 'smtp') {
        setLastMailFailureCategory($runtimeStatus['failure_category']);
        return null;
    }

    if (!loadPhpMailerLibrary()) {
        setLastMailFailureCategory('mail_dependency_missing');
        return null;
    }

    $transport = smtpTransportConfiguration();

    $mail = new PHPMailer(true);
    $mail->isSMTP();
    $mail->Host = $transport['host'];
    $mail->SMTPAuth = true;
    $mail->Username = $transport['user'];
    $mail->Password = $transport['pass'];
    $resolvedEncryption = resolvePhpMailerEncryption($transport['encryption']);
    if ($resolvedEncryption !== '') {
        $mail->SMTPSecure = $resolvedEncryption;
    }
    $mail->Port = $transport['port'];
    $mail->setFrom($transport['from_email'], $transport['from_name']);

    setLastMailFailureCategory(null);
    return $mail;
}

function localMailTroubleshootingMessage(): string {
    $runtimeStatus = mailRuntimeStatus();
    $category = lastMailFailureCategory() ?? $runtimeStatus['failure_category'] ?? 'smtp_transport_failed';
    return 'Local dev OTP email is not configured: ' . mailFailureMessage($category) . '.';
}

function shouldExposeLocalMailDiagnostic(): bool {
    return isLocalDevEnvironment() && !isLocalOtpPreviewMode() && hasMailFailureCategory();
}

function sharedMailFailureClientMessage(string $fallbackMessage): string {
    if (shouldExposeLocalMailDiagnostic()) {
        return localMailTroubleshootingMessage();
    }

    return $fallbackMessage;
}

function localOtpPreviewPayload($otpCode, string $context = 'verification'): array {
    $normalizedOtp = str_pad(trim((string) $otpCode), 6, '0', STR_PAD_LEFT);
    error_log('[LOCAL OTP PREVIEW][' . $context . '] OTP=' . $normalizedOtp . ' (disabled in production)');

    return [
        'enabled' => true,
        'context' => $context,
        'message' => 'Local-only OTP preview is enabled for this environment. This preview is disabled in production.',
        'otp_code' => $normalizedOtp,
    ];
}

function sendVerificationEmail($toEmail, $username, $otpCode, $context = 'register', $device = '', $location = '') {
    setLastMailFailureCategory(null);

    if (shouldBypassLocalPreviewMail()) {
        return true;
    }

    $mail = buildConfiguredMailer();
    if ($mail === null) {
        error_log('Mailer Error [' . (lastMailFailureCategory() ?? 'smtp_transport_failed') . '].');
        return false;
    }

    try {
        // Penerima
        $mail->addAddress($toEmail, $username);

        // Konten Email
        $mail->isHTML(true);
        $mail->Subject = 'Kode OTP Verifikasi - Pahlawan Roleplay';
        
        // Konten Pesan Dinamis Berdasarkan Konteks
        $context_message = "";
        $alert_box = "";
        
        if ($context === 'resend') {
             $context_message = "Kami menerima permintaan untuk mengirim ulang kode OTP, atau Anda mencoba masuk menggunakan akun yang belum sepenuhnya aktif. Silakan gunakan kode OTP di bawah ini untuk melanjutkan.";
        } elseif ($context === 'new_device') {
             $context_message = "Sistem mendeteksi aktivitas login dari <strong>Perangkat Baru</strong>. Demi keamanan akun Anda, silakan masukkan kode OTP di bawah ini untuk masuk.";
             $alert_box = "<div style='background-color: #faf5ff; border: 1px solid #f3e8ff; border-radius: 12px; padding: 20px; margin-bottom: 24px;'><h4 style='margin: 0 0 12px 0; color: #6b21a8; font-size: 14px; text-transform: uppercase; letter-spacing: 0.5px;'>📍 Detail Aktivitas</h4><div style='font-size: 14px; color: #7e22ce; line-height: 1.6;'><strong style='display: inline-block; width: 80px;'>Perangkat:</strong> " . htmlspecialchars($device) . "<br/><strong style='display: inline-block; width: 80px;'>Lokasi:</strong> " . htmlspecialchars($location) . "</div></div>";
        } elseif ($context === 'new_ip') {
             $context_message = "Sistem mendeteksi aktivitas login dari <strong>Lokasi / IP Address Berbeda</strong>. Demi keamanan akun Anda, silakan masukkan kode OTP di bawah ini untuk masuk.";
             $alert_box = "<div style='background-color: #faf5ff; border: 1px solid #f3e8ff; border-radius: 12px; padding: 20px; margin-bottom: 24px;'><h4 style='margin: 0 0 12px 0; color: #6b21a8; font-size: 14px; text-transform: uppercase; letter-spacing: 0.5px;'>📍 Detail Aktivitas</h4><div style='font-size: 14px; color: #7e22ce; line-height: 1.6;'><strong style='display: inline-block; width: 80px;'>Lokasi Baru:</strong> " . htmlspecialchars($location) . "<br/><strong style='display: inline-block; width: 80px;'>Perangkat:</strong> " . htmlspecialchars($device) . "</div></div>";
        } elseif ($context === 'reauth') {
             $context_message = "Demi perlindungan keamanan tingkat lanjut. Sesi akses IP Anda telah usang dan memerlukan verifikasi ulang. Masukkan OTP di bawah ini untuk menyambungkan kembali.";
        } else {
             $context_message = "Terima kasih telah mendaftar di <strong>Pahlawan Roleplay</strong>. Silakan gunakan kode OTP (One Time Password) 6 digit di bawah ini untuk mengaktifkan akun Anda.";
        }

        $html_body = '
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body style="background-color: #f3f4f6; padding: 20px 0; font-family: \'Segoe UI\', Tahoma, Geneva, Verdana, sans-serif; margin: 0;">
    <div style="max-width: 600px; margin: 0 auto; background-color: #ffffff; border-radius: 16px; overflow: hidden; box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06); border: 1px solid #e5e7eb; border-top: 8px solid #dc2626;">
        
        <div style="padding: 32px 24px; text-align: center; border-bottom: 1px solid #f3f4f6;">
            <img src="https://i.ibb.co.com/d4zTLfM6/logo1.png" alt="Pahlawan Roleplay Logo" style="width: 160px;" />
        </div>

        <div style="padding: 32px 24px; color: #1f2937;">
            <div style="text-align: center; margin-bottom: 24px;">
                <span style="display: inline-block; background-color: #fee2e2; color: #ef4444; padding: 6px 16px; border-radius: 9999px; font-size: 12px; font-weight: 800; letter-spacing: 1px; text-transform: uppercase;">Otentikasi Keamanan</span>
                <h1 style="margin: 16px 0 0 0; font-size: 28px; color: #111827; font-weight: 900; letter-spacing: -0.5px;">VERIFIKASI AKUN 🔐</h1>
            </div>
            
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 16px 0;">Halo, <strong style="color: #dc2626;">' . $username . '</strong>!</p>
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 24px 0; color: #4b5563;">' . $context_message . '</p>
            
            ' . $alert_box . '

            <div style="background-color: #f3f4f6; border-radius: 16px; padding: 32px 24px; text-align: center; margin: 32px 0;">
                <span style="font-size: 12px; color: #6b7280; text-transform: uppercase; letter-spacing: 2px; font-weight: 700; display: block; margin-bottom: 12px;">KODE OTP ANDA</span>
                <div style="font-size: 48px; font-family: \'Courier New\', Courier, monospace; font-weight: 900; color: #111827; letter-spacing: 12px; margin: 0; text-shadow: 2px 2px 0px rgba(0,0,0,0.05); padding-left: 12px;">' . $otpCode . '</div>
            </div>
            
            <div style="background-color: #fffbeb; border: 1px solid #fef3c7; border-radius: 12px; padding: 20px; display: flex; gap: 16px; align-items: flex-start;">
                <div style="font-size: 20px;">🛡️</div>
                <div>
                    <strong style="display: block; color: #92400e; font-size: 14px; margin-bottom: 6px;">Perhatian Keamanan</strong>
                    <p style="margin: 0; color: #b45309; font-size: 13px; line-height: 1.5;">Kode ini hanya berlaku <strong>30 menit</strong>. Jangan pernah membagikan kode ini kepada siapapun (termasuk Admin/Staff kami). Jika aktivitas ini bukan Anda yang melakukan, segera amankan akun Anda dengan <a href="https://pahlawanrp.com" style="color: #ea580c; font-weight: bold; text-decoration: underline;">membuat tiket bantuan</a>.</p>
                </div>
            </div>
        </div>
        
        <div style="background-color: #f9fafb; padding: 24px; text-align: center; border-top: 1px solid #f3f4f6;">
            <p style="margin: 0; font-size: 13px; color: #6b7280;">&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
        </div>
    </div>
</body>
</html>
        ';
        
        $mail->Body    = $html_body;
        $mail->AltBody = "Halo $username,\n\nKode OTP Anda adalah: $otpCode\n\nJangan berikan kepada siapapun!";

        $mail->send();
        setLastMailFailureCategory(null);
        return true;
    } catch (Throwable $e) {
        setLastMailFailureCategory('smtp_transport_failed');
        error_log('Mailer Error [smtp_transport_failed].');
        return false;
    }
}

function sendWelcomeEmail($toEmail, $username) {
    setLastMailFailureCategory(null);

    if (shouldBypassLocalPreviewMail()) {
        return true;
    }

    $mail = buildConfiguredMailer();
    if ($mail === null) {
        error_log('Mailer Error [' . (lastMailFailureCategory() ?? 'smtp_transport_failed') . '].');
        return false;
    }

    try {
        $mail->addAddress($toEmail, $username);

        $mail->isHTML(true);
        $mail->Subject = 'Selamat Datang di Pahlawan Roleplay 🎉';
        
        $html_body = '
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body style="background-color: #f3f4f6; padding: 20px 0; font-family: \'Segoe UI\', Tahoma, Geneva, Verdana, sans-serif; margin: 0;">
    <div style="max-width: 600px; margin: 0 auto; background-color: #ffffff; border-radius: 16px; overflow: hidden; box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06); border: 1px solid #e5e7eb; border-top: 8px solid #dc2626;">
        
        <div style="padding: 32px 24px; text-align: center; border-bottom: 1px solid #f3f4f6;">
            <img src="https://i.ibb.co.com/d4zTLfM6/logo1.png" alt="Pahlawan Roleplay Logo" style="width: 160px;" />
        </div>

        <div style="padding: 32px 24px; color: #1f2937;">
            <div style="text-align: center; margin-bottom: 24px;">
                <span style="display: inline-block; background-color: #fee2e2; color: #ef4444; padding: 6px 16px; border-radius: 9999px; font-size: 12px; font-weight: 800; letter-spacing: 1px; text-transform: uppercase;">Akun Berhasil Dibuat</span>
                <h1 style="margin: 16px 0 0 0; font-size: 28px; color: #111827; font-weight: 900; letter-spacing: -0.5px;">SELAMAT DATANG! 🎉</h1>
            </div>
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 16px 0;">Halo, <strong style="color: #dc2626;">' . $username . '</strong>!</p>
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 24px 0; color: #4b5563;">Pendaftaran akun UCP Anda telah berhasil dikonfirmasi. Selamat bergabung di komunitas <strong style="color: #111827;">Pahlawan Roleplay</strong>!</p>
            
            <div style="background-color: #fef2f2; border: 1px solid #fee2e2; border-radius: 12px; padding: 24px; margin: 32px 0;">
                <h3 style="margin: 0 0 16px 0; color: #b91c1c; font-size: 16px; font-weight: 700; text-transform: uppercase; letter-spacing: 0.5px;">🚀 Mulai Petualanganmu</h3>
                <ul style="margin: 0; padding-left: 16px; font-size: 15px; line-height: 1.8; color: #7f1d1d;">
                    <li>Buat Karakter In-Game pertamamu.</li>
                    <li>Lengkapi profil identitas OOC.</li>
                    <li>Selesaikan Character Story untuk membuka fitur.</li>
                    <li>Bergabunglah di server Discord kami.</li>
                </ul>
            </div>
            
            <div style="text-align: center; margin-top: 32px;">
                <a href="https://pahlawanrp.com" style="display: inline-block; padding: 14px 32px; background-color: #dc2626; color: #ffffff; text-decoration: none; border-radius: 8px; font-weight: 600; font-size: 16px; letter-spacing: 0.5px; box-shadow: 0 4px 6px -1px rgba(220, 38, 38, 0.2);">Dashboard UCP</a>
            </div>
        </div>
        
        <div style="background-color: #f9fafb; padding: 24px; text-align: center; border-top: 1px solid #f3f4f6;">
            <p style="margin: 0; font-size: 13px; color: #6b7280;">&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
        </div>
    </div>
</body>
</html>
        ';
        
        $mail->Body    = $html_body;
        $mail->AltBody = "Halo $username,\n\nSelamat karena pendaftaran UCP Anda berhasil diverifikasi!\n\nSelamat datang di Pahlawan Roleplay.";

        $mail->send();
        setLastMailFailureCategory(null);
        return true;
    } catch (Throwable $e) {
        setLastMailFailureCategory('smtp_transport_failed');
        error_log('Mailer Error [smtp_transport_failed].');
        return false;
    }
}

function sendForgotPasswordEmail($toEmail, $username, $otpCode) {
    setLastMailFailureCategory(null);

    if (shouldBypassLocalPreviewMail()) {
        return true;
    }

    $mail = buildConfiguredMailer();
    if ($mail === null) {
        error_log('Mailer Error [' . (lastMailFailureCategory() ?? 'smtp_transport_failed') . '].');
        return false;
    }

    try {
        $mail->addAddress($toEmail, $username);

        $mail->isHTML(true);
        $mail->Subject = 'Reset Kata Sandi - Pahlawan Roleplay 🔑';
        
        $html_body = '
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body style="background-color: #f3f4f6; padding: 20px 0; font-family: \'Segoe UI\', Tahoma, Geneva, Verdana, sans-serif; margin: 0;">
    <div style="max-width: 600px; margin: 0 auto; background-color: #ffffff; border-radius: 16px; overflow: hidden; box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06); border: 1px solid #e5e7eb; border-top: 8px solid #dc2626;">
        
        <div style="padding: 32px 24px; text-align: center; border-bottom: 1px solid #f3f4f6;">
            <img src="https://i.ibb.co.com/d4zTLfM6/logo1.png" alt="Pahlawan Roleplay Logo" style="width: 160px;" />
        </div>

        <div style="padding: 32px 24px; color: #1f2937;">
            <div style="text-align: center; margin-bottom: 24px;">
                <span style="display: inline-block; background-color: #fee2e2; color: #ef4444; padding: 6px 16px; border-radius: 9999px; font-size: 12px; font-weight: 800; letter-spacing: 1px; text-transform: uppercase;">Permintaan Reset Kata Sandi</span>
                <h1 style="margin: 16px 0 0 0; font-size: 28px; color: #111827; font-weight: 900; letter-spacing: -0.5px;">LUPA KATA SANDI 🔑</h1>
            </div>
            
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 16px 0;">Halo, <strong style="color: #dc2626;">' . $username . '</strong>!</p>
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 24px 0; color: #4b5563;">Kami menerima permintaan untuk melakukan setel ulang kata sandi pada akun UCP Anda. Untuk melanjutkan proses penggantian kata sandi, silakan gunakan kode OTP berikut:</p>

            <div style="background-color: #f3f4f6; border-radius: 16px; padding: 32px 24px; text-align: center; margin: 32px 0;">
                <span style="font-size: 12px; color: #6b7280; text-transform: uppercase; letter-spacing: 2px; font-weight: 700; display: block; margin-bottom: 12px;">KODE OTP ANDA</span>
                <div style="font-size: 48px; font-family: \'Courier New\', Courier, monospace; font-weight: 900; color: #111827; letter-spacing: 12px; margin: 0; text-shadow: 2px 2px 0px rgba(0,0,0,0.05); padding-left: 12px;">' . $otpCode . '</div>
            </div>
            
            <div style="background-color: #fffbeb; border: 1px solid #fef3c7; border-radius: 12px; padding: 20px; display: flex; gap: 16px; align-items: flex-start;">
                <div style="font-size: 20px;">🛡️</div>
                <div>
                    <strong style="display: block; color: #92400e; font-size: 14px; margin-bottom: 6px;">Perhatian Keamanan</strong>
                    <p style="margin: 0; color: #b45309; font-size: 13px; line-height: 1.5;">Kode ini hanya berlaku <strong>30 menit</strong>. Jangan pernah membagikan kode ini kepada siapapun (termasuk Admin/Staff kami). Jika Anda tidak meminta pengaturan ulang kata sandi, abaikan email ini atau amankan akun Anda dengan <a href="https://pahlawanrp.com" style="color: #ea580c; font-weight: bold; text-decoration: underline;">membuat tiket bantuan</a>.</p>
                </div>
            </div>
        </div>
        
        <div style="background-color: #f9fafb; padding: 24px; text-align: center; border-top: 1px solid #f3f4f6;">
            <p style="margin: 0; font-size: 13px; color: #6b7280;">&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
        </div>
    </div>
</body>
</html>
        ';
        
        $mail->Body    = $html_body;
        $mail->AltBody = "Halo $username,\n\nKode OTP reset sandi Anda adalah: $otpCode\n\nJangan berikan kepada siapapun!";

        $mail->send();
        setLastMailFailureCategory(null);
        return true;
    } catch (Throwable $e) {
        setLastMailFailureCategory('smtp_transport_failed');
        error_log('Mailer Error [smtp_transport_failed].');
        return false;
    }
}

function sendPasswordResetSuccessEmail($toEmail, $username) {
    setLastMailFailureCategory(null);

    if (shouldBypassLocalPreviewMail()) {
        return true;
    }

    $mail = buildConfiguredMailer();
    if ($mail === null) {
        error_log('Mailer Error [' . (lastMailFailureCategory() ?? 'smtp_transport_failed') . '].');
        return false;
    }

    try {
        $mail->addAddress($toEmail, $username);

        $mail->isHTML(true);
        $mail->Subject = 'Kata Sandi Berhasil Direset ✔️';
        
        $html_body = '
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body style="background-color: #f3f4f6; padding: 20px 0; font-family: \'Segoe UI\', Tahoma, Geneva, Verdana, sans-serif; margin: 0;">
    <div style="max-width: 600px; margin: 0 auto; background-color: #ffffff; border-radius: 16px; overflow: hidden; box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06); border: 1px solid #e5e7eb; border-top: 8px solid #16a34a;">
        
        <div style="padding: 32px 24px; text-align: center; border-bottom: 1px solid #f3f4f6;">
            <img src="https://i.ibb.co.com/d4zTLfM6/logo1.png" alt="Pahlawan Roleplay Logo" style="width: 160px;" />
        </div>

        <div style="padding: 32px 24px; color: #1f2937;">
            <div style="text-align: center; margin-bottom: 24px;">
                <span style="display: inline-block; background-color: #bbf7d0; color: #16a34a; padding: 6px 16px; border-radius: 9999px; font-size: 12px; font-weight: 800; letter-spacing: 1px; text-transform: uppercase;">Keamanan Akun</span>
                <h1 style="margin: 16px 0 0 0; font-size: 28px; color: #111827; font-weight: 900; letter-spacing: -0.5px;">SANDI TELAH DIRESET ✔️</h1>
            </div>
            
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 16px 0;">Halo, <strong style="color: #16a34a;">' . $username . '</strong>!</p>
            <p style="font-size: 16px; line-height: 1.6; margin: 0 0 24px 0; color: #4b5563;">Memberitahukan bahwa kata sandi akun UCP Anda baru saja berhasil diubah atau disetel ulang. Anda kini dapat masuk menggunakan kata sandi yang baru.</p>

            <div style="background-color: #fffbeb; border: 1px solid #fef3c7; border-radius: 12px; padding: 20px; display: flex; gap: 16px; align-items: flex-start;">
                <div style="font-size: 20px;">🚨</div>
                <div>
                    <strong style="display: block; color: #92400e; font-size: 14px; margin-bottom: 6px;">Bukan Anda yang melakukan?</strong>
                    <p style="margin: 0; color: #b45309; font-size: 13px; line-height: 1.5;">Jika Anda tidak merasa mengubah kata sandi Anda hari ini, segera hubungi tim kami dengan <a href="https://pahlawanrp.com" style="color: #ea580c; font-weight: bold; text-decoration: underline;">membuat tiket bantuan</a> untuk mengamankan akun Anda.</p>
                </div>
            </div>
        </div>
        
        <div style="background-color: #f9fafb; padding: 24px; text-align: center; border-top: 1px solid #f3f4f6;">
            <p style="margin: 0; font-size: 13px; color: #6b7280;">&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
        </div>
    </div>
</body>
</html>
        ';
        
        $mail->Body    = $html_body;
        $mail->AltBody = "Halo $username,\n\nKata sandi akun UCP Anda telah berhasil diubah.\n\nBila ini bukan Anda, segera hubungi staff.";

        $mail->send();
        setLastMailFailureCategory(null);
        return true;
    } catch (Throwable $e) {
        setLastMailFailureCategory('smtp_transport_failed');
        error_log('Mailer Error [smtp_transport_failed].');
        return false;
    }
}
?>
