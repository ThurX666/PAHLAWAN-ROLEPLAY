<?php
require_once __DIR__ . '/config.php';
// Masukkan konfigurasi database sentral

$action = isset($_POST['action']) ? $_POST['action'] : '';

if ($action === 'register') {
    $username = $_POST['username'] ?? '';
    $email = $_POST['email'] ?? '';
    $password = $_POST['password'] ?? '';

    // Validasi input kosong
    if (empty($username) || empty($email) || empty($password)) {
        echo json_encode(['status' => 'error', 'message' => 'Semua kolom wajib diisi!']);
        exit;
    }

    // Hash Password menggunakan metode BCRYPT
    // Kita gunakan BCRYPT dengan cost 12 agar identik 100% dan sangat kompatibel 
    // dengan plugin samp-bcrypt (https://github.com/Sreyas-Sreelal/samp-bcrypt)
    $hashed_password = password_hash($password, PASSWORD_BCRYPT, ['cost' => 12]);

    try {
        // Masukkan data ke dalam database
        $stmt_check = $conn->prepare("SELECT ID FROM player_ucp WHERE UCP = :username OR Email = :email");
        $stmt_check->execute(['username' => $username, 'email' => $email]);
        
        if ($stmt_check->rowCount() > 0) {
            echo json_encode(['status' => 'error', 'message' => 'Username atau Email sudah terdaftar!']);
            exit;
        }

        // GENERATE KODE OTP UNTUK VERIFIKASI (6 DIGIT ANGKA ACAK)
        $otp_code = sprintf("%06d", mt_rand(1, 999999));

        // Memasukkan input baru dengan "Verify_Status" = 0
        $stmt = $conn->prepare("INSERT INTO player_ucp (UCP, Email, Password, Verify_Status, Verify_Code, Register_Date) VALUES (:username, :email, :password, 0, :verify_token, CURRENT_TIMESTAMP)");
        $stmt->execute([
            'username' => $username,
            'email' => $email,
            'password' => $hashed_password,
            'verify_token' => $otp_code
        ]);

        // Panggil script pengirim Email OTP
        require_once 'mailer_helper.php';
        $email_sent = sendVerificationEmail($email, $username, $otp_code);

        if ($email_sent) {
            echo json_encode([
                'status' => 'success_verify', 
                'message' => 'Registrasi sukses! Cek Email Inbox/Spam Anda untuk kode verifikasi.',
                'registered_user' => $username
            ]);
        } else {
            echo json_encode([
                'status' => 'error', 
                'message' => 'Akun terdaftar, namun gagal mengirim email OTP. Hubungi Admin.'
            ]);
        }
    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Gagal mendaftar: Terjadi kesalahan pada server.']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid Action!']);
}
?>
