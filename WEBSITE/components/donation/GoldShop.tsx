import React, { useState } from 'react';
import { ShoppingBag, Car, Wrench, User, ArrowRight, Store, Search, Coins, Map } from 'lucide-react';
import { Character } from '../../types';
import { RedeemModal } from './RedeemModal';
import { CustomMappingModal } from './CustomMappingModal';

interface ShopItem {
    id: number;
    name: string;
    price: number;
    category: 'layanan' | 'vehicle' | 'skin' | 'mapping';
    image?: string;
    description: string;
}

interface GoldShopProps {
    userGold: number;
    characters: Character[];
    onRedeem: (characterId: number, item: ShopItem) => Promise<boolean>;
}

const PERMANENT_ITEMS: ShopItem[] = [
    { id: 12, name: "Custom Mapping", price: 0, category: 'mapping', description: "Pesan custom mapping untuk Property atau FnG Hood. Harga menyesuaikan tier." },
    { id: 1, name: "Ganti Nama (CN)", price: 500, category: 'layanan', description: "Ganti nama karakter baru & hapus catatan kriminal." },
    { id: 2, name: "Ganti Nomor HP", price: 200, category: 'layanan', description: "Mendapatkan nomor HP 4-6 digit acak baru." },
    { id: 3, name: "Hapus Warning", price: 1000, category: 'layanan', description: "Menghapus 1 Poin Warning dari akun Anda." },
    { id: 4, name: "Custom Plate", price: 300, category: 'layanan', description: "Ubah teks plat nomor kendaraan pribadi." },
    { id: 5, name: "Skin Eksklusif #299", price: 350, category: 'skin', description: "Buka akses skin langka Malvada untuk karakter." },
    { id: 6, name: "Bundle Skin Gang", price: 100, category: 'skin', description: "Akses 3 skin bertema gangster acak." },
    { id: 7, name: "Sultan (Polos)", price: 1500, category: 'vehicle', description: "Sedan 4 pintu, kecepatan tinggi & full modifikasi." },
    { id: 8, name: "NRG-500 (Polos)", price: 2000, category: 'vehicle', description: "Motor tercepat dengan akselerasi tinggi." },
    { id: 9, name: "Maverick", price: 4500, category: 'vehicle', description: "Helikopter sipil standar untuk mobilitas udara." },
    { id: 10, name: "Jetmax", price: 2500, category: 'vehicle', description: "Kapal cepat untuk aktivitas maritim." },
    { id: 11, name: "Bersihkan Record", price: 250, category: 'layanan', description: "Hapus semua catatan kriminal kepolisian." },
];

export const GoldShop: React.FC<GoldShopProps> = ({ userGold, characters, onRedeem }) => {
  const [activeTab, setActiveTab] = useState<'layanan' | 'vehicle' | 'skin' | 'mapping'>('layanan');
  const [searchQuery, setSearchQuery] = useState('');
  const [selectedItem, setSelectedItem] = useState<ShopItem | null>(null);
  const [isCustomMappingOpen, setIsCustomMappingOpen] = useState(false);
  const [isProcessing, setIsProcessing] = useState(false);
  
  const filteredItems = PERMANENT_ITEMS.filter(item => {
      const matchesTab = item.category === activeTab;
      const matchesSearch = item.name.toLowerCase().includes(searchQuery.toLowerCase());
      return matchesTab && matchesSearch;
  });

  const handleBuyClick = (item: ShopItem) => {
      if (item.id === 12) {
          setIsCustomMappingOpen(true);
      } else {
          setSelectedItem(item);
      }
  };

  const handleConfirmRedeem = async (characterId: number) => {
      if (!selectedItem) return;
      
      setIsProcessing(true);
      try {
          const success = await onRedeem(characterId, selectedItem);
          if (!success) return;
      } finally {
          setIsProcessing(false);
          setSelectedItem(null);
      }
  };

  const handleConfirmCustomMapping = async (characterId: number, targetName: string, tierName: string, price: number, scope: string, theme: string, notes: string) => {
      setIsProcessing(true);
      try {
          const success = await onRedeem(characterId, {
              id: 12,
              name: `Custom Mapping - ${tierName}`,
              price: price,
              category: 'mapping',
              description: `Target: ${targetName} | Area: ${scope} | Tema: ${theme}${notes ? ` | Catatan: ${notes}` : ''}`
          });
          if (!success) return;
      } finally {
          setIsProcessing(false);
          setIsCustomMappingOpen(false);
      }
  };

  return (
    <div className="space-y-4">
        {/* Header Section */}
        <div className="flex flex-col gap-4 mb-2">
            <div className="flex flex-col md:flex-row md:items-center justify-between gap-4">
                <div className="flex items-center gap-2 px-1">
                    <Store className="text-indigo-500" size={24} />
                    <div>
                        <h3 className="text-base md:text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-wide leading-none">Gold Shop</h3>
                        <p className="text-[10px] text-gray-500 font-bold uppercase tracking-wide mt-1">Tukarkan Gold Coin dengan Item Permanen</p>
                    </div>
                </div>

                {/* Player Balance Display */}
                <div className="bg-yellow-50 dark:bg-yellow-900/10 border border-yellow-200 dark:border-yellow-900/30 px-4 py-2 rounded-xl flex items-center gap-3 self-start md:self-auto">
                    <div className="text-right">
                        <p className="text-[9px] font-bold text-yellow-600 dark:text-yellow-500 uppercase tracking-wider">Saldo Anda</p>
                        <p className="text-lg font-black text-gray-900 dark:text-white leading-none">{userGold.toLocaleString()} <span className="text-xs text-yellow-500">GC</span></p>
                    </div>
                    <div className="p-2 bg-yellow-400 rounded-lg text-black shadow-sm">
                        <Coins size={18} />
                    </div>
                </div>
            </div>
            
            {/* Filter & Search Bar */}
            <div className="flex flex-col md:flex-row gap-2 mt-2">
                {/* Tabs */}
                <div className="flex bg-gray-100 dark:bg-black/40 p-1 rounded-xl border border-gray-200 dark:border-white/5 w-full md:w-auto overflow-x-auto">
                    {[
                        { id: 'layanan', label: 'Layanan', icon: Wrench },
                        { id: 'vehicle', label: 'Kendaraan', icon: Car },
                        { id: 'skin', label: 'Skin', icon: User },
                        { id: 'mapping', label: 'Mapping', icon: Map }
                    ].map((tab) => {
                        const Icon = tab.icon;
                        const isActive = activeTab === tab.id;
                        return (
                            <button 
                                key={tab.id}
                                onClick={() => setActiveTab(tab.id as any)}
                                className={`flex-1 md:flex-initial px-3 py-2 rounded-lg text-[10px] font-bold uppercase transition-all flex items-center justify-center gap-1.5 whitespace-nowrap ${isActive ? 'bg-white dark:bg-ph-surface-elevated text-indigo-600 dark:text-indigo-400 shadow-sm' : 'text-gray-400 hover:text-gray-600 dark:hover:text-gray-300'}`}
                            >
                                <Icon size={12}/> {tab.label}
                            </button>
                        )
                    })}
                </div>

                {/* Search */}
                <div className="relative flex-1">
                    <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={14} />
                    <input 
                        type="text" 
                        placeholder="Cari item shop..." 
                        className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/5 rounded-xl pl-9 pr-3 py-2 text-xs font-bold text-gray-700 dark:text-gray-200 focus:border-indigo-500 outline-none transition-all"
                        value={searchQuery}
                        onChange={(e) => setSearchQuery(e.target.value)}
                    />
                </div>
            </div>
        </div>

        {/* Catalog Grid */}
        <div className="grid grid-cols-2 md:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-3">
            {filteredItems.length > 0 ? filteredItems.map(item => (
                <div key={item.id} className="bg-white dark:bg-ph-surface-input border border-gray-200 dark:border-white/5 rounded-xl p-3 hover:border-indigo-500/30 hover:shadow-lg transition-all group flex flex-col h-full relative overflow-hidden">
                     {/* Decorative gradient blob */}
                    <div className="absolute -right-4 -top-4 w-16 h-16 bg-indigo-500/5 rounded-full blur-xl group-hover:bg-indigo-500/10 transition-colors"></div>

                    <div className="flex flex-col justify-between items-start mb-2 relative z-10 gap-2">
                        <div className="flex items-start gap-2">
                            <span className="p-1.5 bg-indigo-50 dark:bg-indigo-900/20 text-indigo-600 dark:text-indigo-400 rounded-lg group-hover:scale-110 transition-transform shrink-0 mt-0.5">
                                {item.category === 'layanan' ? <Wrench size={14}/> : item.category === 'vehicle' ? <Car size={14}/> : item.category === 'mapping' ? <Map size={14}/> : <User size={14}/>}
                            </span>
                            <span className="text-[10px] md:text-xs font-bold text-gray-900 dark:text-white uppercase leading-tight">{item.name}</span>
                        </div>
                        <span className="text-[9px] md:text-xs font-black text-indigo-600 dark:text-indigo-400 whitespace-nowrap bg-indigo-50 dark:bg-indigo-900/10 px-2 py-0.5 rounded border border-indigo-100 dark:border-indigo-900/20">
                            {item.price === 0 ? 'Bervariasi' : `${item.price} GC`}
                        </span>
                    </div>
                    
                    <p className="text-[9px] md:text-[10px] text-gray-500 mb-3 flex-1 leading-relaxed border-t border-gray-100 dark:border-white/5 pt-2 mt-1 relative z-10">
                        {item.description}
                    </p>
                    
                    <button 
                        onClick={() => handleBuyClick(item)}
                        disabled={item.price > 0 && userGold < item.price}
                        className={`relative z-10 w-full border font-bold py-2 rounded-lg text-[9px] md:text-[10px] uppercase transition-all flex items-center justify-center gap-1 group-hover:shadow-md ${
                            item.price === 0 || userGold >= item.price 
                            ? 'bg-gray-50 dark:bg-black/20 border-gray-200 dark:border-white/10 hover:bg-indigo-600 hover:border-indigo-600 hover:text-white dark:hover:bg-indigo-600 dark:hover:border-indigo-600 text-gray-600 dark:text-gray-400'
                            : 'bg-red-50 dark:bg-red-900/10 border-red-200 dark:border-red-900/30 text-red-400 cursor-not-allowed'
                        }`}
                    >
                        {item.price === 0 || userGold >= item.price ? (
                            <>Tukar <ArrowRight size={10} className="md:w-3 md:h-3 group-hover:translate-x-1 transition-transform opacity-0 group-hover:opacity-100 hidden md:block" /></>
                        ) : (
                            "Saldo Kurang"
                        )}
                    </button>
                </div>
            )) : (
                <div className="col-span-full py-8 text-center text-gray-400 bg-gray-50 dark:bg-ph-surface-input rounded-xl border border-dashed border-gray-200 dark:border-white/10">
                    <ShoppingBag size={32} className="mx-auto mb-2 opacity-50" />
                    <p className="text-xs font-bold uppercase">Item tidak ditemukan</p>
                </div>
            )}
        </div>

        {/* Redeem Modal */}
        {selectedItem && (
            <RedeemModal 
                item={selectedItem}
                characters={characters}
                onClose={() => setSelectedItem(null)}
                onConfirm={handleConfirmRedeem}
                isProcessing={isProcessing}
            />
        )}

        {/* Custom Mapping Modal */}
        {isCustomMappingOpen && (
            <CustomMappingModal
                characters={characters}
                userGold={userGold}
                onClose={() => setIsCustomMappingOpen(false)}
                onConfirm={handleConfirmCustomMapping}
                isProcessing={isProcessing}
            />
        )}
    </div>
  );
};
