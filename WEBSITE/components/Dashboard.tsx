
import React, { Suspense, lazy } from 'react';
import { ServerStats, UserProfile } from '../types';
import { DashboardHeader } from './dashboard/DashboardHeader';
import { AccountInfo } from './dashboard/AccountInfo';
import { PlayerTable } from './dashboard/PlayerTable';

const ActivityChart = lazy(() => import('./dashboard/ActivityChart').then(module => ({ default: module.ActivityChart })));

const ChartFallback: React.FC = () => (
  <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-xl md:rounded-2xl p-5 md:p-6 shadow-sm flex min-h-[300px] items-center justify-center">
    <div className="text-center">
      <div className="mx-auto mb-4 h-10 w-10 animate-spin rounded-full border-2 border-gray-300 border-t-gray-900 dark:border-white/20 dark:border-t-white" />
      <p className="text-[10px] font-bold uppercase tracking-[0.3em] text-gray-500 dark:text-gray-400">
        Memuat Grafik...
      </p>
    </div>
  </div>
);

interface DashboardProps {
  stats: ServerStats;
  userName: string;
  onNavigate: (tab: string) => void;
  vipStatus?: { tier: string; expiredAt: string; } | null;
  userGold?: number;
  profile: UserProfile;
  is2FAEnabled: boolean;
}

export const Dashboard: React.FC<DashboardProps> = ({ stats, userName, onNavigate, vipStatus, userGold = 0, profile, is2FAEnabled }) => {

  return (
    <div className="animate-[fadeIn_0.5s_ease-out]">
      {/* Desktop Layout: CSS Grid 12 Columns */}
      <div className="grid grid-cols-1 xl:grid-cols-12 gap-4 lg:gap-6">
        
        {/* Header: Full Width */}
        <div className="col-span-1 xl:col-span-12">
            <DashboardHeader userName={userName} stats={stats} />
        </div>

        {/* Bottom Row: Account Info & Player Table */}
        {/* Account Info */}
        <div className="col-span-1 xl:col-span-4 bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-2xl shadow-sm p-4 md:p-5 flex flex-col gap-4">
            <AccountInfo 
                username={userName} 
                vipStatus={vipStatus} 
                userGold={userGold} 
                profile={profile} 
                is2FAEnabled={is2FAEnabled} 
                onNavigate={onNavigate} 
            />
        </div>

        {/* Player Table */}
        <div className="col-span-1 xl:col-span-8 h-full flex flex-col">
            <PlayerTable />
        </div>

        {/* Chart Row: Full Width */}
        <div className="col-span-1 xl:col-span-12 h-full flex flex-col">
            <Suspense fallback={<ChartFallback />}>
                <ActivityChart />
            </Suspense>
        </div>

      </div>
    </div>
  );
};
