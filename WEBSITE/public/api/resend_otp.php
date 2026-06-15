<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/mailer_helper.php';

$action = isset($_POST['action']) ? $_POST['action'] : '';

if ($action === 'resend_otp') {
    $email_or_username = $_POST['username'] ?? '';

    if (empty($email_or_username)) {
        echo json_encode(['status' => 'error', 'message' => 'Email atau Username tidak valid!']);
        exit;
    }

    try {
        // Cek apakah akun ada dan kondisinya BELUM verifikasi
        $stmt_check = $conn->prepare("SELECT ID, UCP, Email, Verify_Status, Verify_Code, Register_Date, OTP_Attempts FROM player_ucp WHERE UCP = :username OR Email = :email LIMIT 1");
        $stmt_check->execute(['username' => $email_or_username, 'email' => $email_or_username]);
        $user = $stmt_check->fetch(PDO::FETCH_ASSOC);

        if (!$user) {
            echo json_encode(['status' => 'error', 'message' => 'Akun tidak ditemukan.']);
            exit;
        }

        if ((int)$user['Verify_Status'] === 1) {
            echo json_encode(['status' => 'error', 'message' => 'Akun ini sudah diverifikasi, silakan langsung login.']);
            exit;
        }

        // ANTI-SPAM: Cek waktu terakhir minta OTP
        if (!empty($user['Register_Date'])) {
            $last_request = strtotime($user['Register_Date']);
            if (time() - $last_request < 1800) {
                $remaining = max(0, 1800 - (time() - $last_request));
                echo json_encode(['status' => 'error', 'message' => 'Tunggu 30 menit sebelum mengirim ulang OTP!', 'cooldown' => $remaining]);
                exit;
            }
        }

        // CEK LIMIT 3X ATTEMPTS
        $attempts = (int)($user['OTP_Attempts'] ?? 0);
        if ($attempts >= 3) {
            echo json_encode(['status' => 'error', 'message' => 'Batas pengiriman Email OTP tercapai (3/3). Tunggu Admin untuk mereset akun Anda.']);
            exit;
        }

        // GENERATE KODE OTP BARU (SETIAP KIRIM ULANG WAJIB BARU, SEKALIGUS MERESET KODE LAMA)
        $new_otp_code = sprintf("%06d", mt_rand(1, 999999));

        // Update verify code dan waku register/request ke database (Ini juga mereset masa EXPIRED otp jadi 30 menit lagi, dan tambah attempt)
        $stmt_update = $conn->prepare("UPDATE player_ucp SET Verify_Code = :new_token, Register_Date = CURRENT_TIMESTAMP, OTP_Attempts = OTP_Attempts + 1 WHERE ID = :id");
        $stmt_update->execute([
            'new_token' => $new_otp_code,
            'id' => $user['ID']
        ]);

        // Triger pengiriman Email dengan teks Resend
        $email_sent = sendVerificationEmail($user['Email'], $user['UCP'], $new_otp_code, 'resend');

        if ($email_sent) {
            echo json_encode([
                'status' => 'success', 
                'message' => 'Kode OTP baru telah berhasil dikirim ulang ke email ' . $user['Email']
            ]);
        } else {
            echo json_encode([
                'status' => 'error', 
                'message' => 'Gagal mengirim email OTP dari server. Hubungi Admin.'
            ]);
        }

    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Terjadi kesalahan sistem saat mencoba mengirim ulang OTP.']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid Action!']);
}
?>
