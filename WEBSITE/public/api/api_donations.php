<?php
require_once __DIR__ . '/config.php';

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) {
        $action = $data['action'];
    } else {
        $action = '';
    }
}

if ($action === 'get_transactions') {
    $username = ucp_require_username($_GET['username'] ?? null);
    
    if($username) {
        $stmt = $pdo->prepare("SELECT * FROM ucp_transactions WHERE account = ? ORDER BY created_at DESC");
        $stmt->execute([$username]);
        echo json_encode(["status" => "success", "data" => $stmt->fetchAll(PDO::FETCH_ASSOC)]);
    } else {
        echo json_encode(["status" => "error", "message" => "Missing username"]);
    }
    
} else if ($action === 'add_transaction') {
    $sessionUser = ucp_require_user();
    $data = get_sanitized_json();
    
    $account = ucp_require_username($data['account'] ?? null);
    $senderName = $data['senderName'] ?? '';
    $item = $data['item'] ?? '';
    $type = $data['type'] ?? 'donation';
    $quantity = $data['quantity'] ?? 1;
    $amount = $data['amount'] ?? 0;
    $method = $data['method'] ?? '';
    $proofImage = $data['proofImage'] ?? '';
    
    if ($account && $item) {
        $stmt = $pdo->prepare("INSERT INTO ucp_transactions (account, player_name, sender_name, item_name, quantity, amount, payment_method, proof_image, status, type) VALUES (?, ?, ?, ?, ?, ?, ?, ?, 'Pending', ?)");
        $stmt->execute([$account, $account, $senderName, $item, $quantity, $amount, $method, $proofImage, $type]);
        
        $newId = $pdo->lastInsertId();
        echo json_encode(["status" => "success", "transaction_id" => "INV-" . $newId]);
    } else {
        echo json_encode(["status" => "error", "message" => "Invalid parameters"]);
    }
} else if ($action === 'deduct_gold') {
    $sessionUser = ucp_require_user();
    $data = get_sanitized_json();
    $username = ucp_require_username($data['username'] ?? null);
    $amount = intval($data['amount'] ?? 0);
    $itemId = $data['itemId'] ?? null;
    
    if ($username && $amount > 0) {
        $pdo->beginTransaction();
        try {
            // Cek saldo
            $stmt = $pdo->prepare("SELECT gold FROM player_ucp WHERE UCP = ? FOR UPDATE");
            $stmt->execute([$username]);
            $acc = $stmt->fetch(PDO::FETCH_ASSOC);
            
            if ($acc && $acc['gold'] >= $amount) {
                // If it's an item purchase, deduct stock
                if ($itemId) {
                    $itemStmt = $pdo->prepare("SELECT qty FROM ucp_promo_items WHERE id = ? FOR UPDATE");
                    $itemStmt->execute([$itemId]);
                    $item = $itemStmt->fetch(PDO::FETCH_ASSOC);
                    if ($item && $item['qty'] > 0) {
                        $updItem = $pdo->prepare("UPDATE ucp_promo_items SET qty = qty - 1 WHERE id = ?");
                        $updItem->execute([$itemId]);
                    } else if ($item && $item['qty'] <= 0) {
                        throw new Exception("Item promo stok habis.");
                    }
                }
                
                $upd = $pdo->prepare("UPDATE player_ucp SET gold = gold - ? WHERE UCP = ?");
                $upd->execute([$amount, $username]);
                $pdo->commit();
                echo json_encode(["status" => "success", "new_gold" => $acc['gold'] - $amount]);
            } else {
                $pdo->rollBack();
                echo json_encode(["status" => "error", "message" => "Saldo Gold tidak mencukupi"]);
            }
        } catch (Exception $e) {
            $pdo->rollBack();
            echo json_encode(["status" => "error", "message" => $e->getMessage()]);
        }
    } else {
        echo json_encode(["status" => "error", "message" => "Invalid parameters"]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Unknown action"]);
}
?>
