
import React, { useState, useEffect } from 'react';
import { Sparkles, ToggleRight, ToggleLeft, Loader2 } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../../config';

interface PromoConfig {
    isActive: boolean;
    title: string;
    message: string;
}

interface PromoConfigCardProps {
    tempPromo: PromoConfig;
    setTempPromo: (config: PromoConfig) => void;
    onSave: (newConfig?: PromoConfig) => void;
}

export const PromoConfigCard: React.FC<PromoConfigCardProps> = ({ tempPromo, setTempPromo, onSave }) => {
  const [isLoading, setIsLoading] = useState(false);
  const [isFetching, setIsFetching] = useState(true);

  useEffect(() => {
      const fetchPromo = async () => {
          try {
              if (isPreviewEnv()) {
                  // Jika tidak ada API URL (misal di preview), gunakan data mock/initial
                  setTimeout(() => setIsFetching(false), 500);
                  return;
              }
              
              const res = await fetch(`${API_URL}/api_admin_donations.php?action=get_promo`);
              if (res.ok) {
                  const text = await res.text();
                  try {
                      const data = JSON.parse(text);
                      if (data && data.title) {
                          setTempPromo({
                              isActive: data.is_active == 1,
                              title: data.title || '',
                              message: data.description || ''
                          });
                      }
                  } catch (e) {
                      console.warn("Response bukan JSON yang valid (mungkin backend belum siap).");
                  }
              }
          } catch (error) {
              console.error("Gagal memuat konfigurasi promo:", error);
          } finally {
              setIsFetching(false);
          }
      };
      fetchPromo();
  }, [setTempPromo]);

  const handleToggle = async () => {
      const newConfig = { ...tempPromo, isActive: !tempPromo.isActive };
      
      setIsLoading(true);
      try {
          if (isPreviewEnv()) {
              // Simulasi jika backend tidak ada
              setTimeout(() => {
                  setTempPromo(newConfig);
                  onSave(newConfig);
                  setIsLoading(false);
              }, 500);
              return;
          }

          const res = await fetch(`${API_URL}/api_admin_donations.php`, {
              method: 'PUT',
              headers: {
                  'Content-Type': 'application/json',
              },
              body: JSON.stringify({
                  action: 'update_promo',
                  isActive: newConfig.isActive,
                  title: newConfig.title,
                  description: newConfig.message,
                  discountPercent: 20
              })
          });
          
          const text = await res.text();
          try {
              const result = JSON.parse(text);
              if (result.status === 'success') {
                  setTempPromo(newConfig);
                  onSave(newConfig);
              } else {
                  alert("Gagal memperbarui status promo: " + result.message);
              }
          } catch (e) {
              // Fallback jika response bukan JSON
              setTempPromo(newConfig);
              onSave(newConfig);
          }
      } catch (error) {
          console.error("Error updating promo:", error);
          // Fallback untuk preview
          setTempPromo(newConfig);
          onSave(newConfig);
      } finally {
          setIsLoading(false);
      }
  };

  const handleSaveClick = async () => {
      setIsLoading(true);
      try {
          if (isPreviewEnv()) {
              setTimeout(() => {
                  onSave(tempPromo);
                  setIsLoading(false);
              }, 500);
              return;
          }

          const res = await fetch(`${API_URL}/api_admin_donations.php`, {
              method: 'PUT',
              headers: {
                  'Content-Type': 'application/json',
              },
              body: JSON.stringify({
                  action: 'update_promo',
                  isActive: tempPromo.isActive,
                  title: tempPromo.title,
                  description: tempPromo.message,
                  discountPercent: 20
              })
          });
          
          const text = await res.text();
          try {
              const result = JSON.parse(text);
              if (result.status === 'success') {
                  onSave(tempPromo);
              } else {
                  alert("Gagal menyimpan banner promo: " + result.message);
              }
          } catch (e) {
              onSave(tempPromo);
          }
      } catch (error) {
          console.error("Error saving promo:", error);
          onSave(tempPromo);
      } finally {
          setIsLoading(false);
      }
  };

  if (isFetching) {
      return (
          <div className="bg-gradient-to-r from-gray-900 to-black p-4 rounded-xl border border-gray-800 flex justify-center items-center h-40">
              <Loader2 className="animate-spin text-yellow-400" size={24} />
          </div>
      );
  }

  return (
    <div className="bg-gradient-to-r from-gray-900 to-black p-4 rounded-xl border border-gray-800">
        <div className="flex items-center justify-between mb-4">
            <div className="flex items-center gap-2">
                <Sparkles className="text-yellow-400" size={20} />
                <h3 className="text-white font-bold uppercase italic text-sm">Pengaturan Promo Banner</h3>
            </div>
            <button 
                onClick={handleToggle}
                disabled={isLoading}
                className={`flex items-center gap-2 px-3 py-1.5 rounded-full text-xs font-bold uppercase transition-colors disabled:opacity-50 ${tempPromo.isActive ? 'bg-green-600 text-white' : 'bg-gray-700 text-gray-400'}`}
            >
                {isLoading ? <Loader2 className="animate-spin" size={16} /> : (tempPromo.isActive ? <ToggleRight size={16}/> : <ToggleLeft size={16} />)}
                {tempPromo.isActive ? 'Aktif' : 'Non-Aktif'}
            </button>
        </div>
        
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
            <div>
                <label className="text-[10px] text-gray-500 uppercase font-bold block mb-1">Judul Promo</label>
                <input 
                    value={tempPromo.title}
                    onChange={e => setTempPromo({...tempPromo, title: e.target.value})}
                    className="w-full bg-gray-800 border border-gray-700 rounded-lg px-3 py-2 text-xs text-white focus:border-yellow-400 outline-none" 
                />
            </div>
            <div>
                <label className="text-[10px] text-gray-500 uppercase font-bold block mb-1">Pesan Promo</label>
                <input 
                    value={tempPromo.message}
                    onChange={e => setTempPromo({...tempPromo, message: e.target.value})}
                    className="w-full bg-gray-800 border border-gray-700 rounded-lg px-3 py-2 text-xs text-white focus:border-yellow-400 outline-none" 
                />
            </div>
        </div>
        <div className="mt-4 flex justify-end">
            <button 
                onClick={handleSaveClick} 
                disabled={isLoading}
                className="bg-yellow-500 hover:bg-yellow-400 text-black font-bold px-4 py-2 rounded-lg text-xs uppercase disabled:opacity-50 flex items-center gap-2"
            >
                {isLoading && <Loader2 className="animate-spin" size={14} />}
                Simpan Banner
            </button>
        </div>
    </div>
  );
};
