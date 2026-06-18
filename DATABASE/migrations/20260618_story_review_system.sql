-- UCP Story Review System planning migration.
-- Generated 2026-06-18. Review and execute manually; do not auto-run.
-- Apply this file only to the database returned by the Website runtime's
-- SELECT DATABASE(), after confirming ucp_character_stories exists there.
--
-- Legacy note:
-- Older local environments may contain non-prefixed story_reviews and
-- story_review_matches tables. This migration does not rename, copy, alias,
-- or drop them. Inspect and preserve any legacy rows before planning a
-- separate manual data transfer or cleanup.

-- Normalize the existing story table to the contract already used by
-- api_stories_upload.php and api_admin_stories.php.
ALTER TABLE `ucp_character_stories`
  ADD COLUMN IF NOT EXISTS `username` varchar(22) DEFAULT NULL AFTER `character_id`;

UPDATE `ucp_character_stories` AS `cs`
JOIN `player_characters` AS `c` ON `c`.`pID` = `cs`.`character_id`
SET `cs`.`username` = `c`.`Char_UCP`
WHERE `cs`.`username` IS NULL OR `cs`.`username` = '';

CREATE TABLE IF NOT EXISTS `ucp_story_reviews` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `story_id` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `reviewer_id` int(11) NOT NULL,
  `reviewer_username` varchar(22) NOT NULL,
  `ai_provider` varchar(32) NOT NULL DEFAULT 'nvidia',
  `ai_model` varchar(128) NOT NULL,
  `analysis_version` varchar(32) NOT NULL DEFAULT 'story-review-v1',
  `story_content_hash` char(64) NOT NULL,
  `word_count` int(10) unsigned NOT NULL,
  `character_count` int(10) unsigned NOT NULL,
  `overall_score` decimal(5,2) unsigned NOT NULL,
  `grammar_score` decimal(5,2) unsigned NOT NULL,
  `readability_score` decimal(5,2) unsigned NOT NULL,
  `roleplay_score` decimal(5,2) unsigned NOT NULL,
  `plagiarism_score` decimal(5,2) unsigned NOT NULL,
  `plagiarism_threshold` decimal(5,2) unsigned NOT NULL DEFAULT 50.00,
  `review_notes` longtext DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_story_reviews_story_created` (`story_id`, `created_at`, `id`),
  KEY `idx_ucp_story_reviews_character_created` (`character_id`, `created_at`, `id`),
  KEY `idx_ucp_story_reviews_reviewer` (`reviewer_id`),
  KEY `idx_ucp_story_reviews_content_hash` (`story_content_hash`),
  CONSTRAINT `chk_ucp_story_reviews_overall_score`
    CHECK (`overall_score` BETWEEN 0.00 AND 100.00),
  CONSTRAINT `chk_ucp_story_reviews_grammar_score`
    CHECK (`grammar_score` BETWEEN 0.00 AND 100.00),
  CONSTRAINT `chk_ucp_story_reviews_readability_score`
    CHECK (`readability_score` BETWEEN 0.00 AND 100.00),
  CONSTRAINT `chk_ucp_story_reviews_roleplay_score`
    CHECK (`roleplay_score` BETWEEN 0.00 AND 100.00),
  CONSTRAINT `chk_ucp_story_reviews_plagiarism_score`
    CHECK (`plagiarism_score` BETWEEN 0.00 AND 100.00),
  CONSTRAINT `chk_ucp_story_reviews_plagiarism_threshold`
    CHECK (`plagiarism_threshold` BETWEEN 0.00 AND 100.00)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `ucp_story_review_matches` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `review_id` bigint(20) unsigned NOT NULL,
  `matched_story_id` int(11) NOT NULL,
  `matched_character_id` int(11) NOT NULL,
  `similarity_percentage` decimal(5,2) unsigned NOT NULL,
  `match_rank` smallint(5) unsigned NOT NULL,
  `matched_content_hash` char(64) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_ucp_story_review_match` (`review_id`, `matched_story_id`),
  UNIQUE KEY `uq_ucp_story_review_rank` (`review_id`, `match_rank`),
  KEY `idx_ucp_story_review_matches_story` (`matched_story_id`),
  CONSTRAINT `chk_ucp_story_review_matches_similarity`
    CHECK (`similarity_percentage` BETWEEN 0.00 AND 100.00),
  CONSTRAINT `chk_ucp_story_review_matches_rank`
    CHECK (`match_rank` >= 1),
  CONSTRAINT `fk_ucp_story_review_matches_review`
    FOREIGN KEY (`review_id`) REFERENCES `ucp_story_reviews` (`id`)
    ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Destructive rollback notes (manual only; intentionally commented):
-- DROP TABLE IF EXISTS `ucp_story_review_matches`;
-- DROP TABLE IF EXISTS `ucp_story_reviews`;
