
export const formatTime = (dateString: string) => {
    const date = new Date(dateString);
    const now = new Date();
    const diffInSeconds = Math.floor((now.getTime() - date.getTime()) / 1000);

    // Fallback for invalid dates
    if (isNaN(diffInSeconds)) return dateString;

    // Logic < 24 Hours (Relative)
    if (diffInSeconds < 60) {
        return 'Baru saja';
    } else if (diffInSeconds < 3600) {
        return `${Math.floor(diffInSeconds / 60)} menit yang lalu`;
    } else if (diffInSeconds < 86400) { // 24 jam * 60 menit * 60 detik
        return `${Math.floor(diffInSeconds / 3600)} jam yang lalu`;
    } 
    
    // Logic > 24 Hours (Full Date & Time)
    const formattedDate = new Intl.DateTimeFormat('id-ID', {
        day: 'numeric',
        month: 'short',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        hour12: false
    }).format(date);
    
    return `${formattedDate.replace('.', ':')} WIB`;
};

export const getStatusColor = (status: string) => {
    switch(status) {
        case 'Open': return 'bg-amber-100 text-amber-600 border-amber-200 dark:bg-amber-900/30 dark:text-amber-400 dark:border-amber-800';
        case 'Proses': return 'bg-blue-100 text-blue-600 border-blue-200 dark:bg-blue-900/30 dark:text-blue-400 dark:border-blue-800';
        case 'Dijawab': return 'bg-green-100 text-green-600 border-green-200 dark:bg-green-900/30 dark:text-green-400 dark:border-green-800';
        case 'Ditutup': return 'bg-gray-100 text-gray-600 border-gray-200 dark:bg-gray-800 dark:text-gray-400 dark:border-gray-700';
        default: return 'bg-gray-100 text-gray-600';
    }
};
