
import React from 'react';
import { AlertTriangle, AlertCircle, Save, Loader2, Camera } from 'lucide-react';
import { CharacterStory, Character } from '../../types';
import { RichTextEditor } from './RichTextEditor';
import { getCharacterPhotoUrl } from '../../utils/imageUtils';

interface StoryEditorProps {
  storyContent: string;
  setStoryContent: (content: string) => void;
  currentStory: CharacterStory | undefined;
  selectedChar: Character | undefined;
  onSubmit: () => void;
  isSubmitting: boolean;
  onNavigate?: (tabId: string) => void;
}

export const StoryEditor: React.FC<StoryEditorProps> = ({ 
    storyContent, setStoryContent, currentStory, selectedChar, onSubmit, isSubmitting, onNavigate 
}) => {

  const MIN_WORDS = 300;
  const MIN_PARAGRAPHS = 3;

  // Smart Validator V2
  const validateStory = (text: string): { isValid: boolean; error?: string } => {
      // Logika Validasi Sederhana (Hanya saat Submit)
      const totalWords = text.trim().split(/\s+/).filter(w => w !== "").length;
      const totalParagraphs = text.trim().split(/\n+/).filter(p => p.trim() !== "").length;
      
      // 1. Cek Syarat Minimal
      if (totalWords < MIN_WORDS || totalParagraphs < MIN_PARAGRAPHS) {
          return { 
              isValid: false, 
              error: "Cerita Anda belum memenuhi syarat minimal 300 kata dan 3 paragraf." 
          };
      }
      
      // 2. Punctuation Spacing (Titik/Koma harus ada spasi)
      if (/[\.,][a-zA-Z]/.test(text)) return { isValid: false, error: "Harap berikan spasi setelah tanda titik (.) atau koma (,)" };
      
      // 3. Anti-Spam (Kata terlalu panjang > 25 karakter tanpa spasi)
      const words = text.trim().split(/\s+/);
      const hasLongWord = words.some(w => w.length > 25 && !w.includes('http'));
      if (hasLongWord) return { isValid: false, error: "Terdeteksi kata yang tidak wajar (terlalu panjang tanpa spasi)" };
      
      // 4. Anti-Spam (Repetitive Characters e.g. "aaaaaaa")
      if (/(.)\1{4,}/.test(text)) return { isValid: false, error: "Terdeteksi spam karakter berulang (misal: 'aaaaa')" };

      return { isValid: true };
  };

  const handleSubmit = (e: React.FormEvent) => {
      e.preventDefault();
      const validation = validateStory(storyContent);
      
      if (!validation.isValid) {
          alert(`Gagal: ${validation.error}`);
          return;
      }
      
      onSubmit();
  };

  if (!selectedChar?.photoUrl && (!selectedChar || !getCharacterPhotoUrl(selectedChar.name))) {
      return (
          <div className="bg-red-50 dark:bg-red-900/10 border border-red-200 dark:border-red-900/30 p-6 rounded-3xl flex flex-col items-center text-center gap-4">
              <div className="p-4 bg-red-100 dark:bg-red-500/20 text-red-600 dark:text-red-500 rounded-full">
                  <Camera size={32} />
              </div>
              <div>
                  <h3 className="text-xl font-black text-red-700 dark:text-red-500 uppercase tracking-tighter mb-2">Foto Karakter Diperlukan</h3>
                  <p className="text-sm text-red-600 dark:text-red-400 max-w-md mx-auto mb-4">
                      Anda harus mengunggah foto wajah karakter terlebih dahulu sebelum dapat membuat Character Story. 
                      Silakan ke menu <strong>Karakter Saya &gt; Character Detail</strong> untuk mengunggah foto.
                  </p>
                  {onNavigate && (
                      <button 
                          onClick={() => onNavigate('characters')}
                          className="bg-red-600 hover:bg-red-700 text-white font-bold py-2.5 px-6 rounded-xl uppercase tracking-wider text-sm transition-colors"
                      >
                          Unggah Foto Sekarang
                      </button>
                  )}
              </div>
          </div>
      );
  }

  return (
    <form onSubmit={handleSubmit} className="space-y-6 px-0 md:px-6 pb-12">
        {/* Revision Notice */}
        {currentStory && currentStory.status === 'Revision' && (
            <div className="bg-amber-50 dark:bg-amber-900/10 border border-amber-200 dark:border-amber-900/30 p-5 rounded-2xl flex items-start gap-4">
                <AlertTriangle className="text-amber-500 shrink-0 mt-0.5" size={24} />
                <div>
                    <h4 className="text-sm font-bold text-amber-700 dark:text-amber-500 uppercase tracking-wider">Catatan Revisi Admin</h4>
                    <p className="text-sm text-amber-800 dark:text-amber-200 mt-1.5 leading-relaxed">"{currentStory.adminFeedback}"</p>
                </div>
            </div>
        )}

        {/* Rejected Notice */}
        {currentStory && currentStory.status === 'Rejected' && (
            <div className="bg-red-50 dark:bg-red-900/10 border border-red-200 dark:border-red-900/30 p-5 rounded-2xl flex items-start gap-4">
                <AlertTriangle className="text-red-500 shrink-0 mt-0.5" size={24} />
                <div>
                    <h4 className="text-sm font-bold text-red-700 dark:text-red-500 uppercase tracking-wider">Cerita Sebelumnya Ditolak</h4>
                    <p className="text-sm text-red-800 dark:text-red-200 mt-1.5 leading-relaxed">"{currentStory.adminFeedback || 'Cerita tidak memenuhi syarat kelayakan.'}"</p>
                    <p className="text-xs text-red-600 dark:text-red-400 mt-2 font-bold">Silakan buat ulang cerita Anda dan kirim kembali.</p>
                </div>
            </div>
        )}

        <RichTextEditor 
            content={storyContent}
            setContent={setStoryContent}
        />

        {/* Submit Section */}
        <div className="flex flex-col gap-4 pt-4 border-t border-gray-200 dark:border-white/10">
            <div className="flex items-center gap-3 bg-gray-50 dark:bg-white/5 p-4 rounded-xl">
                <AlertCircle size={20} className="text-gray-400 shrink-0" />
                <span className="text-xs font-bold text-gray-500 dark:text-gray-400 leading-relaxed">
                    Pastikan cerita memenuhi syarat minimal 300 kata dan 3 paragraf sebelum mengirim.
                </span>
            </div>
            <button 
                type="submit"
                disabled={isSubmitting}
                className="w-full bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 disabled:opacity-50 disabled:cursor-not-allowed text-white py-4 rounded-xl font-bold uppercase text-sm tracking-widest transition-all shadow-lg flex items-center justify-center gap-3 active:scale-95"
            >
                {isSubmitting ? <Loader2 className="animate-spin" size={20} /> : <Save size={20} />}
                Kirim Cerita
            </button>
        </div>
    </form>
  );
};
