<?php

require_once __DIR__ . '/app_config.php';

const AI_DEFAULT_PROVIDER = 'nvidia';
const AI_DEFAULT_NVIDIA_BASE_URL = 'https://integrate.api.nvidia.com/v1';
const AI_DEFAULT_STORY_REVIEW_MODEL = 'deepseek-ai/deepseek-v4-flash';

$GLOBALS['phrp_ai_provider_metadata'] = [
    'usage' => null,
    'http_status' => null,
    'attempts' => 0,
];

class AiProviderException extends RuntimeException
{
    private string $category;
    private int $httpStatus;

    public function __construct(string $category, string $message, int $httpStatus = 503)
    {
        parent::__construct($message);
        $this->category = $category;
        $this->httpStatus = $httpStatus;
    }

    public function category(): string
    {
        return $this->category;
    }

    public function httpStatus(): int
    {
        return $this->httpStatus;
    }
}

function ai_config_value(string $key, string $default = ''): string
{
    return app_env($key, $default);
}

function ai_config_bool(string $key, bool $default = false): bool
{
    $raw = ai_config_value($key, $default ? 'true' : 'false');
    $value = filter_var($raw, FILTER_VALIDATE_BOOLEAN, FILTER_NULL_ON_FAILURE);
    return $value ?? $default;
}

function ai_config_int(string $key, int $default, int $minimum, int $maximum): int
{
    $value = filter_var(ai_config_value($key, (string)$default), FILTER_VALIDATE_INT);
    if ($value === false) {
        return $default;
    }

    return max($minimum, min($maximum, (int)$value));
}

function ai_config_float(string $key, float $default, float $minimum, float $maximum): float
{
    $value = filter_var(ai_config_value($key, (string)$default), FILTER_VALIDATE_FLOAT);
    if ($value === false) {
        return $default;
    }

    return max($minimum, min($maximum, (float)$value));
}

function ai_config_list(string $key, array $defaults): array
{
    $raw = ai_config_value($key, implode(',', $defaults));
    return array_values(array_filter(array_map('trim', explode(',', $raw)), static fn(string $item): bool => $item !== ''));
}

function ai_story_review_is_enabled(): bool
{
    return ai_config_bool('AI_ENABLED', false)
        && ai_config_bool('AI_STORY_REVIEW_ENABLED', false);
}

function ai_provider_config(): array
{
    return [
        'enabled' => ai_story_review_is_enabled(),
        'provider' => strtolower(ai_config_value('AI_PROVIDER', AI_DEFAULT_PROVIDER)),
        'base_url' => ai_config_value('AI_BASE_URL', AI_DEFAULT_NVIDIA_BASE_URL),
        'model' => ai_config_value('AI_STORY_REVIEW_MODEL', AI_DEFAULT_STORY_REVIEW_MODEL),
        'api_key' => ai_config_value('NVIDIA_NIM_API_KEY'),
        'allowed_base_urls' => ai_config_list('AI_ALLOWED_BASE_URLS', [AI_DEFAULT_NVIDIA_BASE_URL]),
        'allowed_models' => ai_config_list('AI_ALLOWED_MODELS', [AI_DEFAULT_STORY_REVIEW_MODEL]),
        'connect_timeout_ms' => ai_config_int('AI_CONNECT_TIMEOUT_MS', 3000, 500, 10000),
        'timeout_ms' => ai_config_int('AI_STORY_REVIEW_TIMEOUT_MS', 20000, 1000, 60000),
        'max_output_tokens' => ai_config_int('AI_STORY_REVIEW_MAX_OUTPUT_TOKENS', 600, 64, 2048),
        'temperature' => ai_config_float('AI_STORY_REVIEW_TEMPERATURE', 0.0, 0.0, 1.0),
        'max_retries' => ai_config_int('AI_MAX_RETRIES', 1, 0, 1),
        'fallback_enabled' => ai_config_bool('AI_FALLBACK_ENABLED', false),
    ];
}

function ai_validate_server_configuration(array $config): void
{
    foreach (['VITE_NVIDIA_NIM_API_KEY', 'VITE_AI_API_KEY', 'VITE_AI_BASE_URL', 'VITE_AI_MODEL'] as $frontendKey) {
        if (ai_config_value($frontendKey) !== '') {
            throw new AiProviderException('configuration', 'Frontend-visible AI configuration is prohibited.');
        }
    }

    if (($config['provider'] ?? '') !== 'nvidia') {
        throw new AiProviderException('configuration', 'Unsupported AI provider.');
    }
    if (($config['fallback_enabled'] ?? false) === true) {
        throw new AiProviderException('configuration', 'AI fallback is not approved.');
    }
    if (($config['api_key'] ?? '') === '') {
        throw new AiProviderException('configuration', 'NVIDIA NIM credential is missing.');
    }
    if (($config['model'] ?? '') === '' || !in_array($config['model'], $config['allowed_models'], true)) {
        throw new AiProviderException('configuration', 'AI model is missing or not approved.');
    }

    $baseUrl = (string)($config['base_url'] ?? '');
    $parts = parse_url($baseUrl);
    if (
        $baseUrl === ''
        || $parts === false
        || strtolower((string)($parts['scheme'] ?? '')) !== 'https'
        || empty($parts['host'])
        || isset($parts['user'])
        || isset($parts['pass'])
        || isset($parts['query'])
        || isset($parts['fragment'])
        || !in_array(rtrim($baseUrl, '/'), array_map(static fn(string $url): string => rtrim($url, '/'), $config['allowed_base_urls']), true)
    ) {
        throw new AiProviderException('configuration', 'AI base URL is missing or not approved.');
    }
}

function ai_validate_messages(array $messages): array
{
    if ($messages === [] || count($messages) > 8) {
        throw new AiProviderException('validation', 'AI messages are invalid.', 422);
    }

    $normalized = [];
    $totalCharacters = 0;
    foreach ($messages as $message) {
        if (!is_array($message)) {
            throw new AiProviderException('validation', 'AI message is invalid.', 422);
        }

        $role = (string)($message['role'] ?? '');
        $content = (string)($message['content'] ?? '');
        if (!in_array($role, ['system', 'user', 'assistant'], true) || trim($content) === '') {
            throw new AiProviderException('validation', 'AI message role or content is invalid.', 422);
        }

        $totalCharacters += function_exists('mb_strlen')
            ? mb_strlen($content, 'UTF-8')
            : strlen($content);
        $normalized[] = ['role' => $role, 'content' => $content];
    }

    $maxInputCharacters = ai_config_int('AI_STORY_REVIEW_MAX_INPUT_CHARS', 50000, 1000, 100000);
    if ($totalCharacters > $maxInputCharacters) {
        throw new AiProviderException('validation', 'AI input exceeds the approved size.', 422);
    }

    return $normalized;
}

function ai_provider_retryable_status(int $status): bool
{
    return in_array($status, [408, 429, 500, 502, 503, 504], true);
}

function ai_provider_set_metadata(array $metadata): void
{
    $GLOBALS['phrp_ai_provider_metadata'] = [
        'usage' => isset($metadata['usage']) && is_array($metadata['usage'])
            ? [
                'prompt_tokens' => isset($metadata['usage']['prompt_tokens'])
                    ? (int)$metadata['usage']['prompt_tokens']
                    : null,
                'completion_tokens' => isset($metadata['usage']['completion_tokens'])
                    ? (int)$metadata['usage']['completion_tokens']
                    : null,
                'total_tokens' => isset($metadata['usage']['total_tokens'])
                    ? (int)$metadata['usage']['total_tokens']
                    : null,
            ]
            : null,
        'http_status' => isset($metadata['http_status']) ? (int)$metadata['http_status'] : null,
        'attempts' => isset($metadata['attempts']) ? (int)$metadata['attempts'] : 0,
    ];
}

function ai_provider_last_metadata(): array
{
    return is_array($GLOBALS['phrp_ai_provider_metadata'] ?? null)
        ? $GLOBALS['phrp_ai_provider_metadata']
        : ['usage' => null, 'http_status' => null, 'attempts' => 0];
}

function nvidia_nim_send_message(array $messages, array $options = []): string
{
    ai_provider_set_metadata([]);
    $config = ai_provider_config();
    if (!$config['enabled']) {
        throw new AiProviderException('disabled', 'AI Story Review is disabled.');
    }

    ai_validate_server_configuration($config);
    $messages = ai_validate_messages($messages);

    $allowedOptionKeys = ['task', 'model', 'maxTokens', 'temperature', 'responseFormat'];
    if (array_diff(array_keys($options), $allowedOptionKeys) !== []) {
        throw new AiProviderException('validation', 'AI options contain unsupported controls.', 422);
    }
    if (($options['task'] ?? '') !== 'story_review') {
        throw new AiProviderException('validation', 'AI task is not approved.', 422);
    }

    $model = (string)($options['model'] ?? $config['model']);
    if ($model === '' || !in_array($model, $config['allowed_models'], true)) {
        throw new AiProviderException('configuration', 'AI model is not approved.');
    }

    $maxTokens = isset($options['maxTokens'])
        ? max(64, min($config['max_output_tokens'], (int)$options['maxTokens']))
        : $config['max_output_tokens'];
    $temperature = isset($options['temperature'])
        ? max(0.0, min(1.0, (float)$options['temperature']))
        : $config['temperature'];

    $payload = [
        'model' => $model,
        'messages' => $messages,
        'max_tokens' => $maxTokens,
        'temperature' => $temperature,
        'stream' => false,
    ];
    if (($options['responseFormat'] ?? null) === 'json') {
        $payload['response_format'] = ['type' => 'json_object'];
    }

    $encodedPayload = json_encode($payload, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE);
    if ($encodedPayload === false) {
        throw new AiProviderException('validation', 'AI request could not be encoded.', 422);
    }

    $attempts = 1 + $config['max_retries'];
    $lastCategory = 'unavailable';
    for ($attempt = 1; $attempt <= $attempts; $attempt++) {
        if (!function_exists('curl_init')) {
            throw new AiProviderException('configuration', 'AI transport is unavailable.');
        }
        $handle = curl_init(rtrim($config['base_url'], '/') . '/chat/completions');
        if ($handle === false) {
            throw new AiProviderException('unavailable', 'AI transport could not be initialized.');
        }

        curl_setopt_array($handle, [
            CURLOPT_POST => true,
            CURLOPT_RETURNTRANSFER => true,
            CURLOPT_HTTPHEADER => [
                'Authorization: Bearer ' . $config['api_key'],
                'Content-Type: application/json',
            ],
            CURLOPT_POSTFIELDS => $encodedPayload,
            CURLOPT_CONNECTTIMEOUT_MS => $config['connect_timeout_ms'],
            CURLOPT_TIMEOUT_MS => $config['timeout_ms'],
            CURLOPT_FOLLOWLOCATION => false,
            CURLOPT_SSL_VERIFYPEER => true,
            CURLOPT_SSL_VERIFYHOST => 2,
        ]);

        $responseBody = curl_exec($handle);
        $curlError = curl_errno($handle);
        $status = (int)curl_getinfo($handle, CURLINFO_RESPONSE_CODE);
        curl_close($handle);
        ai_provider_set_metadata([
            'http_status' => $status,
            'attempts' => $attempt,
        ]);

        if ($curlError !== 0 || $responseBody === false) {
            $lastCategory = 'unavailable';
            if ($attempt < $attempts) {
                usleep(250000 * $attempt);
                continue;
            }
            break;
        }

        if ($status < 200 || $status >= 300) {
            $lastCategory = in_array($status, [401, 403], true)
                ? 'configuration'
                : ($status === 429 ? 'quota' : 'unavailable');
            if ($attempt < $attempts && ai_provider_retryable_status($status)) {
                usleep(250000 * $attempt);
                continue;
            }
            break;
        }

        $response = json_decode((string)$responseBody, true);
        $message = $response['choices'][0]['message'] ?? null;
        $content = is_array($message)
            ? ($message['content'] ?? $message['reasoning_content'] ?? null)
            : null;
        if (!is_string($content) || trim($content) === '') {
            throw new AiProviderException('invalid_response', 'AI provider returned an invalid response.', 502);
        }

        ai_provider_set_metadata([
            'http_status' => $status,
            'attempts' => $attempt,
            'usage' => is_array($response['usage'] ?? null) ? $response['usage'] : null,
        ]);
        return trim($content);
    }

    throw new AiProviderException($lastCategory, 'AI provider is unavailable.');
}

/**
 * Provider-neutral contract compatible with Discord Bot/PHRP-AI:
 * ordered role/content messages plus bounded server-owned options -> normalized text.
 *
 * Supported options: task, model, maxTokens, temperature, responseFormat.
 */
function ai_send_message(array $messages, array $options = []): string
{
    $provider = strtolower(ai_config_value('AI_PROVIDER', AI_DEFAULT_PROVIDER));
    if ($provider !== 'nvidia') {
        throw new AiProviderException('configuration', 'Unsupported AI provider.');
    }

    return nvidia_nim_send_message($messages, $options);
}
