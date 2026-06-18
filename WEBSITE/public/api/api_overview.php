<?php
require_once __DIR__ . '/config.php';

// Koneksi Database

$action = $_GET['action'] ?? '';

if (in_array($action, ['stats', 'chart', 'assets', 'detail'], true)) {
    ucp_require_admin(5);
}

if ($action === 'server_info') {
    require_once __DIR__ . '/SampQuery.php';
    
    $query = new SampQuery($samp_server_ip, $samp_server_port);
    $server_data = $query->getInfo();

    if ($server_data !== false) {
        echo json_encode([
            "status" => "success",
            "data" => [
                "hostname" => $server_data['hostname'],
                "players" => $server_data['players'],
                "maxPlayers" => $server_data['max_players'],
                "mode" => $server_data['gamemode'],
                "map" => $server_data['mapname'],
                "weather" => "Cerah",
                "status" => "Online",
                "ip_address" => $samp_server_ip . ":" . $samp_server_port
            ]
        ]);
    } else {
        echo json_encode([
            "status" => "success",
            "data" => [
                "hostname" => "Server Offline",
                "players" => 0,
                "maxPlayers" => 0,
                "mode" => "Unknown",
                "map" => "Unknown",
                "weather" => "Unknown",
                "status" => "Offline",
                "ip_address" => $samp_server_ip . ":" . $samp_server_port
            ]
        ]);
    }
} elseif ($action === 'players') {
    // Mengambil data dari MYSQL (disarankan untuk ratusan player)
    // Server Gamemode harus bertanggung jawab melakukan insert/update di tabel ucp_online_players
    try {
        $stmt = $pdo->query("SELECT player_id as id, character_name as name, color, score, ping FROM ucp_online_players ORDER BY player_id ASC");
        $players = $stmt->fetchAll(PDO::FETCH_ASSOC);

        // Ubah tipe data 
        foreach ($players as &$p) {
            $p['id'] = (int)$p['id'];
            $p['score'] = (int)$p['score'];
            $p['ping'] = (int)$p['ping'];
        }

        echo json_encode([
            "status" => "success",
            "data" => $players
        ]);
    } catch (PDOException $e) {
        // Jika tabel belum ada, kembalikan response array kosong
        echo json_encode([
            "status" => "success", // Gunakan success dan return array kosong agar tidak UI error loop
            "data" => [],
            "warning" => "Table ucp_online_players not found. Please setup it in database."
        ]);
    }
} elseif ($action === 'stats') {
    $accounts = "8,420";
    $chars = "12,450";
    $admins = "18";
    $discordMembers = "5,230";
    $houses = 0;
    $biz = 0;
    $jobs = "?";
    $sidejobs = "?";
    $families = 0;
    $pendingCS = 0;
    $pendingDonations = 0;
    $pendingRequests = 0;

    try {
        $stmtAccounts = $pdo->query("SELECT COUNT(*) FROM player_ucp");
        $countsAccounts = $stmtAccounts->fetchColumn();
        if ($countsAccounts !== false) $accounts = number_format($countsAccounts);

        $stmtHouses = $pdo->query("SELECT COUNT(*) FROM houses");
        $houses = (int) $stmtHouses->fetchColumn();

        $stmtBiz = $pdo->query("SELECT COUNT(*) FROM biz");
        $biz = (int) $stmtBiz->fetchColumn();
        
        $stmtFam = $pdo->query("SELECT COUNT(*) FROM families");
        $families = (int) $stmtFam->fetchColumn();
        
        $stmtCS = $pdo->query("SELECT COUNT(*) FROM ucp_character_stories WHERE status = 'Pending'");
        $pendingCS = (int) $stmtCS->fetchColumn();

        $stmtDonations = $pdo->query("SELECT COUNT(*) FROM ucp_transactions WHERE status = 'Pending'");
        $pendingDonations = (int) $stmtDonations->fetchColumn();

        $stmtReq = $pdo->query("SELECT COUNT(*) FROM ucp_data_change_requests WHERE status = 'Pending'");
        $pendingRequests = (int) $stmtReq->fetchColumn();
    } catch (Exception $e) {
        // Just use default mock data if tables don't exist yet
    }
    
    echo json_encode([
        "status" => "success",
        "data" => [
            "accounts" => $accounts,
            "chars" => $chars,
            "admins" => $admins,
            "discordMembers" => $discordMembers,
            "houses" => $houses,
            "biz" => $biz,
            "jobs" => $jobs,
            "sidejobs" => $sidejobs,
            "families" => $families,
            "pendingCS" => $pendingCS,
            "pendingDonations" => $pendingDonations,
            "pendingRequests" => $pendingRequests
        ]
    ]);
} elseif ($action === 'chart') {
    try {
        $stmt = $pdo->query(
            "SELECT stat_date, total_circulation, total_assets_value
             FROM ucp_economy_stats
             ORDER BY stat_date DESC
             LIMIT 7"
        );
        $rows = array_reverse($stmt->fetchAll(PDO::FETCH_ASSOC));
        $chartData = [];

        foreach ($rows as $row) {
            $timestamp = strtotime($row['stat_date']);
            $chartData[] = [
                "day" => $timestamp !== false ? date('d M', $timestamp) : $row['stat_date'],
                "circulation" => (int) $row['total_circulation'],
                "assets" => (int) $row['total_assets_value']
            ];
        }

        $latest = !empty($rows) ? $rows[count($rows) - 1] : null;
        echo json_encode([
            "status" => "success",
            "data" => [
                "totalCash" => $latest ? (int) $latest['total_circulation'] : 0,
                "chartData" => $chartData
            ]
        ]);
    } catch (PDOException $e) {
        http_response_code(503);
        echo json_encode([
            "status" => "error",
            "message" => "Data ekonomi belum tersedia."
        ]);
    }
} elseif ($action === 'assets') {
    $type = $_GET['type'] ?? '';

    $formatLocation = static function (...$coords): string {
        foreach ($coords as $coord) {
            if (!is_numeric($coord)) {
                return "Unknown";
            }
        }

        return sprintf("%.2f, %.2f, %.2f", (float) $coords[0], (float) $coords[1], (float) $coords[2]);
    };

    $safeOwner = static function ($value, string $fallback = "Unknown"): string {
        $value = trim((string) ($value ?? ''));
        return $value !== '' ? $value : $fallback;
    };

    $listTypes = ['houses', 'businesses', 'jobs', 'sidejobs', 'factions', 'families'];
    if (!in_array($type, $listTypes, true)) {
        http_response_code(400);
        echo json_encode([
            "status" => "error",
            "message" => "Unsupported asset type."
        ]);
        exit;
    }

    $data = [];
    if ($type === 'houses') {
        try {
            $stmt = $pdo->query(
                "SELECT ID, OwnerName, X, Y, Z
                 FROM houses
                 ORDER BY ID ASC
                 LIMIT 50"
            );

            foreach ($stmt->fetchAll(PDO::FETCH_ASSOC) as $row) {
                $data[] = [
                    "id" => (int) $row['ID'],
                    "name" => "House",
                    "location" => $formatLocation($row['X'] ?? null, $row['Y'] ?? null, $row['Z'] ?? null),
                    "owner" => $safeOwner($row['OwnerName'] ?? null),
                    "price" => null,
                    "locked" => null
                ];
            }
        } catch (PDOException $e) {
            http_response_code(503);
            echo json_encode([
                "status" => "error",
                "message" => "House asset list is unavailable."
            ]);
            exit;
        }
    } elseif ($type === 'businesses') {
        try {
            $stmt = $pdo->query(
                "SELECT ID, Name, OwnerName, Type, Price, Money, SignX, SignY, SignZ
                 FROM biz
                 ORDER BY ID ASC
                 LIMIT 50"
            );

            foreach ($stmt->fetchAll(PDO::FETCH_ASSOC) as $row) {
                $data[] = [
                    "id" => (int) $row['ID'],
                    "name" => $safeOwner($row['Name'] ?? null, "Unknown Business"),
                    "type" => isset($row['Type']) ? (string) $row['Type'] : "Unknown",
                    "owner" => $safeOwner($row['OwnerName'] ?? null),
                    "price" => isset($row['Price']) ? (int) $row['Price'] : null,
                    "balance" => isset($row['Money']) ? (int) $row['Money'] : null,
                    "money" => isset($row['Money']) ? (int) $row['Money'] : null,
                    "location" => $formatLocation($row['SignX'] ?? null, $row['SignY'] ?? null, $row['SignZ'] ?? null)
                ];
            }
        } catch (PDOException $e) {
            http_response_code(503);
            echo json_encode([
                "status" => "error",
                "message" => "Business asset list is unavailable."
            ]);
            exit;
        }
    } elseif ($type === 'jobs' || $type === 'sidejobs') {
        $data = [
            ["id" => 1, "name" => "Mechanic", "location" => "Ocean Docks", "avgWorkers" => 45, "avgCirculation" => 125000, "avgHours" => 4.5, "type" => "job"],
            ["id" => 2, "name" => "Sweeper", "location" => "Los Santos", "avgWorkers" => 120, "avgCirculation" => 45000, "avgHours" => 1.2, "type" => "sidejob"]
        ];
    } elseif ($type === 'factions') {
        // Based on the static definitions you provided
        $factionsList = [
            "Warga Pahlawan Roleplay",
            "Kepolisian",
            "Paramedis",
            "Putri Deli Beach Club",
            "Pemerintah",
            "Bennys Automotive",
            "Uber",
            "Pinky Tiger Club",
            "Pewarta",
            "Automax Workshop",
            "Handover Motorworks",
            "Sri Mersing Resto",
            "Texas Chicken"
        ];
        
        foreach ($factionsList as $index => $factionName) {
            $data[] = [
                "id" => $index,
                "name" => $factionName,
                "leader" => "System", // Default since it's hardcoded
                "members" => [], 
                "bank" => 0
            ];
        }
    } elseif ($type === 'families') {
        try {
            $stmt = $pdo->query(
                "SELECT ID, Name, LeaderName, Money
                 FROM families
                 ORDER BY ID ASC
                 LIMIT 50"
            );

            foreach ($stmt->fetchAll(PDO::FETCH_ASSOC) as $row) {
                $data[] = [
                    "id" => (int) $row['ID'],
                    "name" => $safeOwner($row['Name'] ?? null, "Unknown Family"),
                    "type" => "Gang",
                    "leader" => $safeOwner($row['LeaderName'] ?? null),
                    "level" => null,
                    "bank" => isset($row['Money']) ? (int) $row['Money'] : null
                ];
            }
        } catch (PDOException $e) {
            http_response_code(503);
            echo json_encode([
                "status" => "error",
                "message" => "Family asset list is unavailable."
            ]);
            exit;
        }
    }
    
    echo json_encode(["status" => "success", "data" => $data]);
} elseif ($action === 'detail') {
    $type = $_GET['type'] ?? '';
    $id = (int)($_GET['id'] ?? 0);
    
    // Simulate detail response
    $item = null;
    if ($type === 'houses') {
        $item = ["id" => $id, "location" => "Vinewood Hills", "owner" => "John_Doe", "price" => 250000, "locked" => true, "storage" => [["item" => "Desert Eagle", "qty" => 1]]];
    } elseif ($type === 'businesses') {
        $revenue = [
            ["day" => "Mon", "amount" => 1200], ["day" => "Tue", "amount" => 1500],
            ["day" => "Wed", "amount" => 900], ["day" => "Thu", "amount" => 2200],
            ["day" => "Fri", "amount" => 3500], ["day" => "Sat", "amount" => 4200],
            ["day" => "Sun", "amount" => 3100]
        ];
        $item = ["id" => $id, "name" => "Iddlewood Gas Station", "type" => "Gas Station", "location" => "Idlewood", "owner" => "Rich_Guy", "balance" => 15000, "revenueHistory" => $revenue];
    } elseif ($type === 'factions' || $type === 'families') {
        $item = ["id" => $id, "name" => "Los Santos Police Department", "leader" => "Chief_Justice", "members" => [
            ["name" => "Officer_Friendly", "rank" => "Cadet", "dutyHours" => 12, "lastLogin" => "2026-04-18"]
        ], "bank" => 500000];
    }
    
    if ($item) {
        echo json_encode(["status" => "success", "data" => $item]);
    } else {
        echo json_encode(["status" => "error", "message" => "Not found"]);
    }
}
?>
