
import React, { useState } from 'react';
import { Info, X } from 'lucide-react';

export const SimulationInfo: React.FC = () => {
  const [isOpen, setIsOpen] = useState(false);

  return (
    <div className="fixed bottom-4 right-4 z-50 flex flex-col items-end">
        {isOpen && (
            <div className="mb-3 bg-black/80 backdrop-blur-md border border-white/10 p-4 rounded-2xl shadow-2xl animate-[fadeIn_0.2s_ease-out] w-72">
                <div className="flex justify-between items-center mb-3">
                    <h4 className="text-xs font-black text-white uppercase flex items-center gap-2">
                        <Info className="text-red-500" size={14} /> Info Simulasi
                    </h4>
                    <button onClick={() => setIsOpen(false)} className="text-gray-500 hover:text-white transition-colors">
                        <X size={14} />
                    </button>
                </div>
                <div className="space-y-2 text-xs text-gray-400 font-mono bg-white/5 p-3 rounded-xl border border-white/5">
                    <div className="flex justify-between items-center">
                        <span className="flex items-center gap-2"><div className="w-2 h-2 rounded-full bg-red-500"></div> <span className="font-bold text-gray-300">Admin:</span></span>
                        <span className="text-red-400 bg-red-500/10 px-2 py-0.5 rounded-md">admin</span>
                    </div>
                    <div className="flex justify-between items-center">
                        <span className="flex items-center gap-2"><div className="w-2 h-2 rounded-full bg-green-500"></div> <span className="font-bold text-gray-300">Player:</span></span>
                        <span className="text-green-400 bg-green-500/10 px-2 py-0.5 rounded-md">player</span>
                    </div>
                </div>
                <p className="text-[10px] text-gray-500 mt-3 text-center italic">Gunakan username di atas, password bebas.</p>
            </div>
        )}

        {!isOpen && (
            <button 
                onClick={() => setIsOpen(true)}
                className="flex items-center justify-center gap-2 bg-black/60 backdrop-blur-md border border-white/10 text-gray-300 hover:text-white hover:bg-black/80 transition-all px-4 py-2 rounded-full shadow-lg text-[10px] uppercase tracking-widest font-bold"
            >
                <Info size={14} className="text-red-500" />
                Info Simulasi
            </button>
        )}
    </div>
  );
};
