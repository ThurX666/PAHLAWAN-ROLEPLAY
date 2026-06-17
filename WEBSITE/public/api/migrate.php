<?php
require_once __DIR__ . '/config.php';
ucp_require_admin(10);

$report = phrp_integrate_database($conn, true);

echo json_encode([
    'status' => $report['status'] ?? 'success',
    'message' => 'Migration complete',
    'integration' => $report,
], JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);
