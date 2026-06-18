<?php

require_once dirname(__DIR__) . '/public/api/db_env.php';

function endpoint_test_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

$endpointTestSessions = [];
register_shutdown_function(static function () use (&$endpointTestSessions): void {
    $savePath = session_save_path();
    if (str_contains($savePath, ';')) {
        $savePath = substr($savePath, strrpos($savePath, ';') + 1);
    }
    foreach ($endpointTestSessions as $sessionId) {
        $sessionFile = rtrim($savePath, DIRECTORY_SEPARATOR)
            . DIRECTORY_SEPARATOR
            . 'sess_'
            . $sessionId;
        if (is_file($sessionFile)) {
            unlink($sessionFile);
        }
    }
});

function endpoint_test_session(int $adminLevel): string
{
    global $endpointTestSessions;

    $sessionId = 'phrptest-' . bin2hex(random_bytes(12));
    session_name('phrp_ucp_session');
    session_id($sessionId);
    session_start();
    $_SESSION['ucp_user'] = [
        'id' => 900000 + $adminLevel,
        'username' => 'offline_test_admin_' . $adminLevel,
        'admin_level' => $adminLevel,
    ];
    $_SESSION['ucp_last_seen'] = time();
    session_write_close();
    $endpointTestSessions[] = $sessionId;
    return $sessionId;
}

function endpoint_test_request(
    string $url,
    array $payload,
    ?string $sessionId = null
): array {
    $headers = ['Content-Type: application/json'];
    if ($sessionId !== null) {
        $headers[] = 'Cookie: phrp_ucp_session=' . $sessionId;
    }

    $context = stream_context_create([
        'http' => [
            'method' => 'POST',
            'header' => implode("\r\n", $headers),
            'content' => json_encode($payload, JSON_UNESCAPED_SLASHES),
            'ignore_errors' => true,
            'timeout' => 10,
        ],
    ]);
    $body = file_get_contents($url, false, $context);
    $responseHeaders = $http_response_header ?? [];
    preg_match('/\s(\d{3})\s/', $responseHeaders[0] ?? '', $statusMatch);

    return [
        'status' => isset($statusMatch[1]) ? (int)$statusMatch[1] : 0,
        'body' => json_decode((string)$body, true),
    ];
}

function endpoint_test_review_count(int $storyId): int
{
    $config = get_db_config();
    $pdo = new PDO(
        "mysql:host={$config['host']};port={$config['port']};dbname={$config['name']};charset=utf8mb4",
        $config['user'],
        $config['pass'],
        [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]
    );
    $stmt = $pdo->prepare('SELECT COUNT(*) FROM ucp_story_reviews WHERE story_id = ?');
    $stmt->execute([$storyId]);
    return (int)$stmt->fetchColumn();
}

$baseUrl = rtrim((string)($argv[1] ?? ''), '/');
$storyId = filter_var($argv[2] ?? null, FILTER_VALIDATE_INT);
$mode = (string)($argv[3] ?? 'negative');
endpoint_test_assert($baseUrl !== '' && $storyId && $storyId > 0, 'Usage: test.php <base-url> <story-id> [negative|failure]');
$endpoint = $baseUrl . '/api/api_story_review.php';

if ($mode === 'negative') {
    $unauthenticated = endpoint_test_request($endpoint, [
        'action' => 'analyze_story',
        'story_id' => $storyId,
    ]);
    endpoint_test_assert($unauthenticated['status'] === 401, 'Unauthenticated request was not rejected.');

    $nonAdmin = endpoint_test_request($endpoint, [
        'action' => 'analyze_story',
        'story_id' => $storyId,
    ], endpoint_test_session(0));
    endpoint_test_assert($nonAdmin['status'] === 403, 'Non-admin request was not rejected.');

    $belowLevelFive = endpoint_test_request($endpoint, [
        'action' => 'analyze_story',
        'story_id' => $storyId,
    ], endpoint_test_session(4));
    endpoint_test_assert($belowLevelFive['status'] === 403, 'Admin below level 5 was not rejected.');

    $adminSession = endpoint_test_session(5);
    $invalidStory = endpoint_test_request($endpoint, [
        'action' => 'analyze_story',
        'story_id' => 0,
    ], $adminSession);
    endpoint_test_assert($invalidStory['status'] === 422, 'Invalid story ID was not rejected.');

    $browserContent = endpoint_test_request($endpoint, [
        'action' => 'analyze_story',
        'story_id' => $storyId,
        'story_text' => 'Browser supplied text must not be analyzed.',
    ], $adminSession);
    endpoint_test_assert($browserContent['status'] === 422, 'Browser-supplied story text was not rejected.');

    echo "story_review_endpoint_negative_test=passed\n";
    exit;
}

endpoint_test_assert($mode === 'failure', 'Unknown test mode.');
$before = endpoint_test_review_count((int)$storyId);
$failure = endpoint_test_request($endpoint, [
    'action' => 'analyze_story',
    'story_id' => $storyId,
], endpoint_test_session(5));
$after = endpoint_test_review_count((int)$storyId);

endpoint_test_assert(
    $failure['status'] === 503,
    'Provider configuration failure did not fail closed (HTTP ' . $failure['status'] . ').'
);
endpoint_test_assert(
    $after === $before,
    "A partial review was persisted after provider failure ({$before} -> {$after})."
);
echo "story_review_endpoint_failure_test=passed\n";
