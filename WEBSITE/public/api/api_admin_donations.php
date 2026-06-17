<?php
require_once __DIR__ . '/config.php';

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) {
        $action = $data['action'];
    }
}

$restricted_actions = ['update_status', 'update_promo', 'add_item', 'toggle_item'];
$adminUser = null;
if ($action === 'get_donations' || in_array($action, $restricted_actions, true)) {
    $adminUser = ucp_require_admin(10);
}

if ($action === 'get_donations') {
    $stmt = $pdo->query("SELECT * FROM ucp_transactions ORDER BY created_at DESC");
    echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
    
} else if ($action === 'update_status') {
    $id = $_POST['id'] ?? null;
    $status = $_POST['status'] ?? null;
    
    if($id && $status) {
        $stmt = $pdo->prepare("UPDATE ucp_transactions SET status = ? WHERE id = ?");
        $stmt->execute([$status, $id]);
        
        // Log action (assuming admin_logs table exists from previous)
        try {
            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, ?, ?, ?)");
            $logStmt->execute([$adminUser['username'], 'UPDATE_TX_STATUS', $id, "Updated to $status"]);
            
            // Get transaction info for Inbox
            $txStmt = $pdo->prepare("SELECT account, item_name, amount FROM ucp_transactions WHERE id = ?");
            $txStmt->execute([$id]);
            $txRow = $txStmt->fetch(PDO::FETCH_ASSOC);
            
            if ($txRow) {
                $targetUser = $txRow['account'];
                $itemName = htmlspecialchars($txRow['item_name']);
                $amount = htmlspecialchars($txRow['amount']);
                $statusDisplay = $status === 'Success' ? 'Berhasil' : ($status === 'Rejected' ? 'Ditolak' : 'Menunggu');
                $statusColor = $status === 'Success' ? '#16a34a' : ($status === 'Rejected' ? '#ef4444' : '#eab308');
                
                $inboxTitle = "Status Donasi Diperbarui: {$statusDisplay}";
                
                $metadata = json_encode([
                    'transactionId' => '#DON-' . $id,
                    'itemName' => $itemName,
                    'amount' => $amount,
                    'status' => $statusDisplay
                ]);
                
                $inbStmt = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, '', 'System', 0, 'PaymentProcessed', ?)");
                $inbStmt->execute([$targetUser, $inboxTitle, $metadata]);
            }
        } catch(Exception $e) {}
        
        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => "ID or Status missing"]);
    }
    
} else if ($action === 'get_promo') {
    $stmt = $pdo->query("SELECT * FROM ucp_promo_config WHERE id = 1");
    echo json_encode($stmt->fetch(PDO::FETCH_ASSOC) ?: ["is_active" => 0, "title" => "", "description" => ""]);
    
} else if ($action === 'update_promo') {
    $data = get_sanitized_json();
    $isActive = isset($data['isActive']) ? ($data['isActive'] ? 1 : 0) : 0;
    $title = $data['title'] ?? '';
    $message = $data['description'] ?? '';
    $discount = isset($data['discountPercent']) ? intval($data['discountPercent']) : 0;
    
    $stmt = $pdo->prepare("UPDATE ucp_promo_config SET is_active = ?, title = ?, description = ?, discount_percent = ? WHERE id = 1");
    $stmt->execute([$isActive, $title, $message, $discount]);
    if ($stmt->rowCount() == 0) {
        $stmt = $pdo->prepare("INSERT IGNORE INTO ucp_promo_config (id, is_active, title, description, discount_percent) VALUES (1, ?, ?, ?, ?)");
        $stmt->execute([$isActive, $title, $message, $discount]);
    }
    echo json_encode(["status" => "success"]);
    
} else if ($action === 'get_items') {
    $stmt = $pdo->query("SELECT * FROM ucp_promo_items ORDER BY id DESC");
    echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
    
} else if ($action === 'add_item') {
    $name = $_POST['name'] ?? '';
    $type = $_POST['type'] ?? 'Item';
    $priceGold = $_POST['priceGold'] ?? 0;
    $desc = $_POST['description'] ?? '';
    $qty = $_POST['qty'] ?? 0;
    $imagePath = '';
    
    if (isset($_FILES['image']) && $_FILES['image']['error'] === UPLOAD_ERR_OK) {
        $uploadDir = '../uploads/items/';
        if (!is_dir($uploadDir)) mkdir($uploadDir, 0777, true);
        $fileName = time() . '_' . basename($_FILES['image']['name']);
        if (move_uploaded_file($_FILES['image']['tmp_name'], $uploadDir . $fileName)) {
            $imagePath = $fileName;
        }
    }
    
    $stmt = $pdo->prepare("INSERT INTO ucp_promo_items (name, type, price_gold, description, qty, is_active, image_path) VALUES (?, ?, ?, ?, ?, 1, ?)");
    if ($stmt->execute([$name, $type, $priceGold, $desc, $qty, $imagePath])) {
        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Failed to insert Data"]);
    }
    
} else if ($action === 'toggle_item') {
    $data = get_sanitized_json();
    $id = $data['item_id'] ?? null;
    $isActive = isset($data['is_active']) ? ($data['is_active'] ? 1 : 0) : null;
    
    if ($id !== null && $isActive !== null) {
        $stmt = $pdo->prepare("UPDATE ucp_promo_items SET is_active = ? WHERE id = ?");
        $stmt->execute([$isActive, $id]);
        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Invalid parameters"]);
    }
    
} else {
    echo json_encode(["status" => "error", "message" => "Unknown action"]);
}
?>
