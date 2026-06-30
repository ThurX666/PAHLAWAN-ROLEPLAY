
import React, { useState } from 'react';
import { Mail, ArrowRight, Loader2, ChevronLeft, Lock, KeyRound } from 'lucide-react';
import { InputGroup } from './InputGroup';

import { isPreviewEnv, API_URL } from '../../config';

const translatePreviewMsg = (msg: string): string => {
    if (msg.toLowerCase().includes('local-only otp preview')) {
        return 'Pratinjau OTP lokal aktif untuk lingkungan ini. Fitur ini dinonaktifkan di produksi.';
    }
    return msg;
};

const canUseLocalAuthPreview = () => {
    if (!import.meta.env.DEV || typeof window === 'undefined') return false;
    const host = window.location.hostname;
    return host === 'localhost' || host === '::1' || host.startsWith('127.');
};

interface ForgotPasswordFormProps {
    onSubmit: (email?: string) => void;
    setView: (view: 'login' | 'register' | 'forgot') => void;
    loading: boolean;
    onError?: (msg: string) => void;
}

export const ForgotPasswordForm: React.FC<ForgotPasswordFormProps> = ({ onSubmit, setView, loading: initialLoading, onError }) => {
    const [step, setStep] = useState<1 | 2>(1);
    const [email, setEmail] = useState('');
    const [otp, setOtp] = useState('');
    const [newPassword, setNewPassword] = useState('');
    const [confirmPassword, setConfirmPassword] = useState('');
    const [error, setError] = useState('');
    const [successMsg, setSuccessMsg] = useState('');
    const [localLoading, setLocalLoading] = useState(false);

    const isLoading = initialLoading || localLoading;
    const localAuthPreview = canUseLocalAuthPreview();

    const handleSendOTP = async (e: React.FormEvent) => {
        e.preventDefault();
        setError('');
        setSuccessMsg('');
        
        if(!email.trim()) {
            setError('Alamat email wajib diisi');
            return;
        }

        setLocalLoading(true);

        if (isPreviewEnv() || localAuthPreview) {
            setTimeout(() => {
                setLocalLoading(false);
                if (!localAuthPreview && email !== 'admin@admin.com' && email !== 'player@player.com') {
                    const msg = 'Email tidak terdaftar di sistem kami.';
                    setError(msg);
                    if (onError) onError(msg);
                } else {
                    setSuccessMsg('Kode OTP telah dikirim ke ' + email);
                    setStep(2);
                }
            }, 1000);
            return;
        }

        try {
            const formData = new FormData();
            formData.append('action', 'forgot_password');
            formData.append('email', email);

            const res = await fetch(`${API_URL}/forgot.php`, {
                method: 'POST',
                body: formData
            });

            const data = await res.json();
            setLocalLoading(false);

            if (data.status === 'success') {
                setSuccessMsg(translatePreviewMsg(data.message));
                setStep(2);
            } else {
                setError(translatePreviewMsg(data.message || 'Gagal mengirim email verifikasi.'));
                if (onError) onError(data.message || 'Gagal mengirim email verifikasi.');
            }
        } catch (err) {
            setLocalLoading(false);
            const msg = 'Terjadi kesalahan jaringan.';
            setError(msg);
            if (onError) onError(msg);
        }
    };

    const handleResetPassword = async (e: React.FormEvent) => {
        e.preventDefault();
        setError('');
        setSuccessMsg('');

        if (!otp.trim() || !newPassword.trim() || !confirmPassword.trim()) {
            setError('Harap isi semua kolom!');
            return;
        }

        if (newPassword !== confirmPassword) {
            setError('Konfirmasi sandi tidak cocok!');
            return;
        }

        if (newPassword.length < 6) {
            setError('Kata sandi harus minimal 6 karakter!');
            return;
        }

        setLocalLoading(true);

        if (isPreviewEnv() || localAuthPreview) {
            setTimeout(() => {
                setLocalLoading(false);
                if (otp !== '123456') {
                    setError('Kode OTP salah! (Gunakan 123456 untuk simulasi)');
                } else {
                    setSuccessMsg('Kata sandi berhasil diubah! Mengalihkan ke halaman login...');
                    setTimeout(() => setView('login'), 2500);
                }
            }, 1000);
            return;
        }

        try {
            const formData = new FormData();
            formData.append('action', 'reset_password');
            formData.append('email', email);
            formData.append('otp', otp);
            formData.append('new_password', newPassword);

            const res = await fetch(`${API_URL}/forgot.php`, {
                method: 'POST',
                body: formData
            });

            const data = await res.json();
            setLocalLoading(false);

            if (data.status === 'success') {
                setSuccessMsg(translatePreviewMsg(data.message || 'Kata sandi berhasil diubah!'));
                setTimeout(() => setView('login'), 2500);
            } else {
                setError(translatePreviewMsg(data.message || 'Gagal mereset kata sandi.'));
                if (onError) onError(data.message || 'Gagal mereset kata sandi.');
            }
        } catch (err) {
            setLocalLoading(false);
            const msg = 'Terjadi kesalahan jaringan.';
            setError(msg);
            if (onError) onError(msg);
        }
    };

    return (
        <div className="animate-auth-slide-up">
            <div className="text-center mb-4">
               <span className="ph-eyebrow mb-3">Account Recovery</span>
               <h2 className="text-[22px] md:text-[26px] font-extrabold text-gray-950 mb-1.5 tracking-tight leading-tight">
                 Atur Ulang Sandi
               </h2>
               <p className="text-gray-500 text-[12px] md:text-[13px] leading-relaxed">
                 {step === 1 ? 'Masukkan email untuk menerima kode OTP' : 'Masukkan kode OTP dan sandi baru'}
               </p>
            </div>

            <div className="mb-4 rounded-lg border border-gray-200 bg-gray-50/80 px-3.5 py-2.5">
                <div className="flex items-center justify-center gap-2.5">
                    <span className={`text-[10px] font-bold uppercase tracking-wider ${step === 1 ? 'text-ph-crimson-700' : 'text-gray-400'}`}>01 Email</span>
                    <div className="relative flex items-center">
                        <div className={`h-px w-10 rounded-full transition-colors ${step >= 2 ? 'bg-gradient-to-r from-ph-gold-600 to-ph-crimson-600' : 'bg-gray-200'}`} />
                        {step >= 2 && <span className="absolute right-0 w-1.5 h-1.5 rounded-full bg-ph-crimson-600"></span>}
                    </div>
                    <span className={`text-[10px] font-bold uppercase tracking-wider ${step === 2 ? 'text-ph-crimson-700' : 'text-gray-400'}`}>02 Reset Sandi</span>
                </div>
            </div>

            {successMsg && (
                <div className="ph-alert ph-alert-success mb-4">
                    <span className="font-semibold">{successMsg}</span>
                </div>
            )}

            {step === 1 ? (
                <form onSubmit={handleSendOTP} className="space-y-3" noValidate>
                    <InputGroup
                        icon={Mail}
                        type="email"
                        placeholder="Alamat Email"
                        autoComplete="email"
                        value={email}
                        onChange={e => {
                            setEmail(e.target.value);
                            setError('');
                        }}
                        error={error}
                        hint="Kami akan mengirim kode OTP reset sandi."
                    />

                    <button
                        type="submit"
                        disabled={isLoading}
                        className="ph-btn-primary w-full py-3.5 mt-1 flex items-center justify-center group"
                    >
                        {isLoading ? <Loader2 className="animate-spin" size={20} /> : (
                            <span className="flex items-center text-sm font-bold tracking-wide">
                                Kirim Kode OTP
                                <ArrowRight size={17} className="ml-2 group-hover:translate-x-1 transition-transform" />
                            </span>
                        )}
                    </button>

                    {localAuthPreview && (
                        <button
                            type="button"
                            onClick={() => {
                                setEmail('preview@pahlawan-rp.local');
                                setOtp('123456');
                                setNewPassword('preview123');
                                setConfirmPassword('preview123');
                                setSuccessMsg('Mode preview lokal: state reset sandi disiapkan.');
                                setStep(2);
                            }}
                            className="w-full rounded-lg border border-gray-200 bg-gray-50 py-3 text-xs font-mono text-gray-600 transition-all hover:bg-ph-crimson-600/5 hover:text-ph-crimson-700"
                        >
                            Preview Reset Step
                        </button>
                    )}
                </form>
            ) : (
                <form onSubmit={handleResetPassword} className="space-y-2.5" noValidate>
                    <InputGroup
                        icon={KeyRound}
                        type="text"
                        placeholder="Kode OTP (6 Digit)"
                        value={otp}
                        onChange={e => {
                            setOtp(e.target.value.replace(/\D/g, '').slice(0, 6));
                            setError('');
                        }}
                        error={error}
                        hint="Masukkan 6 digit kode dari email."
                    />

                    <InputGroup
                        icon={Lock}
                        type="password"
                        placeholder="Sandi Baru"
                        value={newPassword}
                        onChange={e => {
                            setNewPassword(e.target.value);
                            setError('');
                        }}
                    />

                    <InputGroup
                        icon={Lock}
                        type="password"
                        placeholder="Konfirmasi Sandi Baru"
                        value={confirmPassword}
                        onChange={e => {
                            setConfirmPassword(e.target.value);
                            setError('');
                        }}
                    />

                    <button
                        type="submit"
                        disabled={isLoading}
                        className="ph-btn-primary w-full py-3.5 mt-2 flex items-center justify-center group"
                    >
                        {isLoading ? <Loader2 className="animate-spin" size={20} /> : (
                            <span className="flex items-center text-sm font-bold tracking-wide">
                                Ubah Sandi
                                <Lock size={16} className="ml-2 group-hover:scale-110 transition-transform" />
                            </span>
                        )}
                    </button>
                </form>
            )}

            <div className="mt-4 text-center">
                  <button onClick={() => setView('login')} className="text-gray-500 hover:text-ph-crimson-700 text-xs flex min-h-11 items-center justify-center w-full transition-colors font-semibold tracking-wide py-2 group">
                    <ChevronLeft size={14} className="mr-1 group-hover:-translate-x-0.5 transition-transform" /> Kembali ke Login
                 </button>
            </div>
        </div>
    );
};
