
import React, { useState } from 'react';
import { X, Save, Coins, Crown, Car, Home, Building, Package, MapPin, Palette, Search } from 'lucide-react';

interface TopUpProcessorProps {
    isOpen: boolean;
    onClose: () => void;
    targetPlayer: string;
    transactionId?: string;
    onComplete?: (code: string) => void;
}

const PROPERTY_TYPES = {
    Residential: ["House", "Flat", "Gubuk", "Trailer"],
    Commercial: ["Private Farm", "Workshop", "Restaurant", "GYM", "Furniture Shop", "Clothes Shop", "Gas Station", "Sportshop"],
    Other: ["Gudang Pribadi", "Garasi Pribadi"]
};

// --- DATA CONSTANTS ---

const SAMP_COLORS_HEX = [
    "#000000", "#F5F5F5", "#2A77A1", "#840410", "#263739", "#86446E", "#D78E10", "#4C75B7", "#BDBEC6", "#5E7072",
    "#46597A", "#656A79", "#5D7E8D", "#58595A", "#D6DAD6", "#9CA1A3", "#335F3F", "#730E1A", "#7B0A2A", "#9F9D94",
    "#3B4E78", "#732E3E", "#691E3B", "#96918C", "#515459", "#3F3E45", "#A5A9A7", "#635C5A", "#3D4A68", "#979592",
    "#421F21", "#5F272B", "#8494AB", "#767B7C", "#646464", "#5A5752", "#252527", "#2D3A35", "#93A396", "#6D7A88",
    "#221918", "#6F675F", "#7C1C2A", "#5F0A15", "#193826", "#5D1B20", "#9D9872", "#7A7560", "#989586", "#ADB0B0",
    "#848988", "#304F45", "#4D6268", "#162248", "#272F4B", "#7D6256", "#9EA4AB", "#9C8D71", "#6D1822", "#4E6881",
    "#9C9C98", "#917347", "#661C26", "#949D9F", "#A4A7A5", "#8E8C46", "#341A1E", "#6A7A8C", "#AAAD8E", "#AB988F",
    "#851F2E", "#6F8297", "#585853", "#9AA790", "#601A23", "#20202C", "#A4A096", "#AA9D84", "#78222B", "#0E316D",
    "#722A3F", "#7B715E", "#741D28", "#1E2E32", "#4D322F", "#7C1B44", "#2E5B20", "#395A83", "#6D2837", "#A7A28F",
    "#AFB1B1", "#364155", "#6D6C6E", "#0F6A89", "#204B6B", "#2B3E57", "#9B9F9D", "#6C8495", "#4D8495", "#AE9B7F",
    "#406C8F", "#1F253B", "#AB9276", "#134573", "#96816C", "#64686A", "#105082", "#A19983", "#385694", "#525661",
    "#7F6956", "#8C929A", "#596E87", "#473532", "#44624F", "#730A27", "#223457", "#640D1B", "#A3ADC6", "#695853",
    "#9B8B80", "#620B1C", "#5B5D5E", "#624428", "#731827", "#1B376D", "#EC6AAE", "#000000",
    // Extended 0.3x colors
    "#177517", "#210606", "#125478", "#452A0D", "#571E1E", "#010701", "#25225A", "#2C89AA", "#8A4DBD", "#35963A",
    "#B7B7B7", "#464C8D", "#84888C", "#817867", "#817A26", "#6A506F", "#583E6F", "#8CB972", "#824F78", "#6D276A",
    "#1E1D13", "#1E1306", "#1F2518", "#2C4531", "#1E4C99", "#2E5F43", "#1E9948", "#1E9999", "#999976", "#7C8499",
    "#992E1E", "#2C1E08", "#142407", "#993E4D", "#1E4C99", "#198181", "#1A292A", "#16616F", "#1B6687", "#6C3F99",
    "#481A0E", "#7A7399", "#746D99", "#53387E", "#222407", "#3E190C", "#46210E", "#991E1E", "#8D4C8D", "#805B80",
    "#7B3E7E", "#3C1737", "#733517", "#781818", "#83341A", "#8E2F1C", "#7E3E53", "#7C6D7C", "#020C02", "#072407",
    "#163012", "#16301B", "#642B4F", "#368452", "#999590", "#818D96", "#99991E", "#7F994C", "#839292", "#788222",
    "#2B3C99", "#3A3A0B", "#8A794E", "#0E1F49", "#15371C", "#15273A", "#375775", "#060820", "#071326", "#20394B",
    "#2C5089", "#15426C", "#103250", "#241663", "#692015", "#8C8D94", "#516013", "#090F02", "#8C573A", "#52888E",
    "#995C52", "#99581E", "#993A63", "#998F4E", "#99311E", "#0D1842", "#521E1E", "#42420D", "#4C991E", "#082A1D",
    "#96821D", "#197F19", "#3B141F", "#745217", "#893F8D", "#7E1A6C", "#0B370B", "#27450D", "#071F24", "#784573",
    "#8A653A", "#732617", "#319490", "#56941D", "#59163D", "#1B8A2F", "#38160B", "#041804", "#355D8E", "#2E3F5B",
    "#561A28", "#4E0E27", "#706C67", "#3B3E42", "#2E2D33", "#7B7E7D", "#4A4442", "#28344E"
];

const SAMP_VEHICLES = [
    {id: 411, name: "Infernus"}, {id: 560, name: "Sultan"}, {id: 562, name: "Elegy"}, {id: 415, name: "Cheetah"},
    {id: 451, name: "Turismo"}, {id: 541, name: "Bullet"}, {id: 429, name: "Banshee"}, {id: 477, name: "ZR-350"},
    {id: 494, name: "Hotring Racer"}, {id: 502, name: "Hotring Racer 2"}, {id: 503, name: "Hotring Racer 3"},
    {id: 522, name: "NRG-500"}, {id: 461, name: "PCJ-600"}, {id: 521, name: "FCR-900"}, {id: 463, name: "Freeway"},
    {id: 481, name: "BMX"}, {id: 509, name: "Bike"}, {id: 510, name: "Mountain Bike"},
    {id: 400, name: "Landstalker"}, {id: 401, name: "Bravura"}, {id: 402, name: "Buffalo"}, {id: 404, name: "Perennial"},
    {id: 405, name: "Sentinel"}, {id: 409, name: "Stretch (Limo)"}, {id: 410, name: "Manana"}, {id: 412, name: "Voodoo"},
    {id: 419, name: "Esperanto"}, {id: 420, name: "Taxi"}, {id: 421, name: "Washington"}, {id: 426, name: "Premier"},
    {id: 490, name: "FBI Rancher"}, {id: 528, name: "FBI Truck"}, {id: 596, name: "Police LS"}, {id: 597, name: "Police SF"},
    {id: 598, name: "Police LV"}, {id: 427, name: "Enforcer"}, {id: 432, name: "Rhino (Tank)"}, {id: 520, name: "Hydra"},
    {id: 425, name: "Hunter"}, {id: 487, name: "Maverick"}, {id: 488, name: "News Chopper"}, {id: 497, name: "Police Maverick"}
].sort((a,b) => a.name.localeCompare(b.name));

const SPAWN_LOCATIONS = [
    "Unity Station (Los Santos)",
    "Los Santos Airport",
    "Pershing Square (LSPD)",
    "All Saints General Hospital",
    "Santa Maria Beach",
    "Ganton (Grove Street)",
    "Market Station",
    "Vinewood Sign",
    "San Fierro Airport",
    "Las Venturas Airport",
    "Palomino Creek",
    "Montgomery",
    "Angel Pine"
];

export const TopUpProcessor: React.FC<TopUpProcessorProps> = ({ isOpen, onClose, targetPlayer, transactionId, onComplete }) => {
    const [activeTab, setActiveTab] = useState<'currency' | 'vehicle' | 'property'>('currency');
    const [loading, setLoading] = useState(false);

    // Form States
    const [goldAmount, setGoldAmount] = useState<string>('');
    const [vipLevel, setVipLevel] = useState('None');
    const [vipDuration, setVipDuration] = useState('30');
    
    // Vehicle State
    const [vehIdSearch, setVehIdSearch] = useState('');
    const [selectedVehId, setSelectedVehId] = useState<number>(411);
    const [vehColorId1, setVehColorId1] = useState<number>(1);
    const [vehColorId2, setVehColorId2] = useState<number>(0);
    const [spawnLocation, setSpawnLocation] = useState(SPAWN_LOCATIONS[0]);

    // Property State
    const [propCategory, setPropCategory] = useState<keyof typeof PROPERTY_TYPES>('Residential');
    const [propType, setPropType] = useState(PROPERTY_TYPES.Residential[0]);
    const [propLocation, setPropLocation] = useState('');
    const [propInterior, setPropInterior] = useState('');

    if (!isOpen) return null;

    const generateVoucherCode = () => {
        // Generate a 16-char code (e.g., A1B2-C3D4-E5F6-G7H8)
        const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
        let code = '';
        for (let i = 0; i < 16; i++) {
            code += chars.charAt(Math.floor(Math.random() * chars.length));
        }
        return code.match(/.{1,4}/g)?.join('-') || code;
    };

    const handleProcess = (e: React.FormEvent) => {
        e.preventDefault();
        setLoading(true);
        
        setTimeout(() => {
            setLoading(false);
            const voucherCode = generateVoucherCode();
            alert(`Sukses! Kode Redeem: ${voucherCode}\n(Otomatis dikirim ke Inbox Player)`);
            if(onComplete) {
                onComplete(voucherCode);
            } else {
                onClose();
            }
        }, 2000);
    };

    const filteredVehicles = SAMP_VEHICLES.filter(v => 
        v.name.toLowerCase().includes(vehIdSearch.toLowerCase()) || 
        v.id.toString().includes(vehIdSearch)
    );

    const getColorHex = (id: number) => {
        if(id < 0 || id >= SAMP_COLORS_HEX.length) return '#000000';
        return SAMP_COLORS_HEX[id];
    };

    return (
        <div className="fixed inset-0 z-[60] flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
            <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 w-full max-w-3xl rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col overflow-hidden max-h-[95dvh] animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                
                {/* Mobile Drag Handle */}
                <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden shrink-0"></div>

                {/* Header */}
                <div className="flex justify-between items-center p-4 border-b border-gray-200 dark:border-white/5 bg-gray-50 dark:bg-[#151515]">
                    <div>
                        <h3 className="text-sm md:text-lg font-black text-gray-900 dark:text-white uppercase italic flex items-center gap-2">
                           <Package size={18} className="text-red-500"/> Proses Top Up
                        </h3>
                        <p className="text-[10px] text-gray-500 font-mono">
                            Target: <span className="font-bold text-red-500">{targetPlayer}</span> 
                            {transactionId && <span className="ml-2 opacity-50">| Ref: {transactionId}</span>}
                        </p>
                    </div>
                    <button onClick={onClose} className="text-gray-500 hover:text-red-500"><X size={20}/></button>
                </div>

                <div className="flex flex-col md:flex-row h-full overflow-hidden">
                    {/* Sidebar Tabs */}
                    <div className="w-full md:w-48 bg-gray-50 dark:bg-[#0f0f0f] border-b md:border-b-0 md:border-r border-gray-200 dark:border-white/5 p-2 flex md:flex-col gap-1 overflow-x-auto md:overflow-visible">
                        <button 
                            onClick={() => setActiveTab('currency')}
                            className={`flex items-center gap-2 px-4 py-3 rounded-lg text-xs font-bold uppercase transition-all whitespace-nowrap ${activeTab === 'currency' ? 'bg-red-600 text-white shadow-lg shadow-red-600/20' : 'text-gray-500 hover:bg-gray-200 dark:hover:bg-white/5'}`}
                        >
                            <Coins size={16} /> Gold & VIP
                        </button>
                        <button 
                            onClick={() => setActiveTab('vehicle')}
                            className={`flex items-center gap-2 px-4 py-3 rounded-lg text-xs font-bold uppercase transition-all whitespace-nowrap ${activeTab === 'vehicle' ? 'bg-red-600 text-white shadow-lg shadow-red-600/20' : 'text-gray-500 hover:bg-gray-200 dark:hover:bg-white/5'}`}
                        >
                            <Car size={16} /> Kendaraan
                        </button>
                        <button 
                            onClick={() => setActiveTab('property')}
                            className={`flex items-center gap-2 px-4 py-3 rounded-lg text-xs font-bold uppercase transition-all whitespace-nowrap ${activeTab === 'property' ? 'bg-red-600 text-white shadow-lg shadow-red-600/20' : 'text-gray-500 hover:bg-gray-200 dark:hover:bg-white/5'}`}
                        >
                            <Building size={16} /> Properti
                        </button>
                    </div>

                    {/* Content Area */}
                    <form onSubmit={handleProcess} className="flex-1 p-6 overflow-y-auto bg-white dark:bg-[#121212] flex flex-col">
                        
                        {/* TAB: CURRENCY & VIP */}
                        {activeTab === 'currency' && (
                            <div className="space-y-6 animate-[fadeIn_0.3s_ease-out]">
                                <div className="bg-yellow-50 dark:bg-yellow-900/10 border border-yellow-200 dark:border-yellow-900/30 p-4 rounded-xl">
                                    <h4 className="text-sm font-bold text-yellow-700 dark:text-yellow-500 uppercase mb-4 flex items-center gap-2">
                                        <Coins size={16}/> Edit Gold Coins
                                    </h4>
                                    <div className="grid grid-cols-2 gap-4">
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Jumlah Tambahan</label>
                                            <input 
                                                type="number" 
                                                placeholder="Contoh: 1000" 
                                                className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-sm font-bold outline-none focus:border-yellow-500"
                                                value={goldAmount}
                                                onChange={e => setGoldAmount(e.target.value)}
                                            />
                                        </div>
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Tipe Aksi</label>
                                            <select className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-sm outline-none">
                                                <option value="add">Tambah (Credit)</option>
                                                <option value="remove">Kurangi (Debit)</option>
                                                <option value="set">Set Fixed Value</option>
                                            </select>
                                        </div>
                                    </div>
                                </div>

                                <div className="bg-purple-50 dark:bg-purple-900/10 border border-purple-200 dark:border-purple-900/30 p-4 rounded-xl">
                                    <h4 className="text-sm font-bold text-purple-700 dark:text-purple-400 uppercase mb-4 flex items-center gap-2">
                                        <Crown size={16}/> Status VIP
                                    </h4>
                                    <div className="grid grid-cols-2 gap-4">
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Level VIP</label>
                                            <select 
                                                className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-sm outline-none font-bold"
                                                value={vipLevel}
                                                onChange={e => setVipLevel(e.target.value)}
                                            >
                                                <option value="None">Tidak Ada</option>
                                                <option value="Regular">Regular VIP</option>
                                                <option value="Gold">Gold VIP</option>
                                                <option value="Platinum">Platinum VIP</option>
                                            </select>
                                        </div>
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Durasi (Hari)</label>
                                            <input 
                                                type="number" 
                                                className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-sm font-bold outline-none focus:border-purple-500"
                                                value={vipDuration}
                                                onChange={e => setVipDuration(e.target.value)}
                                            />
                                        </div>
                                    </div>
                                </div>
                            </div>
                        )}

                        {/* TAB: VEHICLE */}
                        {activeTab === 'vehicle' && (
                            <div className="space-y-4 animate-[fadeIn_0.3s_ease-out]">
                                <div className="bg-blue-50 dark:bg-blue-900/10 border border-blue-200 dark:border-blue-900/30 p-4 rounded-xl">
                                     <h4 className="text-sm font-bold text-blue-700 dark:text-blue-400 uppercase mb-4 flex items-center gap-2">
                                        <Car size={16}/> Spawn Kendaraan Baru
                                    </h4>
                                    
                                    <div className="mb-4">
                                        <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Pilih Model (ID 400-611)</label>
                                        <div className="relative mb-2">
                                            <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={14} />
                                            <input 
                                                type="text" 
                                                placeholder="Cari ID atau Nama Model..." 
                                                className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg pl-9 p-2 text-xs outline-none focus:border-blue-500"
                                                value={vehIdSearch}
                                                onChange={e => setVehIdSearch(e.target.value)}
                                            />
                                        </div>
                                        <div className="grid grid-cols-2 md:grid-cols-4 gap-2 max-h-[150px] overflow-y-auto custom-scrollbar p-1 bg-white dark:bg-black/10 rounded border border-gray-200 dark:border-white/5">
                                            {filteredVehicles.length > 0 ? filteredVehicles.map(veh => (
                                                <button 
                                                    key={veh.id}
                                                    type="button"
                                                    onClick={() => setSelectedVehId(veh.id)}
                                                    className={`px-3 py-2 rounded text-xs font-bold uppercase border transition-all text-left flex justify-between ${selectedVehId === veh.id ? 'bg-blue-600 text-white border-blue-600' : 'bg-white dark:bg-black/20 border-gray-200 dark:border-white/5 hover:border-blue-400'}`}
                                                >
                                                    <span>{veh.name}</span>
                                                    <span className="opacity-70 font-mono">{veh.id}</span>
                                                </button>
                                            )) : (
                                                <div className="col-span-4 text-center py-4 text-gray-500 text-xs italic">Kendaraan tidak ditemukan</div>
                                            )}
                                        </div>
                                    </div>

                                    <div className="grid grid-cols-2 gap-4 mb-4">
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block flex items-center gap-1"><Palette size={10}/> Warna 1 (ID 0-255)</label>
                                            <div className="flex gap-2 items-center">
                                                <div 
                                                    className="w-10 h-10 rounded-lg border border-gray-300 dark:border-white/20 shadow-sm"
                                                    style={{ backgroundColor: getColorHex(vehColorId1) }}
                                                    title={`Preview Color ID ${vehColorId1}`}
                                                ></div>
                                                <input 
                                                    type="number" 
                                                    min="0"
                                                    max="255"
                                                    value={vehColorId1} 
                                                    onChange={e => setVehColorId1(parseInt(e.target.value))} 
                                                    className="flex-1 bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-2.5 text-xs font-mono font-bold" 
                                                />
                                            </div>
                                        </div>
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block flex items-center gap-1"><Palette size={10}/> Warna 2 (ID 0-255)</label>
                                            <div className="flex gap-2 items-center">
                                                 <div 
                                                    className="w-10 h-10 rounded-lg border border-gray-300 dark:border-white/20 shadow-sm"
                                                    style={{ backgroundColor: getColorHex(vehColorId2) }}
                                                    title={`Preview Color ID ${vehColorId2}`}
                                                ></div>
                                                <input 
                                                    type="number" 
                                                    min="0"
                                                    max="255"
                                                    value={vehColorId2} 
                                                    onChange={e => setVehColorId2(parseInt(e.target.value))} 
                                                    className="flex-1 bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-2.5 text-xs font-mono font-bold" 
                                                />
                                            </div>
                                        </div>
                                    </div>

                                    <div>
                                        <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block flex items-center gap-1"><MapPin size={10}/> Lokasi Spawn</label>
                                        <select 
                                            className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-xs outline-none focus:border-blue-500 font-bold"
                                            value={spawnLocation}
                                            onChange={e => setSpawnLocation(e.target.value)}
                                        >
                                            {SPAWN_LOCATIONS.map((loc, idx) => (
                                                <option key={idx} value={loc}>{loc}</option>
                                            ))}
                                        </select>
                                    </div>
                                </div>
                            </div>
                        )}

                        {/* TAB: PROPERTY */}
                        {activeTab === 'property' && (
                            <div className="space-y-4 animate-[fadeIn_0.3s_ease-out]">
                                <div className="bg-green-50 dark:bg-green-900/10 border border-green-200 dark:border-green-900/30 p-4 rounded-xl">
                                    <h4 className="text-sm font-bold text-green-700 dark:text-green-400 uppercase mb-4 flex items-center gap-2">
                                        <Home size={16}/> Setup Properti Baru
                                    </h4>

                                    <div className="mb-4">
                                        <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Kategori Properti</label>
                                        <div className="flex gap-2">
                                            {(Object.keys(PROPERTY_TYPES) as Array<keyof typeof PROPERTY_TYPES>).map(cat => (
                                                <button
                                                    key={cat}
                                                    type="button"
                                                    onClick={() => { setPropCategory(cat); setPropType(PROPERTY_TYPES[cat][0]); }}
                                                    className={`flex-1 py-2 rounded-lg text-xs font-bold uppercase border transition-all ${propCategory === cat ? 'bg-green-600 text-white border-green-600' : 'bg-white dark:bg-black/20 border-gray-200 dark:border-white/10 text-gray-500'}`}
                                                >
                                                    {cat}
                                                </button>
                                            ))}
                                        </div>
                                    </div>

                                    <div className="mb-4">
                                        <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Tipe Spesifik</label>
                                        <select 
                                            className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-sm outline-none"
                                            value={propType}
                                            onChange={e => setPropType(e.target.value)}
                                        >
                                            {PROPERTY_TYPES[propCategory].map(type => (
                                                <option key={type} value={type}>{type}</option>
                                            ))}
                                        </select>
                                    </div>

                                    <div className="grid grid-cols-2 gap-4">
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Deskripsi Lokasi</label>
                                            <input 
                                                type="text" 
                                                placeholder="Contoh: Mulholland Dr." 
                                                className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-xs outline-none focus:border-green-500"
                                                value={propLocation}
                                                onChange={e => setPropLocation(e.target.value)}
                                            />
                                        </div>
                                        <div>
                                            <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 block">Interior ID (Int)</label>
                                            <input 
                                                type="number" 
                                                placeholder="0" 
                                                className="w-full bg-white dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-lg p-3 text-xs outline-none focus:border-green-500"
                                                value={propInterior}
                                                onChange={e => setPropInterior(e.target.value)}
                                            />
                                        </div>
                                    </div>
                                </div>
                            </div>
                        )}

                        <div className="mt-auto pt-6">
                            <button 
                                type="submit"
                                disabled={loading}
                                className="w-full bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 text-white font-bold py-3.5 rounded-xl uppercase tracking-widest text-xs shadow-lg flex items-center justify-center gap-2 transition-all active:scale-[0.98]"
                            >
                                {loading ? <span className="animate-spin">⌛</span> : <Save size={16} />}
                                {loading ? 'Memproses Database...' : 'Konfirmasi & Kirim Voucher'}
                            </button>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    );
};
