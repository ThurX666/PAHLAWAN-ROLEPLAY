
import React, { useState } from 'react';
import { Crown, Star, Zap, Check, Gem, Sparkles, AlertTriangle } from 'lucide-react';

export const VIP_PACKAGES = [
    { 
        id: 'bronze',
        name: "VIP Bronze", 
        duration: "Aktif 15 Hari", 
        price: "Rp 40.000",
        label: "Trial",
        icon: Star, 
        description: "Awal perjalanan roleplay.", 
        color: "from-orange-700 to-orange-900", 
        iconBg: "bg-orange-100 dark:bg-orange-900/20 text-orange-600 dark:text-orange-500",
        features: [
            "Priority Queue Login", 
            "Bonus Uang $10.000", 
            "+1 Slot Kendaraan", 
            "Bronze Chat Tag"
        ] 
    },
    { 
        id: 'silver',
        name: "VIP Silver", 
        duration: "Aktif 30 Hari", 
        price: "Rp 80.000", 
        label: "Monthly",
        icon: Crown, 
        description: "Fitur standar bulanan.", 
        color: "from-gray-300 via-gray-400 to-gray-500", 
        iconBg: "bg-gray-100 dark:bg-gray-800 text-gray-600 dark:text-gray-400",
        features: [
            "Priority Queue Login", 
            "Bonus Uang $25.000", 
            "+2 Slot Kendaraan", 
            "Silver Chat Tag", 
            "Custom Phone Number (4 Digit)"
        ] 
    },
    { 
        id: 'gold',
        name: "VIP Gold", 
        duration: "Aktif 45 Hari", 
        price: "Rp 150.000", 
        label: "Popular",
        icon: Zap, 
        description: "Favorit (1.5 Bulan).", 
        color: "from-yellow-400 via-amber-500 to-amber-600", 
        iconBg: "bg-amber-100 dark:bg-amber-900/20 text-amber-600 dark:text-amber-500",
        popular: true, 
        features: [
            "High Priority Queue Login", 
            "Bonus Uang $60.000", 
            "+3 Slot Kendaraan", 
            "Gold Chat Tag", 
            "Custom Phone Number",
            "Custom Vehicle Plate", 
            "Akses Modifikasi Neon"
        ] 
    },
    { 
        id: 'diamond',
        name: "VIP Diamond", 
        duration: "Aktif 60 Hari", 
        price: "Rp 250.000", 
        label: "Sultan",
        icon: Gem, 
        description: "Status tertinggi (2 Bulan).", 
        color: "from-cyan-500 to-blue-600",
        iconBg: "bg-cyan-100 dark:bg-cyan-900/20 text-cyan-600 dark:text-cyan-400", 
        isLegendary: true,
        features: [
            "Max Priority Queue Login", 
            "Bonus Uang $150.000", 
            "+5 Slot Kendaraan", 
            "Diamond Chat Tag (Animasi)", 
            "Custom Phone, Plate & Neon",
            "1x Free Change Name (CN)", 
            "Akses Interior Rumah Mewah", 
            "Custom Toy / Accessories"
        ] 
    }
];

interface VipPackagesProps {
    activePkg: any;
    onSelectPackage: (pkg: any) => void;
    currentVipTier?: string | null;
}

export const VipPackages: React.FC<VipPackagesProps> = ({ activePkg, onSelectPackage, currentVipTier }) => {
  const [showWarning, setShowWarning] = useState<string | null>(null);

  const handleSelect = (pkg: any) => {
      if (currentVipTier && currentVipTier.toLowerCase() !== pkg.id) {
          setShowWarning(pkg.id);
      } else {
          setShowWarning(null);
          onSelectPackage(pkg);
      }
  };

  const confirmSelection = (pkg: any) => {
      setShowWarning(null);
      onSelectPackage(pkg);
  };

  return (
      <section className="py-4">
        <div className="flex items-center gap-2 mb-6 px-1">
            <Crown className="text-amber-500" size={24} />
            <div>
                <h3 className="text-base md:text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-wide leading-none">Pilih Membership VIP</h3>
                <p className="text-[10px] text-gray-500 font-bold uppercase tracking-wide mt-1">Pilihan paket dengan durasi fleksibel</p>
            </div>
        </div>

        {/* Grid Layout */}
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-8 items-stretch mb-8">
            {VIP_PACKAGES.map((pkg, idx) => {
            const Icon = pkg.icon;
            const isPopular = pkg.popular;
            const isLegendary = pkg.isLegendary;
            const isWarning = showWarning === pkg.id;

            return (
                <div 
                    key={idx} 
                    onClick={() => !isWarning && handleSelect(pkg)}
                    className={`
                        relative group rounded-2xl md:rounded-3xl flex flex-col h-full overflow-hidden transition-all duration-300 ${!isWarning ? 'cursor-pointer' : ''}
                        ${isLegendary 
                            ? 'bg-gradient-to-b from-white to-blue-50 dark:from-[#1a1a1a] dark:to-[#0f172a] border shadow-2xl shadow-blue-900/10 dark:shadow-black/60' 
                            : 'bg-white dark:bg-[#121212] border shadow-lg hover:border-gray-300 dark:hover:border-white/10'
                        }
                        ${activePkg?.name === pkg.name 
                            ? 'ring-2 ring-red-500 border-red-500 dark:border-red-500 shadow-2xl shadow-red-500/20' 
                            : 'border-gray-200 dark:border-white/10 hover:-translate-y-1 hover:shadow-2xl dark:hover:shadow-black/50'
                        }
                        min-h-[380px] md:min-h-[480px]
                    `}
                >
                    {/* Badge Tags */}
                    {isPopular && (
                        <div className="absolute top-0 right-0 bg-amber-500 text-white text-[9px] md:text-[11px] font-black px-3 py-1 md:px-4 md:py-1.5 rounded-bl-xl md:rounded-bl-2xl uppercase tracking-widest shadow-sm z-20">
                            Paling Laris
                        </div>
                    )}
                    {isLegendary && (
                        <div className="absolute top-0 inset-x-0 h-1 md:h-1.5 bg-gradient-to-r from-cyan-400 to-blue-600"></div>
                    )}
                    {isLegendary && (
                        <div className="absolute top-0 right-0 flex items-center gap-1 md:gap-1.5 bg-blue-100 dark:bg-blue-900/40 text-blue-700 dark:text-blue-300 border-b border-l border-blue-200 dark:border-blue-500/30 px-3 py-1 md:px-4 md:py-1.5 rounded-bl-xl md:rounded-bl-2xl text-[8px] md:text-[11px] font-black uppercase tracking-widest z-20 backdrop-blur-md shadow-sm">
                            <Sparkles size={10} className="w-3 h-3 md:w-4 md:h-4" /> Ultimate
                        </div>
                    )}

                    <div className="p-5 md:p-8 flex flex-col h-full relative z-10 w-full">
                        
                        {/* Header Icon & Name */}
                        <div className="flex justify-between items-start mb-4 md:mb-6 w-full">
                            <div>
                                <h4 className={`text-xl md:text-3xl font-black uppercase italic leading-none tracking-tight ${isLegendary ? 'text-gray-900 dark:text-white' : 'text-gray-900 dark:text-white'}`}>
                                    {pkg.name}
                                </h4>
                                <span className="text-[10px] md:text-sm font-bold text-gray-400 uppercase tracking-widest mt-1 md:mt-1.5 block">{pkg.duration}</span>
                            </div>
                            <div className={`p-3 w-10 h-10 md:p-4 md:w-16 md:h-16 flex items-center justify-center rounded-xl md:rounded-2xl ${pkg.iconBg} shadow-sm group-hover:scale-110 transition-transform duration-300 shrink-0`}>
                                <Icon size={20} className="md:w-8 md:h-8" />
                            </div>
                        </div>

                        {/* Price Section */}
                        <div className="mb-4 pb-4 md:mb-6 md:pb-6 border-b border-dashed border-gray-200 dark:border-white/10 w-full">
                            <div className="flex items-baseline gap-1">
                                <div className={`text-2xl md:text-4xl font-black tracking-tighter ${isLegendary ? 'text-blue-600 dark:text-blue-400' : 'text-gray-900 dark:text-white'}`}>
                                    {pkg.price}
                                </div>
                            </div>
                            
                            <div className="flex items-center justify-between mt-1 md:mt-2">
                                <span className="text-[10px] md:text-sm font-bold text-gray-400 uppercase tracking-widest">
                                    Total Harga
                                </span>
                                {pkg.label && (
                                    <span className={`text-[9px] md:text-[11px] font-bold px-1.5 py-0.5 md:px-2 md:py-1 rounded border uppercase tracking-wider ${isLegendary ? 'bg-blue-50 text-blue-600 border-blue-200 dark:bg-blue-900/30 dark:text-blue-400 dark:border-blue-900/40' : 'bg-gray-100 text-gray-500 border-gray-200 dark:bg-white/5 dark:text-gray-400 dark:border-white/10'}`}>
                                        {pkg.label}
                                    </span>
                                )}
                            </div>
                        </div>
                        
                        {/* Features List */}
                        <ul className="space-y-2 md:space-y-3 mb-6 md:mb-8 flex-1 w-full">
                            {pkg.features.map((feat, i) => (
                                <li key={i} className="flex items-start gap-2 md:gap-3 text-xs md:text-base text-gray-600 dark:text-gray-300">
                                    <div className={`mt-0.5 p-1 md:p-1.5 rounded-full ${isLegendary ? 'bg-blue-100 dark:bg-blue-900/30 text-blue-600 dark:text-blue-400' : 'bg-gray-100 dark:bg-white/10 text-gray-500'}`}>
                                        <Check size={10} strokeWidth={4} className="w-2.5 h-2.5 md:w-3.5 md:h-3.5" />
                                    </div>
                                    <span className={`leading-relaxed ${i === 0 && pkg.id !== 'bronze' ? 'font-bold text-gray-900 dark:text-white' : ''}`}>{feat}</span>
                                </li>
                            ))}
                        </ul>
                        
                        {/* Warning Overlay */}
                        {isWarning && (
                            <div className="absolute inset-0 z-30 bg-white/95 dark:bg-[#121212]/95 backdrop-blur-md flex flex-col items-center justify-center p-5 md:p-8 text-center animate-in fade-in zoom-in-95 duration-200">
                                <div className="w-12 h-12 md:w-20 md:h-20 bg-red-100 dark:bg-red-500/20 text-red-600 dark:text-red-500 rounded-full flex items-center justify-center mb-4 md:mb-6 shadow-inner">
                                    <AlertTriangle size={24} className="md:w-10 md:h-10 w-6 h-6" />
                                </div>
                                <h4 className="text-lg md:text-2xl font-black text-gray-900 dark:text-white uppercase tracking-tight mb-2 md:mb-3">Perhatian!</h4>
                                <p className="text-xs md:text-base text-gray-600 dark:text-gray-400 mb-6 md:mb-8 leading-relaxed max-w-xs">
                                    Anda masih memiliki paket VIP aktif. Jika Anda membeli paket ini, sisa waktu VIP Anda sebelumnya akan <strong className="text-red-500">hangus</strong>.
                                </p>
                                <div className="flex gap-2 md:gap-3 w-full">
                                    <button 
                                        onClick={(e) => { e.stopPropagation(); setShowWarning(null); }}
                                        className="flex-1 py-3 md:py-4 rounded-lg md:rounded-xl font-bold text-[10px] md:text-sm uppercase tracking-widest bg-gray-100 dark:bg-white/5 hover:bg-gray-200 dark:hover:bg-white/10 text-gray-600 dark:text-gray-300 transition-all active:scale-95"
                                    >
                                        Batal
                                    </button>
                                    <button 
                                        onClick={(e) => { e.stopPropagation(); confirmSelection(pkg); }}
                                        className="flex-1 py-3 md:py-4 rounded-lg md:rounded-xl font-bold text-[10px] md:text-sm uppercase tracking-widest bg-red-600 hover:bg-red-500 text-white shadow-lg shadow-red-600/30 transition-all active:scale-95"
                                    >
                                        Lanjut
                                    </button>
                                </div>
                            </div>
                        )}

                        {/* Action Button */}
                        <button 
                            className={`
                                w-full mt-auto py-2.5 md:py-4 rounded-lg md:rounded-xl font-bold uppercase text-[10px] md:text-sm tracking-widest transition-all
                                ${activePkg?.name === pkg.name
                                    ? 'bg-red-600 text-white shadow-xl shadow-red-600/30 ring-2 ring-red-500 ring-offset-2 dark:ring-offset-[#121212]'
                                    : pkg.id === 'diamond' 
                                        ? 'bg-blue-600 hover:bg-blue-500 text-white shadow-lg shadow-blue-600/30'
                                        : pkg.id === 'gold'
                                            ? 'bg-amber-500 hover:bg-amber-600 text-white shadow-lg shadow-amber-500/20'
                                            : pkg.id === 'silver'
                                                ? 'bg-gray-500 hover:bg-gray-600 text-white shadow-lg shadow-gray-500/20'
                                                : pkg.id === 'bronze'
                                                    ? 'bg-orange-600 hover:bg-orange-700 text-white shadow-lg shadow-orange-600/20'
                                                    : 'bg-gray-100 dark:bg-[#1A1A1A] hover:bg-gray-200 dark:hover:bg-[#222222] text-gray-900 dark:text-white border border-gray-200 dark:border-white/5'
                                }
                            `}
                        >
                            {activePkg?.name === pkg.name ? 'Terpilih' : currentVipTier?.toLowerCase() === pkg.id ? 'Perpanjang' : 'Pilih Paket'}
                        </button>
                    </div>
                </div>
            )})}
        </div>
      </section>
  );
};
