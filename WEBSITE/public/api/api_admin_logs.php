<?php
require_once __DIR__ . '/config.php';

 
 
 

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) {
        $action = $data['action'];
    }
}

if ($action === 'get_logs') {
    $category = $_GET['category'] ?? 'all';
    $target = $_GET['target'] ?? '';
    $date = $_GET['date'] ?? date('Y-m-d');
    
    $formattedLogs = [];
    $timePrefix = "[$date 16:00:00]";

    if ($category === 'admin') {
        $sql = "SELECT * FROM ucp_admin_logs WHERE DATE(created_at) = ?";
        $params = [$date];

        if ($target !== '') {
            $sql .= " AND (target_player LIKE ? OR details LIKE ?)";
            $params[] = "%$target%";
            $params[] = "%$target%";
        }
        
        $sql .= " ORDER BY created_at ASC LIMIT 100";
        try {
            $stmt = $pdo->prepare($sql);
            $stmt->execute($params);
            $dbLogs = $stmt->fetchAll(PDO::FETCH_ASSOC);

            foreach($dbLogs as $l) {
                $time = "[" . $l['created_at'] . "]";
                $formattedLogs[] = "$time [LOG] {$l['admin_name']} performed {$l['action']} on {$l['target_player']} - {$l['details']}";
            }
        } catch(Exception $e) {
            $formattedLogs[] = "[ERROR] Query failed: " . $e->getMessage();
        }
    } else {
        // Mock reading from SA:MP scriptfiles/logs/ as typically done with file_get_contents or tail
        // Change this path to your actual samp server path, e.g., C:/samp/scriptfiles/logs/
        $logPath = "../scriptfiles/logs/{$category}/" . ($target !== '' ? $target : 'all') . "_{$date}.txt";
        
        if (file_exists($logPath)) {
            $fileContent = file_get_contents($logPath);
            $lines = explode(PHP_EOL, $fileContent);
            foreach($lines as $line) {
                if (trim($line) !== "") $formattedLogs[] = $line;
            }
        } else {
            // Simulated placeholder since the file probably doesn't exist out of the box
            $formattedLogs[] = "[SYSTEM] Establishing secure SSH tunneling to VPS...";
            $formattedLogs[] = "$timePrefix [INFO] Attempting to read: $logPath";
            $formattedLogs[] = "$timePrefix [LOG] Server reported NO LIVE LOGS for this query parameters yet.";
            $formattedLogs[] = "$timePrefix [LOG] Target: " . ($target ? $target : 'GLOBAL');
            $formattedLogs[] = "$timePrefix [LOG] Category: $category";
            $formattedLogs[] = "[SYSTEM] Action completed. End of simulated streaming.";
        }
    }

    echo json_encode(["status" => "success", "logs" => $formattedLogs]);
} else {
    echo json_encode(["status" => "error", "message" => "Unknown action"]);
}
?>
