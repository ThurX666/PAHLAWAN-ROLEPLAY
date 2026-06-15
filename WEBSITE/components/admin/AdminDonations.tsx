
import React, { useState, useMemo, useEffect } from 'react';
import { CreditCard, Search, Edit, PackageCheck, CheckCircle2, X } from 'lucide-react';
import { PromoItem, InboxMessage } from '../../types';
import { INITIAL_ADMIN_TRANSACTIONS } from '../../data/mockData';
import { PromoConfigCard } from './donations/PromoConfigCard';
import { LimitedItemManager } from './donations/LimitedItemManager';
import { TopUpProcessor } from './donations/TopUpProcessor';
import { getDonationProofUrl } from '../../utils/imageUtils';
import { isPreviewEnv, API_URL } from '../../config';

interface AdminDonationsProps {
  promoConfig?: { isActive: boolean; title: string; message: string; };
  onUpdatePromo?: (config: any) => void;
  promoItems?: PromoItem[];
  onUpdatePromoItems?: React.Dispatch<React.SetStateAction<PromoItem[]>>;
  onSendNotification?: (msg: InboxMessage) => void;
}

interface AdminTransaction {
  id: string;
  player: string;
  senderName?: string; // Added: Nama Pengirim
  item: string;
  quantity?: number; // Added: Jumlah Item/Gold
  amount: string; // Harga Paket
  total_transfer?: string; // Added: Total Transfer (Gross)
  fee_info?: string; // Added: Biaya Admin / Rate Convert
  method: string;
  status: 'Pending' | 'Success' | 'Rejected';
  date: string;
  proofImage?: string;
}

export const AdminDonations: React.FC<AdminDonationsProps> = ({ promoConfig, onUpdatePromo, promoItems = [], onUpdatePromoItems, onSendNotification }) => {
  const [transactions, setTransactions] = useState<AdminTransaction[]>(INITIAL_ADMIN_TRANSACTIONS as AdminTransaction[]);
  const [donationSearch, setDonationSearch] = useState('');
  const [donationFilter, setDonationFilter] = useState<'All' | 'Pending' | 'Success' | 'Rejected'>('All');
  const [editingTxId, setEditingTxId] = useState<string | null>(null);
  const [tempPromo, setTempPromo] = useState(promoConfig || { isActive: false, title: '', message: '' });

  // New States for Top Up Processor
  const [isProcessorOpen, setIsProcessorOpen] = useState(false);
  const [selectedTxForProcessing, setSelectedTxForProcessing] = useState<AdminTransaction | null>(null);

  // New State for Invoice Detail Modal
  const [selectedInvoice, setSelectedInvoice] = useState<AdminTransaction | null>(null);

  useEffect(() => {
      if (isPreviewEnv()) {
          const storedTrx = localStorage.getItem('mock_transactions');
          if (storedTrx) {
              try {
                  const parsed = JSON.parse(storedTrx);
                  if (parsed && parsed.length > 0) {
                      setTransactions(parsed);
                  }
              } catch (e) {}
          }
      } else {
          fetchTransactions();
      }
  }, []);

  const fetchTransactions = async () => {
      try {
          const res = await fetch(`${API_URL}/api_admin_donations.php?action=get_donations`);
          if (res.ok) {
              const data = await res.json();
              if (data && Array.isArray(data)) {
                  const formatted = data.map((item: any) => ({
                      id: item.id.toString(),
                      player: item.account,
                      senderName: item.sender_name,
                      item: item.item_name,
                      quantity: item.quantity,
                      amount: item.amount,
                      total_transfer: item.total_transfer,
                      fee_info: item.fee_info,
                      method: item.payment_method,
                      status: item.status,
                      date: item.created_at,
                      proofImage: item.proof_image ? item.proof_image : undefined
                  }));
                  setTransactions(formatted);
              }
          }
      } catch (error) {
          console.error("Failed to fetch transactions:", error);
      }
  };

  const handleUpdateStatus = async (id: string, newStatus: 'Pending' | 'Success' | 'Rejected') => {
      if(confirm(`Ubah status invoice ${id} menjadi ${newStatus}?`)) {
          if (isPreviewEnv()) {
              const updated = transactions.map(tx => tx.id === id ? { ...tx, status: newStatus } : tx);
              setTransactions(updated);
              localStorage.setItem('mock_transactions', JSON.stringify(updated));
              setEditingTxId(null);
              
              if(onSendNotification) {
                  const tx = transactions.find(t => t.id === id);
                  if (tx) {
                      const statusDisplay = newStatus === 'Success' ? 'Berhasil' : (newStatus === 'Rejected' ? 'Ditolak' : 'Menunggu');
                      const newMsg: any = {
                          id: `msg-${Date.now()}`,
                          title: `Status Donasi Diperbarui: ${statusDisplay}`,
                          type: 'System',
                          date: new Date().toISOString(),
                          targetUsername: tx.username, // so App.tsx knows who exactly
                          read: false,
                          template: 'PaymentProcessed',
                          metadata: {
                              transactionId: `#DON-${id}`,
                              itemName: tx.item,
                              amount: tx.amount,
                              status: statusDisplay
                          }
                      };
                      onSendNotification(newMsg);
                  }
              }
          } else {
              try {
                  const res = await fetch(`${API_URL}/api_admin_donations.php`, {
                      method: 'POST',
                      headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                      body: new URLSearchParams({ action: 'update_status', id: id, status: newStatus })
                  });
                  const result = await res.json();
                  if (result.status === 'success') {
                      fetchTransactions();
                      setEditingTxId(null);
                  } else {
                      alert('Gagal update status: ' + result.message);
                  }
              } catch (error) {
                  console.error('Error updating status:', error);
                  alert('Terjadi kesalahan koneksi.');
              }
          }
      }
  };
  
  const openProcessor = (tx: AdminTransaction | null) => {
      setSelectedTxForProcessing(tx);
      setIsProcessorOpen(true);
  };

  const handleTopUpComplete = async (generatedCode: string) => {
      if(!selectedTxForProcessing) return;
      
      if (isPreviewEnv()) {
          const updated = transactions.map(tx => tx.id === selectedTxForProcessing.id ? { ...tx, status: 'Success' } : tx);
          setTransactions(updated);
          localStorage.setItem('mock_transactions', JSON.stringify(updated));
          
          if(onSendNotification) {
             const newMsgTemplate: any = {
                 id: `msg-${Date.now()}-tpl`,
                 title: `Status Donasi Diperbarui: Berhasil`,
                 type: 'System',
                 date: new Date().toISOString(),
                 targetUsername: selectedTxForProcessing.username, 
                 read: false,
                 template: 'PaymentProcessed',
                 metadata: {
                     transactionId: `#DON-${selectedTxForProcessing.id}`,
                     itemName: selectedTxForProcessing.item,
                     amount: selectedTxForProcessing.amount,
                     status: 'Berhasil'
                 }
             };
             onSendNotification(newMsgTemplate);
          }
      } else {
          try {
              const res = await fetch(`${API_URL}/api_admin_donations.php`, {
                  method: 'POST',
                  headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
                  body: new URLSearchParams({ action: 'update_status', id: selectedTxForProcessing.id, status: 'Success' })
              });
              if(res.ok) fetchTransactions();
          } catch(e) {}
      }

      // Send Notification with Voucher to Player
      if(onSendNotification) {
          const newMsg: any = {
              id: Date.now().toString(),
              title: "Top Up Berhasil - Kode Voucher",
              message: `Terima kasih! Donasi untuk ${selectedTxForProcessing.item} telah diproses. Silakan gunakan kode voucher di bawah ini di dalam game (/redeem).`,
              type: 'Voucher',
              code: generatedCode,
              date: new Date().toISOString(),
              targetUsername: selectedTxForProcessing.username,
              read: false
          };
          onSendNotification(newMsg);
      }
      
      setIsProcessorOpen(false);
      setSelectedTxForProcessing(null);
  };

  const handleSavePromo = (newConfig?: any) => {
    if(onUpdatePromo) {
      onUpdatePromo(newConfig || tempPromo);
      alert("Pengaturan Banner Promo tersimpan!");
    }
  };

  const filteredTransactions = useMemo(() => {
    return transactions.filter(t => {
        const matchesSearch = t.player.toLowerCase().includes(donationSearch.toLowerCase()) ||
                             t.id.toLowerCase().includes(donationSearch.toLowerCase());
        const matchesFilter = donationFilter === 'All' ? true : t.status === donationFilter;
        return matchesSearch && matchesFilter;
    });
  }, [transactions, donationSearch, donationFilter]);

  const formatDate = (dateString: string) => {
      try {
          return new Intl.DateTimeFormat('id-ID', { dateStyle: 'long', timeStyle: 'short' }).format(new Date(dateString));
      } catch (e) {
          return dateString;
      }
  };

  return (
    <div className="animate-[fadeIn_0.3s_ease-out] space-y-6">
    
    {/* TOP UP PROCESSOR MODAL */}
    <TopUpProcessor 
        isOpen={isProcessorOpen}
        onClose={() => { setIsProcessorOpen(false); setSelectedTxForProcessing(null); }}
        targetPlayer={selectedTxForProcessing ? selectedTxForProcessing.player : ''}
        transactionId={selectedTxForProcessing ? selectedTxForProcessing.id : undefined}
        onComplete={handleTopUpComplete}
    />
                
    {/* INVOICE DETAIL MODAL */}
    {selectedInvoice && (
        <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
            <div className="bg-white dark:bg-[#121212] w-full max-w-2xl rounded-t-3xl md:rounded-2xl border border-gray-200 dark:border-white/10 shadow-2xl overflow-hidden flex flex-col md:flex-row max-h-[95dvh] animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                
                {/* Mobile Drag Handle */}
                <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden shrink-0"></div>

                {/* Left Column: Transaction Details */}
                <div className="flex-1 flex flex-col overflow-y-auto custom-scrollbar">
                    <div className="p-4 border-b border-gray-200 dark:border-white/5 bg-gray-50 dark:bg-[#151515] flex justify-between items-center sticky top-0 z-10">
                        <div>
                            <h3 className="font-bold text-gray-900 dark:text-white uppercase text-sm">Invoice #{selectedInvoice.id}</h3>
                            <p className="text-[10px] text-gray-500">{formatDate(selectedInvoice.date)}</p>
                        </div>
                        <div className={`px-2 py-1 rounded text-[10px] font-bold uppercase border ${
                            selectedInvoice.status === 'Success' ? 'bg-green-500/10 text-green-500 border-green-500/30' :
                            selectedInvoice.status === 'Pending' ? 'bg-amber-500/10 text-amber-500 border-amber-500/30' :
                            'bg-red-500/10 text-red-500 border-red-500/30'
                        }`}>
                            {selectedInvoice.status}
                        </div>
                    </div>

                    <div className="p-6 space-y-6">
                        {/* Info Pemain */}
                        <div className="space-y-3">
                            <h4 className="text-xs font-black text-gray-400 uppercase tracking-widest border-b border-gray-100 dark:border-white/5 pb-1">Info Pemain</h4>
                            <div className="grid grid-cols-2 gap-4">
                                <div>
                                    <p className="text-[10px] text-gray-500 uppercase font-bold">Nama Akun (UCP)</p>
                                    <p className="text-sm font-bold text-gray-900 dark:text-white">{selectedInvoice.player}</p>
                                </div>
                                <div>
                                    <p className="text-[10px] text-gray-500 uppercase font-bold">Nama Pengirim</p>
                                    <p className="text-sm font-bold text-gray-900 dark:text-white">{selectedInvoice.senderName || '-'}</p>
                                </div>
                            </div>
                        </div>

                        {/* Rincian Pesanan */}
                        <div className="space-y-3">
                            <h4 className="text-xs font-black text-gray-400 uppercase tracking-widest border-b border-gray-100 dark:border-white/5 pb-1">Rincian Pesanan</h4>
                            <div className="bg-gray-50 dark:bg-white/5 rounded-lg p-3 border border-gray-100 dark:border-white/5">
                                <div className="flex justify-between items-start mb-2">
                                    <div>
                                        <p className="text-sm font-bold text-gray-900 dark:text-white">{selectedInvoice.item}</p>
                                        {selectedInvoice.quantity && <p className="text-[10px] text-gray-500">Qty: {selectedInvoice.quantity}</p>}
                                    </div>
                                    <div className="text-right">
                                        <p className="text-[10px] text-gray-500 uppercase font-bold">Harga Paket</p>
                                        <p className="text-sm font-bold text-gray-700 dark:text-gray-300">{selectedInvoice.amount}</p>
                                    </div>
                                </div>

                                {/* Conditional Fee / Rate Display */}
                                {selectedInvoice.fee_info && (
                                    <div className="flex justify-between items-center py-1 border-t border-dashed border-gray-200 dark:border-white/10 mt-1">
                                        <p className="text-[10px] text-gray-500 uppercase font-bold">
                                            {selectedInvoice.method.toLowerCase().includes('pulsa') ? 'Rate Convert' : 'Biaya Operasional'}
                                        </p>
                                        <p className="text-xs font-bold text-red-500">
                                            {selectedInvoice.method.toLowerCase().includes('pulsa') ? '' : '+ '}{selectedInvoice.fee_info}
                                        </p>
                                    </div>
                                )}

                                {/* Total Transfer Display */}
                                <div className="flex justify-between items-center pt-2 border-t border-gray-200 dark:border-white/10 mt-2 bg-white dark:bg-black/20 p-2 rounded">
                                    <p className="text-[10px] text-gray-500 uppercase font-bold">TOTAL TRANSFER</p>
                                    <p className="text-sm font-black text-blue-600 dark:text-blue-400">{selectedInvoice.total_transfer || selectedInvoice.amount}</p>
                                </div>

                                <div className="flex justify-between items-center pt-2 border-t border-dashed border-gray-200 dark:border-white/10 mt-2">
                                    <div>
                                        <p className="text-[10px] text-gray-500 uppercase font-bold">Tanggal & Waktu</p>
                                        <p className="text-xs font-bold text-gray-900 dark:text-white">{formatDate(selectedInvoice.date)}</p>
                                    </div>
                                    <div className="text-right">
                                        <p className="text-[10px] text-gray-500 uppercase font-bold">Metode Pembayaran</p>
                                        <p className="text-xs font-bold text-gray-900 dark:text-white bg-white dark:bg-black/20 px-2 py-0.5 rounded border border-gray-200 dark:border-white/10 inline-block">
                                            {selectedInvoice.method}
                                        </p>
                                    </div>
                                </div>
                            </div>
                        </div>

                        {/* Action Buttons */}
                        <div className="pt-4 flex gap-3">
                            <button 
                                onClick={() => handleUpdateStatus(selectedInvoice.id, 'Rejected')}
                                className="flex-1 bg-red-50 dark:bg-red-900/10 text-red-600 dark:text-red-400 py-3 rounded-xl font-bold text-xs uppercase hover:bg-red-100 dark:hover:bg-red-900/20 transition-colors border border-red-100 dark:border-red-900/20"
                            >
                                Tolak (Reject)
                            </button>
                            <button 
                                onClick={() => {
                                    handleUpdateStatus(selectedInvoice.id, 'Success');
                                    setSelectedInvoice(null);
                                }}
                                className="flex-1 bg-gradient-to-r from-green-600 to-green-500 text-white py-3 rounded-xl font-bold text-xs uppercase hover:from-green-500 hover:to-green-400 shadow-lg shadow-green-500/20 transition-all transform active:scale-[0.98]"
                            >
                                Setujui (Approve)
                            </button>
                        </div>
                    </div>
                </div>

                {/* Right Column: Proof Image */}
                <div className="w-full md:w-[280px] bg-gray-100 dark:bg-[#0a0a0a] border-l border-gray-200 dark:border-white/5 flex flex-col">
                    <div className="p-3 border-b border-gray-200 dark:border-white/5 flex justify-between items-center bg-gray-50 dark:bg-[#151515] md:hidden">
                        <h3 className="font-bold text-gray-500 uppercase text-[10px]">Bukti Transfer</h3>
                        <button onClick={() => setSelectedInvoice(null)}><X size={16}/></button>
                    </div>
                    <div className="flex-1 p-4 flex items-center justify-center bg-checkered relative group">
                        {selectedInvoice.proofImage ? (
                            <a href={getDonationProofUrl(selectedInvoice.proofImage)} target="_blank" rel="noreferrer" className="relative block w-full h-full flex items-center justify-center">
                                <img 
                                    src={getDonationProofUrl(selectedInvoice.proofImage)} 
                                    alt="Bukti Transfer" 
                                    className="max-w-full max-h-full object-contain rounded shadow-sm transition-transform group-hover:scale-105"
                                />
                                <div className="absolute inset-0 flex items-center justify-center bg-black/50 opacity-0 group-hover:opacity-100 transition-opacity rounded">
                                    <span className="text-white text-[10px] font-bold uppercase tracking-wider border border-white/50 px-2 py-1 rounded">Klik untuk Perbesar</span>
                                </div>
                            </a>
                        ) : (
                            <div className="text-center text-gray-400">
                                <p className="text-xs italic">Tidak ada bukti transfer</p>
                            </div>
                        )}
                    </div>
                    <div className="p-3 bg-white dark:bg-[#121212] border-t border-gray-200 dark:border-white/5 text-center hidden md:block">
                        <button onClick={() => setSelectedInvoice(null)} className="text-xs text-gray-500 hover:text-red-500 font-bold uppercase">Tutup</button>
                    </div>
                </div>
            </div>
        </div>
    )}

    <PromoConfigCard 
        tempPromo={tempPromo}
        setTempPromo={setTempPromo}
        onSave={handleSavePromo}
    />

    <LimitedItemManager 
        promoItems={promoItems}
        onUpdatePromoItems={onUpdatePromoItems}
    />

    <div className="overflow-x-auto rounded-lg border border-gray-200 dark:border-white/5 bg-white dark:bg-[#0a0a0a]">
        <div className="p-4 border-b border-gray-200 dark:border-white/5 flex flex-col md:flex-row justify-between items-center gap-3">
            <h3 className="font-bold text-gray-900 dark:text-white uppercase text-sm flex items-center gap-2">
                <CreditCard size={16} className="text-green-500"/> Riwayat Invoice
            </h3>
            <div className="flex gap-2 w-full md:w-auto">
                    <select 
                        value={donationFilter}
                        onChange={(e: any) => setDonationFilter(e.target.value)}
                        className="bg-gray-100 dark:bg-white/5 border border-gray-200 dark:border-white/10 rounded-lg px-3 py-1.5 text-xs text-gray-700 dark:text-gray-300 outline-none"
                    >
                        <option value="All">Semua Status</option>
                        <option value="Pending">Pending</option>
                        <option value="Success">Success</option>
                        <option value="Rejected">Rejected</option>
                    </select>
                    <div className="relative flex-1">
                        <Search size={14} className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-500" />
                        <input 
                            type="text" 
                            placeholder="Cari ID/Player..." 
                            value={donationSearch}
                            onChange={e => setDonationSearch(e.target.value)}
                            className="w-full bg-gray-100 dark:bg-white/5 pl-8 pr-3 py-1.5 rounded-lg text-xs outline-none focus:border-red-500 border border-gray-200 dark:border-white/10" 
                        />
                    </div>
            </div>
        </div>
        <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400 min-w-[600px]">
            <thead className="bg-gray-50 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500 border-b border-gray-200 dark:border-white/5">
                <tr>
                    <th className="px-3 py-2">ID</th>
                    <th className="px-3 py-2">Player</th>
                    <th className="px-3 py-2">Item</th>
                    <th className="px-3 py-2">Metode</th>
                    <th className="px-3 py-2">Status</th>
                    <th className="px-3 py-2 text-right">Aksi</th>
                </tr>
            </thead>
            <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                    {filteredTransactions.map(tx => (
                    <tr key={tx.id} className="hover:bg-gray-50 dark:hover:bg-white/5">
                        <td className="px-3 py-2 font-mono text-[10px]">{tx.id}</td>
                        <td className="px-3 py-2 font-bold text-gray-900 dark:text-white">{tx.player}</td>
                        <td className="px-3 py-2">{tx.item} <span className="text-green-500 font-mono text-[10px]">({tx.amount})</span></td>
                        <td className="px-3 py-2">{tx.method}</td>
                        <td className="px-3 py-2">
                            {editingTxId === tx.id ? (
                                <select 
                                    value={tx.status} 
                                    onChange={(e) => handleUpdateStatus(tx.id, e.target.value as any)} 
                                    className="bg-white dark:bg-black border border-gray-200 dark:border-white/10 text-gray-900 dark:text-white text-[10px] p-1 rounded outline-none"
                                    autoFocus
                                    onBlur={() => setEditingTxId(null)}
                                >
                                    <option value="Pending">Pending</option>
                                    <option value="Success">Success</option>
                                    <option value="Rejected">Rejected</option>
                                </select>
                            ) : (
                                <span className={`px-2 py-0.5 rounded text-[9px] font-bold uppercase border ${
                                    tx.status === 'Success' ? 'bg-green-500/10 text-green-500 border-green-500/30' :
                                    tx.status === 'Pending' ? 'bg-amber-500/10 text-amber-500 border-amber-500/30' :
                                    'bg-red-500/10 text-red-500 border-red-500/30'
                                }`}>
                                    {tx.status}
                                </span>
                            )}
                        </td>
                        <td className="px-3 py-2 text-right flex justify-end gap-2">
                            <button 
                                onClick={() => setSelectedInvoice(tx)}
                                className="bg-purple-600 hover:bg-purple-500 text-white px-3 py-1.5 rounded shadow-lg text-[10px] font-bold uppercase flex items-center gap-1 transition-transform active:scale-95"
                            >
                                Detail
                            </button>
                            {tx.status === 'Pending' ? (
                                <button 
                                    onClick={() => openProcessor(tx)} 
                                    className="bg-blue-600 hover:bg-blue-500 text-white px-3 py-1.5 rounded shadow-lg text-[10px] font-bold uppercase flex items-center gap-1 transition-transform active:scale-95" 
                                    title="Proses Top Up"
                                >
                                    <PackageCheck size={14} /> Proses
                                </button>
                            ) : tx.status === 'Success' ? (
                                <button disabled className="bg-gray-100 dark:bg-white/10 text-gray-500 cursor-not-allowed px-3 py-1.5 rounded text-[10px] font-bold uppercase flex items-center gap-1">
                                    <CheckCircle2 size={14} /> Selesai
                                </button>
                            ) : (
                                <span className="text-gray-500 text-[10px] italic">Ditutup</span>
                            )}
                            
                            <button onClick={() => setEditingTxId(tx.id)} className="text-gray-400 hover:text-white p-1" title="Edit Manual Status"><Edit size={14} /></button>
                        </td>
                    </tr>
                    ))}
                    {filteredTransactions.length === 0 && (
                        <tr><td colSpan={6} className="text-center py-8 text-gray-500">Tidak ada transaksi ditemukan.</td></tr>
                    )}
            </tbody>
        </table>
    </div>
</div>
  );
};
