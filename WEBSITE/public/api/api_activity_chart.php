<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/SampQuery.php';

$range = isset($_GET['range']) ? $_GET['range'] : '7d';

// Function to translate English days to Indonesian
function getIndonesianDay($index) {
    $days = [1 => 'Minggu', 2 => 'Senin', 3 => 'Selasa', 4 => 'Rabu', 5 => 'Kamis', 6 => 'Jumat', 7 => 'Sabtu'];
    return $days[$index] ?? '';
}

$data = [];

try {
    if ($range === '24h') {
        // Step 1: Ambil data Peak dari jam terdahulu (23 jam terakhir)
        $stmt_past = $pdo->query("
            SELECT 
                DATE_FORMAT(logged_at, '%H:00') as name, 
                MAX(players_online) as active
            FROM ucp_server_activity 
            WHERE logged_at >= NOW() - INTERVAL 24 HOUR
              AND logged_at < DATE_FORMAT(NOW(), '%Y-%m-%d %H:00:00')
            GROUP BY DATE(logged_at), HOUR(logged_at)
            ORDER BY DATE(logged_at) ASC, HOUR(logged_at) ASC
        ");
        $data = $stmt_past->fetchAll(PDO::FETCH_ASSOC);
        
        // Step 2: Ambil data Paling Baru (Real-time Exact Minute) yang terjadi di jam INI
        $stmt_curr = $pdo->query("
            SELECT 
                DATE_FORMAT(logged_at, '%H:%i') as name, 
                players_online as active
            FROM ucp_server_activity 
            WHERE logged_at >= DATE_FORMAT(NOW(), '%Y-%m-%d %H:00:00')
            ORDER BY logged_at DESC 
            LIMIT 1
        ");
        $curr = $stmt_curr->fetch(PDO::FETCH_ASSOC);
        
        if ($curr) {
            $data[] = $curr; // Gabungkan poin real-time di akhir array
        }
    } elseif ($range === '4w') {
        $stmt = $pdo->query("
            SELECT 
                WEEK(logged_at, 1) as week_num, 
                MAX(players_online) as active
            FROM ucp_server_activity 
            WHERE logged_at >= NOW() - INTERVAL 4 WEEK
            GROUP BY YEAR(logged_at), WEEK(logged_at, 1)
            ORDER BY YEAR(logged_at) ASC, WEEK(logged_at, 1) ASC
        ");
        $dbData = $stmt->fetchAll(PDO::FETCH_ASSOC);
        
        $weekCounter = 1;
        foreach($dbData as $row) {
            $data[] = [
                'name' => 'Minggu ' . $weekCounter,
                'active' => (int)$row['active']
            ];
            $weekCounter++;
        }
    } else {
        // Default to '7d'
        $stmt = $pdo->query("
            SELECT 
                DAYOFWEEK(logged_at) as day_index, 
                MAX(players_online) as active
            FROM ucp_server_activity 
            WHERE logged_at >= NOW() - INTERVAL 7 DAY
            GROUP BY DATE(logged_at)
            ORDER BY DATE(logged_at) ASC
        ");
        $dbData = $stmt->fetchAll(PDO::FETCH_ASSOC);
        
        if(count($dbData) > 0) {
            foreach($dbData as $row) {
                $data[] = [
                    'name' => getIndonesianDay((int)$row['day_index']),
                    'active' => (int)$row['active']
                ];
            }
        }
    }
} catch (PDOException $e) {
    // Silently ignore or log error, but return empty array
    $data = [];
}

// Convert active to integers uniformly just in case
foreach($data as &$row) {
    if(isset($row['active'])) {
        $row['active'] = (int)$row['active'];
    }
}

echo json_encode($data);
?>
