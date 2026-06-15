<?php
// =========================================================================
// SECURITY FIREWALL & ANTI-FLOOD PROTECTON
// =========================================================================

// 1. HTTP Security Headers (XSS, Clickjacking, MIME Sniffing protection)
header("X-Content-Type-Options: nosniff");
header("X-Frame-Options: DENY");
header("X-XSS-Protection: 1; mode=block");
header("Strict-Transport-Security: max-age=31536000; includeSubDomains");
header("Content-Security-Policy: default-src 'self'; script-src 'self'; object-src 'none';");

// 2. Anti-DDoS / Rate Limiting (IP Based Tracking)
$ip = $_SERVER['REMOTE_ADDR'] ?? 'unknown';

if ($ip !== 'unknown' && $ip !== '::1' && $ip !== '127.0.0.1') {
    $cache_dir = __DIR__ . '/.rate_limit_cache/';
    if (!is_dir($cache_dir)) {
        @mkdir($cache_dir, 0755, true);
    }
    
    // Hash IP agar aman
    $limiter_file = $cache_dir . 'rate_' . md5($ip) . '.txt';
    $current_time = time();
    $allowed_requests = 45; // Maksimal 45 request
    $time_window = 10;      // ...per 10 detik

    if (file_exists($limiter_file)) {
        $data = explode('|', file_get_contents($limiter_file));
        if ($data[0] > $current_time - $time_window) {
            if ($data[1] >= $allowed_requests) {
                // Return 429 Too Many Requests jika terkena Flood
                http_response_code(429);
                echo json_encode([
                    "status" => "error", 
                    "message" => "Terlalu banyak request. Akses Anda ditahan sementara (Rate Limit/Anti-Flood).",
                    "code" => 429
                ]);
                exit;
            }
            $new_count = $data[1] + 1;
            file_put_contents($limiter_file, $data[0] . '|' . $new_count);
        } else {
            // Reset counter setelah waktu habis
            file_put_contents($limiter_file, $current_time . '|1');
        }
    } else {
        file_put_contents($limiter_file, $current_time . '|1');
    }
}

// 3. Global Input Sanitization (Proteksi XSS Dasar & Karakter Berbahaya)
function sanitize_global(&$array) {
    foreach ($array as $key => &$value) {
        if (is_array($value)) {
            sanitize_global($value);
        } else {
            // JANGAN menyentuh field password sama sekali! (Karena game server tidak melakukan hal ini)
            // Biarkan aslinya sebelum masuk ke algoritma BCRYPT hasher.
            if ($key === 'password' || $key === 'confirm' || $key === 'new_password' || $key === 'old_password') {
                $value = trim($value); // Cukup trim whitespace ujung
            }
            // Hilangkan tag HTML tersembunyi untuk input teks kecuali field yang dikhususkan
            else if ($key === 'story_text' || $key === 'content' || $key === 'html') {
                // Biarkan tag HTML dasar untuk Rich Text Editor, tetapi basmi tag berbahaya
                $safe_tags = '<b><i><u><strong><em><p><br><ul><li><ol><h1><h2><h3><h4><h5><h6><span><div><a><img><blockquote>';
                $clean_html = strip_tags($value, $safe_tags);
                // Basmi atribut on* event (onclick, onerror, dll) dan href="javascript:"
                $clean_html = preg_replace('#(<[^>]+?[\s\r\n\t])on[a-z]+\s*=\s*(["\']).*?\2([^>]*>)#i', '$1$3', $clean_html);
                $clean_html = preg_replace('#(<[^>]+?[\s\r\n\t])href\s*=\s*(["\'])\s*javascript:.*?\2([^>]*>)#i', '$1href="#"$3', $clean_html);
                $value = $clean_html;
            } else {
                $value = htmlspecialchars(strip_tags(trim($value)), ENT_QUOTES, 'UTF-8');
            }
        }
    }
}

// Eksekusi sanitasi ke SUPERGLOBAL POST dan GET
sanitize_global($_POST);
sanitize_global($_GET);

// 4. Secure Helper for JSON Requests
function get_sanitized_json() {
    $raw = file_get_contents('php://input');
    if (!$raw) return [];
    $decoded = json_decode($raw, true);
    if (is_array($decoded)) {
        sanitize_global($decoded);
        return $decoded;
    }
    return [];
}
?>
