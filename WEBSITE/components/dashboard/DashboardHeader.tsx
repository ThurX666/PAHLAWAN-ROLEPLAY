
import React, { useState } from 'react';
import { ServerStats } from '../../types';
import { Copy, Users, Check, LayoutDashboard, Activity, Server, Gamepad2, MapPin } from 'lucide-react';
import { isPreviewEnv } from '../../config';

interface DashboardHeaderProps {
  userName: string;
  stats: ServerStats;
}

export const DashboardHeader: React.FC<DashboardHeaderProps> = ({ userName, stats }) => {
  const [copied, setCopied] = useState(false);
  const serverIP = stats.ip_address || "pahlawan-rp.com:7777";

  const handleCopyIP = () => {
    navigator.clipboard.writeText(serverIP);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  };

  return (
    <div>
      {/* 1. Page Header (Outside Card) */}
      <div className="flex flex-col md:flex-row justify-between items-start md:items-end mb-4 md:mb-6 gap-4 md:gap-6 border-b border-gray-200 dark:border-white/5 pb-4 md:border-none md:pb-0">
        <div className="w-full md:w-auto">
           <div className="flex items-center gap-3 mb-2">
              <div className="p-2 bg-red-600 rounded-lg shadow-lg shadow-red-600/20">
                 <LayoutDashboard className="text-white" size={24} />
              </div>
              <h2 className="text-2xl md:text-4xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter">
                DASHBOARD
              </h2>
           </div>
           <p className="text-xs md:text-sm text-gray-500 dark:text-gray-400 font-medium max-w-2xl leading-relaxed">
              Selamat datang, <span className="text-red-600 font-bold">{userName}!</span> Pantau status server serta statistik akun Anda secara real-time.
           </p>
        </div>
      </div>

      {/* 2. Server Status (Unified Card) */}
      <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-2xl p-4 md:p-6 shadow-sm relative overflow-hidden group">
          {/* Decorative Background */}
          {stats.status === 'Online' && (
            <div className="absolute top-0 right-0 w-1/2 h-full bg-gradient-to-l from-red-600/5 via-transparent to-transparent pointer-events-none"></div>
          )}

          <div className="flex flex-col xl:flex-row xl:items-center justify-between gap-4 xl:gap-8 relative z-10 w-full">
              {stats.status === 'Loading' ? (
                <div className="flex flex-col items-center justify-center py-6 w-full flex-grow border-b xl:border-b-0 border-gray-200 dark:border-white/10 pb-4 xl:pb-0 xl:border-r xl:pr-6">
                   <Server className="text-gray-500 w-10 h-10 animate-pulse mb-3" />
                   <h3 className="text-xl md:text-2xl font-black tracking-widest uppercase text-gray-400 animate-pulse">MEMUAT SERVER...</h3>
                </div>
              ) : stats.status !== 'Online' ? (
                <div className="flex flex-col items-center justify-center py-6 w-full flex-grow border-b xl:border-b-0 border-gray-200 dark:border-white/10 pb-4 xl:pb-0 xl:border-r xl:pr-6">
                   <div className="relative mb-3">
                      <div className="absolute inset-0 bg-red-500 animate-ping rounded-full opacity-20"></div>
                      <div className="p-3 bg-red-500/10 rounded-full relative z-10">
                         <Server className="text-red-500 w-8 h-8" />
                      </div>
                   </div>
                   <h3 className="text-xl md:text-2xl font-black tracking-widest uppercase text-red-500 mt-2 mb-1">SERVER OFFLINE</h3>
                   <p className="text-xs md:text-sm text-gray-500 dark:text-gray-400 text-center max-w-sm">Koneksi ke server terputus atau dalam masa maintenance.</p>
                </div>
              ) : (
                <div className="grid grid-cols-2 lg:grid-cols-4 xl:flex xl:flex-nowrap w-full gap-4 lg:gap-6 flex-grow border-b xl:border-b-0 border-gray-200 dark:border-white/10 pb-4 xl:pb-0 xl:border-r xl:pr-6">
                    {/* Hostname */}
                    <div className="flex items-center gap-2.5 md:gap-3 col-span-2 lg:col-span-1 xl:flex-[2] min-w-[180px]">
                       <div className="p-2.5 rounded-xl bg-red-500/10 text-red-500 shrink-0">
                          <Server size={18} />
                       </div>
                       <div className="overflow-visible w-full">
                          <div className="flex items-center gap-2 mb-0.5">
                             <p className="text-[9px] md:text-[10px] font-bold text-gray-400 uppercase tracking-widest">Hostname</p>
                             {isPreviewEnv() && (
                                <span className="bg-yellow-500/20 text-yellow-600 dark:text-yellow-400 text-[8px] font-bold px-1.5 py-0.5 rounded tracking-wider uppercase">Preview Data</span>
                             )}
                          </div>
                          <h3 className="text-xs md:text-sm lg:text-base font-bold text-gray-900 dark:text-white line-clamp-2 leading-tight w-full" title={stats.hostname || (stats as any).name || 'Unknown'}>{stats.hostname || (stats as any).name || 'Unknown'}</h3>
                       </div>
                    </div>
                    {/* Players */}
                    <div className="flex items-center gap-2.5 md:gap-3 col-span-1 xl:flex-1 min-w-[100px] xl:border-l xl:border-gray-200 xl:dark:border-white/10 xl:pl-6">
                       <div className="p-2.5 rounded-xl bg-blue-500/10 text-blue-500 shrink-0">
                          <Users size={18} />
                       </div>
                       <div>
                          <p className="text-[9px] md:text-[10px] font-bold text-gray-400 uppercase tracking-widest mb-0.5">Players</p>
                          <div className="flex items-baseline gap-1">
                              <h3 className="text-sm md:text-base font-black text-gray-900 dark:text-white italic leading-none">{stats.players || 0}</h3>
                              <span className="text-[9px] md:text-[10px] font-bold text-gray-400">/ {stats.maxPlayers || (stats as any).maxplayers || 1000}</span>
                          </div>
                     </div>
                    </div>
                    {/* Gamemode */}
                    <div className="flex items-center gap-2.5 md:gap-3 col-span-1 xl:flex-[1.5] min-w-[120px] xl:border-l xl:border-gray-200 xl:dark:border-white/10 xl:pl-6">
                       <div className="p-2.5 rounded-xl bg-orange-500/10 text-orange-500 shrink-0">
                          <Gamepad2 size={18} />
                       </div>
                       <div className="overflow-visible w-full">
                          <p className="text-[9px] md:text-[10px] font-bold text-gray-400 uppercase tracking-widest mb-0.5">Gamemode</p>
                          <h3 className="text-xs md:text-sm lg:text-base font-bold text-gray-900 dark:text-white line-clamp-2 leading-tight w-full" title={stats.mode || (stats as any).gamemode || 'Roleplay'}>{stats.mode || (stats as any).gamemode || 'Roleplay'}</h3>
                       </div>
                    </div>
                    {/* Map */}
                    <div className="flex items-center gap-2.5 md:gap-3 col-span-2 lg:col-span-1 xl:flex-1 min-w-[120px] xl:border-l xl:border-gray-200 xl:dark:border-white/10 xl:pl-6">
                       <div className="p-2.5 rounded-xl bg-yellow-500/10 text-yellow-500 shrink-0">
                          <MapPin size={18} />
                       </div>
                       <div className="overflow-visible w-full">
                          <p className="text-[9px] md:text-[10px] font-bold text-gray-400 uppercase tracking-widest mb-0.5">Map</p>
                          <h3 className="text-xs md:text-sm lg:text-base font-bold text-gray-900 dark:text-white line-clamp-2 leading-tight w-full" title={stats.map || (stats as any).mapname || 'San Andreas'}>{stats.map || (stats as any).mapname || 'San Andreas'}</h3>
                       </div>
                    </div>
                </div>
              )}
                
              {/* Action Column */}
              <div className="flex-shrink-0 flex flex-col sm:flex-row xl:flex-col items-center justify-between xl:justify-center gap-2.5 xl:w-[240px] mt-4 xl:mt-0 w-full xl:w-auto">
                 <div className="text-[11px] md:text-xs font-mono text-gray-400 flex items-center justify-between w-full bg-gray-100 dark:bg-white/5 py-2.5 px-3 rounded-xl min-h-[44px]">
                     <span className="truncate flex-1">{stats.status !== 'Online' ? '-:-' : serverIP}</span>
                     <button onClick={handleCopyIP} disabled={stats.status !== 'Online'} className="hover:text-gray-900 dark:hover:text-white transition-colors ml-2 shrink-0 p-1.5 flex items-center justify-center bg-white/5 rounded-md disabled:opacity-50 disabled:cursor-not-allowed" title="Copy IP">
                         {copied ? <Check size={14} className="text-green-500" /> : <Copy size={14} />}
                     </button>
                 </div>
                 {stats.status !== 'Online' ? (
                     <button 
                       disabled
                       className="px-6 py-2.5 xl:py-3 w-full bg-red-600/20 text-red-500/50 dark:bg-white/5 dark:text-gray-500 text-xs md:text-sm font-bold uppercase tracking-wider rounded-xl cursor-not-allowed flex items-center justify-center gap-2 min-h-[44px]"
                     >
                       <Gamepad2 size={16} />
                       <span>PLAY NOW</span>
                     </button>
                 ) : (
                     <a 
                       href={`samp://${serverIP}`}
                       target="_top"
                       rel="noopener noreferrer"
                       className="px-6 py-2.5 xl:py-3 w-full bg-red-600 hover:bg-red-500 text-white text-xs md:text-sm font-bold uppercase tracking-wider rounded-xl shadow-[0_0_15px_rgba(220,38,38,0.4)] hover:shadow-[0_0_25px_rgba(220,38,38,0.6)] transition-all active:scale-95 flex items-center justify-center gap-2 min-h-[44px]"
                     >
                       <Gamepad2 size={16} />
                       <span>PLAY NOW</span>
                     </a>
                 )}
              </div>
          </div>
      </div>
    </div>
  );
};
