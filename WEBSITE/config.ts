export const isPreviewEnv = (): boolean => {
    // Force disabled — no preview/dummy mode. Still used by Settings.tsx (future cleanup: task 2.12 extension)
    return false;
};

// Karena kita akan menaruh file PHP di dalam folder public/api,
// hasil akhirnya (dist/api) akan berada tepat di samping index.html
// Jadi kita bisa menggunakan local path /api atau URL yang di-set di .env
const rawApiUrl = import.meta.env.VITE_API_BASE_URL || import.meta.env.VITE_API_URL || 'api';

export const getResolvedApiUrl = (): string => {
    let base = rawApiUrl;
    if (base.startsWith('http')) return base;
    if (base.startsWith('/')) return base;
    let basePath = import.meta.env.BASE_URL || '/';
    if (!basePath.endsWith('/')) basePath += '/';
    return `${basePath}${base}`;
};

export const API_URL = (() => {
    const res = getResolvedApiUrl();
    return res.endsWith('/') ? res.slice(0, -1) : res;
})();

export const UPLOAD_BASE_URL = (() => {
    let url = getResolvedApiUrl();
    if (url.endsWith('/api')) return url.slice(0, -4);
    if (url.endsWith('/api/')) return url.slice(0, -5);
    return url;
})();
