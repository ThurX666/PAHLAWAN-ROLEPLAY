
import React from 'react';
import { Character, CharacterStory } from '../../types';
import { User, CheckCircle2, Clock, AlertCircle } from 'lucide-react';

interface CharacterSelectorProps {
  characters: Character[];
  userStories: CharacterStory[];
  selectedCharId: number;
  onSelect: (id: number) => void;
}

export const CharacterSelector: React.FC<CharacterSelectorProps> = ({ characters, userStories, selectedCharId, onSelect }) => {
  return (
    <div className="flex lg:flex-col overflow-x-auto lg:overflow-visible gap-3 pb-4 lg:pb-0 scrollbar-hide snap-x snap-mandatory">
       {characters.map(char => {
           const story = userStories.find(s => s.characterId === char.id);
           const status = story ? story.status : 'NONE';
           const isActive = selectedCharId === char.id;
           
           const StatusIcon = status === 'Active' ? CheckCircle2 : status === 'Pending' ? Clock : status === 'Revision' ? AlertCircle : User;
           const statusColor = status === 'Active' ? 'text-green-500' : status === 'Pending' ? 'text-yellow-500' : status === 'Revision' ? 'text-amber-500' : 'text-gray-400';
           
           return (
               <button
                   key={char.id}
                   onClick={() => onSelect(char.id)}
                   className={`
                       snap-center relative overflow-hidden transition-all duration-300 group w-[260px] lg:w-full text-left
                       p-4 rounded-2xl flex items-center gap-4 shrink-0 border
                       ${isActive 
                       ? 'bg-red-600 text-white border-red-600 shadow-lg shadow-red-600/20 ring-4 ring-red-600/10' 
                       : 'bg-white dark:bg-[#1a1a1a] border-gray-200 dark:border-white/5 text-gray-500 dark:text-gray-400 hover:bg-gray-50 dark:hover:bg-white/5 hover:text-gray-900 dark:hover:text-white'}
                   `}
               >
                   <div className={`w-12 h-12 rounded-xl flex items-center justify-center shrink-0 transition-colors ${isActive ? 'bg-white/20 text-white' : 'bg-gray-100 dark:bg-white/5 text-gray-500 dark:text-gray-400 group-hover:text-gray-900 dark:group-hover:text-white'}`}>
                        <StatusIcon size={24} className={isActive ? 'text-white' : statusColor} />
                   </div>

                   <div className="flex-1 min-w-0">
                        <p className={`text-sm font-black uppercase tracking-wide truncate ${isActive ? 'text-white' : 'text-gray-900 dark:text-white'}`}>
                            {char.name.replace('_', ' ')}
                        </p>
                        <div className="flex items-center gap-1.5 mt-1">
                            <span className={`w-1.5 h-1.5 rounded-full ${status === 'Active' ? 'bg-green-500' : status === 'Pending' ? 'bg-yellow-500' : status === 'Revision' ? 'bg-amber-500' : 'bg-gray-400'}`}></span>
                            <p className={`text-[10px] font-bold uppercase tracking-wider ${isActive ? 'text-white/80' : 'text-gray-500'}`}>
                                {status}
                            </p>
                        </div>
                   </div>
               </button>
           )
       })}
    </div>
  );
};
