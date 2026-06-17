<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $user = ucp_current_user();
    if ($user === null) {
        ucp_json_error('Tidak ada sesi aktif.', 401);
    }

    echo json_encode([
        'status' => 'success',
        'data' => [
            'username' => $user['username'],
            'admin_level' => (int)$user['admin_level'],
        ],
    ]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = get_sanitized_json();
    if (($data['action'] ?? '') !== 'logout') {
        ucp_json_error('Aksi tidak valid.');
    }

    ucp_destroy_session();
    echo json_encode(['status' => 'success']);
    exit;
}

ucp_json_error('Metode tidak valid.', 405);
