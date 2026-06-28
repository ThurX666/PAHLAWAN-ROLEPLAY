-- Migration: Add UNIQUE INDEX on player_ucp.discord_id
-- Purpose: Prevent duplicate Discord account links (race condition protection)
-- Date: 2026-06-29
-- Safe: No duplicate discord_id values exist in current data (verified via DB query)

-- Step 1: Clean up empty-string discord_id values to NULL
-- Empty strings break unique constraint semantics and cause confusion
UPDATE player_ucp
SET discord_id = NULL
WHERE discord_id = '';

-- Step 2: Add unique index
-- NULL values are not considered duplicates in MySQL/MariaDB UNIQUE indexes,
-- so multiple rows with discord_id=NULL are allowed (correct behavior)
ALTER TABLE player_ucp
ADD UNIQUE INDEX idx_discord_id_unique (discord_id);

-- Rollback (if needed):
-- ALTER TABLE player_ucp DROP INDEX idx_discord_id_unique;
