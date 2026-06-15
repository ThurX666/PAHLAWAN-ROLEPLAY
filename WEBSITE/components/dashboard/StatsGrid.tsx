
import React, { useState, useEffect } from 'react';
import { Crown, Coins, ShieldCheck, User, ExternalLink, AlertTriangle } from 'lucide-react';
import { getVipStyle } from '../../utils/vip';
import { StatCard } from './StatCard';
import { UserProfile } from '../../types';

import { isPreviewEnv, API_URL } from '../../config';

interface StatsGridProps {
    onNavigate: (tab: string) => void;
    vipStatus?: { tier: string; expiredAt: string; } | null;
    userGold?: number;
    profile: UserProfile;
    is2FAEnabled: boolean;
    username?: string;
}

export const StatsGrid: React.FC<StatsGridProps> = ({ onNavigate, vipStatus, userGold = 0, profile, is2FAEnabled, username }) => {

  const [userStats, setUserStats] = useState({
      vipStatus: "None",
      vipExpired: "-",
      gold: "0 GC",
      security: "Unverified",
      securityDetail: "-",
      charUsed: "0",
      charMax: "3"
  });

  useEffect(() => {
      // Setup default mock values based on profile context
      let securityStatus = "LOW";
      let securityDetail = "Belum Verifikasi";

      if (is2FAEnabled && profile.discordId) {
          securityStatus = "VERIFIED";
          securityDetail = "Discord & Email";
      } else if (profile.discordId) {
          securityStatus = "PARTIAL";
          securityDetail = "Discord Only";
      } else if (is2FAEnabled) {
          securityStatus = "PARTIAL";
          securityDetail = "Email Only";
      }

      setUserStats(prev => ({
          ...prev,
          vipStatus: vipStatus ? `VIP ${vipStatus.tier}` : "None",
          vipExpired: vipStatus ? `Exp: ${vipStatus.expiredAt}` : "-",
          gold: `${userGold.toLocaleString('en-US')} GC`,
          security: securityStatus,
          securityDetail: securityDetail,
          charUsed: "2"
      }));

      // If NOT in preview mode, fetch from actual API
      if (!isPreviewEnv()) {
          const userToFetch = username || 'player';
          fetch(`${API_URL}/api_user_stats.php?username=${userToFetch}`)
              .then(response => response.json())
              .then(data => {
                  if (data && data.status !== 'error') {
                      setUserStats(prev => ({
                          ...prev,
                          ...data // API returns mapped values
                      }));
                  }
              })
              .catch(error => console.error("Error fetching user stats:", error));
      }
  }, [vipStatus, userGold, profile, is2FAEnabled, username]);

  // Styling VIP & Security icons from state
  const vipStyle = getVipStyle(userStats.vipStatus.replace('VIP ', ''));


  let securityColor = "from-red-400 to-red-600";
  let SecurityIcon = AlertTriangle;

  if (userStats.security === "VERIFIED") {
      securityColor = "from-emerald-400 to-teal-600";
      SecurityIcon = ShieldCheck;
  } else if (userStats.security === "PARTIAL") {
      securityColor = "from-yellow-400 to-amber-600";
      SecurityIcon = ShieldCheck;
  }

  return (
    <div className="grid grid-cols-2 lg:grid-cols-4 gap-3 md:gap-6">
        <StatCard 
            title="VIP Status" 
            value={userStats.vipStatus} 
            icon={vipStyle.icon} 
            color={vipStyle.gradientClass} 
            subValue={userStats.vipExpired}
        />
        
        <StatCard 
            title="Gold Coin" 
            value={userStats.gold} 
            icon={Coins} 
            color="from-yellow-400 to-amber-600" 
            subValue={
              <button 
                onClick={() => onNavigate('donation:gold')} 
                className="hover:text-yellow-500 hover:underline decoration-dotted transition-all flex items-center gap-1"
              >
                Top Up <ExternalLink size={10} className="md:w-3 md:h-3" />
              </button>
            }
            isCurrency
        />

        <StatCard 
            title="Security" 
            value={userStats.security} 
            icon={SecurityIcon} 
            color={securityColor} 
            subValue={userStats.securityDetail}
        />

        <StatCard 
            title="Char Slot" 
            value={`${userStats.charUsed} / ${userStats.charMax}`} 
            icon={User} 
            color="from-gray-400 to-gray-600 dark:from-gray-700 dark:to-gray-900" 
            subValue={`${parseInt(userStats.charMax) - parseInt(userStats.charUsed)} Tersedia`}
        />
    </div>
  );
};
