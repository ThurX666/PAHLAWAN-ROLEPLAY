<?php
/**
 * Setup & verifikasi integrasi database website + gamemode SA-MP.
 * Website dan gamemode harus memakai database yang sama (contoh: ariena).
 */

require_once __DIR__ . '/db_env.php';

function phrp_required_gamemode_tables(): array
{
    return ['player_ucp', 'player_characters', 'player_bans'];
}

function phrp_ucp_setup_sql_files(): array
{
    return [
        'setup_sql.txt',
        'settings_sql.txt',
        'support_sql.txt',
        'donations_sql.txt',
        'stories_sql.txt',
        'logs_sql.txt',
        'online_players_sql.txt',
        'data_requests_sql.txt',
        'overview_sql.txt',
    ];
}

function phrp_player_ucp_columns(): array
{
    return [
        'OTP_Attempts INT DEFAULT 0',
        'last_device VARCHAR(255) DEFAULT NULL',
        'last_ip VARCHAR(100) DEFAULT NULL',
        'last_location VARCHAR(255) DEFAULT NULL',
        'discord_id VARCHAR(50) DEFAULT NULL',
    ];
}

function phrp_split_sql_statements(string $sql): array
{
    $statements = [];
    $buffer = '';

    foreach (preg_split('/\R/', $sql) as $line) {
        $trimmed = trim($line);
        if ($trimmed === '' || substr($trimmed, 0, 2) === '--') {
            continue;
        }

        $buffer .= $line . "\n";
        $trimmedBuffer = rtrim($line);
        if ($trimmedBuffer !== '' && substr($trimmedBuffer, -1) === ';') {
            $statement = trim($buffer);
            if ($statement !== '') {
                $statements[] = $statement;
            }
            $buffer = '';
        }
    }

    if (trim($buffer) !== '') {
        $statements[] = trim($buffer);
    }

    return $statements;
}

function phrp_table_exists(PDO $pdo, string $table): bool
{
    $stmt = $pdo->prepare(
        'SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = DATABASE() AND table_name = ?'
    );
    $stmt->execute([$table]);
    return (int) $stmt->fetchColumn() > 0;
}

function phrp_run_sql_file(PDO $pdo, string $filePath, array &$report): void
{
    if (!file_exists($filePath)) {
        $report['warnings'][] = 'File SQL tidak ditemukan: ' . basename($filePath);
        return;
    }

    $sql = file_get_contents($filePath);
    if ($sql === false) {
        $report['errors'][] = 'Gagal membaca file SQL: ' . basename($filePath);
        return;
    }

    foreach (phrp_split_sql_statements($sql) as $statement) {
        try {
            $pdo->exec($statement);
            $report['executed'][] = basename($filePath) . ': ' . substr($statement, 0, 80);
        } catch (PDOException $e) {
            $report['warnings'][] = basename($filePath) . ': ' . $e->getMessage();
        }
    }
}

function phrp_integrate_database(PDO $pdo, bool $force = false): array
{
    $flagFile = __DIR__ . '/.migrated_integrated_v1';
    if (!$force && file_exists($flagFile)) {
        return phrp_database_status($pdo);
    }

    $report = [
        'status' => 'success',
        'database' => get_db_config()['name'],
        'gamemode_tables' => [],
        'ucp_tables' => [],
        'executed' => [],
        'warnings' => [],
        'errors' => [],
    ];

    foreach (phrp_required_gamemode_tables() as $table) {
        $exists = phrp_table_exists($pdo, $table);
        $report['gamemode_tables'][$table] = $exists ? 'ok' : 'missing';
        if (!$exists) {
            $report['errors'][] = "Tabel gamemode wajib tidak ditemukan: {$table}. Import dump DATABASE/phrp.sql terlebih dahulu.";
        }
    }

    if (!empty($report['errors'])) {
        $report['status'] = 'error';
        return $report;
    }

    foreach (phrp_player_ucp_columns() as $columnDefinition) {
        try {
            $pdo->exec("ALTER TABLE player_ucp ADD COLUMN {$columnDefinition}");
            $report['executed'][] = 'player_ucp ADD COLUMN ' . explode(' ', $columnDefinition)[0];
        } catch (PDOException $e) {
            // Kolom sudah ada
        }
    }

    foreach (phrp_ucp_setup_sql_files() as $file) {
        phrp_run_sql_file($pdo, __DIR__ . '/' . $file, $report);
    }

    foreach (['ucp_system_settings', 'ucp_user_profiles', 'ucp_transactions', 'ucp_online_players'] as $table) {
        $report['ucp_tables'][$table] = phrp_table_exists($pdo, $table) ? 'ok' : 'missing';
    }

    if (in_array('missing', $report['ucp_tables'], true)) {
        $report['status'] = 'warning';
    }

    file_put_contents($flagFile, date('c'));
    return $report;
}

function phrp_database_status(PDO $pdo): array
{
    $dbConfig = get_db_config();
    $status = [
        'status' => 'success',
        'database' => $dbConfig['name'],
        'host' => $dbConfig['host'],
        'port' => $dbConfig['port'],
        'integrated_with_gamemode' => true,
        'gamemode_tables' => [],
        'ucp_tables' => [],
        'shared_tables' => ['player_ucp', 'player_characters', 'player_bans'],
        'message' => 'Website terhubung ke database utama gamemode.',
    ];

    foreach (phrp_required_gamemode_tables() as $table) {
        $exists = phrp_table_exists($pdo, $table);
        $status['gamemode_tables'][$table] = $exists ? 'ok' : 'missing';
        if (!$exists) {
            $status['integrated_with_gamemode'] = false;
            $status['status'] = 'error';
        }
    }

    $ucpTables = [
        'ucp_system_settings',
        'ucp_user_profiles',
        'ucp_inbox_messages',
        'ucp_support_tickets',
        'ucp_transactions',
        'ucp_online_players',
        'ucp_character_stories',
        'ucp_admin_logs',
    ];

    foreach ($ucpTables as $table) {
        $status['ucp_tables'][$table] = phrp_table_exists($pdo, $table) ? 'ok' : 'missing';
    }

    if (!$status['integrated_with_gamemode']) {
        $status['message'] = 'Database website terhubung, tetapi tabel gamemode utama belum lengkap. Import DATABASE/phrp.sql.';
    }

    return $status;
}
