import React, { useState } from 'react';
import { FileEdit, X, Check, Loader2, AlertCircle } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';
import { CustomSelect } from './CustomSelect';

interface DataRequestCardProps {
    userName: string;
}

export const DataRequestCard: React.FC<DataRequestCardProps> = ({ userName }) => {
    const [isHovered, setIsHovered] = useState(false);
    const [isModalOpen, setIsModalOpen] = useState(false);
    const [loading, setLoading] = useState(false);
    const [message, setMessage] = useState<{ text: string, type: 'success' | 'error' } | null>(null);

    const [form, setForm] = useState({
        changeType: 'Ganti Nama Asli (OOC)',
        targetInfo: '',
        oldValue: '',
        newValue: '',
        reason: ''
    });

    const handleSubmit = async (e: React.FormEvent) => {
        e.preventDefault();
        setLoading(true);
        setMessage(null);

        if (isPreviewEnv()) {
            setTimeout(() => {
                setLoading(false);
                setMessage({ text: "Pengajuan berhasil dikirim (Preview).", type: "success" });
                setTimeout(() => setIsModalOpen(false), 2000);
            }, 1000);
            return;
        }

        try {
            const res = await fetch(`${API_URL}/api_change_requests.php`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    action: 'submit_request',
                    username: userName,
                    changeType: form.changeType,
                    targetInfo: form.targetInfo,
                    oldValue: form.oldValue,
                    newValue: form.newValue,
                    reason: form.reason
                })
            });

            const data = await res.json();
            if (data.status === 'success') {
                setMessage({ text: data.message, type: "success" });
                setForm({ changeType: 'Ganti Nama Asli (OOC)', targetInfo: '', oldValue: '', newValue: '', reason: '' });
                setTimeout(() => {
                    setIsModalOpen(false);
                    setMessage(null);
                }, 2000);
            } else {
                setMessage({ text: data.message, type: "error" });
            }
        } catch (error) {
            setMessage({ text: "Gagal terhubung ke server.", type: "error" });
        } finally {
            setLoading(false);
        }
    };

    return (
        <>
            <div 
                className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 p-6 md:p-8 rounded-2xl md:rounded-3xl relative overflow-hidden group transition-all duration-500"
                onMouseEnter={() => setIsHovered(true)}
                onMouseLeave={() => setIsHovered(false)}
            >
                {/* Subtle glow effect */}
                <div className="absolute -top-10 -right-10 w-40 h-40 bg-blue-500/20 rounded-full blur-[50px] opacity-0 group-hover:opacity-100 transition-opacity duration-700 pointer-events-none"></div>

                <div className="relative z-10 flex flex-col md:flex-row md:items-center justify-between gap-6">
                    {/* Left Icon & Title */}
                    <div className="flex items-center gap-4 shrink-0 max-w-sm">
                        <div className="w-12 h-12 md:w-16 md:h-16 rounded-2xl flex items-center justify-center border shadow-inner bg-blue-500/10 text-blue-500 border-blue-500/20">
                            <FileEdit size={28} className="md:w-8 md:h-8 w-6 h-6" />
                        </div>
                        <div>
                            <h3 className="text-lg md:text-xl font-black text-gray-900 dark:text-white uppercase tracking-tight">Layanan UCP</h3>
                            <p className="text-gray-500 text-[10px] md:text-xs mt-1 md:mt-1.5 font-medium">Perubahan Data</p>
                        </div>
                    </div>

                    {/* Middle Text Description */}
                    <div className="flex-1 md:px-8 border-t md:border-t-0 md:border-l border-gray-200 dark:border-white/10 pt-4 md:pt-0">
                        <p className="text-[10px] md:text-xs text-gray-500 dark:text-gray-400 leading-relaxed font-medium">
                            Ajukan perubahan data Informasi Pribadi (OOC) seperti Nama Asli, Tanggal Lahir, atau Gender ke Staff. Proses ini membutuhkan review dari Administrator.
                        </p>
                    </div>

                    {/* Right Action Button */}
                    <div className="shrink-0 w-full md:w-auto">
                        <button 
                            onClick={() => setIsModalOpen(true)}
                            className="w-full md:w-auto px-8 bg-ph-surface-panel hover:bg-ph-surface-elevated border border-ph-border-default text-white py-3.5 rounded-xl text-[10px] md:text-xs font-bold uppercase tracking-widest transition-all transform hover:-translate-y-0.5 active:translate-y-0 flex items-center justify-center gap-2 whitespace-nowrap"
                        >
                            <FileEdit size={14} /> Buat Pengajuan
                        </button>
                    </div>
                </div>
            </div>

            {/* Modal */}
            {isModalOpen && (
                <div className="fixed inset-0 z-50 flex items-center justify-center bg-black/60 p-4 backdrop-blur-sm">
                    <div className="bg-white dark:bg-ph-surface-card w-full max-w-lg rounded-2xl shadow-2xl border border-gray-200 dark:border-white/10 overflow-hidden flex flex-col max-h-[90vh]">
                        <div className="p-4 border-b border-gray-200 dark:border-white/10 flex justify-between items-center bg-gray-50 dark:bg-ph-surface-panel">
                            <h3 className="font-bold text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-2">
                                <FileEdit size={18} className="text-blue-500" /> Form Pengajuan
                            </h3>
                            <button onClick={() => setIsModalOpen(false)} className="text-gray-400 hover:text-red-500 transition-colors">
                                <X size={20} />
                            </button>
                        </div>
                        
                        <div className="p-6 overflow-y-auto">
                            {message && (
                                <div className={`mb-4 p-3 rounded-lg flex items-start gap-2 text-sm ${message.type === 'success' ? 'bg-green-50 text-green-700 border border-green-200 dark:bg-green-900/20 dark:text-green-400 dark:border-green-800' : 'bg-red-50 text-red-700 border border-red-200 dark:bg-red-900/20 dark:text-red-400 dark:border-red-800'}`}>
                                    {message.type === 'success' ? <Check size={16} className="mt-0.5" /> : <AlertCircle size={16} className="mt-0.5" />}
                                    <p>{message.text}</p>
                                </div>
                            )}

                            <form onSubmit={handleSubmit} className="space-y-4">
                                <div>
                                    <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 mb-1 z-10">Jenis Perubahan</label>
                                    <CustomSelect 
                                        value={form.changeType}
                                        onChange={(value) => setForm({...form, changeType: value})}
                                        placeholder="Pilih jenis perubahan..."
                                        options={[
                                            { value: 'Ganti Nama Asli (OOC)', label: 'Ganti Nama Asli (OOC)' },
                                            { value: 'Ganti Tanggal Lahir (OOC)', label: 'Ganti Tanggal Lahir (OOC)' },
                                            { value: 'Ganti Gender (OOC)', label: 'Ganti Gender (OOC)' },
                                            { value: 'Ganti Alamat (OOC)', label: 'Ganti Alamat (OOC)' },
                                            { value: 'Ganti Nomor Telepon (OOC)', label: 'Ganti Nomor Telepon (OOC)' },
                                            { value: 'Ganti Discord ID (OOC)', label: 'Ganti Discord ID (OOC)' },
                                            { value: 'Lainnya (OOC)', label: 'Lainnya (OOC)' }
                                        ]}
                                    />
                                </div>

                                <div>
                                    <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 mb-1">Target Informasi</label>
                                    <input 
                                        type="text" 
                                        placeholder="Cth: Udin Samsudin (Nama Asli)"
                                        value={form.targetInfo}
                                        onChange={e => setForm({...form, targetInfo: e.target.value})}
                                        className="w-full bg-gray-50 dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 text-gray-900 dark:text-white rounded-lg px-3 py-2 text-sm focus:ring-2 focus:ring-blue-500 outline-none"
                                        required
                                    />
                                </div>

                                <div className="grid grid-cols-2 gap-4">
                                    <div>
                                        <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 mb-1">Data Lama</label>
                                        <input 
                                            type="text" 
                                            value={form.oldValue}
                                            onChange={e => setForm({...form, oldValue: e.target.value})}
                                            className="w-full bg-gray-50 dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 text-gray-900 dark:text-white rounded-lg px-3 py-2 text-sm focus:ring-2 focus:ring-blue-500 outline-none"
                                        />
                                    </div>
                                    <div>
                                        <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 mb-1">Data Baru</label>
                                        <input 
                                            type="text" 
                                            value={form.newValue}
                                            onChange={e => setForm({...form, newValue: e.target.value})}
                                            className="w-full bg-gray-50 dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 text-gray-900 dark:text-white rounded-lg px-3 py-2 text-sm focus:ring-2 focus:ring-blue-500 outline-none"
                                            required
                                        />
                                    </div>
                                </div>

                                <div>
                                    <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 mb-1">Alasan Perubahan</label>
                                    <textarea 
                                        rows={4}
                                        placeholder="Jelaskan alasan pengajuan perubahan (cth: mendaftar faction, typo, dsb.)"
                                        value={form.reason}
                                        onChange={e => setForm({...form, reason: e.target.value})}
                                        className="w-full bg-gray-50 dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 text-gray-900 dark:text-white rounded-lg px-3 py-2 text-sm focus:ring-2 focus:ring-blue-500 outline-none resize-none"
                                        required
                                    ></textarea>
                                </div>

                                <div className="pt-2">
                                    <button 
                                        type="submit"
                                        disabled={loading}
                                        className="w-full py-3 bg-blue-600 hover:bg-blue-700 text-white rounded-xl text-sm font-bold uppercase tracking-wider transition-colors flex items-center justify-center gap-2 disabled:opacity-50 disabled:cursor-not-allowed"
                                    >
                                        {loading ? <Loader2 size={18} className="animate-spin" /> : <Check size={18} />}
                                        Kirim Pengajuan
                                    </button>
                                </div>
                            </form>
                        </div>
                    </div>
                </div>
            )}
        </>
    );
};
