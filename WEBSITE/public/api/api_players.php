<?php
require_once __DIR__ . '/config.php';


$method = $_SERVER['REQUEST_METHOD'];

// Helper to get Admin ID (in production, use Session)
$adminId = 1;

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
                $adminName = 'Admin UCP';
                $reason = 'Banned from UCP Panel';
                
                $stmtBan = $pdo->prepare("INSERT INTO player_bans (name, ip, longip, ban_expire, ban_date, last_activity_timestamp, admin, reason) VALUES (?, ?, ?, 0, ?, ?, ?, ?)");
                $stmtBan->execute([$charName, $charIp, $longip, $banDate, $banDate, $adminName, $reason]);
                
                $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'BAN', ?, ?)");
                $logStmt->execute(['Admin UCP', $playerId, "Banned Character: $charName"]);
                
                echo json_encode(["status" => "success", "message" => "Pemain $charName berhasil dibanned!"]);
            } else {
                echo json_encode(["status" => "error", "message" => "Karakter tidak ditemukan"]);
            }
            
        } elseif ($action === 'CK') {
            $stmt = $pdo->prepare("UPDATE player_characters SET Char_Level=1, Char_Money=250, Char_BankMoney=0 WHERE pID = ?");
            $stmt->execute([$playerId]);

            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'CK', ?, 'Character Killed & Reset')");
            $logStmt->execute(['Admin System', $playerId]);
            
            echo json_encode(["status" => "success", "message" => "Character Kill (CK) berhasil"]);
            
        } elseif ($action === 'Kick') {
            $stmt = $pdo->prepare("UPDATE player_characters SET Char_Money = Char_Money WHERE pID = ?"); // dummy query just for logging if no direct logic needed
            $stmt->execute([$playerId]);

            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'KICK', ?, 'Kicked from Server')");
            $logStmt->execute(['Admin System', $playerId]);

            echo json_encode(["status" => "success", "message" => "Pemain berhasil dikick"]);
            
        } elseif ($action === 'Reset PW') {
            $stmt = $pdo->prepare("SELECT Char_UCP as ucp_id, UCP FROM player_characters JOIN player_ucp ON player_characters.Char_UCP = player_ucp.UCP WHERE pID = ?");
            $stmt->execute([$playerId]);
            $char = $stmt->fetch();
            
            if ($char && !empty($char['ucp_id'])) {
                $newPassword = "pass" . rand(1000, 9999);
                $hash = password_hash($newPassword, PASSWORD_BCRYPT, ['cost' => 12]);
                
                $updStmt = $pdo->prepare("UPDATE player_ucp SET Password = ? WHERE UCP = ?");
                $updStmt->execute([$hash, $char['ucp_id']]);

                $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'RESET_PW', ?, ?)");
                $logStmt->execute(['Admin System', $playerId, "Password reset (UCP: {$char['ucp_id']})"]);

                echo json_encode(["status" => "success", "message" => "Password baru: " . $newPassword]);
            } else {
                echo json_encode(["status" => "error", "message" => "Data UCP tidak ditemukan untuk karakter ini!"]);
            }
        } elseif ($action === 'Save') {
            $data = $input['data'] ?? [];
            $score = (int) ($data['score'] ?? 1);
            
            $stmt = $pdo->prepare("UPDATE player_characters SET Char_Level = ? WHERE pID = ?");
            $stmt->execute([$score, $playerId]);
            
            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, 'UPDATE_DATA', ?, ?)");
            $logStmt->execute(['Admin System', $playerId, "Update Level=$score"]);

            echo json_encode(["status" => "success", "message" => "Data pemain berhasil disimpan!"]);
        } else {
            echo json_encode(["status" => "error", "message" => "Aksi tidak dikenali"]);
        }
    } catch (PDOException $e) {
        echo json_encode(["status" => "error", "message" => "Gagal: " . $e->getMessage()]);
    }
}
?>
