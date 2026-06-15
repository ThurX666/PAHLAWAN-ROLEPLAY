import React, { useState, useEffect } from 'react';
import { Lightbulb, Unlock, RefreshCcw, HandCoins, AlertTriangle, CheckCircle, Clock } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

interface RequestsProps {
  userName: string;
}

type RequestType = 'Feature' | 'Unban' | 'Namechange' | 'Refund';

interface UserRequest {
  id: number;
  request_type: RequestType;
  content: string;
  metadata: any;
  status: 'Pending' | 'In Review' | 'Approved' | 'Rejected';
  created_at: string;
  admin_feedback?: string;
}

export const Requests: React.FC<RequestsProps> = ({ userName }) => {
  const [activeTab, setActiveTab] = useState<RequestType>('Unban');
  const [requests, setRequests] = useState<UserRequest[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  
  // Submit state
  const [content, setContent] = useState('');
  const [metadata, setMetadata] = useState<any>({});
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [submitResult, setSubmitResult] = useState<{type: 'success'|'error', message: string} | null>(null);

  useEffect(() => {
    loadRequests();
  }, [userName]);

  const loadRequests = async () => {
    setIsLoading(true);
    if (isPreviewEnv()) {
      setTimeout(() => {
        setRequests([
          {
            id: 1,
            request_type: 'Unban',
            content: 'Saya menyesal telah menggunakan mod terlarang, mohon maaf dan berikan saya kesempatan kedua.',
            metadata: { karakterban: 'Ucok_Slepbeuw', admin: 'High_Staff' },
            status: 'Pending',
            created_at: new Date(Date.now() - 86400000).toISOString()
          },
          {
            id: 2,
            request_type: 'Refund',
            content: 'Mobil saya hilang karena bug server saat login kemarin.',
            metadata: { vehicle: 'Infernus', amount: 0 },
            status: 'Approved',
            admin_feedback: 'Mobil telah dikembalikan melalui command /refund di ingame.',
            created_at: new Date(Date.now() - 172800000).toISOString()
          }
        ]);
        setIsLoading(false);
      }, 500);
    } else {
      try {
        const res = await fetch(`${API_URL}/api_user_requests.php?action=get_requests&username=${userName}`);
        const data = await res.json();
        if (data.status === 'success') {
          // Parse metadata
          const parsed = data.data.map((r: any) => ({
            ...r,
            metadata: r.metadata ? JSON.parse(r.metadata) : {}
          }));
          setRequests(parsed);
        }
      } catch (err) {
        console.error(err);
      } finally {
        setIsLoading(false);
      }
    }
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!content) return;
    
    setIsSubmitting(true);
    setSubmitResult(null);

    if (isPreviewEnv()) {
      setTimeout(() => {
        const newReq: UserRequest = {
          id: Date.now(),
          request_type: activeTab,
          content,
          metadata,
          status: 'Pending',
          created_at: new Date().toISOString()
        };
        setRequests([newReq, ...requests]);
        setContent('');
        setMetadata({});
        setSubmitResult({ type: 'success', message: 'Permohonan Anda berhasil dikirim (Preview).' });
        setIsSubmitting(false);
      }, 1000);
    } else {
      try {
        const res = await fetch(`${API_URL}/api_user_requests.php`, {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({
            action: 'submit_request',
            username: userName,
            type: activeTab,
            content,
            metadata
          })
        });
        const data = await res.json();
        if (data.status === 'success') {
          setSubmitResult({ type: 'success', message: data.message });
          setContent('');
          setMetadata({});
          loadRequests();
        } else {
          setSubmitResult({ type: 'error', message: data.message });
        }
      } catch (err) {
        setSubmitResult({ type: 'error', message: 'Koneksi ke server gagal.' });
      } finally {
        setIsSubmitting(false);
      }
    }
  };

  const tabs: {id: RequestType, label: string, icon: React.FC<any>}[] = [
    { id: 'Unban', label: 'Unban Request', icon: Unlock },
    { id: 'Namechange', label: 'Namechange', icon: RefreshCcw },
    { id: 'Refund', label: 'Refund', icon: HandCoins },
    { id: 'Feature', label: 'Feature Request', icon: Lightbulb },
  ];

  if (!isPreviewEnv()) {
    return (
      <div className="flex-1 overflow-auto custom-scrollbar bg-gray-50 dark:bg-[#050505] flex items-center justify-center h-full min-h-[500px]">
        <div className="text-center p-8 bg-white/50 dark:bg-[#121212]/50 border border-gray-200 dark:border-white/5 rounded-2xl backdrop-blur-sm">
          <div className="inline-flex items-center justify-center w-20 h-20 bg-yellow-500/10 text-yellow-500 rounded-3xl mb-6 shadow-sm">
            <AlertTriangle size={40} />
          </div>
          <h1 className="text-2xl font-black text-gray-900 dark:text-white mb-2 uppercase tracking-tight">Under Construction</h1>
          <p className="text-gray-600 dark:text-gray-400 font-medium text-sm">Under Construction by <span className="font-bold text-red-500">ThurX</span></p>
        </div>
      </div>
    );
  }

  return (
    <div className="flex-1 overflow-auto custom-scrollbar bg-gray-50 dark:bg-[#050505]">
      <div className="p-4 md:p-8 max-w-6xl mx-auto space-y-6">
        
        {/* Header Section */}
        <div className="flex flex-col md:flex-row justify-between items-start md:items-center gap-4 bg-white/50 dark:bg-[#121212]/50 p-6 rounded-2xl border border-gray-200 dark:border-white/5 backdrop-blur-sm">
          <div>
            <h1 className="text-2xl md:text-3xl font-black text-gray-900 dark:text-white uppercase tracking-tight">Request Center</h1>
            <p className="text-sm text-gray-500 dark:text-gray-400 mt-1 font-medium">Ajukan permohonan ke tim administrasi server.</p>
          </div>
        </div>

        {/* Tab Navigation */}
        <div className="flex flex-wrap gap-2 p-1 bg-gray-200/50 dark:bg-white/5 rounded-xl border border-gray-200 dark:border-white/5">
            {tabs.map(tab => (
                <button
                    key={tab.id}
                    onClick={() => { setActiveTab(tab.id); setContent(''); setSubmitResult(null); }}
                    className={`flex items-center space-x-2 px-4 py-2.5 outline-none rounded-lg font-bold text-sm transition-all flex-1 md:flex-none justify-center ${
                      activeTab === tab.id 
                          ? 'bg-white dark:bg-[#222] text-red-600 shadow-sm border border-gray-200 dark:border-white/10 scale-100' 
                          : 'text-gray-600 dark:text-gray-400 hover:text-gray-900 dark:hover:text-gray-200 hover:bg-gray-200/50 dark:hover:bg-white/5 scale-[0.98]'
                  }`}
                >
                    <tab.icon size={18} />
                    <span>{tab.label}</span>
                </button>
            ))}
        </div>

        <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
          {/* Form */}
          <div className="bg-white dark:bg-[#121212] rounded-2xl shadow-sm border border-gray-200 dark:border-white/5 p-6 animate-in fade-in slide-in-from-bottom-4 duration-500">
            <h2 className="text-lg font-bold text-gray-900 dark:text-white mb-6 uppercase border-b border-gray-200 dark:border-white/5 pb-4">
              Buat {activeTab} Request
            </h2>

            {submitResult && (
              <div className={`mb-4 p-4 rounded-xl border flex items-start gap-3 ${
                submitResult.type === 'success' 
                ? 'bg-green-50 dark:bg-green-500/10 border-green-200 dark:border-green-500/20 text-green-700 dark:text-green-400'
                : 'bg-red-50 dark:bg-red-500/10 border-red-200 dark:border-red-500/20 text-red-700 dark:text-red-400'
              }`}>
                {submitResult.type === 'success' ? <CheckCircle className="shrink-0" /> : <AlertTriangle className="shrink-0" />}
                <p className="text-sm font-medium">{submitResult.message}</p>
              </div>
            )}

            <form onSubmit={handleSubmit} className="space-y-4">
              {activeTab === 'Unban' && (
                <>
                  <div>
                    <label className="block text-sm text-gray-500 dark:text-gray-400 mb-1.5 font-semibold">Nama Karakter</label>
                    <input type="text" 
                        value={metadata.character || ''} 
                        onChange={(e) => setMetadata({...metadata, character: e.target.value})}
                        className="w-full bg-gray-50 dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-sm text-gray-900 dark:text-white focus:ring-2 focus:ring-red-500/50 outline-none transition-all placeholder:text-gray-400 dark:placeholder:text-gray-600"
                        placeholder="Contoh: Ucok_Slepbeuw" required />
                  </div>
                  <div>
                    <label className="block text-sm text-gray-500 dark:text-gray-400 mb-1.5 font-semibold">Admin yang mem-banned</label>
                    <input type="text" 
                        value={metadata.admin || ''} 
                        onChange={(e) => setMetadata({...metadata, admin: e.target.value})}
                        className="w-full bg-gray-50 dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-sm text-gray-900 dark:text-white focus:ring-2 focus:ring-red-500/50 outline-none transition-all placeholder:text-gray-400 dark:placeholder:text-gray-600"
                        placeholder="Contoh: Admin_Brave" required />
                  </div>
                </>
              )}
              {activeTab === 'Namechange' && (
                <>
                  <div>
                    <label className="block text-sm text-gray-500 dark:text-gray-400 mb-1.5 font-semibold">Nama Lama</label>
                    <input type="text" 
                        value={metadata.oldName || ''} 
                        onChange={(e) => setMetadata({...metadata, oldName: e.target.value})}
                        className="w-full bg-gray-50 dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-sm text-gray-900 dark:text-white focus:ring-2 focus:ring-red-500/50 outline-none transition-all placeholder:text-gray-400 dark:placeholder:text-gray-600"
                        placeholder="Contoh: Budi_Santoso" required />
                  </div>
                  <div>
                    <label className="block text-sm text-gray-500 dark:text-gray-400 mb-1.5 font-semibold">Nama Baru (Tujuan)</label>
                    <input type="text" 
                        value={metadata.newName || ''} 
                        onChange={(e) => setMetadata({...metadata, newName: e.target.value})}
                        className="w-full bg-gray-50 dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-sm text-gray-900 dark:text-white focus:ring-2 focus:ring-red-500/50 outline-none transition-all placeholder:text-gray-400 dark:placeholder:text-gray-600"
                        placeholder="Contoh: Alexander_Rodriguez" required />
                  </div>
                  <div className="flex items-center gap-2 p-3 bg-red-500/10 border border-red-500/20 rounded-xl">
                      <AlertTriangle className="text-red-500 shrink-0" size={18} />
                      <p className="text-xs text-red-600 dark:text-red-400 font-medium">Namechange membutuhkan biaya/item di dalam game setelah disetujui.</p>
                  </div>
                </>
              )}
              {activeTab === 'Refund' && (
                <>
                  <div>
                    <label className="block text-sm text-gray-500 dark:text-gray-400 mb-1.5 font-semibold">Aset yang hilang</label>
                    <input type="text" 
                        value={metadata.lostAsset || ''} 
                        onChange={(e) => setMetadata({...metadata, lostAsset: e.target.value})}
                        className="w-full bg-gray-50 dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-sm text-gray-900 dark:text-white focus:ring-2 focus:ring-red-500/50 outline-none transition-all placeholder:text-gray-400 dark:placeholder:text-gray-600"
                        placeholder="Contoh: Kendaraan Infernus atau Uang $5.000" required />
                  </div>
                </>
              )}
              
              <div>
                <label className="block text-sm text-gray-500 dark:text-gray-400 mb-1.5 font-semibold">Alasan / Penjelasan Detail</label>
                <textarea 
                  value={content}
                  onChange={(e) => setContent(e.target.value)}
                  className="w-full bg-gray-50 dark:bg-[#0a0a0a] border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-sm text-gray-900 dark:text-white focus:ring-2 focus:ring-red-500/50 outline-none transition-all placeholder:text-gray-400 dark:placeholder:text-gray-600 min-h-[120px] resize-y custom-scrollbar"
                  placeholder="Jelaskan dengan detail permohonan Anda..."
                  required
                ></textarea>
              </div>

              {/* Submit Button */}
              <button 
                  type="submit" 
                  disabled={isSubmitting || !content}
                  className="w-full bg-gradient-to-r from-red-600 to-red-600 hover:from-red-500 hover:to-red-600 text-white font-bold py-3.5 px-4 rounded-xl shadow-lg hover:shadow-red-500/25 transition-all outline-none focus:ring-4 focus:ring-red-500/30 active:scale-[0.98] disabled:opacity-50 disabled:cursor-not-allowed flex items-center justify-center tracking-wide"
              >
                  {isSubmitting ? (
                      <div className="w-5 h-5 border-2 border-white/30 border-t-white rounded-full animate-spin"></div>
                  ) : (
                      'KIRIM REQUEST'
                  )}
              </button>
            </form>
          </div>

          {/* Request History */}
          <div className="bg-white dark:bg-[#121212] rounded-2xl shadow-sm border border-gray-200 dark:border-white/5 p-6 flex flex-col min-h-[400px]">
             <h2 className="text-lg font-bold text-gray-900 dark:text-white mb-6 uppercase border-b border-gray-200 dark:border-white/5 pb-4">
                Riwayat Request
             </h2>

             {isLoading ? (
                <div className="flex-1 flex flex-col items-center justify-center text-gray-400">
                   <div className="w-8 h-8 border-4 border-red-500/20 border-t-red-500 rounded-full animate-spin mb-4"></div>
                   <p className="text-sm font-medium">Memuat riwayat...</p>
                </div>
             ) : requests.length === 0 ? (
                <div className="flex-1 flex flex-col items-center justify-center text-gray-400 opacity-70 mt-10">
                   <AlertTriangle size={48} className="mb-4 text-gray-300 dark:text-gray-600" />
                   <p className="text-sm font-medium">Belum ada riwayat permohonan.</p>
                </div>
             ) : (
                <div className="space-y-4 flex-1 overflow-y-auto pr-2 custom-scrollbar">
                    {requests.map(req => (
                        <div key={req.id} className="p-4 rounded-xl border border-gray-200 dark:border-white/5 bg-gray-50/50 dark:bg-[#0a0a0a]/50">
                            <div className="flex justify-between items-start mb-2">
                                <span className="font-bold text-gray-900 dark:text-white text-sm">{req.request_type} Request</span>
                                <span className={`text-[10px] uppercase tracking-wider font-bold px-2 py-1 rounded-md ${
                                    req.status === 'Approved' ? 'bg-green-100 text-green-700 dark:bg-green-500/20 dark:text-green-400' :
                                    req.status === 'Rejected' ? 'bg-red-100 text-red-700 dark:bg-red-500/20 dark:text-red-400' :
                                    'bg-yellow-100 text-yellow-700 dark:bg-yellow-500/20 dark:text-yellow-400'
                                }`}>{req.status}</span>
                            </div>
                            <p className="text-xs text-gray-600 dark:text-gray-400 mb-3 line-clamp-2">{req.content}</p>
                            
                            {req.admin_feedback && (
                                <div className="mt-2 text-xs bg-black/5 dark:bg-white/5 p-2 rounded border border-black/5 dark:border-white/5">
                                    <span className="font-bold text-gray-700 dark:text-gray-300">Admin Note:</span> {req.admin_feedback}
                                </div>
                            )}
                            
                            <div className="flex items-center text-[10px] text-gray-400 mt-2">
                                <Clock size={12} className="mr-1" />
                                {new Date(req.created_at).toLocaleDateString('id-ID', {day: 'numeric', month: 'short', year:'numeric', hour:'2-digit', minute:'2-digit'})}
                            </div>
                        </div>
                    ))}
                </div>
             )}
          </div>
        </div>

      </div>
    </div>
  );
};
