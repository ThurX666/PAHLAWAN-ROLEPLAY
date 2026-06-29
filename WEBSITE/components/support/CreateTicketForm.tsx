
import React, { useState } from 'react';
import { XCircle, AlertCircle, ChevronLeft } from 'lucide-react';

interface CreateTicketFormProps {
  onClose: () => void;
  onSubmit: (subject: string, category: string, message: string) => void;
}

export const CreateTicketForm: React.FC<CreateTicketFormProps> = ({ onClose, onSubmit }) => {
  const [subject, setSubject] = useState('');
  const [category, setCategory] = useState('Masalah Donasi');
  const [message, setMessage] = useState('');
  const [errors, setErrors] = useState<Record<string, string>>({});

  const validate = () => {
      const newErrors: Record<string, string> = {};
      if(!subject.trim()) newErrors.subject = "Subjek wajib diisi";
      if(!message.trim()) newErrors.message = "Pesan wajib diisi";
      setErrors(newErrors);
      return Object.keys(newErrors).length === 0;
  };

  const handleSubmit = (e: React.FormEvent) => {
      e.preventDefault();
      if(validate()) {
          onSubmit(subject, category, message);
      }
  };

  const handleInputChange = (setter: React.Dispatch<React.SetStateAction<string>>, value: string, field: string) => {
      setter(value);
      if(errors[field]) {
          setErrors(prev => {
              const newErr = {...prev};
              delete newErr[field];
              return newErr;
          });
      }
  };

  return (
    <div className="flex flex-col h-full animate-[fadeIn_0.3s_ease-out] bg-white dark:bg-ph-surface-card">
        <div className="p-4 md:p-5 border-b border-gray-200 dark:border-white/5 flex items-center bg-gray-50 dark:bg-ph-surface-panel sticky top-0 z-10">
            <button onClick={onClose} className="md:hidden text-gray-500 hover:text-red-500 p-2 -ml-2 mr-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors active:scale-95">
                <ChevronLeft size={24} />
            </button>
            <h3 className="flex-1 text-base md:text-lg font-black text-gray-900 dark:text-white uppercase italic leading-tight">Buat Tiket Baru</h3>
            <button onClick={onClose} className="hidden md:block text-gray-500 hover:text-red-500 p-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors"><XCircle size={24}/></button>
        </div>
        <form onSubmit={handleSubmit} className="space-y-5 flex-1 p-4 md:p-6 overflow-y-auto custom-scrollbar" noValidate>
            <div>
                <label className="block text-xs font-bold text-gray-500 uppercase mb-2">Kategori</label>
                <select 
                    className="w-full bg-gray-50 dark:bg-ph-surface-deep border border-gray-200 dark:border-white/10 rounded-xl p-4 text-sm md:text-base text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors appearance-none"
                    value={category}
                    onChange={e => setCategory(e.target.value)}
                >
                    <option>Masalah Donasi</option>
                    <option>Lapor Bug UCP</option>
                    <option>Lainnya</option>
                </select>
            </div>
            <div>
                <div className="flex justify-between items-center mb-2">
                    <label className={`block text-xs font-bold uppercase transition-colors ${errors.subject ? 'text-red-500' : 'text-gray-500'}`}>Subjek</label>
                    {errors.subject && <span className="text-[10px] text-red-500 font-bold animate-pulse flex items-center gap-1"><AlertCircle size={12}/> {errors.subject}</span>}
                </div>
                <input 
                    type="text" 
                    className={`w-full bg-gray-50 dark:bg-ph-surface-deep border rounded-xl p-4 text-sm md:text-base text-gray-900 dark:text-white outline-none transition-all ${errors.subject ? 'border-red-500 focus:border-red-600 bg-red-50/10' : 'border-gray-200 dark:border-white/10 focus:border-red-500'}`}
                    placeholder="Judul Masalah"
                    value={subject}
                    onChange={e => handleInputChange(setSubject, e.target.value, 'subject')}
                />
            </div>
            <div className="flex-1 flex flex-col">
                <div className="flex justify-between items-center mb-2">
                    <label className={`block text-xs font-bold uppercase transition-colors ${errors.message ? 'text-red-500' : 'text-gray-500'}`}>Pesan</label>
                    {errors.message && <span className="text-[10px] text-red-500 font-bold animate-pulse flex items-center gap-1"><AlertCircle size={12}/> {errors.message}</span>}
                </div>
                <textarea 
                    rows={8}
                    className={`w-full flex-1 bg-gray-50 dark:bg-ph-surface-deep border rounded-xl p-4 text-sm md:text-base text-gray-900 dark:text-white resize-none outline-none transition-all ${errors.message ? 'border-red-500 focus:border-red-600 bg-red-50/10' : 'border-gray-200 dark:border-white/10 focus:border-red-500'}`}
                    placeholder="Jelaskan detail masalah Anda secara lengkap..."
                    value={message}
                    onChange={e => handleInputChange(setMessage, e.target.value, 'message')}
                ></textarea>
            </div>
            <div className="flex flex-col-reverse md:flex-row justify-end gap-3 pt-4 pb-[calc(16px+env(safe-area-inset-bottom))] md:pb-0">
                <button type="button" onClick={onClose} className="w-full md:w-auto px-6 py-4 md:py-3 font-bold uppercase text-gray-500 text-xs md:text-sm hover:text-gray-800 dark:hover:text-gray-200 transition-colors bg-gray-100 dark:bg-white/5 md:bg-transparent rounded-xl md:rounded-none">Batal</button>
                <button type="submit" className="w-full md:w-auto bg-red-600 hover:bg-red-500 text-white px-8 py-4 md:py-3 rounded-xl font-bold uppercase text-xs md:text-sm shadow-lg transition-all active:scale-95">Kirim Tiket</button>
            </div>
        </form>
    </div>
  );
};
