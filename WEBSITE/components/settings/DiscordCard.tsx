
import React, { useState, useEffect } from 'react';
import { MessageSquare, CheckCheck, RefreshCw, Shield, Lightbulb, Scale, Bug, Terminal, Rocket, Briefcase, Handshake, ShieldCheck, Bot, Tent } from 'lucide-react';
import { isPreviewEnv, API_URL, getResolvedApiUrl } from '../../config';

interface DiscordCardProps {
    discordId?: string;
    onLink: () => void;
}

export const DiscordCard: React.FC<DiscordCardProps> = ({ discordId, onLink }) => {
  const [profileData, setProfileData] = useState<any>(null);
  const [isLoading, setIsLoading] = useState(false);
  const [isUpdating, setIsUpdating] = useState(false);

  const dId = discordId ? discordId.trim() : '';
  const isLinked = dId !== '' && dId !== '0' && dId.length > 5;

  const fetchProfile = async (update = false) => {
      if (!isLinked) {
          setProfileData(null);
          return;
      }
      if (update) setIsUpdating(true);
      else setIsLoading(true);

      try {
          const resolvedBase = getResolvedApiUrl();
          const cleanAPIUrl = resolvedBase.endsWith('/') ? resolvedBase.slice(0, -1) : resolvedBase;
          const res = await fetch(`${cleanAPIUrl}/api_discord_profile.php?id=${dId}`);
          const data = await res.json();
          if (data.status === 'success') {
              setProfileData(data);
          } else {
              setProfileData(null);
          }
      } catch (e) {
          console.error(e);
      } finally {
          setIsLoading(false);
          setIsUpdating(false);
      }
  };

  useEffect(() => {
    fetchProfile();
  }, [discordId, isLinked]);

  // Format date helper
  const formatDate = (dateStr?: string) => {
      if (!dateStr) return '-';
      const d = new Date(dateStr);
      const day = d.getDate();
      const monthIdx = d.getMonth();
      const year = d.getFullYear();
      const h = String(d.getHours()).padStart(2, '0');
      const m = String(d.getMinutes()).padStart(2, '0');
      const months = ['Januari', 'Februari', 'Maret', 'April', 'Mei', 'Juni', 'Juli', 'Agustus', 'September', 'Oktober', 'November', 'Desember'];
      
      const yearsAgo = new Date().getFullYear() - year;
      const agoText = yearsAgo > 0 ? `(${yearsAgo} years ago)` : '';
      return `${day} ${months[monthIdx]} ${year} ${h}.${m} ${agoText}`;
  };

  return (
    <div className="h-full flex flex-col justify-center bg-white dark:bg-ph-surface-card p-6 md:p-8 rounded-2xl md:rounded-3xl border border-gray-200 dark:border-white/10 relative overflow-hidden group">
        {/* Subtle glow effect */}
        <div className="absolute -top-10 -right-10 w-40 h-40 bg-[#5865F2]/20 rounded-full blur-[50px] opacity-0 group-hover:opacity-100 transition-opacity duration-700 pointer-events-none"></div>

        <div className="relative z-10 w-full">
            <div className="flex items-center justify-between mb-4">
                <div className="flex items-center gap-3">
                   <h3 className="text-lg md:text-xl font-black text-gray-900 dark:text-white uppercase tracking-tight">Discord</h3>
                   {isLinked && (
                       <div className="bg-green-500/10 px-2.5 py-1 rounded-full text-green-600 dark:text-green-400 text-[10px] md:text-xs font-bold border border-green-500/20 flex items-center">
                           <CheckCheck className="mr-1" size={14}/> 
                           <span>Terhubung</span>
                       </div>
                   )}
                </div>
                {isLinked && (
                    <button 
                         onClick={() => fetchProfile(true)}
                         disabled={isUpdating}
                         className="flex items-center gap-2 bg-[#5865F2]/10 hover:bg-[#5865F2]/20 text-[#5865F2] px-3 py-1.5 md:py-2 md:px-4 rounded-lg font-bold text-[10px] md:text-xs uppercase tracking-wider transition-all border border-[#5865F2]/20 shadow-sm whitespace-nowrap"
                    >
                         <RefreshCw size={14} className={isUpdating ? 'animate-spin' : ''} />
                         <span>{isUpdating ? 'Updating' : 'Update'}</span>
                    </button>
                )}
            </div>

            {!isLinked && (
                 <>
                    <p className="text-gray-500 dark:text-gray-400 text-[10px] md:text-xs mb-6 font-medium leading-relaxed">
                        Tautkan akun Discord untuk sinkronisasi role donatur & akses channel eksklusif.
                    </p>
                    <button 
                        onClick={onLink}
                        className="w-full bg-[#5865F2] hover:bg-[#4752C4] text-white py-3 md:py-3.5 rounded-xl font-bold text-[10px] md:text-xs uppercase tracking-widest transition-all shadow-[0_0_15px_rgba(88,101,242,0.3)] hover:shadow-[0_0_25px_rgba(88,101,242,0.5)] transform hover:-translate-y-0.5 active:translate-y-0"
                    >
                        Sambungkan
                    </button>
                 </>
            )}

            {isLinked && profileData && !isLoading && (
                <div className="mt-4 border-t border-gray-200 dark:border-white/10 pt-4 flex flex-col gap-4">
                    <div className="flex justify-between items-start">
                        <div>
                            <div className="flex items-center gap-2 mb-2">
                                <div className="w-6 h-6 md:w-8 md:h-8 rounded-full overflow-hidden flex-shrink-0 bg-[#5865F2]/20">
                                    {profileData?.avatar ? (
                                        <img src={profileData.avatar} alt="Discord Avatar Mini" className="w-full h-full object-cover" referrerPolicy="no-referrer" />
                                    ) : (
                                        <MessageSquare size={14} className="w-full h-full p-1 text-[#5865F2]" />
                                    )}
                                </div>
                                <h4 className="text-sm md:text-md font-bold text-gray-900 dark:text-gray-100">
                                    {profileData.username ? `@${profileData.username}` : <span className="text-gray-400 italic">Unknown</span>}
                                </h4>
                            </div>
                        </div>
                        <div className="w-16 h-16 md:w-20 md:h-20 bg-[#5865F2]/10 rounded-xl flex items-center justify-center border border-[#5865F2]/20 shadow-inner overflow-hidden flex-shrink-0">
                            {profileData?.avatar ? (
                                <img src={profileData.avatar} alt="Discord Profile" className="w-full h-full object-cover" referrerPolicy="no-referrer" />
                            ) : (
                                <MessageSquare size={28} className="text-[#5865F2]" />
                            )}                            
                        </div>
                    </div>

                    <div className="grid grid-cols-2 gap-4">
                        <div>
                            <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-1">ID</p>
                            <p className="text-xs md:text-sm text-gray-600 dark:text-gray-300 font-mono">{dId}</p>
                        </div>
                        <div>
                            <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-1">Nickname</p>
                            <p className="text-xs md:text-sm text-gray-900 dark:text-gray-200 font-medium">
                                {profileData.nickname || profileData.global_name || <span className="text-gray-400 italic">-</span>}
                            </p>
                        </div>
                    </div>
                    
                    {profileData.flags && profileData.flags.length > 0 && (
                        <div>
                            <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-1">Badges</p>
                            <div className="flex flex-wrap gap-2">
                                {profileData.flags.map((flag: string) => {
                                    let Icon = undefined;
                                    let iconPath = '';
                                    if (flag === 'House Bravery Member') iconPath = 'icons8-discord-hypesquad-bravery-house-badge-50.png';
                                    else if (flag === 'House Brilliance Member') iconPath = 'icons8-discord-hypesquad-brilliance-house-badge-50.png';
                                    else if (flag === 'House Balance Member') iconPath = 'icons8-discord-hypesquad-balance-house-badge-50.png';
                                    else if (flag === 'Bug Hunter Level 2') iconPath = 'icons8-discord-golden-bug-hunter-badge-50.png';
                                    else if (flag === 'Bug Hunter Level 1') iconPath = 'icons8-discord-bug-hunter-badge-50.png';
                                    else if (flag === 'Active Developer') iconPath = 'icons8-discord-active-developer-badge-50.png';
                                    else if (flag === 'Early Verified Bot Developer') iconPath = 'icons8-discord-early-verified-bot-developer-badge-50.png';
                                    else if (flag === 'Early Nitro Supporter') iconPath = 'icons8-discord-early-supporter-badge-50.png';
                                    else if (flag === 'Discord Employee' || flag.includes('Staff')) iconPath = 'icons8-discord-staff-badge-50.png';
                                    else if (flag === 'Partnered Server Owner') iconPath = 'icons8-discord-partner-server-owner-badge-50.png';
                                    else if (flag === 'Discord Certified Moderator') iconPath = 'icons8-discord-moderator-program-alumni-badge-50.png';
                                    else if (flag === 'HypeSquad Events Member') iconPath = 'icons8-discord-hypesquad-events-badge-50.png';
                                    else if (flag.includes('Nitro')) iconPath = 'icons8-discord-nitro-badge-50.png';

                                    if (iconPath) {
                                        Icon = <img src={`uploads/discord-badges/${iconPath}`} alt={flag} className="w-[18px] h-[18px] object-contain mr-1.5" referrerPolicy="no-referrer" />;
                                    } else {
                                        Icon = <MessageSquare size={14} className="mr-1.5" />;
                                    }

                                    return (
                                        <span key={flag} className="text-[10.5px] font-bold px-2.5 py-1.5 bg-[#5865F2]/5 text-[#5865F2] rounded-full uppercase tracking-wider flex items-center shadow-sm border border-[#5865F2]/20">
                                            {Icon}
                                            {flag.replace(/_/g, ' ')}
                                        </span>
                                    );
                                })}
                            </div>
                        </div>
                    )}

                    <div>
                        <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-1">Created Date</p>
                        <p className="text-xs md:text-sm text-gray-900 dark:text-gray-200 bg-gray-100 dark:bg-white/5 inline-block py-1 px-2 rounded tabular-nums">
                             {formatDate(profileData.created_at)}
                        </p>
                    </div>

                    <div>
                        <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-1">Join Date</p>
                        <p className="text-xs md:text-sm text-gray-900 dark:text-gray-200 bg-gray-100 dark:bg-white/5 inline-block py-1 px-2 rounded tabular-nums">
                             {profileData.joined_at ? formatDate(profileData.joined_at) : <span className="text-gray-400 italic">Tidak tersedia / Bot belum ada di server</span>}
                        </p>
                    </div>

                    {profileData.roles && profileData.roles.length > 0 && (
                        <div>
                            <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-2">Roles [{profileData.roles.length}]</p>
                            <div className="flex flex-wrap gap-2">
                                {profileData.roles.map((r: any) => {
                                    const colorStr = r.color ? `#${r.color.toString(16).padStart(6, '0')}` : '#99aab5';
                                    return (
                                        <span key={r.id} className="text-[10px] md:text-xs font-medium px-2.5 py-1 rounded-md flex items-center gap-1.5" style={{ backgroundColor: `${colorStr}20`, color: colorStr, border: `1px solid ${colorStr}40` }}>
                                            <span className="w-2 h-2 rounded-full" style={{ backgroundColor: colorStr }}></span>
                                            @{r.name}
                                        </span>
                                    );
                                })}
                            </div>
                        </div>
                    )}
                    
                    {profileData.permissions && profileData.permissions.length > 0 && (
                        <div>
                            <p className="text-[10px] md:text-xs text-gray-500 font-bold uppercase tracking-wider mb-2">Permission(s)</p>
                            <p className="text-xs md:text-sm text-gray-900 dark:text-gray-200">
                                {profileData.permissions.join(', ')}
                            </p>
                        </div>
                    )}
                    
                    {profileData.debug_bot_error && (
                         <div className="mt-2 bg-red-100 dark:bg-red-900/20 text-red-600 dark:text-red-400 p-2 rounded text-xs border border-red-200 dark:border-red-900/50 flex flex-col gap-1">
                             <p className="font-bold">Bot API Error:</p>
                             <p>{profileData.debug_bot_error}</p>
                         </div>
                    )}
                    {profileData.debug_guild_error && !profileData.debug_bot_error && (
                         <div className="mt-2 bg-yellow-100 dark:bg-yellow-900/20 text-yellow-700 dark:text-yellow-500 p-2 rounded text-xs border border-yellow-200 dark:border-yellow-900/50 flex flex-col gap-1">
                             <p className="font-bold">Guild Server Sync Warning:</p>
                             <p>{profileData.debug_guild_error}</p>
                         </div>
                    )}
                </div>
            )}
        </div>
    </div>
  );
};
