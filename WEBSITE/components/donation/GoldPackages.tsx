import React, { useState, useMemo } from 'react';
import { Coins, Zap, Calculator, ChevronRight, AlertCircle } from 'lucide-react';

interface GoldPackagesProps {
    activePkg: any;
    onSelectPackage: (pkg: any) => void;
}

export const GoldPackages: React.FC<GoldPackagesProps> = ({ activePkg, onSelectPackage }) => {
  // State for Custom Top Up
  const [customAmount, setCustomAmount] = useState<string>('');
  const [error, setError] = useState<string>('');

  const goldPackages = [
    // Tier 1: Micro (No Bonus)
    { amount: 100, price: "Rp 10.000", bonus: null, iconColor: "text-gray-400", bg: "bg-gray-50 dark:bg-ph-surface-input", border: "border-gray-200 dark:border-white/5" },
    { amount: 250, price: "Rp 25.000", bonus: null, iconColor: "text-gray-300", bg: "bg-gray-50 dark:bg-ph-surface-input", border: "border-gray-200 dark:border-white/5" },
    
    // Tier 2: Low (5% Bonus)
    { amount: 525, price: "Rp 50.000", bonus: "+5%", iconColor: "text-blue-300", bg: "bg-blue-50/50 dark:bg-blue-900/10", border: "border-blue-100 dark:border-blue-900/20" },
    { amount: 790, price: "Rp 75.000", bonus: "+5%", iconColor: "text-blue-400", bg: "bg-blue-50/50 dark:bg-blue-900/10", border: "border-blue-100 dark:border-blue-900/20" },
    
    // Tier 3: Medium (10% Bonus)
    { amount: 1100, price: "Rp 100.000", tag: "Popular", bonus: "+10%", iconColor: "text-amber-400", bg: "bg-amber-50/50 dark:bg-amber-900/10", border: "border-amber-200 dark:border-amber-900/30", shadow: "hover:shadow-amber-500/10" },
    { amount: 2200, price: "Rp 200.000", bonus: "+10%", iconColor: "text-amber-500", bg: "bg-amber-50/50 dark:bg-amber-900/10", border: "border-amber-200 dark:border-amber-900/30", shadow: "hover:shadow-amber-500/10" },
    
    // Tier 4: High (15% Bonus)
    { amount: 3450, price: "Rp 300.000", tag: "Best Value", bonus: "+15%", iconColor: "text-orange-500", bg: "bg-orange-50/50 dark:bg-orange-900/10", border: "border-orange-200 dark:border-orange-900/30", shadow: "hover:shadow-orange-500/10" },
    
    // Tier 5: Sultan (20% Bonus - Max)
    { amount: 6000, price: "Rp 500.000", tag: "Sultan", bonus: "+20%", iconColor: "text-yellow-300", bg: "bg-gradient-to-br from-gray-900 to-black dark:from-yellow-950/30 dark:to-black", border: "border-yellow-500/30", shadow: "hover:shadow-yellow-500/20", isSpecial: true },
  ];

  // --- CUSTOM TOP UP LOGIC ---
  const { calculatedGold, bonusPercent, isValid } = useMemo(() => {
      const amount = parseInt(customAmount.replace(/\./g, '')) || 0;
      
      if (amount === 0) return { calculatedGold: 0, bonusPercent: 0, isValid: false };

      // Base Rate: 100 IDR = 1 Gold
      const baseGold = Math.floor(amount / 100);
      
      // Dynamic Bonus Tier (Max 20%)
      let bonus = 0;
      if (amount >= 500000) bonus = 0.20;      // 20%
      else if (amount >= 300000) bonus = 0.15; // 15%
      else if (amount >= 100000) bonus = 0.10; // 10%
      else if (amount >= 50000) bonus = 0.05;  // 5%

      const totalGold = Math.floor(baseGold * (1 + bonus));
      
      // Validation (10k - 1jt)
      const valid = amount >= 10000 && amount <= 1000000;

      return { 
          calculatedGold: totalGold, 
          bonusPercent: Math.round(bonus * 100), 
          isValid: valid 
      };
  }, [customAmount]);

  const handleCustomSubmit = (e: React.FormEvent) => {
      e.preventDefault();
      const amount = parseInt(customAmount.replace(/\./g, ''));
      
      if (amount < 10000) {
          setError('Minimal top up Rp 10.000');
          return;
      }
      if (amount > 1000000) {
          setError('Maksimal top up Rp 1.000.000');
          return;
      }

      setError('');
      
      const pkg = {
          name: "Custom Gold Pack",
          amount: calculatedGold,
          price: `Rp ${amount.toLocaleString('id-ID')}`,
          bonus: bonusPercent > 0 ? `+${bonusPercent}%` : null,
          custom: true
      };
      
      onSelectPackage(pkg);
  };

  return (
      <section id="gold-section">
         <div className="flex items-center gap-2 mb-4 md:mb-6 px-1">
            <Coins className="text-yellow-500" size={24} />
            <div>
                <h3 className="text-base md:text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-wide leading-none">Top Up Gold Coin</h3>
                <p className="text-[10px] text-gray-500 font-bold uppercase tracking-wide mt-1">Pilih paket atau masukkan nominal sendiri</p>
            </div>
        </div>

        {/* Preset Packages Grid (8 Options) */}
        <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-3 md:gap-6 lg:gap-8 mb-8">
            {goldPackages.map((pkg, idx) => (
                <div 
                    key={idx} 
                    className={`group relative ${pkg.bg} border ${pkg.border} rounded-xl md:rounded-3xl p-3 md:p-8 hover:scale-[1.02] transition-all cursor-pointer flex flex-col items-center justify-between text-center overflow-hidden min-h-[160px] md:min-h-[220px] ${pkg.shadow || 'hover:shadow-xl hover:shadow-black/5 dark:hover:shadow-black/50'} ${activePkg?.amount === pkg.amount && !activePkg?.custom ? 'ring-2 ring-red-500 border-red-500 dark:border-red-500' : ''}`}
                    onClick={() => onSelectPackage(pkg)}
                >
                    {/* Tags & Badges */}
                    {pkg.tag && (
                        <div className={`absolute top-0 right-0 rounded-bl-lg md:rounded-bl-xl px-2 py-1 md:px-3 md:py-1.5 text-[7px] md:text-[10px] font-black uppercase tracking-wider text-white shadow-sm z-10 ${
                            pkg.tag === 'Sultan' ? 'bg-gradient-to-r from-yellow-600 to-yellow-500' : 
                            pkg.tag === 'Popular' ? 'bg-amber-500' : 
                            pkg.tag === 'Best Value' ? 'bg-orange-500' : 'bg-blue-500'
                        }`}>
                            {pkg.tag}
                        </div>
                    )}
                    
                    {/* Special Background Effect for Sultan */}
                    {pkg.isSpecial && (
                        <div className="absolute inset-0  opacity-20 pointer-events-none" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
                    )}
                    
                    {pkg.bonus && (
                        <div className={`absolute top-1.5 left-1.5 md:top-3 md:left-3 flex items-center gap-1 md:gap-1.5 rounded px-1.5 py-0.5 md:px-2 md:py-1.5 border z-10 ${pkg.isSpecial ? 'bg-yellow-500/20 border-yellow-500/30' : 'bg-green-500/10 border-green-500/20'}`}>
                            <Zap size={10} className={`md:w-3 md:h-3 ${pkg.isSpecial ? "text-yellow-400 fill-current" : "text-green-600 dark:text-green-400 fill-current"}`} />
                            <span className={`text-[8px] md:text-[10px] font-black ${pkg.isSpecial ? "text-yellow-400" : "text-green-600 dark:text-green-400"}`}>{pkg.bonus}</span>
                        </div>
                    )}

                    <div className="mb-2 mt-4 md:mb-4 md:mt-8 transform group-hover:scale-110 transition-transform duration-300 relative z-10">
                        <Coins size={36} className={`w-8 h-8 md:w-16 md:h-16 ${pkg.iconColor}`} />
                    </div>
                    
                    <div className="mb-3 md:mb-6 w-full relative z-10 flex-1 flex items-center justify-center">
                        <h4 className={`text-base md:text-3xl font-black italic leading-none ${pkg.isSpecial ? 'text-white' : 'text-gray-900 dark:text-white'}`}>
                            {pkg.amount.toLocaleString('en-US')} <span className="text-[9px] md:text-sm not-italic opacity-50 font-sans font-bold tracking-normal">GC</span>
                        </h4>
                    </div>

                    <button className={`w-full mt-auto font-bold py-2 md:py-3.5 rounded-lg md:rounded-xl text-[9px] md:text-sm uppercase tracking-wider transition-colors shadow-sm relative z-10 border ${
                        activePkg?.amount === pkg.amount && !activePkg?.custom
                        ? 'bg-red-600 text-white border-red-500'
                        : pkg.isSpecial 
                        ? 'bg-yellow-500 text-black border-yellow-400 hover:bg-yellow-400' 
                        : 'bg-white dark:bg-black/20 border-gray-200 dark:border-white/10 hover:bg-gray-900 hover:text-white dark:hover:bg-white dark:hover:text-black'
                    }`}>
                        {activePkg?.amount === pkg.amount && !activePkg?.custom ? 'Terpilih' : pkg.price}
                    </button>
                </div>
            ))}
        </div>

        {/* CUSTOM TOP UP CALCULATOR */}
        <div className="bg-gray-50 dark:bg-ph-surface-input border border-gray-200 dark:border-white/5 rounded-2xl md:rounded-3xl p-5 md:p-8 relative overflow-hidden">
            <div className="absolute top-0 right-0 p-3 opacity-5">
                <Calculator size={100} />
            </div>
            
            <div className="flex items-center gap-2 mb-4 relative z-10">
                <div className="p-1.5 bg-gray-200 dark:bg-white/10 rounded-md">
                    <Calculator size={16} className="text-gray-600 dark:text-gray-300" />
                </div>
                <h4 className="font-black text-gray-900 dark:text-white uppercase italic text-sm">Custom Top Up</h4>
            </div>

            <form onSubmit={handleCustomSubmit} className="flex flex-col lg:flex-row gap-3 md:gap-6 items-start lg:items-end relative z-10">
                <div className="w-full lg:flex-1">
                    <label className="block text-[10px] md:text-sm font-bold text-gray-500 uppercase mb-1.5 md:mb-2">Masukkan Nominal (Rp)</label>
                    <div className="relative">
                        <span className="absolute left-3 md:left-4 top-1/2 -translate-y-1/2 text-gray-500 font-bold text-[11px] md:text-base">Rp</span>
                        <input 
                            type="number" 
                            min="10000"
                            max="1000000"
                            placeholder="10.000 - 1.000.000"
                            className="w-full pl-8 md:pl-11 pr-3 md:pr-4 py-2.5 md:py-4 rounded-xl md:rounded-2xl bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 focus:border-red-500 outline-none text-xs md:text-lg font-bold text-gray-900 dark:text-white"
                            value={customAmount}
                            onChange={(e) => {
                                setCustomAmount(e.target.value);
                                setError('');
                            }}
                        />
                    </div>
                    {error && <p className="text-[9px] md:text-[10px] text-red-500 font-bold mt-1.5 flex items-center gap-1"><AlertCircle size={10}/> {error}</p>}
                </div>

                <div className="w-full lg:w-auto flex items-center justify-center pt-1 md:pt-0">
                    <div className="bg-gray-200 dark:bg-white/5 h-px w-full md:w-px md:h-10"></div>
                </div>

                <div className="w-full lg:flex-1 bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl md:rounded-2xl p-3 md:p-5 flex justify-between items-center">
                    <div>
                        <p className="text-[9px] md:text-xs font-bold text-gray-500 uppercase">Estimasi Gold</p>
                        <div className="flex items-baseline gap-1.5 md:gap-2 mt-0.5 md:mt-1">
                             <span className="text-xl md:text-3xl font-black text-amber-500 leading-none">{calculatedGold.toLocaleString('en-US')} GC</span>
                             {bonusPercent > 0 && (
                                 <span className="text-[8px] md:text-[10px] font-bold text-green-500 bg-green-500/10 px-1.5 md:px-2 py-0.5 md:py-1 rounded border border-green-500/20">+{bonusPercent}% Bonus</span>
                             )}
                        </div>
                    </div>
                </div>

                <button 
                    type="submit"
                    disabled={!isValid}
                    className={`w-full lg:w-auto font-black py-2.5 md:py-4 px-4 md:px-8 rounded-xl md:rounded-2xl uppercase text-[10px] md:text-sm tracking-widest transition-all shadow-lg disabled:opacity-50 disabled:cursor-not-allowed flex items-center justify-center gap-1.5 md:gap-2 h-10 md:h-[60px] ${
                        activePkg?.custom && activePkg?.amount === calculatedGold
                        ? 'bg-red-600 text-white'
                        : 'bg-gray-900 dark:bg-white hover:bg-red-600 dark:hover:bg-red-500 text-white dark:text-black hover:text-white dark:hover:text-white'
                    }`}
                >
                    {activePkg?.custom && activePkg?.amount === calculatedGold ? 'Terpilih' : 'Pilih Custom'} <ChevronRight size={12} className="md:w-3.5 md:h-3.5" />
                </button>
            </form>
            <p className="text-[8px] md:text-[9px] text-gray-400 mt-3 md:mt-2 relative z-10 italic">*Bonus Gold dihitung otomatis berdasarkan nominal top up.</p>
        </div>
      </section>
  );
};