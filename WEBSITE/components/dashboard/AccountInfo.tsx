
import React, { useState, useEffect } from 'react';
import { User, Clock, Smartphone, Lock, ShieldCheck, Crown, Coins, Users, ExternalLink } from 'lucide-react';
import { InfoItem } from './InfoItem';
import { isPreviewEnv, API_URL } from '../../config';
import { UserProfile } from '../../types';

interface AccountInfoProps {
    username?: string;
    vipStatus?: { tier: string; expiredAt: string; } | null;
    userGold?: number;
    profile?: UserProfile;
    is2FAEnabled?: boolean;
    onNavigate?: (tab: string) => void;
}

export const AccountInfo: React.FC<AccountInfoProps> = ({ username, vipStatus, userGold = 0, profile, is2FAEnabled, onNavigate }) => {

  const getDeviceName = () => {
    const ua = navigator.userAgent;
    if (ua.includes("Windows NT 10.0")) return "Windows 10/11";
    if (ua.includes("Windows NT 6.3")) return "Windows 8.1";
    if (ua.includes("Windows NT 6.2")) return "Windows 8";
    if (ua.includes("Windows NT 6.1")) return "Windows 7";
    if (ua.includes("Mac OS X")) return "Mac OS";
    if (ua.includes("Android")) return "Android";
    if (ua.includes("iPhone OS") || ua.includes("iPad")) return "iOS";
    if (ua.includes("Linux")) return "Linux";
    return "Unknown Device";
  };

  const [account, setAccount] = useState({
      id: "#8492",
      joinDate: "Senin, 10 Januari 2023\n15:30:00 WIB",
      device: getDeviceName(),
      ip: "192.168.1.100",
      lastLogin: "Rabu, 14 Februari 2023\n10:15:30 WIB",
      vipStatus: "None",
      vipExpired: "-",
      gold: "0 GC",
      security: "Unverified",
      securityDetail: "-",
      charUsed: "0",
      charMax: "3"
  });

  useEffect(() => {
      // Set default mock stats based on props
      let securityStatus = "LOW";
      let securityDetail = "Belum Verifikasi";

      if (is2FAEnabled && profile?.discordId) {
          securityStatus = "VERIFIED";
          securityDetail = "Discord & Email";
      } else if (profile?.discordId) {
          securityStatus = "PARTIAL";
          securityDetail = "Discord Only";
      } else if (is2FAEnabled) {
          securityStatus = "PARTIAL";
          securityDetail = "Email Only";
      }

      setAccount(prev => ({
          ...prev,
          vipStatus: vipStatus ? `VIP ${vipStatus.tier}` : "None",
          vipExpired: vipStatus ? `Exp: ${vipStatus.expiredAt}` : "-",
          gold: `${userGold.toLocaleString('en-US')} GC`,
          security: securityStatus,
          securityDetail: securityDetail,
          charUsed: "2"
      }));

      if (isPreviewEnv()) {
          // Use generic mock data per user request in preview environment
          setAccount(prev => ({
              ...prev,
              ip: "192.168.1.100\n(Jakarta, ID)",
              device: getDeviceName(),
              id: "#8492"
          }));
          return;
      }

      const userToFetch = username || 'player'; 
      
      // Fetch Account Info
      fetch(`${API_URL}/api_account_info.php?username=${userToFetch}`)
          .then(response => response.json())
          .then(data => {
              if (data && data.status !== 'error') {
                 setAccount(prev => ({
                     ...prev,
                     id: data.id,
                     joinDate: data.joinDate,
                     device: data.device && data.device !== "Unknown Device" ? data.device : getDeviceName(),
                     ip: (data.ip && data.ip.length > 5) ? data.ip : prev.ip,
                     lastLogin: data.lastLogin
                 }));
              }
          })
          .catch(error => console.error("Error fetching account info:", error));

      // Fetch User Stats
      fetch(`${API_URL}/api_user_stats.php?username=${userToFetch}`)
          .then(response => response.json())
          .then(data => {
              if (data && data.status !== 'error') {
                  setAccount(prev => ({
                      ...prev,
                      vipStatus: data.vipStatus,
                      vipExpired: data.vipExpired,
                      gold: data.gold,
                      security: data.security,
                      securityDetail: data.securityDetail,
                      charUsed: data.charUsed,
                      charMax: data.charMax
                  }));
              }
          })
          .catch(error => console.error("Error fetching user stats:", error));

  }, [username, vipStatus, userGold, profile, is2FAEnabled]);

  return (
    <div className="flex flex-col h-full">
        <div className="flex items-center justify-between mb-4">
            <h3 className="text-sm md:text-base font-bold text-gray-900 dark:text-white uppercase tracking-wider flex items-center">
                <User className="mr-2 text-red-500" size={18} /> Informasi Akun
            </h3>
            <span className="text-[10px] font-mono text-gray-500 bg-gray-100 dark:bg-white/5 px-2 py-1 rounded-lg border border-gray-200 dark:border-white/5">{account.id}</span>
        </div>
        
        <div className="flex flex-col gap-2.5 flex-1">
             <InfoItem icon={Clock} label="Bergabung" value={account.joinDate} />
             <InfoItem icon={Smartphone} label="Perangkat" value={account.device} />
             <InfoItem icon={Lock} label="IP Address" value={account.ip} />
             
             {/* New Integration */}
             <InfoItem 
                icon={Crown} 
                label="VIP Status" 
                value={account.vipStatus} 
             />
             <InfoItem 
                icon={Coins} 
                label="Gold Coin" 
                value={account.gold} 
                rightElement={
                    <button 
                        onClick={() => onNavigate && onNavigate('donation:gold')} 
                        className="bg-black/80 dark:bg-white/10 hover:bg-black dark:hover:bg-white/20 text-white text-[10px] px-2.5 py-1 md:px-3 md:py-1.5 rounded-md cursor-pointer flex items-center gap-1.5 transition-colors shadow-sm font-semibold whitespace-nowrap"
                    >
                        Top Up <ExternalLink size={12} />
                    </button>
                }
             />
             <InfoItem 
                icon={ShieldCheck} 
                label="Security" 
                value={account.security} 
             />
             <InfoItem 
                icon={Users} 
                label="Char Slot" 
                value={`${account.charUsed} / ${account.charMax}`} 
             />
        </div>
        
        <div className="mt-4 pt-4 border-t border-gray-200 dark:border-white/5 text-center">
            <p className="text-[10px] text-gray-400 whitespace-pre-line leading-relaxed">Terakhir login: {account.lastLogin}</p>
        </div>
    </div>
  );
};
