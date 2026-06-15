
import React, { useState } from 'react';
import { Mail, ArrowRight, Loader2, ChevronLeft, Lock, KeyRound } from 'lucide-react';
import { InputGroup } from './InputGroup';

import { isPreviewEnv, API_URL } from '../../config';

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

    const handleSendOTP = async (e: React.FormEvent) => {
        e.preventDefault();
        setError('');
        setSuccessMsg('');
        
        if(!email.trim()) {
            setError('Alamat email wajib diisi');
            return;
        }

        setLocalLoading(true);

        if (isPreviewEnv()) {
            setTimeout(() => {
                setLocalLoading(false);
                if (email !== 'admin@admin.com' && email !== 'player@player.com') {
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
                setSuccessMsg(data.message);
                setStep(2);
            } else {
                setError(data.message || 'Gagal mengirim email verifikasi.');
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

        if (isPreviewEnv()) {
            setTimeout(() => {
                setLocalLoading(false);
                if (otp !== '123456') {
                    setError('Kode OTP salah! (Gunakan 123456 untuk simulasi)');
                } else {
                    alert('Kata sandi berhasil diubah! Silakan masuk dengan sandi baru Anda.');
                    setView('login');
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
                alert(data.message);
                setView('login');
            } else {
                setError(data.message || 'Gagal mereset kata sandi.');
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
        <div className="animate-[fadeIn_0.3s_ease-out]">
            <div className="text-center mb-8">
               <h2 className="text-3xl font-black text-gray-900 dark:text-white mb-2 uppercase italic tracking-tighter">
                 Reset Password
               </h2>
               <p className="text-gray-500 text-xs uppercase tracking-widest font-bold">
                 {step === 1 ? 'Recover Account' : 'Set New Password'}
               </p>
            </div>

            {successMsg && (
                <div className="mb-4 p-3 bg-green-500/20 border border-green-500/50 rounded-lg text-green-400 text-sm font-medium text-center">
                    {successMsg}
                </div>
            )}

            {step === 1 ? (
                <form onSubmit={handleSendOTP} className="space-y-4" noValidate>
                    <InputGroup 
                        icon={Mail} 
                        type="email" 
                        placeholder="Email Address" 
                        autoComplete="email"
                        value={email}
                        onChange={e => {
                            setEmail(e.target.value);
                            setError('');
                        }}
                        error={error}
                    />

                    <button 
                        type="submit" 
                        disabled={isLoading}
                        className="w-full bg-gradient-to-r from-red-600 to-red-700 hover:from-red-500 hover:to-red-600 text-white font-bold py-4 rounded-xl transition-all transform hover:scale-[1.02] active:scale-[0.98] shadow-lg shadow-red-600/20 disabled:opacity-70 disabled:cursor-not-allowed flex items-center justify-center group"
                    >
                        {isLoading ? <Loader2 className="animate-spin" size={20} /> : (
                            <span className="flex items-center text-sm uppercase tracking-widest">
                                Send Reset Link
                                <ArrowRight size={16} className="ml-2 group-hover:translate-x-1 transition-transform" />
                            </span>
                        )}
                    </button>
                </form>
            ) : (
                <form onSubmit={handleResetPassword} className="space-y-4" noValidate>
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
                        className="w-full bg-gradient-to-r from-red-600 to-red-700 hover:from-red-500 hover:to-red-600 text-white font-bold py-4 rounded-xl transition-all transform hover:scale-[1.02] active:scale-[0.98] shadow-lg shadow-red-600/20 disabled:opacity-70 disabled:cursor-not-allowed flex items-center justify-center group"
                    >
                        {isLoading ? <Loader2 className="animate-spin" size={20} /> : (
                            <span className="flex items-center text-sm uppercase tracking-widest">
                                Ubah Sandi
                                <Lock size={16} className="ml-2 group-hover:translate-y-[2px] transition-transform" />
                            </span>
                        )}
                    </button>
                </form>
            )}

            <div className="mt-8 text-center">
                 <button onClick={() => setView('login')} className="text-gray-500 dark:text-gray-400 hover:text-gray-900 dark:hover:text-white text-xs flex items-center justify-center w-full transition-colors uppercase font-bold tracking-wider py-4">
                    <ChevronLeft size={14} className="mr-1" /> Back to Login
                 </button>
            </div>
        </div>
    );
};
