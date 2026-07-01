
import React, { useState } from 'react';
import { User, Lock, Mail, ArrowRight, Loader2, ChevronLeft } from 'lucide-react';
import { InputGroup } from './InputGroup';
import { isPreviewEnv, API_URL } from '../../config';

const canUseLocalAuthPreview = () => {
    if (!import.meta.env.DEV || typeof window === 'undefined') return false;
    const host = window.location.hostname;
    return host === 'localhost' || host === '::1' || host.startsWith('127.');
};

interface RegisterFormProps {
    onSubmit: (username: string, password?: string) => void;
    setView: (view: 'login' | 'register' | 'forgot') => void;
    loading: boolean;
    onError?: (msg: string) => void;
}

export const RegisterForm: React.FC<RegisterFormProps> = ({ onSubmit, setView, loading, onError }) => {
    const [formData, setFormData] = useState({ username: '', email: '', password: '', confirm: '' });
    const [errors, setErrors] = useState({ username: '', email: '', password: '', confirm: '' });

    const [isSubmitting, setIsSubmitting] = useState(false);
    const localAuthPreview = canUseLocalAuthPreview();

    const handleChange = (field: string, value: string) => {
        setFormData(prev => ({ ...prev, [field]: value }));
        if(errors[field as keyof typeof errors]) {
            setErrors(prev => ({ ...prev, [field]: '' }));
        }
    };

    const validate = () => {
        const newErrors = { username: '', email: '', password: '', confirm: '' };
        let isValid = true;

        // Regex Rules
        const usernameRegex = /^[a-zA-Z0-9_]{4,24}$/;
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

        if(!formData.username.trim()) { 
            newErrors.username = 'Username wajib diisi'; 
            isValid = false; 
        } else if(!usernameRegex.test(formData.username)) {
            newErrors.username = '4-24 karakter, hanya huruf, angka, dan underscore';
            isValid = false;
        }

        if(!formData.email.trim()) { 
            newErrors.email = 'Email wajib diisi'; 
            isValid = false; 
        } else if(!emailRegex.test(formData.email)) {
            newErrors.email = 'Format email tidak valid';
            isValid = false;
        }

        if(!formData.password) { 
            newErrors.password = 'Password wajib diisi'; 
            isValid = false; 
        } else if(formData.password.length < 4 || formData.password.length > 32) {
            newErrors.password = 'Password harus 4-32 karakter';
            isValid = false;
        }

        if(formData.password !== formData.confirm) { 
            newErrors.confirm = 'Password tidak cocok'; 
            isValid = false; 
        }

        setErrors(newErrors);
        return isValid;
    };

    const handleSubmit = async (e: React.FormEvent) => {
        e.preventDefault();
        if(validate()) {
            setIsSubmitting(true);
            try {
                if (isPreviewEnv() || localAuthPreview) {
                    setTimeout(() => {
                        setIsSubmitting(false);
                        const isTakenUsername = formData.username.toLowerCase() === 'admin' || formData.username.toLowerCase() === 'player';
                        const isTakenEmail = formData.email.toLowerCase() === 'admin@admin.com' || formData.email.toLowerCase() === 'player@player.com';
                        
                        if (!localAuthPreview && (isTakenUsername || isTakenEmail)) {
                            const msg = isTakenUsername ? 'Username sudah terdaftar.' : 'Email sudah terdaftar.';
                            if (onError) onError(msg);
                            setErrors({
                                username: '', email: '', password: '', confirm: '',
                                ...(isTakenUsername ? { username: msg } : { email: msg })
                            });
                            return;
                        }
                        onSubmit(formData.email, formData.password);
                    }, 1000);
                    return;
                }

                const apiUrl = `${API_URL}/register.php`;

                const formDataToSend = new FormData();
                formDataToSend.append('action', 'register');
                formDataToSend.append('username', formData.username);
                formDataToSend.append('email', formData.email);
                formDataToSend.append('password', formData.password);

                const res = await fetch(apiUrl, {
                    method: 'POST',
                    credentials: 'include',
                    body: formDataToSend
                });

                if(!res.ok) throw new Error('Network error');
                
                const data = await res.json();
                setIsSubmitting(false);
                
                if(data.status === 'success' || data.status === 'success_verify') {
                    // Berhasil mendaftar, lempar EMAIL nya agar layar verifikasi menampilkannya
                    onSubmit(formData.email, formData.password);
                } else {
                    const msg = data.message || 'Pendaftaran gagal.';
                    if (onError) onError(msg);
                    
                    const newErrors = { username: '', email: '', password: '', confirm: '' };
                    if (msg.toLowerCase().includes('email')) {
                        newErrors.email = msg;
                    } else {
                        newErrors.username = msg;
                    }
                    
                    // Tetap tambahkan pesan error kecil di form untuk penekanan
                    setErrors(newErrors);
                }
            } catch (err) {
                 console.error("Register fetch error:", err);
                 setIsSubmitting(false);
                 const errorMessage = err instanceof Error ? err.message : String(err);
                 // Fallback if API fail
                 if (onError) {
                     if (errorMessage === "Failed to fetch") {
                         onError(`Server lokal tidak merespon (API URL: ${API_URL}). Pastikan server PHP jalan.`);
                     } else {
                         onError(`Gagal menghubungi server. Details: ${errorMessage}`);
                     }
                 }
                 setErrors({
                    ...errors,
                    username: 'Network error',
                 });
            }
        }
    };

    return (
        <div className="animate-auth-slide-up">
            <div className="text-center mb-5">
               <span className="ph-eyebrow block mb-1.5">Account Enrollment</span>
               <h2 className="text-[18px] md:text-[22px] font-extrabold text-gray-950 mb-1 tracking-tight leading-tight">
                 Buat Akun Baru
               </h2>
               <p className="text-gray-500 text-[11.5px] md:text-[12.5px] leading-[1.5]">
                 Mulai perjalanan roleplay Anda di Pahlawan Roleplay.
               </p>
            </div>

            <div className="mb-3 rounded-lg border border-ph-gold-600/20 bg-ph-gold-600/[0.08] px-3 py-2 text-[10.5px] md:text-[11px] leading-relaxed text-gray-600">
                <div className="flex items-start gap-2">
                    <div className="shrink-0 mt-0.5 w-4 h-4 rounded-full bg-ph-gold-600/12 flex items-center justify-center">
                        <span className="text-[9px] font-black text-ph-gold-700">!</span>
                    </div>
                    <span>Gunakan email aktif untuk menerima <b className="text-gray-950">kode OTP</b> dan menjaga keamanan akun UCP Anda.</span>
                </div>
            </div>

            <form onSubmit={handleSubmit} className="space-y-2.5" noValidate>
                <InputGroup
                    icon={User}
                    type="text"
                    placeholder="Username"
                    autoComplete="username"
                    value={formData.username}
                    onChange={e => handleChange('username', e.target.value)}
                    error={errors.username}
                    hint="4-24 karakter: huruf, angka, underscore."
                />

                <InputGroup
                    icon={Mail}
                    type="email"
                    placeholder="Alamat Email"
                    autoComplete="email"
                    value={formData.email}
                    onChange={e => handleChange('email', e.target.value)}
                    error={errors.email}
                    hint="OTP verifikasi akan dikirim ke email ini."
                />

                <InputGroup
                    icon={Lock}
                    type="password"
                    placeholder="Password"
                    autoComplete="new-password"
                    value={formData.password}
                    onChange={e => handleChange('password', e.target.value)}
                    error={errors.password}
                    hint="Gunakan 4-32 karakter sesuai aturan server."
                />

                <InputGroup
                    icon={Lock}
                    type="password"
                    placeholder="Konfirmasi Password"
                    autoComplete="new-password"
                    value={formData.confirm}
                    onChange={e => handleChange('confirm', e.target.value)}
                    error={errors.confirm}
                />

                <button
                    type="submit"
                    disabled={loading || isSubmitting}
                    className="ph-btn-primary w-full py-2.5 flex items-center justify-center group"
                >
                    {loading || isSubmitting ? <Loader2 className="animate-spin" size={20} /> : (
                        <span className="flex items-center text-sm font-bold tracking-wide">
                            Daftar Akun
                            <ArrowRight size={17} className="ml-2 group-hover:translate-x-1 transition-transform" />
                        </span>
                    )}
                </button>
            </form>

            <div className="mt-4 text-center">
                 <button onClick={() => setView('login')} className="text-gray-500 hover:text-ph-crimson-700 text-xs flex min-h-11 items-center justify-center w-full transition-colors font-semibold tracking-wide py-2 group">
                    <ChevronLeft size={14} className="mr-1 group-hover:-translate-x-0.5 transition-transform" /> Kembali ke Login
                 </button>
            </div>
        </div>
    );
};
