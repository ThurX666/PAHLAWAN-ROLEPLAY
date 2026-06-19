<?php

function endpoint_contract_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

class EndpointFakeStatement
{
    private EndpointFakePdo $pdo;
    private string $sql;
    private array $result = [];

    public function __construct(EndpointFakePdo $pdo, string $sql)
    {
        $this->pdo = $pdo;
        $this->sql = $sql;
    }

    public function bindParam(string $parameter, mixed &$variable): bool
    {
        return true;
    }

    public function execute(?array $params = null): bool
    {
        $handler = $this->pdo->handler;
        $this->result = $handler($this->sql, $params ?? [], $this->pdo);
        $this->pdo->executed[] = ['sql' => $this->sql, 'params' => $params ?? []];
        return true;
    }

    public function fetch(int $mode = PDO::FETCH_ASSOC): array|false
    {
        return $this->result['fetch'] ?? false;
    }

    public function fetchColumn(int $column = 0): mixed
    {
        return $this->result['fetchColumn'] ?? false;
    }

    public function rowCount(): int
    {
        return $this->result['rowCount'] ?? 0;
    }
}

class EndpointFakePdo
{
    public array $executed = [];
    public $handler;

    public function __construct(callable $handler)
    {
        $this->handler = $handler;
    }

    public function prepare(string $sql): EndpointFakeStatement
    {
        return new EndpointFakeStatement($this, $sql);
    }
}

function endpoint_contract_mail_state(array $overrides = []): array
{
    return array_merge([
        'preview' => false,
        'failure_message' => 'MAIL_FAILURE',
        'send_verification' => true,
        'send_forgot' => true,
        'send_welcome' => true,
        'send_reset_success' => true,
        'last_failure_category' => null,
        'sessions' => [],
        'pending_sessions' => [],
        'preview_calls' => [],
    ], $overrides);
}

function setLastMailFailureCategory(?string $category): void
{
    $GLOBALS['__endpoint_mail_state']['last_failure_category'] = $category;
}

function lastMailFailureCategory(): ?string
{
    return $GLOBALS['__endpoint_mail_state']['last_failure_category'] ?? null;
}

function hasMailFailureCategory(): bool
{
    return lastMailFailureCategory() !== null;
}

function isLocalOtpPreviewMode(): bool
{
    return (bool) ($GLOBALS['__endpoint_mail_state']['preview'] ?? false);
}

function localOtpPreviewPayload($otpCode, string $context = 'verification'): array
{
    $payload = [
        'enabled' => true,
        'context' => $context,
        'message' => 'Local-only OTP preview is enabled for this environment. This preview is disabled in production.',
        'otp_code' => str_pad(trim((string) $otpCode), 6, '0', STR_PAD_LEFT),
    ];
    $GLOBALS['__endpoint_mail_state']['preview_calls'][] = $payload;
    return $payload;
}

function sharedMailFailureClientMessage(string $fallbackMessage): string
{
    return $GLOBALS['__endpoint_mail_state']['failure_message'] ?? $fallbackMessage;
}

function sendVerificationEmail($toEmail, $username, $otpCode, $context = 'register', $device = '', $location = ''): bool
{
    if (!($GLOBALS['__endpoint_mail_state']['send_verification'] ?? false)) {
        setLastMailFailureCategory('smtp_transport_failed');
        return false;
    }

    setLastMailFailureCategory(null);
    return true;
}

function sendForgotPasswordEmail($toEmail, $username, $otpCode): bool
{
    if (!($GLOBALS['__endpoint_mail_state']['send_forgot'] ?? false)) {
        setLastMailFailureCategory('smtp_transport_failed');
        return false;
    }

    setLastMailFailureCategory(null);
    return true;
}

function sendWelcomeEmail($toEmail, $username): bool
{
    if (!($GLOBALS['__endpoint_mail_state']['send_welcome'] ?? false)) {
        setLastMailFailureCategory('smtp_transport_failed');
        return false;
    }

    setLastMailFailureCategory(null);
    return true;
}

function sendPasswordResetSuccessEmail($toEmail, $username): bool
{
    if (!($GLOBALS['__endpoint_mail_state']['send_reset_success'] ?? false)) {
        setLastMailFailureCategory('smtp_transport_failed');
        return false;
    }

    setLastMailFailureCategory(null);
    return true;
}

function ucp_create_session(array $user): void
{
    $GLOBALS['__endpoint_mail_state']['sessions'][] = $user['username'] ?? null;
}

function ucp_create_pending_session(array $user): void
{
    $GLOBALS['__endpoint_mail_state']['pending_sessions'][] = $user['username'] ?? null;
}

function endpoint_contract_source(string $filePath): string
{
    $source = file_get_contents($filePath);
    if ($source === false) {
        throw new RuntimeException('Tidak dapat membaca file endpoint: ' . $filePath);
    }

    $source = preg_replace('/^\s*<\?php\s*/', '', $source, 1);
    $source = preg_replace('/\?>\s*$/', '', $source, 1);
    $source = preg_replace('/^\s*require_once .*config\.php.*;\R/m', '', $source);
    $source = preg_replace('/^\s*require_once .*mailer_helper\.php.*;\R/m', '', $source);
    $source = preg_replace('/\bexit\s*\([^;]*\)\s*;/', 'return;', $source);
    $source = preg_replace('/\bexit\s*;/', 'return;', $source);

    return (string) $source;
}

function run_endpoint_contract(string $filePath, array $post, EndpointFakePdo $pdo, array $mailState, array $server = []): array
{
    $GLOBALS['__endpoint_mail_state'] = endpoint_contract_mail_state($mailState);
    $_POST = $post;
    $_SERVER = array_merge([
        'REQUEST_METHOD' => 'POST',
        'REMOTE_ADDR' => '127.0.0.1',
    ], $server);
    $conn = $pdo;

    ob_start();
    try {
        eval(endpoint_contract_source($filePath));
    } catch (Throwable $throwable) {
        ob_end_clean();
        throw $throwable;
    }

    $output = ob_get_clean();
    $decoded = json_decode((string) $output, true);

    endpoint_contract_assert(is_array($decoded), 'Endpoint tidak mengembalikan JSON valid: ' . $filePath);

    return [
        'json' => $decoded,
        'raw' => (string) $output,
        'queries' => $pdo->executed,
        'mail_state' => $GLOBALS['__endpoint_mail_state'],
    ];
}

function assert_no_secret_leak(string $payload, array $disallowed, string $label): void
{
    foreach ($disallowed as $token) {
        endpoint_contract_assert(
            !str_contains($payload, $token),
            $label . ' membocorkan nilai sensitif: ' . $token
        );
    }
}

$apiRoot = dirname(__DIR__) . '/public/api';

$registerSource = file_get_contents($apiRoot . '/register.php');
endpoint_contract_assert($registerSource !== false, 'register.php tidak dapat dibaca.');
endpoint_contract_assert(str_contains($registerSource, 'INSERT INTO player_ucp'), 'Register flow harus menulis ke player_ucp.');
endpoint_contract_assert(!str_contains($registerSource, 'ucp_pending_registrations'), 'Register flow tidak boleh memakai ucp_pending_registrations.');

$registerFailurePdo = new EndpointFakePdo(function (string $sql, array $params): array {
    if (str_contains($sql, 'SELECT ID FROM player_ucp')) {
        return ['rowCount' => 0];
    }
    if (str_contains($sql, 'INSERT INTO player_ucp')) {
        return ['rowCount' => 1];
    }
    throw new RuntimeException('Query register tidak dikenali: ' . $sql);
});
$registerFailure = run_endpoint_contract(
    $apiRoot . '/register.php',
    ['action' => 'register', 'username' => 'regUser', 'email' => 'reg@example.com', 'password' => 'secret'],
    $registerFailurePdo,
    ['send_verification' => false, 'failure_message' => 'MAIL_FAILURE']
);
endpoint_contract_assert($registerFailure['json']['status'] === 'error', 'Register harus gagal tertutup saat email gagal terkirim.');
endpoint_contract_assert(!str_contains($registerFailure['json']['message'], 'Inbox/Spam'), 'Register tidak boleh mengklaim email terkirim saat runtime mail gagal.');
assert_no_secret_leak($registerFailure['raw'], ['654321', 'smtp-user', 'smtp-pass', 'ErrorInfo', 'Set-Cookie', 'token'], 'register failure');

$registerPreview = run_endpoint_contract(
    $apiRoot . '/register.php',
    ['action' => 'register', 'username' => 'regPreview', 'email' => 'preview@example.com', 'password' => 'secret'],
    $registerFailurePdo,
    ['preview' => true, 'send_verification' => false]
);
endpoint_contract_assert($registerPreview['json']['status'] === 'success_verify', 'Register preview lokal harus tetap kompatibel dengan frontend.');
endpoint_contract_assert(isset($registerPreview['json']['local_preview']['otp_code']), 'Register preview lokal harus mengembalikan local_preview.');

$authPdo = new EndpointFakePdo(function (string $sql, array $params): array {
    if (str_contains($sql, 'FROM player_ucp WHERE UCP = :username OR Email = :username')) {
        return ['fetch' => [
            'id' => 10,
            'username' => 'authUser',
            'email' => 'auth@example.com',
            'password' => password_hash('secret', PASSWORD_BCRYPT),
            'is_verified' => 1,
            'Verify_Code' => '-1',
            'Register_Date' => date('Y-m-d H:i:s', time() - 7200),
            'Last_Login' => date('Y-m-d H:i:s', time() - 172800),
            'OTP_Attempts' => 0,
            'admin_level' => 0,
            'vip_status' => 'None',
            'gold' => 0,
            'last_device' => 'Old Device',
            'last_ip' => '10.0.0.1',
            'last_location' => 'Old City',
            'discord_id' => 'discord-1',
        ]];
    }
    if (str_contains($sql, 'UPDATE player_ucp SET Verify_Status = 0')) {
        return ['rowCount' => 1];
    }
    throw new RuntimeException('Query auth tidak dikenali: ' . $sql);
});
$authFailure = run_endpoint_contract(
    $apiRoot . '/auth.php',
    ['action' => 'login', 'username' => 'authUser', 'password' => 'secret', 'device' => 'New Device', 'ip' => '20.0.0.2', 'location' => 'Jakarta'],
    $authPdo,
    ['send_verification' => false, 'failure_message' => 'MAIL_FAILURE']
);
endpoint_contract_assert($authFailure['json']['status'] === 'unverified', 'Auth reauth gagal kirim mail harus tetap mengembalikan status unverified.');
endpoint_contract_assert(($authFailure['json']['cooldown'] ?? null) === 1800, 'Auth reauth harus mempertahankan cooldown 1800.');
assert_no_secret_leak($authFailure['raw'], ['000000', 'smtp-user', 'smtp-pass', 'ErrorInfo', 'Set-Cookie', 'session'], 'auth failure');

$resendPdo = new EndpointFakePdo(function (string $sql, array $params): array {
    if (str_contains($sql, 'SELECT ID, UCP, Email, Verify_Status')) {
        return ['fetch' => [
            'ID' => 22,
            'UCP' => 'resendUser',
            'Email' => 'resend@example.com',
            'Verify_Status' => 0,
            'Verify_Code' => '123456',
            'Register_Date' => date('Y-m-d H:i:s', time() - 7200),
            'OTP_Attempts' => 0,
        ]];
    }
    if (str_contains($sql, 'UPDATE player_ucp SET Verify_Code = :new_token')) {
        return ['rowCount' => 1];
    }
    throw new RuntimeException('Query resend tidak dikenali: ' . $sql);
});
$resendFailure = run_endpoint_contract(
    $apiRoot . '/resend_otp.php',
    ['action' => 'resend_otp', 'username' => 'resendUser'],
    $resendPdo,
    ['send_verification' => false, 'failure_message' => 'MAIL_FAILURE']
);
endpoint_contract_assert($resendFailure['json']['status'] === 'error', 'Resend harus fail closed jika email gagal terkirim.');
assert_no_secret_leak($resendFailure['raw'], ['123456', 'smtp-user', 'smtp-pass', 'ErrorInfo', 'Set-Cookie', 'token'], 'resend failure');

$forgotPdo = new EndpointFakePdo(function (string $sql, array $params): array {
    if (str_contains($sql, 'SELECT ID as id, UCP as username, Verify_Status as is_verified FROM player_ucp')) {
        return ['fetch' => ['id' => 33, 'username' => 'forgotUser', 'is_verified' => 1]];
    }
    if (str_contains($sql, 'UPDATE player_ucp SET reset_token = :token')) {
        return ['rowCount' => 1];
    }
    throw new RuntimeException('Query forgot tidak dikenali: ' . $sql);
});
$forgotFailure = run_endpoint_contract(
    $apiRoot . '/forgot.php',
    ['action' => 'forgot_password', 'email' => 'forgot@example.com'],
    $forgotPdo,
    ['send_forgot' => false, 'failure_message' => 'MAIL_FAILURE']
);
endpoint_contract_assert($forgotFailure['json']['status'] === 'error', 'Forgot password harus fail closed jika email OTP gagal.');
assert_no_secret_leak($forgotFailure['raw'], ['smtp-user', 'smtp-pass', 'ErrorInfo', 'Set-Cookie', 'token'], 'forgot failure');

$verifyPdo = new EndpointFakePdo(function (string $sql, array $params): array {
    if (str_contains($sql, 'FROM player_ucp WHERE UCP = :username OR Email = :email')) {
        return ['fetch' => [
            'id' => 44,
            'username' => 'verifyUser',
            'email' => 'verify@example.com',
            'admin_level' => 0,
            'vip_status' => 'None',
            'gold' => 0,
            'discord_id' => 'discord-verify',
            'is_verified' => 0,
            'verify_token' => '654321',
            'created_at' => date('Y-m-d H:i:s', time() - 300),
        ]];
    }
    if (str_contains($sql, 'UPDATE player_ucp SET Verify_Status = 1')) {
        return ['rowCount' => 1];
    }
    if (str_contains($sql, 'SELECT COUNT(*) FROM ucp_inbox_messages')) {
        return ['fetchColumn' => 0];
    }
    if (str_contains($sql, 'INSERT INTO ucp_inbox_messages')) {
        return ['rowCount' => 1];
    }
    throw new RuntimeException('Query verify tidak dikenali: ' . $sql);
});
$verifySuccess = run_endpoint_contract(
    $apiRoot . '/verify.php',
    ['action' => 'verify_otp', 'username' => 'verifyUser', 'otp_code' => '654321', 'device' => 'Phone', 'ip' => '127.0.0.1', 'location' => 'Bandung'],
    $verifyPdo,
    ['send_welcome' => false]
);
endpoint_contract_assert($verifySuccess['json']['status'] === 'success', 'Verify harus tetap sukses walau welcome email best-effort gagal.');
assert_no_secret_leak($verifySuccess['raw'], ['smtp-user', 'smtp-pass', 'ErrorInfo', 'Set-Cookie', 'session', 'provider'], 'verify success');

echo "email_otp_endpoint_contract_test=passed\n";
