<?php
// Script testing SA-MP Query
require_once __DIR__ . '/config.php';
ucp_require_admin(10);
header('Content-Type: text/html');

$ip = $samp_server_ip;
$port = $samp_server_port;

echo "<h3>Testing SA-MP UDP Query</h3>";
echo "Mencoba query ke ping <b>$ip:$port</b>...<br><br>";

$fp = @fsockopen("udp://$ip", $port, $errno, $errstr, 2);
if (!$fp) {
    die("Koneksi gagal (fsockopen error): $errno - $errstr");
}

stream_set_timeout($fp, 2);

$packet = "SAMP";
$ipParts = explode(".", $ip);
if (count($ipParts) !== 4) $ipParts = [127, 0, 0, 1];
foreach ($ipParts as $part) {
    $packet .= chr((int)$part);
}
$packet .= chr($port & 0xFF);
$packet .= chr($port >> 8 & 0xFF);
$packet .= 'i'; // Opcode 'i' for Information

fwrite($fp, $packet);
$response = fread($fp, 2048);
fclose($fp);

if (!$response) {
    echo "<span style='color:red; font-weight:bold;'>ERROR: Tidak ada respon dari server UDP.</span><br><br>";
    echo "<b>Kemungkinan penyebab (kalau run di XAMPP lokal):</b><br>";
    echo "1. Server SA-MP.exe belum dijalankan di komputer kamu.<br>";
    echo "2. Port di server.cfg SA-MP kamu bukan $port.<br>";
    echo "3. Di file <b>server.cfg</b> SA-MP kamu, settingan query dimatiin. Coba buka server.cfg dan pastikan ada tulisan <b>query 1</b> (bukan query 0).<br>";
    echo "4. Fitur UDP fsockopen keblock sama Firewall Windows. Buka Windows Defender Firewall, allow port 7777 atau allow server-samp.exe & xampp apache.<br>";
} else {
    echo "<span style='color:green; font-weight:bold;'>SUCCESS: Berhasil dapat respon dari server SA-MP!</span><br><br>";
    echo "Panjang respons: " . strlen($response) . " bytes.<br>";
    
    if (strlen($response) >= 11 && substr($response, 0, 4) === "SAMP") {
        $offset = 11;
        $passworded = ord($response[$offset]); $offset += 1;
        $players = ord($response[$offset]) | (ord($response[$offset+1]) << 8); $offset += 2;
        $max_players = ord($response[$offset]) | (ord($response[$offset+1]) << 8); $offset += 2;
        
        $hostnameLen = ord($response[$offset]) | (ord($response[$offset+1]) << 8) | (ord($response[$offset+2]) << 16) | (ord($response[$offset+3]) << 24); $offset += 4;
        $hostname = mb_convert_encoding(substr($response, $offset, $hostnameLen), "UTF-8", "auto"); $offset += $hostnameLen;
        
        echo "<br><b>Data Parsed:</b><br>";
        echo "- Hostname: " . htmlspecialchars($hostname) . "<br>";
        echo "- Players: $players / $max_players<br>";
        echo "- Passworded: " . ($passworded ? "Yes" : "No") . "<br>";
    } else {
        echo "Respon tidak sesuai format SA-MP. Data: " . htmlspecialchars($response);
    }
}
?>
