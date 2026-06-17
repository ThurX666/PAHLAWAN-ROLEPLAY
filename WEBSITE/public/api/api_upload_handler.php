<?php
require_once __DIR__ . '/config.php';

$action = $_POST['action'] ?? null;
$sessionUser = ucp_require_user();

if ($action === 'upload_photo') {
    $charName = preg_replace('/[^a-zA-Z0-9_]/', '', $_POST['characterName'] ?? 'unknown');
    
    if (isset($_FILES['photo']) && $_FILES['photo']['error'] === UPLOAD_ERR_OK) {
        $ext = strtolower(pathinfo($_FILES['photo']['name'], PATHINFO_EXTENSION));
        $allowed = ['jpg', 'jpeg', 'png', 'webp'];
        
        // Proteksi Tambahan: Verifikasi MIME type
        $finfo = finfo_open(FILEINFO_MIME_TYPE);
        $mime = finfo_file($finfo, $_FILES['photo']['tmp_name']);
        finfo_close($finfo);
        $allowed_mimes = ['image/jpeg', 'image/png', 'image/webp'];
        
        if (in_array($ext, $allowed) && in_array($mime, $allowed_mimes)) {
            $newName = $charName . '_' . time() . '.' . $ext;
            $uploadDir = '../uploads/characters/';
            
            if (!is_dir($uploadDir)) mkdir($uploadDir, 0777, true);
            
            if (move_uploaded_file($_FILES['photo']['tmp_name'], $uploadDir . $newName)) {
                
                // Update the photo_url in characters using the characterName if requested
                // Note: It's safer to pass char_id, but we'll use name here based on the payload pattern
                $savedPath = "uploads/characters/" . $newName;
                try {
                    $stmtUpdate = $pdo->prepare("
                        UPDATE ucp_character_stories cs
                        JOIN player_characters c ON c.pID = cs.character_id
                        SET cs.photo_url = ?
                        WHERE c.Char_Name = ? AND c.Char_UCP = ?
                    ");
                    $stmtUpdate->execute([$savedPath, $charName, $sessionUser['username']]);
                } catch(PDOException $e) {
                    // Ignore error, it will just return the path
                }
                
                echo json_encode(["status" => "success", "path" => $savedPath]);
                exit;
            }
        }
    }
    echo json_encode(["status" => "error", "message" => "Gagal upload gambar character"]);
    
} else if ($action === 'upload_payment_proof') {
    $ucpName = preg_replace('/[^a-zA-Z0-9_]/', '', $_POST['ucpName'] ?? 'user');
    
    if (isset($_FILES['proof']) && $_FILES['proof']['error'] === UPLOAD_ERR_OK) {
        $ext = strtolower(pathinfo($_FILES['proof']['name'], PATHINFO_EXTENSION));
        $allowed = ['jpg', 'jpeg', 'png', 'pdf'];
        
        // Proteksi Tambahan: Verifikasi MIME type
        $finfo = finfo_open(FILEINFO_MIME_TYPE);
        $mime = finfo_file($finfo, $_FILES['proof']['tmp_name']);
        finfo_close($finfo);
        $allowed_mimes = ['image/jpeg', 'image/png', 'application/pdf'];
        
        if (in_array($ext, $allowed) && in_array($mime, $allowed_mimes)) {
            $newName = $ucpName . '_' . time() . '.' . $ext;
            $uploadDir = '../uploads/payment_proofs/';
            
            if (!is_dir($uploadDir)) mkdir($uploadDir, 0777, true);
            
            if (move_uploaded_file($_FILES['proof']['tmp_name'], $uploadDir . $newName)) {
                echo json_encode(["status" => "success", "path" => "uploads/payment_proofs/" . $newName]);
                exit;
            }
        }
    }
    echo json_encode(["status" => "error", "message" => "Gagal upload struk pembayaran"]);
} else {
    echo json_encode(["status" => "error", "message" => "Unknown upload action"]);
}
?>
