-- Apply manually to the same database used by the gamemode.
-- This migration is intentionally not executed from normal API requests.

ALTER TABLE `player_characters`
  ADD COLUMN IF NOT EXISTS `story_status` ENUM('None','Pending','Active','Revision') NOT NULL DEFAULT 'None';

ALTER TABLE `ucp_user_profiles`
  ADD COLUMN IF NOT EXISTS `discord_avatar_hash` VARCHAR(255) DEFAULT NULL;

ALTER TABLE `ucp_character_stories`
  ADD COLUMN IF NOT EXISTS `username` VARCHAR(22) NOT NULL DEFAULT '',
  ADD COLUMN IF NOT EXISTS `character_name` VARCHAR(64) NOT NULL DEFAULT '',
  ADD COLUMN IF NOT EXISTS `photo_url` VARCHAR(255) DEFAULT NULL,
  ADD COLUMN IF NOT EXISTS `plagiarism_score` INT NOT NULL DEFAULT 0;

CREATE TABLE IF NOT EXISTS `ucp_item_claims` (
  `id` BIGINT NOT NULL AUTO_INCREMENT,
  `claim_code` VARCHAR(24) NOT NULL,
  `username` VARCHAR(22) NOT NULL,
  `character_id` INT NOT NULL DEFAULT 0,
  `claim_type` ENUM('Item','Vehicle','Property','Service','Skin') NOT NULL DEFAULT 'Item',
  `promo_item_id` INT DEFAULT NULL,
  `item_name` VARCHAR(255) NOT NULL,
  `item_model` INT NOT NULL DEFAULT 0,
  `quantity` INT NOT NULL DEFAULT 1,
  `metadata` LONGTEXT DEFAULT NULL,
  `gold_cost` INT NOT NULL DEFAULT 0,
  `status` ENUM('Pending','Manual','Claimed','Cancelled') NOT NULL DEFAULT 'Pending',
  `claimed_at` DATETIME DEFAULT NULL,
  `created_at` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_ucp_claim_code` (`claim_code`),
  KEY `idx_ucp_claim_character_status` (`character_id`, `status`),
  KEY `idx_ucp_claim_username_status` (`username`, `status`, `created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_job_activity` (
  `id` BIGINT NOT NULL AUTO_INCREMENT,
  `character_id` INT NOT NULL,
  `job_type` VARCHAR(32) NOT NULL,
  `earned_money` BIGINT NOT NULL DEFAULT 0,
  `worked_seconds` INT NOT NULL DEFAULT 0,
  `logged_at` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `idx_ucp_job_activity_type_date` (`job_type`, `logged_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

UPDATE `ucp_character_stories` cs
JOIN `player_characters` c ON c.`pID` = cs.`character_id`
SET cs.`username` = c.`Char_UCP`,
    cs.`character_name` = c.`Char_Name`
WHERE cs.`username` = '' OR cs.`character_name` = '';
