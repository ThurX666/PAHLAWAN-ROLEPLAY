<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/mailer_helper.php';

$action = isset($_POST['action']) ? $_POST['action'] : '';

if ($action === 'forgot_password') {
    $email = $_POST['email'] ?? '';

    if (empty($email)) {
        echo json_encode(['status' => 'error', 'message' => 'Alamat email wajib diisi!']);
        exit;
    }

    try {
        // Cek apakah email terdaftar
        $stmt = $conn->prepare("SELECT ID as id, UCP as username, Verify_Status as is_verified FROM player_ucp WHERE Email = :email LIMIT 1");
        $stmt->execute(['email' => $email]);
        $user = $stmt->fetch(PDO::FETCH_ASSOC);

        if (!$user) {
            // Jika email tidak terdaftar, tampilkan pesan gagal
            echo json_encode(['status' => 'error', 'message' => 'Email tersebut belum terdaftar dalam sistem kami.']);
            exit;
        }

        // Generate OTP
        $otpCode = sprintf("%06d", mt_rand(1, 999999));
        $reset_expires = date('Y-m-d H:i:s', strtotime('+30 minutes'));

        $update = $conn->prepare("UPDATE player_ucp SET reset_token = :token, reset_expires = :expires WHERE ID = :id");
        $update->execute([
            'token' => $otpCode,
            'expires' => $reset_expires,
            'id' => $user['id']
        ]);

        if (isLocalOtpPreviewMode()) {
            echo json_encode([
                'status' => 'success',
                'message' => 'Local-only OTP preview is enabled. This preview is disabled in production.',
                'local_preview' => localOtpPreviewPayload($otpCode, 'forgot_password'),
            ]);
            exit;
        }

        $emailSent = sendForgotPasswordEmail($email, $user['username'], $otpCode);

        if ($emailSent) {
            echo json_encode([
                'status' => 'success', 
                'message' => 'Kode OTP untuk reset kata sandi telah dikirim ke email Anda.'
            ]);
        } else {
            echo json_encode([
                'status' => 'error',
                'message' => sharedMailFailureClientMessage('Gagal mengirim email OTP. Silakan coba lagi.')
            ]);
        }

    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Terjadi kesalahan sistem.']);
    }
} elseif ($action === 'reset_password') {
    $email = $_POST['email'] ?? '';
    $otp = $_POST['otp'] ?? '';
    $new_password = $_POST['new_password'] ?? '';

    if (empty($email) || empty($otp) || empty($new_password)) {
        echo json_encode(['status' => 'error', 'message' => 'Harap isi semua kolom!']);
        exit;
    }

    try {
        $stmt = $conn->prepare("SELECT ID as id, reset_token, reset_expires FROM player_ucp WHERE Email = :email LIMIT 1");
        $stmt->execute(['email' => $email]);
        $user = $stmt->fetch(PDO::FETCH_ASSOC);

        if (!$user) {
            echo json_encode(['status' => 'error', 'message' => 'Pengguna tidak ditemukan.']);
            exit;
        }

        if ($user['reset_token'] !== $otp) {
            echo json_encode(['status' => 'error', 'message' => 'Kode OTP salah.']);
            exit;
        }

        if (strtotime($user['reset_expires']) < time()) {
            echo json_encode(['status' => 'error', 'message' => 'Kode OTP telah kedaluwarsa.']);
            exit;
        }

        $hashed_password = password_hash($new_password, PASSWORD_BCRYPT);

        $update = $conn->prepare("UPDATE player_ucp SET Password = :password, reset_token = NULL, reset_expires = NULL WHERE ID = :id");
        $update->execute([
            'password' => $hashed_password,
            'id' => $user['id']
        ]);

        $resetSuccessMailSent = sendPasswordResetSuccessEmail($email, $user['username'] ?? 'Player');
        if (!$resetSuccessMailSent && hasMailFailureCategory()) {
            error_log('Password reset success mail skipped [' . lastMailFailureCategory() . '].');
        }

        echo json_encode(['status' => 'success', 'message' => 'Kata sandi berhasil diubah! Silakan masuk dengan sandi baru Anda.']);

    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Terjadi kesalahan sistem.']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid Action!']);
}
?>
