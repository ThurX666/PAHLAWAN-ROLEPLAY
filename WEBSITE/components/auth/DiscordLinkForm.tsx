import React, { useState } from 'react';
import { ArrowRight, Loader2, ShieldCheck, UserCheck } from 'lucide-react';
import { API_URL, isPreviewEnv } from '../../config';

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

  const handleLinkDiscord = async () => {
    setLoading(true);

    if (isPreviewEnv()) {
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
          <div className="animate-[slideInUp_0.4s_ease-out] w-full max-w-md mx-auto flex flex-col items-center justify-center relative z-10 text-center">
              <div className="absolute top-0 w-full h-full bg-[#5865F2]/10 blur-3xl -z-10 rounded-full opacity-50" />
              
              <div className="w-20 h-20 bg-green-500/20 rounded-full flex items-center justify-center border border-green-500/30 mb-6 drop-shadow-[0_0_15px_rgba(34,197,94,0.3)]">
                  <ShieldCheck size={40} className="text-green-500 dark:text-green-400" />
              </div>
              
              <h2 className="text-2xl font-bold text-gray-900 dark:text-white mb-3">Tautan Berhasil!</h2>
              <p className="text-gray-600 dark:text-gray-400 text-sm mb-8 leading-relaxed max-w-[280px]">
                  {authData?.roleSuccess === false 
                    ? "Akun Discord Anda telah terhubung. Namun limitasi role (Admin/Owner) mencegah sistem mengatur nickname/role secara otomatis."
                    : "Akun Discord Anda telah terhubung. Anda kini memiliki role Warga di server komunitas kami. Selamat bermain!"}
              </p>
              
              <button
                  onClick={() => {
                      if (authData) onLinkSuccess(authData.username, authData.adminLevel, authData.gold);
                  }}
                  className="w-full bg-[#5865F2] hover:bg-[#4752C4] text-white font-bold py-3.5 px-6 rounded-2xl transition-all shadow-[0_0_20px_rgba(88,101,242,0.3)] hover:shadow-[0_0_25px_rgba(88,101,242,0.5)] transform active:scale-[0.98]"
              >
                  Lanjut ke Dashboard
              </button>
          </div>
      );
  }

  return (
    <div className="animate-[slideInUp_0.4s_ease-out] w-full max-w-md mx-auto flex flex-col items-center justify-center relative z-10">
      <div className="absolute top-0 w-full h-full bg-[#5865F2]/10 blur-3xl -z-10 rounded-full opacity-50" />

      <div className="mb-8 flex justify-center w-full relative">
        <div className="absolute inset-0 bg-[#5865F2] blur-xl opacity-20 rounded-full animate-pulse" />
        <div className="w-24 h-24 bg-gradient-to-tr from-[#5865F2]/20 to-[#5865F2]/5 rounded-3xl flex items-center justify-center border border-[#5865F2]/30 shadow-[0_0_30px_rgba(88,101,242,0.2)] backdrop-blur-xl relative z-10">
          <div className="text-[#5865F2] drop-shadow-[0_0_15px_rgba(88,101,242,0.5)]">
            <IconDiscord size={48} />
          </div>
        </div>
      </div>
      
      <div className="text-center mb-10 px-4">
        <h2 className="text-3xl font-black text-transparent bg-clip-text bg-gradient-to-r from-gray-900 to-gray-600 dark:from-white dark:to-gray-400 uppercase tracking-tight mb-4">
          Hubungkan Discord
        </h2>
        <p className="text-gray-500 dark:text-gray-400 text-sm leading-relaxed max-w-[280px] mx-auto">
          Selamat <b className="text-gray-900 dark:text-white font-bold">{username}</b>!<br />
          Satu langkah lagi untuk bergabung ke komunitas, tautkan Discord Anda sekarang.
        </p>
      </div>

      <div className="space-y-3 w-full mb-10">
        <div className="flex items-start gap-4 p-4 bg-gray-100 dark:bg-white/[0.03] border border-gray-200 dark:border-white/[0.05] rounded-2xl hover:bg-gray-200 dark:hover:bg-white/[0.05] transition-all duration-300 group">
           <div className="bg-[#5865F2]/10 dark:bg-[#5865F2]/20 p-2 rounded-xl group-hover:bg-[#5865F2]/20 dark:group-hover:bg-[#5865F2]/30 transition-colors mt-0.5">
             <UserCheck size={18} className="text-[#5865F2] shrink-0"/>
           </div>
           <div>
             <p className="text-sm text-gray-900 dark:text-white font-bold mb-0.5">Otomatisasi Nickname</p>
             <p className="text-xs text-gray-500 dark:text-gray-400">Nickname server mengikuti identitas UCP Anda.</p>
           </div>
        </div>
        <div className="flex items-start gap-4 p-4 bg-gray-100 dark:bg-white/[0.03] border border-gray-200 dark:border-white/[0.05] rounded-2xl hover:bg-gray-200 dark:hover:bg-white/[0.05] transition-all duration-300 group">
           <div className="bg-[#5865F2]/10 dark:bg-[#5865F2]/20 p-2 rounded-xl group-hover:bg-[#5865F2]/20 dark:group-hover:bg-[#5865F2]/30 transition-colors mt-0.5">
             <ShieldCheck size={18} className="text-[#5865F2] shrink-0"/>
           </div>
           <div>
             <p className="text-sm text-gray-900 dark:text-white font-bold mb-0.5">Akses Role Warga</p>
             <p className="text-xs text-gray-500 dark:text-gray-400">Dapatkan akses ke channel khusus warga di Discord.</p>
           </div>
        </div>
      </div>

      <button
        onClick={handleLinkDiscord}
        disabled={loading}
        className="relative w-full overflow-hidden rounded-2xl group mb-4 disabled:opacity-50 disabled:cursor-not-allowed transform active:scale-[0.98] transition-all"
      >
        <div className="absolute inset-0 bg-gradient-to-r from-[#5865F2] to-[#4752C4] transition-transform duration-300 group-hover:scale-[1.05] origin-center" />
        <div className="relative py-4 px-6 flex items-center justify-center">
          {loading ? (
            <Loader2 className="animate-spin text-white" size={24} />
          ) : (
            <>
              <span className="text-white font-bold text-base mr-3">Tautkan Sekarang</span>
              <ArrowRight size={20} className="text-white group-hover:translate-x-1.5 transition-transform" />
            </>
          )}
        </div>
      </button>

      {isPreviewEnv() && (
          <button
            onClick={() => onLinkSuccess(username, 0, 0)}
            disabled={loading}
            className="w-full bg-transparent hover:bg-gray-100 dark:hover:bg-white/5 text-gray-500 hover:text-gray-900 dark:hover:text-gray-300 font-semibold py-3 px-4 rounded-xl transition-all flex items-center justify-center border border-transparent hover:border-gray-200 dark:hover:border-white/10 disabled:opacity-50 disabled:cursor-not-allowed text-sm"
          >
            Lewati Proses (Mode Preview)
          </button>
      )}

      <div className="text-center pt-6 pb-2 px-6">
          <p className="text-[11px] text-gray-600 leading-relaxed font-medium">
            Dengan menghubungkan akun, Anda menyetujui<br/>aturan komunitas server Discord kami.
          </p>
      </div>
    </div>
  );
};
