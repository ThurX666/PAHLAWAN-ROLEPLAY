<?php

require_once __DIR__ . '/ai_provider.php';

class AiRateLimitLease
{
    private array $handles;

    public function __construct(array $handles)
    {
        $this->handles = $handles;
    }

    public function release(): void
    {
        foreach ($this->handles as $handle) {
            if (is_resource($handle)) {
                flock($handle, LOCK_UN);
                fclose($handle);
            }
        }
        $this->handles = [];
    }

    public function __destruct()
    {
        $this->release();
    }
}

function ai_runtime_storage_directory(): string
{
    $configured = ai_config_value('AI_RATE_LIMIT_STORAGE_DIR');
    $directory = $configured !== ''
        ? $configured
        : sys_get_temp_dir() . DIRECTORY_SEPARATOR . 'phrp_story_review_ai';

    if (!is_dir($directory) && !@mkdir($directory, 0700, true) && !is_dir($directory)) {
        throw new AiProviderException('configuration', 'AI rate-limit storage is unavailable.');
    }

    return $directory;
}

function ai_runtime_locked_file(string $path, bool $nonBlocking = false)
{
    $handle = @fopen($path, 'c+');
    if ($handle === false) {
        throw new AiProviderException('configuration', 'AI runtime lock is unavailable.');
    }

    $operation = LOCK_EX | ($nonBlocking ? LOCK_NB : 0);
    if (!flock($handle, $operation)) {
        fclose($handle);
        return null;
    }

    return $handle;
}

function ai_runtime_read_timestamps($handle): array
{
    rewind($handle);
    $decoded = json_decode((string)stream_get_contents($handle), true);
    if (!is_array($decoded)) {
        return [];
    }

    return array_values(array_filter(
        array_map('intval', $decoded),
        static fn(int $timestamp): bool => $timestamp > 0
    ));
}

function ai_runtime_write_timestamps($handle, array $timestamps): void
{
    rewind($handle);
    ftruncate($handle, 0);
    $encoded = json_encode(array_values($timestamps));
    if ($encoded === false || fwrite($handle, $encoded) === false) {
        throw new AiProviderException('configuration', 'AI rate-limit state could not be written.');
    }
    fflush($handle);
}

function ai_runtime_count_since(array $timestamps, int $minimumTimestamp): int
{
    return count(array_filter(
        $timestamps,
        static fn(int $timestamp): bool => $timestamp >= $minimumTimestamp
    ));
}

function ai_story_review_acquire_concurrency_slot(): AiRateLimitLease
{
    $limit = ai_config_int('AI_STORY_REVIEW_GLOBAL_CONCURRENCY', 2, 1, 20);
    $directory = ai_runtime_storage_directory();

    for ($slot = 0; $slot < $limit; $slot++) {
        $handle = ai_runtime_locked_file(
            $directory . DIRECTORY_SEPARATOR . 'concurrency_' . $slot . '.lock',
            true
        );
        if ($handle !== null) {
            return new AiRateLimitLease([$handle]);
        }
    }

    throw new AiProviderException('rate_limited', 'AI concurrency limit reached.', 429);
}

function ai_story_review_acquire_limits(int $adminId, int $storyId): AiRateLimitLease
{
    if ($adminId < 1 || $storyId < 1) {
        throw new AiProviderException('validation', 'AI rate-limit identity is invalid.', 422);
    }

    $concurrencyLease = ai_story_review_acquire_concurrency_slot();
    $directory = ai_runtime_storage_directory();
    $actorPath = $directory . DIRECTORY_SEPARATOR . 'actor_' . hash('sha256', (string)$adminId) . '.json';
    $storyPath = $directory . DIRECTORY_SEPARATOR . 'story_' . hash('sha256', (string)$storyId) . '.json';
    $paths = [$actorPath, $storyPath];
    sort($paths, SORT_STRING);
    $handles = [];

    try {
        foreach ($paths as $path) {
            $handles[$path] = ai_runtime_locked_file($path);
        }

        $now = time();
        $dayAgo = $now - 86400;
        $actorTimestamps = array_values(array_filter(
            ai_runtime_read_timestamps($handles[$actorPath]),
            static fn(int $timestamp): bool => $timestamp >= $dayAgo
        ));
        $storyTimestamps = array_values(array_filter(
            ai_runtime_read_timestamps($handles[$storyPath]),
            static fn(int $timestamp): bool => $timestamp >= $dayAgo
        ));

        $actorFiveMinuteLimit = ai_config_int('AI_STORY_REVIEW_RATE_5M', 3, 1, 100);
        $actorHourlyLimit = ai_config_int('AI_STORY_REVIEW_RATE_HOUR', 12, 1, 500);
        $actorDailyLimit = ai_config_int('AI_STORY_REVIEW_RATE_DAY', 40, 1, 2000);
        if (
            ai_runtime_count_since($actorTimestamps, $now - 300) >= $actorFiveMinuteLimit
            || ai_runtime_count_since($actorTimestamps, $now - 3600) >= $actorHourlyLimit
            || count($actorTimestamps) >= $actorDailyLimit
        ) {
            throw new AiProviderException('rate_limited', 'AI actor rate limit reached.', 429);
        }

        $storyCooldown = ai_config_int('AI_STORY_REVIEW_STORY_COOLDOWN_SECONDS', 60, 0, 3600);
        $storyHourlyLimit = ai_config_int('AI_STORY_REVIEW_STORY_RATE_HOUR', 3, 1, 100);
        $latestStoryRequest = $storyTimestamps === [] ? 0 : max($storyTimestamps);
        if (
            ($storyCooldown > 0 && $latestStoryRequest > $now - $storyCooldown)
            || ai_runtime_count_since($storyTimestamps, $now - 3600) >= $storyHourlyLimit
        ) {
            throw new AiProviderException('rate_limited', 'AI story rate limit reached.', 429);
        }

        $actorTimestamps[] = $now;
        $storyTimestamps[] = $now;
        ai_runtime_write_timestamps($handles[$actorPath], $actorTimestamps);
        ai_runtime_write_timestamps($handles[$storyPath], $storyTimestamps);
    } catch (Throwable $exception) {
        foreach ($handles as $handle) {
            if (is_resource($handle)) {
                flock($handle, LOCK_UN);
                fclose($handle);
            }
        }
        $concurrencyLease->release();
        throw $exception;
    }

    foreach ($handles as $handle) {
        flock($handle, LOCK_UN);
        fclose($handle);
    }

    return $concurrencyLease;
}

function ai_story_review_log_path(): string
{
    $configured = ai_config_value('AI_STORY_REVIEW_LOG_PATH');
    if ($configured !== '') {
        return $configured;
    }

    return dirname(__DIR__, 2)
        . DIRECTORY_SEPARATOR . '.runtime-logs'
        . DIRECTORY_SEPARATOR . 'ai-story-review.jsonl';
}

function ai_story_review_log_event(array $event): void
{
    $path = ai_story_review_log_path();
    $directory = dirname($path);
    if (!is_dir($directory) && !@mkdir($directory, 0700, true) && !is_dir($directory)) {
        return;
    }

    $usage = $event['usage'] ?? null;
    $safeUsage = null;
    if (is_array($usage)) {
        $safeUsage = [
            'prompt_tokens' => isset($usage['prompt_tokens']) ? max(0, (int)$usage['prompt_tokens']) : null,
            'completion_tokens' => isset($usage['completion_tokens']) ? max(0, (int)$usage['completion_tokens']) : null,
            'total_tokens' => isset($usage['total_tokens']) ? max(0, (int)$usage['total_tokens']) : null,
        ];
    }

    $safeEvent = [
        'timestamp' => gmdate('c'),
        'request_id' => substr((string)($event['request_id'] ?? ''), 0, 64),
        'task' => 'story_review',
        'provider' => substr((string)($event['provider'] ?? ''), 0, 64),
        'model' => substr((string)($event['model'] ?? ''), 0, 128),
        'actor_ref' => (int)($event['actor_ref'] ?? 0),
        'story_ref' => (int)($event['story_ref'] ?? 0),
        'latency_ms' => max(0, (int)($event['latency_ms'] ?? 0)),
        'result_category' => substr((string)($event['result_category'] ?? 'unknown'), 0, 64),
        'usage' => $safeUsage,
    ];

    $encoded = json_encode($safeEvent, JSON_UNESCAPED_SLASHES);
    if ($encoded !== false) {
        @file_put_contents($path, $encoded . PHP_EOL, FILE_APPEND | LOCK_EX);
    }
}

function ai_story_review_request_id(): string
{
    try {
        return bin2hex(random_bytes(16));
    } catch (Throwable $exception) {
        return hash('sha256', uniqid('story-review-', true));
    }
}
