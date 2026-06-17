import React, { useState, useEffect } from 'react';
import { Headset, LifeBuoy, MessageCircleQuestion, Sparkles, Crown, Coins, AlertTriangle, CheckCircle } from 'lucide-react';
import { Character, PromoItem, InboxMessage } from '../types';
import { DonationHeader } from './donation/DonationHeader';
import { VipPackages, VIP_PACKAGES } from './donation/VipPackages';
import { GoldPackages } from './donation/GoldPackages';
import { PromoShop } from './donation/PromoShop';
import { GoldShop } from './donation/GoldShop';
import { TransactionHistory, Transaction } from './donation/TransactionHistory';
import { PaymentModal } from './donation/PaymentModal';
import { PromoItemModal } from './donation/PromoItemModal';
import { saveDonationProof } from '../utils/imageUtils';
import { isPreviewEnv, API_URL } from '../config';

interface DonationProps {
  initialTab?: 'exclusive' | 'vip' | 'gold';
  promoConfig?: {
    isActive: boolean;
    title: string;
    message: string;
  };
  promoItems?: PromoItem[];
  userGold: number;
  characters: Character[];
  userName: string;
  accountId?: string | number;
  vipStatus?: {
    tier: string;
    expiredAt: string;
  } | null;
  onRedeem: (characterId: number, item: { id?: number; name: string; price: number; description?: string }) => Promise<boolean>;
  onNavigate?: (tab: string) => void;
  onSendNotification?: (msg: InboxMessage) => void;
}

import { INITIAL_ADMIN_TRANSACTIONS } from '../data/mockData';

export const Donation: React.FC<DonationProps> = ({ 
  initialTab = 'vip',
  promoConfig, 
  promoItems = [], 
  userGold, 
  characters, 
  userName,
  accountId = 8492,
  vipStatus,
  onRedeem,
  onNavigate,
  onSendNotification
}) => {
  const [activePkg, setActivePkg] = useState<any>(null);
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [selectedPromoItem, setSelectedPromoItem] = useState<PromoItem | null>(null);
  const [transactions, setTransactions] = useState<Transaction[]>([]);
  const [isSubmitting, setIsSubmitting] = useState(false);
  const [activeTab, setActiveTab] = useState<'exclusive' | 'vip' | 'gold'>(initialTab);
  const [alertConfig, setAlertConfig] = useState<{title: string, message: string, type: 'warning' | 'success'} | null>(null);

  useEffect(() => {
    setActiveTab(initialTab);
  }, [initialTab]);

  useEffect(() => {
      const fetchTransactions = async () => {
          if (!isPreviewEnv()) {
              try {
                  const res = await fetch(`${API_URL}/api_donations.php?action=get_transactions&username=${encodeURIComponent(userName)}`);
                  const data = await res.json();
                  if (data.status === 'success' && data.data) {
                      const apiTransactions = data.data.map((trx: any) => ({
                          id: parseInt(trx.id),
                          packageName: trx.item_name,
                          amount: trx.quantity ? trx.quantity.toString() + (trx.item_name.includes('Gold') || trx.item_name.includes('GC') ? ' GC' : '') : '',
                          price: trx.amount,
                          status: trx.status,
                          date: trx.created_at,
                          method: trx.payment_method,
                          proofUrl: trx.proof_image
                      }));
                      setTransactions(apiTransactions);
                      return;
                  }
              } catch (err) {
                  console.error("Failed to fetch transactions:", err);
              }
          }
          
          // Fallback to local simulation
          const storedTrx = localStorage.getItem('mock_transactions');
          let allTransactions = INITIAL_ADMIN_TRANSACTIONS;
          
          if (storedTrx) {
              try {
                  const parsed = JSON.parse(storedTrx);
                  if (parsed && parsed.length > 0) {
                      allTransactions = parsed;
                  }
              } catch (e) {}
          }

          const filteredTransactions = allTransactions
            .filter(trx => userName.toLowerCase() === 'admin' || trx.account.toLowerCase() === userName.toLowerCase())
            .map(trx => ({
              id: typeof trx.id === 'string' ? parseInt(trx.id.replace('INV-', '')) : trx.id,
              packageName: trx.item,
              amount: trx.quantity ? trx.quantity.toString() + (trx.item.includes('Gold') ? ' GC' : '') : '',
              price: trx.amount,
              status: trx.status as 'Pending' | 'Success' | 'Rejected',
              date: trx.date.includes('T') ? new Intl.DateTimeFormat('id-ID', {
                day: 'numeric',
                month: 'short',
                year: 'numeric',
                hour: '2-digit',
                minute: '2-digit',
                hour12: false
              }).format(new Date(trx.date)).replace(/\./g, ':') : trx.date,
              method: trx.method,
              proofUrl: trx.proofImage
            }));
            
          setTransactions(filteredTransactions);
      };

      fetchTransactions();
  }, [userName]);

  const handlePaymentSubmit = async (formData: any) => {
    setIsSubmitting(true);
    
    // Create Date with Time
    const now = new Date();
    const formattedDate = new Intl.DateTimeFormat('id-ID', {
        day: 'numeric',
        month: 'short',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        hour12: false
    }).format(now).replace(/\./g, ':'); // Ensure format is friendly

    let proofPath = '';
    if (formData.paymentProof) {
        proofPath = await saveDonationProof(userName, formData.paymentProof);
    }

    if (!isPreviewEnv()) {
        try {
            const res = await fetch(`${API_URL}/api_donations.php`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    action: 'add_transaction',
                    account: userName,
                    senderName: formData.senderName,
                    item: formData.packageName,
                    type: 'donation',
                    quantity: formData.amount || 1,
                    amount: formData.price,
                    method: formData.paymentMethod,
                    proofImage: proofPath
                })
            });
            const data = await res.json();
            if (data.status === 'success') {
                const newTrx: Transaction = {
                    id: parseInt(String(data.transaction_id || '').replace('INV-', '') || '0'),
                    packageName: formData.packageName,
                    amount: formData.amount ? `${formData.amount} GC` : 'Membership',
                    price: formData.price,
                    status: 'Pending',
                    date: formattedDate,
                    method: formData.paymentMethod,
                    proofUrl: proofPath
                };
                setTransactions([newTrx, ...transactions]);
            }
        } catch (err) {
            console.error("Failed to post transaction:", err);
        }
    } else {
        // Mock execution
        await new Promise(r => setTimeout(r, 1500));
        const newTrx: Transaction = {
            id: Date.now(),
            packageName: formData.packageName,
            amount: formData.amount ? `${formData.amount} GC` : 'Membership',
            price: formData.price,
            status: 'Pending',
            date: formattedDate,
            method: formData.paymentMethod,
            proofUrl: proofPath
        };

        const newAdminTrx = {
            id: `INV-${newTrx.id}`,
            account: userName,
            player: userName,
            senderName: formData.senderName,
            item: formData.packageName,
            type: "donation",
            quantity: formData.amount || 1,
            amount: formData.price,
            total_transfer: formData.price,
            fee_info: "",
            method: formData.paymentMethod,
            status: "Pending",
            date: now.toISOString(),
            proofImage: proofPath
        };

        const storedTrx = localStorage.getItem('mock_transactions');
        let allTransactions = INITIAL_ADMIN_TRANSACTIONS;
        if (storedTrx) {
            try {
                allTransactions = JSON.parse(storedTrx);
            } catch (e) {}
        }
        
        const updatedAllTransactions = [newAdminTrx, ...allTransactions];
        localStorage.setItem('mock_transactions', JSON.stringify(updatedAllTransactions));

        setTransactions([newTrx, ...transactions]);
    }

    setIsSubmitting(false);
    setIsModalOpen(false);
    setActivePkg(null);
    
    if (onSendNotification) {
        onSendNotification({
            id: Date.now().toString(),
            title: `Konfirmasi Pembayaran: ${formData.packageName}`,
            message: `Yth. ${userName},\n\nTerima kasih atas konfirmasi pembayaran Anda untuk paket <b>${formData.packageName}</b> senilai <b>${formData.price}</b>.\n\nBukti transfer yang Anda kirimkan telah kami terima dengan baik dan saat ini sedang dalam proses antrean verifikasi oleh tim kami. Proses ini membutuhkan waktu maksimal <b>1x24 jam</b>. Apabila setelah melewati batas waktu tersebut status transaksi Anda belum diperbarui, silakan menghubungi kami melalui layanan Support Ticket.\n\nKami menyampaikan apresiasi dan terima kasih yang sebesar-besarnya atas donasi serta dukungan yang Anda berikan. Kontribusi Anda memiliki peran penting dalam menjaga keberlangsungan dan pengembangan Pahlawan Roleplay ke arah yang lebih baik. Kehadiran Anda sebagai bagian dari komunitas ini sangat berarti bagi kami.\n\nHormat kami,\n<b>Tim Pahlawan Roleplay</b>`,
            type: 'System',
            date: now.toISOString(),
            read: false
        });
    }

    setAlertConfig({
        title: "Berhasil!",
        message: "Bukti pembayaran berhasil dikirim dan sedang dalam antrean verifikasi.",
        type: "success"
    });
  };

  return (
    <div className="w-full animate-[fadeIn_0.5s_ease-out]">
      
      {/* UX IMPROVEMENT: Professional Grid Layout */}
      <div className="grid grid-cols-1 lg:grid-cols-12 gap-4 md:gap-8 lg:gap-10 items-start">
        
        {/* 1. Header & Promo Banner (Full Width) */}
        <div className="lg:col-span-12">
            <DonationHeader 
                promoConfig={promoConfig} 
                userGold={userGold} 
                userName={userName} 
                accountId={accountId}
                vipStatus={vipStatus}
                onTopUpClick={() => setActiveTab('gold')}
                onExtendVipClick={(tier) => {
                    setActiveTab('vip');
                    const pkg = VIP_PACKAGES.find(p => p.id === tier.toLowerCase());
                    if (pkg) {
                        setActivePkg(pkg);
                        setTimeout(() => {
                            const vipSection = document.getElementById('vip-section');
                            if(vipSection) vipSection.scrollIntoView({ behavior: 'smooth', block: 'start' });
                        }, 100);
                    }
                }}
            />
        </div>

        {/* Store Navigation Tabs */}
        <div className="lg:col-span-12">
            <div className="flex items-center justify-between md:justify-center gap-1.5 sm:gap-2 md:gap-3 px-1 w-full">
                {[
                    { id: 'exclusive', label: 'EXCLUSIVE', icon: Sparkles, color: 'text-purple-500', activeBg: 'bg-purple-600', border: 'border-purple-500/30' },
                    { id: 'vip', label: 'VIP', icon: Crown, color: 'text-amber-500', activeBg: 'bg-amber-600', border: 'border-amber-500/30' },
                    { id: 'gold', label: 'GOLD', icon: Coins, color: 'text-yellow-500', activeBg: 'bg-yellow-600', border: 'border-yellow-500/30' }
                ].map(tab => {
                    const Icon = tab.icon;
                    const isActive = activeTab === tab.id;
                    return (
                        <button
                            key={tab.id}
                            onClick={() => setActiveTab(tab.id as any)}
                            className={`
                                flex items-center justify-center gap-1 sm:gap-1.5 md:gap-2.5 px-2 sm:px-4 md:px-6 py-2.5 md:py-3.5 rounded-xl md:rounded-2xl font-black text-[9px] sm:text-[10px] md:text-sm uppercase tracking-wider md:tracking-widest transition-all duration-300 whitespace-nowrap border-2 flex-1 md:flex-none
                                ${isActive 
                                    ? `${tab.activeBg} text-white border-transparent shadow-lg shadow-${tab.activeBg.split('-')[1]}-500/30 scale-[1.02] md:scale-105` 
                                    : `bg-white dark:bg-[#1a1a1a] text-gray-500 dark:text-gray-400 border-gray-200 dark:border-white/5 hover:bg-gray-50 dark:hover:bg-white/10 hover:border-gray-300 dark:hover:border-white/10`
                                }
                            `}
                        >
                            <Icon className={`w-3.5 h-3.5 sm:w-4 sm:h-4 md:w-[18px] md:h-[18px] shrink-0 ${isActive ? 'text-white animate-pulse' : tab.color}`} />
                            <span className="truncate">{tab.label}</span>
                        </button>
                    )
                })}
            </div>
        </div>

        {/* Main Content Column (Full Width) */}
        <div className="lg:col-span-12 space-y-4 md:space-y-8 lg:space-y-10 min-w-0">
             
             {/* Tab Content */}
             <div>
                 {activeTab === 'exclusive' && (
                     <div className="animate-[fadeIn_0.3s_ease-out]">
                         <PromoShop promoItems={promoItems} onSelectItem={setSelectedPromoItem} />
                     </div>
                 )}

                 {activeTab === 'vip' && (
                     <div id="vip-section" className="animate-[fadeIn_0.3s_ease-out] bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-2xl p-4 md:p-6 shadow-sm scroll-mt-24">
                         <VipPackages activePkg={activePkg} onSelectPackage={setActivePkg} currentVipTier={vipStatus?.tier} />
                     </div>
                 )}

                 {activeTab === 'gold' && (
                     <div id="gold-section" className="animate-[fadeIn_0.3s_ease-out] space-y-4 md:space-y-8 lg:space-y-10 scroll-mt-24">
                         <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-2xl p-4 md:p-6 shadow-sm">
                             <GoldPackages activePkg={activePkg} onSelectPackage={setActivePkg} />
                         </div>
                         <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-2xl p-4 md:p-6 shadow-sm">
                             <GoldShop 
                                 userGold={userGold}
                                 characters={characters}
                                 onRedeem={async (characterId, item) => {
                                     const success = await onRedeem(characterId, item);
                                     if (success !== false) {
                                         // Create Transaction Record
                                         const now = new Date();
                                         const formattedDate = new Intl.DateTimeFormat('id-ID', {
                                             day: 'numeric',
                                             month: 'short',
                                             year: 'numeric',
                                             hour: '2-digit',
                                             minute: '2-digit',
                                             hour12: false
                                         }).format(now).replace(/\./g, ':');

                                         const newTrx: Transaction = {
                                             id: Date.now(),
                                             packageName: item.name,
                                             amount: '1 Item',
                                             price: `${item.price} GC`,
                                             status: 'Success',
                                             date: formattedDate,
                                             method: 'Gold Coin',
                                             proofUrl: ''
                                         };

                                         const newAdminTrx = {
                                             id: `INV-${newTrx.id}`,
                                             account: userName,
                                             player: userName,
                                             senderName: userName,
                                             item: item.name,
                                             type: "redeem",
                                             quantity: 1,
                                             amount: item.price,
                                             total_transfer: item.price,
                                             fee_info: "",
                                             method: "Gold Coin",
                                             status: "Success",
                                             date: now.toISOString(),
                                             proofImage: ""
                                         };

                                         const storedTrx = localStorage.getItem('mock_transactions');
                                         let allTransactions = INITIAL_ADMIN_TRANSACTIONS;
                                         if (storedTrx) {
                                             try {
                                                 allTransactions = JSON.parse(storedTrx);
                                             } catch (e) {}
                                         }
                                         
                                         const updatedAllTransactions = [newAdminTrx, ...allTransactions];
                                         localStorage.setItem('mock_transactions', JSON.stringify(updatedAllTransactions));

                                         setTransactions(prev => [newTrx, ...prev]);
                                     }
                                 }}
                             />
                         </div>
                     </div>
                 )}
             </div>

             {/* Transactions Section */}
             <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-2xl p-4 md:p-6 shadow-sm">
                <TransactionHistory transactions={transactions} />
             </div>

             {/* Mini Help Card (Enhanced UI) */}
             <div className="relative overflow-hidden rounded-2xl border border-blue-200/50 dark:border-blue-500/20 bg-gradient-to-br from-blue-50 to-indigo-50 dark:from-blue-900/10 dark:to-indigo-900/10 p-5 shadow-lg group">
                 {/* Abstract Decor */}
                 <div className="absolute -right-5 -top-5 text-blue-500/10 dark:text-blue-400/5 transform rotate-12 group-hover:rotate-45 transition-transform duration-700">
                     <LifeBuoy size={120} />
                 </div>

                 <div className="relative z-10">
                     <div className="flex items-center gap-2.5 mb-3">
                         <div className="p-2 bg-blue-100 dark:bg-blue-500/20 rounded-lg text-blue-600 dark:text-blue-400 shadow-sm ring-1 ring-blue-500/20">
                             <Headset size={18} />
                         </div>
                         <div>
                             <h4 className="font-black text-gray-900 dark:text-white uppercase italic text-sm tracking-wide leading-none">Butuh Bantuan?</h4>
                             <span className="text-[10px] font-bold text-blue-500 uppercase tracking-widest">Support 24/7</span>
                         </div>
                     </div>
                     
                     <p className="text-xs text-gray-600 dark:text-gray-400 mb-4 leading-relaxed font-medium border-l-2 border-blue-500/30 pl-3">
                         Jika mengalami kendala saat konfirmasi pembayaran, silakan buat tiket bantuan.
                     </p>
                     
                     <button 
                         onClick={() => onNavigate && onNavigate('tickets')}
                         className="w-fit px-6 bg-gradient-to-r from-blue-600 to-indigo-600 hover:from-blue-500 hover:to-indigo-500 text-white font-bold py-3 rounded-xl text-[10px] uppercase tracking-widest shadow-lg shadow-blue-500/20 flex items-center justify-center gap-2 transition-all transform active:scale-95 group-hover:shadow-blue-500/30 border border-blue-400/20">
                         <MessageCircleQuestion size={14} /> Hubungi Admin
                     </button>
                 </div>
             </div>
        </div>

      </div>

      {/* Modals */}
      {isModalOpen && activePkg && (
          <PaymentModal 
            selectedPkg={activePkg} 
            onClose={() => setIsModalOpen(false)} 
            onSubmit={handlePaymentSubmit}
            isSubmitting={isSubmitting}
          />
      )}

      {selectedPromoItem && (
          <PromoItemModal 
            item={selectedPromoItem} 
            onClose={() => setSelectedPromoItem(null)} 
            onRedeem={(item) => {
                const charId = characters.length > 0 ? characters[0].id : 0;
                const success = onRedeem(charId, {
                    name: item.name,
                    price: item.priceGold || 0,
                    description: item.description
                });
                
                if (success !== false) {
                    const now = new Date();
                    const formattedDate = new Intl.DateTimeFormat('id-ID', {
                        day: 'numeric', month: 'short', year: 'numeric',
                        hour: '2-digit', minute: '2-digit', hour12: false
                    }).format(now).replace(/\./g, ':');

                    const newTrx: Transaction = {
                        id: Date.now(),
                        packageName: item.name,
                        amount: '1 Item',
                        price: `${item.priceGold} GC`,
                        status: 'Success',
                        date: formattedDate,
                        method: 'Gold Coin',
                        proofUrl: ''
                    };

                    const newAdminTrx = {
                        id: `INV-${newTrx.id}`,
                        account: userName,
                        player: userName,
                        senderName: userName,
                        item: item.name,
                        type: "redeem",
                        quantity: 1,
                        amount: item.priceGold || 0,
                        total_transfer: item.priceGold || 0,
                        fee_info: "",
                        method: "Gold Coin",
                        status: "Success",
                        date: now.toISOString(),
                        proofImage: ""
                    };

                    const storedTrx = localStorage.getItem('mock_transactions');
                    let allTransactions = INITIAL_ADMIN_TRANSACTIONS;
                    if (storedTrx) {
                        try { allTransactions = JSON.parse(storedTrx); } catch (e) {}
                    }
                    
                    const updatedAllTransactions = [newAdminTrx, ...allTransactions];
                    localStorage.setItem('mock_transactions', JSON.stringify(updatedAllTransactions));

                    setTransactions(prev => [newTrx, ...prev]);
                    setSelectedPromoItem(null);
                }
            }}
          />
      )}

      {/* Sticky Bottom CTA for Mobile & Desktop when Package is Selected */}
      {activePkg && !isModalOpen && (
          <div className="fixed bottom-16 md:bottom-0 left-0 right-0 md:left-64 z-40 bg-white dark:bg-[#121212] border-t border-gray-200 dark:border-white/10 p-4 shadow-[0_-10px_40px_rgba(0,0,0,0.1)] dark:shadow-[0_-10px_40px_rgba(0,0,0,0.5)] animate-in slide-in-from-bottom-full duration-300">
              <div className="w-full mx-auto flex items-center justify-between gap-4">
                  <div className="flex-1 min-w-0">
                      <p className="text-[10px] font-bold text-gray-500 uppercase tracking-wider mb-0.5">Item Terpilih</p>
                      <div className="flex items-center gap-2">
                          <h4 className="font-black text-gray-900 dark:text-white truncate text-sm md:text-base">
                              {activePkg.name || `${activePkg.amount} Gold`}
                          </h4>
                          <span className="bg-red-100 dark:bg-red-500/20 text-red-600 dark:text-red-400 text-[10px] font-bold px-2 py-0.5 rounded uppercase whitespace-nowrap">
                              {activePkg.price}
                          </span>
                      </div>
                  </div>
                  <button 
                      onClick={() => {
                          const hasPending = transactions.some(trx => trx.status === 'Pending');
                          if (hasPending) {
                              setAlertConfig({
                                  title: "Transaksi Tertunda",
                                  message: "Anda masih memiliki transaksi yang berstatus Pending. Harap tunggu hingga transaksi sebelumnya diproses oleh Admin.",
                                  type: "warning"
                              });
                              return;
                          }
                          setIsModalOpen(true);
                      }}
                      className="bg-red-600 hover:bg-red-700 text-white font-black py-3 px-6 md:px-10 rounded-xl uppercase tracking-widest text-xs md:text-sm shadow-lg shadow-red-600/20 transition-all transform active:scale-95 whitespace-nowrap"
                  >
                      Bayar
                  </button>
              </div>
          </div>
      )}

      {/* Custom Alert Modal */}
      {alertConfig && (
          <div className="fixed inset-0 z-[100] flex items-center justify-center p-4 bg-black/60 backdrop-blur-sm animate-in fade-in duration-200">
              <div className="bg-white dark:bg-[#1a1a1a] rounded-2xl p-6 max-w-sm w-full shadow-2xl border border-gray-200 dark:border-white/10 text-center animate-in zoom-in-95 duration-200">
                  <div className={`w-16 h-16 rounded-full flex items-center justify-center mx-auto mb-4 ${
                      alertConfig.type === 'success' 
                          ? 'bg-green-100 dark:bg-green-500/20 text-green-500' 
                          : 'bg-yellow-100 dark:bg-yellow-500/20 text-yellow-500'
                  }`}>
                      {alertConfig.type === 'success' ? <CheckCircle size={32} /> : <AlertTriangle size={32} />}
                  </div>
                  <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase mb-2">{alertConfig.title}</h3>
                  <p className="text-sm text-gray-600 dark:text-gray-400 mb-6 leading-relaxed">
                      {alertConfig.message}
                  </p>
                  <button 
                      onClick={() => setAlertConfig(null)}
                      className="w-full bg-gray-900 hover:bg-gray-800 dark:bg-white dark:hover:bg-gray-200 text-white dark:text-gray-900 font-bold py-3 rounded-xl transition-colors uppercase tracking-widest text-sm"
                  >
                      Tutup
                  </button>
              </div>
          </div>
      )}

    </div>
  );
};
