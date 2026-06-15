
import React, { useState } from 'react';
import { X, Save, User, Flag, Calendar, Users, AlertCircle, ChevronDown, Search, Check, Minus, Plus, Ruler, Weight } from 'lucide-react';
import { InputGroup } from '../settings/InputGroup';

const COUNTRIES = [
  "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados", "Belarus", "Belgium", "Belize", "Benin", "Bhutan", "Bolivia", "Bosnia and Herzegovina", "Botswana", "Brazil", "Brunei", "Bulgaria", "Burkina Faso", "Burundi", "Cabo Verde", "Cambodia", "Cameroon", "Canada", "Central African Republic", "Chad", "Chile", "China", "Colombia", "Comoros", "Congo", "Costa Rica", "Croatia", "Cuba", "Cyprus", "Czechia", "Denmark", "Djibouti", "Dominica", "Dominican Republic", "Ecuador", "Egypt", "El Salvador", "Equatorial Guinea", "Eritrea", "Estonia", "Eswatini", "Ethiopia", "Fiji", "Finland", "France", "Gabon", "Gambia", "Georgia", "Germany", "Ghana", "Greece", "Grenada", "Guatemala", "Guinea", "Guinea-Bissau", "Guyana", "Haiti", "Honduras", "Hungary", "Iceland", "India", "Indonesia", "Iran", "Iraq", "Ireland", "Israel", "Italy", "Jamaica", "Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati", "Kuwait", "Kyrgyzstan", "Laos", "Latvia", "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg", "Madagascar", "Malawi", "Malaysia", "Maldives", "Mali", "Malta", "Marshall Islands", "Mauritania", "Mauritius", "Mexico", "Micronesia", "Moldova", "Monaco", "Mongolia", "Montenegro", "Morocco", "Mozambique", "Myanmar", "Namibia", "Nauru", "Nepal", "Netherlands", "New Zealand", "Nicaragua", "Niger", "Nigeria", "North Korea", "North Macedonia", "Norway", "Oman", "Pakistan", "Palau", "Palestine", "Panama", "Papua New Guinea", "Paraguay", "Peru", "Philippines", "Poland", "Portugal", "Qatar", "Romania", "Russia", "Rwanda", "Saint Kitts and Nevis", "Saint Lucia", "Saint Vincent and the Grenadines", "Samoa", "San Marino", "Sao Tome and Principe", "Saudi Arabia", "Senegal", "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovakia", "Slovenia", "Solomon Islands", "Somalia", "South Africa", "South Korea", "South Sudan", "Spain", "Sri Lanka", "Sudan", "Suriname", "Sweden", "Switzerland", "Syria", "Tajikistan", "Tanzania", "Thailand", "Timor-Leste", "Togo", "Tonga", "Trinidad and Tobago", "Tunisia", "Turkey", "Turkmenistan", "Tuvalu", "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom", "United States of America", "Uruguay", "Uzbekistan", "Vanuatu", "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe"
];

interface CreateCharacterModalProps {
  onClose: () => void;
  onCreate: (formData: any) => void;
}

export const CreateCharacterModal: React.FC<CreateCharacterModalProps> = ({ onClose, onCreate }) => {
  const [formData, setFormData] = useState({ name: '', origin: 'United States of America', gender: 'Male', age: '', height: '', weight: '' });
  const [errors, setErrors] = useState<Record<string, string>>({});
  const [showCountrySelect, setShowCountrySelect] = useState(false);
  const [showGenderSelect, setShowGenderSelect] = useState(false);
  const [countrySearch, setCountrySearch] = useState('');

  const filteredCountries = COUNTRIES.filter(c => c.toLowerCase().includes(countrySearch.toLowerCase()));

  const validate = () => {
      const newErrors: Record<string, string> = {};
      
      // Regex for Firstname_Lastname (e.g., John_Doe)
      const nameRegex = /^[A-Z][a-zA-Z]*_[A-Z][a-zA-Z]*$/;
      
      if (!formData.name.trim()) {
          newErrors.name = "Wajib diisi";
      } else if (!nameRegex.test(formData.name)) {
          newErrors.name = "Format harus First_Last (Cth: John_Doe)";
      }

      if (!formData.age) newErrors.age = "Wajib diisi";
      else if (parseInt(formData.age) < 17 || parseInt(formData.age) > 60) newErrors.age = "17-60 Thn";
      
      if (!formData.height) newErrors.height = "Wajib diisi";
      else if (parseInt(formData.height) < 140 || parseInt(formData.height) > 220) newErrors.height = "140-220 CM";

      if (!formData.weight) newErrors.weight = "Wajib diisi";
      else if (parseInt(formData.weight) < 40 || parseInt(formData.weight) > 150) newErrors.weight = "40-150 KG";

      if (!formData.origin.trim()) newErrors.origin = "Wajib diisi";
      
      setErrors(newErrors);
      return Object.keys(newErrors).length === 0;
  };

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if(validate()) {
        onCreate(formData);
    }
  };

  const handleChange = (field: string, value: string) => {
      setFormData(prev => ({ ...prev, [field]: value }));
      if(errors[field]) {
          setErrors(prev => {
              const newErr = {...prev};
              delete newErr[field];
              return newErr;
          });
      }
  };

  return (
    <div className="fixed inset-0 z-[60] flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
        <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 w-full max-w-sm md:max-w-md rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col max-h-[95dvh] overflow-hidden transform scale-100 transition-all animate-in slide-in-from-bottom-full md:slide-in-from-bottom-0 md:zoom-in-95 duration-300">
            
            {/* Mobile Drag Handle */}
            <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

            <div className="flex justify-between items-center p-4 md:p-5 border-b border-gray-200 dark:border-white/5 bg-gray-50 dark:bg-[#151515]">
                <h3 className="text-sm md:text-lg font-bold text-gray-900 dark:text-white uppercase italic">Buat Karakter Baru</h3>
                <button onClick={onClose} className="text-gray-500 hover:text-red-500 transition-colors">
                    <X size={20} />
                </button>
            </div>
            
            <form onSubmit={handleSubmit} className="p-5 md:p-6 space-y-4 md:space-y-5" noValidate>
                <InputGroup 
                    label="NAMA KARAKTER"
                    icon={User}
                    placeholder="Contoh: Ucok_Slepbeuw"
                    value={formData.name}
                    onChange={e => handleChange('name', e.target.value)}
                    error={errors.name}
                />

                <div className="grid grid-cols-2 gap-3 md:gap-4">
                    <div>
                        <div className="flex justify-between items-center mb-1.5 ml-1">
                            <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase">Gender</label>
                        </div>
                        <div 
                            className="relative group cursor-pointer"
                            onClick={() => setShowGenderSelect(true)}
                        >
                            <Users className="absolute left-4 top-1/2 -translate-y-1/2 text-gray-400 dark:text-gray-500 group-hover:text-red-500 transition-colors" size={18} />
                            <div className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl pl-12 pr-4 py-3 md:py-3.5 text-xs md:text-sm text-gray-900 dark:text-white flex items-center justify-between transition-all group-hover:border-red-500">
                                <span className="truncate">{formData.gender === 'Male' ? 'Laki-laki' : 'Perempuan'}</span>
                                <ChevronDown size={16} className="text-gray-400 flex-shrink-0 ml-2" />
                            </div>
                        </div>
                    </div>
                    
                    <div>
                        <div className="flex justify-between items-center mb-1.5 ml-1">
                            <label className={`block text-[10px] md:text-xs font-bold uppercase transition-colors ${errors.age ? 'text-red-500' : 'text-gray-500'}`}>
                                Umur (17-60)
                            </label>
                            {errors.age && (
                                <span className="text-[9px] font-bold text-red-500 flex items-center gap-1 animate-[fadeIn_0.2s_ease-out]">
                                    {errors.age}
                                </span>
                            )}
                        </div>
                        <div className="relative group flex items-center">
                            <Calendar className={`absolute left-4 top-1/2 -translate-y-1/2 transition-colors ${errors.age ? 'text-red-500' : 'text-gray-400 dark:text-gray-500 group-focus-within:text-red-500'}`} size={18} />
                            
                            <input 
                                type="number"
                                min="17"
                                max="60"
                                className={`w-full bg-gray-50 dark:bg-black/20 border rounded-xl pl-12 pr-20 py-3 md:py-3.5 text-gray-900 dark:text-white text-xs md:text-sm placeholder-gray-400 dark:placeholder-gray-600 outline-none transition-all dark:[color-scheme:dark] appearance-none [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:appearance-none
                                    ${errors.age 
                                        ? 'border-red-500 focus:border-red-600 focus:ring-1 focus:ring-red-500/20 bg-red-50/10 dark:bg-red-900/10' 
                                        : 'border-gray-200 dark:border-white/10 focus:border-red-500 focus:bg-white dark:focus:bg-black/40'
                                    }
                                `}
                                value={formData.age}
                                onChange={e => handleChange('age', e.target.value)}
                            />
                            
                            <div className="absolute right-2 flex items-center gap-1">
                                <button 
                                    type="button"
                                    onClick={() => {
                                        const currentAge = parseInt(formData.age) || 17;
                                        if (currentAge > 17) handleChange('age', (currentAge - 1).toString());
                                    }}
                                    className="p-1.5 bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300 rounded-lg hover:bg-red-100 hover:text-red-600 dark:hover:bg-red-500/20 dark:hover:text-red-400 transition-colors"
                                >
                                    <Minus size={14} />
                                </button>
                                <button 
                                    type="button"
                                    onClick={() => {
                                        const currentAge = parseInt(formData.age) || 17;
                                        if (currentAge < 60) handleChange('age', (currentAge + 1).toString());
                                        else if (!formData.age) handleChange('age', '17');
                                    }}
                                    className="p-1.5 bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300 rounded-lg hover:bg-red-100 hover:text-red-600 dark:hover:bg-red-500/20 dark:hover:text-red-400 transition-colors"
                                >
                                    <Plus size={14} />
                                </button>
                            </div>
                        </div>
                    </div>
                </div>

                <div className="grid grid-cols-2 gap-3 md:gap-4">
                    <div>
                        <div className="flex justify-between items-center mb-1.5 ml-1">
                            <label className={`block text-[10px] md:text-xs font-bold uppercase transition-colors ${errors.height ? 'text-red-500' : 'text-gray-500'}`}>
                                Tinggi (140-220 CM)
                            </label>
                            {errors.height && (
                                <span className="text-[9px] font-bold text-red-500 flex items-center gap-1 animate-[fadeIn_0.2s_ease-out]">
                                    {errors.height}
                                </span>
                            )}
                        </div>
                        <div className="relative group flex items-center">
                            <Ruler className={`absolute left-4 top-1/2 -translate-y-1/2 transition-colors ${errors.height ? 'text-red-500' : 'text-gray-400 dark:text-gray-500 group-focus-within:text-red-500'}`} size={18} />
                            
                            <input 
                                type="number"
                                min="140"
                                max="220"
                                className={`w-full bg-gray-50 dark:bg-black/20 border rounded-xl pl-12 pr-20 py-3 md:py-3.5 text-gray-900 dark:text-white text-xs md:text-sm placeholder-gray-400 dark:placeholder-gray-600 outline-none transition-all dark:[color-scheme:dark] appearance-none [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:appearance-none
                                    ${errors.height 
                                        ? 'border-red-500 focus:border-red-600 focus:ring-1 focus:ring-red-500/20 bg-red-50/10 dark:bg-red-900/10' 
                                        : 'border-gray-200 dark:border-white/10 focus:border-red-500 focus:bg-white dark:focus:bg-black/40'
                                    }
                                `}
                                value={formData.height}
                                onChange={e => handleChange('height', e.target.value)}
                            />
                            
                            <div className="absolute right-2 flex items-center gap-1">
                                <button 
                                    type="button"
                                    onClick={() => {
                                        const currentHeight = parseInt(formData.height) || 170;
                                        if (currentHeight > 140) handleChange('height', (currentHeight - 1).toString());
                                    }}
                                    className="p-1.5 bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300 rounded-lg hover:bg-red-100 hover:text-red-600 dark:hover:bg-red-500/20 dark:hover:text-red-400 transition-colors"
                                >
                                    <Minus size={14} />
                                </button>
                                <button 
                                    type="button"
                                    onClick={() => {
                                        const currentHeight = parseInt(formData.height) || 170;
                                        if (currentHeight < 220) handleChange('height', (currentHeight + 1).toString());
                                        else if (!formData.height) handleChange('height', '170');
                                    }}
                                    className="p-1.5 bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300 rounded-lg hover:bg-red-100 hover:text-red-600 dark:hover:bg-red-500/20 dark:hover:text-red-400 transition-colors"
                                >
                                    <Plus size={14} />
                                </button>
                            </div>
                        </div>
                    </div>

                    <div>
                        <div className="flex justify-between items-center mb-1.5 ml-1">
                            <label className={`block text-[10px] md:text-xs font-bold uppercase transition-colors ${errors.weight ? 'text-red-500' : 'text-gray-500'}`}>
                                Berat (40-150 KG)
                            </label>
                            {errors.weight && (
                                <span className="text-[9px] font-bold text-red-500 flex items-center gap-1 animate-[fadeIn_0.2s_ease-out]">
                                    {errors.weight}
                                </span>
                            )}
                        </div>
                        <div className="relative group flex items-center">
                            <Weight className={`absolute left-4 top-1/2 -translate-y-1/2 transition-colors ${errors.weight ? 'text-red-500' : 'text-gray-400 dark:text-gray-500 group-focus-within:text-red-500'}`} size={18} />
                            
                            <input 
                                type="number"
                                min="40"
                                max="150"
                                className={`w-full bg-gray-50 dark:bg-black/20 border rounded-xl pl-12 pr-20 py-3 md:py-3.5 text-gray-900 dark:text-white text-xs md:text-sm placeholder-gray-400 dark:placeholder-gray-600 outline-none transition-all dark:[color-scheme:dark] appearance-none [&::-webkit-inner-spin-button]:appearance-none [&::-webkit-outer-spin-button]:appearance-none
                                    ${errors.weight 
                                        ? 'border-red-500 focus:border-red-600 focus:ring-1 focus:ring-red-500/20 bg-red-50/10 dark:bg-red-900/10' 
                                        : 'border-gray-200 dark:border-white/10 focus:border-red-500 focus:bg-white dark:focus:bg-black/40'
                                    }
                                `}
                                value={formData.weight}
                                onChange={e => handleChange('weight', e.target.value)}
                            />
                            
                            <div className="absolute right-2 flex items-center gap-1">
                                <button 
                                    type="button"
                                    onClick={() => {
                                        const currentWeight = parseInt(formData.weight) || 65;
                                        if (currentWeight > 40) handleChange('weight', (currentWeight - 1).toString());
                                    }}
                                    className="p-1.5 bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300 rounded-lg hover:bg-red-100 hover:text-red-600 dark:hover:bg-red-500/20 dark:hover:text-red-400 transition-colors"
                                >
                                    <Minus size={14} />
                                </button>
                                <button 
                                    type="button"
                                    onClick={() => {
                                        const currentWeight = parseInt(formData.weight) || 65;
                                        if (currentWeight < 150) handleChange('weight', (currentWeight + 1).toString());
                                        else if (!formData.weight) handleChange('weight', '65');
                                    }}
                                    className="p-1.5 bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300 rounded-lg hover:bg-red-100 hover:text-red-600 dark:hover:bg-red-500/20 dark:hover:text-red-400 transition-colors"
                                >
                                    <Plus size={14} />
                                </button>
                            </div>
                        </div>
                    </div>
                </div>

                <div>
                    <div className="flex justify-between items-center mb-1.5 ml-1">
                        <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase">Asal Negara</label>
                    </div>
                    <div 
                        className="relative group cursor-pointer"
                        onClick={() => setShowCountrySelect(true)}
                    >
                        <Flag className="absolute left-4 top-1/2 -translate-y-1/2 text-gray-400 dark:text-gray-500 group-hover:text-red-500 transition-colors" size={18} />
                        <div className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl pl-12 pr-4 py-3 md:py-3.5 text-xs md:text-sm text-gray-900 dark:text-white flex items-center justify-between transition-all group-hover:border-red-500">
                            <span className="truncate">{formData.origin}</span>
                            <ChevronDown size={16} className="text-gray-400 flex-shrink-0 ml-2" />
                        </div>
                    </div>
                </div>

                <button 
                    type="submit"
                    className="w-full bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 text-white font-bold py-3.5 md:py-4 rounded-xl text-xs md:text-sm uppercase tracking-wider shadow-lg mt-2 flex items-center justify-center gap-2 transition-all transform hover:scale-[1.02]"
                >
                    <Save size={16} /> Buat Karakter
                </button>
            </form>
        </div>

        {/* Custom Country Select Modal / Bottom Sheet */}
        {showCountrySelect && (
            <div className="fixed inset-0 z-[70] flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
                <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 w-full h-[85dvh] md:h-auto md:max-h-[80dvh] md:max-w-md rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col overflow-hidden animate-in slide-in-from-bottom-full md:zoom-in-95 duration-300">
                    
                    {/* Mobile Drag Handle */}
                    <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

                    <div className="p-4 border-b border-gray-200 dark:border-white/10 flex items-center gap-3 bg-gray-50 dark:bg-[#151515]">
                        <button 
                            type="button" 
                            onClick={() => {
                                setShowCountrySelect(false);
                                setCountrySearch('');
                            }} 
                            className="p-2 -ml-2 text-gray-500 hover:text-red-500 transition-colors"
                        >
                            <X size={20} />
                        </button>
                        <div className="flex-1 relative">
                            <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={16} />
                            <input 
                                type="text" 
                                placeholder="Cari negara..." 
                                className="w-full bg-white dark:bg-black/40 border border-gray-200 dark:border-white/10 rounded-xl pl-9 pr-4 py-2.5 text-sm text-gray-900 dark:text-white focus:border-red-500 outline-none transition-all"
                                value={countrySearch}
                                onChange={e => setCountrySearch(e.target.value)}
                                autoFocus
                            />
                        </div>
                    </div>
                    
                    <div className="flex-1 overflow-y-auto p-2">
                        {filteredCountries.map(country => (
                            <button
                                key={country}
                                type="button"
                                className={`w-full text-left px-4 py-3.5 rounded-xl text-sm transition-colors flex items-center justify-between mb-1 ${
                                    formData.origin === country 
                                        ? 'bg-red-50 dark:bg-red-500/10 text-red-600 dark:text-red-400 font-bold' 
                                        : 'text-gray-700 dark:text-gray-300 hover:bg-gray-50 dark:hover:bg-white/5'
                                }`}
                                onClick={() => {
                                    handleChange('origin', country);
                                    setShowCountrySelect(false);
                                    setCountrySearch('');
                                }}
                            >
                                {country}
                                {formData.origin === country && <Check size={18} className="text-red-500" />}
                            </button>
                        ))}
                        {filteredCountries.length === 0 && (
                            <div className="p-8 text-center text-gray-500 text-sm flex flex-col items-center gap-2">
                                <AlertCircle size={24} className="text-gray-400" />
                                <p>Negara tidak ditemukan</p>
                            </div>
                        )}
                    </div>
                </div>
            </div>
        )}

        {/* Custom Gender Select Modal / Bottom Sheet */}
        {showGenderSelect && (
            <div className="fixed inset-0 z-[70] flex items-end md:items-center justify-center p-0 md:p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
                <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 w-full md:max-w-sm rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col overflow-hidden animate-in slide-in-from-bottom-full md:zoom-in-95 duration-300">
                    
                    {/* Mobile Drag Handle */}
                    <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-3 mb-1 md:hidden"></div>

                    <div className="p-4 border-b border-gray-200 dark:border-white/10 flex items-center justify-between bg-gray-50 dark:bg-[#151515]">
                        <h3 className="font-bold text-gray-900 dark:text-white">Pilih Gender</h3>
                        <button 
                            type="button" 
                            onClick={() => setShowGenderSelect(false)} 
                            className="p-2 -mr-2 text-gray-500 hover:text-red-500 transition-colors"
                        >
                            <X size={20} />
                        </button>
                    </div>
                    
                    <div className="p-2">
                        {[
                            { value: 'Male', label: 'Laki-laki' },
                            { value: 'Female', label: 'Perempuan' }
                        ].map(gender => (
                            <button
                                key={gender.value}
                                type="button"
                                className={`w-full text-left px-4 py-3.5 rounded-xl text-sm transition-colors flex items-center justify-between mb-1 ${
                                    formData.gender === gender.value 
                                        ? 'bg-red-50 dark:bg-red-500/10 text-red-600 dark:text-red-400 font-bold' 
                                        : 'text-gray-700 dark:text-gray-300 hover:bg-gray-50 dark:hover:bg-white/5'
                                }`}
                                onClick={() => {
                                    handleChange('gender', gender.value);
                                    setShowGenderSelect(false);
                                }}
                            >
                                {gender.label}
                                {formData.gender === gender.value && <Check size={18} className="text-red-500" />}
                            </button>
                        ))}
                    </div>
                </div>
            </div>
        )}
    </div>
  );
};
