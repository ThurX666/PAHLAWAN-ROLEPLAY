<?php
require_once __DIR__ . '/config.php';


$method = $_SERVER['REQUEST_METHOD'];
$adminUser = ucp_require_admin(5);

if ($method === 'GET') {
    $action = $_GET['action'] ?? '';
    
    if ($action === 'list') {
        try {
            // Fetch characters
            $stmt = $pdo->query("SELECT pID as id, Char_Name as name, Char_Level as score, Char_Money as money, 'Warga Sipil' as faction, 'Offline' as status FROM player_characters ORDER BY pID DESC");
            $characters = $stmt->fetchAll(PDO::FETCH_ASSOC);
            
            // Format for frontend
            $formatted = array_map(function($char) {
                return [
                    "id" => $char['id'],
                    "name" => $char['name'],
                    "score" => (int) $char['score'],
                    "faction" => $char['faction'] ?: 'Warga Sipil',
                    "ping" => rand(20, 80), // Simulated ping
                    "status" => $char['status'],
                    "money" => (int) $char['money']
                ];
            }, $characters);
            
            echo json_encode(["status" => "success", "data" => $formatted]);
        } catch (PDOException $e) {
            echo json_encode(["status" => "error", "message" => "DB Error: " . $e->getMessage()]);
        }
    }
} elseif ($method === 'POST') {
    $input = get_sanitized_json();
    $action = $input['action'] ?? '';
    $playerId = $input['playerId'] ?? 0;
    
    if (!$playerId) {
        echo json_encode(["status" => "error", "message" => "Parameter tidak valid (ID diperlukan)"]);
        exit;
    }
    
    try {
        if ($action === 'Ban') {
            $stmtChar = $pdo->prepare("SELECT Char_Name, Char_IP FROM player_characters WHERE pID = ?");
            $stmtChar->execute([$playerId]);
            $charData = $stmtChar->fetch();
            
            if ($charData) {
                $charName = $charData['Char_Name'];
                $charIp = $charData['Char_IP'];
                $longip = ip2long($charIp);
                $banDate = time();
                $adminName = $adminUser['username'];
                $reason = 'Banned from UCP Panel';
                
                $stmtBan = $pdo->prepare("INSERT INTO player_bans (name, ip, longip, ban_expire, ban_date, last_activity_timestamp, admin, reason) VALUES (?, ?, ?, 0, ?, ?, ?, ?)");
                $stmtBan->execute([$charName, $charIp, $longip, $banDate, $banDate, $adminName, $reason]);
                
                $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'BAN', ?, ?)");
                $logStmt->execute([$adminUser['username'], $playerId, "Banned Character: $charName"]);
                
                echo json_encode(["status" => "success", "message" => "Pemain $charName berhasil dibanned!"]);
            } else {
                echo json_encode(["status" => "error", "message" => "Karakter tidak ditemukan"]);
            }
            
        } elseif ($action === 'CK') {
            ucp_json_error('Aksi CK dinonaktifkan sampai prosedur reset seluruh data karakter tersedia.', 501);
            
        } elseif ($action === 'Kick') {
            ucp_json_error('Kick dari UCP membutuhkan command bridge gamemode dan belum diaktifkan.', 501);
            
        } elseif ($action === 'Reset PW') {
            ucp_json_error('Reset password admin dinonaktifkan. Gunakan alur OTP lupa password.', 501);
        } elseif ($action === 'Save') {
            $data = $input['data'] ?? [];
            $score = (int) ($data['score'] ?? 1);
            
            $stmt = $pdo->prepare("UPDATE player_characters SET Char_Level = ? WHERE pID = ?");
            $stmt->execute([$score, $playerId]);
            
            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'UPDATE_DATA', ?, ?)");
            $logStmt->execute([$adminUser['username'], $playerId, "Update Level=$score"]);

            echo json_encode(["status" => "success", "message" => "Data pemain berhasil disimpan!"]);
        } else {
            echo json_encode(["status" => "error", "message" => "Aksi tidak dikenali"]);
        }
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal: " . $e->getMessage()]);
    }
}
?>
