import React, { useState } from 'react';
import { ArrowRight, Loader2, ShieldCheck, UserCheck, ChevronLeft } from 'lucide-react';
import { API_URL, isPreviewEnv } from '../../config';

const canUseLocalAuthPreview = () => {
    if (!import.meta.env.DEV || typeof window === 'undefined') return false;
    const host = window.location.hostname;
    return host === 'localhost' || host === '::1' || host.startsWith('127.');
};

interface DiscordLinkFormProps {
  username: string;
  onLinkSuccess: (username: string, adminLevel: number, gold?: number) => void;
  setView: (view: 'login' | 'register' | 'forgot' | 'verify') => void;
  onError?: (msg: string) => void;
}

export const DiscordLinkForm: React.FC<DiscordLinkFormProps> = ({ username, onLinkSuccess, setView, onError }) => {
  const [loading, setLoading] = useState(false);
  const [showSuccess, setShowSuccess] = useState(false);
  const [authData, setAuthData] = useState<{username: string, adminLevel: number, gold?: number, roleSuccess?: boolean} | null>(null);
  const localAuthPreview = canUseLocalAuthPreview();

  const handleLinkDiscord = async () => {
    setLoading(true);

    if (isPreviewEnv() || localAuthPreview) {
        setTimeout(() => {
            setLoading(false);
            setAuthData({ username, adminLevel: 0, gold: 0, roleSuccess: true });
            setShowSuccess(true);
        }, 1500);
        return;
    }

    try {
        let baseUrl = API_URL;
        if (!baseUrl.startsWith('http')) {
            if (baseUrl.startsWith('/')) {
                baseUrl = `${window.location.origin}${baseUrl}`;
            } else {
                const currentPath = window.location.pathname.substring(0, window.location.pathname.lastIndexOf('/') + 1);
                baseUrl = `${window.location.origin}${currentPath}${baseUrl}`;
            }
        }
        
        const url = new URL(`${baseUrl}/discord_link.php`);
        url.searchParams.append('username', username);
        url.searchParams.append('return_url', window.location.href);
        
        // Redirect directly in the same tab
        window.location.href = url.toString();
        
        // No need to set loading to false because page will navigate away
    } catch (err) {
        setLoading(false);
        if (onError) onError("Kesalahan jaringan.");
    }
  };

  const IconDiscord = ({ size = 24 }: { size?: number }) => (
      <svg width={size} height={size} viewBox="0 0 24 24" fill="currentColor">
          <path d="M20.317 4.3698a19.7913 19.7913 0 00-4.8851-1.5152.0741.0741 0 00-.0785.0371c-.211.3753-.4447.8648-.6083 1.2495-1.8447-.2762-3.68-.2762-5.4868 0-.1636-.3933-.4058-.8742-.6177-1.2495a.077.077 0 00-.0785-.037 19.7363 19.7363 0 00-4.8852 1.515.0699.0699 0 00-.0321.0277C.5334 9.0458-.319 13.5799.0992 18.0578a.0824.0824 0 00.0312.0561c2.0528 1.5076 4.0413 2.4228 5.9929 3.0294a.0777.0777 0 00.0842-.0276c.4616-.6304.8731-1.2952 1.226-1.9942a.076.076 0 00-.0416-.1057c-.6528-.2476-1.2743-.5495-1.8722-.8923a.077.077 0 01-.0076-.1277c.1258-.0943.2517-.1923.3718-.2914a.0743.0743 0 01.0776-.0105c3.9278 1.7933 8.18 1.7933 12.0614 0a.0739.0739 0 01.0785.0095c.1202.099.246.1981.3728.2924a.077.077 0 01-.0066.1276 12.2986 12.2986 0 01-1.873.8914.0766.0766 0 00-.0407.1067c.3604.698.7719 1.3628 1.225 1.9932a.076.076 0 00.0842.0286c1.961-.6067 3.9495-1.5219 6.0023-3.0294a.077.077 0 00.0313-.0552c.5004-5.177-.8382-9.6739-3.5485-13.6604a.061.061 0 00-.0312-.0286zM8.02 15.3312c-1.1825 0-2.1569-1.0857-2.1569-2.419 0-1.3332.9555-2.4189 2.157-2.4189 1.2108 0 2.1757 1.0952 2.1568 2.419 0 1.3332-.9555 2.4189-2.1569 2.4189zm7.9748 0c-1.1825 0-2.1569-1.0857-2.1569-2.419 0-1.3332.9554-2.4189 2.1569-2.4189 1.2108 0 2.1757 1.0952 2.1568 2.419 0 1.3332-.946 2.4189-2.1568 2.4189z"/>
      </svg>
  );

  if (showSuccess) {
      return (
          <div className="animate-auth-slide-up w-full max-w-md mx-auto flex flex-col items-center justify-center relative z-10 text-center">

              <div className="text-center mb-3 w-full">
                <span className="ph-eyebrow mb-3">Tautan Berhasil</span>
              </div>

              <div className="relative w-14 h-14 mb-4">
                <div className="w-full h-full bg-gradient-to-br from-green-500/15 to-green-600/5 rounded-xl flex items-center justify-center border border-green-500/20 shadow-md">
                  <ShieldCheck size={28} className="text-green-600" />
                </div>
              </div>

              <h2 className="text-[22px] md:text-[26px] font-extrabold text-gray-950 mb-1.5 tracking-tight leading-tight">Tautan Berhasil!</h2>
              <p className="text-gray-500 text-[12px] md:text-[13px] mb-5 leading-relaxed max-w-[300px]">
                  {authData?.roleSuccess === false
                    ? "Akun Discord Anda telah terhubung. Namun limitasi role (Admin/Owner) mencegah sistem mengatur nickname/role secara otomatis."
                    : "Akun Discord Anda telah terhubung. Anda kini memiliki role Warga di server komunitas kami. Selamat bermain!"}
              </p>

              <button
                  onClick={() => {
                      if (authData) onLinkSuccess(authData.username, authData.adminLevel, authData.gold);
                  }}
                  className="ph-btn-primary w-full py-3.5 px-6 flex items-center justify-center group"
              >
                  <span className="flex items-center text-sm font-bold tracking-wide">
                    Lanjut ke Dashboard
                    <ArrowRight size={17} className="ml-2 group-hover:translate-x-1 transition-transform" />
                  </span>
              </button>
          </div>
      );
  }

  return (
    <div className="animate-auth-slide-up w-full max-w-md mx-auto flex flex-col items-center justify-center relative z-10">

      <div className="text-center mb-3 w-full">
        <span className="ph-eyebrow mb-3">Komunitas PHRP</span>
      </div>

      <div className="mb-3 flex justify-center w-full">
        <div className="w-16 h-16 bg-gradient-to-br from-[#5865F2]/10 to-[#5865F2]/5 rounded-xl flex items-center justify-center border border-[#5865F2]/18 shadow-sm">
            <div className="text-[#5865F2]">
              <IconDiscord size={34} />
            </div>
        </div>
      </div>

      <div className="text-center mb-4 px-2">
        <h2 className="text-[22px] md:text-[26px] font-extrabold text-gray-950 tracking-tight mb-1.5 leading-tight">
          Hubungkan Discord
        </h2>
        <p className="text-gray-500 text-[12px] md:text-[13px] leading-relaxed max-w-[300px] mx-auto">
          Selamat <b className="text-gray-950 font-bold">{username}</b>!<br />
          Satu langkah terakhir untuk mengaktifkan akses komunitas PHRP Anda.
        </p>
      </div>

      <div className="space-y-2.5 w-full mb-4">
        <div className="flex items-start gap-3 p-3 bg-gray-50/80 border border-gray-200 rounded-lg hover:bg-white transition-all duration-200 group">
           <div className="bg-gradient-to-br from-[#5865F2]/12 to-[#5865F2]/5 p-2 rounded-lg group-hover:from-[#5865F2]/18 group-hover:to-[#5865F2]/10 transition-colors mt-0.5 shrink-0">
             <UserCheck size={16} className="text-[#5865F2] shrink-0"/>
           </div>
           <div className="min-w-0">
             <p className="text-sm text-gray-950 font-semibold mb-0.5">Otomatisasi Nickname</p>
               <p className="text-xs text-gray-500 leading-relaxed">Nickname server mengikuti identitas UCP Anda.</p>
           </div>
        </div>
        <div className="flex items-start gap-3 p-3 bg-gray-50/80 border border-gray-200 rounded-lg hover:bg-white transition-all duration-200 group">
           <div className="bg-gradient-to-br from-[#5865F2]/12 to-[#5865F2]/5 p-2 rounded-lg group-hover:from-[#5865F2]/18 group-hover:to-[#5865F2]/10 transition-colors mt-0.5 shrink-0">
             <ShieldCheck size={16} className="text-[#5865F2] shrink-0"/>
           </div>
           <div className="min-w-0">
              <p className="text-sm text-gray-950 font-semibold mb-0.5">Akses Role Warga</p>
               <p className="text-xs text-gray-500 leading-relaxed">Dapatkan akses ke channel warga resmi PHRP.</p>
           </div>
        </div>
      </div>

      <button
        onClick={handleLinkDiscord}
        disabled={loading}
        className="relative w-full overflow-hidden rounded-xl group mb-2 disabled:opacity-50 disabled:cursor-not-allowed transform active:scale-[0.98] transition-all shadow-md hover:shadow-lg"
      >
        <div className="absolute inset-0 bg-gradient-to-r from-[#5865F2] to-[#4752C4] transition-transform duration-300 group-hover:scale-[1.04] origin-center" />
        <div className="relative py-3.5 px-6 flex items-center justify-center">
          {loading ? (
            <Loader2 className="animate-spin text-white" size={22} />
          ) : (
            <>
              <span className="text-white font-bold text-sm mr-2.5 tracking-wide">Tautkan Sekarang</span>
              <ArrowRight size={18} className="text-white group-hover:translate-x-1.5 transition-transform" />
            </>
          )}
        </div>
      </button>

      {localAuthPreview && (
          <button
            onClick={() => onLinkSuccess(username, 0, 0)}
            disabled={loading}
            className="w-full bg-transparent hover:bg-ph-crimson-600/[0.05] text-gray-500 hover:text-ph-crimson-700 font-semibold py-3 px-4 rounded-xl transition-all flex items-center justify-center border border-transparent hover:border-ph-crimson-600/10 disabled:opacity-50 disabled:cursor-not-allowed text-xs"
          >
            Lewati Proses (Mode Pratinjau)
          </button>
      )}

      <div className="text-center pt-2">
          <button
              type="button"
              onClick={() => setView('login')}
              className="text-gray-500 hover:text-ph-crimson-700 text-xs flex min-h-11 items-center justify-center w-full transition-colors font-semibold tracking-wide py-2 group"
          >
              <ChevronLeft size={14} className="mr-1 group-hover:-translate-x-0.5 transition-transform" /> Kembali ke Login
          </button>
      </div>

      <div className="text-center pt-1 pb-1 px-4">
            <p className="text-[11px] text-gray-500 leading-relaxed">
            Dengan menghubungkan akun, Anda menyetujui<br/>aturan komunitas server Discord kami.
          </p>
      </div>
    </div>
  );
};
