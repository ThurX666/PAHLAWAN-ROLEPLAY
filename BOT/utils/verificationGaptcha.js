const verificationCodes = new Map();

// Generate kode random 6 karakter (huruf + angka)
function generateVerificationCode() {
    const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    let code = '';
    for (let i = 0; i < 6; i++) {
        code += chars.charAt(Math.floor(Math.random() * chars.length));
    }
    return code;
}

// Simpan kode verifikasi
function saveVerificationCode(userId, code, expiresInMinutes = 5) {
    const expires = Date.now() + (expiresInMinutes * 60 * 1000);
    verificationCodes.set(userId, { code, expires });
    return { code, expires };
}

// Ambil kode verifikasi
function getVerificationCode(userId) {
    return verificationCodes.get(userId);
}

// Hapus kode verifikasi
function deleteVerificationCode(userId) {
    return verificationCodes.delete(userId);
}

// Cek apakah kode valid
function isValidCode(userId, inputCode) {
    const data = verificationCodes.get(userId);
    if (!data) return false;
    
    const { code, expires } = data;
    if (Date.now() > expires) {
        verificationCodes.delete(userId);
        return false;
    }
    
    return inputCode.toUpperCase() === code;
}

// Bersihkan kode expired (bisa dipanggil periodik)
function cleanupExpiredCodes() {
    const now = Date.now();
    for (const [userId, data] of verificationCodes.entries()) {
        if (now > data.expires) {
            verificationCodes.delete(userId);
        }
    }
}

module.exports = {
    verificationCodes,
    generateVerificationCode,
    saveVerificationCode,
    getVerificationCode,
    deleteVerificationCode,
    isValidCode,
    cleanupExpiredCodes
};