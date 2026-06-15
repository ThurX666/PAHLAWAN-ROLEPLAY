import React, { useState } from 'react';
import { Send, Target, AlertCircle } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

interface AdminBroadcastProps {
    onSendNotification?: (msg: any) => void;
}

export const AdminBroadcast: React.FC<AdminBroadcastProps> = ({ onSendNotification }) => {
    const [targetType, setTargetType] = useState<'All' | 'Single'>('Single');
    const [targetUser, setTargetUser] = useState('');
    const [msgType, setMsgType] = useState<'Admin' | 'Voucher'>('Admin');
    const [title, setTitle] = useState('');
    const [message, setMessage] = useState('');
    const [voucherCode, setVoucherCode] = useState('');
    const [itemName, setItemName] = useState('');
    const [itemDescription, setItemDescription] = useState('');
    const [itemPrice, setItemPrice] = useState('');
    const [loading, setLoading] = useState(false);

    const handleSend = async (e: React.FormEvent) => {
        e.preventDefault();
        
        if (targetType === 'Single' && !targetUser.trim()) {
            alert('Username target harus diisi.');
            return;
        }

        if (!title.trim() || !message.trim()) {
            alert('Judul dan Pesan harus diisi.');
            return;
        }

        if (msgType === 'Voucher' && !voucherCode.trim()) {
            alert('Kode Voucher harus diisi untuk pesan tipe Voucher.');
            return;
        }

        if (confirm(`Kirim pesan ini ke ${targetType === 'All' ? 'Semua Pemain' : targetUser}?`)) {
            setLoading(true);

            if (isPreviewEnv()) {
                setTimeout(() => {
                    setLoading(false);
                    if (onSendNotification && targetType === 'Single') {
                         onSendNotification({
                             id: `msg-custom-${Date.now()}`,
                             title: title,
                             message: message,
                             type: msgType,
                             date: new Date().toISOString(),
                             targetUsername: targetUser,
                             read: false,
                             code: msgType === 'Voucher' ? voucherCode : undefined,
                             itemName: msgType === 'Voucher' ? itemName : undefined,
                             itemDescription: msgType === 'Voucher' ? itemDescription : undefined,
                             itemPrice: msgType === 'Voucher' ? parseInt(itemPrice) || 0 : undefined,
                         });
                    }
                    alert('Pesan berhasil dikirim (Preview).');
                }, 1000);
                return;
            }

            try {
                const res = await fetch(`${API_URL}/api_inbox.php`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        action: targetType === 'All' ? 'broadcast_message' : 'send_message',
                        username: targetUser,
                        title: title,
                        message: message,
                        type: msgType,
                        code: msgType === 'Voucher' ? voucherCode : undefined,
                        itemName: msgType === 'Voucher' ? itemName : undefined,
                        itemDescription: msgType === 'Voucher' ? itemDescription : undefined,
                        itemPrice: msgType === 'Voucher' ? parseInt(itemPrice) || null : undefined,
                    })
                });
                const data = await res.json();
                if (data && data.status === 'success') {
                     alert(targetType === 'All' ? 'Pesan broadcast berhasil dikirim (antrian).' : 'Pesan berhasil dikirim.');
                     if (targetType === 'Single') setTargetUser('');
                     setTitle('');
                     setMessage('');
                     setVoucherCode('');
                     setItemName('');
                     setItemDescription('');
                     setItemPrice('');
                } else {
                     alert(data.message || 'Gagal mengirim pesan.');
                }
            } catch (err) {
                 console.error(err);
                 alert('Kesalahan jaringan.');
            } finally {
                 setLoading(false);
            }
        }
    };

    return (
        <div className="animate-[fadeIn_0.3s_ease-out]">
            <div className="bg-white dark:bg-[#0a0a0a] rounded-xl border border-gray-200 dark:border-white/5 overflow-hidden shadow-sm">
                <div className="p-4 border-b border-gray-200 dark:border-white/5">
                    <h3 className="font-bold text-gray-900 dark:text-white uppercase text-sm flex items-center gap-2">
                        <Send size={16} className="text-red-500"/> Kirim Pesan Custom
                    </h3>
                </div>
                
                <form onSubmit={handleSend} className="p-4 md:p-6 space-y-4">
                    <div className="bg-yellow-50 dark:bg-yellow-900/10 border border-yellow-200 dark:border-yellow-900/30 rounded-lg p-3 flex gap-3 text-yellow-800 dark:text-yellow-200 text-xs md:text-sm">
                        <AlertCircle className="shrink-0 mt-0.5" size={16} />
                        <p>Pesan ini akan dikirim langsung ke UCP Inbox target. Mendukung tag HTML sederhana seperti &lt;strong&gt;, &lt;br&gt;, &lt;span style="..."&gt; di dalam body pesan.</p>
                    </div>

                    <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                        <div>
                            <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase mb-1">Target</label>
                            <div className="flex gap-2">
                                <select 
                                    value={targetType}
                                    onChange={(e) => setTargetType(e.target.value as 'All' | 'Single')}
                                    className="bg-gray-50 dark:bg-[#121212] flex-none border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors"
                                >
                                    <option value="Single">Pemain Spesifik</option>
                                    <option value="All">Semua Pemain (Broadcast)</option>
                                </select>
                                {targetType === 'Single' && (
                                    <div className="relative flex-1">
                                        <Target size={14} className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-500" />
                                        <input 
                                            type="text" 
                                            value={targetUser}
                                            onChange={(e) => setTargetUser(e.target.value)}
                                            placeholder="Username UCP..."
                                            className="w-full bg-gray-50 dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg pl-8 pr-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors"
                                        />
                                    </div>
                                )}
                            </div>
                        </div>

                        <div>
                            <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase mb-1">Tipe Pesan</label>
                            <select 
                                value={msgType}
                                onChange={(e) => setMsgType(e.target.value as 'Admin' | 'Voucher')}
                                className="w-full bg-gray-50 dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors"
                            >
                                <option value="Admin">Admin</option>
                                <option value="Voucher">Voucher</option>
                            </select>
                        </div>
                    </div>

                    <div>
                        <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase mb-1">Judul Pesan</label>
                        <input 
                            type="text" 
                            value={title}
                            onChange={(e) => setTitle(e.target.value)}
                            placeholder="Contoh: Pemberitahuan Penting / Hadiah Spesial"
                            className="w-full bg-gray-50 dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors"
                        />
                    </div>

                    <div>
                        <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase mb-1">Isi Pesan (Mendukung HTML)</label>
                        <textarea 
                            value={message}
                            onChange={(e) => setMessage(e.target.value)}
                            placeholder="Tulis pesan lengkap di sini..."
                            className="w-full bg-gray-50 dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors min-h-[150px] font-mono text-xs"
                        />
                    </div>

                    {msgType === 'Voucher' && (
                        <div className="bg-blue-50 dark:bg-blue-900/5 p-4 rounded-xl border border-blue-100 dark:border-blue-900/20 space-y-4">
                            <h4 className="text-xs font-bold text-blue-800 dark:text-blue-400 uppercase">Detail Voucher</h4>
                            <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                                <div>
                                    <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Kode Voucher</label>
                                    <input 
                                        type="text" 
                                        value={voucherCode}
                                        onChange={(e) => setVoucherCode(e.target.value)}
                                        placeholder="Contoh: FREE-INF-2026"
                                        className="w-full bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-blue-500 font-mono tracking-wider transition-colors"
                                    />
                                </div>
                                <div>
                                    <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Nama Item</label>
                                    <input 
                                        type="text" 
                                        value={itemName}
                                        onChange={(e) => setItemName(e.target.value)}
                                        placeholder="Contoh: Infernus / Gold Coin"
                                        className="w-full bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-blue-500 transition-colors"
                                    />
                                </div>
                                <div>
                                    <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Harga (Opsional)</label>
                                    <input 
                                        type="number" 
                                        value={itemPrice}
                                        onChange={(e) => setItemPrice(e.target.value)}
                                        placeholder="Nilai dalam GC"
                                        className="w-full bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-blue-500 transition-colors"
                                    />
                                </div>
                                <div>
                                    <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Deskripsi Item (Opsional)</label>
                                    <input 
                                        type="text" 
                                        value={itemDescription}
                                        onChange={(e) => setItemDescription(e.target.value)}
                                        placeholder="Penjelasan singkat item"
                                        className="w-full bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-lg px-3 py-2 text-sm text-gray-900 dark:text-white outline-none focus:border-blue-500 transition-colors"
                                    />
                                </div>
                            </div>
                        </div>
                    )}

                    <div className="pt-2">
                        <button 
                            type="submit" 
                            disabled={loading}
                            className="bg-red-600 hover:bg-red-700 text-white px-6 py-2 rounded-lg font-bold uppercase text-xs tracking-wider transition-colors disabled:opacity-50 disabled:cursor-not-allowed flex items-center gap-2"
                        >
                            {loading ? (
                                <><span className="w-4 h-4 rounded-full border-2 border-white/30 border-t-white animate-spin"></span> Mengirim...</>
                            ) : (
                                <><Send size={14} /> Kirim Pesan</>
                            )}
                        </button>
                    </div>
                </form>
            </div>
        </div>
    );
};
