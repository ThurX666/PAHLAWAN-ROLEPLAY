const fs = require('fs');
const path = require('path');

const apiDir = path.join(__dirname, 'public', 'api');

function injectSecurity() {
    const files = fs.readdirSync(apiDir).filter(f => f.endsWith('.php') && f !== 'security.php');
    
    files.forEach(file => {
        const filePath = path.join(apiDir, file);
        let content = fs.readFileSync(filePath, 'utf8');
        
        // Remove existing require_once if it exists to avoid duplicates
        content = content.replace(/require_once __DIR__ \. '\/security\.php';\r?\n?/g, '');
        
        // Add security.php explicitly after <?php
        if (content.startsWith('<?php')) {
            content = content.replace(/^<\?php\r?\n?/, "<?php\nrequire_once __DIR__ . '/security.php';\n");
            fs.writeFileSync(filePath, content, 'utf8');
            console.log(`Injected into ${file}`);
        }
    });
}

injectSecurity();
