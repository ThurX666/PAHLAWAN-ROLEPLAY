
import React, { useState } from 'react';
import { Character } from '../types';
import { PageHeader } from './ui/PageHeader';
import { CharacterCard } from './characters/CharacterCard';
import { CreateCharacterCard } from './characters/CreateCharacterCard';
import { CreateCharacterModal } from './characters/CreateCharacterModal';
import { Users } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../config';

interface CharacterListProps {
  userName: string;
  characters: Character[];
  setCharacters: React.Dispatch<React.SetStateAction<Character[]>>;
  onSelectCharacter: (character: Character) => void;
  onCharacterCreated?: (name: string, formData: any) => void;
  isDiscordLinked?: boolean;
  onRequireSync?: () => void;
}

export const CharacterList: React.FC<CharacterListProps> = ({ userName, characters, setCharacters, onSelectCharacter, onCharacterCreated, isDiscordLinked, onRequireSync }) => {
  const [isCreating, setIsCreating] = useState(false);
  const [deletingId, setDeletingId] = useState<number | null>(null);
  const maxSlots = 3;
  const currentSlots = characters.length;

  const handleOpenCreateModal = () => {
    if (isDiscordLinked === false) {
      if (onRequireSync) onRequireSync();
      return;
    }
    setIsCreating(true);
  };

  const handleCreate = async (formData: any) => {
    if (characters.length >= 3) return;

    if (!isPreviewEnv()) {
        try {
            const res = await fetch(`${API_URL}/api_characters.php`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    action: 'create',
                    username: userName,
                    name: formData.name,
                    gender: formData.gender,
                    age: formData.age,
                    height: formData.height,
                    weight: formData.weight,
                    origin: formData.origin
                })
            });
            const data = await res.json();
            if (data && data.status === 'success') {
                const newChar: Character = {
                  id: data.id,
                  name: formData.name,
                  level: 1,
                  money: 250,
                  bank: 500,
                  faction: "Warga Sipil",
                  jobName: "Unemployed",
                  lastLogin: "Baru Dibuat",
                  status: "Offline", 
                  skinId: data.skinId || 2, // Use returned skinId or default
                  needsHunger: 100,
                  needsThirsty: 100,
                  needsMood: 100,
                  storyStatus: 'None',
                  logs: []
                };
                setCharacters([...characters, newChar]);
                if (onCharacterCreated) onCharacterCreated(formData.name, formData);
            } else {
                alert(data?.message || 'Gagal membuat karakter.');
            }
        } catch (e) {
            console.error('Create error:', e);
            alert('Terjadi kesalahan koneksi.');
        }
    } else {
        const newChar: Character = {
          id: Date.now(),
          name: formData.name,
          level: 1,
          money: 250,
          bank: 500,
          faction: "Warga Sipil",
          jobName: "Unemployed",
          lastLogin: "Baru Dibuat",
          status: "Offline", 
          skinId: 0,
          needsHunger: 100,
          needsThirsty: 100,
          needsMood: 100,
          storyStatus: 'None',
          logs: []
        };
        
        setCharacters([...characters, newChar]);
        if (onCharacterCreated) onCharacterCreated(formData.name, formData);
    }
    setIsCreating(false);
  };

  const handleDelete = (id: number) => {
    setDeletingId(id);
  };

  const confirmDelete = async () => {
    if (deletingId !== null) {
      if (!isPreviewEnv()) {
          try {
              const res = await fetch(`${API_URL}/api_characters.php`, {
                  method: 'POST',
                  headers: { 'Content-Type': 'application/json' },
                  body: JSON.stringify({
                      action: 'delete',
                      id: deletingId
                  })
              });
              const data = await res.json();
              if (data && data.status === 'success') {
                  setCharacters(characters.filter(c => c.id !== deletingId));
              } else {
                  alert(data?.message || 'Gagal menghapus karakter.');
              }
          } catch (e) {
              console.error('Delete error:', e);
              alert('Terjadi kesalahan koneksi saat menghapus.');
          }
      } else {
          setCharacters(characters.filter(c => c.id !== deletingId));
      }
      setDeletingId(null);
    }
  };

  const SlotCounter = () => (
    <div className="flex items-center gap-4 bg-white dark:bg-[#121212] p-4 rounded-2xl border border-gray-200 dark:border-white/10 shadow-sm w-full md:w-auto">
      <div className="flex-1 md:flex-none">
          <p className="text-[10px] font-black text-gray-400 uppercase tracking-widest mb-1">Slot Terpakai</p>
          <div className="flex items-end gap-1">
              <span className="text-2xl font-black text-gray-900 dark:text-white leading-none">{currentSlots}</span>
              <span className="text-sm font-bold text-gray-400 mb-0.5">/ {maxSlots}</span>
          </div>
      </div>
      
      <div className="flex gap-1.5">
         {Array.from({ length: maxSlots }, (_, i) => {
             const isFilled = i < currentSlots;
             return (
                 <div 
                    key={i} 
                    className={`w-3 h-10 rounded-full transition-all duration-500 ${
                        isFilled 
                        ? 'bg-gradient-to-t from-red-600 to-red-400 shadow-lg shadow-red-500/30' 
                        : 'bg-gray-100 dark:bg-white/5 border border-gray-200 dark:border-white/5'
                    }`}
                 ></div>
             );
         })}
      </div>
    </div>
  );

  return (
    <div className="w-full animate-[fadeIn_0.5s_ease-out]">
      <PageHeader 
        title="Karakter Saya" 
        icon={Users}
        description="Kelola identitas Roleplay Anda. Pantau statistik, aset, dan perkembangan karakter secara mendetail, atau buat karakter baru untuk memulai perjalanan baru."
        action={<SlotCounter />}
      />

      {/* UX UPDATE: Grid Layout for Desktop/Tablet instead of vertical list */}
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6 items-stretch mt-6 md:mt-8">
        {characters.map((char) => (
            <div key={char.id} className="h-full">
                <CharacterCard 
                    character={char} 
                    onSelect={onSelectCharacter} 
                    onDelete={handleDelete} 
                />
            </div>
        ))}

        {characters.length < 3 && (
            <div className="h-full min-h-[450px]">
                <CreateCharacterCard onClick={handleOpenCreateModal} />
            </div>
        )}
      </div>

      {/* CREATE CHARACTER MODAL */}
      {isCreating && (
          <CreateCharacterModal 
            onClose={() => setIsCreating(false)} 
            onCreate={handleCreate} 
          />
      )}

      {/* DELETE CONFIRMATION MODAL */}
      {deletingId !== null && (
        <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/60 backdrop-blur-sm animate-in fade-in duration-200">
            <div className="bg-white dark:bg-[#1a1a1a] w-full max-w-md overflow-hidden shadow-2xl border border-gray-200 dark:border-white/10 flex flex-col rounded-t-3xl md:rounded-2xl animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                {/* Mobile Drag Handle */}
                <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>
                
                <div className="p-6 text-center">
                    <div className="w-16 h-16 bg-red-100 dark:bg-red-500/20 text-red-600 dark:text-red-500 rounded-full flex items-center justify-center mx-auto mb-4">
                        <Users size={32} />
                    </div>
                    <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tight mb-2">Hapus Karakter?</h3>
                    <p className="text-sm text-gray-500 dark:text-gray-400 mb-6">Tindakan ini tidak dapat dibatalkan. Karakter beserta semua asetnya akan dihapus secara permanen.</p>
                    
                    <div className="flex gap-3">
                        <button 
                            onClick={() => setDeletingId(null)}
                            className="flex-1 py-3 rounded-xl font-bold text-gray-700 dark:text-gray-300 bg-gray-100 dark:bg-white/5 hover:bg-gray-200 dark:hover:bg-white/10 transition-colors"
                        >
                            Batal
                        </button>
                        <button 
                            onClick={confirmDelete}
                            className="flex-1 py-3 rounded-xl font-bold text-white bg-red-600 hover:bg-red-700 shadow-lg shadow-red-600/20 transition-all active:scale-95"
                        >
                            Hapus
                        </button>
                    </div>
                </div>
            </div>
        </div>
      )}
    </div>
  );
};
