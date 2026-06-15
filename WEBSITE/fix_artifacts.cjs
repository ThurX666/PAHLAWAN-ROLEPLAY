const fs = require('fs');
const path = require('path');

const dir = path.join(__dirname, 'public', 'api');
const files = fs.readdirSync(dir).filter(f => f.endsWith('.php') && f !== 'config.php');

files.forEach(f => {
    let p = path.join(dir, f);
    let code = fs.readFileSync(p, 'utf8');
    
    if (code.includes('Database connection failed')) {
        console.log("Fixing pattern in", f);
        // Replace everything between config.php and the $action/$username declaration
        code = code.replace(/require_once __DIR__ \. '\/config\.php';[\s\S]*?\}[\r\n\s]*(?=\$action|\$_GET|\$data)/, "require_once __DIR__ . '/config.php';\n\n");
        fs.writeFileSync(p, code, 'utf8');
    }
});
