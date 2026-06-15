<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $charId = $_GET['char_id'] ?? 0;
    
    if ($charId > 0) {
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
