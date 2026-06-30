
import React, { useState } from 'react';
import { User, Lock, ArrowRight, Loader2 } from 'lucide-react';
import { InputGroup } from './InputGroup';

interface LoginFormProps {
    onSubmit: (username: string, password?: string) => void;
    setView: (view: 'login' | 'register' | 'forgot') => void;
    loading: boolean;
}

export const LoginForm: React.FC<LoginFormProps> = ({ onSubmit, setView, loading }) => {
    const [identifier, setIdentifier] = useState('');
    const [password, setPassword] = useState('');
    const [errors, setErrors] = useState({ identifier: '', password: '' });

    const validate = () => {
        const newErrors = { identifier: '', password: '' };
        let isValid = true;

        if(!identifier.trim()) { newErrors.identifier = 'Username atau email wajib diisi'; isValid = false; }
        if(!password.trim()) { newErrors.password = 'Password wajib diisi'; isValid = false; }

        setErrors(newErrors);
        return isValid;
    };

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        if(validate()) {
            onSubmit(identifier, password);
        }
    };

    return (
        <div className="animate-auth-slide-up">
            <div className="text-center mb-3">
               <span className="ph-eyebrow mb-2">Roleplay Identity</span>
                <h2 className="text-[20px] md:text-[24px] font-extrabold text-gray-950 mb-1 tracking-tight leading-tight">
                  Selamat Datang
                </h2>
               <p className="text-gray-500 text-[12px] md:text-[13px] leading-relaxed">
                  Masuk ke UCP Pahlawan Roleplay<br className="hidden md:block"/> untuk mengelola akses akun Anda.
                </p>
            </div>

            <div className="mb-3 grid grid-cols-2 gap-2 text-left">
                <div className="rounded-xl border border-gray-200/80 bg-gray-50/80 px-3 py-2">
                    <p className="text-[9px] font-black uppercase tracking-[0.16em] text-gray-500">Akses</p>
                    <p className="mt-0.5 text-xs font-bold text-gray-900">UCP Warga</p>
                </div>
                <div className="rounded-xl border border-ph-gold-600/20 bg-ph-gold-600/[0.06] px-3 py-2">
                    <p className="text-[9px] font-black uppercase tracking-[0.16em] text-ph-gold-700">Secure</p>
                    <p className="mt-0.5 text-xs font-bold text-gray-900">OTP Guard</p>
                </div>
            </div>

            <form onSubmit={handleSubmit} className="space-y-2.5" noValidate>
                <InputGroup
                    icon={User}
                    type="text"
                    placeholder="Username atau Email"
                    autoComplete="username"
                    value={identifier}
                    onChange={e => {
                        setIdentifier(e.target.value);
                        if(errors.identifier) setErrors(prev => ({...prev, identifier: ''}));
                    }}
                    error={errors.identifier}
                />

                <InputGroup
                    icon={Lock}
                    type="password"
                    placeholder="Password"
                    autoComplete="current-password"
                    value={password}
                    onChange={e => {
                        setPassword(e.target.value);
                        if(errors.password) setErrors(prev => ({...prev, password: ''}));
                    }}
                    error={errors.password}
                />

                <div className="flex justify-end mt-0.5 mb-2">
                    <button
                        type="button"
                        onClick={() => setView('forgot')}
                        className="inline-flex min-h-11 items-center gap-1 rounded-md px-1 text-xs text-gray-500 hover:text-ph-crimson-700 transition-colors font-semibold"
                    >
                        Lupa Password?
                    </button>
                </div>

                <button
                    type="submit"
                    disabled={loading}
                    className="ph-btn-primary w-full py-3 mt-1 flex items-center justify-center group"
                >
                    {loading ? <Loader2 className="animate-spin" size={20} /> : (
                        <span className="flex items-center text-sm font-bold tracking-wide">
                            Masuk ke Akun
                            <ArrowRight size={17} className="ml-2 group-hover:translate-x-1 transition-transform" />
                        </span>
                    )}
                </button>
            </form>

            <div className="mt-5 text-center">
                <div className="flex items-center gap-3 mb-3">
                    <div className="flex-1 h-px bg-gradient-to-r from-transparent to-gray-200"></div>
                    <span className="text-[10px] font-bold uppercase tracking-[0.18em] text-gray-400">Atau</span>
                    <div className="flex-1 h-px bg-gradient-to-l from-transparent to-gray-200"></div>
                </div>
                <p className="text-gray-500 text-xs md:text-[13px]">
                    Belum punya akun?{' '}
                    <button
                        onClick={() => setView('register')}
                        type="button"
                        className="inline-flex min-h-11 items-center rounded-md px-1 text-ph-crimson-700 font-bold hover:text-ph-crimson-800 transition-colors"
                    >
                        Daftar Sekarang
                    </button>
                </p>
            </div>
        </div>
    );
};
