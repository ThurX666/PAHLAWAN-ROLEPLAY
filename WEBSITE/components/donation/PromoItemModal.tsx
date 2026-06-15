
import React from 'react';
import { X, ShoppingCart } from 'lucide-react';
import { PromoItem } from '../../types';

interface PromoItemModalProps {
    item: PromoItem;
    onClose: () => void;
    onRedeem?: (item: PromoItem) => void;
}

export const PromoItemModal: React.FC<PromoItemModalProps> = ({ item, onClose, onRedeem }) => {
  return (
      <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/90 backdrop-blur-md animate-[fadeIn_0.2s_ease-out]">
           <div className="bg-[#121212] border border-gray-800 w-full max-w-2xl rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col md:flex-row overflow-hidden max-h-[95dvh] animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
               
               {/* Mobile Drag Handle */}
               <div className="w-12 h-1.5 bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden absolute top-0 left-1/2 -translate-x-1/2 z-10"></div>

               {/* Image Section */}
               <div className="w-full md:w-1/2 h-48 md:h-auto relative shrink-0">
                   <img src={item.image} alt={item.name} className="w-full h-full object-cover" />
                   <div className="absolute inset-0 bg-gradient-to-t from-[#121212] via-transparent to-transparent md:bg-gradient-to-r"></div>
                   {item.isLimited && (
                       <div className="absolute top-4 left-4 bg-red-600 text-white text-[10px] font-black px-3 py-1 rounded uppercase tracking-widest shadow-lg">
                           Limited Edition
                       </div>
                   )}
               </div>
               
               {/* Detail Section */}
               <div className="w-full md:w-1/2 p-6 md:p-8 flex flex-col relative">
                   <button onClick={onClose} className="absolute top-4 right-4 text-gray-500 hover:text-white transition-colors">
                       <X size={24} />
                   </button>

                   <div className="mb-4">
                       <span className="text-xs font-bold text-purple-400 uppercase tracking-widest mb-1 block">{item.type}</span>
                       <h2 className="text-2xl md:text-3xl font-black text-white uppercase italic leading-none">{item.name}</h2>
                   </div>

                   <div className="flex items-end gap-3 mb-6">
                       <span className="text-3xl font-black text-yellow-400">{item.priceGold} <span className="text-sm font-bold text-yellow-600">GC</span></span>
                       {item.originalPriceGold && (
                           <span className="text-sm text-gray-500 line-through mb-1.5">{item.originalPriceGold} GC</span>
                       )}
                   </div>

                   <p className="text-sm text-gray-300 leading-relaxed mb-6 border-l-2 border-gray-700 pl-4 italic">
                       {item.description}
                   </p>

                   <div className="grid grid-cols-1 gap-2 mb-8">
                       {item.stats.map((stat, idx) => (
                           <div key={idx} className="flex justify-between items-center bg-white/5 p-2 rounded px-3 border border-white/5">
                               <span className="text-[10px] text-gray-400 uppercase font-bold">{stat.label}</span>
                               <span className="text-xs font-bold text-white font-mono">{stat.value}</span>
                           </div>
                       ))}
                   </div>

                   <div className="mt-auto">
                       <button 
                           onClick={() => {
                               if (onRedeem) {
                                   onRedeem(item);
                               }
                           }}
                           className="w-full bg-yellow-500 hover:bg-yellow-400 text-black font-black py-4 rounded-xl uppercase text-xs tracking-widest shadow-lg shadow-yellow-500/20 transform active:scale-95 transition-all flex items-center justify-center gap-2"
                       >
                           <ShoppingCart size={16} /> Beli Sekarang
                       </button>
                       <p className="text-[9px] text-center text-gray-500 mt-2">
                           Pastikan saldo Gold Coin Anda mencukupi sebelum membeli.
                       </p>
                   </div>
               </div>
           </div>
      </div>
  );
};
