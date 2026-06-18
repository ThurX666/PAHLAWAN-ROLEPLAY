<?php

require_once dirname(__DIR__) . '/public/api/db_env.php';

function migration_state_assert(bool $condition, string $message): void
{
    if (!$condition) {
        throw new RuntimeException($message);
    }
}

$config = get_db_config();
$pdo = new PDO(
    "mysql:host={$config['host']};port={$config['port']};dbname={$config['name']};charset=utf8mb4",
    $config['user'],
    $config['pass'],
    [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]
);

$migrationPath = dirname(__DIR__, 2) . '/DATABASE/migrations/20260618_story_review_system.sql';
migration_state_assert(is_file($migrationPath), 'Story Review migration file is missing.');

$requiredColumns = [
    'ucp_character_stories' => ['id', 'character_id', 'content', 'username'],
    'ucp_story_reviews' => [
        'id', 'story_id', 'character_id', 'reviewer_id', 'reviewer_username',
        'ai_provider', 'ai_model', 'analysis_version', 'story_content_hash',
        'word_count', 'character_count', 'overall_score', 'grammar_score',
        'readability_score', 'roleplay_score', 'plagiarism_score',
        'plagiarism_threshold', 'review_notes', 'created_at',
    ],
    'ucp_story_review_matches' => [
        'id', 'review_id', 'matched_story_id', 'matched_character_id',
        'similarity_percentage', 'match_rank', 'matched_content_hash', 'created_at',
    ],
];

foreach ($requiredColumns as $table => $columns) {
    $tableStmt = $pdo->prepare(
        'SELECT COUNT(*)
         FROM information_schema.TABLES
         WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = ?'
    );
    $tableStmt->execute([$table]);
    migration_state_assert((int)$tableStmt->fetchColumn() === 1, "Required table {$table} is missing.");

    $columnStmt = $pdo->prepare(
        'SELECT COLUMN_NAME
         FROM information_schema.COLUMNS
         WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = ?'
    );
    $columnStmt->execute([$table]);
    $actualColumns = $columnStmt->fetchAll(PDO::FETCH_COLUMN);
    foreach ($columns as $column) {
        migration_state_assert(
            in_array($column, $actualColumns, true),
            "Required column {$table}.{$column} is missing."
        );
    }
}

$legacyStmt = $pdo->query(
    "SELECT TABLE_NAME
     FROM information_schema.TABLES
     WHERE TABLE_SCHEMA = DATABASE()
       AND TABLE_NAME IN ('story_reviews', 'story_review_matches')"
);
migration_state_assert($legacyStmt->fetchAll(PDO::FETCH_COLUMN) === [], 'Legacy non-prefixed review tables still exist.');

echo "story_review_migration_state_test=passed\n";
