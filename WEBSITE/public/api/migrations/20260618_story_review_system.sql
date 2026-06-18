-- Story Review System planning migration.
-- Generated 2026-06-18. Review and execute manually; do not auto-run.

-- Normalize the existing story table to the contract already used by
-- api_stories_upload.php and api_admin_stories.php.
ALTER TABLE `ucp_character_stories`
  ADD COLUMN IF NOT EXISTS `username` varchar(22) DEFAULT NULL AFTER `character_id`;

UPDATE `ucp_character_stories` AS `cs`
JOIN `player_characters` AS `c` ON `c`.`pID` = `cs`.`character_id`
SET `cs`.`username` = `c`.`Char_UCP`
WHERE `cs`.`username` IS NULL OR `cs`.`username` = '';

CREATE TABLE IF NOT EXISTS `story_reviews` (
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
  KEY `idx_story_reviews_story_created` (`story_id`, `created_at`),
  KEY `idx_story_reviews_character_created` (`character_id`, `created_at`),
  KEY `idx_story_reviews_reviewer` (`reviewer_id`),
  KEY `idx_story_reviews_content_hash` (`story_content_hash`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE IF NOT EXISTS `story_review_matches` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `review_id` bigint(20) unsigned NOT NULL,
  `matched_story_id` int(11) NOT NULL,
  `matched_character_id` int(11) NOT NULL,
  `similarity_percentage` decimal(5,2) unsigned NOT NULL,
  `match_rank` smallint(5) unsigned NOT NULL,
  `matched_content_hash` char(64) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_story_review_match` (`review_id`, `matched_story_id`),
  KEY `idx_story_review_matches_rank` (`review_id`, `match_rank`),
  KEY `idx_story_review_matches_story` (`matched_story_id`),
  CONSTRAINT `fk_story_review_matches_review`
    FOREIGN KEY (`review_id`) REFERENCES `story_reviews` (`id`)
    ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Destructive rollback (manual only; intentionally commented):
-- DROP TABLE IF EXISTS `story_review_matches`;
-- DROP TABLE IF EXISTS `story_reviews`;
