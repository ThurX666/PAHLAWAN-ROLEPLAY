const fs = require('fs');
const path = require('path');

const apiDir = path.join(__dirname, 'public', 'api');

function modulerize() {
    const files = fs.readdirSync(apiDir).filter(f => f.endsWith('.php') && f !== 'security.php' && f !== 'config.php' && f !== 'mailer_helper.php');
    
    files.forEach(file => {
        const filePath = path.join(apiDir, file);
        let content = fs.readFileSync(filePath, 'utf8');
        
        // 1. Ganti semua format koneksi menjadi cukup memanggil config.php
        let newContent = content
            // Remove previous explicit security includes since config handles it
            .replace(/require_once __DIR__ \. '\/security\.php';\r?\n?/g, '')
            // Remove redundant header calls
            .replace(/header\("Access-Control-[^"]+"\);\r?\n?/g, '')
            .replace(/header\("Content-Type:[^"]+"\);\r?\n?/g, '')
            // Remove OPTIONS block
            .replace(/if \(\$_SERVER\['REQUEST_METHOD'\] (?:===|==) 'OPTIONS'\) \{\s*http_response_code\(200\);\s*exit;\s*\}\r?\n?/g, '')
            .replace(/if \(\$_SERVER\['REQUEST_METHOD'\] (?:===|==) 'OPTIONS'\) \{\s*exit\(0\);\s*\}\r?\n?/g, '')
            // Remove hardcoded database variables
            .replace(/\$db_host\s*=\s*'[^']+';\r?\n?/g, '')
            .replace(/\$db_host\s*=\s*"[^"]+";\r?\n?/g, '')
            .replace(/\$db_name\s*=\s*'[^']+';\r?\n?/g, '')
            .replace(/\$db_name\s*=\s*"[^"]+";\r?\n?/g, '')
            .replace(/\$db_user\s*=\s*'[^']+';\r?\n?/g, '')
            .replace(/\$db_user\s*=\s*"[^"]+";\r?\n?/g, '')
            .replace(/\$db_pass\s*=\s*'[^']*';\r?\n?/g, '')
            .replace(/\$db_pass\s*=\s*"[^"]*";\r?\n?/g, '')
            .replace(/\$db_port\s*=\s*['"]?[^'"]+['"]?;\r?\n?/g, '')
            .replace(/\/\/\s*Konfigurasi Database\r?\n?/gi, '')
            // Remove local PDO setup blocks specifically for the hardcoded endpoints
            .replace(/try\s*\{\s*\$pdo\s*=\s*new\s*PDO\([^)]+\);\s*\$pdo->setAttribute\([^)]+\);\s*\}\s*catch\s*\([^)]+\)\s*\{[\s\S]*?exit;\s*\}/, '')
            .replace(/\$pdo\s*=\s*new\s*PDO\("[^"]+",\s*"[^"]+",\s*"[^"]*"\);/g, '')
            ;
            
        // 2. Ensure config.php is required at the very top (right after <?php)
        if (newContent.startsWith('<?php')) {
            newContent = newContent.replace(/^<\?php\r?\n?/, "<?php\nrequire_once __DIR__ . '/config.php';\n");
            
            // Cleanup double blanks
            newContent = newContent.replace(/\n{3,}/g, '\n\n');
            
            fs.writeFileSync(filePath, newContent, 'utf8');
            console.log(`Modularized ${file}`);
        }
    });
}

modulerize();
