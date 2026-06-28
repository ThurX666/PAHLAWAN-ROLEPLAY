-- Migration: player_ucp date columns + otp_expiry
-- File: DATABASE/migrations/20260628_player_ucp_date_columns.sql
-- 
-- ⚠️ BACKUP DATABASE SEBELUM EKSEKUSI
-- 
-- Changes:
-- 1. ALTER Register_Date varchar(30) → DATETIME
-- 2. ALTER Last_Login varchar(30) → DATETIME
-- 3. ADD otp_expiry DATETIME (untuk OTP expiry check)
--
-- Caveats:
-- - varchar values sudah dalam format 'YYYY-MM-DD HH:MM:SS', kompatibel dengan ALTER
-- - Gunakan ALGORITHM=INPLACE untuk menghindari table copy (InnoDB 5.6+)
-- - Test dulu di environment dev/staging

START TRANSACTION;

-- 1. Convert Register_Date
ALTER TABLE player_ucp 
  MODIFY Register_Date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

-- 2. Convert Last_Login  
ALTER TABLE player_ucp
  MODIFY Last_Login DATETIME DEFAULT NULL;

-- 3. Add otp_expiry column
ALTER TABLE player_ucp
  ADD otp_expiry DATETIME DEFAULT NULL AFTER Verify_Code;

-- Verify
SELECT 
  COLUMN_NAME, 
  DATA_TYPE, 
  COLUMN_DEFAULT
FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_SCHEMA = 'arivena' 
  AND TABLE_NAME = 'player_ucp'
  AND COLUMN_NAME IN ('Register_Date', 'Last_Login', 'otp_expiry');

-- ROLLBACK jika error: ROLLBACK;
-- Jika sukses: COMMIT;

COMMIT;
