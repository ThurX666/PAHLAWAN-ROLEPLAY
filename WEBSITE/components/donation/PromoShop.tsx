
import React from 'react';
import { Gem, ArrowRight, Sparkles, Clock } from 'lucide-react';
import { PromoItem } from '../../types';

interface PromoShopProps {
    promoItems: PromoItem[];
    onSelectItem: (item: PromoItem) => void;
}

export const PromoShop: React.FC<PromoShopProps> = ({ promoItems, onSelectItem }) => {
  const activePromoItems = promoItems.filter(item => item.isActive);

  if (activePromoItems.length === 0) return null;

  return (
      <section className="relative overflow-hidden rounded-2xl border border-purple-100 dark:border-purple-500/20 bg-white dark:bg-[#121212] p-4 md:p-5 shadow-xl dark:shadow-purple-900/5 group/section">
        
        {/* Ambient Background Effects */}
        <div className="absolute -top-24 -right-24 w-64 h-64 bg-purple-500/10 dark:bg-purple-600/10 rounded-full blur-[80px] pointer-events-none group-hover/section:bg-purple-500/20 transition-colors duration-700"></div>
        <div className="absolute top-0 left-0 w-full h-1 bg-gradient-to-r from-purple-500 via-indigo-500 to-purple-500 opacity-50"></div>

        {/* Header */}
        <div className="relative z-10 flex items-center justify-between mb-4 md:mb-5">
            <div className="flex items-center gap-2.5">
                <div className="flex h-8 w-8 items-center justify-center rounded-lg bg-purple-50 dark:bg-purple-900/20 text-purple-600 dark:text-purple-400 shadow-sm ring-1 ring-purple-100 dark:ring-purple-500/20">
                    <Gem size={18} className="animate-[pulse_3s_ease-in-out_infinite]" />
                </div>
                <div>
                    <h3 className="text-base md:text-lg font-black italic uppercase leading-none tracking-tighter text-gray-900 dark:text-white">
                        Exclusive Shop
                    </h3>
                    <p className="mt-0.5 text-[9px] md:text-[10px] font-bold uppercase tracking-widest text-gray-500 dark:text-gray-400 flex items-center gap-1">
                        <Sparkles size={10} className="text-purple-500" /> Limited Time Offers
                    </p>
                </div>
            </div>
        </div>
        
        {/* Grid Layout */}
        <div className="relative z-10 grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-6">
            {activePromoItems.map(item => (
                <div 
                    key={item.id} 
                    onClick={() => onSelectItem(item)}
                    className="group relative cursor-pointer overflow-hidden rounded-2xl md:rounded-3xl border border-gray-100 dark:border-white/5 bg-gray-50 dark:bg-[#181818] shadow-sm transition-all duration-300 hover:-translate-y-1 hover:shadow-2xl hover:shadow-purple-500/10 hover:border-purple-500/30 dark:hover:border-purple-500/30 flex flex-col h-full min-h-[280px] md:min-h-[340px]"
                >
                    {/* Badge: Limited */}
                    {item.isLimited && (
                        <div className="absolute left-3 top-3 z-30 flex items-center gap-1 rounded-full bg-gradient-to-r from-red-600 to-pink-600 px-3 py-1.5 text-[9px] md:text-[10px] font-black uppercase tracking-widest text-white shadow-lg shadow-red-500/20">
                            <Clock size={12} className="animate-pulse" /> Limited
                        </div>
                    )}

                    {/* Image Area */}
                    <div className="relative h-36 md:h-48 w-full overflow-hidden">
                        <div className="absolute inset-0 z-10 bg-gradient-to-t from-gray-900 via-gray-900/40 to-transparent opacity-80 transition-opacity duration-300 group-hover:opacity-60"></div>
                        <img 
                            src={item.image} 
                            alt={item.name} 
                            className="h-full w-full object-cover transition-transform duration-700 group-hover:scale-110" 
                        />
                        
                        {/* Price Tag Overlay */}
                        <div className="absolute bottom-3 left-3 md:bottom-4 md:left-4 z-20">
                            <span className="mb-1 block text-[10px] md:text-xs font-bold uppercase tracking-widest text-purple-200 opacity-90">{item.type}</span>
                            <div className="flex items-end gap-2 text-shadow-md">
                                <span className="text-2xl md:text-3xl font-black italic tracking-tighter text-white drop-shadow-lg leading-none">
                                    {item.priceGold} <span className="text-[12px] md:text-[14px] text-yellow-400 not-italic">GC</span>
                                </span>
                                {item.originalPriceGold && (
                                    <span className="mb-1 text-xs md:text-sm font-bold text-gray-300 line-through decoration-red-500 decoration-2 drop-shadow-md">
                                        {item.originalPriceGold}
                                    </span>
                                )}
                            </div>
                        </div>
                    </div>

                    {/* Content Area */}
                    <div className="flex flex-col gap-3 p-4 md:p-6 flex-1 justify-between">
                        <div className="space-y-2">
                            <h4 className="line-clamp-2 text-base md:text-lg font-black italic uppercase leading-tight text-gray-900 dark:text-white group-hover:text-purple-600 dark:group-hover:text-purple-400 transition-colors">
                                {item.name}
                            </h4>
                            <p className="line-clamp-3 text-xs md:text-sm font-medium leading-relaxed text-gray-500 dark:text-gray-400">
                                {item.description}
                            </p>
                        </div>

                        {/* Action Button */}
                        <button className="flex w-full items-center justify-center gap-2 rounded-xl bg-white dark:bg-white/5 py-3 md:py-3.5 text-[11px] md:text-xs font-bold uppercase tracking-widest text-gray-900 dark:text-white ring-1 ring-gray-200 dark:ring-white/10 transition-all group-hover:bg-purple-600 group-hover:text-white group-hover:ring-purple-600 dark:group-hover:bg-purple-600 dark:group-hover:text-white mt-4 shadow-sm">
                            Lihat Detail <ArrowRight size={14} className="transition-transform group-hover:translate-x-1" />
                        </button>
                    </div>
                </div>
            ))}
        </div>
      </section>
  );
};
