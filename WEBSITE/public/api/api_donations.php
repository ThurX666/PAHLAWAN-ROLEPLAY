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
    ucp_require_user();
    $data = get_sanitized_json();
    $username = ucp_require_username($data['username'] ?? null);
    $amount = intval($data['amount'] ?? 0);
    $itemId = $data['itemId'] ?? null;
    $characterId = (int)($data['characterId'] ?? 0);

    $catalog = [
        1 => ['name' => 'Ganti Nama (CN)', 'price' => 500, 'type' => 'Service', 'model' => 0],
        2 => ['name' => 'Ganti Nomor HP', 'price' => 200, 'type' => 'Service', 'model' => 0],
        3 => ['name' => 'Hapus Warning', 'price' => 1000, 'type' => 'Service', 'model' => 0],
        4 => ['name' => 'Custom Plate', 'price' => 300, 'type' => 'Service', 'model' => 0],
        5 => ['name' => 'Skin Eksklusif #299', 'price' => 350, 'type' => 'Skin', 'model' => 299],
        6 => ['name' => 'Bundle Skin Gang', 'price' => 100, 'type' => 'Service', 'model' => 0],
        7 => ['name' => 'Sultan (Polos)', 'price' => 1500, 'type' => 'Vehicle', 'model' => 560],
        8 => ['name' => 'NRG-500 (Polos)', 'price' => 2000, 'type' => 'Vehicle', 'model' => 522],
        9 => ['name' => 'Maverick', 'price' => 4500, 'type' => 'Vehicle', 'model' => 487],
        10 => ['name' => 'Jetmax', 'price' => 2500, 'type' => 'Vehicle', 'model' => 493],
        11 => ['name' => 'Bersihkan Record', 'price' => 250, 'type' => 'Service', 'model' => 0],
    ];

    $catalogItem = isset($catalog[(int)$itemId]) ? $catalog[(int)$itemId] : null;
    $customMapping = (int)$itemId === 12 && $amount > 0;
    
    if ($username && $characterId > 0 && ($catalogItem || $customMapping)) {
        if ($catalogItem && $amount !== $catalogItem['price']) {
            ucp_json_error('Harga item tidak sesuai katalog.', 422);
        }
        $pdo->beginTransaction();
        try {
            $ownerStmt = $pdo->prepare('SELECT Char_Name FROM player_characters WHERE pID = ? AND Char_UCP = ? FOR UPDATE');
            $ownerStmt->execute([$characterId, $username]);
            $characterName = $ownerStmt->fetchColumn();
            if (!$characterName) {
                throw new Exception('Karakter tujuan tidak valid.');
            }

            // Cek saldo
            $stmt = $pdo->prepare("SELECT gold FROM player_ucp WHERE UCP = ? FOR UPDATE");
            $stmt->execute([$username]);
            $acc = $stmt->fetch(PDO::FETCH_ASSOC);
            
            if ($acc && $acc['gold'] >= $amount) {
                // Item promo dinamis memakai ID database di luar katalog permanen.
                if (!$catalogItem && !$customMapping && $itemId) {
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

                $claimCode = strtoupper(bin2hex(random_bytes(8)));
                $itemName = $catalogItem['name'] ?? trim((string)($data['itemName'] ?? 'Custom Mapping'));
                $claimType = $catalogItem['type'] ?? 'Property';
                $itemModel = (int)($catalogItem['model'] ?? 0);
                $description = trim((string)($data['description'] ?? ''));
                $claimStatus = in_array($claimType, ['Vehicle', 'Skin'], true) || $itemName === 'Hapus Warning'
                    ? 'Pending'
                    : 'Manual';
                $claim = $pdo->prepare(
                    "INSERT INTO ucp_item_claims
                        (claim_code, username, character_id, claim_type, promo_item_id, item_name,
                         item_model, quantity, metadata, gold_cost, status)
                     VALUES (?, ?, ?, ?, ?, ?, ?, 1, ?, ?, ?)"
                );
                $claim->execute([
                    $claimCode,
                    $username,
                    $characterId,
                    $claimType,
                    $catalogItem ? null : $itemId,
                    $itemName,
                    $itemModel,
                    json_encode(['description' => $description, 'character_name' => $characterName]),
                    $amount,
                    $claimStatus,
                ]);

                $transaction = $pdo->prepare(
                    "INSERT INTO ucp_transactions
                        (account, player_name, sender_name, item_name, quantity, amount,
                         payment_method, proof_image, status, type)
                     VALUES (?, ?, ?, ?, 1, ?, 'Gold Coin', '', 'Success', 'redeem')"
                );
                $transaction->execute([$username, $characterName, $username, $itemName, $amount]);

                $inbox = $pdo->prepare(
                    "INSERT INTO ucp_inbox_messages
                        (username, title, message, type, is_read, voucher_code, item_name,
                         item_description, item_price, template, metadata)
                     VALUES (?, ?, ?, 'Voucher', 0, ?, ?, ?, ?, 'ItemClaimCreated', ?)"
                );
                $inbox->execute([
                    $username,
                    'Pembelian ' . $itemName . ' Berhasil',
                    $claimStatus === 'Pending'
                        ? 'Klaim akan diproses otomatis saat karakter tujuan login.'
                        : 'Klaim tercatat dan menunggu tindak lanjut admin.',
                    $claimCode,
                    $itemName,
                    $description,
                    $amount,
                    json_encode(['characterId' => $characterId, 'characterName' => $characterName, 'claimType' => $claimType]),
                ]);

                $pdo->commit();
                echo json_encode([
                    "status" => "success",
                    "new_gold" => $acc['gold'] - $amount,
                    "claim_code" => $claimCode,
                    "item_name" => $itemName,
                ]);
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
