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

            {/* ── Header Block ── */}
            <div className="text-center mb-7">
                <span className="ph-eyebrow block mb-2">Roleplay Identity</span>
                <h2 className="text-[20px] md:text-[24px] font-extrabold text-gray-950 mb-1.5 tracking-tight leading-tight">
                    Selamat Datang
                </h2>
                <p className="text-gray-500 text-[12px] md:text-[13px] leading-[1.6]">
                    Masuk ke UCP Pahlawan Roleplay<br className="hidden md:block" />{' '}untuk mengelola akses akun Anda.
                </p>
            </div>

            {/* ── Form Block ── */}
            <form onSubmit={handleSubmit} className="space-y-3" noValidate>
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

                <div className="space-y-0.5">
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
                    {/* Forgot password — tight to password field */}
                    <div className="flex justify-end">
                        <button
                            type="button"
                            onClick={() => setView('forgot')}
                            className="inline-flex items-center rounded px-1.5 py-0 text-[11px] font-semibold text-gray-400 hover:text-ph-crimson-700 transition-colors duration-200"
                        >
                            Lupa Password?
                        </button>
                    </div>
                </div>

                {/* CTA Button */}
                <button
                    type="submit"
                    disabled={loading}
                    className="ph-btn-primary w-full py-3 flex items-center justify-center group"
                >
                    {loading ? <Loader2 className="animate-spin" size={20} /> : (
                        <span className="flex items-center text-sm font-bold tracking-wide">
                            Masuk ke Akun
                            <ArrowRight size={17} className="ml-2 group-hover:translate-x-1 transition-transform" />
                        </span>
                    )}
                </button>
            </form>

            {/* ── Divider + Register ── */}
            <div className="mt-6 text-center">
                <div className="flex items-center gap-4 mb-4">
                    <div className="flex-1 h-px bg-gradient-to-r from-transparent to-gray-200"></div>
                    <span className="text-[10px] font-bold uppercase tracking-[0.2em] text-gray-300">Atau</span>
                    <div className="flex-1 h-px bg-gradient-to-l from-transparent to-gray-200"></div>
                </div>
                <p className="text-gray-500 text-[12px] md:text-[13px]">
                    Belum punya akun?{' '}
                    <button
                        onClick={() => setView('register')}
                        type="button"
                        className="inline-flex items-center rounded px-1 py-0.5 text-ph-crimson-700 font-bold hover:text-ph-crimson-800 transition-colors duration-200"
                    >
                        Daftar Sekarang
                    </button>
                </p>
            </div>
        </div>
    );
};
