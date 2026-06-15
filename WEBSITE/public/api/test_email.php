<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/mailer_helper.php';

echo "Memulai pengetesan email...<br>";

// Buat OTP dummy
$otp_code = "123456";
$test_email = $smtp_user; // Kirim ke email sendiri yang ada di config

echo "Mencoba mengirim ke: $test_email <br>";

$result = sendVerificationEmail($test_email, "TestUser", $otp_code);

if ($result) {
    echo "<b style='color:green;'>SUKSES!</b> Email berhasil terkirim ke $test_email. Cek inbox/spam.";
} else {
    echo "<b style='color:red;'>GAGAL!</b> Periksa kredensial SMTP di config.php atau pastikan folder PHPMailer sudah benar.";
}
?>
