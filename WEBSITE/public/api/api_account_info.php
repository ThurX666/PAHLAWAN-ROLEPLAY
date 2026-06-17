<?php
require_once __DIR__ . '/config.php';


$username = ucp_require_username($_GET['username'] ?? null);

try {
    $stmt = $conn->prepare("SELECT ID as id, Register_Date as created_at, Last_Login as last_login, Verify_Status as is_verified, last_device, last_ip, last_location FROM player_ucp WHERE UCP = :username LIMIT 1");
    $stmt->bindParam(':username', $username);
    $stmt->execute();
    
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user) {
        $timestamp = !empty($user['created_at']) ? strtotime($user['created_at']) : 0;
        if ($timestamp > 0) {
            $hari = array('Minggu', 'Senin', 'Selasa', 'Rabu', 'Kamis', 'Jumat', 'Sabtu');
            $bulan = array(1 => 'Januari', 'Februari', 'Maret', 'April', 'Mei', 'Juni', 'Juli', 'Agustus', 'September', 'Oktober', 'November', 'Desember');
            $joinDate = $hari[date('w', $timestamp)] . ', ' . date('d', $timestamp) . ' ' . $bulan[date('n', $timestamp)] . ' ' . date('Y', $timestamp) . "\n" . date('H:i:s', $timestamp) . ' WIB';
        } else {
            $joinDate = "-";
        }
        
        $lastLogin = "-";
        if (!empty($user['last_login'])) {
            $ts = strtotime($user['last_login']);
            $now = time();
            $diff = $now - $ts;
            
            $is_today = date('Y-m-d', $ts) === date('Y-m-d', $now);
            
            if ($is_today) {
                if ($diff < 60) {
                    $lastLogin = "Baru saja";
                } elseif ($diff < 3600) {
                    $menit = floor($diff / 60);
                    $lastLogin = "$menit menit yang lalu";
                } elseif ($diff < 86400) {
                    $jam = floor($diff / 3600);
                    $lastLogin = "$jam jam yang lalu";
                } else {
                    $lastLogin = "Hari ini";
                }
            } else {
                $hari = array('Minggu', 'Senin', 'Selasa', 'Rabu', 'Kamis', 'Jumat', 'Sabtu');
                $bulan = array(1 => 'Januari', 'Februari', 'Maret', 'April', 'Mei', 'Juni', 'Juli', 'Agustus', 'September', 'Oktober', 'November', 'Desember');
                $lastLogin = $hari[date('w', $ts)] . ', ' . date('d', $ts) . ' ' . $bulan[date('n', $ts)] . ' ' . date('Y', $ts) . "\n" . date('H:i:s', $ts) . ' WIB';
            }
        } else {
            $lastLogin = "Belum pernah login";
        }
        
        $dbDevice = !empty($user['last_device']) ? $user['last_device'] : "Unknown Device";
        $dbIp = !empty($user['last_ip']) ? $user['last_ip'] : ($_SERVER['REMOTE_ADDR'] === '::1' ? '127.0.0.1' : $_SERVER['REMOTE_ADDR']);
        $dbLoc = !empty($user['last_location']) ? "\n(" . $user['last_location'] . ")" : "";

        echo json_encode([
            'status' => 'success',
            'id' => "#" . str_pad($user['id'], 4, "0", STR_PAD_LEFT),
            'joinDate' => $joinDate,
            'device' => $dbDevice,
            'ip' => trim($dbIp . $dbLoc),
            'accountStatus' => ((int)$user['is_verified'] === 1) ? "Aktif" : "Menunggu Verifikasi",
            'lastLogin' => $lastLogin
        ]);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Akun tidak ditemukan.']);
    }
} catch (PDOException $e) {
    echo json_encode(['status' => 'error', 'message' => 'Database error.']);
}
?>
