<?php
// cron_activity.php
// File ini dirancang untuk dijalankan melalui Cron Job setiap 1 menit:
// * * * * * php /path/to/public/api/cron_activity.php
//
// Sistem ini akan mengecek jumlah pemain setiap menit. Jika jumlah pemain 
// saat ini lebih tinggi dari rekor tertinggi pada jam berjalan, maka nilai 
// di tabel akan diperbarui (menyimpan nilai tertinggi / peak player per jam).

require_once __DIR__ . '/config.php';
require_once __DIR__ . '/SampQuery.php';

try {
    // Ambil info dari server menggunakan UDP Query
    $query = new SampQuery($samp_server_ip, $samp_server_port);
    $server_data = $query->getInfo();

    if ($server_data !== false) {
        $players_online = (int)$server_data['players'];

        // Cek apakah sudah ada data untuk jam ini (misal: hari ini jam 15:xx)
        $stmt_check = $pdo->query("SELECT `id`, `players_online` FROM `ucp_server_activity` WHERE DATE(logged_at) = CURDATE() AND HOUR(logged_at) = HOUR(NOW()) LIMIT 1");
        $row = $stmt_check->fetch(PDO::FETCH_ASSOC);

        if ($row) {
            // Data sudah ada untuk jam ini, cek apakah player saat ini lebih banyak
            $peak_players = (int)$row['players_online'];
            if ($players_online > $peak_players) {
                // Update nilai tertinggi
                $stmt_update = $pdo->prepare("UPDATE `ucp_server_activity` SET `players_online` = :players WHERE `id` = :id");
                $stmt_update->execute([':players' => $players_online, ':id' => $row['id']]);
                echo "Berhasil: Nilai tertinggi diperbarui menjadi " . $players_online . " pemain pada jam ini.\n";
            } else {
                echo "Info: Jumlah pemain saat ini (" . $players_online . ") tidak melebihi record tertinggi jam ini (" . $peak_players . "). Tidak ada update.\n";
            }
        } else {
            // Belum ada data untuk jam ini (pergantian jam baru), insert data baru
            // Anda bisa mengatur format waktunya agar tepat menit 00 atau membiarkan NOW()
            $stmt_insert = $pdo->prepare("INSERT INTO `ucp_server_activity` (`players_online`, `logged_at`) VALUES (:players, NOW())");
            $stmt_insert->execute([':players' => $players_online]);
            echo "Berhasil: Data jam baru ditambahkan. Jumlah awal: " . $players_online . " pemain.\n";
        }
    } else {
        echo "Error: Tidak bisa mengambil informasi server. Server mungkin sedang offline.\n";
    }
} catch (Exception $e) {
    echo "Error: Terjadi kesalahan database atau sistem - " . $e->getMessage() . "\n";
}
?>
