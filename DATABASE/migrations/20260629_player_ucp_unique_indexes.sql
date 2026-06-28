-- Migration: Add UNIQUE INDEX on player_ucp.UCP and player_ucp.Email
-- Purpose: DB-level duplicate prevention untuk register flow
-- Date: 2026-06-29
-- Safe: No duplicate UCP or Email values exist in current data (verified via DB query)
-- Previous: Only app-level check (SELECT before INSERT) — rawan race condition

-- Clean up empty strings to NULL (consistency)
UPDATE player_ucp SET Email = NULL WHERE Email = '';

-- Step 1: Unique index on UCP (username)
ALTER TABLE player_ucp
ADD UNIQUE INDEX idx_ucp_unique (UCP);

-- Step 2: Unique index on Email
-- NULL values allowed (multiple rows with Email=NULL are fine in MySQL/MariaDB)
ALTER TABLE player_ucp
ADD UNIQUE INDEX idx_email_unique (Email);

-- Rollback (if needed):
-- ALTER TABLE player_ucp DROP INDEX idx_ucp_unique;
-- ALTER TABLE player_ucp DROP INDEX idx_email_unique;
