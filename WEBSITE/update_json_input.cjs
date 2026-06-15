const fs = require('fs');
const path = require('path');

const dir = path.join(__dirname, 'public', 'api');
const files = fs.readdirSync(dir).filter(f => f.endsWith('.php'));

files.forEach(f => {
    let p = path.join(dir, f);
    let code = fs.readFileSync(p, 'utf8');
    
    if (code.includes("json_decode(file_get_contents('php://input'), true)")) {
        code = code.replace(/json_decode\s*\(\s*file_get_contents\s*\(\s*['"]php:\/\/input['"]\s*\)\s*,\s*true\s*\)/g, "get_sanitized_json()");
        fs.writeFileSync(p, code, 'utf8');
        console.log("Updated to get_sanitized_json() in", f);
    }
    
    // Some might have it without true flag or slightly different spacing, though earlier grep showed exact match format
});
