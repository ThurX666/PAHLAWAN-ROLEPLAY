<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $sessionUser = ucp_require_user();
    $charId = $_GET['char_id'] ?? 0;
    
    if ($charId > 0) {
        $stmtOwner = $pdo->prepare("SELECT pID FROM player_characters WHERE pID = ? AND Char_UCP = ?");
        $stmtOwner->execute([$charId, $sessionUser['username']]);
        if (!$stmtOwner->fetchColumn()) {
            ucp_json_error('Karakter tidak ditemukan atau bukan milik Anda.', 404);
        }
        $stmtVeh = $pdo->prepare("SELECT id, PVeh_ModelID as name, PVeh_Plate as plate, PVeh_Parked as location FROM player_vehicles WHERE PVeh_Owner = ?");
        $stmtVeh->execute([$charId]);
        $vehicles = $stmtVeh->fetchAll(PDO::FETCH_ASSOC);

        $stmtProp = $pdo->prepare("SELECT ID as id, 'House' as name, OwnerName as location, Type as type FROM houses WHERE OwnerID = ?
                                  UNION ALL
                                  SELECT ID as id, Name as name, 'Business' as location, Type as type FROM biz WHERE OwnerID = ?");
        $stmtProp->execute([$charId, $charId]);
        $properties = $stmtProp->fetchAll(PDO::FETCH_ASSOC);

        echo json_encode([
            "vehicles" => $vehicles,
            "properties" => $properties
        ]);
        exit;
    } else {
        echo json_encode(["error" => "Character ID required"]);
        exit;
    }
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
