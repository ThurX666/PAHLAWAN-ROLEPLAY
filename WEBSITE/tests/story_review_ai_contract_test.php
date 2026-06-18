<?php

putenv('AI_ENABLED=false');
putenv('AI_STORY_REVIEW_ENABLED=false');

require_once dirname(__DIR__) . '/public/api/db_env.php';
require_once dirname(__DIR__) . '/public/api/story_review_ai.php';
require_once dirname(__DIR__) . '/public/api/ai_runtime_safety.php';

function story_review_test_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

function story_review_test_temp_directory(string $suffix): string
{
    $directory = sys_get_temp_dir()
        . DIRECTORY_SEPARATOR
        . 'phrp-story-review-test-'
        . $suffix
        . '-'
        . bin2hex(random_bytes(4));
    if (!mkdir($directory, 0700, true) && !is_dir($directory)) {
        throw new RuntimeException('Could not create test directory.');
    }
    return $directory;
}

function story_review_test_remove_directory(string $directory): void
{
    foreach (glob($directory . DIRECTORY_SEPARATOR . '*') ?: [] as $path) {
        if (is_file($path)) {
            unlink($path);
        }
    }
    rmdir($directory);
}

story_review_test_assert(!ai_story_review_is_enabled(), 'Story Review AI must be disabled by default.');

try {
    ai_send_message(
        [['role' => 'user', 'content' => 'This offline test must not reach a provider.']],
        ['task' => 'story_review']
    );
    throw new RuntimeException('Disabled provider was accepted.');
} catch (AiProviderException $exception) {
    story_review_test_assert($exception->category() === 'disabled', 'Disabled provider category mismatch.');
}

$missingKeyConfig = ai_provider_config();
$missingKeyConfig['enabled'] = true;
$missingKeyConfig['api_key'] = '';
try {
    ai_validate_server_configuration($missingKeyConfig);
    throw new RuntimeException('Missing provider credential was accepted.');
} catch (AiProviderException $exception) {
    story_review_test_assert($exception->category() === 'configuration', 'Missing key category mismatch.');
}

$story = 'Raka tiba di Los Santos dan berusaha membangun hidup baru secara masuk akal.';
$messages = story_review_ai_build_messages($story);
story_review_test_assert(count($messages) === 2, 'Story Review prompt shape is invalid.');
story_review_test_assert(str_contains($messages[1]['content'], $story), 'Selected story is missing from the prompt.');
foreach (['reviewer_id', 'username', 'cookie', 'matched_story_id'] as $privateField) {
    story_review_test_assert(
        !str_contains($messages[1]['content'], $privateField),
        'Story Review prompt contains private metadata.'
    );
}

$validResponse = json_encode([
    'schema_version' => STORY_REVIEW_AI_SCHEMA_VERSION,
    'grammar_score' => 80,
    'readability_score' => 70,
    'roleplay_score' => 90,
    'overall_score' => 82,
    'review_notes' => 'Cerita memiliki karakter yang konsisten dan alur yang jelas. Perbaiki struktur beberapa kalimat agar lebih mudah dibaca.',
]);
$validated = story_review_ai_validate_response((string)$validResponse);
story_review_test_assert($validated['overall_score'] === 82.0, 'Overall score was not recomputed.');

$invalidResponses = [
    '{"schema_version":"story-review-rubric-v1","grammar_score":101,"readability_score":70,"roleplay_score":90,"overall_score":88,"review_notes":"Catatan cukup panjang tetapi skor berada di luar rentang."}',
    '{"schema_version":"story-review-rubric-v1","grammar_score":80,"readability_score":70,"roleplay_score":90,"review_notes":"Respons parsial harus ditolak oleh validator."}',
];
foreach ($invalidResponses as $invalidResponse) {
    try {
        story_review_ai_validate_response($invalidResponse);
        throw new RuntimeException('Invalid provider response was accepted.');
    } catch (AiProviderException $exception) {
        story_review_test_assert(
            $exception->category() === 'invalid_response',
            'Invalid response category mismatch.'
        );
    }
}

$adminRateDirectory = story_review_test_temp_directory('admin-rate');
putenv('AI_RATE_LIMIT_STORAGE_DIR=' . $adminRateDirectory);
putenv('AI_STORY_REVIEW_GLOBAL_CONCURRENCY=2');
putenv('AI_STORY_REVIEW_RATE_5M=2');
putenv('AI_STORY_REVIEW_RATE_HOUR=10');
putenv('AI_STORY_REVIEW_RATE_DAY=10');
putenv('AI_STORY_REVIEW_STORY_COOLDOWN_SECONDS=0');
putenv('AI_STORY_REVIEW_STORY_RATE_HOUR=10');
$lease = ai_story_review_acquire_limits(100, 1001);
$lease->release();
$lease = ai_story_review_acquire_limits(100, 1002);
$lease->release();
try {
    ai_story_review_acquire_limits(100, 1003);
    throw new RuntimeException('Per-admin rate limit was not enforced.');
} catch (AiProviderException $exception) {
    story_review_test_assert($exception->category() === 'rate_limited', 'Admin rate category mismatch.');
}
story_review_test_remove_directory($adminRateDirectory);

$storyRateDirectory = story_review_test_temp_directory('story-rate');
putenv('AI_RATE_LIMIT_STORAGE_DIR=' . $storyRateDirectory);
putenv('AI_STORY_REVIEW_RATE_5M=10');
putenv('AI_STORY_REVIEW_STORY_COOLDOWN_SECONDS=60');
$lease = ai_story_review_acquire_limits(201, 2001);
$lease->release();
try {
    ai_story_review_acquire_limits(202, 2001);
    throw new RuntimeException('Per-story cooldown was not enforced.');
} catch (AiProviderException $exception) {
    story_review_test_assert($exception->category() === 'rate_limited', 'Story rate category mismatch.');
}
story_review_test_remove_directory($storyRateDirectory);

$concurrencyDirectory = story_review_test_temp_directory('concurrency');
putenv('AI_RATE_LIMIT_STORAGE_DIR=' . $concurrencyDirectory);
putenv('AI_STORY_REVIEW_GLOBAL_CONCURRENCY=1');
putenv('AI_STORY_REVIEW_STORY_COOLDOWN_SECONDS=0');
$activeLease = ai_story_review_acquire_limits(301, 3001);
try {
    ai_story_review_acquire_limits(302, 3002);
    throw new RuntimeException('Global concurrency limit was not enforced.');
} catch (AiProviderException $exception) {
    story_review_test_assert($exception->category() === 'rate_limited', 'Concurrency category mismatch.');
}
$activeLease->release();
story_review_test_remove_directory($concurrencyDirectory);

$loggingDirectory = story_review_test_temp_directory('logging');
$loggingPath = $loggingDirectory . DIRECTORY_SEPARATOR . 'events.jsonl';
putenv('AI_STORY_REVIEW_LOG_PATH=' . $loggingPath);
ai_story_review_log_event([
    'request_id' => 'offline-test-request',
    'provider' => 'nvidia',
    'model' => AI_DEFAULT_STORY_REVIEW_MODEL,
    'actor_ref' => 401,
    'story_ref' => 4001,
    'latency_ms' => 123,
    'result_category' => 'offline_test',
    'usage' => [
        'prompt_tokens' => 10,
        'completion_tokens' => 5,
        'total_tokens' => 15,
    ],
    'story_content' => 'must-not-be-logged',
    'api_key' => 'must-not-be-logged',
]);
$logLine = trim((string)file_get_contents($loggingPath));
$loggedEvent = json_decode($logLine, true);
story_review_test_assert(is_array($loggedEvent), 'Privacy log is not valid JSON.');
story_review_test_assert(
    array_keys($loggedEvent) === [
        'timestamp',
        'request_id',
        'task',
        'provider',
        'model',
        'actor_ref',
        'story_ref',
        'latency_ms',
        'result_category',
        'usage',
    ],
    'Privacy log fields do not match the allowlist.'
);
story_review_test_assert(!str_contains($logLine, 'must-not-be-logged'), 'Privacy log leaked excluded data.');
story_review_test_assert($loggedEvent['usage']['total_tokens'] === 15, 'Token usage was not logged.');
story_review_test_remove_directory($loggingDirectory);

echo "story_review_ai_contract_test=passed\n";
