<?php
require_once __DIR__ . '/config.php';

$action = isset($_GET['action']) ? $_GET['action'] : (isset($_POST['action']) ? $_POST['action'] : null);
if (!$action) {
    $data = get_sanitized_json();
    if (isset($data['action'])) {
        $action = $data['action'];
    }
}

if ($action === 'get_stories') {
    $stmt = $pdo->query("
        SELECT cs.*, c.Char_Name as character_name, 'None' as photo_url, c.Char_Skin as skin_id
        FROM ucp_character_stories cs
        JOIN player_characters c ON cs.character_id = c.pID
        ORDER BY cs.last_updated DESC
    ");
    echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
    
} else if ($action === 'update_status') {
    $storyId = $_POST['story_id'] ?? null;
    $status = $_POST['status'] ?? null;
    $feedback = $_POST['feedback'] ?? '';
    
    if($storyId && $status) {
        $stmt = $pdo->prepare("UPDATE ucp_character_stories SET status = ?, admin_feedback = ?, reviewed_by = ?, reviewed_at = CURRENT_TIMESTAMP WHERE id = ?");
        // Using "Admin UCP" as a hardcoded reviewer for testing.
        $stmt->execute([$status, $feedback, "Admin UCP", $storyId]);
        
        // Dapatkan character_id dari cerita ini
        $stmtChar = $pdo->prepare("SELECT cs.character_id, cs.username, c.Char_Name FROM ucp_character_stories cs JOIN player_characters c ON cs.character_id = c.pID WHERE cs.id = ?");
        $stmtChar->execute([$storyId]);
        $charRow = $stmtChar->fetch(PDO::FETCH_ASSOC);
        
        if ($charRow) {
            $charId = $charRow['character_id'];
            $targetUser = $charRow['username'];
            $charName = $charRow['Char_Name'];
            
            $stmtCharUpdate = $pdo->prepare("UPDATE player_characters SET story_status = ? WHERE pID = ?");
            // If the story is rejected, maybe set it to 'None', or keep it 'Rejected'. 
            // The characters table enum is: 'None', 'Pending', 'Active', 'Revision'
            // So if status is 'Rejected', map it to 'None' or 'Revision'
            $charStatusMap = $status === 'Rejected' ? 'None' : $status;
            $stmtCharUpdate->execute([$charStatusMap, $charId]);
            
            // --- INBOX NOTIFICATION: CHARACTER STORY REVIEWED ---
            $adminFeedbackSafe = htmlspecialchars($feedback ?: 'Tidak ada catatan tambahan.');
            $statusDisplay = $status === 'Active' ? 'Disetujui' : ($status === 'Rejected' ? 'Ditolak' : 'Butuh Revisi');
            $statusColor = $status === 'Active' ? '#16a34a' : ($status === 'Rejected' ? '#ef4444' : '#eab308');
            $charNameSafe = htmlspecialchars($charName);
            
            $inboxTitle = "Pemberitahuan: Character Story {$charNameSafe}";
            
            $metadataObj = [
                'characterName' => $charNameSafe,
                'status' => $statusDisplay,
                'message' => $adminFeedbackSafe
            ];
            $metadataJson = json_encode($metadataObj);

            $stmt_inbox = $pdo->prepare("INSERT INTO ucp_inbox_messages (username, title, message, type, is_read, template, metadata) VALUES (?, ?, ?, 'System', 0, 'CharacterStoryReview', ?)");
            $stmt_inbox->execute([
                $targetUser, 
                $inboxTitle, 
                "Hasil pemeriksaan Character Story untuk karakter {$charNameSafe}.",
                $metadataJson
            ]);
        }
        
        try {
            $logStmt = $pdo->prepare("INSERT INTO ucp_admin_logs (admin_name, action, target_player, details) VALUES (?, ?, ?, ?)");
            $logStmt->execute(['Admin UCP', 'STORY_EVALUATION', $storyId, "Story status updated to $status"]);
        } catch(Exception $e) {}
        
        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => "Story ID or Status missing"]);
    }
    
} else {
    echo json_encode(["status" => "error", "message" => "Unknown action"]);
}
?>
