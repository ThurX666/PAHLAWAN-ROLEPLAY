
import React from 'react';
import { X, DollarSign, Activity, Car, Home, Shield, Ban, Key, Skull, Edit, AlertTriangle, Save } from 'lucide-react';
import { Player } from '../../../types';

interface PlayerControlModalProps {
    player: Player;
    onClose: () => void;
    onAction: (action: string) => void;
    onSave: (e: React.FormEvent) => void;
    actionLoading: string | null;
}

export const PlayerControlModal: React.FC<PlayerControlModalProps> = ({ player, onClose, onAction, onSave, actionLoading }) => {
  return (
    <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
        <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 w-full max-w-2xl rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col overflow-hidden max-h-[95dvh] animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
            
            {/* Mobile Drag Handle */}
            <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

            {/* Header */}
            <div className="flex justify-between items-center p-4 border-b border-gray-200 dark:border-white/5 bg-gray-50 dark:bg-[#151515]">
                <div>
                    <h3 className="text-sm md:text-lg font-black text-gray-900 dark:text-white uppercase italic">Control Center: {player.name}</h3>
                    <p className="text-[10px] text-gray-500 font-mono">Database ID: #{player.id} | IP: 192.168.1.XX</p>
                </div>
                <button onClick={onClose} className="text-gray-500 hover:text-red-500"><X size={20}/></button>
            </div>

            <div className="flex-1 overflow-y-auto p-4 md:p-6 space-y-6">
                
                {/* 1. Quick Stats & Economy Check */}
                <div className="grid grid-cols-2 md:grid-cols-4 gap-3">
                    <div className="p-3 bg-green-50 dark:bg-green-900/10 border border-green-200 dark:border-green-900/30 rounded-lg">
                        <p className="text-[9px] uppercase font-bold text-green-600 dark:text-green-400 mb-1 flex items-center"><DollarSign size={10} className="mr-1"/> Cash</p>
                        <p className="text-sm font-black text-gray-900 dark:text-white">${(player.money || 0).toLocaleString()}</p>
                    </div>
                    <div className="p-3 bg-blue-50 dark:bg-blue-900/10 border border-blue-200 dark:border-blue-900/30 rounded-lg">
                        <p className="text-[9px] uppercase font-bold text-blue-600 dark:text-blue-400 mb-1 flex items-center"><Activity size={10} className="mr-1"/> Score/Level</p>
                        <p className="text-sm font-black text-gray-900 dark:text-white">{player.score}</p>
                    </div>
                    <div className="p-3 bg-amber-50 dark:bg-amber-900/10 border border-amber-200 dark:border-amber-900/30 rounded-lg">
                        <p className="text-[9px] uppercase font-bold text-amber-600 dark:text-amber-400 mb-1 flex items-center"><Car size={10} className="mr-1"/> Vehicles</p>
                        <p className="text-sm font-black text-gray-900 dark:text-white">2 Unit</p>
                    </div>
                    <div className="p-3 bg-purple-50 dark:bg-purple-900/10 border border-purple-200 dark:border-purple-900/30 rounded-lg">
                        <p className="text-[9px] uppercase font-bold text-purple-600 dark:text-purple-400 mb-1 flex items-center"><Home size={10} className="mr-1"/> Property</p>
                        <p className="text-sm font-black text-gray-900 dark:text-white">1 Unit</p>
                    </div>
                </div>

                {/* 2. Admin Actions (The reason UCP exists) */}
                <div>
                    <h4 className="text-xs font-bold text-gray-500 uppercase mb-3 flex items-center gap-2 border-b border-gray-200 dark:border-white/5 pb-2">
                        <Shield size={14} /> Administrative Actions
                    </h4>
                    <div className="grid grid-cols-2 md:grid-cols-4 gap-3">
                        <button 
                            onClick={() => onAction('Kick')}
                            disabled={!!actionLoading}
                            className="p-3 bg-gray-100 dark:bg-white/5 hover:bg-gray-200 dark:hover:bg-white/10 rounded-lg text-left transition-colors border border-transparent hover:border-gray-300 dark:hover:border-white/20"
                        >
                            <Activity className="mb-2 text-amber-500" size={20} />
                            <span className="block text-xs font-bold text-gray-900 dark:text-white">Kick Player</span>
                            <span className="text-[9px] text-gray-500">Force disconnect</span>
                        </button>
                        
                        <button 
                            onClick={() => onAction('Ban')}
                            disabled={!!actionLoading}
                            className="p-3 bg-red-50 dark:bg-red-900/10 hover:bg-red-100 dark:hover:bg-red-900/20 rounded-lg text-left transition-colors border border-red-200 dark:border-red-900/30"
                        >
                            <Ban className="mb-2 text-red-600" size={20} />
                            <span className="block text-xs font-bold text-red-700 dark:text-red-400">Ban Account</span>
                            <span className="text-[9px] text-red-500/70">Block access</span>
                        </button>

                        <button 
                            onClick={() => onAction('Reset PW')}
                            disabled={!!actionLoading}
                            className="p-3 bg-blue-50 dark:bg-blue-900/10 hover:bg-blue-100 dark:hover:bg-blue-900/20 rounded-lg text-left transition-colors border border-blue-200 dark:border-blue-900/30"
                        >
                            <Key className="mb-2 text-blue-600" size={20} />
                            <span className="block text-xs font-bold text-blue-700 dark:text-blue-400">Reset Password</span>
                            <span className="text-[9px] text-blue-500/70">Send temp pass</span>
                        </button>

                        <button 
                            onClick={() => onAction('CK')}
                            disabled={!!actionLoading}
                            className="p-3 bg-gray-900 dark:bg-black hover:bg-gray-800 rounded-lg text-left transition-colors border border-gray-700"
                        >
                            <Skull className="mb-2 text-gray-400" size={20} />
                            <span className="block text-xs font-bold text-white">Character Kill</span>
                            <span className="text-[9px] text-gray-500">Wipe progress</span>
                        </button>
                    </div>
                </div>

                {/* 3. Basic Data Edit Form */}
                <form onSubmit={onSave} className="space-y-4 pt-4 border-t border-gray-200 dark:border-white/5">
                    <h4 className="text-xs font-bold text-gray-500 uppercase mb-1 flex items-center gap-2">
                        <Edit size={14} /> Edit Data Dasar
                    </h4>
                    <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                        <div>
                            <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Set Faksi</label>
                            <select 
                                name="faction"
                                className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-2.5 text-xs text-gray-900 dark:text-white"
                                defaultValue={player.faction}
                            >
                                <option value="Warga Sipil">Warga Sipil</option>
                                <option value="LSPD">LSPD (Police)</option>
                                <option value="SAMD">SAMD (Medic)</option>
                                <option value="Grove Street">Grove Street</option>
                                <option value="Gov">Government</option>
                            </select>
                        </div>
                        <div>
                            <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Set Level (Score)</label>
                            <input 
                                type="number"
                                name="score"
                                className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-2.5 text-xs text-gray-900 dark:text-white"
                                defaultValue={player.score}
                            />
                        </div>
                    </div>
                    
                    {/* Security Warning */}
                    <div className="bg-yellow-50 dark:bg-yellow-900/10 border border-yellow-200 dark:border-yellow-900/30 p-3 rounded-lg flex items-start gap-3">
                        <AlertTriangle className="text-yellow-600 shrink-0" size={16} />
                        <p className="text-[10px] text-yellow-800 dark:text-yellow-200 leading-relaxed">
                            Setiap perubahan data di panel ini akan dicatat dalam <strong>Admin Log</strong>. Penyalahgunaan fitur (Abuse Admin) akan mengakibatkan penurunan pangkat atau ban permanen.
                        </p>
                    </div>

                    <div className="flex justify-end gap-2 pt-2">
                        <button 
                            type="button" 
                            onClick={onClose}
                            className="px-4 py-2 rounded-lg text-gray-500 font-bold text-xs uppercase hover:bg-gray-100 dark:hover:bg-white/5"
                        >
                            Batal
                        </button>
                        <button 
                            type="submit"
                            className="px-6 py-2 rounded-lg bg-red-600 hover:bg-red-500 text-white font-bold text-xs uppercase shadow-lg shadow-red-600/20"
                        >
                            <Save size={14} className="inline mr-1" /> Simpan Perubahan
                        </button>
                    </div>
                </form>

            </div>
        </div>
    </div>
  );
};
