import React, { useState, useEffect } from 'react';
import { Search, Loader2, CheckCircle, XCircle, FileEdit, User, Inbox } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

interface DataRequest {
    id: number;
    username: string;
    change_type: string;
    target_information: string;
    old_value: string;
    new_value: string;
    reason: string;
    status: 'Pending' | 'Approved' | 'Rejected';
    admin_feedback: string | null;
    reviewed_by: string | null;
    created_at: string;
}

interface AdminRequestsProps {
    onOocReviewed?: (username: string, type: string, status: string, feedback: string) => void;
}

export const AdminRequests: React.FC<AdminRequestsProps> = ({ onOocReviewed }) => {
    const [requests, setRequests] = useState<DataRequest[]>([]);
    const [loading, setLoading] = useState(true);
    const [searchQuery, setSearchQuery] = useState('');
    const [filter, setFilter] = useState<'All' | 'Pending' | 'Approved' | 'Rejected'>('Pending');
    const [selectedRequest, setSelectedRequest] = useState<DataRequest | null>(null);
    const [adminFeedback, setAdminFeedback] = useState('');
    const [processingAction, setProcessingAction] = useState<string | null>(null);

    const fetchRequests = async () => {
        setLoading(true);
        if (!isPreviewEnv()) {
            try {
                const res = await fetch(`${API_URL}/api_change_requests.php?action=get_requests`);
                const data = await res.json();
                if (data.status === 'success') {
                    setRequests(data.data);
                }
            } catch (err) {
                console.error("Gagal get_requests", err);
            }
        } else {
            // Mock data
            setRequests([
                {
                    id: 1,
                    username: 'user_budi',
                    change_type: 'Ganti Nama Asli (OOC)',
                    target_information: 'Nama Asli',
                    old_value: 'Budi Santoso',
                    new_value: 'Budi Susanto',
                    reason: 'Ada kesalahan pengetikan nama asli saat mendaftar UCP',
                    status: 'Pending',
                    admin_feedback: null,
                    reviewed_by: null,
                    created_at: new Date().toISOString()
                }
            ]);
        }
        setLoading(false);
    };

    useEffect(() => {
        fetchRequests();
    }, []);

    const handleAction = async (status: 'Approved' | 'Rejected') => {
        if (!selectedRequest) return;
        setProcessingAction(status);

        if (!isPreviewEnv()) {
            try {
                const res = await fetch(`${API_URL}/api_change_requests.php`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        action: 'process_request',
                        id: selectedRequest.id,
                        status: status,
                        adminFeedback: adminFeedback
                    })
                });
                const data = await res.json();
                if (data.status === 'success') {
                    setRequests(prev => prev.map(r => r.id === selectedRequest.id ? { ...r, status, admin_feedback: adminFeedback, reviewed_by: 'Admin System' } : r));
                    setSelectedRequest(null);
                    setAdminFeedback('');
                    alert("Pengajuan berhasil diproses.");
                } else {
                    alert("Gagal: " + data.message);
                }
            } catch (err) {
                alert("Kesalahan koneksi.");
            }
        } else {
            setTimeout(() => {
                setRequests(prev => prev.map(r => r.id === selectedRequest.id ? { ...r, status, admin_feedback: adminFeedback, reviewed_by: 'Admin Preview' } : r));
                if (onOocReviewed) {
                    onOocReviewed(
                        selectedRequest.username, 
                        selectedRequest.change_type, 
                        status === 'Approved' ? 'Diizinkan' : 'Ditolak', 
                        adminFeedback || 'Tidak ada catatan khusus.'
                    );
                }
                setSelectedRequest(null);
                setAdminFeedback('');
            }, 1000);
        }
        setProcessingAction(null);
    };

    const filteredRequests = requests.filter(r => {
        const matchesFilter = filter === 'All' || r.status === filter;
        const matchesSearch = r.username.toLowerCase().includes(searchQuery.toLowerCase()) || r.target_information.toLowerCase().includes(searchQuery.toLowerCase());
        return matchesFilter && matchesSearch;
    });

    return (
        <div className="flex flex-col h-full animate-[fadeIn_0.5s_ease-out]">
            <div className="mb-6 flex flex-col md:flex-row md:items-center justify-between gap-4">
                <div>
                    <h2 className="text-2xl font-bold text-gray-900 dark:text-white flex items-center gap-2">
                        <FileEdit className="text-blue-500" />
                        Pengajuan Perubahan Data
                    </h2>
                    <p className="text-sm text-gray-500 dark:text-gray-400 mt-1">
                        Verifikasi permintaan player untuk merubah Informasi Pribadi (OOC) seperti nama asli, gender, tanggal lahir, dll.
                    </p>
                </div>
            </div>

            <div className="flex flex-col lg:flex-row gap-6 flex-1 min-h-0">
                {/* Left Area - Request List */}
                <div className="lg:w-1/3 flex flex-col bg-white dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 rounded-2xl shadow-sm overflow-hidden">
                    <div className="p-4 border-b border-gray-200 dark:border-white/10 space-y-4">
                        <div className="relative">
                            <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={16} />
                            <input 
                                type="text"
                                placeholder="Cari UCP atau Nama..."
                                value={searchQuery}
                                onChange={(e) => setSearchQuery(e.target.value)}
                                className="w-full pl-9 pr-4 py-2 bg-gray-50 dark:bg-white/5 border border-gray-200 dark:border-white/10 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white transition-all outline-none"
                            />
                        </div>
                        <div className="flex gap-2">
                            {['Pending', 'Approved', 'Rejected', 'All'].map(f => (
                                <button
                                    key={f}
                                    onClick={() => setFilter(f as any)}
                                    className={`px-3 py-1.5 rounded-lg text-xs font-bold transition-colors ${
                                        filter === f 
                                        ? 'bg-blue-500 text-white' 
                                        : 'bg-gray-100 dark:bg-white/5 text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10'
                                    }`}
                                >
                                    {f}
                                </button>
                            ))}
                        </div>
                    </div>

                    <div className="flex-1 overflow-y-auto p-2 space-y-2 custom-scrollbar">
                        {loading && requests.length === 0 ? (
                            <div className="flex justify-center p-8 text-gray-400">
                                <Loader2 size={24} className="animate-spin" />
                            </div>
                        ) : filteredRequests.length === 0 ? (
                            <div className="text-center p-8 text-gray-500 dark:text-gray-400 flex flex-col items-center">
                                <Inbox size={32} className="opacity-20 mb-3" />
                                <p className="text-sm">Tidak ada pengajuan ditemukan.</p>
                            </div>
                        ) : (
                            filteredRequests.map(req => (
                                <button
                                    key={req.id}
                                    onClick={() => setSelectedRequest(req)}
                                    className={`w-full text-left p-4 rounded-xl border transition-all ${
                                        selectedRequest?.id === req.id
                                        ? 'bg-blue-50 dark:bg-blue-900/20 border-blue-200 dark:border-blue-800'
                                        : 'bg-white dark:bg-transparent border-transparent hover:bg-gray-50 dark:hover:bg-white/5'
                                    }`}
                                >
                                    <div className="flex justify-between items-start mb-2">
                                        <span className="font-bold text-gray-900 dark:text-white text-sm">{req.target_information}</span>
                                        <span className={`text-[10px] uppercase tracking-wider font-bold px-2 py-1 rounded-md ${
                                            req.status === 'Pending' ? 'bg-yellow-100 text-yellow-700 dark:bg-yellow-900/30 dark:text-yellow-400' :
                                            req.status === 'Approved' ? 'bg-green-100 text-green-700 dark:bg-green-900/30 dark:text-green-400' :
                                            'bg-red-100 text-red-700 dark:bg-red-900/30 dark:text-red-400'
                                        }`}>
                                            {req.status}
                                        </span>
                                    </div>
                                    <div className="text-xs text-blue-600 dark:text-blue-400 font-medium mb-1">{req.change_type}</div>
                                    <div className="text-xs text-gray-500 dark:text-gray-400">UCP: {req.username}</div>
                                </button>
                            ))
                        )}
                    </div>
                </div>

                {/* Right Area - Detail */}
                <div className="lg:w-2/3 bg-white dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 rounded-2xl shadow-sm flex flex-col overflow-hidden">
                    {selectedRequest ? (
                        <div className="flex flex-col h-full">
                            <div className="p-6 border-b border-gray-200 dark:border-white/10 flex-shrink-0">
                                <div className="flex items-center gap-3 mb-1">
                                    <h3 className="text-xl font-bold text-gray-900 dark:text-white uppercase tracking-tight">{selectedRequest.change_type}</h3>
                                </div>
                                <div className="text-sm text-gray-500 dark:text-gray-400 flex items-center gap-2">
                                    <User size={14} /> {selectedRequest.username} | Tanggal: {new Date(selectedRequest.created_at).toLocaleDateString()}
                                </div>
                            </div>
                            
                            <div className="flex-1 p-6 overflow-y-auto space-y-6 custom-scrollbar">
                                <div className="grid grid-cols-2 gap-4">
                                    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-xl border border-gray-200 dark:border-white/10">
                                        <div className="text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-wider mb-2">Data Lama</div>
                                        <div className="font-mono text-gray-900 dark:text-gray-300 line-through opacity-70">
                                            {selectedRequest.old_value || '-'}
                                        </div>
                                    </div>
                                    <div className="bg-blue-50 dark:bg-blue-900/10 p-4 rounded-xl border border-blue-200 dark:border-blue-800/30">
                                        <div className="text-xs font-bold text-blue-600 dark:text-blue-400 uppercase tracking-wider mb-2">Data Baru</div>
                                        <div className="font-mono text-gray-900 dark:text-white font-bold">
                                            {selectedRequest.new_value}
                                        </div>
                                    </div>
                                </div>

                                <div>
                                    <h4 className="text-sm font-bold text-gray-900 dark:text-white mb-2">Alasan Pengajuan</h4>
                                    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-xl border border-gray-200 dark:border-white/10 text-sm text-gray-700 dark:text-gray-300 italic whitespace-pre-wrap">
                                        "{selectedRequest.reason}"
                                    </div>
                                </div>

                                {selectedRequest.status !== 'Pending' && (
                                    <div className="pt-4 border-t border-gray-200 dark:border-white/10">
                                        <h4 className="text-sm font-bold text-gray-900 dark:text-white mb-2">Tanggapan Admin ({selectedRequest.reviewed_by})</h4>
                                        <div className="p-4 rounded-xl border border-gray-200 dark:border-white/10 text-sm text-gray-700 dark:text-gray-300">
                                            {selectedRequest.admin_feedback || 'Tanpa catatan khusus.'}
                                        </div>
                                    </div>
                                )}
                            </div>

                            {selectedRequest.status === 'Pending' && (
                                <div className="p-6 bg-gray-50 dark:bg-ph-surface-input border-t border-gray-200 dark:border-white/10 flex-shrink-0">
                                    <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 mb-2">Pesan Konfirmasi / Tolak</label>
                                    <textarea 
                                        rows={3}
                                        value={adminFeedback}
                                        onChange={(e) => setAdminFeedback(e.target.value)}
                                        placeholder="Berikan alasan kenapa pengajuan diterima/ditolak..."
                                        className="w-full bg-white dark:bg-ph-surface-panel border border-gray-300 dark:border-white/10 text-gray-900 dark:text-white rounded-xl px-4 py-3 text-sm focus:ring-2 focus:ring-blue-500 outline-none resize-none mb-4"
                                    ></textarea>
                                    
                                    <div className="flex gap-3">
                                        <button 
                                            onClick={() => handleAction('Approved')}
                                            disabled={processingAction !== null}
                                            className="flex-1 py-3 bg-green-600 hover:bg-green-700 text-white rounded-xl text-sm font-bold uppercase tracking-wider flex items-center justify-center gap-2 transition-colors disabled:opacity-50"
                                        >
                                            {processingAction === 'Approved' ? <Loader2 size={18} className="animate-spin" /> : <CheckCircle size={18} />}
                                            Setujui
                                        </button>
                                        <button 
                                            onClick={() => handleAction('Rejected')}
                                            disabled={processingAction !== null}
                                            className="flex-1 py-3 bg-red-600 hover:bg-red-700 text-white rounded-xl text-sm font-bold uppercase tracking-wider flex items-center justify-center gap-2 transition-colors disabled:opacity-50"
                                        >
                                            {processingAction === 'Rejected' ? <Loader2 size={18} className="animate-spin" /> : <XCircle size={18} />}
                                            Tolak
                                        </button>
                                    </div>
                                </div>
                            )}
                        </div>
                    ) : (
                        <div className="flex-1 flex flex-col items-center justify-center text-gray-400 p-8 text-center">
                            <FileEdit size={64} className="opacity-20 mb-4" />
                            <h3 className="text-xl font-bold text-gray-900 dark:text-white mb-2">Pilih Pengajuan</h3>
                            <p className="text-sm max-w-md">Silakan pilih item pengajuan di panel sebelah kiri untuk melihat detail atau memberikan persetujuan.</p>
                        </div>
                    )}
                </div>
            </div>
        </div>
    );
};
