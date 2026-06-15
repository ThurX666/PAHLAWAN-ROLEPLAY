<?php
require_once __DIR__ . '/config.php';

$action = isset($_POST['action']) ? $_POST['action'] : '';

if ($action === 'verify_otp') {
    $username = $_POST['username'] ?? '';
    $otp_code = $_POST['otp_code'] ?? '';

    if (empty($username) || empty($otp_code)) {
        echo json_encode(['status' => 'error', 'message' => 'Username dan Kode OTP harus diisi!']);
        exit;
    }

    try {
        // Cari akun berdasarkan username ATAU email
        $stmt = $conn->prepare("SELECT 
            ID as id, 
            UCP as username,
            Email as email,
            admin_level,
            vip_status,
            gold,
            Verify_Status as is_verified, 
            Verify_Code as verify_token, 
            Register_Date as created_at 
            FROM player_ucp WHERE UCP = :username OR Email = :email LIMIT 1");
        $stmt->execute(['username' => $username, 'email' => $username]);
        $user = $stmt->fetch(PDO::FETCH_ASSOC);

        if (!$user) {
            echo json_encode(['status' => 'error', 'message' => 'Akun tidak ditemukan.']);
            exit;
        }

        if ((int)$user['is_verified'] === 1) {
            echo json_encode(['status' => 'error', 'message' => 'Akun ini sudah pernah diverifikasi!']);
            exit;
        }

        // Ambil token dari DB (integer) dan padding dengan 0 agar selalu 6 digit
        // (contoh: di DB 98963 -> jadi '098963')
        $db_token = str_pad(trim((string)$user['verify_token']), 6, '0', STR_PAD_LEFT);
        $input_token = str_pad(trim((string)$otp_code), 6, '0', STR_PAD_LEFT);

        if ($db_token !== $input_token) {
            echo json_encode(['status' => 'error', 'message' => 'Kode OTP salah atau tidak valid!']);
            exit;
        }
        
        // Cek apakah expired (jika waktu sekarang melebihi 30 menit dari created_at)
        if (!empty($user['created_at'])) {
            $expire_time = strtotime($user['created_at']) + (30 * 60); // + 30 menit
            if (time() > $expire_time) {
                // Berubah menjadi -1 secara live ketika kadaluarsa
                $stmt_expire = $conn->prepare("UPDATE player_ucp SET Verify_Code = '-1' WHERE ID = :id");
                $stmt_expire->execute(['id' => $user['id']]);

                echo json_encode(['status' => 'error', 'message' => 'Kode OTP telah habis masa berlakunya (lebih dari 30 menit). Silakan minta ulang.']);
                exit;
            }
        }

        $device = $_POST['device'] ?? 'Unknown Device';
        $ip = $_POST['ip'] ?? ($_SERVER['REMOTE_ADDR'] === '::1' ? '127.0.0.1' : $_SERVER['REMOTE_ADDR']);
        $location = $_POST['location'] ?? 'Unknown Location';

        // KODE BENAR! Update is_verified menjadi 1
        $update = $conn->prepare("UPDATE player_ucp SET Verify_Status = 1, Verify_Code = '-1', last_device = :device, last_ip = :ip, last_location = :location WHERE ID = :id");
        $update->execute([
            'id' => $user['id'],
            'device' => $device,
            'ip' => $ip,
            'location' => $location
        ]);

        $welcome_title = "Welcome to Pahlawan Roleplay! 🎉";
        
        // Cek apakah ini Pendaftaran Baru atau Re-Auth (verifikasi device/IP baru)
        // Jika sudah pernah menerima pesan Welcome sebelumnya, berarti ini adalah Re-Auth (Login Keamanan)
        $stmt_check = $conn->prepare("SELECT COUNT(*) FROM ucp_inbox_messages WHERE username = :username AND title = :title");
        $stmt_check->execute(['username' => $user['username'], 'title' => $welcome_title]);
        $is_reauth = $stmt_check->fetchColumn() > 0;

        if (!$is_reauth) {
            // --- MENGIRIM PESAN SELAMAT DATANG KE INBOX (NEW REGISTER) ---
            $stmt_inbox = $conn->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, template) VALUES (:username, :title, :message, 'System', 'Welcome')");
            $stmt_inbox->execute([
                'username' => $user['username'],
                'title' => $welcome_title,
                'message' => 'Selamat Datang di Pahlawan Roleplay! Silakan ikuti panduan awal ini.' // plain text fallback
            ]);
            // --- AKHIR PESAN SELAMAT DATANG ---
        } else {
            // --- MENGIRIM PESAN LOGIN ALERT (RE-AUTH) ---
            $alert_title = "Peringatan Keamanan: Login Baru Terdeteksi";
            $ip_safe = htmlspecialchars($ip);
            $device_safe = htmlspecialchars($device);
            $location_safe = htmlspecialchars($location);
            
            // Format waktu saat ini untuk ditampilkan di alert (zona waktu Indonesia/Jakarta disarankan, atau set default time)
            $login_time = date('d M Y, H:i') . ' WIB'; 
            
            $metadata = json_encode([
                'time' => $login_time,
                'device' => $device_safe,
                'ip' => $ip_safe,
                'location' => $location_safe
            ]);

            $stmt_inbox_alert = $conn->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, template, metadata) VALUES (:username, :title, :message, 'System', 'NewLoginDetected', :metadata)");
            $stmt_inbox_alert->execute([
                'username' => $user['username'],
                'title' => $alert_title,
                'message' => 'Sistem mendeteksi login baru ke akun UCP Anda.',
                'metadata' => $metadata
            ]);
            // --- AKHIR PESAN LOGIN ALERT ---
        }
        
        // --- KIRIM EMAIL SELAMAT DATANG ---
        require_once __DIR__ . '/mailer_helper.php';
        if (!empty($user['email'])) {
            sendWelcomeEmail($user['email'], $user['username']);
        }

        // Kirim response sukses yang meniru payload auth.php supaya React bisa langsung auto-login
        // Jika discord_id kosong (pasti karena baru verify) maka kita kirim discord_required
        echo json_encode([
            'status' => 'discord_required', 
            'message' => 'Verifikasi Email Berhasil! Lanjut hubungkan Discord...',
            'username' => $user['username']
        ]);

    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Terjadi kesalahan sistem saat mencoba verifikasi OTP.']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid Action!']);
}
?>
