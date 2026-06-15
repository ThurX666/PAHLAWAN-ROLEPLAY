
import React, { useState } from 'react';
import { LayoutDashboard, User, LogOut, Settings, CreditCard, Sun, Moon, ShieldAlert, Mail, BookOpen, Menu, X } from 'lucide-react';
import { ADMIN_RANKS } from '../data/mockData';
import { isPreviewEnv, API_URL, getResolvedApiUrl } from '../config';

interface LayoutProps {
  children: React.ReactNode;
  activeTab: string;
  onTabChange: (tab: string) => void;
  onLogout: () => void;
  isDarkMode: boolean;
  toggleTheme: () => void;
  isAdmin?: boolean;
  adminLevel?: number;
  userName?: string;
  unreadCount?: number;
  discordId?: string;
}

export const Layout: React.FC<LayoutProps> = ({ children, activeTab, onTabChange, onLogout, isDarkMode, toggleTheme, isAdmin = false, adminLevel, userName = "Player", unreadCount = 0, discordId }) => {
  const [isMobileMenuOpen, setIsMobileMenuOpen] = React.useState(false);
  const [discordAvatarUrl, setDiscordAvatarUrl] = React.useState<string | null>(null);

  React.useEffect(() => {
    if (discordId && discordId !== '0') {
        let isMounted = true;
        const fetchAvatar = async () => {
             if (isPreviewEnv()) {
                // Mock avatar for preview environment
                if (isMounted) setDiscordAvatarUrl('https://cdn.discordapp.com/avatars/103233864016666624/655c6e838e5399ff8782ee8440590a3a.png');
                return;
             }
             try {
                const resolvedBase = getResolvedApiUrl();
                const cleanAPIUrl = resolvedBase.endsWith('/') ? resolvedBase.slice(0, -1) : resolvedBase;
                const res = await fetch(`${cleanAPIUrl}/api_discord_avatar.php?id=${discordId}`);
                const data = await res.json();
                if (data.status === 'success' && data.url && isMounted) {
                    setDiscordAvatarUrl(data.url);
                }
             } catch (e) {
                console.error("Failed to fetch discord avatar", e);
             }
        };
        fetchAvatar();
        return () => { isMounted = false; };
    } else if (isPreviewEnv()) {
         // Provide a fallback dummy discord avatar in preview mode even if discordId is missing
         setDiscordAvatarUrl('https://cdn.discordapp.com/avatars/103233864016666624/655c6e838e5399ff8782ee8440590a3a.png');
    } else {
         setDiscordAvatarUrl(null);
    }
  }, [discordId]);

  // Grouping menu items for better UX structure on Desktop
  const menuGroups = [
    {
      title: "Main Menu",
      items: [
        { id: 'dashboard', label: 'Dashboard', icon: LayoutDashboard },
        { id: 'tickets', label: 'Pesan & Bantuan', icon: Mail },
      ]
    },
    {
      title: "Gameplay",
      items: [
        { id: 'characters', label: 'Karakter Saya', icon: User },
        { id: 'story', label: 'Character Story', icon: BookOpen },
        { id: 'requests', label: 'Permohonan', icon: Mail },
        { id: 'donation', label: 'VIP & Donasi', icon: CreditCard },
      ]
    },
    {
      title: "System",
      items: [
        { id: 'settings', label: 'Pengaturan', icon: Settings },
        ...(isAdmin ? [{ id: 'admin', label: 'Admin Panel', icon: ShieldAlert }] : [])
      ]
    }
  ];

  const handleTabClick = (id: string) => {
      onTabChange(id);
      setIsMobileMenuOpen(false); 
  };

  return (
    <div className="flex h-[100dvh] bg-gray-50 dark:bg-[#050505] text-gray-900 dark:text-gray-100 overflow-hidden font-sans transition-colors duration-500 relative">
      {/* Background Pattern */}
      <div className="absolute inset-0 z-0 bg-grid-pattern-light dark:bg-grid-pattern opacity-[0.4] pointer-events-none"></div>
      
      {/* Ambient Glow */}
      <div className="absolute top-0 left-0 w-[500px] h-[500px] bg-red-500/10 dark:bg-red-600/10 rounded-full blur-[120px] pointer-events-none"></div>
      <div className="absolute bottom-0 right-0 w-[500px] h-[500px] bg-amber-500/10 dark:bg-amber-600/10 rounded-full blur-[120px] pointer-events-none"></div>

      {/* Mobile Menu Backdrop */}
      {isMobileMenuOpen && (
          <div 
            className="fixed inset-0 bg-black/60 z-40 md:hidden backdrop-blur-sm transition-opacity"
            onClick={() => setIsMobileMenuOpen(false)}
          ></div>
      )}

      {/* Sidebar - Persistent on Desktop/Tablet */}
      <aside className={`
          fixed md:relative inset-y-0 left-0 z-50 
          transition-transform duration-300 ease-in-out
          flex flex-col border-r border-white/20 dark:border-white/5 
          bg-white/95 dark:bg-[#121212] md:bg-white dark:md:bg-[#0a0a0a]
          shadow-2xl md:shadow-none overflow-visible whitespace-nowrap
          
          /* Dimensions */
          w-64 md:w-[260px] lg:w-[280px] xl:w-[300px] flex-shrink-0

          /* Mobile Logic: Slide in/out */
          transform ${isMobileMenuOpen ? 'translate-x-0' : '-translate-x-full'}
          
          /* Desktop Logic: Always visible (Reset transform) */
          md:translate-x-0
      `}>
        
        {/* Mobile Close Button */}
        {isMobileMenuOpen && (
            <button 
                 onClick={() => setIsMobileMenuOpen(false)} 
                 className="md:hidden absolute top-8 -right-12 w-12 h-12 flex items-center justify-center z-50 bg-white/95 dark:bg-[#121212] border-y border-r border-gray-200 dark:border-white/5 rounded-r-xl shadow-[4px_0_15px_rgba(0,0,0,0.1)] dark:shadow-[4px_0_15px_rgba(0,0,0,0.5)] text-gray-500 hover:text-red-500"
            >
                 <X size={24} />
            </button>
        )}

        {/* Header Logo */}
        <div className="relative pt-6 px-6 pb-[14px] flex flex-col items-center flex-shrink-0">
          <div className="w-full h-16 md:h-20 flex items-center justify-center relative group cursor-pointer mb-2">
             <div className="absolute inset-0 bg-red-500/20 blur-xl opacity-0 group-hover:opacity-100 transition-opacity duration-500 rounded-full"></div>
             {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
             <img 
               src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} 
               alt="Pahlawan Roleplay" 
               className="h-full w-auto object-contain relative z-10 drop-shadow-md transform group-hover:scale-105 transition-transform duration-300"
             />
          </div>
        </div>

        {/* Navigation */}
        <nav className="flex-1 px-4 py-2 space-y-6 overflow-y-auto custom-scrollbar">
          {menuGroups.map((group, gIdx) => (
            <div key={gIdx}>
                <h4 className="px-3 mb-2 text-[10px] font-black text-gray-400 dark:text-gray-600 uppercase tracking-widest">{group.title}</h4>
                <div className="space-y-1">
                    {group.items.map((item) => {
                        const Icon = item.icon;
                        const isActive = activeTab === item.id;
                        const isAdminItem = item.id === 'admin';
                        
                        return (
                        <button
                            key={item.id}
                            onClick={() => handleTabClick(item.id)}
                            className={`flex items-center justify-between w-full px-3 py-2.5 rounded-lg transition-all duration-200 group relative ${
                            isActive
                                ? 'bg-red-50 dark:bg-red-900/10 text-red-600 dark:text-red-500 font-bold'
                                : isAdminItem 
                                ? 'text-red-600/70 hover:bg-red-50 dark:hover:bg-red-900/10'
                                : 'text-gray-600 dark:text-gray-400 hover:bg-gray-100 dark:hover:bg-white/5 hover:text-gray-900 dark:hover:text-white'
                            }`}
                        >
                            <div className="flex items-center min-w-0">
                                <Icon className={`w-4 h-4 md:w-5 md:h-5 mr-3 transition-colors flex-shrink-0 ${isActive ? 'text-red-600 dark:text-red-500' : 'text-gray-400 group-hover:text-gray-600 dark:group-hover:text-gray-300'}`} />
                                <span className="text-sm tracking-wide truncate">{item.label}</span>
                            </div>
                            
                            {/* Notification Badge */}
                            {item.id === 'tickets' && unreadCount > 0 && (
                                <span className="bg-red-600 text-white text-[9px] font-bold px-1.5 py-0.5 rounded-md min-w-[18px] text-center shadow-sm ml-2">
                                    {unreadCount}
                                </span>
                            )}
                            
                            {isActive && <div className="w-1 h-4 bg-red-600 rounded-full absolute left-0 top-1/2 -translate-y-1/2"></div>}
                        </button>
                        );
                    })}
                </div>
            </div>
          ))}
        </nav>

        {/* User Footer */}
        <div className="p-4 mt-auto border-t border-gray-100 dark:border-white/5 bg-gray-50 dark:bg-[#0c0c0c] flex-shrink-0">
             <div className="flex items-center justify-between mb-4">
                <div className="flex items-center space-x-3 min-w-0">
                  <div className="w-10 h-10 rounded-lg bg-gradient-to-br from-red-500 to-amber-600 p-[1px] shadow-sm flex-shrink-0">
                     <div className="w-full h-full bg-white dark:bg-[#121212] rounded-[7px] flex items-center justify-center overflow-hidden">
                        {discordAvatarUrl ? (
                            <img src={discordAvatarUrl} alt="Discord Avatar" className="w-full h-full object-cover rounded-[6px]" referrerPolicy="no-referrer" />
                        ) : (
                            <img src="https://cdn.discordapp.com/embed/avatars/0.png" alt="Discord Avatar Default" className="w-full h-full object-cover rounded-[6px] opacity-80" referrerPolicy="no-referrer" />
                        )}
                     </div>
                  </div>
                  <div className="overflow-hidden">
                    <p className="text-sm font-bold text-gray-800 dark:text-gray-200 truncate max-w-[120px]">{userName}</p>
                    <p className="text-[10px] text-gray-500 uppercase tracking-wider font-bold">
                        {isAdmin ? (adminLevel ? ADMIN_RANKS[adminLevel] : 'Administrator') : 'Citizen'}
                    </p>
                  </div>
                </div>
             </div>
             
             <div className="grid grid-cols-2 gap-2">
               <button 
                 onClick={toggleTheme}
                 className="flex items-center justify-center p-2 rounded-lg bg-white dark:bg-[#1a1a1a] border border-gray-200 dark:border-white/10 hover:border-gray-300 dark:hover:border-white/20 text-gray-600 dark:text-gray-400 transition-colors"
               >
                 {isDarkMode ? <Sun size={16} /> : <Moon size={16} />}
               </button>
               <button 
                 onClick={onLogout}
                 className="flex items-center justify-center p-2 rounded-lg bg-red-50 dark:bg-red-900/10 border border-red-100 dark:border-red-900/20 hover:bg-red-100 dark:hover:bg-red-900/30 text-red-600 dark:text-red-500 transition-colors"
               >
                 <LogOut size={16} />
               </button>
             </div>
        </div>
      </aside>

      {/* Main Content Container */}
      <main className="flex-1 flex flex-col h-full relative z-10 overflow-hidden w-full min-w-0">
        
        {/* Mobile Header Bar */}
        <div className="md:hidden flex items-center justify-between p-4 border-b border-gray-200 dark:border-white/5 bg-white/70 dark:bg-[#0a0a0a]/70 backdrop-blur-md sticky top-0 z-30">
            <button onClick={() => setIsMobileMenuOpen(true)} className="p-2 text-gray-600 dark:text-gray-300 active:scale-95 transition-transform">
                <Menu size={24} />
            </button>
            <div className="h-8 flex items-center justify-center">
                {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
                <img 
                    src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} 
                    alt="Pahlawan Roleplay" 
                    className="h-full w-auto object-contain drop-shadow-md"
                />
            </div>
            <div className="w-10 h-10 flex items-center justify-center">
                 {/* Mobile Badge Indicator */}
                 {unreadCount > 0 && (
                    <div className="relative">
                        <Mail size={20} className="text-gray-500"/>
                        <span className="absolute -top-1 -right-1 h-3 w-3 bg-red-600 rounded-full border-2 border-[#0a0a0a]"></span>
                    </div>
                 )}
            </div>
        </div>

        {/* Scrollable Content Area */}
        <div className="flex-1 overflow-y-auto custom-scrollbar p-4 md:p-8 lg:p-10 pb-[calc(81px+env(safe-area-inset-bottom))] md:pb-8">
           <div className="max-w-[1600px] mx-auto w-full min-h-full flex flex-col">
             {children}
           </div>
        </div>

        {/* Mobile Bottom Navigation */}
        <div className="md:hidden fixed bottom-0 left-0 right-0 bg-white/90 dark:bg-[#0a0a0a]/90 backdrop-blur-lg border-t border-gray-200 dark:border-white/10 z-40 pb-safe">
            <div className="flex items-center justify-around p-2">
                {[
                    { id: 'dashboard', icon: LayoutDashboard, label: 'Home', action: () => onTabChange('dashboard') },
                    { id: 'donation', icon: CreditCard, label: 'Donate', action: () => onTabChange('donation') },
                    { id: 'theme', icon: isDarkMode ? Sun : Moon, label: 'Tema', action: toggleTheme },
                    { id: 'settings', icon: Settings, label: 'Setting', action: () => onTabChange('settings') },
                ].map(tab => {
                    const isActive = activeTab === tab.id;
                    const Icon = tab.icon;
                    return (
                        <button
                            key={tab.id}
                            onClick={tab.action}
                            className={`flex flex-col items-center justify-center w-16 h-12 gap-1 transition-colors ${isActive ? 'text-red-600 dark:text-red-500' : 'text-gray-500 dark:text-gray-400 hover:text-gray-900 dark:hover:text-gray-200'}`}
                        >
                            <Icon size={20} className={isActive ? 'animate-bounce-subtle' : ''} />
                            <span className="text-[10px] font-bold">{tab.label}</span>
                        </button>
                    )
                })}
            </div>
        </div>
      </main>
    </div>
  );
};
