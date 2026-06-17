<?php
require_once __DIR__ . '/config.php';


$username = ucp_require_username($_GET['username'] ?? null);

try {
    // Ambil data akun UCP beserta data profil untuk keamanan
    $stmt = $conn->prepare("
        SELECT 
            p.ID as id, 
            p.vip_status, 
            p.gold, 
            p.Verify_Status as is_verified,
            up.discord_id,
            up.is_2fa_enabled 
        FROM player_ucp p 
        LEFT JOIN ucp_user_profiles up ON p.UCP = up.username 
        WHERE p.UCP = :username LIMIT 1");
    $stmt->execute(['username' => $username]);
    
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user) {
        $ucp_id = $user['id'];
        
        // Ambil jumlah karakter
        $stmt_char = $conn->prepare("SELECT COUNT(pID) as char_count FROM player_characters WHERE Char_UCP = :ucp_id");
        // Gunakan ucp_id (ID bukan UCP string) jika Char_UCP di database adalah ID. 
        // Jika Char_UCP adalah string username, ganti $ucp_id dengan $username
        $stmt_char->bindParam(':ucp_id', $username);
        $stmt_char->execute();
        $charData = $stmt_char->fetch(PDO::FETCH_ASSOC);
        $charUsed = $charData ? $charData['char_count'] : 0;
        
        // Setup Security Status (Gabungan Email, 2FA, Discord)
        $securityStatus = "LOW";
        $securityDetail = "Belum Verifikasi";
        
        $hasEmail = (int)$user['is_verified'] === 1;
        $has2FA = !empty($user['is_2fa_enabled']) && (int)$user['is_2fa_enabled'] === 1;
        $hasDiscord = !empty($user['discord_id']);

        if ($has2FA && $hasDiscord) {
            $securityStatus = "VERIFIED";
            $securityDetail = "2FA & Discord";
        } else if ($has2FA) {
            $securityStatus = "PARTIAL";
            $securityDetail = "2FA Only";
        } else if ($hasEmail && $hasDiscord) {
            $securityStatus = "VERIFIED";
            $securityDetail = "Email & Discord";
        } else if ($hasDiscord) {
            $securityStatus = "PARTIAL";
            $securityDetail = "Discord Only";
        } else if ($hasEmail) {
            $securityStatus = "PARTIAL";
            $securityDetail = "Email Only";
        }

        echo json_encode([
            'status' => 'success',
            'vipStatus' => ($user['vip_status'] !== 'None' && $user['vip_status'] !== '') ? "VIP " . $user['vip_status'] : "None",
            'vipExpired' => ($user['vip_status'] !== 'None' && $user['vip_status'] !== '') ? "Aktif" : "-",
            'gold' => number_format((int)$user['gold'], 0, ',', '.') . " GC",
            'security' => $securityStatus,
            'securityDetail' => $securityDetail,
            'charUsed' => (string)$charUsed,
            'charMax' => "3"
        ]);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Akun tidak ditemukan.']);
    }
} catch (PDOException $e) {
    if (strpos($e->getMessage(), "Table") !== false && strpos($e->getMessage(), "characters") !== false) {
        // Fallback jika tabel characters belum dibuat
        echo json_encode([
            'status' => 'success',
            'vipStatus' => "None",
            'vipExpired' => "-",
            'gold' => "0 GC",
            'security' => "LOW",
            'securityDetail' => "Menunggu DB Characters",
            'charUsed' => "0",
            'charMax' => "3"
        ]);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Database error.']);
    }
}
?>
