
import React, { useState } from 'react';
import { Character, CharacterStory } from '../types';
import { PageHeader } from './ui/PageHeader';
import { CharacterSelector } from './story/CharacterSelector';
import { StoryEditor } from './story/StoryEditor';
import { StoryView } from './story/StoryView';
import { BookOpen } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../config';

interface CharacterStoryProps {
  characters: Character[];
  userStories: CharacterStory[];
  onSubmitStory: (charId: number, content: string) => void;
  username: string;
  onNavigate?: (tabId: string) => void;
}

export const CharacterStoryPage: React.FC<CharacterStoryProps> = ({ characters, userStories, onSubmitStory, username, onNavigate }) => {
  const [selectedCharId, setSelectedCharId] = useState<number>(characters[0]?.id || 0);
  const [storyContent, setStoryContent] = useState('');
  const [isSubmitting, setIsSubmitting] = useState(false);
  
  const currentStory = userStories.find(s => s.characterId === selectedCharId);
  const selectedChar = characters.find(c => c.id === selectedCharId);

  // Sync content when character changes
  React.useEffect(() => {
    if (currentStory && (currentStory.status === 'Revision' || currentStory.status === 'Pending' || currentStory.status === 'Rejected')) {
        setStoryContent(currentStory.content);
    } else {
        setStoryContent('');
    }
  }, [currentStory, selectedCharId]);

  const handleSubmit = async () => {
    setIsSubmitting(true);
    
    if (!isPreviewEnv()) {
        try {
            const formData = new FormData();
            formData.append('username', username);
            formData.append('char_id', selectedCharId.toString());
            formData.append('story_text', storyContent);
            // formData.append('photo', file); // Optional: Jika ada file upload

            const response = await fetch(`${API_URL}/api_stories_upload.php`, {
                method: 'POST',
                body: formData
            });

            const data = await response.json();
            
            if (data && data.status === 'success') {
                onSubmitStory(selectedCharId, storyContent);
            } else {
                alert(data?.message || 'Gagal mengirim cerita.');
            }
        } catch (error) {
            console.error('Error submitting story:', error);
            alert('Terjadi kesalahan koneksi saat mengirim cerita.');
        } finally {
            setIsSubmitting(false);
        }
    } else {
        // Simulasi loading
        setTimeout(() => {
            onSubmitStory(selectedCharId, storyContent);
            setIsSubmitting(false);
        }, 1500);
    }
  };

  return (
    <div className="max-w-[1600px] mx-auto animate-[fadeIn_0.5s_ease-out] space-y-4 md:space-y-8">
      <PageHeader 
        title="Character Story" 
        icon={BookOpen}
        description="Ceritakan perjalanan hidup karakter Anda secara mendalam."
      />

      {/* UX UPDATE: 12-Col Grid for Desktop. Sidebar takes 3, Content takes 9 */}
      <div className="grid grid-cols-1 lg:grid-cols-12 gap-4 md:gap-8 lg:gap-10 items-start">
         
         {/* Sidebar Wrapper - Sticky on Desktop */}
         <div className="lg:col-span-3 lg:sticky lg:top-8 z-10 -mx-4 px-4 lg:mx-0 lg:px-0">
            <CharacterSelector 
                characters={characters}
                userStories={userStories}
                selectedCharId={selectedCharId}
                onSelect={setSelectedCharId}
            />
         </div>

         {/* Main Content Area */}
         <div className="lg:col-span-9 min-w-0">
            {(!currentStory || currentStory.status === 'Revision' || currentStory.status === 'Rejected') ? (
                <StoryEditor 
                    storyContent={storyContent}
                    setStoryContent={setStoryContent}
                    currentStory={currentStory}
                    selectedChar={selectedChar}
                    onSubmit={handleSubmit}
                    isSubmitting={isSubmitting}
                    onNavigate={onNavigate}
                />
            ) : (
                selectedChar && <StoryView character={selectedChar} story={currentStory} />
            )}
         </div>
      </div>
    </div>
  );
};
