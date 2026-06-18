<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/story_review_ai.php';
require_once __DIR__ . '/ai_runtime_safety.php';

const STORY_REVIEW_ANALYSIS_VERSION = 'story-review-local-v1';
const STORY_REVIEW_PROVIDER = 'local';
const STORY_REVIEW_MODEL = 'deterministic-placeholder-v1';
const STORY_REVIEW_BATCH_SIZE = 200;
const STORY_REVIEW_MATCH_LIMIT = 5;

function story_review_json_success(array $data, int $statusCode = 200): void
{
    http_response_code($statusCode);
    echo json_encode([
        'status' => 'success',
        'data' => $data,
    ]);
    exit;
}

function story_review_require_schema(PDO $pdo): void
{
    $requiredColumns = [
        'ucp_character_stories' => ['id', 'character_id', 'character_name', 'content'],
        'player_characters' => ['pID', 'Char_Name'],
        'ucp_story_reviews' => [
            'id', 'story_id', 'character_id', 'reviewer_id', 'reviewer_username',
            'ai_provider', 'ai_model', 'analysis_version', 'story_content_hash',
            'word_count', 'character_count', 'overall_score', 'grammar_score',
            'readability_score', 'roleplay_score', 'plagiarism_score',
            'plagiarism_threshold', 'review_notes', 'created_at',
        ],
        'ucp_story_review_matches' => [
            'id', 'review_id', 'matched_story_id', 'matched_character_id',
            'similarity_percentage', 'match_rank', 'matched_content_hash',
            'created_at',
        ],
    ];

    try {
        foreach ($requiredColumns as $table => $columns) {
            if (!phrp_table_exists($pdo, $table)) {
                ucp_json_error('Story Review belum tersedia. Terapkan migrasi yang disetujui terlebih dahulu.', 503);
            }
            foreach ($columns as $column) {
                if (!phrp_column_exists($pdo, $table, $column)) {
                    ucp_json_error('Story Review belum tersedia. Skema database belum lengkap.', 503);
                }
            }
        }
    } catch (PDOException $e) {
        ucp_json_error('Story Review tidak dapat memverifikasi skema database.', 503);
    }
}

function story_review_plain_text(string $content): string
{
    $withSpacing = preg_replace('/<\s*br\s*\/?\s*>|<\/\s*(p|div|li|h[1-6]|blockquote)\s*>/iu', ' ', $content);
    $plain = html_entity_decode(strip_tags((string)$withSpacing), ENT_QUOTES | ENT_HTML5, 'UTF-8');
    return trim((string)preg_replace('/\s+/u', ' ', $plain));
}

function story_review_tokens(string $plainText): array
{
    $normalized = function_exists('mb_strtolower')
        ? mb_strtolower($plainText, 'UTF-8')
        : strtolower($plainText);

    if (preg_match_all('/[\p{L}\p{N}]+/u', $normalized, $matches) !== false) {
        return $matches[0];
    }

    return [];
}

function story_review_character_count(string $plainText): int
{
    return function_exists('mb_strlen')
        ? mb_strlen($plainText, 'UTF-8')
        : strlen($plainText);
}

function story_review_readability_score(string $plainText, array $tokens): float
{
    $wordCount = count($tokens);
    if ($wordCount === 0) {
        return 0.0;
    }

    $sentenceCount = preg_match_all('/[.!?]+(?:\s|$)/u', $plainText, $sentenceMatches);
    $sentenceCount = max(1, $sentenceCount === false ? 1 : $sentenceCount);

    $totalWordCharacters = 0;
    foreach ($tokens as $token) {
        $totalWordCharacters += story_review_character_count($token);
    }

    $averageSentenceLength = $wordCount / $sentenceCount;
    $averageWordLength = $totalWordCharacters / $wordCount;
    $sentencePenalty = max(0.0, $averageSentenceLength - 18.0) * 2.0;
    $wordPenalty = abs($averageWordLength - 5.0) * 5.0;
    $lengthPenalty = $wordCount < 300 ? min(30.0, (300 - $wordCount) / 6.0) : 0.0;

    return round(max(0.0, min(100.0, 100.0 - $sentencePenalty - $wordPenalty - $lengthPenalty)), 2);
}

function story_review_shingles(array $tokens): array
{
    $shingles = [];
    $tokenCount = count($tokens);

    if ($tokenCount < 3) {
        foreach ($tokens as $token) {
            $shingles[$token] = true;
        }
        return $shingles;
    }

    for ($index = 0; $index <= $tokenCount - 3; $index++) {
        $shingle = $tokens[$index] . "\x1F" . $tokens[$index + 1] . "\x1F" . $tokens[$index + 2];
        $shingles[$shingle] = true;
    }

    return $shingles;
}

function story_review_similarity(array $left, array $right): float
{
    $leftCount = count($left);
    $rightCount = count($right);
    if ($leftCount === 0 || $rightCount === 0) {
        return 0.0;
    }

    $smaller = $leftCount <= $rightCount ? $left : $right;
    $larger = $leftCount <= $rightCount ? $right : $left;
    $intersection = 0;

    foreach ($smaller as $shingle => $_present) {
        if (isset($larger[$shingle])) {
            $intersection++;
        }
    }

    $union = $leftCount + $rightCount - $intersection;
    return $union > 0 ? round(($intersection / $union) * 100.0, 2) : 0.0;
}

function story_review_threshold(): float
{
    $configured = filter_var(app_env('AI_STORY_PLAGIARISM_THRESHOLD', '50'), FILTER_VALIDATE_FLOAT);
    if ($configured === false) {
        return 50.0;
    }
    return round(max(0.0, min(100.0, (float)$configured)), 2);
}

function story_review_load_story(PDO $pdo, int $storyId): array
{
    $stmt = $pdo->prepare(
        'SELECT cs.id, cs.character_id, cs.content, c.Char_Name AS character_name
         FROM ucp_character_stories cs
         INNER JOIN player_characters c ON c.pID = cs.character_id
         WHERE cs.id = ?
         LIMIT 1'
    );
    $stmt->execute([$storyId]);
    $story = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$story) {
        ucp_json_error('Story tidak ditemukan atau relasi karakter tidak valid.', 404);
    }

    return $story;
}

function story_review_find_matches(PDO $pdo, int $storyId, array $sourceShingles): array
{
    $matches = [];
    $lastId = 0;

    do {
        $stmt = $pdo->prepare(
            'SELECT id, character_id, content
             FROM ucp_character_stories
             WHERE id > ? AND id <> ?
             ORDER BY id ASC
             LIMIT ' . STORY_REVIEW_BATCH_SIZE
        );
        $stmt->execute([$lastId, $storyId]);
        $batch = $stmt->fetchAll(PDO::FETCH_ASSOC);

        foreach ($batch as $candidate) {
            $lastId = (int)$candidate['id'];
            $candidateContent = (string)$candidate['content'];
            $candidateTokens = story_review_tokens(story_review_plain_text($candidateContent));
            $similarity = story_review_similarity(
                $sourceShingles,
                story_review_shingles($candidateTokens)
            );

            if ($similarity <= 0.0) {
                continue;
            }

            $matches[] = [
                'matched_story_id' => (int)$candidate['id'],
                'matched_character_id' => (int)$candidate['character_id'],
                'similarity_percentage' => $similarity,
                'matched_content_hash' => hash('sha256', $candidateContent),
            ];
        }

        usort($matches, function (array $left, array $right): int {
            if ($left['similarity_percentage'] === $right['similarity_percentage']) {
                return $left['matched_story_id'] <=> $right['matched_story_id'];
            }
            return $left['similarity_percentage'] < $right['similarity_percentage'] ? 1 : -1;
        });
        $matches = array_slice($matches, 0, STORY_REVIEW_MATCH_LIMIT);
    } while (count($batch) === STORY_REVIEW_BATCH_SIZE);

    foreach ($matches as $index => &$match) {
        $match['match_rank'] = $index + 1;
    }
    unset($match);

    return $matches;
}

function story_review_format_review(array $row): array
{
    $currentContent = $row['current_content'] ?? null;
    $isStale = $currentContent === null
        || !hash_equals((string)$row['story_content_hash'], hash('sha256', (string)$currentContent));

    return [
        'id' => (int)$row['id'],
        'story_id' => (int)$row['story_id'],
        'character_id' => (int)$row['character_id'],
        'character_name' => $row['character_name'] ?? null,
        'reviewer_id' => (int)$row['reviewer_id'],
        'reviewer_username' => (string)$row['reviewer_username'],
        'ai_provider' => (string)$row['ai_provider'],
        'ai_model' => (string)$row['ai_model'],
        'analysis_version' => (string)$row['analysis_version'],
        'word_count' => (int)$row['word_count'],
        'character_count' => (int)$row['character_count'],
        'overall_score' => (float)$row['overall_score'],
        'grammar_score' => (float)$row['grammar_score'],
        'readability_score' => (float)$row['readability_score'],
        'roleplay_score' => (float)$row['roleplay_score'],
        'plagiarism_score' => (float)$row['plagiarism_score'],
        'plagiarism_threshold' => (float)$row['plagiarism_threshold'],
        'review_notes' => $row['review_notes'],
        'created_at' => (string)$row['created_at'],
        'is_stale' => $isStale,
        'is_deterministic_placeholder' => (
            $row['ai_provider'] === STORY_REVIEW_PROVIDER
            && $row['ai_model'] === STORY_REVIEW_MODEL
        ),
    ];
}

function story_review_fetch_review(PDO $pdo, int $storyId, ?int $reviewId = null): ?array
{
    $sql =
        'SELECT r.*, cs.content AS current_content, c.Char_Name AS character_name
         FROM ucp_story_reviews r
         LEFT JOIN ucp_character_stories cs ON cs.id = r.story_id
         LEFT JOIN player_characters c ON c.pID = r.character_id
         WHERE r.story_id = ?';
    $params = [$storyId];

    if ($reviewId !== null) {
        $sql .= ' AND r.id = ?';
        $params[] = $reviewId;
    }

    $sql .= ' ORDER BY r.created_at DESC, r.id DESC LIMIT 1';
    $stmt = $pdo->prepare($sql);
    $stmt->execute($params);
    $review = $stmt->fetch(PDO::FETCH_ASSOC);

    return $review ? story_review_format_review($review) : null;
}

$jsonData = get_sanitized_json();
$requestData = array_merge($_GET, $_POST, $jsonData);
$action = (string)($requestData['action'] ?? '');
$adminUser = ucp_require_admin(5);
if ((int)($adminUser['id'] ?? 0) < 1) {
    ucp_json_error('Referensi akun admin tidak valid.', 403);
}

story_review_require_schema($pdo);

if ($action === 'get_story_review') {
    if ($_SERVER['REQUEST_METHOD'] !== 'GET') {
        ucp_json_error('Method tidak diizinkan.', 405);
    }

    $storyId = filter_var($requestData['story_id'] ?? null, FILTER_VALIDATE_INT);
    $reviewId = isset($requestData['review_id'])
        ? filter_var($requestData['review_id'], FILTER_VALIDATE_INT)
        : null;

    if (!$storyId || $storyId < 1 || ($reviewId !== null && (!$reviewId || $reviewId < 1))) {
        ucp_json_error('Story ID atau review ID tidak valid.', 422);
    }

    $review = story_review_fetch_review($pdo, (int)$storyId, $reviewId === null ? null : (int)$reviewId);
    if ($reviewId !== null && $review === null) {
        ucp_json_error('Review tidak ditemukan untuk story tersebut.', 404);
    }
    if ($review === null) {
        story_review_load_story($pdo, (int)$storyId);
    }
    story_review_json_success([
        'review' => $review,
    ]);
}

if ($action === 'get_story_matches') {
    if ($_SERVER['REQUEST_METHOD'] !== 'GET') {
        ucp_json_error('Method tidak diizinkan.', 405);
    }

    $reviewId = filter_var($requestData['review_id'] ?? null, FILTER_VALIDATE_INT);
    if (!$reviewId || $reviewId < 1) {
        ucp_json_error('Review ID tidak valid.', 422);
    }

    $reviewStmt = $pdo->prepare(
        'SELECT id, plagiarism_threshold
         FROM ucp_story_reviews
         WHERE id = ?
         LIMIT 1'
    );
    $reviewStmt->execute([(int)$reviewId]);
    $review = $reviewStmt->fetch(PDO::FETCH_ASSOC);
    if (!$review) {
        ucp_json_error('Review tidak ditemukan.', 404);
    }

    $matchStmt = $pdo->prepare(
        'SELECT m.*, cs.content AS current_content,
                COALESCE(c.Char_Name, cs.character_name) AS character_name
         FROM ucp_story_review_matches m
         LEFT JOIN ucp_character_stories cs ON cs.id = m.matched_story_id
         LEFT JOIN player_characters c ON c.pID = m.matched_character_id
         WHERE m.review_id = ?
         ORDER BY m.match_rank ASC'
    );
    $matchStmt->execute([(int)$reviewId]);
    $threshold = (float)$review['plagiarism_threshold'];
    $matches = [];

    foreach ($matchStmt->fetchAll(PDO::FETCH_ASSOC) as $match) {
        $currentContent = $match['current_content'];
        $matches[] = [
            'id' => (int)$match['id'],
            'review_id' => (int)$match['review_id'],
            'matched_story_id' => (int)$match['matched_story_id'],
            'matched_character_id' => (int)$match['matched_character_id'],
            'character_name' => $match['character_name'],
            'similarity_percentage' => (float)$match['similarity_percentage'],
            'match_rank' => (int)$match['match_rank'],
            'is_flagged' => (float)$match['similarity_percentage'] >= $threshold,
            'is_stale' => $currentContent === null
                || !hash_equals(
                    (string)$match['matched_content_hash'],
                    hash('sha256', (string)$currentContent)
                ),
            'created_at' => (string)$match['created_at'],
        ];
    }

    story_review_json_success([
        'review_id' => (int)$reviewId,
        'plagiarism_threshold' => $threshold,
        'matches' => $matches,
    ]);
}

if ($action === 'analyze_story') {
    $requestId = ai_story_review_request_id();
    $requestStartedAt = hrtime(true);
    $logRejectedRequest = static function (string $category, int $storyRef = 0) use (
        $requestId,
        $requestStartedAt,
        $adminUser
    ): void {
        $config = ai_provider_config();
        ai_story_review_log_event([
            'request_id' => $requestId,
            'provider' => $config['provider'],
            'model' => $config['model'],
            'actor_ref' => (int)$adminUser['id'],
            'story_ref' => $storyRef,
            'latency_ms' => (int)round((hrtime(true) - $requestStartedAt) / 1000000),
            'result_category' => $category,
            'usage' => null,
        ]);
    };

    if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
        $logRejectedRequest('method_rejected');
        ucp_json_error('Method tidak diizinkan.', 405);
    }

    foreach (['content', 'story', 'story_text'] as $forbiddenField) {
        if (array_key_exists($forbiddenField, $requestData)) {
            $logRejectedRequest('client_content_rejected');
            ucp_json_error('Story text tidak boleh dikirim dari browser.', 422);
        }
    }

    $storyId = filter_var($requestData['story_id'] ?? null, FILTER_VALIDATE_INT);
    if (!$storyId || $storyId < 1) {
        $logRejectedRequest('story_id_rejected');
        ucp_json_error('Story ID tidak valid.', 422);
    }

    $story = story_review_load_story($pdo, (int)$storyId);
    $content = (string)$story['content'];
    $plainText = story_review_plain_text($content);
    $tokens = story_review_tokens($plainText);
    $sourceShingles = story_review_shingles($tokens);
    $contentHash = hash('sha256', $content);
    $wordCount = count($tokens);
    $characterCount = story_review_character_count($plainText);
    $readabilityScore = story_review_readability_score($plainText, $tokens);
    $matches = story_review_find_matches($pdo, (int)$storyId, $sourceShingles);
    $plagiarismScore = $matches ? (float)$matches[0]['similarity_percentage'] : 0.0;
    $originalityScore = max(0.0, 100.0 - $plagiarismScore);
    $overallScore = round(($readabilityScore + $originalityScore) / 2.0, 2);
    $threshold = story_review_threshold();
    $reviewNotes = 'Deterministic mode. Readability and local plagiarism were calculated server-side. NVIDIA rubric scoring is disabled, so grammar and roleplay scores remain 0.';
    $reviewProvider = STORY_REVIEW_PROVIDER;
    $reviewModel = STORY_REVIEW_MODEL;
    $analysisVersion = STORY_REVIEW_ANALYSIS_VERSION;
    $grammarScore = 0.0;
    $roleplayScore = 0.0;
    $providerUsage = null;
    $providerEnabled = ai_story_review_is_enabled();

    if ($providerEnabled) {
        $rateLimitLease = null;
        $providerException = null;
        try {
            $rateLimitLease = ai_story_review_acquire_limits(
                (int)$adminUser['id'],
                (int)$storyId
            );
            $aiRubric = story_review_ai_analyze($plainText);
            $providerUsage = ai_provider_last_metadata()['usage'] ?? null;
            $reviewProvider = (string)$aiRubric['ai_provider'];
            $reviewModel = (string)$aiRubric['ai_model'];
            $analysisVersion = (string)$aiRubric['analysis_version'];
            $grammarScore = (float)$aiRubric['grammar_score'];
            $readabilityScore = (float)$aiRubric['readability_score'];
            $roleplayScore = (float)$aiRubric['roleplay_score'];
            $overallScore = (float)$aiRubric['overall_score'];
            $reviewNotes = (string)$aiRubric['review_notes'];
        } catch (AiProviderException $e) {
            $providerException = $e;
        } finally {
            if ($rateLimitLease instanceof AiRateLimitLease) {
                $rateLimitLease->release();
            }
        }

        if ($providerException instanceof AiProviderException) {
            $config = ai_provider_config();
            ai_story_review_log_event([
                'request_id' => $requestId,
                'provider' => $config['provider'],
                'model' => $config['model'],
                'actor_ref' => (int)$adminUser['id'],
                'story_ref' => (int)$storyId,
                'latency_ms' => (int)round((hrtime(true) - $requestStartedAt) / 1000000),
                'result_category' => $providerException->category(),
                'usage' => ai_provider_last_metadata()['usage'] ?? null,
            ]);
            $publicError = story_review_ai_public_error($providerException);
            ucp_json_error($publicError['message'], $publicError['status']);
        }
    }

    $pdo->beginTransaction();
    try {
        $lockStmt = $pdo->prepare(
            'SELECT content
             FROM ucp_character_stories
             WHERE id = ? AND character_id = ?
             FOR UPDATE'
        );
        $lockStmt->execute([(int)$storyId, (int)$story['character_id']]);
        $lockedContent = $lockStmt->fetchColumn();

        if ($lockedContent === false) {
            throw new RuntimeException('Story tidak lagi tersedia.');
        }
        if (!hash_equals($contentHash, hash('sha256', (string)$lockedContent))) {
            throw new RuntimeException('Story berubah selama proses analisis. Silakan ulangi.');
        }

        $reviewStmt = $pdo->prepare(
            'INSERT INTO ucp_story_reviews (
                story_id, character_id, reviewer_id, reviewer_username,
                ai_provider, ai_model, analysis_version, story_content_hash,
                word_count, character_count, overall_score, grammar_score,
                readability_score, roleplay_score, plagiarism_score,
                plagiarism_threshold, review_notes
             ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)'
        );
        $reviewStmt->execute([
            (int)$storyId,
            (int)$story['character_id'],
            (int)$adminUser['id'],
            (string)$adminUser['username'],
            $reviewProvider,
            $reviewModel,
            $analysisVersion,
            $contentHash,
            $wordCount,
            $characterCount,
            $overallScore,
            $grammarScore,
            $readabilityScore,
            $roleplayScore,
            $plagiarismScore,
            $threshold,
            $reviewNotes,
        ]);
        $reviewId = (int)$pdo->lastInsertId();

        if ($matches) {
            $matchStmt = $pdo->prepare(
                'INSERT INTO ucp_story_review_matches (
                    review_id, matched_story_id, matched_character_id,
                    similarity_percentage, match_rank, matched_content_hash
                 ) VALUES (?, ?, ?, ?, ?, ?)'
            );
            foreach ($matches as $match) {
                $matchStmt->execute([
                    $reviewId,
                    $match['matched_story_id'],
                    $match['matched_character_id'],
                    $match['similarity_percentage'],
                    $match['match_rank'],
                    $match['matched_content_hash'],
                ]);
            }
        }

        $pdo->commit();
    } catch (RuntimeException $e) {
        if ($pdo->inTransaction()) {
            $pdo->rollBack();
        }
        ai_story_review_log_event([
            'request_id' => $requestId,
            'provider' => $reviewProvider,
            'model' => $reviewModel,
            'actor_ref' => (int)$adminUser['id'],
            'story_ref' => (int)$storyId,
            'latency_ms' => (int)round((hrtime(true) - $requestStartedAt) / 1000000),
            'result_category' => 'persistence_conflict',
            'usage' => $providerUsage,
        ]);
        ucp_json_error($e->getMessage(), 409);
    } catch (PDOException $e) {
        if ($pdo->inTransaction()) {
            $pdo->rollBack();
        }
        ai_story_review_log_event([
            'request_id' => $requestId,
            'provider' => $reviewProvider,
            'model' => $reviewModel,
            'actor_ref' => (int)$adminUser['id'],
            'story_ref' => (int)$storyId,
            'latency_ms' => (int)round((hrtime(true) - $requestStartedAt) / 1000000),
            'result_category' => 'persistence_error',
            'usage' => $providerUsage,
        ]);
        ucp_json_error('Gagal menyimpan Story Review. Pastikan migrasi database telah diterapkan.', 503);
    }

    $persistedReview = story_review_fetch_review($pdo, (int)$storyId, $reviewId);
    ai_story_review_log_event([
        'request_id' => $requestId,
        'provider' => $reviewProvider,
        'model' => $reviewModel,
        'actor_ref' => (int)$adminUser['id'],
        'story_ref' => (int)$storyId,
        'latency_ms' => (int)round((hrtime(true) - $requestStartedAt) / 1000000),
        'result_category' => $providerEnabled
            ? 'provider_review_persisted'
            : 'deterministic_review_persisted',
        'usage' => $providerUsage,
    ]);
    story_review_json_success([
        'review' => $persistedReview,
        'match_count' => count($matches),
        'manual_approval_required' => true,
    ], 201);
}

ucp_json_error('Action Story Review tidak didukung.', 404);
