<?php
require_once __DIR__ . '/config.php';
// Masukkan konfigurasi database sentral

// Cek apakah ada POST data
$action = isset($_POST['action']) ? $_POST['action'] : '';

if ($action === 'login') {
    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';
    $device = $_POST['device'] ?? 'Unknown Device';
    $ip = $_POST['ip'] ?? ($_SERVER['REMOTE_ADDR'] === '::1' ? '127.0.0.1' : $_SERVER['REMOTE_ADDR']);
    $location = $_POST['location'] ?? 'Unknown Location';

    // Cari user di database
    $stmt = $conn->prepare("SELECT 
        ID as id, 
        UCP as username, 
        Email as email, 
        Password as password, 
        Verify_Status as is_verified,
        Verify_Code, 
        Register_Date,
        Last_Login,
        OTP_Attempts,
        admin_level, 
        vip_status, 
        gold,
        last_device,
        last_ip,
        last_location,
        discord_id
        FROM player_ucp WHERE UCP = :username OR Email = :username LIMIT 1");
    $stmt->bindParam(':username', $username);
    $stmt->execute();
    
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    // KETAT: Periksa Password
    if ($user && password_verify($password, $user['password'])) {
        
        $reason_title = 'reauth';
        $reason_msg = 'Sesi perangkat Anda memudar atau IP Anda dicurigai. Demi keamanan sistem, memohon verifikasi OTP Email ulang.';

        // 1. SISTEM 2FA RE-VERIFIKASI (Jika User Terakhir Login > 7 Hari / Cookie Habis panjang ATAU Perangkat/IP beda)
        if (isset($user['is_verified']) && (int)$user['is_verified'] === 1) {
            $require_reauth = false;
            
            // Cek IP dan Perangkat
            if (!empty($user['last_device']) && $user['last_device'] !== $device) {
                $require_reauth = true;
                $reason_title = 'new_device';
                $reason_msg = 'Sistem mendeteksi login dari Perangkat Baru (' . $device . '). Demi keamanan, silakan masukkan OTP yang dikirim ke Email Anda.';
            } else if (!empty($user['last_ip']) && $user['last_ip'] !== $ip) {
                $require_reauth = true;
                $reason_title = 'new_ip';
                $reason_msg = 'Sistem mendeteksi login dari Lokasi Berbeda (' . $location . '). Demi keamanan, silakan masukkan OTP yang dikirim ke Email Anda.';
            }

            // Cek waktu
            if (!$require_reauth) {
                if (!empty($user['Last_Login'])) {
                    $last_login_time = strtotime($user['Last_Login']);
                    if ((time() - $last_login_time) >= (1 * 86400)) { // 1 Hari (Wajib verifikasi sehari sekali)
                        $require_reauth = true;
                    }
                } else {
                    $require_reauth = true; // Jika null (belum pernah login di web)
                }
            }

            if ($require_reauth) {
                // RESET Attempts
                $new_otp_code = sprintf("%06d", mt_rand(1, 999999));
                
                // Downgrade status ke 0 (kunci sementara) agar dia masuk form Verifikasi
                $stmt_update = $conn->prepare("UPDATE player_ucp SET Verify_Status = 0, Verify_Code = :new_token, Register_Date = CURRENT_TIMESTAMP, OTP_Attempts = 1 WHERE ID = :id");
                $stmt_update->execute(['new_token' => $new_otp_code, 'id' => $user['id']]);

                require_once __DIR__ . '/mailer_helper.php';

                if (isLocalOtpPreviewMode()) {
                    echo json_encode([
                        'status' => 'unverified',
                        'message' => $reason_msg,
                        'registered_user' => $user['email'],
                        'cooldown' => 1800,
                        'local_preview' => localOtpPreviewPayload($new_otp_code, $reason_title),
                    ]);
                    exit;
                }

                $email_sent = sendVerificationEmail($user['email'], $user['username'], $new_otp_code, $reason_title, $device, $location);

                if (!$email_sent && isLocalDevEnvironment() && localMailMode() === 'error') {
                    echo json_encode([
                        'status' => 'error',
                        'message' => localMailTroubleshootingMessage(),
                    ]);
                    exit;
                }

                echo json_encode([
                    'status' => 'unverified', 
                    'message' => $reason_msg,
                    'registered_user' => $user['email'],
                    'cooldown' => 1800
                ]);
                exit;
            }
        }

        // 2. Cek Apakah is_verified sudah 0 (Proses normal Daftar Baru)
        if (isset($user['is_verified']) && (int)$user['is_verified'] === 0) {
            
            // LOGIC BARU: Coba Auto-Send saat mereka klik Register
            // Kita juga tetep jaga dari serangan brutal dengan filter 3 Menit
            require_once __DIR__ . '/mailer_helper.php';
            
            $msg_to_client = 'Akun belum aktif! Anda harus melakukan verifikasi email terlebih dahulu.';
            $cooldown_remaining = 0;
            $local_preview = null;
            
            if (!empty($user['Register_Date'])) {
                $last_request = strtotime($user['Register_Date']);
                $time_passed = time() - $last_request;

                if ($time_passed < 1800) {
                    $cooldown_remaining = max(0, 1800 - $time_passed);
                    if (isLocalOtpPreviewMode()) {
                        $local_preview = localOtpPreviewPayload($user['Verify_Code'] ?? '', 'existing_unverified');
                    }
                } else {
                    // Cek limit OTP Attempts
                    $attempts = (int)($user['OTP_Attempts'] ?? 0);
                    if ($attempts >= 3) {
                        $msg_to_client = 'Batas pengiriman Email OTP tercapai (3/3). Tunggu Admin untuk mereset akun Anda atau hubungi support.';
                    } else {
                        // Kalo udah lebih dari 3 menit, generate KODE BARU!
                        $new_otp_code = sprintf("%06d", mt_rand(1, 999999));
                        
                        // Update ke database (Kode baru, Reset Date, Tambah Attempt)
                        $stmt_update = $conn->prepare("UPDATE player_ucp SET Verify_Code = :new_token, Register_Date = CURRENT_TIMESTAMP, OTP_Attempts = OTP_Attempts + 1 WHERE ID = :id");
                        $stmt_update->execute(['new_token' => $new_otp_code, 'id' => $user['id']]);

                        if (isLocalOtpPreviewMode()) {
                            $local_preview = localOtpPreviewPayload($new_otp_code, 'resend');
                        } else {
                        // Nembak Email Langsung
                            $email_sent = sendVerificationEmail($user['email'], $user['username'], $new_otp_code, 'resend');

                            if (!$email_sent && isLocalDevEnvironment() && localMailMode() === 'error') {
                                echo json_encode([
                                    'status' => 'error',
                                    'message' => localMailTroubleshootingMessage(),
                                ]);
                                exit;
                            }
                        }
                        
                        $msg_to_client = 'Akun belum terverifikasi! Sistem baru saja MENGIRIM KODE OTP BARU secara otomatis ke Email Anda.';
                        $cooldown_remaining = 1800;
                    }
                }
            }

            echo json_encode([
                'status' => 'unverified', 
                'message' => $msg_to_client,
                'registered_user' => $user['email'], // Mengembalikan email saja agar frontend bisa pass ke VerifyForm
                'cooldown' => $cooldown_remaining,
                'local_preview' => $local_preview,
            ]);
            exit;
        }

        // Update Device, IP, Location
        $update = $conn->prepare("UPDATE player_ucp SET last_device = :device, last_ip = :ip, last_location = :location WHERE ID = :id");
        $update->execute([
            'device' => $device,
            'ip' => $ip,
            'location' => $location,
            'id' => $user['id']
        ]);

        if (empty($user['discord_id'])) {
            ucp_create_pending_session($user);
            echo json_encode([
                'status' => 'discord_required',
                'message' => 'Anda harus menghubungkan akun Discord sebelum dapat mengakses dashboard.',
                'username' => $user['username']
            ]);
            exit;
        }

        // Kirim response sukses ke React
        ucp_create_session($user);
        echo json_encode([
            'status' => 'success',
            'message' => 'Login berhasil',
            'username' => $user['username'],
            'admin_level' => (int)($user['admin_level'] ?? 0),
            'vip_status' => $user['vip_status'] ?? 'None',
            'gold' => (int)($user['gold'] ?? 0)
        ]);
        
    } else {
        echo json_encode([
            'status' => 'error', 
            'message' => 'Username atau Password salah!'
        ]);
    }
} else {
    echo json_encode([
        'status' => 'error', 
        'message' => 'Invalid Action!'
    ]);
}
?>
