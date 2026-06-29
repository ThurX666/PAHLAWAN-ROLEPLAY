import React, { useState } from 'react';
import { X, MapPin, Home, Users, CheckCircle2, AlertCircle, Box, Trees, Layout, MessageSquare } from 'lucide-react';
import { Character } from '../../types';

interface CustomMappingModalProps {
    characters: Character[];
    userGold: number;
    onClose: () => void;
    onConfirm: (characterId: number, targetName: string, tierName: string, price: number, scope: string, theme: string, notes: string) => void;
    isProcessing: boolean;
}

const MAPPING_TIERS = [
    { id: 'low', name: 'Low Mapping', objects: 50, price: 1000, desc: 'Cocok untuk dekorasi interior kecil atau eksterior minimalis.' },
    { id: 'medium', name: 'Medium Mapping', objects: 150, price: 2000, desc: 'Ideal untuk rumah menengah atau bisnis kecil.' },
    { id: 'high', name: 'High Mapping', objects: 300, price: 3500, desc: 'Sempurna untuk mansion, bisnis besar, atau markas.' },
    { id: 'extreme', name: 'Extreme Mapping', objects: 500, price: 5000, desc: 'Maksimal object untuk FnG Hood atau kompleks besar.' },
];

// Mock properties since we don't have real property data in props
const MOCK_PROPERTIES = [
    { id: 1, name: 'House #102 (Vinewood)', type: 'house' },
    { id: 2, name: 'Business #45 (Idlewood Gas)', type: 'business' },
];

const SCOPES = [
    { id: 'Interior Only', label: 'Interior Only', icon: Box, desc: 'Fokus pada bagian dalam ruangan' },
    { id: 'Exterior Only', label: 'Exterior Only', icon: Trees, desc: 'Fokus pada halaman & luar bangunan' },
    { id: 'Interior + Exterior', label: 'Interior + Exterior', icon: Layout, desc: 'Kombinasi luar dan dalam' }
];

const THEMES = [
    "Modern Minimalist",
    "Industrial & Raw",
    "Luxury / High-End",
    "Street / Ghetto",
    "Vintage / Classic",
    "Cozy / Warm",
    "Cyberpunk / Neon"
];

export const CustomMappingModal: React.FC<CustomMappingModalProps> = ({
    characters,
    userGold,
    onClose,
    onConfirm,
    isProcessing
}) => {
    const [step, setStep] = useState<1 | 2 | 3 | 4>(1);
    const [selectedCharacterId, setSelectedCharacterId] = useState<number | null>(null);
    const [selectedTarget, setSelectedTarget] = useState<{ type: string, name: string } | null>(null);
    const [selectedTier, setSelectedTier] = useState<typeof MAPPING_TIERS[0] | null>(null);
    const [mappingScope, setMappingScope] = useState<string>('');
    const [mappingTheme, setMappingTheme] = useState<string>('');
    const [mappingNotes, setMappingNotes] = useState<string>('');

    // Find if selected character is in a faction (FnG)
    const selectedCharacter = characters.find(c => c.id === selectedCharacterId);
    const factionLower = selectedCharacter?.faction?.toLowerCase().trim() || 'none';
    const isFnG = selectedCharacter && 
                  factionLower !== 'none' && 
                  factionLower !== 'civilian' && 
                  factionLower !== 'warga sipil' &&
                  !['lspd', 'safmd', 'gov', 'san andreas government', 'police', 'medic'].includes(factionLower);

    const handleNextStep1 = () => {
        if (selectedCharacterId && selectedTarget) setStep(2);
    };

    const handleNextStep2 = () => {
        if (selectedTier) setStep(3);
    };

    const handleNextStep3 = () => {
        if (mappingScope && mappingTheme) setStep(4);
    };

    const handleConfirm = () => {
        if (selectedCharacterId && selectedTarget && selectedTier && mappingScope && mappingTheme) {
            onConfirm(selectedCharacterId, selectedTarget.name, selectedTier.name, selectedTier.price, mappingScope, mappingTheme, mappingNotes);
        }
    };

    return (
        <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/60 backdrop-blur-sm animate-in fade-in duration-200">
            <div className="bg-white dark:bg-ph-surface-panel w-full max-w-2xl overflow-hidden shadow-2xl border border-gray-200 dark:border-white/10 flex flex-col max-h-[95dvh] rounded-t-3xl md:rounded-2xl animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                
                {/* Mobile Drag Handle */}
                <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

                {/* Header */}
                <div className="p-5 md:p-6 border-b border-gray-100 dark:border-white/5 flex justify-between items-center bg-gray-50 dark:bg-black/20">
                    <div>
                        <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tight">Custom Mapping</h3>
                        <p className="text-xs text-gray-500 font-medium mt-1">
                            {step === 1 ? 'Pilih Karakter & Target Lokasi' : step === 2 ? 'Pilih Paket Mapping' : step === 3 ? 'Detail Mapping' : 'Konfirmasi Pembayaran'}
                        </p>
                    </div>
                    <button 
                        onClick={onClose}
                        className="p-2 text-gray-400 hover:text-gray-600 dark:hover:text-white hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors"
                    >
                        <X size={20} />
                    </button>
                </div>

                {/* Content */}
                <div className="p-5 md:p-6 overflow-y-auto flex-1">
                    {step === 1 && (
                        <div className="space-y-6">
                            {/* Character Selection */}
                            <div>
                                <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase tracking-wider mb-3">1. Pilih Karakter</label>
                                <div className="grid grid-cols-1 sm:grid-cols-2 gap-3">
                                    {characters.map(char => (
                                        <div 
                                            key={char.id}
                                            onClick={() => {
                                                setSelectedCharacterId(char.id);
                                                setSelectedTarget(null); // Reset target when character changes
                                            }}
                                            className={`p-3 rounded-xl border-2 cursor-pointer transition-all flex items-center gap-3 ${
                                                selectedCharacterId === char.id 
                                                ? 'border-indigo-500 bg-indigo-50 dark:bg-indigo-500/10' 
                                                : 'border-gray-200 dark:border-white/10 hover:border-indigo-300 dark:hover:border-white/20'
                                            }`}
                                        >
                                            <div className={`w-10 h-10 rounded-lg flex items-center justify-center ${selectedCharacterId === char.id ? 'bg-indigo-500 text-white' : 'bg-gray-100 dark:bg-white/5 text-gray-500'}`}>
                                                <Users size={20} />
                                            </div>
                                            <div>
                                                <p className="text-sm font-bold text-gray-900 dark:text-white">{char.name}</p>
                                                <p className="text-[10px] text-gray-500 uppercase">{char.faction !== 'None' ? char.faction : 'Civilian'}</p>
                                            </div>
                                        </div>
                                    ))}
                                </div>
                            </div>

                            {/* Target Selection */}
                            {selectedCharacterId && (
                                <div className="animate-in slide-in-from-bottom-4 fade-in duration-300">
                                    <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase tracking-wider mb-3">2. Pilih Target Mapping</label>
                                    <div className="space-y-2">
                                        {MOCK_PROPERTIES.map(prop => (
                                            <div 
                                                key={prop.id}
                                                onClick={() => setSelectedTarget({ type: prop.type, name: prop.name })}
                                                className={`p-4 rounded-xl border-2 cursor-pointer transition-all flex items-center gap-3 ${
                                                    selectedTarget?.name === prop.name 
                                                    ? 'border-indigo-500 bg-indigo-50 dark:bg-indigo-500/10' 
                                                    : 'border-gray-200 dark:border-white/10 hover:border-indigo-300 dark:hover:border-white/20'
                                                }`}
                                            >
                                                <Home size={18} className={selectedTarget?.name === prop.name ? 'text-indigo-500' : 'text-gray-400'} />
                                                <span className="text-sm font-bold text-gray-900 dark:text-white">{prop.name}</span>
                                            </div>
                                        ))}
                                        
                                        {/* FnG Hood Option */}
                                        {isFnG && (
                                            <div 
                                                onClick={() => setSelectedTarget({ type: 'fng', name: `FnG Hood (${selectedCharacter.faction})` })}
                                                className={`p-4 rounded-xl border-2 cursor-pointer transition-all flex items-center gap-3 ${
                                                    selectedTarget?.type === 'fng' 
                                                    ? 'border-red-500 bg-red-50 dark:bg-red-500/10' 
                                                    : 'border-dashed border-red-300 dark:border-red-500/30 hover:border-red-500 dark:hover:border-red-500/50'
                                                }`}
                                            >
                                                <MapPin size={18} className={selectedTarget?.type === 'fng' ? 'text-red-500' : 'text-red-400'} />
                                                <div>
                                                    <span className="text-sm font-bold text-gray-900 dark:text-white block">FnG Hood Mapping</span>
                                                    <span className="text-[10px] text-red-500 uppercase tracking-wider">{selectedCharacter.faction}</span>
                                                </div>
                                            </div>
                                        )}
                                    </div>
                                </div>
                            )}
                        </div>
                    )}

                    {step === 2 && (
                        <div className="space-y-4 animate-in slide-in-from-right-8 fade-in duration-300">
                            <div className="bg-gray-50 dark:bg-black/20 p-4 rounded-xl border border-gray-200 dark:border-white/5 mb-6">
                                <p className="text-xs text-gray-500 uppercase font-bold mb-1">Target Mapping:</p>
                                <p className="text-sm font-black text-gray-900 dark:text-white">{selectedTarget?.name}</p>
                            </div>

                            <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
                                {MAPPING_TIERS.map(tier => (
                                    <div 
                                        key={tier.id}
                                        onClick={() => {
                                            setSelectedTier(tier);
                                            // Reset scope if downgrading from High/Extreme to Low/Medium
                                            if (mappingScope === 'Interior + Exterior' && !['high', 'extreme'].includes(tier.id)) {
                                                setMappingScope('');
                                            }
                                        }}
                                        className={`p-5 rounded-xl border-2 cursor-pointer transition-all relative overflow-hidden group ${
                                            selectedTier?.id === tier.id 
                                            ? 'border-yellow-500 bg-yellow-50 dark:bg-yellow-500/10' 
                                            : 'border-gray-200 dark:border-white/10 hover:border-yellow-400/50'
                                        }`}
                                    >
                                        {selectedTier?.id === tier.id && (
                                            <div className="absolute top-0 right-0 bg-yellow-500 text-black text-[10px] font-black px-3 py-1 rounded-bl-lg uppercase">
                                                Terpilih
                                            </div>
                                        )}
                                        <h4 className="text-lg font-black text-gray-900 dark:text-white italic uppercase">{tier.name}</h4>
                                        <div className="flex items-center gap-2 mt-2 mb-3">
                                            <span className="text-xs font-bold bg-gray-200 dark:bg-white/10 px-2 py-1 rounded text-gray-700 dark:text-gray-300">
                                                {tier.objects} Objects
                                            </span>
                                        </div>
                                        <p className="text-xs text-gray-500 dark:text-gray-400 leading-relaxed mb-4 min-h-[40px]">
                                            {tier.desc}
                                        </p>
                                        <div className="text-lg font-black text-yellow-600 dark:text-yellow-500">
                                            {tier.price} GC
                                        </div>
                                    </div>
                                ))}
                            </div>
                        </div>
                    )}

                    {step === 3 && (
                        <div className="space-y-6 animate-in slide-in-from-right-8 fade-in duration-300">
                            {/* Scope Selection */}
                            <div>
                                <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase tracking-wider mb-3">1. Area Mapping</label>
                                <div className="grid grid-cols-1 sm:grid-cols-3 gap-3">
                                    {SCOPES.filter(scope => scope.id !== 'Interior + Exterior' || ['high', 'extreme'].includes(selectedTier?.id || '')).map(scope => {
                                        const Icon = scope.icon;
                                        return (
                                            <div 
                                                key={scope.id}
                                                onClick={() => setMappingScope(scope.id)}
                                                className={`p-4 rounded-xl border-2 cursor-pointer transition-all flex flex-col items-center text-center gap-2 ${
                                                    mappingScope === scope.id 
                                                    ? 'border-indigo-500 bg-indigo-50 dark:bg-indigo-500/10' 
                                                    : 'border-gray-200 dark:border-white/10 hover:border-indigo-300 dark:hover:border-white/20'
                                                }`}
                                            >
                                                <Icon size={24} className={mappingScope === scope.id ? 'text-indigo-500' : 'text-gray-400'} />
                                                <div>
                                                    <span className="text-sm font-bold text-gray-900 dark:text-white block">{scope.label}</span>
                                                    <span className="text-[9px] text-gray-500 mt-1 block">{scope.desc}</span>
                                                </div>
                                            </div>
                                        );
                                    })}
                                </div>
                            </div>

                            {/* Theme Selection */}
                            <div>
                                <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase tracking-wider mb-3">2. Tema / Style</label>
                                <div className="flex flex-wrap gap-2">
                                    {THEMES.map(theme => (
                                        <button 
                                            key={theme}
                                            onClick={() => setMappingTheme(theme)}
                                            className={`px-4 py-2 rounded-lg text-xs font-bold transition-all border ${
                                                mappingTheme === theme 
                                                ? 'bg-indigo-600 border-indigo-600 text-white shadow-md shadow-indigo-500/20' 
                                                : 'bg-white dark:bg-ph-surface-elevated border-gray-200 dark:border-white/10 text-gray-600 dark:text-gray-300 hover:border-indigo-300 dark:hover:border-white/30'
                                            }`}
                                        >
                                            {theme}
                                        </button>
                                    ))}
                                </div>
                            </div>

                            {/* Notes */}
                            <div>
                                <label className="block text-xs font-bold text-gray-700 dark:text-gray-300 uppercase tracking-wider mb-3 flex items-center gap-2">
                                    <MessageSquare size={14} />
                                    3. Catatan Tambahan (Opsional)
                                </label>
                                <textarea 
                                    value={mappingNotes}
                                    onChange={(e) => setMappingNotes(e.target.value)}
                                    placeholder="Contoh: Tolong buatkan garasi yang luas, tambahkan banyak tanaman hijau, warna dominan hitam putih..."
                                    className="w-full h-24 bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl p-4 text-sm text-gray-900 dark:text-white placeholder-gray-400 focus:outline-none focus:border-indigo-500 focus:ring-1 focus:ring-indigo-500 transition-all resize-none"
                                />
                                <p className="text-[10px] text-gray-500 mt-2">Berikan detail spesifik agar mapper dapat menyesuaikan dengan keinginan Anda.</p>
                            </div>
                        </div>
                    )}

                    {step === 4 && selectedTier && selectedTarget && selectedCharacter && (
                        <div className="space-y-6 animate-in slide-in-from-right-8 fade-in duration-300">
                            <div className="bg-yellow-50 dark:bg-yellow-500/10 border border-yellow-200 dark:border-yellow-500/20 rounded-xl p-6 text-center">
                                <h4 className="text-xl font-black text-gray-900 dark:text-white uppercase italic mb-2">Konfirmasi Pesanan</h4>
                                <p className="text-sm text-gray-600 dark:text-gray-400">Anda akan menukarkan Gold Coin untuk layanan Custom Mapping.</p>
                            </div>

                            <div className="bg-gray-50 dark:bg-ph-surface-input rounded-xl border border-gray-200 dark:border-white/5 p-5 space-y-4">
                                <div className="flex justify-between items-center pb-4 border-b border-gray-200 dark:border-white/5">
                                    <span className="text-sm text-gray-500 font-medium">Karakter</span>
                                    <span className="text-sm font-bold text-gray-900 dark:text-white">{selectedCharacter.name}</span>
                                </div>
                                <div className="flex justify-between items-center pb-4 border-b border-gray-200 dark:border-white/5">
                                    <span className="text-sm text-gray-500 font-medium">Target Lokasi</span>
                                    <span className="text-sm font-bold text-gray-900 dark:text-white">{selectedTarget.name}</span>
                                </div>
                                <div className="flex justify-between items-center pb-4 border-b border-gray-200 dark:border-white/5">
                                    <span className="text-sm text-gray-500 font-medium">Paket Mapping</span>
                                    <div className="text-right">
                                        <span className="text-sm font-bold text-gray-900 dark:text-white block">{selectedTier.name}</span>
                                        <span className="text-[10px] text-gray-500 uppercase">{selectedTier.objects} Objects</span>
                                    </div>
                                </div>
                                <div className="pb-4 border-b border-gray-200 dark:border-white/5 space-y-2">
                                    <div className="flex justify-between items-center">
                                        <span className="text-sm text-gray-500 font-medium">Area</span>
                                        <span className="text-sm font-bold text-gray-900 dark:text-white">{mappingScope}</span>
                                    </div>
                                    <div className="flex justify-between items-center">
                                        <span className="text-sm text-gray-500 font-medium">Tema</span>
                                        <span className="text-sm font-bold text-gray-900 dark:text-white">{mappingTheme}</span>
                                    </div>
                                    {mappingNotes && (
                                        <div className="pt-2">
                                            <span className="text-xs text-gray-500 font-medium block mb-1">Catatan:</span>
                                            <p className="text-xs text-gray-700 dark:text-gray-300 bg-white dark:bg-black/40 p-3 rounded-lg border border-gray-200 dark:border-white/5 italic">"{mappingNotes}"</p>
                                        </div>
                                    )}
                                </div>
                                <div className="flex justify-between items-center pt-2">
                                    <span className="text-base font-black text-gray-900 dark:text-white uppercase">Total Biaya</span>
                                    <span className="text-xl font-black text-yellow-600 dark:text-yellow-500">{selectedTier.price} GC</span>
                                </div>
                            </div>

                            <div className="bg-red-50 dark:bg-red-500/10 border border-red-200 dark:border-red-500/20 rounded-xl p-4 flex gap-3">
                                <AlertCircle className="text-red-500 shrink-0 mt-0.5" size={18} />
                                <div>
                                    <p className="text-sm font-bold text-red-800 dark:text-red-400 mb-1">Syarat & Ketentuan</p>
                                    <div className="text-xs text-red-600 dark:text-red-300 leading-relaxed space-y-1">
                                        <p>Mapping bersifat permanen. Namun, mapping akan <strong>HANGUS / DIHAPUS</strong> apabila:</p>
                                        <ul className="list-disc ml-4">
                                            <li>Property (Rumah/Bisnis) dijual atau berpindah tangan ke player lain.</li>
                                            <li>Fraksi (FnG) terkena status <em>Takedown</em> atau dibubarkan.</li>
                                        </ul>
                                    </div>
                                </div>
                            </div>

                            {userGold < selectedTier.price && (
                                <div className="flex items-start gap-3 p-4 bg-red-50 dark:bg-red-500/10 border border-red-200 dark:border-red-500/20 rounded-xl">
                                    <AlertCircle className="text-red-500 shrink-0 mt-0.5" size={18} />
                                    <div>
                                        <p className="text-sm font-bold text-red-800 dark:text-red-400">Saldo Gold Coin Tidak Cukup</p>
                                        <p className="text-xs text-red-600 dark:text-red-300 mt-1">Anda membutuhkan {selectedTier.price - userGold} GC lagi untuk membeli paket ini.</p>
                                    </div>
                                </div>
                            )}
                        </div>
                    )}
                </div>

                {/* Footer Actions */}
                <div className="p-5 md:p-6 border-t border-gray-100 dark:border-white/5 bg-gray-50 dark:bg-black/20 flex justify-between items-center">
                    {step > 1 ? (
                        <button 
                            onClick={() => setStep(step - 1 as 1 | 2 | 3)}
                            className="px-6 py-2.5 rounded-xl font-bold text-sm text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10 transition-colors"
                        >
                            Kembali
                        </button>
                    ) : (
                        <div></div>
                    )}

                    {step === 1 && (
                        <button 
                            onClick={handleNextStep1}
                            disabled={!selectedCharacterId || !selectedTarget}
                            className="px-8 py-2.5 bg-indigo-600 hover:bg-indigo-500 disabled:bg-gray-300 dark:disabled:bg-gray-800 disabled:text-gray-500 text-white font-bold text-sm rounded-xl transition-colors shadow-lg shadow-indigo-500/20 disabled:shadow-none"
                        >
                            Lanjut
                        </button>
                    )}

                    {step === 2 && (
                        <button 
                            onClick={handleNextStep2}
                            disabled={!selectedTier}
                            className="px-8 py-2.5 bg-indigo-600 hover:bg-indigo-500 disabled:bg-gray-300 dark:disabled:bg-gray-800 disabled:text-gray-500 text-white font-bold text-sm rounded-xl transition-colors shadow-lg shadow-indigo-500/20 disabled:shadow-none"
                        >
                            Lanjut Detail
                        </button>
                    )}

                    {step === 3 && (
                        <button 
                            onClick={handleNextStep3}
                            disabled={!mappingScope || !mappingTheme}
                            className="px-8 py-2.5 bg-indigo-600 hover:bg-indigo-500 disabled:bg-gray-300 dark:disabled:bg-gray-800 disabled:text-gray-500 text-white font-bold text-sm rounded-xl transition-colors shadow-lg shadow-indigo-500/20 disabled:shadow-none"
                        >
                            Lanjut Konfirmasi
                        </button>
                    )}

                    {step === 4 && selectedTier && (
                        <button 
                            onClick={handleConfirm}
                            disabled={isProcessing || userGold < selectedTier.price}
                            className="px-8 py-2.5 bg-yellow-500 hover:bg-yellow-400 disabled:bg-gray-300 dark:disabled:bg-gray-800 disabled:text-gray-500 text-black font-black uppercase text-sm rounded-xl transition-colors shadow-lg shadow-yellow-500/20 disabled:shadow-none flex items-center gap-2"
                        >
                            {isProcessing ? (
                                <span className="animate-pulse">Memproses...</span>
                            ) : (
                                <>
                                    <CheckCircle2 size={18} />
                                    Bayar Sekarang
                                </>
                            )}
                        </button>
                    )}
                </div>
            </div>
        </div>
    );
};
