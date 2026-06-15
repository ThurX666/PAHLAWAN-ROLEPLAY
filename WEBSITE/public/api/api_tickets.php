<?php
require_once __DIR__ . '/config.php';

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $username = $_GET['username'] ?? '';
    if (!$username) {
        echo json_encode(['status' => 'error', 'message' => 'Username required']);
        exit;
    }

    // Cek apakah user ini admin
    $stmtCheck = $pdo->prepare("SELECT admin_level FROM player_ucp WHERE UCP = ?");
    $stmtCheck->execute([$username]);
    $userRow = $stmtCheck->fetch(PDO::FETCH_ASSOC);
    
    $isAdmin = false;
    if ($userRow && (int)$userRow['admin_level'] > 0) {
        $isAdmin = true;
    }

    // Ambil data untuk Admin atau User biasa
    if ($isAdmin || strtolower($username) === 'admin') {
        $stmt = $pdo->prepare("SELECT * FROM ucp_support_tickets ORDER BY last_update DESC");
        $stmt->execute();
    } else {
        $stmt = $pdo->prepare("SELECT * FROM ucp_support_tickets WHERE username = ? ORDER BY last_update DESC");
        $stmt->execute([$username]);
    }
    
    $tickets = $stmt->fetchAll(PDO::FETCH_ASSOC);
    $output = [];

    foreach ($tickets as $row) {
        $stmtMsg = $pdo->prepare("SELECT * FROM ucp_support_messages WHERE ticket_id = ? ORDER BY created_at ASC");
        $stmtMsg->execute([$row['id']]);
        $msgs = $stmtMsg->fetchAll(PDO::FETCH_ASSOC);
        
        $messagesFormat = [];
        foreach ($msgs as $m) {
            $messagesFormat[] = [
                'sender' => $m['sender_name'],
                'text' => $m['message_text'],
                'time' => $m['created_at']
            ];
        }

        $output[] = [
            'id' => (int)$row['id'],
            'subject' => $row['subject'],
            'category' => $row['category'],
            'status' => $row['status'],
            'lastUpdate' => $row['last_update'],
            'messages' => $messagesFormat
        ];
    }

    echo json_encode(['status' => 'success', 'data' => $output]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = get_sanitized_json();
    $action = $data['action'] ?? '';

    if ($action === 'create_ticket') {
        $username = $data['username'];
        $subject = $data['subject'];
        $category = $data['category'];
        $initial_message = $data['initial_message'];

        $stmt = $pdo->prepare("INSERT INTO ucp_support_tickets (username, subject, category) VALUES (?, ?, ?)");
        $stmt->execute([$username, $subject, $category]);
        $ticketId = $pdo->lastInsertId();

        $stmtMsg = $pdo->prepare("INSERT INTO ucp_support_messages (ticket_id, sender_name, message_text) VALUES (?, ?, ?)");
        $stmtMsg->execute([$ticketId, $username, $initial_message]);

        echo json_encode(['status' => 'success', 'ticket_id' => $ticketId]);
        exit;
    }

    if ($action === 'reply_ticket') {
        $ticket_id = $data['ticket_id'];
        $sender = $data['sender'];
        $text = $data['text'];
        $status = $data['status'];

        $stmtMsg = $pdo->prepare("INSERT INTO ucp_support_messages (ticket_id, sender_name, message_text) VALUES (?, ?, ?)");
        $stmtMsg->execute([$ticket_id, $sender, $text]);

        // Update last_update dan status
        $stmtTick = $pdo->prepare("UPDATE ucp_support_tickets SET status = ?, last_update = CURRENT_TIMESTAMP WHERE id = ?");
        $stmtTick->execute([$status, $ticket_id]);

        echo json_encode(['status' => 'success']);
        exit;
    }

    if ($action === 'update_status') {
        $ticket_id = $data['ticket_id'];
        $status = $data['status'];

        $stmtTick = $pdo->prepare("UPDATE ucp_support_tickets SET status = ?, last_update = CURRENT_TIMESTAMP WHERE id = ?");
        $stmtTick->execute([$status, $ticket_id]);
        
        // --- INBOX NOTIFICATION: TICKET CLOSED/RESOLVED ---
        if ($status === 'Resolved' || $status === 'Closed') {
            $stmtTickInfo = $pdo->prepare("SELECT username, subject, category FROM ucp_support_tickets WHERE id = ?");
            $stmtTickInfo->execute([$ticket_id]);
            $tickInfo = $stmtTickInfo->fetch(PDO::FETCH_ASSOC);
            
            if ($tickInfo) {
                $targetUser = $tickInfo['username'];
                $subjectSafe = htmlspecialchars($tickInfo['subject']);
                $categorySafe = htmlspecialchars($tickInfo['category']);
                $statusColor = $status === 'Resolved' ? '#16a34a' : '#5865F2';
                $statusDisplay = $status === 'Resolved' ? 'Selesai (Resolved)' : 'Ditutup (Closed)';
                
                $inboxTitle = "Pemberitahuan: Tiket Bantuan \"{$subjectSafe}\" {$statusDisplay}";
                $metadata = json_encode([
                    'ticketId' => '#TICKET-' . $ticket_id,
                    'ticketTitle' => $tickInfo['subject'],
                    'category' => $tickInfo['category'],
                    'status' => $statusDisplay
                ]);
                
                $inboxStmt = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, '', 'System', 0, 'TicketClosed', ?)");
                $inboxStmt->execute([$targetUser, $inboxTitle, $metadata]);
            }
        }

        echo json_encode(['status' => 'success']);
        exit;
    }
}

echo json_encode(['status' => 'error', 'message' => 'Invalid method']);
