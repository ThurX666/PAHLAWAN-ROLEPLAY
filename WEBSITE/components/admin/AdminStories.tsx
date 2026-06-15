import React, { useState, useEffect } from 'react';
import { CharacterStory } from '../../types';
import { CheckCircle, XCircle, AlertTriangle, Search, FileText, RefreshCw, ChevronRight, ChevronLeft, User, Calendar, ShieldCheck, BookOpen } from 'lucide-react';
import { getCharacterPhotoUrl } from '../../utils/imageUtils';
import { isPreviewEnv, API_URL } from '../../config';

// --- MOCK DATABASE FOR PLAGIARISM CHECK ---
const EXISTING_STORIES_DB = [
    { id: 101, char: "Michael DeSanta", content: "Michael lahir di Los Santos pada tahun 1990. Dia tumbuh di lingkungan yang keras dan belajar bertahan hidup sejak kecil. Ayahnya adalah seorang mekanik dan ibunya bekerja di restoran." },
    { id: 102, char: "Franklin Clinton", content: "Franklin adalah seorang pemuda yang ambisius. Dia ingin keluar dari kehidupan geng dan menjadi sukses. Dia ahli dalam mengemudi dan sering terlibat balapan liar." },
    { id: 103, char: "Trevor Philips", content: "Trevor lahir di perbatasan Kanada. Dia memiliki masa kecil yang sulit dan sering berpindah-pindah. Dia pernah menjadi pilot angkatan udara sebelum diberhentikan karena masalah mental." },
    { id: 104, char: "Tommy Vercetti", content: "Tommy baru saja keluar dari penjara setelah 15 tahun. Dia dikirim ke Vice City untuk melakukan transaksi narkoba yang kemudian berantakan. Sekarang dia mencoba membangun kembali kekuasaannya." },
    { id: 105, char: "Carl Johnson", content: "CJ kembali ke Los Santos setelah ibunya meninggal. Dia menemukan geng lamanya, Grove Street Families, dalam keadaan berantakan. Dia harus menyatukan kembali keluarga dan teman-temannya." }
];

// --- UTILITY: SIMULATED AI PLAGIARISM CHECK ---
const checkPlagiarism = (content: string) => {
    if (!content) return { score: 0, match: null };
    
    const normalize = (str: string) => str.toLowerCase().replace(/[^\w\s]/g, '').split(/\s+/);
    const inputTokens = normalize(content);
    const inputSet = new Set(inputTokens);

    let maxSimilarity = 0;
    let bestMatch = null;

    for (const dbStory of EXISTING_STORIES_DB) {
        const dbTokens = normalize(dbStory.content);
        const dbSet = new Set(dbTokens);
        
        // Jaccard Similarity
        const intersection = new Set([...inputSet].filter(x => dbSet.has(x)));
        const union = new Set([...inputSet, ...dbSet]);
        const similarity = (intersection.size / union.size) * 100;

        if (similarity > maxSimilarity) {
            maxSimilarity = similarity;
            bestMatch = dbStory;
        }
    }

    // Add some random noise to make it feel more "AI"
    const noise = Math.random() * 5; 
    const finalScore = Math.min(100, Math.max(0, maxSimilarity + (maxSimilarity > 0 ? noise : 0)));

    return {
        score: parseFloat(finalScore.toFixed(1)),
        match: bestMatch ? { source: `Story of ${bestMatch.char}`, similarity: parseFloat(finalScore.toFixed(1)) } : null
    };
};

// --- MOCK PENDING STORIES ---
const INITIAL_STORIES: CharacterStory[] = [
    {
        id: 1,
        characterId: 201,
        characterName: "Ucok Subejo",
        photoUrl: "https://picsum.photos/seed/ucok/400/400",
        skinId: 1,
        content: "Ucok lahir di Medan dan merantau ke Los Santos untuk mencari pekerjaan. Dia bekerja keras sebagai supir taksi dan mengirim uang ke kampung halaman.",
        status: 'Pending',
        lastUpdated: new Date().toISOString()
    },
    {
        id: 2,
        characterId: 202,
        characterName: "Asep Knalpot",
        skinId: 2,
        content: "Michael lahir di Los Santos pada tahun 1990. Dia tumbuh di lingkungan yang keras dan belajar bertahan hidup sejak kecil.", // Intentionally copied
        status: 'Pending',
        lastUpdated: new Date(Date.now() - 86400000).toISOString()
    },
    {
        id: 3,
        characterId: 203,
        characterName: "Budi Santoso",
        skinId: 3,
        content: "Budi adalah seorang dokter yang berdedikasi. Dia lulus dari universitas ternama dan ingin membantu orang-orang di Los Santos.",
        status: 'Revision',
        adminFeedback: "Tolong tambahkan detail tentang masa kecilnya.",
        reviewedBy: "Admin_Ganteng",
        reviewedAt: new Date(Date.now() - 172800000).toISOString(),
        lastUpdated: new Date(Date.now() - 172800000).toISOString()
    },
    {
        id: 4,
        characterId: 204,
        characterName: "Siti Aminah",
        skinId: 4,
        content: "Siti adalah seorang pengusaha muda yang sukses. Dia memiliki beberapa bisnis di Los Santos dan selalu berusaha membantu masyarakat sekitar.",
        status: 'Active',
        reviewedBy: "Admin_Kece",
        reviewedAt: new Date(Date.now() - 259200000).toISOString(),
        lastUpdated: new Date(Date.now() - 259200000).toISOString()
    },
    {
        id: 5,
        characterId: 205,
        characterName: "Joko Anwar",
        skinId: 5,
        content: "Joko adalah seorang sutradara film terkenal. Dia datang ke Los Santos untuk mencari inspirasi untuk film terbarunya.",
        status: 'Rejected',
        adminFeedback: "Cerita terlalu singkat dan tidak memiliki detail yang cukup.",
        reviewedBy: "Admin_Tegas",
        reviewedAt: new Date(Date.now() - 345600000).toISOString(),
        lastUpdated: new Date(Date.now() - 345600000).toISOString()
    },
    {
        id: 6,
        characterId: 206,
        characterName: "Rina Nose",
        skinId: 6,
        content: "Rina adalah seorang komedian yang lucu. Dia sering tampil di klub komedi di Los Santos dan selalu berhasil membuat penonton tertawa.",
        status: 'Pending',
        lastUpdated: new Date(Date.now() - 432000000).toISOString()
    },
    {
        id: 7,
        characterId: 207,
        characterName: "Tukul Arwana",
        skinId: 7,
        content: "Tukul adalah seorang presenter televisi yang terkenal. Dia memiliki acara talk show sendiri di Los Santos dan sering mewawancarai selebriti.",
        status: 'Pending',
        lastUpdated: new Date(Date.now() - 518400000).toISOString()
    }
];

interface AdminStoriesProps {
    onStoryReviewed?: (characterName: string, status: string, feedback: string) => void;
}

export const AdminStories: React.FC<AdminStoriesProps> = ({ onStoryReviewed }) => {
    const [stories, setStories] = useState<CharacterStory[]>(INITIAL_STORIES);
    const [selectedStory, setSelectedStory] = useState<CharacterStory | null>(null);
    const [filter, setFilter] = useState<'All' | 'Pending' | 'Revision' | 'Active' | 'Rejected'>('All');
    const [searchQuery, setSearchQuery] = useState('');
    const [isChecking, setIsChecking] = useState(false);
    const [feedback, setFeedback] = useState('');

    const [grammarCheckResult, setGrammarCheckResult] = useState<{ isValid: boolean; errors: string[] } | null>(null);

    const fetchStories = async () => {
        if (!isPreviewEnv()) {
            try {
                const res = await fetch(`${API_URL}/api_admin_stories.php?action=get_stories`);
                if (res.ok) {
                    const data = await res.json();
                    if (Array.isArray(data)) {
                        setStories(data.map(item => ({
                            id: item.id,
                            characterId: item.character_id,
                            characterName: item.character_name,
                            photoUrl: item.photo_url || null,
                            skinId: item.skin_id,
                            content: item.content,
                            status: item.status,
                            adminFeedback: item.admin_feedback,
                            reviewedBy: item.reviewed_by,
                            reviewedAt: item.reviewed_at,
                            lastUpdated: item.last_updated
                        })));
                    }
                }
            } catch (err) {
                console.error("Gagal get_stories", err);
            }
        }
    };

    useEffect(() => {
        fetchStories();
    }, []);

    React.useEffect(() => {
        setGrammarCheckResult(null);
    }, [selectedStory]);

    const countWords = (text: string) => {
        if (!text) return 0;
        return text.trim().split(/\s+/).filter(word => word.length > 0).length;
    };

    const countParagraphs = (text: string) => {
        if (!text) return 0;
        return text.trim().split(/\n+/).filter(para => para.trim().length > 0).length;
    };

    const handleCheckGrammar = () => {
        if (!selectedStory) return;
        const text = selectedStory.content;
        const errors: string[] = [];

        // 1. Punctuation Spacing
        if (/(?<=[.,?!])(?=[^\s])/.test(text)) {
            errors.push("Spasi hilang setelah tanda baca (titik/koma).");
        }

        // 2. Repetitive Characters
        if (/(.)\1{4,}/.test(text)) {
            errors.push("Terdeteksi spam karakter berulang (misal: 'aaaaa').");
        }

        // 3. Capitalization (Basic check: Start of story)
        if (text.length > 0 && /^[a-z]/.test(text)) {
            errors.push("Awal cerita tidak menggunakan huruf kapital.");
        }

        setGrammarCheckResult({
            isValid: errors.length === 0,
            errors
        });
    };

    const [alertState, setAlertState] = useState<{
        isOpen: boolean;
        title: string;
        message: string;
        type: 'success' | 'error' | 'info';
    }>({ isOpen: false, title: '', message: '', type: 'info' });

    const showAlert = (title: string, message: string, type: 'success' | 'error' | 'info' = 'info') => {
        setAlertState({ isOpen: true, title, message, type });
    };

    const closeAlert = () => setAlertState(prev => ({ ...prev, isOpen: false }));

    const filteredStories = stories.filter(s => {
        const matchesFilter = filter === 'All' || s.status === filter;
        const matchesSearch = s.characterName.toLowerCase().includes(searchQuery.toLowerCase());
        return matchesFilter && matchesSearch;
    });

    const [currentPage, setCurrentPage] = useState(1);
    const itemsPerPage = 5;
    const totalPages = Math.ceil(filteredStories.length / itemsPerPage);
    
    const currentStories = filteredStories.slice(
        (currentPage - 1) * itemsPerPage,
        currentPage * itemsPerPage
    );

    // Reset pagination when filter or search changes
    React.useEffect(() => {
        setCurrentPage(1);
    }, [filter, searchQuery]);

    const handleCheckPlagiarism = () => {
        if (!selectedStory) return;
        setIsChecking(true);
        
        // Simulate API delay
        setTimeout(() => {
            const result = checkPlagiarism(selectedStory.content);
            const updatedStory = {
                ...selectedStory,
                plagiarismScore: result.score,
                plagiarismDetails: result.match ? [result.match] : []
            };
            
            setStories(stories.map(s => s.id === selectedStory.id ? updatedStory : s));
            setSelectedStory(updatedStory);
            setIsChecking(false);
        }, 1500);
    };

    const [isShaking, setIsShaking] = useState(false);

    const handleAction = async (status: 'Active' | 'Revision' | 'Rejected') => {
        if (!selectedStory) return;
        
        if ((status === 'Revision' || status === 'Rejected') && !feedback.trim()) {
            setIsShaking(true);
            setTimeout(() => setIsShaking(false), 500);
            showAlert("Action Required", "Harap isi feedback / alasan untuk melakukan Revisi atau Reject!", "error");
            return;
        }

        const updatedStory = {
            ...selectedStory,
            status: status,
            adminFeedback: feedback,
            reviewedBy: "Admin_Current", // In a real app, this would be the logged-in admin's name
            reviewedAt: new Date().toISOString(),
            lastUpdated: new Date().toISOString()
        };

        if (isPreviewEnv()) {
            setStories(stories.map(s => s.id === selectedStory.id ? updatedStory : s));
            if (onStoryReviewed) {
                const statusDisplay = status === 'Active' ? 'Disetujui' : (status === 'Rejected' ? 'Ditolak' : 'Butuh Revisi');
                onStoryReviewed(selectedStory.characterName, statusDisplay, feedback || 'Tidak ada catatan khusus.');
            }
            setSelectedStory(null);
            setFeedback('');
            showAlert("Success", `Story berhasil di-update statusnya menjadi: ${status}`, "success");
        } else {
            try {
                const res = await fetch(`${API_URL}/api_admin_stories.php`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                    body: new URLSearchParams({
                        action: 'update_status',
                        story_id: selectedStory.id.toString(),
                        status: status,
                        feedback: feedback
                    })
                });
                const data = await res.json();
                if (data.status === 'success') {
                    if (onStoryReviewed) {
                        const statusDisplay = status === 'Active' ? 'Disetujui' : (status === 'Rejected' ? 'Ditolak' : 'Butuh Revisi');
                        onStoryReviewed(selectedStory.characterName, statusDisplay, feedback || 'Tidak ada catatan khusus.');
                    }
                    fetchStories();
                    setSelectedStory(null);
                    setFeedback('');
                    showAlert("Success", `Story berhasil di-update statusnya menjadi: ${status}`, "success");
                } else {
                    showAlert("Error", "Gagal mengupdate story di database.", "error");
                }
            } catch (err) {
                console.error("Gagal update_status", err);
                showAlert("Error", "Terjadi kesalahan koneksi.", "error");
            }
        }
    };

    const formatDate = (dateStr: string) => {
        try {
            return new Date(dateStr).toLocaleDateString();
        } catch (e) {
            return 'Invalid Date';
        }
    };

    const formatDateTime = (dateStr: string) => {
        try {
            return new Date(dateStr).toLocaleString();
        } catch (e) {
            return 'Invalid Date';
        }
    };

    return (
        <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 h-[calc(100vh-200px)] min-h-[600px]">
            {/* LIST SECTION */}
            <div className={`lg:col-span-4 flex flex-col bg-gray-50 dark:bg-[#151515] rounded-xl border border-gray-200 dark:border-white/10 overflow-hidden ${selectedStory ? 'hidden lg:flex' : 'flex'}`}>
                <div className="p-4 border-b border-gray-200 dark:border-white/10 bg-white dark:bg-[#1a1a1a]">
                    <div className="flex items-center justify-between mb-4">
                        <h3 className="font-black text-gray-900 dark:text-white uppercase italic">Daftar Cerita</h3>
                        <span className="bg-red-100 text-red-600 text-[10px] font-bold px-2 py-0.5 rounded-full">{filteredStories.length}</span>
                    </div>

                    {/* Search Input */}
                    <div className="mb-4 relative">
                        <input 
                            type="text" 
                            placeholder="Cari nama karakter..." 
                            value={searchQuery}
                            onChange={(e) => setSearchQuery(e.target.value)}
                            className="w-full bg-gray-100 dark:bg-white/5 border border-gray-200 dark:border-white/10 rounded-lg pl-9 pr-3 py-2 text-xs focus:outline-none focus:border-red-500 dark:focus:border-red-500 transition-colors"
                        />
                        <Search size={14} className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" />
                    </div>
                    
                    {/* Filters */}
                    <div className="flex gap-2 overflow-x-auto pb-2 scrollbar-hide">
                        {['All', 'Pending', 'Revision', 'Active', 'Rejected'].map(f => (
                            <button
                                key={f}
                                onClick={() => setFilter(f as any)}
                                className={`px-3 py-1 rounded-lg text-[10px] font-bold uppercase whitespace-nowrap transition-all ${
                                    filter === f 
                                    ? 'bg-red-600 text-white shadow-md' 
                                    : 'bg-gray-200 dark:bg-white/5 text-gray-500 hover:bg-gray-300 dark:hover:bg-white/10'
                                }`}
                            >
                                {f}
                            </button>
                        ))}
                    </div>
                </div>

                <div className="flex-1 overflow-y-auto p-2 space-y-2 custom-scrollbar">
                    {currentStories.map(story => (
                        <div 
                            key={story.id}
                            onClick={() => setSelectedStory(story)}
                            className={`p-3 rounded-xl border cursor-pointer transition-all hover:shadow-md ${
                                selectedStory?.id === story.id 
                                ? 'bg-white dark:bg-[#222] border-red-500 ring-1 ring-red-500' 
                                : 'bg-white dark:bg-[#1a1a1a] border-gray-200 dark:border-white/5 hover:border-gray-300 dark:hover:border-white/20'
                            }`}
                        >
                            <div className="flex gap-3">
                                {/* Photo */}
                                <div className="w-10 h-10 rounded-full overflow-hidden border border-gray-200 dark:border-white/10 shrink-0 bg-gray-100 dark:bg-[#121212]">
                                    {story.photoUrl || getCharacterPhotoUrl(story.characterName) ? (
                                        <img src={getCharacterPhotoUrl(story.characterName, story.photoUrl)} alt={story.characterName} className="w-full h-full object-cover" />
                                    ) : (
                                        <div className="w-full h-full flex flex-col items-center justify-center text-gray-400 dark:text-gray-500" title="Belum ada foto karakter">
                                            <User size={16} className="opacity-50" />
                                        </div>
                                    )}
                                </div>
                                <div className="flex-1 min-w-0">
                                    <div className="flex justify-between items-start mb-1">
                                        <h4 className="font-bold text-sm text-gray-900 dark:text-white truncate">{story.characterName}</h4>
                                        <span className={`text-[9px] px-1.5 py-0.5 rounded font-bold uppercase shrink-0 ${
                                            story.status === 'Pending' ? 'bg-yellow-100 text-yellow-700' :
                                            story.status === 'Active' ? 'bg-green-100 text-green-700' :
                                            story.status === 'Revision' ? 'bg-orange-100 text-orange-700' :
                                            'bg-red-100 text-red-700'
                                        }`}>
                                            {story.status}
                                        </span>
                                    </div>
                                    <p className="text-xs text-gray-500 line-clamp-2 mb-2">{story.content}</p>
                                    <div className="flex items-center gap-2 text-[10px] text-gray-400">
                                        <User size={10} />
                                        <span>ID: {story.characterId}</span>
                                        <span className="mx-1">•</span>
                                        <Calendar size={10} />
                                        <span>{formatDate(story.lastUpdated)}</span>
                                    </div>
                                </div>
                            </div>
                        </div>
                    ))}
                </div>

                {/* Pagination Controls */}
                {totalPages > 1 && (
                    <div className="flex items-center justify-between px-4 py-3 border-t border-gray-200 dark:border-white/5 bg-gray-100/50 dark:bg-[#111]/50 shrink-0">
                        <button 
                            onClick={() => setCurrentPage(prev => Math.max(prev - 1, 1))}
                            disabled={currentPage === 1}
                            className="p-1.5 rounded-md text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10 disabled:opacity-30 disabled:cursor-not-allowed transition-colors"
                        >
                            <ChevronLeft size={18} />
                        </button>
                        <span className="text-[10px] md:text-xs font-bold text-gray-500 uppercase tracking-wider">
                            Halaman {currentPage} dari {totalPages}
                        </span>
                        <button 
                            onClick={() => setCurrentPage(prev => Math.min(prev + 1, totalPages))}
                            disabled={currentPage === totalPages}
                            className="p-1.5 rounded-md text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10 disabled:opacity-30 disabled:cursor-not-allowed transition-colors"
                        >
                            <ChevronRight size={18} />
                        </button>
                    </div>
                )}
            </div>

            {/* DETAIL SECTION */}
            <div className={`lg:col-span-8 flex flex-col bg-white dark:bg-[#151515] rounded-xl border border-gray-200 dark:border-white/10 overflow-hidden relative transition-all duration-300 ${
                selectedStory 
                ? '!fixed !inset-0 !z-[9999] !w-full !h-full !m-0 !rounded-none lg:!static lg:!h-auto lg:!rounded-xl lg:!border' 
                : 'hidden lg:flex'
            }`}>
                {selectedStory ? (
                    <>
                        {/* Header */}
                        <div className="p-4 md:p-6 border-b border-gray-200 dark:border-white/10 flex flex-col md:flex-row justify-between items-start md:items-center gap-4 bg-gray-50 dark:bg-[#1a1a1a]">
                            <div className="flex items-center gap-3 w-full md:w-auto">
                                <button 
                                    onClick={() => setSelectedStory(null)}
                                    className="lg:hidden p-2 -ml-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors"
                                >
                                    <ChevronLeft size={24} className="text-gray-900 dark:text-white" />
                                </button>
                                
                                {/* Character Photo */}
                                <div className="w-12 h-12 md:w-16 md:h-16 rounded-full overflow-hidden border-2 border-gray-200 dark:border-white/10 shrink-0 bg-gray-100 dark:bg-[#121212]">
                                    {selectedStory.photoUrl || getCharacterPhotoUrl(selectedStory.characterName) ? (
                                        <img src={getCharacterPhotoUrl(selectedStory.characterName, selectedStory.photoUrl)} alt={selectedStory.characterName} className="w-full h-full object-cover" />
                                    ) : (
                                        <div className="w-full h-full flex flex-col items-center justify-center text-gray-400 dark:text-gray-500" title="Belum ada foto karakter">
                                            <User size={20} className="opacity-50" />
                                        </div>
                                    )}
                                </div>

                                <div>
                                    <h2 className="text-xl md:text-2xl font-black text-gray-900 dark:text-white uppercase italic tracking-tight mb-1">
                                        {selectedStory.characterName}
                                    </h2>
                                    <div className="flex items-center gap-3 text-xs text-gray-500">
                                        <span className="flex items-center gap-1"><User size={12}/> ID: {selectedStory.characterId}</span>
                                        <span className="w-1 h-1 bg-gray-400 rounded-full"></span>
                                        <span className="flex items-center gap-1"><Calendar size={12}/> {formatDateTime(selectedStory.lastUpdated)}</span>
                                    </div>
                                </div>
                            </div>
                            
                            {/* AI Score Badge */}
                            {selectedStory.plagiarismScore !== undefined && (
                                <div className={`flex flex-col items-end px-3 py-2 rounded-lg border w-full md:w-auto ${
                                    selectedStory.plagiarismScore > 50 
                                    ? 'bg-red-50 border-red-200 text-red-700' 
                                    : 'bg-green-50 border-green-200 text-green-700'
                                }`}>
                                    <span className="text-[10px] font-bold uppercase tracking-wider">AI Plagiarism Score</span>
                                    <span className="text-xl font-black">{selectedStory.plagiarismScore}%</span>
                                </div>
                            )}
                        </div>

                        <div className="flex-1 overflow-y-auto p-4 md:p-6 custom-scrollbar bg-white dark:bg-[#151515]">
                            
                            {/* Status Banner for non-Pending */}
                            {selectedStory.status !== 'Pending' && (
                                <div className={`mb-6 p-4 rounded-xl border ${
                                    selectedStory.status === 'Revision' ? 'bg-orange-50 dark:bg-orange-900/10 border-orange-200 dark:border-orange-900/30 text-orange-800 dark:text-orange-300' :
                                    selectedStory.status === 'Rejected' ? 'bg-red-50 dark:bg-red-900/10 border-red-200 dark:border-red-900/30 text-red-800 dark:text-red-300' :
                                    'bg-green-50 dark:bg-green-900/10 border-green-200 dark:border-green-900/30 text-green-800 dark:text-green-300'
                                }`}>
                                    <div className="flex items-start gap-3">
                                        {selectedStory.status === 'Revision' && <RefreshCw className="shrink-0 mt-0.5" size={20} />}
                                        {selectedStory.status === 'Rejected' && <XCircle className="shrink-0 mt-0.5" size={20} />}
                                        {selectedStory.status === 'Active' && <CheckCircle className="shrink-0 mt-0.5" size={20} />}
                                        <div className="flex-1">
                                            <h3 className="font-bold text-sm uppercase tracking-wider mb-1">
                                                {selectedStory.status === 'Revision' ? 'Story Sedang Direvisi' :
                                                 selectedStory.status === 'Rejected' ? 'Story Ditolak' : 'Story Diterima'}
                                            </h3>
                                            <p className="text-xs opacity-90 mb-3">
                                                {selectedStory.status === 'Revision' ? 'Story ini sedang dalam tahap revisi oleh player. Harap tunggu hingga player melakukan perubahan.' :
                                                 selectedStory.status === 'Rejected' ? 'Story ini telah ditolak oleh admin.' : 'Story ini telah disetujui oleh admin.'}
                                            </p>
                                            
                                            <div className="bg-white/50 dark:bg-black/20 rounded-lg p-3 text-xs border border-current/10">
                                                <div className="grid grid-cols-2 gap-2 mb-2">
                                                    <div>
                                                        <span className="block opacity-70 text-[10px] uppercase font-bold mb-0.5">Ditindak Oleh</span>
                                                        <span className="font-medium flex items-center gap-1"><User size={10}/> {selectedStory.reviewedBy || 'Admin'}</span>
                                                    </div>
                                                    <div>
                                                        <span className="block opacity-70 text-[10px] uppercase font-bold mb-0.5">Tanggal Tindakan</span>
                                                        <span className="font-medium flex items-center gap-1"><Calendar size={10}/> {selectedStory.reviewedAt ? formatDateTime(selectedStory.reviewedAt) : formatDateTime(selectedStory.lastUpdated)}</span>
                                                    </div>
                                                </div>
                                                {(selectedStory.status === 'Revision' || selectedStory.status === 'Rejected') && selectedStory.adminFeedback && (
                                                    <div className="mt-2 pt-2 border-t border-current/10">
                                                        <span className="block opacity-70 text-[10px] uppercase font-bold mb-0.5">Alasan / Feedback</span>
                                                        <p className="font-medium italic">"{selectedStory.adminFeedback}"</p>
                                                    </div>
                                                )}
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            )}

                            {/* Story Content */}
                            <div className="prose dark:prose-invert max-w-none mb-8">
                                <div className="flex items-center justify-between mb-2">
                                    <h3 className="text-sm font-bold uppercase text-gray-400 flex items-center gap-2">
                                        <FileText size={16} /> Story Content
                                    </h3>
                                    <div className="flex items-center gap-2 text-[10px] font-mono text-gray-500 bg-gray-100 dark:bg-white/5 px-2 py-1 rounded">
                                        <span>{countWords(selectedStory.content)} Words</span>
                                        <span className="w-px h-3 bg-gray-300 dark:bg-white/10"></span>
                                        <span>{countParagraphs(selectedStory.content)} Paras</span>
                                    </div>
                                </div>
                                <div className="p-4 bg-gray-50 dark:bg-[#0a0a0a] rounded-xl border border-gray-200 dark:border-white/10 text-sm leading-relaxed text-gray-800 dark:text-gray-200 whitespace-pre-wrap">
                                    {selectedStory.content}
                                </div>
                            </div>

                            {/* AI Analysis Section (Only for Pending) */}
                            {selectedStory.status === 'Pending' && (
                                <div className="mb-8">
                                    <div className="flex items-center justify-between mb-3">
                                        <h3 className="text-sm font-bold uppercase text-gray-400 flex items-center gap-2">
                                            <ShieldCheck size={16} /> AI Analysis
                                        </h3>
                                        <div className="flex gap-2">
                                            <button 
                                                onClick={handleCheckGrammar}
                                                className="text-xs flex items-center gap-1.5 px-3 py-1.5 bg-blue-600 hover:bg-blue-700 text-white rounded-lg transition-colors"
                                            >
                                                <BookOpen size={12}/> Check Grammar
                                            </button>
                                            <button 
                                                onClick={handleCheckPlagiarism}
                                                disabled={isChecking}
                                                className="text-xs flex items-center gap-1.5 px-3 py-1.5 bg-indigo-600 hover:bg-indigo-700 text-white rounded-lg transition-colors disabled:opacity-50"
                                            >
                                                {isChecking ? <RefreshCw size={12} className="animate-spin"/> : <Search size={12}/>}
                                                {isChecking ? 'Checking...' : 'Check Plagiarism'}
                                            </button>
                                        </div>
                                    </div>

                                    {/* Grammar Check Result Display */}
                                    {grammarCheckResult && (
                                        <div className={`mb-4 p-3 rounded-lg border text-xs ${
                                            grammarCheckResult.isValid 
                                            ? 'bg-green-50 border-green-200 text-green-700' 
                                            : 'bg-orange-50 border-orange-200 text-orange-700'
                                        }`}>
                                            <div className="flex items-start gap-2">
                                                {grammarCheckResult.isValid ? <CheckCircle size={16} /> : <AlertTriangle size={16} />}
                                                <div>
                                                    <span className="font-bold block mb-1">Grammar Check Result:</span>
                                                    {grammarCheckResult.isValid ? (
                                                        <span>No obvious grammar issues found.</span>
                                                    ) : (
                                                        <ul className="list-disc pl-4 space-y-1">
                                                            {grammarCheckResult.errors.map((err, idx) => (
                                                                <li key={idx}>{err}</li>
                                                            ))}
                                                        </ul>
                                                    )}
                                                </div>
                                            </div>
                                        </div>
                                    )}

                                    {selectedStory.plagiarismScore !== undefined ? (
                                        <div className={`p-4 rounded-xl border ${
                                            selectedStory.plagiarismScore > 50 
                                            ? 'bg-red-50 dark:bg-red-900/10 border-red-200 dark:border-red-900/30' 
                                            : 'bg-green-50 dark:bg-green-900/10 border-green-200 dark:border-green-900/30'
                                        }`}>
                                            <div className="flex items-start gap-3">
                                                {selectedStory.plagiarismScore > 50 
                                                    ? <AlertTriangle className="text-red-500 shrink-0" size={20} />
                                                    : <CheckCircle className="text-green-500 shrink-0" size={20} />
                                                }
                                                <div>
                                                    <h4 className={`font-bold text-sm ${selectedStory.plagiarismScore > 50 ? 'text-red-700 dark:text-red-400' : 'text-green-700 dark:text-green-400'}`}>
                                                        {selectedStory.plagiarismScore > 50 ? 'High Similarity Detected' : 'Original Content'}
                                                    </h4>
                                                    <p className="text-xs text-gray-600 dark:text-gray-400 mt-1">
                                                        {selectedStory.plagiarismScore > 50 
                                                            ? `This story shares ${selectedStory.plagiarismScore}% similarity with existing database records.` 
                                                            : "This story appears to be unique and does not match existing records."}
                                                    </p>
                                                    {selectedStory.plagiarismDetails && selectedStory.plagiarismDetails.length > 0 && (
                                                        <div className="mt-3 pt-3 border-t border-red-200 dark:border-red-900/30">
                                                            <p className="text-[10px] uppercase font-bold text-red-500 mb-1">Potential Match:</p>
                                                            {selectedStory.plagiarismDetails.map((match, idx) => (
                                                                <div key={idx} className="flex justify-between text-xs">
                                                                    <span className="font-medium">{match.source}</span>
                                                                    <span className="font-bold">{match.similarity}% Match</span>
                                                                </div>
                                                            ))}
                                                        </div>
                                                    )}
                                                </div>
                                            </div>
                                        </div>
                                    ) : (
                                        <div className="p-8 text-center border-2 border-dashed border-gray-200 dark:border-white/10 rounded-xl">
                                            <p className="text-xs text-gray-400">Run plagiarism check to analyze this story.</p>
                                        </div>
                                    )}
                                </div>
                            )}
                        </div>

                        {/* Action Form - Fixed at bottom (Only for Pending) */}
                        {selectedStory.status === 'Pending' && (
                            <div className="p-3 border-t border-gray-200 dark:border-white/10 bg-gray-50 dark:bg-[#1a1a1a] shrink-0">
                                <div className="mb-2">
                                    <textarea 
                                        value={feedback}
                                        onChange={(e) => setFeedback(e.target.value)}
                                        placeholder="Feedback / Reason (Required for Revision/Reject)..."
                                        className={`w-full bg-white dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-lg p-2 text-xs focus:border-indigo-500 outline-none min-h-[60px] resize-none transition-all ${isShaking ? 'border-red-500 ring-2 ring-red-500 animate-[shake_0.5s_ease-in-out]' : ''}`}
                                    />
                                </div>

                                <div className="grid grid-cols-3 gap-2">
                                    <button 
                                        onClick={() => handleAction('Active')}
                                        className="bg-green-600 hover:bg-green-700 text-white py-2.5 rounded-lg text-[10px] font-bold uppercase tracking-wider flex flex-col md:flex-row items-center justify-center gap-1 md:gap-2 transition-colors shadow-lg shadow-green-600/20"
                                    >
                                        <CheckCircle size={14} /> <span>Approve</span>
                                    </button>
                                    <button 
                                        onClick={() => handleAction('Revision')}
                                        className="bg-orange-500 hover:bg-orange-600 text-white py-2.5 rounded-lg text-[10px] font-bold uppercase tracking-wider flex flex-col md:flex-row items-center justify-center gap-1 md:gap-2 transition-colors shadow-lg shadow-orange-500/20"
                                    >
                                        <RefreshCw size={14} /> <span>Revision</span>
                                    </button>
                                    <button 
                                        onClick={() => handleAction('Rejected')}
                                        className="bg-red-600 hover:bg-red-700 text-white py-2.5 rounded-lg text-[10px] font-bold uppercase tracking-wider flex flex-col md:flex-row items-center justify-center gap-1 md:gap-2 transition-colors shadow-lg shadow-red-600/20"
                                    >
                                        <XCircle size={14} /> <span>Reject</span>
                                    </button>
                                </div>
                            </div>
                        )}
                    </>
                ) : (
                    <div className="flex flex-col items-center justify-center h-full text-gray-400 p-8 text-center">
                        <div className="w-20 h-20 bg-gray-100 dark:bg-white/5 rounded-full flex items-center justify-center mb-4">
                            <BookOpen size={40} className="opacity-50" />
                        </div>
                        <h3 className="text-xl font-bold uppercase tracking-widest mb-2">No Story Selected</h3>
                        <p className="text-sm max-w-xs mx-auto">Select a character story from the list to review content, check plagiarism, and take action.</p>
                    </div>
                )}
            </div>

            {/* CUSTOM ALERT MODAL */}
            {alertState.isOpen && (
                <div className="fixed inset-0 z-[10000] flex items-center justify-center bg-black/50 backdrop-blur-sm p-4 animate-[fadeIn_0.2s_ease-out]">
                    <div className="bg-white dark:bg-[#1a1a1a] rounded-2xl shadow-2xl max-w-sm w-full overflow-hidden border border-gray-200 dark:border-white/10 transform animate-[scaleIn_0.2s_ease-out]">
                        <div className={`p-4 flex items-center gap-3 border-b border-gray-100 dark:border-white/5 ${
                            alertState.type === 'error' ? 'bg-red-50 dark:bg-red-900/20' : 
                            alertState.type === 'success' ? 'bg-green-50 dark:bg-green-900/20' : 
                            'bg-blue-50 dark:bg-blue-900/20'
                        }`}>
                            {alertState.type === 'error' && <AlertTriangle className="text-red-600 dark:text-red-500" size={24} />}
                            {alertState.type === 'success' && <CheckCircle className="text-green-600 dark:text-green-500" size={24} />}
                            {alertState.type === 'info' && <div className="text-blue-600 dark:text-blue-500"><AlertTriangle size={24} /></div>}
                            <h3 className={`font-bold text-lg ${
                                alertState.type === 'error' ? 'text-red-700 dark:text-red-400' : 
                                alertState.type === 'success' ? 'text-green-700 dark:text-green-400' : 
                                'text-blue-700 dark:text-blue-400'
                            }`}>{alertState.title}</h3>
                        </div>
                        <div className="p-6">
                            <p className="text-gray-600 dark:text-gray-300 text-sm leading-relaxed">{alertState.message}</p>
                        </div>
                        <div className="p-4 bg-gray-50 dark:bg-[#151515] flex justify-end">
                            <button 
                                onClick={closeAlert}
                                className="px-6 py-2 bg-gray-900 dark:bg-white text-white dark:text-black rounded-xl font-bold text-sm hover:opacity-90 transition-opacity"
                            >
                                OK, Mengerti
                            </button>
                        </div>
                    </div>
                </div>
            )}
        </div>
    );
};
