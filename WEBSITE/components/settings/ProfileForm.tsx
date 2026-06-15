
import React, { useState, useMemo, useEffect } from 'react';
import { User, Calendar, Users, Phone, MapPin, Save, Loader2, AlertTriangle, CheckCircle2, Lock, Gift, ShieldCheck, Globe } from 'lucide-react';
import { UserProfile } from '../../types';
import { InputGroup } from './InputGroup';
import { CustomSelect } from './CustomSelect';
import { INDONESIA_REGIONS } from '../../utils/indonesia-regions';
import { COUNTRIES } from '../../utils/countries';

interface ProfileFormProps {
    profile: UserProfile;
    setProfile: React.Dispatch<React.SetStateAction<UserProfile>>;
    onSave: (e: React.FormEvent) => void;
    isLoading: boolean;
}

export const ProfileForm: React.FC<ProfileFormProps> = ({ profile, setProfile, onSave, isLoading }) => {
  const [showConfirm, setShowConfirm] = useState(false);
  const [errors, setErrors] = useState<Record<string, string>>({});
  const [selectedProvince, setSelectedProvince] = useState<string>('');
  const [selectedCity, setSelectedCity] = useState<string>('');
  const [regionType, setRegionType] = useState<'WNI' | 'WNA'>('WNI');
  const [selectedCountry, setSelectedCountry] = useState<string>('');

  // Initialize from profile.address if it exists
  useEffect(() => {
    if (profile.address) {
      const parts = profile.address.split(', ');
      if (parts.length === 2 && INDONESIA_REGIONS[parts[1]]) {
        setRegionType('WNI');
        setSelectedProvince(parts[1]);
        setSelectedCity(parts[0]);
      } else if (COUNTRIES.includes(profile.address)) {
        setRegionType('WNA');
        setSelectedCountry(profile.address);
      }
    }
  }, [profile.address]);

  const handleRegionTypeChange = (type: 'WNI' | 'WNA') => {
    setRegionType(type);
    setSelectedProvince('');
    setSelectedCity('');
    setSelectedCountry('');
    handleInputChange('address', ''); // reset address
  };

  const handleProvinceChange = (prov: string) => {
    setSelectedProvince(prov);
    setSelectedCity('');
    handleInputChange('address', ''); // reset address
  };

  const handleCityChange = (city: string) => {
    setSelectedCity(city);
    if (selectedProvince && city) {
      handleInputChange('address', `${city}, ${selectedProvince}`);
    } else {
      handleInputChange('address', '');
    }
  };

  const handleCountryChange = (country: string) => {
    setSelectedCountry(country);
    handleInputChange('address', country);
  };

  // Calculate Age automatically
  const calculatedAge = useMemo(() => {
      if (!profile.birthDate) return null;
      const today = new Date();
      const birthDate = new Date(profile.birthDate);
      let age = today.getFullYear() - birthDate.getFullYear();
      const m = today.getMonth() - birthDate.getMonth();
      if (m < 0 || (m === 0 && today.getDate() < birthDate.getDate())) {
          age--;
      }
      return age;
  }, [profile.birthDate]);

  // Format Date for Display (Indonesia)
  const formattedBirthDate = useMemo(() => {
      if (!profile.birthDate) return '-';
      return new Date(profile.birthDate).toLocaleDateString('id-ID', {
          day: 'numeric',
          month: 'long',
          year: 'numeric'
      });
  }, [profile.birthDate]);

  const validateForm = () => {
      const newErrors: Record<string, string> = {};
      if (!profile.oocName.trim()) newErrors.oocName = "Wajib diisi";
      if (!profile.birthDate) newErrors.birthDate = "Wajib diisi";
      if (!profile.phoneNumber.trim()) newErrors.phoneNumber = "Wajib diisi";
      if (!profile.address.trim()) newErrors.address = "Wajib diisi";
      
      setErrors(newErrors);
      return Object.keys(newErrors).length === 0;
  };

  const handleInitialSubmit = (e: React.FormEvent) => {
      e.preventDefault();
      if(validateForm()) {
          setShowConfirm(true);
      }
  };

  const handleFinalConfirm = (e: React.FormEvent) => {
      setShowConfirm(false);
      onSave(e);
  };

  const handleInputChange = (field: keyof UserProfile, value: string) => {
      setProfile(prev => ({...prev, [field]: value}));
      if (errors[field]) {
          setErrors(prev => {
              const newErrors = {...prev};
              delete newErrors[field];
              return newErrors;
          });
      }
  };

  return (
    <>
        <div className="h-full flex flex-col justify-center bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 p-4 md:p-8 rounded-2xl md:rounded-3xl shadow-sm relative">
            <div className="absolute top-0 right-0 p-8 opacity-5 pointer-events-none text-gray-900 dark:text-white hidden md:block overflow-hidden rounded-3xl">
                <User size={120} />
            </div>

            <div className="flex justify-between items-center mb-6 md:mb-8 relative z-10">
                <h3 className="text-lg md:text-xl font-black text-gray-900 dark:text-white flex items-center uppercase italic tracking-tighter">
                    <span className="w-1.5 h-6 md:h-8 bg-red-600 rounded-full mr-3"></span>
                    Informasi Pribadi
                </h3>
                {profile.isLocked && (
                    <div className="flex items-center gap-2 px-3 py-1.5 bg-green-500/10 text-green-600 dark:text-green-400 rounded-full border border-green-500/20 shadow-sm">
                        <CheckCircle2 size={14} strokeWidth={3} />
                        <span className="text-[10px] font-black uppercase tracking-widest">Terverifikasi</span>
                    </div>
                )}
            </div>
            
            {profile.isLocked ? (
                <div className="flex flex-col relative z-10">
                    {/* Security Banner */}
                    <div className="bg-gray-50 dark:bg-[#0f0f0f] border border-gray-200 dark:border-white/5 rounded-2xl p-6 md:p-8 text-center mb-6 relative overflow-hidden group">
                        <div className="absolute inset-0 bg-[radial-gradient(ellipse_at_center,_var(--tw-gradient-stops))] from-green-500/5 via-transparent to-transparent opacity-50 pointer-events-none"></div>
                        
                        <div className="w-16 h-16 md:w-20 md:h-20 bg-gradient-to-b from-green-100 to-green-50 dark:from-green-900/30 dark:to-green-900/10 rounded-2xl flex items-center justify-center mx-auto text-green-600 dark:text-green-500 shadow-lg shadow-green-900/5 mb-4 border border-green-200 dark:border-green-500/20 transform group-hover:scale-110 transition-transform duration-500">
                            <ShieldCheck size={32} strokeWidth={1.5} className="md:w-10 md:h-10" />
                        </div>
                        
                        <div className="relative z-10 max-w-lg mx-auto">
                            <h4 className="text-gray-900 dark:text-white font-black uppercase text-sm md:text-base tracking-widest mb-2">Data Terenkripsi & Aman</h4>
                            <p className="text-gray-500 dark:text-gray-400 text-[10px] md:text-xs leading-relaxed font-medium">
                                Data pribadi Anda disimpan dalam database terenkripsi (AES-256). Informasi ini <strong className="text-green-600 dark:text-green-400">bersifat rahasia</strong> dan hanya digunakan untuk verifikasi kepemilikan akun.
                            </p>
                        </div>
                    </div>
                    
                    {/* Data Grid */}
                    <div className="grid grid-cols-1 md:grid-cols-2 gap-3 md:gap-4">
                        <LockedField 
                            label="Nama Lengkap" 
                            value={profile.oocName} 
                            icon={User}
                        />
                        <LockedField 
                            label="Jenis Kelamin" 
                            value={profile.gender === 'Male' ? 'Laki-laki' : 'Perempuan'} 
                            icon={Users}
                        />
                        <LockedField 
                            label="Tanggal Lahir" 
                            value={formattedBirthDate}
                            subValue={`${calculatedAge} Tahun`}
                            icon={Calendar}
                        />
                        <LockedField 
                            label="Nomor Whatsapp" 
                            value={profile.phoneNumber} 
                            icon={Phone}
                        />
                        <LockedField 
                            label="Domisili / Kota" 
                            value={profile.address} 
                            icon={MapPin}
                            className="md:col-span-2"
                        />
                    </div>
                </div>
            ) : (
                <form onSubmit={handleInitialSubmit} className="space-y-4 md:space-y-6 relative z-10" noValidate>
                    <div className="bg-blue-50 dark:bg-blue-900/10 border border-blue-100 dark:border-blue-900/20 p-4 rounded-xl flex gap-3 items-start">
                        <div className="p-1.5 bg-blue-100 dark:bg-blue-500/20 rounded-lg shrink-0 text-blue-600 dark:text-blue-400">
                            <AlertTriangle size={16} />
                        </div>
                        <div className="flex-1">
                            <h4 className="text-[10px] md:text-xs font-bold text-blue-700 dark:text-blue-300 uppercase mb-1">Perhatian</h4>
                            <p className="text-[10px] md:text-xs text-blue-800 dark:text-blue-200 leading-relaxed opacity-80">
                                Isi data sesuai KTP/Identitas Asli. Tanggal lahir digunakan untuk verifikasi umur dan <strong>Reward Ulang Tahun</strong>. Data akan dikunci setelah disimpan.
                            </p>
                        </div>
                    </div>

                    <div className="grid grid-cols-1 md:grid-cols-2 gap-4 md:gap-6">
                        <InputGroup 
                            label="Nama Asli (OOC)" 
                            icon={User} 
                            value={profile.oocName} 
                            onChange={(e) => handleInputChange('oocName', e.target.value)}
                            placeholder="Nama Lengkap Sesuai KTP"
                            error={errors.oocName}
                        />
                        
                        <div className="relative">
                            <InputGroup 
                                label="Tanggal Lahir" 
                                icon={Calendar} 
                                type="date"
                                value={profile.birthDate} 
                                onChange={(e) => handleInputChange('birthDate', e.target.value)}
                                error={errors.birthDate}
                            />
                            {calculatedAge !== null && (
                                <div className="absolute right-0 top-0 flex items-center gap-1.5 bg-green-100 dark:bg-green-900/20 text-green-700 dark:text-green-400 px-2 py-0.5 rounded text-[10px] font-bold border border-green-200 dark:border-green-900/30">
                                    <Gift size={10} />
                                    <span>{calculatedAge} Tahun</span>
                                </div>
                            )}
                        </div>
                    </div>
                    
                    <div className="grid grid-cols-1 md:grid-cols-2 gap-4 md:gap-6">
                            <div>
                            <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase mb-1.5 ml-1">Gender</label>
                            <CustomSelect
                                value={profile.gender}
                                onChange={(val) => setProfile(prev => ({...prev, gender: val}))}
                                options={[
                                    { value: 'Male', label: 'Laki-laki' },
                                    { value: 'Female', label: 'Perempuan' }
                                ]}
                                placeholder="Pilih Gender"
                                icon={<Users size={18} />}
                            />
                        </div>
                        <InputGroup 
                            label="Whatsapp Aktif" 
                            icon={Phone} 
                            value={profile.phoneNumber} 
                            onChange={(e) => handleInputChange('phoneNumber', e.target.value)}
                            placeholder="08xxxxxxxxxx"
                            type="tel"
                            error={errors.phoneNumber}
                        />
                    </div>

                    <div className="space-y-4 md:space-y-6">
                        <div>
                            <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase mb-2 ml-1">Kewarganegaraan / Region</label>
                            <div className="flex gap-3 md:gap-4">
                                <label className={`flex-1 flex items-center justify-center gap-2 py-3 px-4 rounded-xl border cursor-pointer transition-all ${regionType === 'WNI' ? 'bg-red-50 border-red-500 text-red-600 dark:bg-red-500/10 dark:border-red-500/50 dark:text-red-400' : 'bg-gray-50 border-gray-200 text-gray-600 dark:bg-black/20 dark:border-white/10 dark:text-gray-400 hover:bg-gray-100 dark:hover:bg-white/5'}`}>
                                    <input type="radio" name="regionType" value="WNI" checked={regionType === 'WNI'} onChange={() => handleRegionTypeChange('WNI')} className="hidden" />
                                    <MapPin size={16} />
                                    <span className="text-xs md:text-sm font-bold">WNI (Indonesia)</span>
                                </label>
                                <label className={`flex-1 flex items-center justify-center gap-2 py-3 px-4 rounded-xl border cursor-pointer transition-all ${regionType === 'WNA' ? 'bg-red-50 border-red-500 text-red-600 dark:bg-red-500/10 dark:border-red-500/50 dark:text-red-400' : 'bg-gray-50 border-gray-200 text-gray-600 dark:bg-black/20 dark:border-white/10 dark:text-gray-400 hover:bg-gray-100 dark:hover:bg-white/5'}`}>
                                    <input type="radio" name="regionType" value="WNA" checked={regionType === 'WNA'} onChange={() => handleRegionTypeChange('WNA')} className="hidden" />
                                    <Globe size={16} />
                                    <span className="text-xs md:text-sm font-bold">WNA (Luar Negeri)</span>
                                </label>
                            </div>
                        </div>

                        {regionType === 'WNI' ? (
                            <div className="grid grid-cols-1 md:grid-cols-2 gap-4 md:gap-6">
                                <div>
                                    <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase mb-1.5 ml-1">Provinsi</label>
                                    <CustomSelect
                                        value={selectedProvince}
                                        onChange={handleProvinceChange}
                                        options={Object.keys(INDONESIA_REGIONS).sort().map(prov => ({ value: prov, label: prov }))}
                                        placeholder="Pilih Provinsi"
                                        icon={<MapPin size={18} />}
                                        error={errors.address}
                                        searchable={true}
                                    />
                                </div>

                                <div>
                                    <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase mb-1.5 ml-1">Kota / Kabupaten</label>
                                    <CustomSelect
                                        value={selectedCity}
                                        onChange={handleCityChange}
                                        options={selectedProvince ? INDONESIA_REGIONS[selectedProvince].sort().map(city => ({ value: city, label: city })) : []}
                                        placeholder="Pilih Kota/Kabupaten"
                                        icon={<MapPin size={18} />}
                                        error={errors.address}
                                        disabled={!selectedProvince}
                                        searchable={true}
                                    />
                                    {errors.address && (
                                        <p className="text-red-500 text-[10px] md:text-xs mt-1.5 ml-1 font-medium">{errors.address}</p>
                                    )}
                                </div>
                            </div>
                        ) : (
                            <div>
                                <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase mb-1.5 ml-1">Negara Domisili</label>
                                <CustomSelect
                                    value={selectedCountry}
                                    onChange={handleCountryChange}
                                    options={COUNTRIES.map(c => ({ value: c, label: c }))}
                                    placeholder="Pilih Negara"
                                    icon={<Globe size={18} />}
                                    error={errors.address}
                                    searchable={true}
                                />
                                {errors.address && (
                                    <p className="text-red-500 text-[10px] md:text-xs mt-1.5 ml-1 font-medium">{errors.address}</p>
                                )}
                            </div>
                        )}
                    </div>

                    <div className="pt-6 mt-4 border-t border-gray-100 dark:border-white/10">
                        <button 
                            type="submit"
                            disabled={isLoading}
                            className="w-full bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 text-white font-bold py-3.5 md:py-4 rounded-xl uppercase text-xs tracking-widest shadow-lg shadow-red-600/20 disabled:opacity-50 disabled:cursor-not-allowed transform active:scale-[0.99] transition-all flex items-center justify-center gap-2"
                        >
                            {isLoading ? <Loader2 className="animate-spin" size={18} /> : <Save size={18} />}
                            <span>Simpan Permanen</span>
                        </button>
                    </div>
                </form>
            )}
        </div>

        {/* CONFIRMATION MODAL */}
        {showConfirm && (
            <div className="fixed inset-0 z-50 flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.1s_ease-out]">
                <div className="bg-white dark:bg-[#121212] w-full max-w-md rounded-t-3xl md:rounded-2xl border-t-4 border-red-600 shadow-2xl overflow-hidden animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
                    
                    {/* Mobile Drag Handle */}
                    <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

                    <div className="p-6 text-center">
                        <div className="w-16 h-16 bg-red-100 dark:bg-red-900/20 rounded-full flex items-center justify-center mx-auto mb-4 text-red-600 animate-pulse">
                            <AlertTriangle size={32} />
                        </div>
                        <h3 className="text-xl font-black text-gray-900 dark:text-white uppercase italic mb-2">Konfirmasi Data</h3>
                        <p className="text-sm text-gray-600 dark:text-gray-300 leading-relaxed mb-6">
                            Pastikan data yang Anda masukkan <strong>100% BENAR</strong>.
                            <br/>
                            Data ini <span className="text-red-600 font-bold">TIDAK BISA DIUBAH</span> setelah disimpan.
                        </p>
                        
                        <div className="flex flex-col gap-3">
                            <button 
                                onClick={handleFinalConfirm}
                                className="w-full bg-red-600 hover:bg-red-500 text-white font-bold py-3.5 rounded-xl uppercase text-xs tracking-widest shadow-lg shadow-red-600/20"
                            >
                                Ya, Simpan Data
                            </button>
                            <button 
                                onClick={() => setShowConfirm(false)}
                                className="w-full bg-transparent border border-gray-200 dark:border-white/10 hover:bg-gray-50 dark:hover:bg-white/5 text-gray-500 hover:text-gray-900 dark:text-gray-400 dark:hover:text-white font-bold py-3.5 rounded-xl uppercase text-xs tracking-widest"
                            >
                                Periksa Kembali
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        )}
    </>
  );
};

// Refined LockedField for better fit and visual appeal
const LockedField = ({label, value, subValue, icon: Icon, className = ""}: {label: string, value: string, subValue?: string, icon: any, className?: string}) => (
    <div className={`bg-gray-50 dark:bg-[#151515] p-3 md:p-4 rounded-2xl border border-gray-200 dark:border-white/5 flex items-center gap-3 md:gap-4 group hover:border-gray-300 dark:hover:border-white/20 transition-all ${className}`}>
        <div className="w-10 h-10 md:w-12 md:h-12 bg-white dark:bg-white/5 rounded-xl flex items-center justify-center text-gray-400 group-hover:text-red-500 transition-colors shadow-sm shrink-0 border border-gray-100 dark:border-white/5">
            <Icon size={20} className="md:w-5 md:h-5" />
        </div>
        <div className="min-w-0 flex-1 flex flex-col justify-center">
            <span className="text-[10px] text-gray-500 uppercase font-bold tracking-wider mb-0.5">{label}</span>
            <div className="flex items-center gap-2">
                <span className="text-sm md:text-base font-bold text-gray-900 dark:text-white truncate">{value}</span>
                {subValue && (
                    <span className="text-[10px] bg-gray-200 dark:bg-white/10 text-gray-600 dark:text-gray-300 px-1.5 py-0.5 rounded font-mono font-bold">{subValue}</span>
                )}
            </div>
        </div>
    </div>
);
