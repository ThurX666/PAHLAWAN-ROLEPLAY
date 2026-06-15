
import React from 'react';
import { Character } from '../../types';
import { User, Trash2, CreditCard, Shield, Clock, Trophy, Wallet, Landmark, Phone, AlertTriangle, Hourglass, Skull, Building2 } from 'lucide-react';
import { getCharacterPhotoUrl } from '../../utils/imageUtils';

interface CharacterCardProps {
  character: Character;
  onSelect: (char: Character) => void;
  onDelete: (id: number) => void;
}

export const CharacterCard: React.FC<CharacterCardProps> = ({ character, onSelect, onDelete }) => {
  const getFactionDetails = (faction: string) => {
      const lower = faction?.toLowerCase() || '';
      if (lower === 'warga sipil' || lower === 'none' || !lower) {
          return { icon: User, color: 'text-gray-400' };
      }
      if (lower.includes('lspd') || lower.includes('lsmd') || lower.includes('gov') || lower.includes('police') || lower.includes('medical') || lower.includes('department')) {
          return { icon: Building2, color: 'text-blue-400' };
      }
      return { icon: Skull, color: 'text-red-500' };
  };

  const getStatusColor = (status: string) => {
      switch(status) {
          case 'Online': return 'bg-green-500 text-white shadow-green-500/50';
          case 'Jailed': return 'bg-red-600 text-white shadow-red-600/50';
          default: return 'bg-gray-500 text-white shadow-gray-500/50';
      }
  };

  return (
    <div className="group relative h-full bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-3xl overflow-hidden shadow-sm hover:shadow-2xl hover:border-red-500/30 transition-all duration-500 flex flex-col">
        
        {/* Header Status & Name */}
        <div className="absolute top-0 left-0 w-full p-5 flex justify-between items-start z-20">
            <div className={`px-3 py-1 rounded-full text-[10px] font-black uppercase tracking-widest shadow-lg backdrop-blur-md ${getStatusColor(character.status)}`}>
                {character.status}
            </div>
            <div className="flex flex-col items-end">
                <h3 className="text-2xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter drop-shadow-md">
                    {character.name.replace('_', ' ')}
                </h3>
                <div className="flex items-center gap-1.5 bg-black/50 backdrop-blur-md px-2 py-0.5 rounded-md border border-white/10">
                    {React.createElement(getFactionDetails(character.faction).icon, { 
                        size: 10, 
                        className: getFactionDetails(character.faction).color 
                    })}
                    <span className="text-[10px] font-bold text-white uppercase tracking-wider">{character.faction}</span>
                </div>
            </div>
        </div>

        {/* Skin Render Area */}
        <div className="relative h-80 xl:h-96 w-full bg-gradient-to-b from-gray-100 to-white dark:from-[#1a1a1a] dark:to-[#121212] flex items-end justify-center overflow-hidden">
            <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
            
            {/* Skin Image or Photo */}
            {character.photoUrl || getCharacterPhotoUrl(character.name) ? (
                <img 
                    src={getCharacterPhotoUrl(character.name, character.photoUrl)} 
                    alt={character.name}
                    className="h-full w-full object-cover transform group-hover:scale-105 transition-transform duration-700 ease-out"
                />
            ) : (
                <div className="h-full w-full flex flex-col items-center justify-center bg-gray-200 dark:bg-[#1a1a1a] text-gray-400 dark:text-gray-500">
                    <User size={48} className="mb-2 opacity-50" />
                    <span className="text-[10px] font-bold uppercase tracking-widest opacity-50">No Image</span>
                </div>
            )}
            
            {/* Gradient Overlay for Text Readability */}
            <div className="absolute bottom-0 left-0 w-full h-24 bg-gradient-to-t from-white via-white/80 to-transparent dark:from-[#121212] dark:via-[#121212]/80 dark:to-transparent"></div>
        </div>

        {/* Metrics Grid */}
        <div className="px-5 pb-5 flex-1 flex flex-col relative z-10">
            <div className="grid grid-cols-3 gap-3 mb-6">
                <MetricItem icon={Trophy} label="Level" value={character.level} color="text-amber-500" />
                <MetricItem icon={Wallet} label="Cash" value={`$${(character.money || 0).toLocaleString()}`} color="text-green-500" />
                <MetricItem icon={Landmark} label="Bank" value={`$${(character.bank || 0).toLocaleString()}`} color="text-blue-500" />
                
                <MetricItem icon={Phone} label="Phone" value={character.phoneNumber || "-"} color="text-purple-500" />
                <MetricItem icon={Hourglass} label="Hours" value={`${character.playingHours || 0}h`} color="text-cyan-500" />
                <MetricItem icon={AlertTriangle} label="Warns" value={`${character.warns || 0}/20`} color="text-red-500" />
            </div>

            {/* Action Buttons */}
            <div className="mt-auto flex gap-3">
                <button 
                    onClick={() => onSelect(character)}
                    className="flex-1 bg-gray-900 dark:bg-white text-white dark:text-black font-black py-3 rounded-xl uppercase text-xs tracking-[0.2em] hover:bg-red-600 dark:hover:bg-red-500 hover:text-white dark:hover:text-white transition-all shadow-lg hover:shadow-red-500/30 transform active:scale-95"
                >
                    Character Detail
                </button>
                <button 
                    onClick={() => onDelete(character.id)}
                    className="w-12 flex items-center justify-center rounded-xl bg-gray-100 dark:bg-white/5 text-gray-400 hover:text-red-500 hover:bg-red-50 dark:hover:bg-red-900/20 transition-all border border-transparent hover:border-red-200 dark:hover:border-red-900/30 group/trash"
                    title="Delete Character"
                >
                    <Trash2 className="w-5 h-5 group-hover/trash:rotate-12 transition-transform" />
                </button>
            </div>
        </div>
    </div>
  );
};

const MetricItem = ({ icon: Icon, label, value, color }: any) => (
    <div className="flex flex-col items-center p-2 rounded-xl bg-gray-50 dark:bg-white/5 border border-gray-100 dark:border-white/5 hover:border-gray-200 dark:hover:border-white/10 transition-colors">
        <div className={`p-1.5 rounded-lg bg-white dark:bg-black/20 mb-1 ${color}`}>
            <Icon size={12} />
        </div>
        <span className="text-[9px] font-bold text-gray-400 uppercase tracking-wider mb-0.5">{label}</span>
        <span className="text-xs font-black text-gray-900 dark:text-white truncate w-full text-center">{value}</span>
    </div>
);
