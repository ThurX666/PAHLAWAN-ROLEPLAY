
import React, { useState } from 'react';
import { Sparkles, Store, X, CreditCard, Coins, User, Info, Crown, UserCircle } from 'lucide-react';
import { PageHeader } from '../ui/PageHeader';
import { getVipStyle } from '../../utils/vip';

interface DonationHeaderProps {
  promoConfig?: {
    isActive: boolean;
    title: string;
    message: string;
  };
  userGold?: number;
  userName?: string;
  accountId?: string | number;
  vipStatus?: {
    tier: string;
    expiredAt: string;
  } | null;
  onTopUpClick?: () => void;
  onExtendVipClick?: (tier: string) => void;
}

export const DonationHeader: React.FC<DonationHeaderProps> = ({ 
    promoConfig, 
    userGold = 0, 
    userName = "Player",
    accountId = 8492,
    vipStatus,
    onTopUpClick,
    onExtendVipClick
}) => {
  const [isBannerVisible, setIsBannerVisible] = useState(true);
  const vipStyle = getVipStyle(vipStatus?.tier);

  const scrollToGold = () => {
      if (onTopUpClick) {
          onTopUpClick();
      }
      setTimeout(() => {
          const goldSection = document.getElementById('gold-section');
          if(goldSection) {
              goldSection.scrollIntoView({ behavior: 'smooth', block: 'start' });
          }
      }, 100);
  };

  return (
      <>
        <PageHeader 
            title="DONATION STORE" 
            icon={Store}
        />

        {/* Subtle Description */}
        <p className="text-xs md:text-sm text-gray-500 dark:text-gray-400 mb-6 leading-relaxed px-1">
            Dukungan Anda adalah pilar keberlangsungan server. Kontribusi ini dialokasikan sepenuhnya untuk pemeliharaan infrastruktur dan pengembangan fitur.
        </p>

        {/* Account Info - Sleek Game Topup Style */}
        <div>
            <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-2xl p-4 flex flex-col gap-4 shadow-sm">
                
                {/* Top Row */}
                <div className="flex flex-col md:flex-row items-stretch justify-between gap-4 w-full">
                    {/* User Info & Title Combined */}
                    <div className="flex items-center justify-start w-full md:flex-1 gap-4 p-2">
                        <div className="flex items-center gap-3">
                            <UserCircle className="text-red-600 shrink-0" size={24} />
                            <div className="flex flex-col justify-center">
                                <h3 className="text-sm md:text-base font-black italic text-gray-900 dark:text-white uppercase tracking-widest mb-0.5">Informasi Akun</h3>
                                <div className="flex items-center gap-1.5">
                                    <p className="text-xs md:text-sm font-bold text-gray-700 dark:text-gray-300 truncate max-w-[120px] leading-tight">{userName}</p>
                                    <span className="text-gray-300 dark:text-gray-600 text-[10px]">•</span>
                                    <p className="text-[10px] md:text-xs font-bold text-gray-500 uppercase tracking-widest">ID: {accountId}</p>
                                </div>
                            </div>
                        </div>
                    </div>

                    <div className="w-full md:w-px h-px md:h-auto md:min-h-[80px] bg-gray-200 dark:bg-white/10 hidden md:block self-stretch"></div>

                    {/* VIP Status Wrapper */}
                    <div className="w-full md:flex-1 flex flex-col bg-gray-50 dark:bg-ph-surface-panel rounded-xl border border-gray-200 dark:border-white/5 overflow-hidden">
                        
                        {/* VIP Status */}
                        <div className="flex items-center justify-between w-full gap-4 p-3 md:p-4">
                            <div>
                                <p className="text-[9px] md:text-[10px] font-bold text-gray-500 uppercase tracking-widest mb-0.5">Status VIP</p>
                                {vipStatus ? (
                                    <div className="flex items-center gap-1.5">
                                        <vipStyle.icon className={vipStyle.colorClass} size={16} />
                                        <span className={`text-base md:text-lg font-black font-mono leading-none ${vipStyle.colorClass}`}>{vipStatus.tier}</span>
                                    </div>
                                ) : (
                                    <div className="flex items-center gap-1.5">
                                        <Crown className="text-gray-400" size={16} />
                                        <span className="text-base md:text-lg font-black text-gray-400 font-mono leading-none">Non-VIP</span>
                                    </div>
                                )}
                            </div>
                            {vipStatus && (
                                <button 
                                    onClick={() => {
                                        if (onExtendVipClick) {
                                            onExtendVipClick(vipStatus.tier);
                                        }
                                    }}
                                    className={`${vipStyle.buttonClass} text-[9px] font-bold uppercase tracking-widest px-3 py-2 rounded-lg transition-colors border`}
                                >
                                    Perpanjang
                                </button>
                            )}
                        </div>

                        {/* Expired VIP Banner - Attached */}
                        {vipStatus && (
                            <div className={`flex-1 w-full ${vipStyle.bgClass} border-t ${vipStyle.borderClass} p-3 flex items-start gap-3 relative group`}>
                                {/* Decorative background element */}
                                <div className={`absolute right-0 top-0 bottom-0 w-32 bg-gradient-to-l ${vipStyle.colorClass.replace('text-', 'from-').replace('-400', '-500/5').replace('-500', '-500/5')} to-transparent pointer-events-none`}></div>
                                
                                <div className={`p-2 ${vipStyle.bgClass} rounded-lg ${vipStyle.colorClass} shrink-0 shadow-inner mt-0.5`}>
                                    <Info size={16} />
                                </div>
                                <div className="relative z-10">
                                    <div className="flex items-center gap-2 mb-1">
                                        <span className={`text-[8px] font-black ${vipStyle.colorClass} uppercase tracking-widest ${vipStyle.bgClass} px-1.5 py-0.5 rounded border ${vipStyle.borderClass}`}>Masa Aktif</span>
                                    </div>
                                    <h4 className="text-xs md:text-sm font-black text-gray-900 dark:text-white italic tracking-wide mb-0.5">Berakhir Pada</h4>
                                    <p className="text-[10px] text-gray-600 dark:text-gray-300 leading-relaxed font-medium">
                                        <strong className={vipStyle.colorClass}>{vipStatus.expiredAt}</strong>
                                    </p>
                                </div>
                            </div>
                        )}
                    </div>

                    <div className="w-full md:w-px h-px md:h-auto md:min-h-[80px] bg-gray-200 dark:bg-white/10 hidden md:block self-stretch"></div>

                    {/* Gold Balance & Promo Wrapper */}
                    <div className="w-full md:flex-1 flex flex-col bg-gray-50 dark:bg-ph-surface-panel rounded-xl overflow-hidden">
                        
                        {/* Gold Balance & CTA */}
                        <div className="flex items-center justify-between w-full gap-4 p-3 md:p-4">
                            <div>
                                <p className="text-[9px] md:text-[10px] font-bold text-gray-500 uppercase tracking-widest mb-0.5">Saldo Gold Coin</p>
                                <div className="flex items-center gap-1.5">
                                    <Coins className="text-yellow-500" size={16} />
                                    <span className="text-base md:text-lg font-black text-yellow-500 font-mono leading-none">{userGold.toLocaleString('en-US')}</span>
                                </div>
                            </div>
                            <button 
                                onClick={scrollToGold}
                                className="bg-yellow-50 dark:bg-yellow-500/10 text-yellow-600 dark:text-yellow-400 hover:bg-yellow-100 dark:hover:bg-yellow-500/20 text-[9px] font-bold uppercase tracking-widest px-3 py-2 rounded-lg transition-colors border border-yellow-200 dark:border-yellow-500/20"
                            >
                                Top Up
                            </button>
                        </div>

                        {/* Promo Banner - Attached */}
                        {promoConfig?.isActive && (
                            <div className="w-full bg-gradient-to-br from-yellow-50 to-amber-50 dark:from-yellow-900/20 dark:to-amber-900/20 border-t border-yellow-200 dark:border-yellow-500/30 p-3 flex items-start gap-3 relative group">
                                {/* Decorative background element */}
                                <div className="absolute right-0 top-0 bottom-0 w-32 bg-gradient-to-l from-yellow-500/5 to-transparent pointer-events-none"></div>
                                
                                <div className="p-2 bg-yellow-100 dark:bg-yellow-500/20 rounded-lg text-yellow-600 dark:text-yellow-400 shrink-0 shadow-inner mt-0.5">
                                    <Sparkles size={16} className="animate-pulse" />
                                </div>
                                <div className="relative z-10">
                                    <div className="flex items-center gap-2 mb-1">
                                        <span className="text-[8px] font-black text-yellow-600 dark:text-yellow-400 uppercase tracking-widest bg-yellow-100 dark:bg-yellow-500/20 px-1.5 py-0.5 rounded border border-yellow-200 dark:border-yellow-500/30">Penawaran Terbatas</span>
                                    </div>
                                    <h4 className="text-xs md:text-sm font-black text-gray-900 dark:text-white italic tracking-wide mb-0.5">Promo Spesial!</h4>
                                    <p className="text-[10px] text-gray-600 dark:text-gray-300 leading-relaxed font-medium">
                                        Dapatkan Bonus Gold <strong className="text-yellow-600 dark:text-yellow-400">+20%</strong> untuk setiap donasi di atas Rp 100.000. <span className="underline decoration-yellow-500/50 underline-offset-2">Hanya hari ini!</span>
                                    </p>
                                </div>
                            </div>
                        )}
                    </div>
                </div>
            </div>
        </div>

        {/* Promo Banner (Top) */}
        {promoConfig && promoConfig.isActive && isBannerVisible && (
            <div className="
                fixed inset-0 z-[100] flex items-center justify-center bg-black/90 backdrop-blur-md
                md:relative md:z-10 md:block md:bg-transparent md:backdrop-blur-none
                mb-0 md:mt-6 md:mb-8 animate-in zoom-in-95 md:slide-in-from-top-4 duration-500 fade-in-0
            ">
                <div className="
                    relative w-full h-full md:h-auto flex flex-col justify-center
                    md:rounded-2xl overflow-hidden shadow-2xl border-0 md:border border-red-500/30 
                    bg-gradient-to-br from-[#1a1a1a] to-[#0a0a0a]
                ">
                    
                    {/* Abstract Background Elements */}
                    <div className="absolute top-0 right-0 w-full h-full  opacity-10 mix-blend-overlay" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
                    <div className="absolute -top-24 -right-24 w-96 h-96 bg-red-600/20 rounded-full blur-[80px] pointer-events-none"></div>
                    <div className="absolute -bottom-24 -left-24 w-96 h-96 bg-yellow-500/10 rounded-full blur-[80px] pointer-events-none"></div>

                    <div className="p-8 md:p-8 relative z-10 flex flex-col md:flex-row items-center md:items-center justify-between gap-8 md:gap-6 text-center md:text-left h-full md:h-auto">
                        
                        <button 
                            onClick={() => setIsBannerVisible(false)}
                            className="absolute top-6 right-6 md:top-4 md:right-4 text-gray-400 hover:text-white transition-colors p-3 md:p-2 bg-white/5 md:bg-transparent hover:bg-white/10 rounded-full z-20"
                            aria-label="Close banner"
                        >
                            <X size={24} className="md:w-5 md:h-5" />
                        </button>

                        <div className="flex-1 flex flex-col items-center md:items-start justify-center max-w-lg md:max-w-none mx-auto md:mx-0 md:pr-12 mt-12 md:mt-0">
                            <div className="inline-flex items-center gap-2 px-4 py-1.5 md:px-3 md:py-1 rounded-full bg-red-500/10 border border-red-500/20 text-red-500 text-xs md:text-[10px] font-bold uppercase tracking-widest mb-6 md:mb-3">
                                <Sparkles size={14} className="animate-pulse md:w-3 md:h-3" />
                                Penawaran Terbatas
                            </div>
                            
                            <h3 className="text-4xl md:text-3xl lg:text-4xl font-black text-white italic uppercase tracking-tight mb-4 md:mb-2">
                                {promoConfig.title}
                            </h3>
                            
                            <p className="text-base md:text-sm lg:text-base text-gray-400 font-medium leading-relaxed max-w-3xl">
                                {promoConfig.message}
                            </p>
                        </div>

                        <div className="shrink-0 w-full md:w-auto mt-auto md:mt-0 mb-8 md:mb-0 md:pr-8">
                            <button 
                                onClick={() => {
                                    if (window.innerWidth < 768) {
                                        setIsBannerVisible(false);
                                        setTimeout(scrollToGold, 300);
                                    } else {
                                        scrollToGold();
                                    }
                                }} 
                                className="w-full md:w-auto relative overflow-hidden bg-yellow-500 hover:bg-yellow-400 text-black font-black uppercase text-base md:text-sm px-8 py-5 md:py-4 rounded-2xl md:rounded-xl shadow-[0_0_30px_rgba(234,179,8,0.3)] md:shadow-[0_0_20px_rgba(234,179,8,0.2)] transform transition-all hover:scale-105 active:scale-95 flex items-center justify-center gap-2 group"
                            >
                                <span className="relative z-10">Top Up Sekarang</span>
                                <div className="absolute inset-0 bg-white/20 translate-y-full group-hover:translate-y-0 transition-transform duration-300 ease-out"></div>
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        )}
      </>
  );
};
