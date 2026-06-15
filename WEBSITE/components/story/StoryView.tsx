import React from 'react';
import { Character, CharacterStory } from '../../types';
import { Clock, User } from 'lucide-react';
import { getCharacterPhotoUrl } from '../../utils/imageUtils';

interface StoryViewProps {
  character: Character;
  story: CharacterStory;
}

export const StoryView: React.FC<StoryViewProps> = ({ character, story }) => {
  return (
    <div className="bg-white dark:bg-gradient-to-br dark:from-[#1a1a1a] dark:to-[#2a1a1a] border border-gray-200 dark:border-white/10 rounded-3xl overflow-hidden shadow-sm dark:shadow-2xl relative min-h-[500px]">
        {/* Background Glow */}
        <div className="absolute top-0 right-0 w-[500px] h-[500px] bg-purple-500/10 dark:bg-purple-900/20 blur-[120px] rounded-full pointer-events-none"></div>

        <div className="p-6 md:p-8 lg:p-12 relative z-10">
            {/* Header Section */}
            <div className="flex flex-col md:flex-row gap-6 md:gap-8 mb-8 md:mb-12 items-center md:items-start text-center md:text-left">
                {/* Avatar/Image */}
                <div className="w-32 h-32 md:w-40 md:h-40 bg-gray-100 dark:bg-[#121212] rounded-2xl border border-gray-200 dark:border-white/10 shadow-xl overflow-hidden shrink-0">
                    {character.photoUrl || getCharacterPhotoUrl(character.name) ? (
                        <img src={getCharacterPhotoUrl(character.name, character.photoUrl)} className="w-full h-full object-cover" alt="Character Photo" />
                    ) : (
                        <div className="w-full h-full flex flex-col items-center justify-center bg-gray-200 dark:bg-[#1a1a1a] text-gray-400 dark:text-gray-500">
                            <User size={32} className="mb-1 opacity-50" />
                            <span className="text-[10px] font-bold uppercase tracking-widest opacity-50 text-center leading-tight">No Image</span>
                        </div>
                    )}
                </div>

                {/* Info */}
                <div className="flex flex-col justify-center items-center md:items-start">
                    <h1 className="text-3xl md:text-5xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter mb-4">
                        {character.name.replace('_', ' ')}
                    </h1>
                    
                    <div className="flex flex-wrap justify-center md:justify-start items-center gap-3 md:gap-4">
                        <span className={`px-3 py-1 rounded-md text-[10px] font-bold uppercase tracking-wider ${
                            story.status === 'Active' ? 'bg-green-100 dark:bg-green-900/30 text-green-600 dark:text-green-400 border border-green-200 dark:border-green-900/50' : 
                            story.status === 'Pending' ? 'bg-yellow-100 dark:bg-yellow-900/30 text-yellow-600 dark:text-yellow-400 border border-yellow-200 dark:border-yellow-900/50' :
                            'bg-red-100 dark:bg-red-900/30 text-red-600 dark:text-red-400 border border-red-200 dark:border-red-900/50'
                        }`}>
                            {story.status}
                        </span>
                        
                        <span className="text-gray-500 text-xs font-medium flex items-center gap-1.5">
                            <Clock size={12} />
                            Updated: {story.lastUpdated}
                        </span>
                    </div>
                </div>
            </div>

            {/* Content Section */}
            <div className="prose dark:prose-invert prose-lg max-w-none">
                <div 
                    className="text-gray-600 dark:text-gray-300 font-serif leading-relaxed text-lg first-letter:text-6xl first-letter:font-bold first-letter:text-gray-900 dark:first-letter:text-white first-letter:mr-3 first-letter:float-left"
                    dangerouslySetInnerHTML={{ __html: story.content }}
                />
            </div>
        </div>
    </div>
  );
};
