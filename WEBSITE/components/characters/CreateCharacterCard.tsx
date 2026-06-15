
import React from 'react';
import { Plus } from 'lucide-react';

interface CreateCharacterCardProps {
  onClick: () => void;
}

export const CreateCharacterCard: React.FC<CreateCharacterCardProps> = ({ onClick }) => {
  return (
    <button 
        onClick={onClick}
        className="w-full h-full min-h-[200px] border-2 border-dashed border-gray-300 dark:border-white/10 rounded-xl md:rounded-[1.5rem] flex flex-col items-center justify-center hover:bg-gray-50 dark:hover:bg-white/5 transition-all group hover:border-red-500/30 hover:shadow-2xl relative overflow-hidden"
    >
        <div className="absolute inset-0 bg-red-500/0 group-hover:bg-red-500/5 transition-colors duration-500"></div>
        <div className="w-16 h-16 md:w-24 md:h-24 rounded-full bg-gray-100 dark:bg-white/5 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform duration-500 group-hover:bg-red-500 group-hover:text-white shadow-xl relative z-10">
            <Plus className="w-8 h-8 md:w-12 md:h-12 text-gray-400 group-hover:text-white transition-colors" />
        </div>
        <span className="text-xs md:text-sm font-black text-gray-400 uppercase tracking-[0.2em] group-hover:text-red-500 transition-colors relative z-10">Create New Character</span>
    </button>
  );
};
