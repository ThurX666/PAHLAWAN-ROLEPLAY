const fs = require('fs');
const path = require('path');

const dir = path.join(__dirname, 'public', 'api');
const files = fs.readdirSync(dir).filter(f => f.endsWith('.php'));

files.forEach(f => {
    let p = path.join(dir, f);
    let code = fs.readFileSync(p, 'utf8');
    
    if (code.includes("require_once 'config.php';")) {
        code = code.replace(/require_once 'config\.php';\r?\n?/g, "");
        fs.writeFileSync(p, code, 'utf8');
        console.log("Removed redundant config include from", f);
    }
});
