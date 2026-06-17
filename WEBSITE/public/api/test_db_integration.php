<?php
require_once __DIR__ . '/config.php';
ucp_require_admin(10);

$health = phrp_database_status($conn);

$sample = [];
if ($health['integrated_with_gamemode']) {
    try {
        $ucpCount = (int) $conn->query('SELECT COUNT(*) FROM player_ucp')->fetchColumn();
        $charCount = (int) $conn->query('SELECT COUNT(*) FROM player_characters')->fetchColumn();
        $onlineCount = 0;

        if (($health['ucp_tables']['ucp_online_players'] ?? '') === 'ok') {
            $onlineCount = (int) $conn->query('SELECT COUNT(*) FROM ucp_online_players')->fetchColumn();
        }

        $sample = [
            'player_ucp_rows' => $ucpCount,
            'player_characters_rows' => $charCount,
            'ucp_online_players_rows' => $onlineCount,
        ];
    } catch (PDOException $e) {
        $sample['error'] = $e->getMessage();
    }
}

echo json_encode([
    'status' => $health['status'],
    'integrated_with_gamemode' => $health['integrated_with_gamemode'],
    'message' => $health['message'],
    'connection' => [
        'host' => $health['host'],
        'port' => $health['port'],
        'database' => $health['database'],
    ],
    'gamemode_tables' => $health['gamemode_tables'],
    'ucp_tables' => $health['ucp_tables'],
    'sample_counts' => $sample,
], JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);
