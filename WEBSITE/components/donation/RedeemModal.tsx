import React, { useState } from 'react';
import { X, User, Check, AlertCircle } from 'lucide-react';
import { Character } from '../../types';

interface ShopItem {
    id: number;
    name: string;
    price: number;
    category: 'layanan' | 'vehicle' | 'skin';
    image?: string;
    description: string;
}

interface RedeemModalProps {
    item: ShopItem;
    characters: Character[];
    onClose: () => void;
    onConfirm: (characterId: number) => void;
    isProcessing: boolean;
}

export const RedeemModal: React.FC<RedeemModalProps> = ({ 
    item, 
    characters, 
    onClose, 
    onConfirm,
    isProcessing 
}) => {
    const [selectedCharId, setSelectedCharId] = useState<number | null>(null);

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        if (selectedCharId) {
            onConfirm(selectedCharId);
        }
    };

    return (
        <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
            <div className="bg-white dark:bg-[#18181b] w-full max-w-md rounded-t-3xl md:rounded-2xl shadow-2xl border border-gray-200 dark:border-white/10 overflow-hidden flex flex-col max-h-[95dvh] animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                
                {/* Mobile Drag Handle */}
                <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

                {/* Header */}
                <div className="p-5 border-b border-gray-100 dark:border-white/5 flex justify-between items-center bg-gray-50/50 dark:bg-white/5">
                    <div>
                        <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-wide">
                            Konfirmasi Penukaran
                        </h3>
                        <p className="text-xs text-gray-500 font-medium mt-0.5">
                            Pilih karakter penerima item
                        </p>
                    </div>
                    <button 
                        onClick={onClose}
                        className="p-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors text-gray-500 dark:text-gray-400"
                    >
                        <X size={18} />
                    </button>
                </div>

                {/* Content */}
                <div className="p-6 overflow-y-auto custom-scrollbar">
                    
                    {/* Item Summary */}
                    <div className="flex items-start gap-4 mb-6 bg-indigo-50 dark:bg-indigo-900/10 p-4 rounded-xl border border-indigo-100 dark:border-indigo-500/20">
                        <div className="p-3 bg-indigo-100 dark:bg-indigo-500/20 rounded-lg text-indigo-600 dark:text-indigo-400">
                            <User size={24} />
                        </div>
                        <div>
                            <h4 className="font-bold text-gray-900 dark:text-white text-sm">{item.name}</h4>
                            <p className="text-xs text-gray-600 dark:text-gray-400 mt-1">{item.description}</p>
                            <div className="mt-2 inline-flex items-center px-2 py-1 rounded bg-indigo-200/50 dark:bg-indigo-500/20 border border-indigo-200 dark:border-indigo-500/30">
                                <span className="text-[10px] font-black text-indigo-700 dark:text-indigo-300 uppercase tracking-wider">
                                    Harga: {item.price} GC
                                </span>
                            </div>
                        </div>
                    </div>

                    <form onSubmit={handleSubmit} className="space-y-4">
                        <div className="space-y-2">
                            <label className="text-xs font-bold text-gray-500 uppercase tracking-wider block">
                                Pilih Karakter
                            </label>
                            
                            {characters.length > 0 ? (
                                <div className="grid gap-2">
                                    {characters.map((char) => (
                                        <label 
                                            key={char.id}
                                            className={`relative flex items-center gap-3 p-3 rounded-xl border cursor-pointer transition-all ${
                                                selectedCharId === char.id 
                                                ? 'bg-indigo-50 dark:bg-indigo-900/20 border-indigo-500 ring-1 ring-indigo-500' 
                                                : 'bg-white dark:bg-black/20 border-gray-200 dark:border-white/10 hover:border-gray-300 dark:hover:border-white/20'
                                            }`}
                                        >
                                            <input 
                                                type="radio" 
                                                name="character" 
                                                value={char.id}
                                                checked={selectedCharId === char.id}
                                                onChange={() => setSelectedCharId(char.id)}
                                                className="sr-only"
                                            />
                                            <div className={`w-4 h-4 rounded-full border flex items-center justify-center ${
                                                selectedCharId === char.id 
                                                ? 'border-indigo-500 bg-indigo-500' 
                                                : 'border-gray-300 dark:border-gray-600'
                                            }`}>
                                                {selectedCharId === char.id && <Check size={10} className="text-white" />}
                                            </div>
                                            <div>
                                                <p className="text-sm font-bold text-gray-900 dark:text-white">{char.name}</p>
                                                <p className="text-[10px] text-gray-500">Level {char.level} • {char.faction}</p>
                                            </div>
                                        </label>
                                    ))}
                                </div>
                            ) : (
                                <div className="text-center p-4 bg-red-50 dark:bg-red-900/10 rounded-xl border border-red-200 dark:border-red-900/30">
                                    <AlertCircle className="mx-auto text-red-500 mb-2" size={20} />
                                    <p className="text-xs text-red-600 dark:text-red-400 font-medium">
                                        Tidak ada karakter ditemukan. Buat karakter terlebih dahulu.
                                    </p>
                                </div>
                            )}
                        </div>

                        <div className="pt-4 border-t border-gray-100 dark:border-white/5 flex gap-3">
                            <button
                                type="button"
                                onClick={onClose}
                                className="flex-1 px-4 py-2.5 rounded-xl text-xs font-bold uppercase tracking-wider text-gray-600 dark:text-gray-400 hover:bg-gray-100 dark:hover:bg-white/5 transition-colors"
                            >
                                Batal
                            </button>
                            <button
                                type="submit"
                                disabled={!selectedCharId || isProcessing}
                                className="flex-1 px-4 py-2.5 rounded-xl bg-indigo-600 hover:bg-indigo-500 text-white text-xs font-bold uppercase tracking-wider shadow-lg shadow-indigo-500/20 disabled:opacity-50 disabled:cursor-not-allowed transition-all flex items-center justify-center gap-2"
                            >
                                {isProcessing ? (
                                    <>
                                        <span className="w-3 h-3 border-2 border-white/30 border-t-white rounded-full animate-spin"/>
                                        Memproses...
                                    </>
                                ) : (
                                    <>
                                        <Check size={14} />
                                        Konfirmasi
                                    </>
                                )}
                            </button>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    );
};
