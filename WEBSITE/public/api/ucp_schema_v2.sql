CREATE TABLE IF NOT EXISTS `ucp_system_settings` (
  `setting_key` varchar(100) NOT NULL,
  `setting_value` text DEFAULT NULL,
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`setting_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_user_profiles` (
  `id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(22) NOT NULL,
  `ooc_name` varchar(100) DEFAULT NULL,
  `birth_date` date DEFAULT NULL,
  `phone_number` varchar(20) DEFAULT NULL,
  `address` varchar(255) DEFAULT NULL,
  `gender` varchar(20) DEFAULT NULL,
  `discord_id` varchar(50) DEFAULT NULL,
  `discord_avatar_hash` varchar(255) DEFAULT NULL,
  `is_locked` tinyint(1) NOT NULL DEFAULT 0,
  `is_2fa_enabled` tinyint(1) NOT NULL DEFAULT 0,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_ucp_profile_username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_inbox_messages` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `username` varchar(22) NOT NULL,
  `title` varchar(255) NOT NULL,
  `message` text DEFAULT NULL,
  `type` varchar(50) NOT NULL DEFAULT 'System',
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `is_read` tinyint(1) NOT NULL DEFAULT 0,
  `voucher_code` varchar(50) DEFAULT NULL,
  `item_name` varchar(100) DEFAULT NULL,
  `item_description` text DEFAULT NULL,
  `item_price` int DEFAULT NULL,
  `template` varchar(50) DEFAULT NULL,
  `metadata` longtext DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_ucp_inbox_username_date` (`username`, `created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_support_tickets` (
  `id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(22) NOT NULL,
  `subject` varchar(255) NOT NULL,
  `category` varchar(50) DEFAULT NULL,
  `status` enum('Open','Proses','Dijawab','Ditutup') NOT NULL DEFAULT 'Open',
  `last_update` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_ticket_username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_support_messages` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `ticket_id` int NOT NULL,
  `sender_name` varchar(22) NOT NULL,
  `message_text` text NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_support_ticket` (`ticket_id`),
  CONSTRAINT `fk_ucp_support_ticket` FOREIGN KEY (`ticket_id`) REFERENCES `ucp_support_tickets` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_promo_config` (
  `id` int NOT NULL,
  `is_active` tinyint(1) NOT NULL DEFAULT 0,
  `title` varchar(255) NOT NULL DEFAULT '',
  `description` text DEFAULT NULL,
  `discount_percent` int NOT NULL DEFAULT 0,
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_promo_items` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `type` enum('Vehicle','Property','Item') NOT NULL DEFAULT 'Item',
  `price_gold` int NOT NULL,
  `image_path` varchar(255) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `qty` int NOT NULL DEFAULT 0,
  `is_active` tinyint(1) NOT NULL DEFAULT 1,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_transactions` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `account` varchar(22) NOT NULL,
  `player_name` varchar(64) DEFAULT NULL,
  `sender_name` varchar(255) DEFAULT NULL,
  `type` varchar(50) NOT NULL DEFAULT 'donation',
  `item_name` varchar(255) NOT NULL,
  `quantity` int NOT NULL DEFAULT 1,
  `amount` varchar(50) NOT NULL,
  `payment_method` varchar(50) NOT NULL,
  `status` enum('Pending','Success','Rejected') NOT NULL DEFAULT 'Pending',
  `proof_image` varchar(255) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_transaction_account` (`account`, `created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_item_claims` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `claim_code` varchar(24) NOT NULL,
  `username` varchar(22) NOT NULL,
  `character_id` int NOT NULL,
  `claim_type` enum('Item','Vehicle','Property','Service','Skin') NOT NULL DEFAULT 'Item',
  `promo_item_id` int DEFAULT NULL,
  `item_name` varchar(255) NOT NULL,
  `item_model` int NOT NULL DEFAULT 0,
  `quantity` int NOT NULL DEFAULT 1,
  `metadata` longtext DEFAULT NULL,
  `item_description` text DEFAULT NULL,
  `gold_cost` int NOT NULL,
  `status` enum('Pending','Manual','Claimed','Cancelled') NOT NULL DEFAULT 'Pending',
  `claimed_at` datetime DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_ucp_claim_code` (`claim_code`),
  KEY `idx_ucp_claim_character_status` (`character_id`, `status`),
  KEY `idx_ucp_claim_username` (`username`, `created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_character_stories` (
  `id` int NOT NULL AUTO_INCREMENT,
  `character_id` int NOT NULL,
  `username` varchar(22) NOT NULL,
  `character_name` varchar(64) NOT NULL,
  `photo_url` varchar(255) DEFAULT NULL,
  `content` longtext NOT NULL,
  `status` enum('Pending','Revision','Active','Rejected') NOT NULL DEFAULT 'Pending',
  `admin_feedback` text DEFAULT NULL,
  `reviewed_by` varchar(50) DEFAULT NULL,
  `reviewed_at` timestamp NULL DEFAULT NULL,
  `plagiarism_score` int NOT NULL DEFAULT 0,
  `last_updated` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_ucp_story_character` (`character_id`),
  KEY `idx_ucp_story_username_status` (`username`, `status`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_admin_logs` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `admin_name` varchar(255) NOT NULL,
  `action` varchar(255) NOT NULL,
  `target_player` varchar(255) DEFAULT NULL,
  `details` text DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_admin_log_date` (`created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_online_players` (
  `player_id` int NOT NULL,
  `character_name` varchar(32) NOT NULL,
  `color` varchar(10) NOT NULL DEFAULT '#FFFFFF',
  `score` int NOT NULL DEFAULT 0,
  `ping` int NOT NULL DEFAULT 0,
  `login_time` datetime NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_server_activity` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `players_online` int NOT NULL DEFAULT 0,
  `logged_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_ucp_activity_logged_at` (`logged_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_economy_stats` (
  `id` int NOT NULL AUTO_INCREMENT,
  `stat_date` date NOT NULL,
  `total_circulation` bigint NOT NULL DEFAULT 0,
  `total_assets_value` bigint NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uq_ucp_economy_date` (`stat_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_data_change_requests` (
  `id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(22) NOT NULL,
  `change_type` varchar(100) NOT NULL,
  `target_information` varchar(255) DEFAULT '',
  `old_value` varchar(255) DEFAULT '',
  `new_value` varchar(255) NOT NULL,
  `reason` text NOT NULL,
  `status` enum('Pending','Approved','Rejected') NOT NULL DEFAULT 'Pending',
  `admin_feedback` text DEFAULT NULL,
  `reviewed_by` varchar(255) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_change_request_status` (`status`, `created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_user_requests` (
  `id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(22) NOT NULL,
  `request_type` varchar(100) NOT NULL,
  `content` text NOT NULL,
  `metadata` longtext DEFAULT NULL,
  `status` enum('Pending','Approved','Rejected') NOT NULL DEFAULT 'Pending',
  `admin_feedback` text DEFAULT NULL,
  `reviewed_by` varchar(255) DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT current_timestamp(),
  `updated_at` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_user_request_username` (`username`, `created_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

CREATE TABLE IF NOT EXISTS `ucp_job_activity` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `character_id` int NOT NULL,
  `job_type` varchar(32) NOT NULL,
  `earned_money` bigint NOT NULL DEFAULT 0,
  `worked_seconds` int NOT NULL DEFAULT 0,
  `logged_at` datetime NOT NULL DEFAULT current_timestamp(),
  PRIMARY KEY (`id`),
  KEY `idx_ucp_job_activity_type_date` (`job_type`, `logged_at`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
