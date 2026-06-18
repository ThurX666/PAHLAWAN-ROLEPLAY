
import React, { Suspense, lazy, useState, useMemo, useRef, useEffect } from 'react';
import { X, Upload, Info, Copy, CreditCard, Wallet, ShoppingCart, AlertTriangle, AlertCircle, Smartphone, ChevronDown, Check, Zap, Camera } from 'lucide-react';

const ImageCropModal = lazy(() => import('../ui/ImageCropModal').then(module => ({ default: module.ImageCropModal })));

const CropperFallback: React.FC = () => (
    <div className="fixed inset-0 z-[70] flex items-center justify-center bg-black/80 backdrop-blur-sm p-4">
        <div className="bg-white dark:bg-[#1a1a1a] rounded-2xl w-full max-w-md border border-gray-200 dark:border-white/10 p-8 text-center shadow-2xl">
            <div className="mx-auto mb-4 h-10 w-10 animate-spin rounded-full border-2 border-gray-300 border-t-gray-900 dark:border-white/20 dark:border-t-white" />
            <p className="text-[10px] font-bold uppercase tracking-[0.3em] text-gray-500 dark:text-gray-400">
                Memuat Cropper...
            </p>
        </div>
    </div>
);

interface PaymentModalProps {
    selectedPkg: any;
    onClose: () => void;
    onSubmit: (formData: any) => void;
    isSubmitting: boolean;
}

const PAYMENT_CHANNELS: Record<string, { number: string; holder: string; icon: any; color: string }> = {
    'BRI': { number: '1234 0100 5678 505', holder: 'PAHLAWAN RP FOUNDATION', icon: CreditCard, color: 'text-blue-700' },
    'SeaBank': { number: '9012 3456 7890', holder: 'Admin PR (Ucok)', icon: CreditCard, color: 'text-orange-500' },
    'DANA': { number: '0812-3456-7890', holder: 'Admin PR (Ucok)', icon: Wallet, color: 'text-blue-500' },
    'Gopay': { number: '0812-3456-7890', holder: 'Admin PR (Ucok)', icon: Wallet, color: 'text-green-500' },
    'OVO': { number: '0812-3456-7890', holder: 'Admin PR (Ucok)', icon: Wallet, color: 'text-purple-500' },
    'Pulsa Tsel': { number: '0812-3456-7890', holder: 'Admin PR (Ucok)', icon: Smartphone, color: 'text-red-600' },
    'Pulsa Tri': { number: '0896-1234-5678', holder: 'Admin PR (Ucok)', icon: Smartphone, color: 'text-white' },
};

const PAYMENT_GROUPS = [
    { label: "Bank Transfer", options: ["BRI", "SeaBank"] },
    { label: "E-Wallet", options: ["DANA", "Gopay", "OVO"] },
    { label: "Pulsa (Rate 0.85)", options: ["Pulsa Tsel", "Pulsa Tri"] },
];

export const PaymentModal: React.FC<PaymentModalProps> = ({ selectedPkg, onClose, onSubmit, isSubmitting }) => {
    const [paymentProof, setPaymentProof] = useState<string | null>(null);
    const [previewUrl, setPreviewUrl] = useState<string | null>(null);
    const [senderName, setSenderName] = useState('');
    const [paymentMethod, setPaymentMethod] = useState('BRI');
    const [isDropdownOpen, setIsDropdownOpen] = useState(false);
    const [errors, setErrors] = useState<Record<string, string>>({});
    const dropdownRef = useRef<HTMLDivElement>(null);
    const fileInputRef = useRef<HTMLInputElement>(null);

    // Cropper State
    const [imageSrc, setImageSrc] = useState<string | null>(null);
    const [isCropping, setIsCropping] = useState(false);

    // Close dropdown when clicking outside
    useEffect(() => {
        const handleClickOutside = (event: MouseEvent) => {
            if (dropdownRef.current && !dropdownRef.current.contains(event.target as Node)) {
                setIsDropdownOpen(false);
            }
        };
        document.addEventListener('mousedown', handleClickOutside);
        return () => document.removeEventListener('mousedown', handleClickOutside);
    }, []);

    // --- LOGIC PERHITUNGAN BIAYA ADMIN & RATE PULSA ---
    const { rawPrice, feeAmount, totalPrice, displayFee, displayTotal, isPulsa, feeLabel } = useMemo(() => {
        // Hapus 'Rp ' dan '.' untuk parsing angka
        const raw = parseInt(selectedPkg.price.replace(/[^0-9]/g, ''), 10);
        const isPulsaMethod = paymentMethod.includes('Pulsa');
        
        let fee = 0;
        let total = raw;
        let label = "Biaya Operasional";

        if (isPulsaMethod) {
            // Logic Rate 0.85: Total = Harga / 0.85
            // Pembulatan ke ribuan terdekat (misal 588.236 -> 588.000)
            const priceWithRate = raw / 0.85; 
            total = Math.round(priceWithRate / 1000) * 1000;
            fee = total - raw; // Selisihnya dianggap biaya konversi rate
            label = "Biaya Convert Rate (0.85)";
        } else {
            // Logic Bank/E-Wallet: Fee 5% jika harga >= 100.000
            if (raw >= 100000) {
                fee = raw * 0.05; // 5% Fee
            }
            total = raw + fee;
        }

        const formatter = new Intl.NumberFormat('id-ID', { style: 'currency', currency: 'IDR', minimumFractionDigits: 0 });

        return {
            rawPrice: raw,
            feeAmount: fee,
            totalPrice: total,
            displayFee: fee > 0 ? formatter.format(fee) : 'GRATIS',
            displayTotal: formatter.format(total),
            isPulsa: isPulsaMethod,
            feeLabel: label
        };
    }, [selectedPkg.price, paymentMethod]);

    const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const file = e.target.files?.[0];
        if (file) {
            const reader = new FileReader();
            reader.addEventListener('load', () => {
                setImageSrc(reader.result?.toString() || null);
                setIsCropping(true);
            });
            reader.readAsDataURL(file);
        }
        if (fileInputRef.current) {
            fileInputRef.current.value = '';
        }
    };

    const handleCropConfirm = async (croppedImage: string) => {
        try {
            setPaymentProof(croppedImage);
            setPreviewUrl(croppedImage);
            if(errors.proof) setErrors(prev => ({...prev, proof: ''}));
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

    const validate = () => {
        const newErrors: Record<string, string> = {};
        if (!senderName.trim()) newErrors.sender = "Wajib diisi";
        if (!paymentProof) newErrors.proof = "Bukti wajib diupload";
        
        setErrors(newErrors);
        return Object.keys(newErrors).length === 0;
    };

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        if(validate()) {
            onSubmit({ 
                paymentProof, 
                senderName, 
                paymentMethod, 
                packageName: selectedPkg.name || `${selectedPkg.amount} Gold`, 
                amount: selectedPkg.amount, 
                price: displayTotal // Simpan harga total ke history
            });
        }
    };

    const copyToClipboard = (text: string) => {
        navigator.clipboard.writeText(text.replace(/-/g, '').replace(/ /g, ''));
        alert(`Nomor ${text} disalin ke clipboard!`);
    };

  return (
      <div className="fixed inset-0 z-[60] flex items-end md:items-center justify-center bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
          {/* Cropper Modal */}
          {isCropping && imageSrc && (
              <Suspense fallback={<CropperFallback />}>
                  <ImageCropModal
                      aspect={3 / 4}
                      imageSrc={imageSrc}
                      title="Sesuaikan Bukti Transfer"
                      onCancel={handleCropCancel}
                      onConfirm={handleCropConfirm}
                  />
              </Suspense>
          )}

          {/* Mobile: Bottom Sheet, Desktop: Centered Modal */}
          <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 w-full md:max-w-2xl rounded-t-3xl md:rounded-2xl shadow-2xl flex flex-col md:flex-row overflow-hidden max-h-[95dvh] animate-[slideUp_0.3s_ease-out] md:animate-none relative">
              
              {/* Mobile Drag Handle */}
              <div className="w-full flex justify-center pt-3 pb-1 md:hidden absolute top-0 left-0 z-50 bg-white dark:bg-[#121212] rounded-t-3xl">
                  <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full"></div>
              </div>

              {/* Left Column: Summary & Info (Desktop) */}
              <div className="w-full md:w-5/12 bg-gray-50 dark:bg-[#0f0f0f] border-b md:border-b-0 md:border-r border-gray-200 dark:border-white/5 p-4 md:p-6 flex flex-col shrink-0 pt-8 md:pt-6 overflow-y-auto custom-scrollbar">
                  <div className="flex justify-between items-center mb-4 md:mb-6 md:hidden">
                        <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase italic">Konfirmasi</h3>
                        <button onClick={onClose} className="p-2 bg-gray-100 dark:bg-white/5 rounded-full"><X size={18} className="text-gray-500 hover:text-red-500" /></button>
                  </div>

                  <div className="text-center mb-2 mt-0 md:mt-10 md:mb-6 flex flex-row md:flex-col items-center gap-3 md:gap-0 px-1 md:px-0">
                        {/* Mobile: Smaller Icon/Card */}
                        <div className="w-12 h-12 md:w-20 md:h-20 bg-white dark:bg-white/5 rounded-xl md:rounded-2xl flex items-center justify-center md:mx-auto md:mb-4 shadow-sm border border-gray-100 dark:border-white/10 relative shrink-0">
                            <div className="absolute -top-1 -right-1 md:-top-2 md:-right-2 bg-red-600 text-white rounded-full p-1 md:p-1.5 shadow-md">
                                <ShoppingCart size={10} className="md:w-[14px] md:h-[14px]" />
                            </div>
                            <span className="text-xl md:text-4xl">🛒</span>
                        </div>
                        <div className="text-left md:text-center">
                            <h4 className="text-[9px] md:text-xs font-bold text-gray-400 uppercase tracking-widest mb-0.5">Item Pesanan</h4>
                            <p className="text-sm md:text-2xl font-black text-gray-900 dark:text-white uppercase italic leading-tight">{selectedPkg.name || `${selectedPkg.amount} Gold Coins`}</p>
                            {selectedPkg.duration && <span className="inline-block mt-1 md:mt-2 text-[8px] md:text-[10px] bg-red-100 dark:bg-red-900/30 text-red-600 dark:text-red-400 px-2 py-0.5 md:px-3 md:py-1 rounded-full font-bold uppercase">{selectedPkg.duration}</span>}
                        </div>
                  </div>

                  <div className="space-y-1.5 md:space-y-3 mt-auto mb-2 md:mb-6 bg-white dark:bg-black/10 p-2 rounded-lg md:bg-transparent md:p-0 border border-gray-100 dark:border-white/5 md:border-none">
                        <div className="flex justify-between items-center p-1 md:p-3 md:bg-white md:dark:bg-black/20 md:rounded-lg md:border md:border-gray-200 md:dark:border-white/5">
                            <span className="text-[10px] md:text-xs text-gray-500 font-bold uppercase">Harga</span>
                            <span className="text-[10px] md:text-sm font-black text-gray-900 dark:text-white">{selectedPkg.price}</span>
                        </div>
                        <div className="flex justify-between items-center p-1 md:p-3 md:bg-white md:dark:bg-black/20 md:rounded-lg md:border md:border-gray-200 md:dark:border-white/5">
                            <div className="flex flex-col text-left">
                                <span className="text-[10px] md:text-xs text-gray-500 font-bold uppercase">{feeLabel}*</span>
                            </div>
                            <span className={`text-[10px] md:text-sm font-black ${feeAmount > 0 ? 'text-gray-900 dark:text-gray-300' : 'text-green-500'}`}>
                                {displayFee}
                            </span>
                        </div>
                        <div className="border-t border-dashed border-gray-200 dark:border-white/10 pt-2 md:pt-4 flex justify-between items-center mt-1">
                            <span className="text-[10px] md:text-sm text-gray-900 dark:text-white font-black uppercase">Total</span>
                            <div className="flex items-center gap-2">
                                <span className="text-lg md:text-2xl font-black text-red-600">{displayTotal}</span>
                                <button
                                    type="button"
                                    onClick={() => {
                                        navigator.clipboard.writeText(totalPrice.toString());
                                        alert(`Nominal Rp ${totalPrice.toLocaleString('id-ID')} disalin!`);
                                    }}
                                    className="p-1.5 md:p-2 bg-red-50 dark:bg-red-900/20 text-red-600 hover:bg-red-100 dark:hover:bg-red-900/30 rounded-lg transition-colors border border-red-100 dark:border-red-900/30 active:scale-95"
                                    title="Salin Nominal Transfer"
                                >
                                    <Copy size={14} className="md:w-4 md:h-4" />
                                </button>
                            </div>
                        </div>
                  </div>
                  
                  {isPulsa ? (
                      <div className="bg-orange-50 dark:bg-orange-900/10 p-2 md:p-3 rounded-lg border border-orange-100 dark:border-orange-900/20 flex gap-2 items-start mb-1">
                          <Zap className="text-orange-500 shrink-0 mt-0.5" size={12} />
                          <p className="text-[8px] md:text-[10px] text-orange-800 dark:text-orange-300 leading-relaxed text-left">
                              *Via Pulsa kena <strong>Rate 0.85</strong>.
                          </p>
                      </div>
                  ) : null}

                  <div className="bg-blue-50 dark:bg-blue-900/10 p-3 rounded-lg border border-blue-100 dark:border-blue-900/20 text-[10px] text-blue-700 dark:text-blue-300 leading-relaxed text-center hidden md:block">
                      <strong>PENTING:</strong> Mohon transfer sesuai nominal <strong>TOTAL TRANSFER</strong> agar sistem dapat memverifikasi otomatis.
                  </div>
              </div>

              {/* Right Column: Form */}
              <div className="w-full md:w-7/12 flex flex-col h-full bg-white dark:bg-[#121212] overflow-hidden">
                  <div className="hidden md:flex justify-between items-center p-6 border-b border-gray-200 dark:border-white/5 shrink-0">
                      <div>
                        <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase italic">Selesaikan Pembayaran</h3>
                        <p className="text-[10px] text-gray-500">Isi formulir di bawah ini untuk konfirmasi.</p>
                      </div>
                      <button onClick={onClose}><X size={24} className="text-gray-400 hover:text-red-500 transition-colors" /></button>
                  </div>

                  {/* Scrollable Form Area */}
                  <div className="flex-1 p-3 md:p-6 overflow-y-auto custom-scrollbar">
                        <form id="pay-form" onSubmit={handleSubmit} className="space-y-3 md:space-y-5 pb-2" noValidate>
                            <div>
                                <label className="text-[10px] font-bold text-gray-500 uppercase mb-1 md:mb-1.5 block">1. Pilih Metode Transfer</label>
                                
                                {/* Custom Dropdown Trigger */}
                                <div className="relative" ref={dropdownRef}>
                                    <div 
                                        onClick={() => setIsDropdownOpen(!isDropdownOpen)}
                                        className={`w-full bg-gray-50 dark:bg-black/20 border cursor-pointer rounded-xl pl-9 md:pl-10 pr-8 py-2.5 md:py-3.5 flex items-center justify-between transition-all ${isDropdownOpen ? 'border-red-500 ring-1 ring-red-500/20' : 'border-gray-200 dark:border-white/10 hover:border-gray-300 dark:hover:border-white/20'}`}
                                    >
                                        <div className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-500">
                                            {React.createElement(PAYMENT_CHANNELS[paymentMethod]?.icon || CreditCard, { size: 16, className: isDropdownOpen ? 'text-red-500' : '' })}
                                        </div>
                                        <span className="text-xs md:text-sm font-bold text-gray-900 dark:text-white">
                                            {paymentMethod}
                                        </span>
                                        <div className="absolute right-3 top-1/2 -translate-y-1/2 text-gray-500">
                                            <ChevronDown size={14} className={`transition-transform duration-200 ${isDropdownOpen ? 'rotate-180' : ''}`} />
                                        </div>
                                    </div>

                                    {/* Custom Dropdown Menu */}
                                    {isDropdownOpen && (
                                        <div className="absolute top-full left-0 w-full mt-2 bg-white dark:bg-[#151515] border border-gray-200 dark:border-white/10 rounded-xl shadow-xl z-50 overflow-hidden animate-[fadeIn_0.1s_ease-out] max-h-56 overflow-y-auto custom-scrollbar">
                                            {PAYMENT_GROUPS.map((group, groupIdx) => (
                                                <div key={group.label} className={groupIdx > 0 ? 'border-t border-gray-100 dark:border-white/5' : ''}>
                                                    <div className="px-3 md:px-4 py-1.5 md:py-2 bg-gray-50 dark:bg-white/5 text-[9px] font-bold text-gray-400 uppercase tracking-widest sticky top-0 backdrop-blur-sm">
                                                        {group.label}
                                                    </div>
                                                    <div>
                                                        {group.options.map(opt => (
                                                            <div 
                                                                key={opt}
                                                                onClick={() => {
                                                                    setPaymentMethod(opt);
                                                                    setIsDropdownOpen(false);
                                                                }}
                                                                className={`px-3 md:px-4 py-2.5 md:py-3 cursor-pointer flex items-center justify-between text-xs transition-colors ${paymentMethod === opt ? 'bg-red-50 dark:bg-red-900/20 text-red-600' : 'text-gray-700 dark:text-gray-300 hover:bg-gray-100 dark:hover:bg-white/5'}`}
                                                            >
                                                                <span className="font-bold">{opt}</span>
                                                                {paymentMethod === opt && <Check size={14} />}
                                                            </div>
                                                        ))}
                                                    </div>
                                                </div>
                                            ))}
                                        </div>
                                    )}
                                </div>
                            </div>

                            {/* Dynamic Payment Details Info */}
                            {paymentMethod && PAYMENT_CHANNELS[paymentMethod] && (
                                <div className="bg-gray-50 dark:bg-[#1a1a1a] border border-gray-200 dark:border-white/10 rounded-xl p-3 md:p-4 relative group animate-[fadeIn_0.3s_ease-out]">
                                    <p className="text-[9px] md:text-[10px] text-gray-500 font-bold uppercase mb-2 flex items-center gap-1">
                                        <Info size={10} /> Rekening Tujuan
                                    </p>
                                    <div className="flex items-center justify-between">
                                        <div>
                                            <div className={`text-sm md:text-lg font-black text-gray-900 dark:text-white flex items-center gap-2 ${PAYMENT_CHANNELS[paymentMethod].color}`}>
                                                {React.createElement(PAYMENT_CHANNELS[paymentMethod].icon, { size: 18 })}
                                                <span className="font-mono tracking-wider">{PAYMENT_CHANNELS[paymentMethod].number}</span>
                                            </div>
                                            <p className="text-[9px] md:text-[10px] text-gray-500 font-bold mt-1 uppercase tracking-wide">A.N {PAYMENT_CHANNELS[paymentMethod].holder}</p>
                                        </div>
                                        <button
                                            type="button"
                                            onClick={() => copyToClipboard(PAYMENT_CHANNELS[paymentMethod].number)}
                                            className="p-2 md:p-2.5 bg-white dark:bg-black/20 hover:bg-gray-200 dark:hover:bg-white/10 rounded-lg text-gray-500 hover:text-black dark:hover:text-white transition-colors shadow-sm border border-gray-200 dark:border-white/5"
                                            title="Salin Nomor"
                                        >
                                            <Copy size={14} className="md:w-4 md:h-4" />
                                        </button>
                                    </div>
                                    <div className="mt-2 md:mt-3 pt-2 border-t border-dashed border-gray-200 dark:border-white/10">
                                        <p className="text-[10px] md:text-[10px] text-red-500 font-bold uppercase animate-pulse">
                                            Transfer Tepat: {displayTotal}
                                        </p>
                                    </div>
                                </div>
                            )}

                            <div>
                                <div className="flex justify-between items-center mb-1 md:mb-2">
                                    <label className={`text-[10px] font-bold uppercase transition-colors ${errors.sender ? 'text-red-500' : 'text-gray-500'}`}>2. Informasi Pengirim</label>
                                    {errors.sender && <span className="text-[9px] text-red-500 font-bold animate-pulse flex items-center gap-1"><AlertCircle size={10}/> {errors.sender}</span>}
                                </div>
                                <input 
                                    type="text" 
                                    value={senderName} 
                                    onChange={e => {
                                        setSenderName(e.target.value);
                                        if(errors.sender) setErrors(prev => {
                                            const n = {...prev};
                                            delete n.sender;
                                            return n;
                                        });
                                    }} 
                                    className={`w-full bg-gray-50 dark:bg-[#0a0a0a] border rounded-xl p-2.5 md:p-3.5 text-xs text-gray-900 dark:text-white outline-none transition-all font-medium ${errors.sender ? 'border-red-500 focus:border-red-600 bg-red-50/10' : 'border-gray-200 dark:border-white/10 focus:border-red-500'}`} 
                                    placeholder="Nama Pemilik Rekening Anda" 
                                />
                            </div>

                            <div>
                                <div className="flex justify-between items-center mb-1 md:mb-2">
                                    <label className={`text-[10px] font-bold uppercase transition-colors ${errors.proof ? 'text-red-500' : 'text-gray-500'}`}>3. Bukti Transfer</label>
                                    {errors.proof && <span className="text-[9px] text-red-500 font-bold animate-pulse flex items-center gap-1"><AlertCircle size={10}/> {errors.proof}</span>}
                                </div>
                                <div className={`border-2 border-dashed rounded-xl p-4 md:p-6 text-center relative transition-all bg-gray-50 dark:bg-[#0a0a0a] group ${errors.proof ? 'border-red-500 bg-red-50/10' : 'border-gray-300 dark:border-white/10 hover:border-red-500/50 hover:bg-red-50/10'}`}>
                                    <input 
                                        type="file" 
                                        accept="image/*" 
                                        onChange={handleFileChange} 
                                        ref={fileInputRef}
                                        className="absolute inset-0 w-full h-full opacity-0 cursor-pointer" 
                                    />
                                    <div className={`flex flex-col items-center justify-center transition-colors ${errors.proof ? 'text-red-500' : 'text-gray-500 group-hover:text-red-500'}`}>
                                        {previewUrl ? (
                                            <div className="relative">
                                                <img src={previewUrl} className="h-24 md:h-32 object-contain rounded-lg shadow-md" />
                                                <div className="absolute inset-0 bg-black/50 flex items-center justify-center text-white opacity-0 hover:opacity-100 transition-opacity rounded-lg text-xs font-bold uppercase">Ganti Gambar</div>
                                            </div>
                                        ) : (
                                            <>
                                                <Upload size={24} className="mb-2 md:w-8 md:h-8" />
                                                <p className="text-[10px] md:text-xs font-bold uppercase">Klik untuk upload bukti</p>
                                                <p className="text-[8px] md:text-[10px] mt-1 opacity-70">JPG, PNG, PDF (Max 2MB)</p>
                                            </>
                                        )}
                                    </div>
                                </div>
                            </div>
                            
                            {/* Mobile Button: Inside Form Flow */}
                            <button 
                                type="submit"
                                disabled={isSubmitting} 
                                className="md:hidden w-full bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 text-white font-bold py-3 rounded-lg text-xs uppercase shadow-lg shadow-red-500/20 disabled:opacity-50 disabled:cursor-not-allowed tracking-widest transition-all transform active:scale-[0.98] flex items-center justify-center gap-2 mt-4"
                            >
                                {isSubmitting ? 'Memproses...' : <>Kirim Konfirmasi <CreditCard size={14} /></>}
                            </button>

                            {/* Spacer */}
                            <div className="h-2 md:h-4"></div>
                        </form>
                  </div>

                  {/* Desktop Footer Action: Fixed at bottom */}
                  <div className="hidden md:block p-6 border-t border-gray-200 dark:border-white/5 bg-gray-50 dark:bg-[#151515] shrink-0 z-20 relative pb-6">
                      <button form="pay-form" disabled={isSubmitting} className="w-full bg-gradient-to-r from-red-600 to-red-500 hover:from-red-500 hover:to-red-400 text-white font-bold py-4 rounded-xl text-sm uppercase shadow-lg shadow-red-500/20 disabled:opacity-50 disabled:cursor-not-allowed tracking-widest transition-all transform active:scale-[0.98] flex items-center justify-center gap-2">
                          {isSubmitting ? 'Memproses...' : <>Kirim Konfirmasi <CreditCard size={16} className="w-4 h-4" /></>}
                      </button>
                  </div>
              </div>
          </div>
      </div>
  );
};
