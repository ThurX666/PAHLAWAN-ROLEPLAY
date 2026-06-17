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
    // Economy inflation chart data
    $chartData = [
        ["day" => "Mon", "circulation" => 1200000, "assets" => 800000],
        ["day" => "Tue", "circulation" => 1350000, "assets" => 820000],
        ["day" => "Wed", "circulation" => 1250000, "assets" => 850000],
        ["day" => "Thu", "circulation" => 1500000, "assets" => 900000],
        ["day" => "Fri", "circulation" => 1450000, "assets" => 950000],
        ["day" => "Sat", "circulation" => 1800000, "assets" => 1100000],
        ["day" => "Sun", "circulation" => 1700000, "assets" => 1050000],
    ];
    echo json_encode([
        "status" => "success",
        "data" => [
            "totalCash" => "$2.6M",
            "chartData" => $chartData
        ]
    ]);
} elseif ($action === 'assets') {
    $type = $_GET['type'] ?? '';
    // Normally fetch from DB: SELECT * FROM houses, etc.
    $data = [];
    if ($type === 'houses') {
        $stmt = $pdo->query("SELECT ID as id, 'House' as name, OwnerName as owner, Type as price, Locked as locked FROM houses LIMIT 10");
        $data = $stmt->fetchAll(PDO::FETCH_ASSOC);
    } elseif ($type === 'businesses') {
        $stmt = $pdo->query("SELECT ID as id, Name as name, Type as type, OwnerName as owner, Money as balance FROM biz LIMIT 10");
        $data = $stmt->fetchAll(PDO::FETCH_ASSOC);
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
        $stmt = $pdo->query("SELECT ID as id, Name as name, 'Gang' as type, LeaderName as leader, Money as bank FROM families LIMIT 10");
        $data = $stmt->fetchAll(PDO::FETCH_ASSOC);
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
