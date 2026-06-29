
import React, { Suspense, lazy, useState, useEffect } from 'react';
import { Database, Users, UserCheck, ShieldAlert, Home, Building, Briefcase, Flag, Users as FamilyIcon, ArrowLeft, Search, MessageSquare, FileText, CreditCard, ChevronRight, LayoutDashboard, FileEdit } from 'lucide-react';
import { StatWidget, AssetStatWidget } from '../ui/StatWidget';
import { AssetList } from './overview/AssetList';
import { PageHeader } from '../ui/PageHeader';
import { isPreviewEnv, API_URL } from '../../config';

const EconomyChart = lazy(() => import('./overview/EconomyChart').then(module => ({ default: module.EconomyChart })));
const AssetDetail = lazy(() => import('./overview/AssetDetail').then(module => ({ default: module.AssetDetail })));

const ChartFallback: React.FC = () => (
    <div className="bg-white dark:bg-ph-surface-card rounded-2xl border border-gray-100 dark:border-white/5 p-6 flex min-h-[350px] items-center justify-center shadow-sm">
        <div className="text-center">
            <div className="mx-auto mb-4 h-10 w-10 animate-spin rounded-full border-2 border-gray-300 border-t-gray-900 dark:border-white/20 dark:border-t-white" />
            <p className="text-[10px] font-bold uppercase tracking-[0.3em] text-gray-500 dark:text-gray-400">
                Memuat Grafik...
            </p>
        </div>
    </div>
);

const DetailFallback: React.FC = () => (
    <div className="flex min-h-[320px] items-center justify-center p-6 text-center">
        <div>
            <div className="mx-auto mb-4 h-10 w-10 animate-spin rounded-full border-2 border-gray-300 border-t-gray-900 dark:border-white/20 dark:border-t-white" />
            <p className="text-[10px] font-bold uppercase tracking-[0.3em] text-gray-500 dark:text-gray-400">
                Memuat Detail...
            </p>
        </div>
    </div>
);

interface AdminOverviewProps {
    onNavigate?: (tab: 'overview' | 'players' | 'logs' | 'setup' | 'donations' | 'stories' | 'tickets' | 'tickets:tickets' | string) => void;
    tickets?: any[];
}

export const AdminOverview: React.FC<AdminOverviewProps> = ({ onNavigate, tickets = [] }) => {
  const [viewLevel, setViewLevel] = useState<'main' | 'list' | 'detail'>('main');
  const [selectedCategory, setSelectedCategory] = useState<string | null>(null);
  const [selectedDetailId, setSelectedDetailId] = useState<number | null>(null);

  const [stats, setStats] = useState({ 
        accounts: "0", 
        chars: "0",   
        admins: "0",
        discordMembers: "0",      
        houses: "0",     
        biz: "0",         
        jobs: "0",        
        sidejobs: "0",     
        families: "0",
        pendingCS: 0,
        pendingDonations: 0,
        pendingTickets: 0,
        pendingRequests: 0
    });

    const pendingTicketsCount = tickets.filter(t => t.status === 'Open' || t.status === 'Proses').length;

    useEffect(() => {
        const fetchStats = async () => {
            if (isPreviewEnv()) {
                setStats({
                    accounts: "8,420", 
                    chars: "12,450",   
                    admins: "18",
                    discordMembers: "5,230",      
                    houses: "450",     
                    biz: "85",         
                    jobs: "12",        
                    sidejobs: "8",     
                    families: "24",
                    pendingCS: 2,
                    pendingDonations: 2,
                    pendingTickets: pendingTicketsCount,
                    pendingRequests: 1
                });
                return;
            }

            try {
                const res = await fetch(`${API_URL}/api_overview.php?action=stats`);
                const data = await res.json();
                if (data && data.status === 'success') {
                    setStats({
                        ...data.data,
                        pendingTickets: pendingTicketsCount
                    });
                }
            } catch (e) {
                console.error("Failed to fetch overview stats", e);
            }
        };
        fetchStats();
    }, [pendingTicketsCount]);

  return (
    <div className="space-y-4 md:space-y-6">
        {viewLevel === 'main' && (
            <PageHeader 
                title="Dashboard Overview" 
                icon={LayoutDashboard}
                description="Real-time server statistics and monitoring."
            />
        )}
        
        {/* BREADCRUMB NAVIGATION FOR ASSETS */}
        {viewLevel !== 'main' && (
            <div className="flex items-center gap-2 mb-4 animate-[fadeIn_0.3s_ease-out]">
                <button 
                    onClick={() => {
                        if(viewLevel === 'detail') setViewLevel('list');
                        else setViewLevel('main');
                    }}
                    className="flex items-center gap-1 text-xs font-bold uppercase text-gray-500 hover:text-white transition-colors bg-gray-100 dark:bg-white/5 px-3 py-1.5 rounded-lg"
                >
                    <ArrowLeft size={14} /> Kembali
                </button>
                <span className="text-gray-400 text-xs">/</span>
                <span className="text-xs font-bold uppercase text-red-500">{selectedCategory}</span>
                {viewLevel === 'detail' && (
                        <>
                        <span className="text-gray-400 text-xs">/</span>
                        <span className="text-xs font-bold uppercase text-white">Detail #{selectedDetailId}</span>
                        </>
                )}
            </div>
        )}

        {/* MAIN DASHBOARD */}
        {viewLevel === 'main' && (
            <div className="space-y-6 animate-[fadeIn_0.3s_ease-out]">
                
                {/* ROW 1: KEY METRICS (4 COLUMNS) */}
                <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-4">
                    <StatWidget 
                        icon={Users} 
                        label="Total Akun Terdaftar" 
                        value={stats.accounts} 
                        color="text-blue-500 bg-blue-500/10" 
                        className="h-full"
                    />
                    <StatWidget 
                        icon={UserCheck} 
                        label="Total Karakter Terbuat" 
                        value={stats.chars} 
                        color="text-emerald-500 bg-emerald-500/10" 
                        className="h-full"
                    />
                    <StatWidget 
                        icon={ShieldAlert} 
                        label="Total Admin" 
                        value={stats.admins} 
                        color="text-red-500 bg-red-500/10" 
                        className="h-full"
                    />
                    <StatWidget 
                        icon={MessageSquare} 
                        label="Total Member Discord" 
                        value={stats.discordMembers} 
                        color="text-indigo-500 bg-indigo-500/10" 
                        className="h-full"
                    />
                </div>

                {/* ROW 2: ECONOMY CHART & PENDING ACTIONS (3 COLUMNS) */}
                <div className="grid grid-cols-1 lg:grid-cols-3 gap-6">
                    {/* CHART (2/3) */}
                    <div className="lg:col-span-2 h-full min-h-[350px]">
                        <Suspense fallback={<ChartFallback />}>
                            <EconomyChart />
                        </Suspense>
                    </div>

                    {/* PENDING ACTIONS (1/3) */}
                    <div className="bg-white dark:bg-ph-surface-card rounded-2xl border border-gray-100 dark:border-white/5 p-6 flex flex-col h-full shadow-sm hover:shadow-md transition-shadow duration-300">
                        <h3 className="text-gray-900 dark:text-white font-black uppercase text-sm tracking-widest mb-6 flex items-center">
                            <ShieldAlert className="mr-2 text-red-500" size={20} /> Antrean Tugas
                        </h3>
                        
                        <div className="flex-1 flex flex-col space-y-4">
                            {/* Pending Character Stories */}
                            <div 
                                onClick={() => onNavigate?.('stories')}
                                className="flex items-center justify-between p-4 bg-gray-50 dark:bg-white/5 rounded-xl border border-gray-100 dark:border-white/5 hover:border-red-500/30 hover:bg-gray-100 dark:hover:bg-white/10 transition-all cursor-pointer group"
                            >
                                <div className="flex items-center gap-3">
                                    <div className="p-2 bg-orange-500/10 rounded-lg text-orange-500 group-hover:bg-orange-500 group-hover:text-white transition-colors">
                                        <FileText size={18} />
                                    </div>
                                    <div>
                                        <h4 className="text-xs font-bold text-gray-500 uppercase tracking-wider group-hover:text-gray-900 dark:group-hover:text-white transition-colors">Character Story</h4>
                                        <p className="text-sm font-medium text-gray-900 dark:text-gray-300">Menunggu Review</p>
                                    </div>
                                </div>
                                <div className="flex items-center gap-2">
                                    {stats.pendingCS > 0 ? (
                                        <span className="bg-red-500 text-white text-xs font-bold px-2.5 py-1 rounded-full animate-pulse">
                                            {stats.pendingCS}
                                        </span>
                                    ) : (
                                        <span className="text-gray-400 text-xs font-bold">0</span>
                                    )}
                                    <ChevronRight size={16} className="text-gray-400 group-hover:text-gray-600 dark:group-hover:text-gray-200 transition-transform group-hover:translate-x-1" />
                                </div>
                            </div>

                            {/* Pending Donations */}
                            <div 
                                onClick={() => onNavigate?.('donations')}
                                className="flex items-center justify-between p-4 bg-gray-50 dark:bg-white/5 rounded-xl border border-gray-100 dark:border-white/5 hover:border-red-500/30 hover:bg-gray-100 dark:hover:bg-white/10 transition-all cursor-pointer group"
                            >
                                <div className="flex items-center gap-3">
                                    <div className="p-2 bg-green-500/10 rounded-lg text-green-500 group-hover:bg-green-500 group-hover:text-white transition-colors">
                                        <CreditCard size={18} />
                                    </div>
                                    <div>
                                        <h4 className="text-xs font-bold text-gray-500 uppercase tracking-wider group-hover:text-gray-900 dark:group-hover:text-white transition-colors">Donasi</h4>
                                        <p className="text-sm font-medium text-gray-900 dark:text-gray-300">Menunggu Persetujuan</p>
                                    </div>
                                </div>
                                <div className="flex items-center gap-2">
                                    {stats.pendingDonations > 0 ? (
                                        <span className="bg-red-500 text-white text-xs font-bold px-2.5 py-1 rounded-full animate-pulse">
                                            {stats.pendingDonations}
                                        </span>
                                    ) : (
                                        <span className="text-gray-400 text-xs font-bold">0</span>
                                    )}
                                    <ChevronRight size={16} className="text-gray-400 group-hover:text-gray-600 dark:group-hover:text-gray-200 transition-transform group-hover:translate-x-1" />
                                </div>
                            </div>

                            {/* Pending Requests */}
                            <div 
                                onClick={() => onNavigate?.('requests')}
                                className="flex items-center justify-between p-4 bg-gray-50 dark:bg-white/5 rounded-xl border border-gray-100 dark:border-white/5 hover:border-blue-500/30 hover:bg-gray-100 dark:hover:bg-white/10 transition-all cursor-pointer group"
                            >
                                <div className="flex items-center gap-3">
                                    <div className="p-2 bg-blue-500/10 rounded-lg text-blue-500 group-hover:bg-blue-500 group-hover:text-white transition-colors">
                                        <FileEdit size={18} />
                                    </div>
                                    <div>
                                        <h4 className="text-xs font-bold text-gray-500 uppercase tracking-wider group-hover:text-gray-900 dark:group-hover:text-white transition-colors">Data Request</h4>
                                        <p className="text-sm font-medium text-gray-900 dark:text-gray-300">Menunggu Validasi</p>
                                    </div>
                                </div>
                                <div className="flex items-center gap-2">
                                    {stats.pendingRequests > 0 ? (
                                        <span className="bg-blue-500 text-white text-xs font-bold px-2.5 py-1 rounded-full animate-pulse">
                                            {stats.pendingRequests}
                                        </span>
                                    ) : (
                                        <span className="text-gray-400 text-xs font-bold">0</span>
                                    )}
                                    <ChevronRight size={16} className="text-gray-400 group-hover:text-gray-600 dark:group-hover:text-gray-200 transition-transform group-hover:translate-x-1" />
                                </div>
                            </div>

                            {/* Pending Tickets */}
                            <div 
                                onClick={() => onNavigate?.('tickets:tickets')}
                                className="flex items-center justify-between p-4 bg-gray-50 dark:bg-white/5 rounded-xl border border-gray-100 dark:border-white/5 hover:border-amber-500/30 hover:bg-gray-100 dark:hover:bg-white/10 transition-all cursor-pointer group"
                            >
                                <div className="flex items-center gap-3">
                                    <div className="p-2 bg-amber-500/10 rounded-lg text-amber-500 group-hover:bg-amber-500 group-hover:text-white transition-colors">
                                        <MessageSquare size={18} />
                                    </div>
                                    <div>
                                        <h4 className="text-xs font-bold text-gray-500 uppercase tracking-wider group-hover:text-gray-900 dark:group-hover:text-white transition-colors">Tiket Bantuan</h4>
                                        <p className="text-sm font-medium text-gray-900 dark:text-gray-300">Menunggu Balasan</p>
                                    </div>
                                </div>
                                <div className="flex items-center gap-2">
                                    {stats.pendingTickets > 0 ? (
                                        <span className="bg-amber-500 text-white text-xs font-bold px-2.5 py-1 rounded-full animate-pulse">
                                            {stats.pendingTickets}
                                        </span>
                                    ) : (
                                        <span className="text-gray-400 text-xs font-bold">0</span>
                                    )}
                                    <ChevronRight size={16} className="text-gray-400 group-hover:text-gray-600 dark:group-hover:text-gray-200 transition-transform group-hover:translate-x-1" />
                                </div>
                            </div>

                            <div className="mt-auto pt-4 text-center">
                                <p className="text-[10px] text-gray-400 uppercase tracking-widest">
                                    Selesaikan tugas prioritas tinggi terlebih dahulu.
                                </p>
                            </div>
                        </div>
                    </div>
                </div>
                
                {/* ROW 3: DETAILED ASSET GRID (UNIFORM) */}
                <div className="grid grid-cols-2 md:grid-cols-4 lg:grid-cols-6 gap-4">
                     <AssetStatWidget 
                        label="Total Rumah" 
                        value={stats.houses} 
                        icon={Home} 
                        color="text-blue-500" 
                        onClick={() => { setSelectedCategory('houses'); setViewLevel('list'); }} 
                    />
                    <AssetStatWidget 
                        label="Total Bisnis" 
                        value={stats.biz} 
                        icon={Building} 
                        color="text-emerald-500" 
                        onClick={() => { setSelectedCategory('businesses'); setViewLevel('list'); }}
                    />
                    <AssetStatWidget 
                        label="Total Jobs" 
                        value={stats.jobs} 
                        icon={Briefcase} 
                        color="text-amber-500" 
                        onClick={() => { setSelectedCategory('jobs'); setViewLevel('list'); }}
                    />
                    <AssetStatWidget 
                        label="Sidejobs" 
                        value={stats.sidejobs} 
                        icon={Briefcase} 
                        color="text-orange-500" 
                        onClick={() => { setSelectedCategory('sidejobs'); setViewLevel('list'); }}
                    />
                    <AssetStatWidget 
                        label="Total Fraksi" 
                        value="5" 
                        icon={Flag} 
                        color="text-purple-500" 
                        onClick={() => { setSelectedCategory('factions'); setViewLevel('list'); }}
                    />
                    <AssetStatWidget 
                        label="Total Family" 
                        value={stats.families} 
                        icon={FamilyIcon} 
                        color="text-red-500" 
                        onClick={() => { setSelectedCategory('families'); setViewLevel('list'); }}
                    />
                </div>
            </div>
        )}

        {/* LIST VIEW */}
        {viewLevel === 'list' && (
            <div className="bg-white dark:bg-ph-surface-deep rounded-xl border border-gray-200 dark:border-white/5 overflow-hidden animate-[fadeIn_0.3s_ease-out]">
                <div className="p-4 border-b border-gray-200 dark:border-white/5 flex justify-between items-center">
                    <h3 className="font-bold text-gray-900 dark:text-white uppercase text-sm">List {selectedCategory}</h3>
                    <div className="relative">
                        <Search size={14} className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-500" />
                        <input type="text" placeholder="Cari..." className="bg-gray-100 dark:bg-black/20 pl-8 pr-3 py-1.5 rounded-lg text-xs outline-none focus:border-red-500 border border-transparent" />
                    </div>
                </div>
                <AssetList 
                    category={selectedCategory} 
                    onSelectDetail={(id) => { setSelectedDetailId(id); setViewLevel('detail'); }}
                />
            </div>
        )}

        {/* DETAIL VIEW */}
        {viewLevel === 'detail' && (
            <div className="bg-white dark:bg-ph-surface-deep rounded-xl border border-gray-200 dark:border-white/5 overflow-hidden animate-[fadeIn_0.3s_ease-out]">
                <Suspense fallback={<DetailFallback />}>
                    <AssetDetail category={selectedCategory} detailId={selectedDetailId} />
                </Suspense>
            </div>
        )}
    </div>
  );
};
