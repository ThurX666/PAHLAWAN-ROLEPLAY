<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $username = $_GET['username'] ?? '';
    if (!$username) {
        echo json_encode(['status' => 'error', 'message' => 'Username required']);
        exit;
    }

    $stmt = $pdo->prepare("SELECT * FROM ucp_inbox_messages WHERE username = ? ORDER BY created_at DESC, id DESC");
    $stmt->execute([$username]);
    $results = $stmt->fetchAll(PDO::FETCH_ASSOC);

    $messages = [];
    foreach ($results as $row) {
        $messages[] = [
            'id' => (string)$row['id'],
            'title' => $row['title'],
            'message' => $row['message'],
            'type' => $row['type'],
            'date' => $row['created_at'],
            'read' => (bool)$row['is_read'],
            'code' => $row['voucher_code'] ?: null,
            'itemName' => $row['item_name'] ?: null,
            'itemDescription' => $row['item_description'] ?: null,
            'itemPrice' => $row['item_price'] ? (int)$row['item_price'] : null,
            'template' => $row['template'] ?: null,
            'metadata' => $row['metadata'] ? json_decode($row['metadata'], true) : null,
        ];
    }

    echo json_encode(['status' => 'success', 'data' => $messages]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'PUT') {
    $data = get_sanitized_json();
    $messageId = $data['message_id'] ?? '';
    
    if ($messageId) {
        $stmt = $pdo->prepare("UPDATE ucp_inbox_messages SET is_read = 1 WHERE id = ?");
        $stmt->execute([$messageId]);
        echo json_encode(['status' => 'success']);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Message ID required']);
    }
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = get_sanitized_json();
    $action = $data['action'] ?? '';

    if ($action === 'broadcast_message' || $action === 'send_message') {
        $username = $data['username'] ?? '';
        $title = $data['title'] ?? '';
        $message = $data['message'] ?? '';
        $type = $data['type'] ?? 'System';
        $voucherCode = $data['code'] ?? null;
        $itemName = $data['itemName'] ?? null;
        $itemDescription = $data['itemDescription'] ?? null;
        $itemPrice = $data['itemPrice'] ?? null;
        $template = $data['template'] ?? null;
        $metadata = isset($data['metadata']) ? json_encode($data['metadata']) : null;

        if (empty($title)) {
             echo json_encode(['status' => 'error', 'message' => 'Title is required']);
             exit;
        }

        if ($action === 'send_message') {
             if (empty($username)) {
                 echo json_encode(['status' => 'error', 'message' => 'Username is required']);
                 exit;
             }
             $stmt = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, voucher_code, item_name, item_description, item_price, template, metadata) VALUES (?, ?, ?, ?, 0, ?, ?, ?, ?, ?, ?)");
             $stmt->execute([$username, $title, $message, $type, $voucherCode, $itemName, $itemDescription, $itemPrice, $template, $metadata]);
             
             $newId = $pdo->lastInsertId();
             echo json_encode(['status' => 'success', 'id' => $newId]);
             exit;
        } else {
             // Broadcast: insert for all distinct users in player_ucp table
             $stmtUsers = $pdo->query("SELECT UCP as username FROM player_ucp");
             $users = $stmtUsers->fetchAll(PDO::FETCH_ASSOC);
             
             $pdo->beginTransaction();
             try {
                 $stmt = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, voucher_code, item_name, item_description, item_price, template, metadata) VALUES (?, ?, ?, ?, 0, ?, ?, ?, ?, ?, ?)");
                 foreach ($users as $u) {
                     $stmt->execute([$u['username'], $title, $message, $type, $voucherCode, $itemName, $itemDescription, $itemPrice, $template, $metadata]);
                 }
                 $pdo->commit();
                 echo json_encode(['status' => 'success', 'broadcast_count' => count($users)]);
             } catch (Exception $e) {
                 $pdo->rollBack();
                 echo json_encode(['status' => 'error', 'message' => 'Broadcast failed: ' . $e->getMessage()]);
             }
             exit;
        }
    }
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
