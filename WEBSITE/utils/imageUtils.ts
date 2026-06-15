import { isPreviewEnv, API_URL, UPLOAD_BASE_URL } from '../config';

export const saveCharacterPhoto = async (characterName: string, dataUrl: string): Promise<string> => {
    if (isPreviewEnv()) {
        try {
            const path = `src/images/char/${characterName.replace(/\s+/g, '_')}.png`;
            localStorage.setItem(path, dataUrl);
            return path;
        } catch (e) {
            console.error("Failed to save character photo to simulated storage:", e);
            return dataUrl;
        }
    } else {
        // Upload via API
        try {
            const formData = new FormData();
            formData.append('action', 'upload_photo');
            formData.append('characterName', characterName);
            // Convert dataUrl to blob
            const responseData = await fetch(dataUrl);
            const blob = await responseData.blob();
            formData.append('photo', blob, `${characterName.replace(/\s+/g, '_')}.png`);
            
            const res = await fetch(`${API_URL}/api_upload_handler.php`, {
                method: 'POST',
                body: formData
            });
            const data = await res.json();
            if (data.status === 'success') {
                return data.path; // e.g. "uploads/characters/name.png"
            }
        } catch (e) {
            console.error("Upload error:", e);
        }
        return dataUrl;
    }
};

export const getCharacterPhotoUrl = (characterName: string, fallbackUrl?: string) => {
    if (isPreviewEnv()) {
        try {
            const path = `src/images/char/${characterName.replace(/\s+/g, '_')}.png`;
            const storedDataUrl = localStorage.getItem(path);
            if (storedDataUrl) {
                return storedDataUrl;
            }
        } catch (e) {}
        if (fallbackUrl?.startsWith('src/images/char/')) return undefined;
        return fallbackUrl;
    } else {
        if (!fallbackUrl) return undefined;
        // If it's a relative path from API uploads
        if (!fallbackUrl.startsWith('http') && !fallbackUrl.startsWith('data:')) {
            const cleanBase = UPLOAD_BASE_URL ? (UPLOAD_BASE_URL.endsWith('/') ? UPLOAD_BASE_URL : UPLOAD_BASE_URL + '/') : '';
            return `${cleanBase}${fallbackUrl}`;
        }
        return fallbackUrl;
    }
};

export const saveDonationProof = async (ucpName: string, dataUrl: string): Promise<string> => {
    if (isPreviewEnv()) {
        try {
            const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
            const path = `src/images/donate/${ucpName.replace(/\s+/g, '_')}_${timestamp}.png`;
            localStorage.setItem(path, dataUrl);
            return path;
        } catch (e) {
            return dataUrl;
        }
    } else {
        try {
            const formData = new FormData();
            formData.append('action', 'upload_payment_proof');
            formData.append('ucpName', ucpName);
            
            const responseData = await fetch(dataUrl);
            const blob = await responseData.blob();
            formData.append('proof', blob, `${ucpName.replace(/\s+/g, '_')}_${Date.now()}.png`);
            
            const res = await fetch(`${API_URL}/api_upload_handler.php`, {
                method: 'POST',
                body: formData
            });
            const data = await res.json();
            if (data.status === 'success') {
                return data.path;
            }
        } catch (e) {
            console.error(e);
        }
        return dataUrl;
    }
};

export const getDonationProofUrl = (path: string) => {
    if (isPreviewEnv()) {
        try {
            const storedDataUrl = localStorage.getItem(path);
            if (storedDataUrl) return storedDataUrl;
        } catch (e) {}
        return path;
    } else {
        if (!path.startsWith('http') && !path.startsWith('data:')) {
            const cleanBase = UPLOAD_BASE_URL ? (UPLOAD_BASE_URL.endsWith('/') ? UPLOAD_BASE_URL : UPLOAD_BASE_URL + '/') : '';
            return `${cleanBase}${path}`;
        }
        return path;
    }
};
