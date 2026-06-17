
import React, { useState } from 'react';
import { User, Lock, Mail, ArrowRight, Loader2, ChevronLeft } from 'lucide-react';
import { InputGroup } from './InputGroup';
import { isPreviewEnv, API_URL } from '../../config';

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
            newErrors.username = 'Username required'; 
            isValid = false; 
        } else if(!usernameRegex.test(formData.username)) {
            newErrors.username = '4-24 characters, only letters, numbers, and underscore';
            isValid = false;
        }

        if(!formData.email.trim()) { 
            newErrors.email = 'Email required'; 
            isValid = false; 
        } else if(!emailRegex.test(formData.email)) {
            newErrors.email = 'Invalid email format (e.g. name@domain.com)';
            isValid = false;
        }

        if(!formData.password) { 
            newErrors.password = 'Password required'; 
            isValid = false; 
        } else if(formData.password.length < 4 || formData.password.length > 32) {
            newErrors.password = 'Password must be 4-32 characters';
            isValid = false;
        }

        if(formData.password !== formData.confirm) { 
            newErrors.confirm = 'Passwords do not match'; 
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
                if (isPreviewEnv()) {
                    setTimeout(() => {
                        setIsSubmitting(false);
                        const isTakenUsername = formData.username.toLowerCase() === 'admin' || formData.username.toLowerCase() === 'player';
                        const isTakenEmail = formData.email.toLowerCase() === 'admin@admin.com' || formData.email.toLowerCase() === 'player@player.com';
                        
                        if (isTakenUsername || isTakenEmail) {
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
        <div className="animate-[fadeIn_0.3s_ease-out]">
            <div className="text-center mb-8">
               <h2 className="text-3xl font-black text-gray-900 dark:text-white mb-2 uppercase italic tracking-tighter">
                 Join the City
               </h2>
               <p className="text-gray-500 text-xs uppercase tracking-widest font-bold">
                 Start your new life
               </p>
            </div>

            <form onSubmit={handleSubmit} className="space-y-4" noValidate>
                <InputGroup 
                    icon={User} 
                    type="text" 
                    placeholder="Username" 
                    autoComplete="username"
                    value={formData.username} 
                    onChange={e => handleChange('username', e.target.value)} 
                    error={errors.username}
                />

                <InputGroup 
                    icon={Mail} 
                    type="email" 
                    placeholder="Email Address" 
                    autoComplete="email"
                    value={formData.email}
                    onChange={e => handleChange('email', e.target.value)}
                    error={errors.email}
                />
                
                <InputGroup 
                    icon={Lock} 
                    type="password" 
                    placeholder="Password" 
                    autoComplete="new-password"
                    value={formData.password}
                    onChange={e => handleChange('password', e.target.value)}
                    error={errors.password}
                />
                
                <InputGroup 
                    icon={Lock} 
                    type="password" 
                    placeholder="Confirm Password" 
                    autoComplete="new-password"
                    value={formData.confirm}
                    onChange={e => handleChange('confirm', e.target.value)}
                    error={errors.confirm}
                />

                <button 
                    type="submit" 
                    disabled={loading || isSubmitting}
                    className="w-full bg-gradient-to-r from-red-600 to-red-700 hover:from-red-500 hover:to-red-600 text-white font-bold py-4 rounded-xl transition-all transform hover:scale-[1.02] active:scale-[0.98] shadow-lg shadow-red-600/20 disabled:opacity-70 disabled:cursor-not-allowed flex items-center justify-center group mt-6"
                >
                    {loading || isSubmitting ? <Loader2 className="animate-spin" size={20} /> : (
                        <span className="flex items-center text-sm uppercase tracking-widest">
                            Register Account
                            <ArrowRight size={16} className="ml-2 group-hover:translate-x-1 transition-transform" />
                        </span>
                    )}
                </button>
            </form>

            <div className="mt-8 text-center">
                 <button onClick={() => setView('login')} className="text-gray-500 dark:text-gray-400 hover:text-gray-900 dark:hover:text-white text-xs flex items-center justify-center w-full transition-colors uppercase font-bold tracking-wider py-4">
                    <ChevronLeft size={14} className="mr-1" /> Back to Login
                 </button>
            </div>
        </div>
    );
};
