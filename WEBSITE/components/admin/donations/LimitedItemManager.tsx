
import React, { useState, useRef, useEffect } from 'react';
import { Tag, Plus, ToggleRight, ToggleLeft, Trash2, X, Upload, Loader2 } from 'lucide-react';
import { PromoItem } from '../../../types';
import { isPreviewEnv, API_URL, UPLOAD_BASE_URL } from '../../../config';

interface LimitedItemManagerProps {
    promoItems: PromoItem[];
    onUpdatePromoItems?: React.Dispatch<React.SetStateAction<PromoItem[]>>;
}

export const LimitedItemManager: React.FC<LimitedItemManagerProps> = ({ promoItems, onUpdatePromoItems }) => {
    const [isAddingItem, setIsAddingItem] = useState(false);
    const [isLoading, setIsLoading] = useState(false);
    const [isFetching, setIsFetching] = useState(true);
    const [newItem, setNewItem] = useState<Partial<PromoItem>>({
        type: 'Vehicle',
        isLimited: true,
        isActive: true,
        stats: [{ label: 'Speed', value: '200km/h' }],
        qty: 10 // Default QTY
    });
    const fileInputRef = useRef<HTMLInputElement>(null);

    useEffect(() => {
        const fetchItems = async () => {
            try {
                if (isPreviewEnv()) {
                    setTimeout(() => setIsFetching(false), 500);
                    return;
                }
                const res = await fetch(`${API_URL}/api_admin_donations.php?action=get_items&admin_view=1`);
                if (res.ok) {
                    const text = await res.text();
                    try {
                        const data = JSON.parse(text);
                        if (Array.isArray(data) && onUpdatePromoItems) {
                            const formattedItems: PromoItem[] = data.map((item: any) => ({
                                id: item.id.toString(),
                                name: item.name,
                                type: item.type,
                                priceGold: parseInt(item.price_gold),
                                image: item.image_path ? (UPLOAD_BASE_URL ? `${UPLOAD_BASE_URL.endsWith('/') ? UPLOAD_BASE_URL : UPLOAD_BASE_URL + '/'}uploads/items/${item.image_path}` : `uploads/items/${item.image_path}`) : "https://placehold.co/600x400/111/FFF?text=No+Image",
                                description: item.description,
                                stats: [], // Bisa disesuaikan jika ada di DB
                                isLimited: true,
                                isActive: item.is_active == 1,
                                qty: parseInt(item.qty)
                            }));
                            onUpdatePromoItems(formattedItems);
                        }
                    } catch (e) {
                        console.warn("Response bukan JSON yang valid (mungkin backend belum siap).");
                    }
                }
            } catch (error) {
                console.error("Gagal memuat daftar item:", error);
            } finally {
                setIsFetching(false);
            }
        };
        fetchItems();
    }, [onUpdatePromoItems]);

    const handleAddItem = async () => {
        if(!onUpdatePromoItems || !newItem.name || !newItem.priceGold) return;
        
        setIsLoading(true);
        try {
            if (isPreviewEnv()) {
                setTimeout(() => {
                    const item: PromoItem = {
                        id: Date.now().toString(),
                        name: newItem.name as string,
                        type: newItem.type as any,
                        priceGold: Number(newItem.priceGold),
                        image: newItem.image || "https://placehold.co/600x400/111/FFF?text=No+Image",
                        description: newItem.description || "Deskripsi item...",
                        stats: newItem.stats || [],
                        isLimited: newItem.isLimited || false,
                        isActive: true,
                        qty: newItem.qty || 0
                    };
                    onUpdatePromoItems(prev => [...prev, item]);
                    setIsAddingItem(false);
                    setNewItem({ type: 'Vehicle', isLimited: true, isActive: true, stats: [{ label: 'Speed', value: '200km/h' }], qty: 10 });
                    setIsLoading(false);
                }, 500);
                return;
            }

            const formData = new FormData();
            formData.append('action', 'add_item');
            formData.append('name', newItem.name);
            formData.append('type', newItem.type as string);
            formData.append('priceGold', newItem.priceGold.toString());
            formData.append('description', newItem.description || "Deskripsi item...");
            formData.append('qty', (newItem.qty || 0).toString());
            
            if (fileInputRef.current?.files?.[0]) {
                formData.append('image', fileInputRef.current.files[0]);
            }

            const res = await fetch(`${API_URL}/api_admin_donations.php`, {
                method: 'POST',
                body: formData
            });
            
            const text = await res.text();
            try {
                const result = JSON.parse(text);
                if (result.status === 'success') {
                    // Refresh list
                    const refreshRes = await fetch(`${API_URL}/api_admin_donations.php?action=get_items&admin_view=1`);
                    if (refreshRes.ok) {
                        const refreshText = await refreshRes.text();
                        try {
                            const data = JSON.parse(refreshText);
                            const formattedItems: PromoItem[] = data.map((item: any) => ({
                                id: item.id.toString(),
                                name: item.name,
                                type: item.type,
                                priceGold: parseInt(item.price_gold),
                                image: item.image_path ? (UPLOAD_BASE_URL ? `${UPLOAD_BASE_URL.endsWith('/') ? UPLOAD_BASE_URL : UPLOAD_BASE_URL + '/'}uploads/items/${item.image_path}` : `uploads/items/${item.image_path}`) : "https://placehold.co/600x400/111/FFF?text=No+Image",
                                description: item.description,
                                stats: [],
                                isLimited: true,
                                isActive: item.is_active == 1,
                                qty: parseInt(item.qty)
                            }));
                            onUpdatePromoItems(formattedItems);
                        } catch(e) {}
                    }
                    setIsAddingItem(false);
                    setNewItem({ type: 'Vehicle', isLimited: true, isActive: true, stats: [{ label: 'Speed', value: '200km/h' }], qty: 10 });
                } else {
                    alert("Gagal menambahkan item: " + result.message);
                }
            } catch (e) {
                // Fallback
                const item: PromoItem = {
                    id: Date.now().toString(),
                    name: newItem.name as string,
                    type: newItem.type as any,
                    priceGold: Number(newItem.priceGold),
                    image: newItem.image || "https://placehold.co/600x400/111/FFF?text=No+Image",
                    description: newItem.description || "Deskripsi item...",
                    stats: newItem.stats || [],
                    isLimited: newItem.isLimited || false,
                    isActive: true,
                    qty: newItem.qty || 0
                };
                onUpdatePromoItems(prev => [...prev, item]);
                setIsAddingItem(false);
                setNewItem({ type: 'Vehicle', isLimited: true, isActive: true, stats: [{ label: 'Speed', value: '200km/h' }], qty: 10 });
            }
        } catch (error) {
            console.error("Error adding item:", error);
            // Fallback
            const item: PromoItem = {
                id: Date.now().toString(),
                name: newItem.name as string,
                type: newItem.type as any,
                priceGold: Number(newItem.priceGold),
                image: newItem.image || "https://placehold.co/600x400/111/FFF?text=No+Image",
                description: newItem.description || "Deskripsi item...",
                stats: newItem.stats || [],
                isLimited: newItem.isLimited || false,
                isActive: true,
                qty: newItem.qty || 0
            };
            onUpdatePromoItems(prev => [...prev, item]);
            setIsAddingItem(false);
            setNewItem({ type: 'Vehicle', isLimited: true, isActive: true, stats: [{ label: 'Speed', value: '200km/h' }], qty: 10 });
        } finally {
            setIsLoading(false);
        }
    };

    const handleDeleteItem = (id: string) => {
        if(!onUpdatePromoItems) return;
        if(confirm("Hapus item promo ini? (Di backend sebaiknya menggunakan soft delete atau set is_active = 0)")) {
            // Untuk sementara hapus dari state saja, atau panggil API delete jika ada
            onUpdatePromoItems(prev => prev.filter(i => i.id !== id));
        }
    };

    const toggleItemActive = async (id: string, currentStatus: boolean) => {
        if(!onUpdatePromoItems) return;
        
        // Optimistic update
        onUpdatePromoItems(prev => prev.map(i => i.id === id ? { ...i, isActive: !currentStatus } : i));
        
        try {
            if (isPreviewEnv()) return;

            const res = await fetch(`${API_URL}/api_admin_donations.php`, {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({
                    action: 'toggle_item',
                    item_id: id,
                    is_active: !currentStatus
                })
            });
            
            const text = await res.text();
            try {
                const result = JSON.parse(text);
                if (result.status !== 'success') {
                    // Revert on failure
                    onUpdatePromoItems(prev => prev.map(i => i.id === id ? { ...i, isActive: currentStatus } : i));
                    alert("Gagal mengubah status item: " + result.message);
                }
            } catch (e) {
                // Ignore if not JSON (e.g. preview environment)
            }
        } catch (error) {
            console.error("Error toggling item:", error);
            // Revert on failure
            onUpdatePromoItems(prev => prev.map(i => i.id === id ? { ...i, isActive: currentStatus } : i));
            alert("Terjadi kesalahan koneksi saat mengubah status item.");
        }
    };

    const handleImageUpload = (e: React.ChangeEvent<HTMLInputElement>) => {
        const file = e.target.files?.[0];
        if (file) {
            const imageUrl = URL.createObjectURL(file);
            setNewItem({ ...newItem, image: imageUrl });
        }
    };

  if (isFetching) {
      return (
          <div className="bg-white dark:bg-[#1a1a1a] p-4 rounded-xl border border-gray-200 dark:border-gray-800 flex justify-center items-center h-40">
              <Loader2 className="animate-spin text-purple-600 dark:text-purple-400" size={24} />
          </div>
      );
  }

  return (
    <div className="bg-white dark:bg-[#1a1a1a] p-4 rounded-xl border border-gray-200 dark:border-gray-800 transition-colors">
        <div className="flex items-center justify-between mb-4">
            <div className="flex items-center gap-2">
                <Tag className="text-purple-600 dark:text-purple-400" size={20} />
                <h3 className="text-gray-900 dark:text-white font-bold uppercase italic text-sm">Exclusive Shop</h3>
            </div>
            <button 
                onClick={() => setIsAddingItem(true)}
                className="bg-purple-600 hover:bg-purple-500 text-white px-3 py-1.5 rounded-lg text-xs font-bold uppercase flex items-center gap-1 transition-colors"
            >
                <Plus size={14} /> Tambah Item
            </button>
        </div>

        {isAddingItem && (
            <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center bg-black/50 backdrop-blur-sm p-0 md:p-4">
                <div className="bg-white dark:bg-[#111] w-full max-w-md rounded-t-3xl md:rounded-xl border border-gray-200 dark:border-purple-900/50 shadow-2xl overflow-hidden flex flex-col max-h-[95dvh] animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                    <div className="flex justify-center pt-3 pb-1 md:hidden">
                        <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full"></div>
                    </div>
                    <div className="flex justify-between items-center p-4 border-b border-gray-200 dark:border-gray-800">
                        <h3 className="text-gray-900 dark:text-white font-bold uppercase text-sm">Tambah Item Exclusive</h3>
                        <button onClick={() => setIsAddingItem(false)} className="text-gray-500 hover:text-gray-700 dark:text-gray-400 dark:hover:text-white transition-colors">
                            <X size={20} />
                        </button>
                    </div>
                    
                    <div className="p-4 overflow-y-auto space-y-4">
                        <div className="space-y-3">
                            <div>
                                <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Nama Item</label>
                                <input placeholder="Contoh: Infernus Neon" className="w-full bg-gray-50 dark:bg-[#222] text-gray-900 dark:text-white text-xs p-2.5 rounded-lg border border-gray-200 dark:border-gray-700 focus:border-purple-500 focus:ring-1 focus:ring-purple-500 outline-none transition-all" value={newItem.name || ''} onChange={e => setNewItem({...newItem, name: e.target.value})} />
                            </div>
                            
                            <div className="grid grid-cols-2 gap-3">
                                <div>
                                    <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Tipe</label>
                                    <select className="w-full bg-gray-50 dark:bg-[#222] text-gray-900 dark:text-white text-xs p-2.5 rounded-lg border border-gray-200 dark:border-gray-700 focus:border-purple-500 outline-none" value={newItem.type} onChange={e => setNewItem({...newItem, type: e.target.value as any})}>
                                        <option value="Vehicle">Vehicle</option>
                                        <option value="Property">Property</option>
                                        <option value="Item">Item</option>
                                    </select>
                                </div>
                                <div>
                                    <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Harga Gold</label>
                                    <input placeholder="0" type="number" className="w-full bg-gray-50 dark:bg-[#222] text-gray-900 dark:text-white text-xs p-2.5 rounded-lg border border-gray-200 dark:border-gray-700 focus:border-purple-500 outline-none" value={newItem.priceGold || ''} onChange={e => setNewItem({...newItem, priceGold: parseInt(e.target.value)})} />
                                </div>
                            </div>

                            <div>
                                <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Stok (QTY)</label>
                                <input placeholder="0" type="number" className="w-full bg-purple-50 dark:bg-[#222] text-gray-900 dark:text-white text-xs p-2.5 rounded-lg border border-purple-200 dark:border-purple-500/50 focus:border-purple-500 outline-none" value={newItem.qty || ''} onChange={e => setNewItem({...newItem, qty: parseInt(e.target.value)})} />
                            </div>

                            <div>
                                <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Upload Gambar</label>
                                <div 
                                    className="w-full border-2 border-dashed border-gray-300 dark:border-gray-700 rounded-lg p-4 flex flex-col items-center justify-center cursor-pointer hover:border-purple-500 dark:hover:border-purple-500 transition-colors bg-gray-50 dark:bg-[#222]"
                                    onClick={() => fileInputRef.current?.click()}
                                >
                                    {newItem.image && newItem.image.startsWith('blob:') ? (
                                        <div className="relative w-full h-32 rounded overflow-hidden">
                                            <img src={newItem.image} alt="Preview" className="w-full h-full object-cover" />
                                            <div className="absolute inset-0 bg-black/50 flex items-center justify-center opacity-0 hover:opacity-100 transition-opacity">
                                                <span className="text-white text-xs font-bold">Ganti Gambar</span>
                                            </div>
                                        </div>
                                    ) : (
                                        <>
                                            <Upload className="text-gray-400 mb-2" size={24} />
                                            <span className="text-xs text-gray-500 dark:text-gray-400 font-medium">Klik untuk upload gambar</span>
                                        </>
                                    )}
                                    <input 
                                        type="file" 
                                        ref={fileInputRef} 
                                        className="hidden" 
                                        accept="image/*"
                                        onChange={handleImageUpload}
                                    />
                                </div>
                            </div>

                            <div>
                                <label className="block text-[10px] font-bold text-gray-500 uppercase mb-1">Deskripsi</label>
                                <textarea placeholder="Deskripsi item..." rows={3} className="w-full bg-gray-50 dark:bg-[#222] text-gray-900 dark:text-white text-xs p-2.5 rounded-lg border border-gray-200 dark:border-gray-700 focus:border-purple-500 outline-none resize-none" value={newItem.description || ''} onChange={e => setNewItem({...newItem, description: e.target.value})}></textarea>
                            </div>
                        </div>
                    </div>
                    
                    <div className="p-4 border-t border-gray-200 dark:border-gray-800 bg-gray-50 dark:bg-[#1a1a1a]">
                        <button 
                            onClick={handleAddItem} 
                            disabled={isLoading}
                            className="w-full bg-green-600 hover:bg-green-500 text-white text-xs font-bold py-3 rounded-lg transition-colors uppercase tracking-wider disabled:opacity-50 flex justify-center items-center gap-2"
                        >
                            {isLoading && <Loader2 className="animate-spin" size={16} />}
                            Simpan Item
                        </button>
                    </div>
                </div>
            </div>
        )}

        <div className="grid grid-cols-1 md:grid-cols-2 gap-3">
            {promoItems.map(item => (
                <div key={item.id} className="flex items-center justify-between bg-gray-50 dark:bg-[#222] p-3 rounded-lg border border-gray-200 dark:border-gray-700 transition-colors">
                    <div className="flex items-center gap-3">
                        <img src={item.image} className="w-10 h-10 object-cover rounded shadow-sm" />
                        <div>
                            <p className="text-xs font-bold text-gray-900 dark:text-white">{item.name}</p>
                            <div className="flex gap-2 text-[9px]">
                                <span className="text-yellow-600 dark:text-yellow-400 font-bold">{item.priceGold} GC</span>
                                <span className={`font-bold ${item.qty && item.qty > 0 ? 'text-green-600 dark:text-green-400' : 'text-red-600 dark:text-red-500'}`}>
                                    Stok: {item.qty || 0}
                                </span>
                            </div>
                        </div>
                    </div>
                    <div className="flex items-center gap-2">
                        <button onClick={() => toggleItemActive(item.id, item.isActive)} className={`p-1.5 rounded transition-colors ${item.isActive ? 'bg-green-100 dark:bg-green-600/20 text-green-600 dark:text-green-400' : 'bg-gray-200 dark:bg-gray-700 text-gray-500 dark:text-gray-400'}`}>
                            {item.isActive ? <ToggleRight size={16}/> : <ToggleLeft size={16} />}
                        </button>
                        <button onClick={() => handleDeleteItem(item.id)} className="p-1.5 bg-red-100 dark:bg-red-600/20 text-red-600 dark:text-red-400 rounded hover:bg-red-600 hover:text-white dark:hover:bg-red-600 dark:hover:text-white transition-colors">
                            <Trash2 size={16} />
                        </button>
                    </div>
                </div>
            ))}
        </div>
    </div>
  );
};
