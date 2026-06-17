<?php
require_once __DIR__ . '/config.php';
ucp_require_admin(10);

$force = isset($_GET['force']) && $_GET['force'] === '1';
$report = phrp_integrate_database($conn, $force);

echo json_encode([
    'status' => $report['status'] ?? 'success',
    'integration' => $report,
    'health' => phrp_database_status($conn),
], JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);
