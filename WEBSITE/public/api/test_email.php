<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/mailer_helper.php';
ucp_require_admin(10);

echo "Memulai pengetesan email...<br>";

// Buat OTP dummy
$otp_code = "123456";
$test_email = $smtp_user; // Kirim ke email sendiri yang ada di config

echo "Mencoba mengirim email diagnostik.<br>";

$result = sendVerificationEmail($test_email, "TestUser", $otp_code);

if ($result) {
    echo "<b style='color:green;'>SUKSES!</b> Email berhasil terkirim. Cek inbox/spam.";
} else {
    echo "<b style='color:red;'>GAGAL!</b> Periksa kredensial SMTP di config.php atau pastikan folder PHPMailer sudah benar.";
}
?>
