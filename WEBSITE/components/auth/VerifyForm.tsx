import React, { useState, useEffect } from 'react';
import { Mail, ArrowRight, Loader2, KeyRound, RefreshCw, Clock } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

interface VerifyFormProps {
  username: string;
  initialCooldown?: number;
  deviceInfo?: { device: string; ip: string; location: string };
  onVerifySuccess: (username: string, adminLevel: number, gold?: number, isDiscordLinked?: boolean) => void;
  onDiscordRequired?: (username: string) => void;
  setView: (view: 'login' | 'register' | 'forgot' | 'verify') => void;
  onError?: (msg: string) => void;
}

export const VerifyForm: React.FC<VerifyFormProps> = ({ username: email, initialCooldown = 0, deviceInfo, onVerifySuccess, onDiscordRequired, setView, onError }) => {
  const [otp, setOtp] = useState('');
  const [loading, setLoading] = useState(false);
  const [resending, setResending] = useState(false);
  
  // Format seconds to HH:MM:SS
  const formatCooldown = (seconds: number) => {
      const h = Math.floor(seconds / 3600);
      const m = Math.floor((seconds % 3600) / 60);
      const s = seconds % 60;
      return `${h.toString().padStart(2, '0')}:${m.toString().padStart(2, '0')}:${s.toString().padStart(2, '0')}`;
  };

  // Anti- drift state
  const [expireTime, setExpireTime] = useState<number>(Date.now() + initialCooldown * 1000);
  const [cooldown, setCooldown] = useState(initialCooldown);
  
  const [errorMsg, setErrorMsg] = useState<string | null>(null);
  const [successMsg, setSuccessMsg] = useState<string | null>(null);

  // Sync expire time jika prop diganti dari parent (misal Auth me-render ulang form)
  useEffect(() => {
      if (initialCooldown > 0) {
          setExpireTime(Date.now() + initialCooldown * 1000);
      }
  }, [initialCooldown]);

  // Timer Efek kebal Tab-Background-Sleep
  useEffect(() => {
    const timer = setInterval(() => {
        const remaining = Math.max(0, Math.ceil((expireTime - Date.now()) / 1000));
        setCooldown(remaining);
    }, 1000);
    return () => clearInterval(timer);
  }, [expireTime]);

  const handleResend = async () => {
    setResending(true);
    setErrorMsg(null);
    setSuccessMsg(null);

    if (isPreviewEnv()) {
        setTimeout(() => {
            setResending(false);
            setSuccessMsg("Mode Preview: Simulasi kirim ulang berhasil dikirim.");
        }, 1000);
        return;
    }

    try {
        const formData = new FormData();
        formData.append('action', 'resend_otp');
        formData.append('username', email);

        const response = await fetch(`${API_URL}/resend_otp.php`, {
            method: 'POST',
            body: formData
        });

        const data = await response.json();
        setResending(false);

        if (data.status === 'success') {
            setSuccessMsg(data.message);
            setExpireTime(Date.now() + 1800 * 1000); // Reset timer mutlak 30 menit ke depan
        } else {
            setErrorMsg(data.message || 'Gagal mengirim ulang OTP.');
            if (data.cooldown) {
                setExpireTime(Date.now() + data.cooldown * 1000); 
            }
        }
    } catch (err) {
        setResending(false);
        setErrorMsg("Kesalahan koneksi ke server saat mengirim ulang.");
    }
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    setErrorMsg(null);
    setSuccessMsg(null);

    // [Rest of Submit Logic Remained Immutable Below, only update UI text]
    if (isPreviewEnv()) {
        setTimeout(() => {
            setLoading(false);
            if (otp === '123456') {
                setSuccessMsg("Verifikasi Berhasil! Bersiap untuk masuk...");
                setTimeout(() => {
                   onVerifySuccess(email, 0, 0);
                }, 2000);
            } else {
                const msg = 'Mode Preview: Kode OTP salah. Harap masukkan 123456.';
                setErrorMsg(msg);
                if (onError) onError(msg);
            }
        }, 1000);
        return;
    }

    try {
        const formData = new FormData();
        formData.append('action', 'verify_otp');
        // Ingat, variabel di register.js yang dikirim adalah EMAIL jadi backend verify juga akan mendeteksi dari Email/Username yang di-pass
        formData.append('username', email); 
        formData.append('otp_code', otp);
        let currentDevice = deviceInfo?.device;
        if (!currentDevice) {
            if (navigator.userAgent.includes("Windows")) currentDevice = "Windows PC";
            else if (navigator.userAgent.includes("Mac")) currentDevice = "Mac";
            else if (navigator.userAgent.includes("Linux")) currentDevice = "Linux";
            else if (navigator.userAgent.includes("Android")) currentDevice = "Android";
            else if (navigator.userAgent.includes("iPhone") || navigator.userAgent.includes("iPad")) currentDevice = "iOS";
            else currentDevice = "Unknown Device";
        }
        formData.append('device', currentDevice);
        
        if (deviceInfo?.ip) formData.append('ip', deviceInfo.ip);
        if (deviceInfo?.location) formData.append('location', deviceInfo.location);

        const response = await fetch(`${API_URL}/verify.php`, {
            method: 'POST',
            body: formData
        });

        const data = await response.json();
        setLoading(false);

        if (data.status === 'success') {
            setSuccessMsg(data.message);
            // Delay 2 seconds so user can read the success message
            setTimeout(() => {
                onVerifySuccess(data.username || email, data.admin_level || 0, data.gold || 0, data.is_discord_linked); // Langsung lempar payload ke Auth, bypass layar Login
            }, 2000);
        } else if (data.status === 'discord_required') {
            setSuccessMsg(data.message);
            if (data.username) {
                localStorage.setItem('pending_discord_username', data.username);
            }
            setTimeout(() => {
                if (onDiscordRequired) {
                    onDiscordRequired(data.username || email);
                } else {
                    setView('discord');
                }
            }, 2000);
        } else {
            const msg = data.message || 'Gagal memverifikasi OTP.';
            setErrorMsg(msg);
            if (onError) onError(msg);
        }
    } catch (err: any) {
        setLoading(false);
        console.error("Verify API Error:", err);
        const msg = "Kesalahan: " + (err.message || 'Koneksi ke server gagal.');
        setErrorMsg(msg);
        if (onError) onError(msg);
    }
  };

  return (
    <div className="animate-[slideInUp_0.4s_ease-out]">
      <div className="mb-6 flex justify-center">
        <div className="w-16 h-16 bg-red-600/10 rounded-2xl flex items-center justify-center border border-red-500/20 shadow-inner">
          <Mail size={32} className="text-red-500" />
        </div>
      </div>
      
      <div className="text-center mb-8">
        <h2 className="text-2xl font-black text-gray-900 dark:text-white uppercase tracking-tight mb-2">Verifikasi Email</h2>
        <p className="text-gray-600 dark:text-gray-400 text-sm">
          Kode 6 digit telah dikirim ke Email <b>{email}</b>. 
          <br/>Silakan periksa kotak masuk atau folder spam Anda.
        </p>
      </div>

      {errorMsg && (
          <div className="mb-4 bg-red-500/10 border-l-4 border-red-500 p-3 rounded text-red-200 text-sm">
              {errorMsg}
          </div>
      )}

      {successMsg && (
          <div className="mb-4 bg-green-500/10 border-l-4 border-green-500 p-3 rounded text-green-300 text-sm">
              {successMsg}
          </div>
      )}

      <form onSubmit={handleSubmit} className="space-y-5">
        <div>
          <label className="block text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-wider mb-2 ml-1">
            Kode OTP (6 Angka)
          </label>
          <div className="relative group">
            <div className="absolute inset-y-0 left-0 pl-4 flex items-center pointer-events-none">
              <KeyRound size={20} className="text-gray-500 group-focus-within:text-red-500 transition-colors" />
            </div>
            <input
              type="text"
              value={otp}
              onChange={(e) => setOtp(e.target.value)}
              placeholder="XXXXXX"
              maxLength={6}
              className="w-full bg-white dark:bg-black/40 border-2 border-gray-200 dark:border-white/10 rounded-xl py-3.5 pl-12 pr-4 text-gray-900 dark:text-white placeholder-gray-400 dark:placeholder-gray-600 font-mono text-center tracking-[0.5em] text-lg focus:outline-none focus:border-red-500/50 focus:bg-gray-50 dark:focus:bg-black/60 transition-all shadow-inner"
              required
            />
          </div>
        </div>

        <button
          type="submit"
          disabled={loading || otp.length < 6}
          className="w-full bg-gradient-to-r from-red-600 to-red-800 hover:from-red-500 hover:to-red-700 text-white font-bold py-3.5 px-4 rounded-xl transition-all flex items-center justify-center shadow-lg shadow-red-900/40 border border-red-500/30 disabled:opacity-50 disabled:cursor-not-allowed group"
        >
          {loading ? (
            <Loader2 className="animate-spin" size={24} />
          ) : (
            <>
              VERIFIKASI AKUN
              <ArrowRight size={20} className="ml-2 group-hover:translate-x-1 transition-transform" />
            </>
          )}
        </button>

        <div className="text-center pt-2 space-y-3 flex flex-col items-center">
            <button
                type="button"
                onClick={handleResend}
                disabled={resending || cooldown > 0}
                className="text-gray-500 dark:text-gray-400 hover:text-gray-900 dark:hover:text-white text-xs flex items-center justify-center transition-colors uppercase font-bold tracking-wider disabled:opacity-50 border border-transparent hover:border-gray-300 dark:hover:border-white/10 bg-gray-100 dark:bg-white/5 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full px-4 py-2"
            >
                {resending ? (
                    <><Loader2 className="animate-spin mr-2" size={14} /> Mengirim Ulang...</>
                ) : cooldown > 0 ? (
                    <><Clock size={14} className="mr-2" /> Tunggu {formatCooldown(cooldown)}</>
                ) : (
                    <><RefreshCw size={14} className="mr-2" /> Kirim Ulang OTP</>
                )}
            </button>
            
          <p className="text-gray-600 dark:text-gray-500 flex flex-col gap-2 text-xs font-medium w-full border-t border-gray-200 dark:border-white/5 pt-4">
            <button 
                type="button" 
                onClick={() => setView('login')} 
                className="text-gray-500 dark:text-gray-400 hover:text-gray-900 dark:hover:text-white transition-colors uppercase font-bold tracking-wider py-2"
            >
              Kembali ke Halaman Login
            </button>
          </p>
        </div>
      </form>
    </div>
  );
};
