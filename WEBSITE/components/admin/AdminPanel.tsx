
import React, { useState, useEffect } from 'react';
import { ShieldAlert, Users, Database, Terminal, CreditCard, BookOpen, Code, MonitorX, FileEdit, HelpCircle, LifeBuoy } from 'lucide-react';
import { PromoItem, InboxMessage } from '../../types';
import { AdminOverview } from './AdminOverview';
import { AdminPlayers } from './AdminPlayers';
import { AdminDonations } from './AdminDonations';
import { AdminStories } from './AdminStories';
import { AdminSetup } from './AdminSetup';
import { AdminLogs } from './AdminLogs';
import { AdminRequests } from './AdminRequests';
import { AdminGuide } from './AdminGuide';
import { AdminBroadcast } from './AdminBroadcast';
import { ADMIN_RANKS } from '../../data/mockData';

interface PromoConfig {
  isActive: boolean;
  title: string;
  message: string;
}

interface AdminPanelProps {
  promoConfig?: PromoConfig;
  onUpdatePromo?: (config: PromoConfig) => void;
  promoItems?: PromoItem[];
  onUpdatePromoItems?: React.Dispatch<React.SetStateAction<PromoItem[]>>;
  onSendNotification?: (msg: InboxMessage) => void;
  onMainNavigate?: (tab: string) => void;
  adminLevel?: number;
  tickets?: any[];
  onOocReviewed?: (username: string, type: string, status: string, feedback: string) => void;
  onStoryReviewed?: (characterName: string, status: string, feedback: string) => void;
}

export const AdminPanel: React.FC<AdminPanelProps> = ({ promoConfig, onUpdatePromo, promoItems = [], onUpdatePromoItems, onSendNotification, onMainNavigate, adminLevel = 10, tickets = [], onOocReviewed, onStoryReviewed }) => {
  const availableTabs = [
    { id: 'overview', label: 'Home', icon: Database, minLevel: 5 },
    { id: 'tickets', label: 'Tiket', icon: LifeBuoy, minLevel: 1 },
    { id: 'players', label: 'Warga', icon: Users, minLevel: 5 },
    { id: 'requests', label: 'Requests', icon: FileEdit, minLevel: 5 },
    { id: 'broadcast', label: 'Siaran', icon: Terminal, minLevel: 10 },
    { id: 'donations', label: 'Donasi', icon: CreditCard, minLevel: 10 },
    { id: 'stories', label: 'Stories', icon: BookOpen, minLevel: 5 },
    { id: 'logs', label: 'Logs', icon: Terminal, minLevel: 5 },
    { id: 'setup', label: 'Setup', icon: Code, minLevel: 10 },
    { id: 'guide', label: 'Panduan', icon: HelpCircle, minLevel: 10 },
  ].filter(tab => adminLevel >= tab.minLevel);

  const [activeTab, setActiveTab] = useState<string>(
      availableTabs.find(t => t.id === 'overview') ? 'overview' : (availableTabs[0]?.id || '')
  );
  const [isMobile, setIsMobile] = useState(false);

  const adminRankName = ADMIN_RANKS[adminLevel] || "Unknown Rank";

  useEffect(() => {
    const checkMobile = () => {
      setIsMobile(window.innerWidth < 1024); // 1024px is lg breakpoint, suitable for complex admin panels
    };
    
    // Check initially
    checkMobile();
    
    // Add event listener
    window.addEventListener('resize', checkMobile);
    
    // Cleanup
    return () => window.removeEventListener('resize', checkMobile);
  }, []);

  const handleOverviewNavigate = (tab: string) => {
      if (tab.startsWith('tickets')) {
          onMainNavigate?.(tab);
      } else {
          setActiveTab(tab as any);
      }
  };

  if (isMobile) {
    return (
      <div className="flex flex-col items-center justify-center min-h-[60vh] text-center px-6 animate-[fadeIn_0.5s_ease-out]">
        <div className="w-24 h-24 bg-red-100 dark:bg-red-900/20 rounded-full flex items-center justify-center mb-6 shadow-lg shadow-red-500/10 border border-red-200 dark:border-red-500/20">
          <MonitorX size={48} className="text-red-600 dark:text-red-500" />
        </div>
        <h2 className="text-2xl md:text-3xl font-black text-gray-900 dark:text-white uppercase italic tracking-tight mb-3">
          Akses Dibatasi
        </h2>
        <p className="text-sm text-gray-600 dark:text-gray-400 max-w-md mx-auto leading-relaxed mb-8">
          Demi alasan keamanan dan kenyamanan pengelolaan data yang kompleks, <strong>Admin Panel</strong> hanya dapat diakses melalui perangkat Desktop atau Laptop (layar lebar).
        </p>
        <button 
          onClick={() => onMainNavigate?.('dashboard')}
          className="bg-gray-900 dark:bg-white text-white dark:text-gray-900 px-8 py-3 rounded-xl font-bold text-sm uppercase tracking-widest hover:bg-gray-800 dark:hover:bg-gray-100 transition-colors shadow-xl"
        >
          Kembali ke Dashboard
        </button>
      </div>
    );
  }

  return (
    <div className="space-y-4 md:space-y-6 text-gray-900 dark:text-white">
      <header className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 p-4 md:p-6 rounded-xl shadow-xl flex flex-col md:flex-row items-center justify-between gap-4 relative overflow-hidden">
        <div className="absolute top-0 left-0 w-1 h-full bg-gradient-to-b from-red-600 to-red-900"></div>
        <div className="flex items-center gap-4 relative z-10 w-full md:w-auto">
             <div className="p-3 bg-gradient-to-br from-red-600 to-red-800 rounded-xl shadow-lg shadow-red-600/20 border border-white/10 shrink-0">
                 <ShieldAlert className="text-white" size={28} />
             </div>
             <div>
                 <h2 className="text-2xl md:text-3xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-2 flex-wrap">
                    ADMIN PANEL
                 </h2>
                 <div className="flex items-center gap-2 mt-1">
                    <span className="bg-red-100 dark:bg-red-900/30 text-red-700 dark:text-red-400 text-[10px] font-bold px-2 py-0.5 rounded-full uppercase tracking-wider border border-red-200 dark:border-red-800/50">
                        Level {adminLevel}
                    </span>
                    <p className="text-sm font-medium text-gray-600 dark:text-gray-400">{adminRankName}</p>
                 </div>
             </div>
        </div>
        
        <div className="flex bg-gray-100 dark:bg-black/40 p-1.5 rounded-xl border border-gray-200 dark:border-white/10 backdrop-blur-md overflow-x-auto w-full md:w-auto scrollbar-hide gap-1">
            {availableTabs.map(tab => (
                <button
                    key={tab.id}
                    onClick={() => setActiveTab(tab.id as any)}
                    className={`flex items-center px-4 py-2 rounded-lg text-xs font-bold uppercase transition-all whitespace-nowrap ${activeTab === tab.id ? 'bg-white dark:bg-white/10 text-gray-900 dark:text-white shadow-sm border border-gray-300 dark:border-white/5' : 'text-gray-500 hover:text-gray-700 dark:hover:text-gray-300 hover:bg-gray-200/50 dark:hover:bg-white/5'}`}
                >
                    <tab.icon size={14} className="mr-2" />
                    {tab.label}
                </button>
            ))}
        </div>
      </header>

      <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-xl p-3 md:p-6 min-h-[400px] shadow-2xl relative">
        {activeTab === 'overview' && <AdminOverview onNavigate={handleOverviewNavigate} tickets={tickets} />}
        {activeTab === 'tickets' && (
            <div className="flex flex-col items-center justify-center min-h-[400px] text-center animate-[fadeIn_0.5s_ease-out]">
                <div className="w-20 h-20 bg-blue-100 dark:bg-blue-900/20 rounded-full flex items-center justify-center mb-6 shadow-lg shadow-blue-500/10">
                    <LifeBuoy size={40} className="text-blue-600 dark:text-blue-500" />
                </div>
                <h3 className="text-2xl font-black mb-2 text-gray-900 dark:text-white uppercase tracking-tighter">Sistem Tiket Bantuan</h3>
                <p className="text-gray-500 dark:text-gray-400 mb-8 max-w-sm mx-auto">Silahkan kelola semua percakapan dan keluhan Player melalui menu panel tiket khusus.</p>
                <button 
                    onClick={() => onMainNavigate?.('tickets:tickets')} 
                    className="px-8 py-3 bg-blue-600 hover:bg-blue-700 text-white font-bold rounded-xl shadow-xl shadow-blue-600/20 uppercase tracking-widest text-sm transition-all"
                >
                    Buka Panel Tiket
                </button>
            </div>
        )}
        {activeTab === 'players' && <AdminPlayers />}
        {activeTab === 'requests' && <AdminRequests onOocReviewed={onOocReviewed} />}
        {activeTab === 'broadcast' && <AdminBroadcast onSendNotification={onSendNotification} />}
        {activeTab === 'donations' && (
            <AdminDonations 
                promoConfig={promoConfig} 
                onUpdatePromo={onUpdatePromo}
                promoItems={promoItems}
                onUpdatePromoItems={onUpdatePromoItems}
                onSendNotification={onSendNotification}
            />
        )}
        {activeTab === 'stories' && <AdminStories onStoryReviewed={onStoryReviewed} />}
        {activeTab === 'setup' && <AdminSetup />}
        {activeTab === 'logs' && <AdminLogs />}
        {activeTab === 'guide' && <AdminGuide />}
      </div>
    </div>
  );
};
