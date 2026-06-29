
import React, { Suspense, lazy, useRef, useState, useEffect } from 'react';
import { Character } from '../types';
import { PageHeader } from './ui/PageHeader';
import { saveCharacterPhoto, getCharacterPhotoUrl } from '../utils/imageUtils';
import { isPreviewEnv, API_URL } from '../config';
import { 
    ArrowLeft, Shield, Zap, Heart, Crosshair, DollarSign, CreditCard, 
    Briefcase, Car, Home, MapPin, Smartphone, AlertTriangle, Clock, 
    Trophy, User, Wallet, Landmark, Droplets, Utensils, FileCheck, FileX, Smile,
    Skull, Building2, Camera
} from 'lucide-react';

const ImageCropModal = lazy(() => import('./ui/ImageCropModal').then(module => ({ default: module.ImageCropModal })));

const CropperFallback: React.FC = () => (
  <div className="fixed inset-0 z-[70] flex items-center justify-center bg-black/80 backdrop-blur-sm p-4">
    <div className="bg-white dark:bg-ph-surface-panel rounded-2xl w-full max-w-md border border-gray-200 dark:border-white/10 p-8 text-center shadow-2xl">
      <div className="mx-auto mb-4 h-10 w-10 animate-spin rounded-full border-2 border-gray-300 border-t-gray-900 dark:border-white/20 dark:border-t-white" />
      <p className="text-[10px] font-bold uppercase tracking-[0.3em] text-gray-500 dark:text-gray-400">
        Memuat Cropper...
      </p>
    </div>
  </div>
);

interface CharacterDetailProps {
  character: Character;
  onBack: () => void;
  onUpdateCharacter: (updatedChar: Character) => void;
}

export const CharacterDetail: React.FC<CharacterDetailProps> = ({ character, onBack, onUpdateCharacter }) => {
  // Real Data State
  const [vehicles, setVehicles] = useState<any[]>([
      { name: 'Infernus', plate: 'B 1234 CD', location: 'Garage', icon: Car },
      { name: 'NRG-500', plate: 'D 5678 EF', location: 'Garage', icon: Car },
  ]);
  const [assets, setAssets] = useState<any>({
      residential: [
          { type: 'House', name: 'Mulholland Safehouse', location: 'Richman', icon: Home },
          { type: 'Apartment', name: 'Rodeo Luxury Apt', location: 'Rodeo', icon: Home },
      ],
      commercial: [
          { type: 'Business', name: 'Ammunition Store', location: 'Downtown', icon: Briefcase },
      ],
      other: []
  });

  useEffect(() => {
      if (!isPreviewEnv()) {
          fetch(`${API_URL}/api_character_detail.php?char_id=${character.id}`)
              .then(res => res.json())
              .then(data => {
                  if (data && !data.error) {
                      setVehicles(data.vehicles || []);
                      if (data.character) {
                          setLiveStats({
                              health: Number(data.character.health ?? 100),
                              armor: Number(data.character.armor ?? 0),
                              hunger: Number(data.character.hunger ?? 100),
                              thirst: Number(data.character.thirst ?? 100),
                              stress: Number(data.character.stress ?? 0),
                              paycheck: Number(data.character.paycheck ?? 0),
                          });
                      }
                      
                      const residential: any[] = [];
                      const commercial: any[] = [];
                      const other: any[] = [];
                      
                      if (data.properties) {
                          data.properties.forEach((prop: any) => {
                              const p = { ...prop, icon: prop.type === 'Commercial' ? Briefcase : Home };
                              if (prop.type === 'Residential') residential.push(p);
                              else if (prop.type === 'Commercial') commercial.push(p);
                              else other.push(p);
                          });
                      }
                      
                      setAssets({ residential, commercial, other });
                  }
              })
              .catch(err => console.error("Error fetching character details:", err));
      }
  }, [character.id]);

  const [liveStats, setLiveStats] = useState({
      health: character.health ?? 100,
      armor: character.armor ?? 0,
      hunger: character.needsHunger ?? 100,
      thirst: character.needsThirsty ?? 100,
      stress: character.needsMood ?? 0,
      paycheck: character.paycheck ?? 0,
  });

  const health = liveStats.health;
  const armor = liveStats.armor;
  
  // Real Data for HTM (Hunger, Thirsty, Mood)
  const hunger = liveStats.hunger;
  const thirsty = liveStats.thirst;
  const mood = Math.max(0, 100 - liveStats.stress);
  
  // Job Data
  const jobName = character.jobName || "Unemployed";

  // License Helper Functions
  const checkLicenseValid = (expDate?: string) => {
      if (!expDate) return { valid: false, text: '-' };
      const current = new Date();
      const exp = new Date(expDate);
      if (current > exp) return { valid: false, text: 'Expired' };
      return { 
          valid: true, 
          text: new Intl.DateTimeFormat('id-ID', { day: 'numeric', month: 'short', year: 'numeric' }).format(exp)
      };
  };

  const drvLic = checkLicenseValid(character.licenseDriveExp);
  const flyLic = checkLicenseValid(character.licenseFlyExp);
  const sailLic = checkLicenseValid(character.licenseBoatExp);
  const gunLic = checkLicenseValid(character.licenseGunExp);

  // Licenses Array
  const licenses = [
      { name: 'Driving', exp: drvLic.text, valid: drvLic.valid },
      { name: 'Flying', exp: flyLic.text, valid: flyLic.valid },
      { name: 'Sailing', exp: sailLic.text, valid: sailLic.valid },
      { name: 'Weapon', exp: gunLic.text, valid: gunLic.valid },
  ];
  
  const getFactionDetails = (faction: string) => {
      const lower = faction?.toLowerCase() || '';
      if (lower === 'warga sipil' || lower === 'none' || !lower) {
          return { icon: User, color: 'text-gray-500 dark:text-gray-400', bg: 'bg-gray-100 dark:bg-white/10', border: 'border-gray-200 dark:border-white/5' };
      }
      if (lower.includes('lspd') || lower.includes('lsmd') || lower.includes('gov') || lower.includes('police') || lower.includes('medical') || lower.includes('department')) {
          return { icon: Building2, color: 'text-blue-600 dark:text-blue-400', bg: 'bg-blue-500/10', border: 'border-blue-500/20' };
      }
      return { icon: Skull, color: 'text-red-600 dark:text-red-400', bg: 'bg-red-500/10', border: 'border-red-500/20' };
  };

  const factionDetails = getFactionDetails(character.faction);

  const fileInputRef = useRef<HTMLInputElement>(null);

  // Cropper State
  const [imageSrc, setImageSrc] = useState<string | null>(null);
  const [isCropping, setIsCropping] = useState(false);

  const handlePhotoUpload = (e: React.ChangeEvent<HTMLInputElement>) => {
      const file = e.target.files?.[0];
      if (file) {
          const reader = new FileReader();
          reader.addEventListener('load', () => {
              setImageSrc(reader.result?.toString() || null);
              setIsCropping(true);
          });
          reader.readAsDataURL(file);
      }
      // Reset input so the same file can be selected again if needed
      if (fileInputRef.current) {
          fileInputRef.current.value = '';
      }
  };

  const handleCropConfirm = async (croppedImage: string) => {
      try {
          const savedPath = await saveCharacterPhoto(character.name, croppedImage);
          onUpdateCharacter({ ...character, photoUrl: savedPath });
      } catch (e) {
          console.error(e);
      }
      setIsCropping(false);
      setImageSrc(null);
  };

  const handleCropCancel = () => {
      setIsCropping(false);
      setImageSrc(null);
  };

  return (
    <div className="w-full animate-[fadeIn_0.4s_ease-out]">
      {/* Cropper Modal */}
      {isCropping && imageSrc && (
          <Suspense fallback={<CropperFallback />}>
              <ImageCropModal
                  aspect={1}
                  imageSrc={imageSrc}
                  title="Sesuaikan Foto"
                  onCancel={handleCropCancel}
                  onConfirm={handleCropConfirm}
              />
          </Suspense>
      )}

      <PageHeader 
        title="Character Detail" 
        icon={User}
        description="Informasi lengkap mengenai status, aset, dan lisensi karakter Anda."
        action={
          <button 
            onClick={onBack}
            className="group flex items-center gap-2 px-4 py-2 rounded-full bg-white dark:bg-white/5 border border-gray-200 dark:border-white/10 hover:border-red-500/30 hover:bg-red-50 dark:hover:bg-red-900/20 transition-all"
          >
              <div className="p-1.5 rounded-full bg-gray-100 dark:bg-white/10 group-hover:bg-red-500 group-hover:text-white transition-colors">
                  <ArrowLeft size={16} />
              </div>
              <span className="text-sm font-bold text-gray-600 dark:text-gray-300 group-hover:text-red-600 dark:group-hover:text-red-400 uppercase tracking-wide">
                  Back to Characters
              </span>
          </button>
        }
      />

      <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 mb-6 items-stretch">
        {/* LEFT COLUMN: Profile (Span 4) */}
        <div className="col-span-1 lg:col-span-4">
            <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-3xl p-6 shadow-sm flex flex-col items-center text-center overflow-hidden relative h-full">
                
                {/* Background Pattern */}
                <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>

                {/* Skin/Photo Render - Flexible Height */}
                <div className="relative w-full flex-1 min-h-[250px] bg-gradient-to-b from-gray-100 to-white dark:from-ph-surface-panel dark:to-ph-surface-card rounded-2xl flex items-end justify-center mb-6 overflow-hidden border border-gray-100 dark:border-white/5 group">
                    <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
                    
                    {character.photoUrl || getCharacterPhotoUrl(character.name) ? (
                        <img 
                            src={getCharacterPhotoUrl(character.name, character.photoUrl)} 
                            alt="Character Photo"
                            className="absolute inset-0 w-full h-full object-cover transform hover:scale-105 transition-transform duration-700"
                        />
                    ) : (
                        <div className="absolute inset-0 w-full h-full flex flex-col items-center justify-center bg-gray-200 dark:bg-ph-surface-panel text-gray-400 dark:text-gray-500">
                            <User size={64} className="mb-4 opacity-50" />
                            <span className="text-xs font-bold uppercase tracking-widest opacity-50">No Image</span>
                        </div>
                    )}
                    
                    {/* Upload Button */}
                    <div className="absolute bottom-4 right-4 z-20">
                        <button 
                            onClick={() => fileInputRef.current?.click()}
                            className="flex items-center gap-2 bg-white/90 dark:bg-ph-surface-panel/90 backdrop-blur-md px-4 py-2.5 rounded-full shadow-xl border border-gray-200 dark:border-white/10 hover:scale-105 active:scale-95 transition-all duration-300 group/btn"
                        >
                            <Camera size={16} className="text-gray-700 dark:text-gray-300 group-hover/btn:text-red-500 transition-colors" />
                            <span className="text-[10px] font-black uppercase tracking-wider text-gray-700 dark:text-gray-300 group-hover/btn:text-red-500 transition-colors">
                                {character.photoUrl ? "Ubah Foto" : "Upload Foto"}
                            </span>
                        </button>
                        <input 
                            type="file" 
                            ref={fileInputRef}
                            onChange={handlePhotoUpload}
                            accept="image/*"
                            className="hidden"
                        />
                    </div>
                    
                    {/* Gradient Overlay */}
                    <div className="absolute bottom-0 left-0 w-full h-32 bg-gradient-to-t from-white via-white/80 to-transparent dark:from-ph-surface-card dark:via-ph-surface-card/80 dark:to-transparent z-10 pointer-events-none"></div>
                </div>

                {/* Name & Level */}
                <div className="relative z-10 w-full mt-auto">
                    <h1 className="text-4xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter mb-2 drop-shadow-sm">
                        {character.name.replace('_', ' ')}
                    </h1>
                    
                    <div className="flex items-center justify-center gap-3 mb-6">
                        <div className="px-3 py-1 rounded-lg bg-gray-100 dark:bg-white/10 border border-gray-200 dark:border-white/5">
                            <span className="text-xs font-black uppercase tracking-widest text-gray-600 dark:text-gray-300">
                                Level {character.level}
                            </span>
                        </div>
                        <div className="flex items-center gap-1.5 px-3 py-1 rounded-lg bg-gray-100 dark:bg-white/10 border border-gray-200 dark:border-white/5">
                            <Clock size={12} className="text-gray-500" />
                            <span className="text-[10px] font-bold uppercase tracking-widest text-gray-500">
                                {character.lastLogin}
                            </span>
                        </div>
                    </div>

                    {/* Badges */}
                    <div className="flex flex-wrap justify-center gap-2 mb-8 w-full">
                        <div className={`flex items-center gap-2 px-4 py-2 rounded-xl border ${factionDetails.bg} ${factionDetails.border} ${factionDetails.color}`}>
                            <factionDetails.icon size={14} />
                            <span className="text-xs font-black uppercase tracking-wider">{character.faction}</span>
                        </div>
                        <div className="flex items-center gap-2 px-4 py-2 rounded-xl bg-blue-500/10 border border-blue-500/20 text-blue-600 dark:text-blue-400">
                            <Briefcase size={14} />
                            <span className="text-xs font-black uppercase tracking-wider">{jobName}</span>
                        </div>
                    </div>

                    {/* Status Grid */}
                    <div className="grid grid-cols-2 gap-4 w-full pt-6 border-t border-gray-200 dark:border-white/10">
                        <div className="p-4 rounded-2xl bg-gray-50 dark:bg-white/5 border border-gray-100 dark:border-white/5">
                            <p className="text-[10px] text-gray-400 uppercase font-bold mb-1 tracking-wider">Character Story</p>
                            <p className={`text-sm font-black uppercase tracking-wide ${character.storyStatus === 'Active' ? 'text-green-500' : 'text-amber-500'}`}>
                                {character.storyStatus}
                            </p>
                        </div>
                        <div className="p-4 rounded-2xl bg-gray-50 dark:bg-white/5 border border-gray-100 dark:border-white/5">
                            <p className="text-[10px] text-gray-400 uppercase font-bold mb-1 tracking-wider">Skin ID</p>
                            <p className="text-sm font-black text-gray-900 dark:text-white tracking-wide">{character.skinId}</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        {/* RIGHT COLUMN: Dashboard Data (Span 8) */}
        <div className="col-span-1 lg:col-span-8 flex flex-col gap-4 md:gap-8 lg:gap-10">
            
            {/* Card 1: Vitals & Financials */}
            <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-3xl p-6 shadow-sm relative overflow-hidden">
                <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
                
                <div className="grid grid-cols-1 md:grid-cols-2 gap-8 relative z-10">
                    {/* Left: Vitals (HTM + Health/Armor) */}
                    <div className="space-y-6">
                        <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-3 mb-6">
                            <div className="p-2 rounded-lg bg-gray-100 dark:bg-white/10">
                                <ActivityIcon />
                            </div>
                            Vitals & Survival
                        </h3>
                        <div className="space-y-5">
                            <ProgressBar label="Health" value={health} color="bg-green-500" icon={Heart} />
                            <ProgressBar label="Armor" value={armor} color="bg-blue-500" icon={Shield} />
                        </div>
                        <div className="space-y-5 pt-6 border-t border-gray-100 dark:border-white/10">
                            <ProgressBar label="Hunger" value={hunger} color="bg-orange-500" icon={Utensils} />
                            <ProgressBar label="Thirsty" value={thirsty} color="bg-cyan-400" icon={Droplets} />
                            <ProgressBar label="Mood" value={mood} color="bg-purple-500" icon={Smile} />
                        </div>
                    </div>

                    {/* Right: Financials */}
                    <div className="space-y-6">
                        <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-3 mb-6">
                            <div className="p-2 rounded-lg bg-gray-100 dark:bg-white/10">
                                <Wallet size={20} />
                            </div>
                            Financials
                        </h3>
                        <div className="grid grid-cols-1 gap-4">
                            <StatCard label="Cash" value={`$${character.money.toLocaleString()}`} icon={Wallet} color="text-green-500" bg="bg-green-500/10" />
                            <StatCard label="Bank" value={`$${character.bank.toLocaleString()}`} icon={Landmark} color="text-blue-500" bg="bg-blue-500/10" />
                            <StatCard label="Paycheck" value={`$${liveStats.paycheck.toLocaleString()}`} icon={DollarSign} color="text-amber-500" bg="bg-amber-500/10" />
                        </div>
                    </div>
                </div>
            </div>

            {/* Card 2: Licenses */}
            <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-3xl p-6 shadow-sm relative overflow-hidden">
                <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
                
                <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-3 mb-6 relative z-10">
                    <div className="p-2 rounded-lg bg-gray-100 dark:bg-white/10">
                        <FileCheck size={20} />
                    </div>
                    Licenses
                </h3>
                <div className="grid grid-cols-2 lg:grid-cols-4 gap-4 relative z-10">
                    {licenses.map((lic, idx) => (
                        <div key={idx} className={`flex flex-col p-4 rounded-2xl border transition-all ${lic.valid ? 'bg-green-50 dark:bg-green-900/10 border-green-200 dark:border-green-900/30' : 'bg-gray-50 dark:bg-white/5 border-gray-200 dark:border-white/5'}`}>
                            <div className="flex items-center gap-3 mb-4">
                                <div className={`p-2 rounded-xl ${lic.valid ? 'bg-green-100 dark:bg-green-900/30 text-green-600 dark:text-green-400' : 'bg-gray-200 dark:bg-white/10 text-gray-500'}`}>
                                    {lic.valid ? <FileCheck size={18} /> : <FileX size={18} />}
                                </div>
                                <span className={`text-xs font-black uppercase tracking-wide ${lic.valid ? 'text-gray-900 dark:text-white' : 'text-gray-500'}`}>{lic.name}</span>
                            </div>
                            <div className="mt-auto pt-3 border-t border-black/5 dark:border-white/5 flex justify-between items-center">
                                <span className="text-[9px] font-bold text-gray-400 uppercase tracking-wider">Status</span>
                                <span className={`text-[10px] font-mono font-bold uppercase ${lic.valid ? 'text-green-600 dark:text-green-400' : 'text-red-500'}`}>
                                    {lic.exp}
                                </span>
                            </div>
                        </div>
                    ))}
                </div>
            </div>

        </div>
      </div>

      {/* BOTTOM ROW: Assets & Vehicles */}
      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6 items-stretch">
          {/* Assets */}
          <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-3xl p-6 shadow-sm relative overflow-hidden">
              <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
              
              <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-3 mb-6 relative z-10">
                  <div className="p-2 rounded-lg bg-gray-100 dark:bg-white/10">
                      <Home size={20} />
                  </div>
                  Assets
              </h3>
              <div className="space-y-6 relative z-10">
                  <div className="space-y-4">
                      <AssetCategory title="Residential" items={assets.residential} />
                      <AssetCategory title="Commercial" items={assets.commercial} />
                  </div>
                  <div className="space-y-4">
                      <AssetCategory title="Other" items={assets.other} />
                  </div>
              </div>
          </div>

          {/* Vehicles */}
          <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-3xl p-6 shadow-sm relative overflow-hidden">
              <div className="absolute inset-0  opacity-[0.03]" style={{ backgroundImage: `url(${import.meta.env.BASE_URL}assets/images/carbon-fibre.png)` }}></div>
              
              <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-3 mb-6 relative z-10">
                  <div className="p-2 rounded-lg bg-gray-100 dark:bg-white/10">
                      <Car size={20} />
                  </div>
                  Personal Vehicles
              </h3>
              <div className="space-y-3 relative z-10">
                  {vehicles.length > 0 ? (
                      vehicles.map((veh, idx) => {
                          const VehIcon = veh.icon || Car;
                          return (
                          <div key={idx} className="flex items-center justify-between p-4 rounded-2xl bg-gray-50 dark:bg-white/5 border border-gray-100 dark:border-white/5 hover:border-gray-200 dark:hover:border-white/10 transition-colors">
                              <div className="flex items-center gap-4">
                                  <div className="p-2.5 rounded-xl bg-gray-200 dark:bg-white/10 text-gray-600 dark:text-gray-300">
                                      <VehIcon size={18} />
                                  </div>
                                  <div>
                                      <p className="text-sm font-black text-gray-900 dark:text-white">{veh.name}</p>
                                      <p className="text-[10px] font-mono text-gray-500 uppercase tracking-wider">{veh.plate}</p>
                                  </div>
                              </div>
                              <span className="text-[10px] font-bold uppercase tracking-wider text-gray-400 bg-gray-100 dark:bg-white/5 px-2 py-1 rounded-lg">{veh.location}</span>
                          </div>
                      )})
                  ) : (
                      <div className="w-full border-2 border-dashed border-gray-200 dark:border-gray-700/50 rounded-2xl p-8 flex items-center justify-center bg-gray-50 dark:bg-gray-800/20">
                          <p className="text-gray-400 dark:text-gray-500 font-medium text-sm italic">Tidak ada kendaraan pribadi</p>
                      </div>
                  )}
              </div>
          </div>
      </div>
    </div>
  );
};

// --- Helper Components ---

const ProgressBar = ({ label, value, color, icon: Icon }: any) => (
    <div>
        <div className="flex justify-between text-xs font-bold mb-2">
            <div className="flex items-center gap-2 text-gray-500 uppercase tracking-wider text-[10px]">
                {Icon && <Icon size={12} />}
                <span>{label}</span>
            </div>
            <span className={color.replace('bg-', 'text-')}>{value}%</span>
        </div>
        <div className="h-2.5 w-full bg-gray-100 dark:bg-white/5 rounded-full overflow-hidden border border-gray-100 dark:border-white/5">
            <div className={`h-full ${color} rounded-full shadow-[0_0_10px_rgba(0,0,0,0.2)]`} style={{ width: `${value}%` }}></div>
        </div>
    </div>
);

const AssetCategory = ({ title, items }: any) => (
    <div>
        <h4 className="text-[10px] font-black text-gray-400 uppercase mb-3 border-b border-gray-100 dark:border-white/5 pb-2 tracking-widest">{title}</h4>
        <div className="space-y-2">
            {items.length > 0 ? (
                items.map((asset: any, idx: number) => {
                    const AssetIcon = asset.icon || Home;
                    return (
                    <div key={idx} className="flex items-center justify-between p-3 rounded-xl hover:bg-gray-50 dark:hover:bg-white/5 transition-colors border border-transparent hover:border-gray-100 dark:hover:border-white/5 group">
                        <div className="flex items-center gap-3">
                            <div className="p-2 rounded-lg bg-gray-100 dark:bg-white/10 text-gray-500 group-hover:text-gray-900 dark:group-hover:text-white transition-colors">
                                <AssetIcon size={14} />
                            </div>
                            <p className="text-xs font-bold text-gray-900 dark:text-white">{asset.name}</p>
                        </div>
                        <p className="text-[9px] text-gray-500 uppercase font-bold tracking-wider bg-gray-100 dark:bg-white/5 px-2 py-1 rounded-md">{asset.location}</p>
                    </div>
                )})
            ) : (
                <div className="w-full border-2 border-dashed border-gray-200 dark:border-gray-700/50 rounded-xl p-4 flex items-center justify-center bg-gray-50 dark:bg-gray-800/20">
                    <p className="text-gray-400 dark:text-gray-500 font-medium text-xs italic">Tidak ada properti di kategori ini</p>
                </div>
            )}
        </div>
    </div>
);

const ActivityIcon = () => (
    <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
        <path d="M22 12h-4l-3 9L9 3l-3 9H2"/>
    </svg>
);

const InfoBox = ({ icon: Icon, label, value, color }: any) => (
    <div className="flex flex-col items-center justify-center p-4 rounded-2xl bg-gray-50 dark:bg-white/5 border border-gray-100 dark:border-white/5">
        <Icon size={18} className={`mb-2 ${color}`} />
        <span className="text-[9px] font-bold text-gray-400 uppercase tracking-wider">{label}</span>
        <span className="text-sm font-black text-gray-900 dark:text-white">{value}</span>
    </div>
);

const StatCard = ({ label, value, icon: Icon, color, bg }: any) => (
    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-2xl border border-gray-100 dark:border-white/5 flex items-center gap-4 transition-colors hover:bg-gray-100 dark:hover:bg-white/10">
        <div className={`p-3 rounded-xl bg-white dark:bg-white/10 ${color} shadow-sm`}>
            <Icon size={20} />
        </div>
        <div>
            <p className="text-[10px] font-bold text-gray-400 uppercase tracking-wider mb-0.5">{label}</p>
            <p className={`text-lg font-black ${color}`}>{value}</p>
        </div>
    </div>
);
