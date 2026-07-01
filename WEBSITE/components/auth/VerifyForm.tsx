import React, { useState, useEffect } from 'react';
import { Mail, ArrowRight, Loader2, KeyRound, RefreshCw, Clock } from 'lucide-react';
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
  const localAuthPreview = canUseLocalAuthPreview();

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

    if (isPreviewEnv() || localAuthPreview) {
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
            setSuccessMsg(translatePreviewMsg(data.message));
            setExpireTime(Date.now() + 1800 * 1000); // Reset timer mutlak 30 menit ke depan
        } else {
            setErrorMsg(translatePreviewMsg(data.message || 'Gagal mengirim ulang OTP.'));
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
    if (isPreviewEnv() || localAuthPreview) {
        setTimeout(() => {
            setLoading(false);
            if (otp === '123456') {
                setSuccessMsg("Verifikasi berhasil. Menyiapkan akses UCP Anda...");
                setTimeout(() => {
                   if (localAuthPreview && onDiscordRequired) {
                       onDiscordRequired(email);
                   } else {
                       onVerifySuccess(email, 0, 0);
                   }
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
            credentials: 'include',
            body: formData
        });

        const data = await response.json();
        setLoading(false);

        if (data.status === 'success') {
            setSuccessMsg(translatePreviewMsg(data.message));
            // Delay 2 seconds so user can read the success message
            setTimeout(() => {
                onVerifySuccess(data.username || email, data.admin_level || 0, data.gold || 0, data.is_discord_linked); // Langsung lempar payload ke Auth, bypass layar Login
            }, 2000);
        } else if (data.status === 'discord_required') {
            setSuccessMsg(translatePreviewMsg(data.message));
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
            const msg = translatePreviewMsg(data.message || 'Gagal memverifikasi OTP.');
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
    <div className="animate-auth-slide-up">
      <div className="text-center mb-5">
        <span className="ph-eyebrow block mb-1.5">Email Verification</span>
      </div>
      <div className="mb-2.5 flex justify-center">
        <div className="w-12 h-12 bg-ph-crimson-600/[0.08] rounded-xl flex items-center justify-center border border-ph-crimson-600/20 shadow-sm">
          <Mail size={22} className="text-ph-crimson-700" />
        </div>
      </div>

      <div className="text-center mb-4">
        <h2 className="text-[18px] md:text-[22px] font-extrabold text-gray-950 mb-1 tracking-tight leading-tight">Verifikasi Email</h2>
        <p className="text-gray-500 text-[11.5px] md:text-[12.5px] leading-[1.5]">
          Kode 6 digit telah dikirim ke email <b className="text-gray-950">{email}</b>. Silakan periksa kotak masuk atau folder spam Anda.
        </p>
      </div>

      {errorMsg && (
          <div className="ph-alert ph-alert-error mb-4">{errorMsg}</div>
      )}

      {successMsg && (
          <div className="ph-alert ph-alert-success mb-4">{successMsg}</div>
      )}

      <form onSubmit={handleSubmit} className="space-y-2.5">
        <div>
          <label className="block text-[10px] font-bold text-gray-500 uppercase tracking-[0.18em] mb-2 ml-0.5">
            Kode OTP <span className="text-ph-crimson-700">*</span>
          </label>
          <div className="relative group">
            <div className="absolute inset-y-0 left-0 pl-3.5 flex items-center pointer-events-none z-10">
              <KeyRound size={17} className="text-gray-400 group-focus-within:text-ph-crimson-700 transition-colors" />
            </div>
            <input
              type="text"
              inputMode="numeric"
              pattern="[0-9]*"
              value={otp}
              onChange={(e) => setOtp(e.target.value.replace(/\D/g, '').slice(0, 6))}
              placeholder="XXXXXX"
              maxLength={6}
              className="ph-input-focus w-full bg-ph-surface-input border border-gray-200 rounded-lg py-3.5 pl-11 pr-4 text-gray-900 placeholder-gray-300 font-mono text-center tracking-[0.6em] text-[20px] font-bold transition-all duration-200 shadow-sm"
              required
            />
          </div>
          <div className="mt-3 rounded-xl border border-gray-200/80 bg-gray-50/80 px-3 py-2.5">
            <div className="mb-2 flex items-center justify-between gap-3">
              <span className="text-[10px] font-black uppercase tracking-[0.16em] text-gray-500">Waktu OTP</span>
              <span className="font-mono text-[11px] font-bold text-gray-800">{formatCooldown(cooldown)}</span>
            </div>
            <div className="h-1.5 overflow-hidden rounded-full bg-gray-200">
              <div
                className="h-full rounded-full bg-gradient-to-r from-ph-gold-500 to-ph-crimson-600 transition-all duration-500"
                style={{ width: `${Math.max(0, Math.min(100, (cooldown / Math.max(initialCooldown || 1800, 1)) * 100))}%` }}
              />
            </div>
          </div>
          {localAuthPreview && (
            <button
              type="button"
              onClick={() => setOtp('123456')}
              className="mt-2 min-h-11 rounded-lg border border-gray-200 bg-gray-50 px-3 py-2 text-xs font-mono font-semibold text-gray-600 transition-all hover:bg-ph-crimson-600/[0.05] hover:text-ph-crimson-700"
            >
              Isi OTP demo 123456
            </button>
          )}
        </div>

        <button
          type="submit"
          disabled={loading || otp.length < 6}
          className="ph-btn-primary w-full py-3 flex items-center justify-center group"
        >
          {loading ? (
            <Loader2 className="animate-spin" size={22} />
          ) : (
            <span className="flex items-center text-sm font-bold tracking-wide">
              Verifikasi Akun
              <ArrowRight size={17} className="ml-2 group-hover:translate-x-1 transition-transform" />
            </span>
          )}
        </button>

        <div className="mt-6 text-center space-y-2.5 flex flex-col items-center">
            <button
                type="button"
                onClick={handleResend}
                disabled={resending || cooldown > 0}
                className="text-gray-600 hover:text-ph-crimson-700 text-xs flex items-center justify-center transition-colors font-semibold tracking-wide disabled:opacity-40 bg-gray-50 hover:bg-ph-crimson-600/[0.05] rounded-full px-4 py-2 border border-gray-200"
            >
                {resending ? (
                    <><Loader2 className="animate-spin mr-2" size={14} /> Mengirim Ulang...</>
                ) : cooldown > 0 ? (
                    <><Clock size={14} className="mr-2" /> Tunggu {formatCooldown(cooldown)}</>
                ) : (
                    <><RefreshCw size={14} className="mr-2" /> Kirim Ulang OTP</>
                )}
            </button>

          <button
              type="button"
              onClick={() => setView('login')}
              className="min-h-11 text-gray-500 hover:text-ph-crimson-700 text-xs transition-colors font-semibold tracking-wide py-2"
          >
            Kembali ke Halaman Login
          </button>
        </div>
      </form>
    </div>
  );
};
