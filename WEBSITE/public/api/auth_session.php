<?php

function ucp_session_start(): void
{
    if (session_status() === PHP_SESSION_ACTIVE) {
        return;
    }

    $isHttps = !empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off';
    session_name('phrp_ucp_session');
    session_set_cookie_params([
        'lifetime' => 0,
        'path' => '/',
        'secure' => $isHttps,
        'httponly' => true,
        'samesite' => 'Lax',
    ]);
    session_start();
}

function ucp_json_error(string $message, int $statusCode = 400): void
{
    http_response_code($statusCode);
    echo json_encode(['status' => 'error', 'message' => $message]);
    exit;
}

function ucp_create_session(array $user): void
{
    ucp_session_start();
    session_regenerate_id(true);

    $_SESSION['ucp_user'] = [
        'id' => (int)($user['id'] ?? 0),
        'username' => (string)($user['username'] ?? ''),
        'admin_level' => (int)($user['admin_level'] ?? 0),
    ];
    unset($_SESSION['ucp_pending_user'], $_SESSION['discord_link_username']);
    $_SESSION['ucp_last_seen'] = time();
}

function ucp_create_pending_session(array $user): void
{
    ucp_session_start();
    session_regenerate_id(true);
    $_SESSION['ucp_pending_user'] = [
        'id' => (int)($user['id'] ?? 0),
        'username' => (string)($user['username'] ?? ''),
        'admin_level' => (int)($user['admin_level'] ?? 0),
    ];
}

function ucp_require_pending_username(?string $requestedUsername = null): string
{
    ucp_session_start();
    $pending = $_SESSION['ucp_pending_user'] ?? null;
    if (!is_array($pending) || empty($pending['username'])) {
        ucp_json_error('Sesi penautan Discord tidak valid. Silakan login kembali.', 401);
    }

    $username = (string)$pending['username'];
    if ($requestedUsername !== null && $requestedUsername !== '' && strcasecmp($requestedUsername, $username) !== 0) {
        ucp_json_error('Username penautan Discord tidak sesuai.', 403);
    }
    return $username;
}

function ucp_destroy_session(): void
{
    ucp_session_start();
    $_SESSION = [];

    if (ini_get('session.use_cookies')) {
        $params = session_get_cookie_params();
        setcookie(session_name(), '', time() - 42000, $params['path'], $params['domain'], $params['secure'], $params['httponly']);
    }

    session_destroy();
}

function ucp_current_user(): ?array
{
    ucp_session_start();
    $user = $_SESSION['ucp_user'] ?? null;
    if (!is_array($user) || empty($user['username'])) {
        return null;
    }

    $idleLimit = (int)app_env('UCP_SESSION_IDLE_SECONDS', '7200');
    $lastSeen = (int)($_SESSION['ucp_last_seen'] ?? 0);
    if ($lastSeen > 0 && $idleLimit > 0 && time() - $lastSeen > $idleLimit) {
        ucp_destroy_session();
        return null;
    }

    $_SESSION['ucp_last_seen'] = time();
    return $user;
}

function ucp_require_user(): array
{
    $user = ucp_current_user();
    if ($user === null) {
        ucp_json_error('Sesi tidak valid atau telah berakhir. Silakan login kembali.', 401);
    }
    return $user;
}

function ucp_require_admin(int $minimumLevel = 1): array
{
    $user = ucp_require_user();
    if ((int)$user['admin_level'] < $minimumLevel) {
        ucp_json_error('Anda tidak memiliki izin untuk tindakan ini.', 403);
    }
    return $user;
}

function ucp_require_username(?string $requestedUsername = null): string
{
    $user = ucp_require_user();
    $sessionUsername = (string)$user['username'];

    if ($requestedUsername !== null && $requestedUsername !== '' && strcasecmp($requestedUsername, $sessionUsername) !== 0) {
        ucp_json_error('Anda tidak dapat mengakses data akun lain.', 403);
    }

    return $sessionUsername;
}

function ucp_is_admin(array $user, int $minimumLevel = 1): bool
{
    return (int)($user['admin_level'] ?? 0) >= $minimumLevel;
}
