
import React, { useState, useEffect, useRef } from 'react';
import { Shield, Mic, Globe, TrendingUp, Users, Wifi, X, XCircle } from 'lucide-react';
import { LoginForm } from './auth/LoginForm';
import { RegisterForm } from './auth/RegisterForm';
import { ForgotPasswordForm } from './auth/ForgotPasswordForm';
import { VerifyForm } from './auth/VerifyForm';
import { DiscordLinkForm } from './auth/DiscordLinkForm';
import { API_URL } from '../config';
import { ServerStats } from '../types';
import { UCP_VERSION } from '../version';

interface AuthProps {
  onLogin: (username: string, adminLevel?: number, password?: string) => void;
  serverStats?: ServerStats;
}

type AuthView = 'login' | 'register' | 'forgot' | 'verify' | 'discord';

const AUTH_FLOW_STEPS = [
  { view: 'register', label: 'Daftar' },
  { view: 'verify', label: 'Verifikasi' },
  { view: 'discord', label: 'Discord' },
] as const;

const canUseLocalAuthPreview = () => {
  if (!import.meta.env.DEV || typeof window === 'undefined') return false;
  const host = window.location.hostname;
  return host === 'localhost' || host === '::1' || host.startsWith('127.');
};

// Updated Professional Slideshow Data (5 Slides, Visual Heavy, Indonesian Descriptions)
const SLIDES = [
  {
    id: 1,
    image: `${import.meta.env.BASE_URL}assets/images/Advanced-Voice-System1.png`, // https://i.ibb.co.com/nsrpFFtM/Advanced-Voice-System1.png (Immersive Roleplay Experience)
    title: "Immersive Roleplay Experience",
    subtitle: "Rasakan pengalaman Roleplay yang mendalam di Pahlawan Roleplay. Ciptakan cerita unik karaktermu dalam dunia yang hidup dan dinamis.",
    icon: Globe,
    color: "from-blue-600 to-indigo-600"
  },
  {
    id: 2,
    image: `${import.meta.env.BASE_URL}assets/images/Dynamic-Economic-System3.png`, // https://i.ibb.co.com/h1cWvzjs/Dynamic-Economic-System3.png (Dynamic Economic System)
    title: "Dynamic Economic System",
    subtitle: "Sistem ekonomi yang stabil dan realistis. Mulai dari pekerja harian hingga menjadi pengusaha sukses, semua peluang terbuka lebar.",
    icon: TrendingUp,
    color: "from-emerald-500 to-green-700"
  },
  {
    id: 3,
    image: `${import.meta.env.BASE_URL}assets/images/Law-Enforcement-Justice1.png`, // https://i.ibb.co.com/1GSTHbp2/Law-Enforcement-Justice1.png (Law Enforcement & Justice)
    title: "Law Enforcement & Justice",
    subtitle: "Tegakkan keadilan sebagai petugas hukum atau kuasai dunia bawah tanah. Keseimbangan kekuatan ada di tangan para pemain.",
    icon: Shield,
    color: "from-slate-700 to-slate-900"
  },
  {
    id: 4,
    image: `${import.meta.env.BASE_URL}assets/images/Advanced-Voice-System2.png`, // https://i.ibb.co.com/kVF6yGGc/Advanced-Voice-System2.png (Advanced Voice Systems)
    title: "Advanced Voice Systems",
    subtitle: "Komunikasi tanpa batas dengan fitur 3D Voice Chat jernih dan sistem smartphone canggih untuk menunjang interaksi sosial.",
    icon: Mic,
    color: "from-purple-600 to-fuchsia-600"
  },
  {
    id: 5,
    image: `${import.meta.env.BASE_URL}assets/images/Thriving-Community1.png`, // https://i.ibb.co.com/0Rh0TfTM/Thriving-Community1.png (Thriving Community)
    title: "Thriving Community",
    subtitle: "Bergabunglah dengan komunitas yang solid. Hadiri event harian, balapan jalanan, dan skenario roleplay yang seru.",
    icon: Users,
    color: "from-red-600 to-orange-600"
  }
];

export const Auth: React.FC<AuthProps> = ({ onLogin, serverStats }) => {
  const [view, setView] = useState<AuthView>('login');
  const [loading, setLoading] = useState(false);
  const [currentSlide, setCurrentSlide] = useState(0);
  const [error, setError] = useState<string | null>(null);
  const [verifyUser, setVerifyUser] = useState<string | null>(null);
  const [initialCooldown, setInitialCooldown] = useState<number>(0);
  const [deviceInfo, setDeviceInfo] = useState({ device: '', ip: '', location: '' });
  const formScrollRef = useRef<HTMLDivElement | null>(null);

  const clearPendingAuthState = () => {
    localStorage.removeItem('pending_discord_username');
    localStorage.removeItem('pending_discord_password');
  };

  // Get device Info
  useEffect(() => {
    const ua = navigator.userAgent;
    let deviceName = "Unknown Device";
    if (ua.includes("Windows NT 10.0")) deviceName = "Windows 10/11";
    else if (ua.includes("Windows NT 6.3")) deviceName = "Windows 8.1";
    else if (ua.includes("Windows NT 6.2")) deviceName = "Windows 8";
    else if (ua.includes("Windows NT 6.1")) deviceName = "Windows 7";
    else if (ua.includes("Mac OS X")) deviceName = "Mac OS";
    else if (ua.includes("Android")) deviceName = "Android";
    else if (ua.includes("iPhone OS") || ua.includes("iPad")) deviceName = "iOS";
    else if (ua.includes("Linux")) deviceName = "Linux";

    fetch('https://api4.ipify.org?format=json')
      .then(res => res.json())
      .then(data => {
          if (data.ip) {
              const ipv4 = data.ip;
              fetch(`https://ipapi.co/${ipv4}/json/`)
                .then(r => r.json())
                .then(locData => {
                    setDeviceInfo({
                        device: deviceName,
                        ip: ipv4,
                        location: (locData.city && locData.region) ? `${locData.city}, ${locData.region}` : ''
                    });
                })
                .catch(() => setDeviceInfo({ device: deviceName, ip: ipv4, location: '' }));
          }
      }).catch(() => {
          fetch('https://ipapi.co/json/')
            .then(r => r.json())
            .then(data => {
                if (data.ip) {
                    setDeviceInfo({
                        device: deviceName,
                        ip: data.ip,
                        location: (data.city && data.region) ? `${data.city}, ${data.region}` : ''
                    });
                }
            })
            .catch(() => setDeviceInfo({ device: deviceName, ip: '', location: '' }));
      });
  }, []);

  // Auto-rotate slideshow
  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentSlide((prev) => (prev + 1) % SLIDES.length);
    }, 10000); // 10 seconds interval
    return () => clearInterval(timer);
  }, []);

  // Handle Discord OAuth Callback
  useEffect(() => {
    const urlParams = new URLSearchParams(window.location.search);
    if (urlParams.get('discord_success') === '1') {
      const u = localStorage.getItem('pending_discord_username');
      const p = localStorage.getItem('pending_discord_password');
      const roleSuccess = urlParams.get('roleSuccess') !== '0';
      
      if (u) {
        clearPendingAuthState();
        
        // Clean URL
        window.history.replaceState({}, document.title, window.location.pathname);
        
        // Login immediately
        handleLoginSubmit(u, p || undefined);
        
        // Trigger success notification or something if needed
      }
    }
  }, []);

  // Clear error when switching views
  useEffect(() => {
      setError(null);
      window.scrollTo(0, 0);
      formScrollRef.current?.scrollTo({ top: 0 });
  }, [view]);

  // Handler for Login Logic
  const handleLoginSubmit = async (usernameInput: string, passwordInput?: string) => {
    setLoading(true);
    setError(null);
    const normalizedUser = usernameInput.toLowerCase().trim();

    if (localAuthPreview && normalizedUser === 'preview') {
        setTimeout(() => {
            setLoading(false);
            if (passwordInput === 'preview123') {
                clearPendingAuthState();
                onLogin('PreviewPlayer', 0, undefined, true, true);
            } else {
                setError("Kredensial Login tidak valid. Gunakan akun preview / preview123 untuk mode QA lokal.");
            }
        }, 500);
    } else {
        // MODE LIVE (XAMPP / HOSTING - FETCH MYSQL API)
        try {
            const formData = new FormData();
            formData.append('action', 'login');
            formData.append('username', usernameInput);
            formData.append('password', passwordInput || '');
            
            let currentDevice = deviceInfo.device;
            if (!currentDevice) {
                if (navigator.userAgent.includes("Windows")) currentDevice = "Windows PC";
                else if (navigator.userAgent.includes("Mac")) currentDevice = "Mac";
                else if (navigator.userAgent.includes("Linux")) currentDevice = "Linux";
                else if (navigator.userAgent.includes("Android")) currentDevice = "Android";
                else if (navigator.userAgent.includes("iPhone") || navigator.userAgent.includes("iPad")) currentDevice = "iOS";
                else currentDevice = "Unknown Device";
            }
            formData.append('device', currentDevice);
            
            if (deviceInfo.ip) formData.append('ip', deviceInfo.ip);
            if (deviceInfo.location) formData.append('location', deviceInfo.location);

            const response = await fetch(`${API_URL}/auth.php`, {
                method: 'POST',
                credentials: 'include',
                body: formData
            });

            if (!response.ok) {
                throw new Error(`HTTP Error: ${response.status} ${response.statusText}`);
            }

            const data = await response.json();

            setLoading(false);
            if (data.status === 'success') {
                // Pass level from DB (kalau adminLevel tidak ada, default to 0)
                onLogin(data.username, data.admin_level || 0, passwordInput, true, data.is_discord_linked);
            } else if (data.status === 'discord_required') {
                localStorage.setItem('pending_discord_username', data.username || usernameInput);
                localStorage.setItem('pending_discord_password', passwordInput || '');
                setVerifyUser(data.username || usernameInput);
                setView('discord');
            } else if (data.status === 'unverified') {
                localStorage.setItem('pending_discord_username', data.registered_user || usernameInput);
                localStorage.setItem('pending_discord_password', passwordInput || '');
                // Akun belum OTP! Arahkan ke halaman verifikasi.
                setVerifyUser(data.registered_user || usernameInput);
                setInitialCooldown(data.cooldown || 0);
                setView('verify');
            } else {
                setError(data.message || 'Login gagal. Periksa username dan password Anda.');
            }
        } catch (err) {
            console.error("Login fetch error:", err);
            setLoading(false);
            const errorMessage = err instanceof Error ? err.message : String(err);
            setError(`Gagal menghubungi server. Details: ${errorMessage} | Pastikan API URL benar: ${API_URL}`);
        }
    }
  };

  // Handler for Register Success -> Verify
    const handleRegisterSuccess = (username: string, password?: string) => {
      localStorage.setItem('pending_discord_username', username);
      if (password) localStorage.setItem('pending_discord_password', password);
      
      setVerifyUser(username);
      setInitialCooldown(1800); // Register sent new OTP, set to 1800
      setView('verify');
  };

  const activeSlide = SLIDES[currentSlide];
  const activeFlowIndex = AUTH_FLOW_STEPS.findIndex(step => step.view === view);
  const localAuthPreview = canUseLocalAuthPreview();

  return (
    <div className="min-h-[100dvh] flex flex-col items-center justify-center relative overflow-hidden font-sans bg-ph-surface-base ph-page-vignette p-3 sm:p-5 md:p-6 lg:p-8">

      {/* Phase 4.15: light premium hosting x roleplay backdrop */}
      <div className="absolute inset-0 z-0">
         <div className="absolute top-[-22%] left-[-12%] w-[54%] h-[54%] rounded-full bg-ph-crimson-600/[0.08] blur-[140px]"></div>
         <div className="absolute bottom-[-28%] right-[-18%] w-[48%] h-[48%] rounded-full bg-ph-gold-600/[0.07] blur-[150px]"></div>
         <div className="absolute inset-0 bg-dot-pattern-light opacity-[0.18]"></div>
      </div>

      <div className="relative z-10 grid max-h-[680px] w-full max-w-[940px] md:grid-cols-[1fr_1fr] grid-rows-[1fr] rounded-[20px] overflow-hidden shadow-[0_20px_60px_rgba(24,24,30,0.12),0_6px_18px_rgba(159,18,31,0.08)] border border-black/10 bg-white animate-auth-fade-in">

        {/* LEFT SIDE: Roleplay highlight panel */}
        <div className="relative hidden md:flex min-h-0 bg-black flex-col justify-between p-7 lg:p-8 overflow-hidden">
             <div className="absolute inset-0 bg-gradient-to-t from-black/[0.72] via-black/[0.18] to-black/[0.10] z-[6] pointer-events-none"></div>

             {SLIDES.map((slide, index) => (
                 <div
                    key={slide.id}
                    className={`absolute inset-0 transition-opacity duration-1000 ease-in-out ${index === currentSlide ? 'opacity-100' : 'opacity-0'}`}
                 >
                    <img
                        src={slide.image}
                        className={`w-full h-full object-cover transition-transform duration-[10000ms] ease-linear ${index === currentSlide ? 'scale-[1.08]' : 'scale-100'}`}
                        alt={slide.title}
                    />
                 </div>
             ))}

             <div className="relative z-20 flex items-start justify-between gap-4">
                <div className="flex items-center gap-3">
                    <div className="flex h-10 w-10 items-center justify-center rounded-xl bg-white/[0.12] border border-white/[0.18] text-sm font-black tracking-tight text-white">
                      PH
                    </div>
                    <div>
                      <p className="text-[10px] font-bold uppercase tracking-[0.22em] text-white/[0.72]">PHRP</p>
                      <p className="mt-1 text-xs font-semibold text-white">Est. 2020</p>
                    </div>
                </div>
                <span className="rounded-md border border-white/[0.16] bg-white/[0.10] px-2.5 py-1 text-[10px] font-bold uppercase tracking-[0.16em] text-white/[0.78] font-mono">
                  {String(currentSlide + 1).padStart(2, '0')} <span className="text-white/[0.30] mx-1">/</span> {String(SLIDES.length).padStart(2, '0')}
                </span>
             </div>

             <div className="relative z-20 mt-auto max-w-[470px]">
                 <div key={activeSlide.id} className="animate-auth-fade-in">
                     <p className="mb-2 inline-flex rounded-full border border-white/[0.18] bg-white/[0.10] px-2.5 py-0.5 text-[9px] font-bold uppercase tracking-[0.20em] text-white/[0.82]">Live Server Access</p>
                     <h1 className="text-[24px] md:text-[28px] font-extrabold text-white tracking-tight leading-tight mb-2">
                        Pahlawan Roleplay UCP
                     </h1>
                     <p className="text-white/[0.82] text-[12px] max-w-md leading-relaxed">
                        Kelola identitas roleplay Anda, verifikasi akun, dan masuk ke ekosistem komunitas Pahlawan Roleplay dari satu client-area yang rapi.
                     </p>
                     <div className="mt-5 grid grid-cols-1 sm:grid-cols-3 md:grid-cols-1 lg:grid-cols-3 gap-2.5">
                        {['Kelola karakter', 'Verifikasi akun', 'Hubungkan Discord'].map(item => (
                          <div key={item} className="rounded-lg border border-white/[0.14] bg-white/[0.10] px-3 py-2 text-[11px] font-semibold text-white/[0.88]">
                            {item}
                          </div>
                        ))}
                     </div>
                     <p className="mt-5 text-[11px] font-semibold uppercase tracking-[0.18em] text-white/[0.60]">
                        {activeSlide.title}
                     </p>
                 </div>
             </div>

             {/* Minimal slide indicators */}
             <div className="relative z-20 flex items-center gap-1.5 mt-5">
                 {SLIDES.map((slide, index) => (
                     <button
                        key={slide.id}
                        onClick={() => setCurrentSlide(index)}
                        className="group flex h-10 w-10 items-center justify-start"
                        aria-label={`Slide ${index + 1}`}
                     >
                         <div className={`h-1.5 rounded-full transition-all duration-500 ${index === currentSlide ? 'w-9 bg-white' : 'w-2 bg-white/[0.32] hover:bg-white/[0.55]'}`}></div>
                      </button>
                  ))}
              </div>
         </div>

        {/* RIGHT SIDE: Auth Form Container */}
        <div className="w-full flex flex-col relative min-h-0 h-full ph-auth-surface overflow-hidden">

          {/* Top Accent Line */}
          <div className="absolute top-0 left-0 right-0 h-[2px] ph-auth-accent-line z-20"></div>

          <div className="shrink-0 flex min-h-[56px] items-center justify-between gap-4 px-5 md:px-7 pt-4 md:pt-5 pb-2 md:pb-3">
              <div>
                  <span className="text-[10px] font-bold uppercase tracking-[0.22em] text-gray-500">Account Access</span>
                  <p className="mt-1 text-xs font-semibold text-gray-700">Secure UCP gateway</p>
              </div>
              <span className="self-center rounded-md border border-ph-gold-600/20 bg-ph-gold-600/[0.08] px-2.5 py-1.5 text-[10px] leading-none font-mono font-semibold tracking-[0.15em] text-ph-gold-700 whitespace-nowrap">{UCP_VERSION}</span>
          </div>

          {/* Server Status Bar */}
          <div className="shrink-0 px-4 md:px-7 pb-2 md:pb-3">
              <div className="flex flex-col divide-y divide-gray-200 sm:grid sm:grid-cols-2 md:grid-cols-[0.78fr_0.82fr_1.4fr] ph-status-pill rounded-xl overflow-hidden">
                  {/* Status */}
                  <div className="min-w-0 px-3 py-2.5">
                    <p className="mb-1 text-[9px] font-bold uppercase tracking-[0.18em] text-gray-500">Status</p>
                    <div className="flex items-center gap-1.5">
                      <div className="relative flex h-2 w-2">
                        {serverStats?.status === 'Online' ? (
                            <>
                                <span className="animate-ping absolute inline-flex h-full w-full rounded-full bg-green-400 opacity-75"></span>
                                <span className="relative inline-flex rounded-full h-2 w-2 bg-green-500"></span>
                            </>
                        ) : serverStats?.status === 'Loading' ? (
                            <>
                                <span className="animate-ping absolute inline-flex h-full w-full rounded-full bg-yellow-400 opacity-75"></span>
                                <span className="relative inline-flex rounded-full h-2 w-2 bg-yellow-500"></span>
                            </>
                        ) : (
                          <span className="relative inline-flex rounded-full h-2 w-2 bg-red-500"></span>
                        )}
                      </div>
                      <span className={`text-[11px] font-bold uppercase tracking-wider ${serverStats?.status === 'Online' ? 'text-green-600' : serverStats?.status === 'Loading' ? 'text-yellow-600' : 'text-ph-crimson-700'}`}>
                          {serverStats?.status === 'Online' ? 'Online' : serverStats?.status === 'Loading' ? 'Memuat...' : 'Offline'}
                      </span>
                    </div>
                  </div>

                  {/* Players */}
                  <div className="min-w-0 px-3 py-2.5">
                    <p className="mb-1 text-[9px] font-bold uppercase tracking-[0.18em] text-gray-500">Players</p>
                    <div className="flex items-center gap-1.5">
                      <Users size={13} className="text-gray-500" />
                      <span className="text-[11px] font-bold text-gray-900 font-mono whitespace-nowrap">
                          {serverStats?.players ?? 0}<span className="font-sans font-semibold text-gray-500 ml-1">pemain</span>
                      </span>
                    </div>
                  </div>

                  {/* IP */}
                  <div className="hidden sm:block min-w-0 px-3 py-2.5">
                    <p className="mb-1 text-[9px] font-bold uppercase tracking-[0.18em] text-gray-500">Server IP</p>
                    <div className="flex min-w-0 items-center gap-1.5">
                      <Wifi size={13} className="text-gray-500 shrink-0" />
                      <span className="truncate text-[10px] sm:text-[11px] font-semibold text-gray-800 font-mono tracking-wide">{serverStats?.ip_address || "pahlawan-rp.com:7777"}</span>
                    </div>
                  </div>
              </div>
          </div>

          {/* Scrollable Form Area — with scroll fade indicator */}
          <div className="relative flex-1 min-h-0">
          <div ref={formScrollRef} className="h-full overflow-y-auto overflow-x-hidden px-4 md:px-8 pb-6 pt-1 ph-scroll-thin" onScroll={(e) => { const el = e.currentTarget; const fade = el.parentElement?.querySelector('.ph-scroll-fade'); if(fade) fade.style.opacity = el.scrollTop + el.clientHeight >= el.scrollHeight - 8 ? '0' : '1'; }}>
           <div className="ph-auth-panel-inner max-w-[400px] mx-auto w-full rounded-2xl px-5 md:px-6 py-5 md:py-6 my-0.5">

             {/* Logo + sub-brand */}
            <div className="flex flex-col items-center mb-4 mt-0">
                <div className="relative">
                    <img
                        src={`${import.meta.env.BASE_URL}assets/images/logo1.png`}
                        alt="Pahlawan Roleplay"
                        className="w-24 md:w-28 max-h-10 md:max-h-12 object-contain hover:scale-[1.02] transition-transform duration-500 relative z-10"
                    />
                </div>
            </div>

            {activeFlowIndex >= 0 && (
                <div className="mb-4 rounded-xl border border-gray-200 bg-gray-50/70 p-2" aria-label="Progress pendaftaran akun">
                    <div className="flex items-center justify-between gap-1.5">
                        {AUTH_FLOW_STEPS.map((step, index) => {
                            const isActive = index === activeFlowIndex;
                            const isDone = index < activeFlowIndex;
                            const stepCircleClass = isActive
                                ? 'border-ph-crimson-600/35 bg-ph-crimson-600/10 text-ph-crimson-700'
                                : isDone
                                    ? 'border-ph-crimson-600/30 bg-ph-crimson-600/[0.08] text-ph-crimson-700'
                                    : 'border-gray-200 bg-white text-gray-500';
                            const stepLabelClass = isActive
                                ? 'text-gray-900'
                                : isDone
                                    ? 'text-gray-700'
                                    : 'text-gray-500';
                            const connectorClass = index < activeFlowIndex ? 'bg-ph-crimson-600/45' : 'bg-gray-200';
                            return (
                                <React.Fragment key={step.view}>
                                    <div className="flex min-w-0 flex-1 flex-col items-center gap-1">
                                        <div className={`flex h-6 w-6 items-center justify-center rounded-full border text-[10px] font-black transition-all ${stepCircleClass}`} aria-current={isActive ? 'step' : undefined}>
                                            {index + 1}
                                        </div>
                                        <span className={`truncate text-[9px] font-bold tracking-wide ${stepLabelClass}`}>
                                            {step.label}
                                        </span>
                                    </div>
                                    {index < AUTH_FLOW_STEPS.length - 1 && (
                                        <div className={`mb-4 h-px w-4 shrink-0 ${connectorClass}`} />
                                    )}
                                </React.Fragment>
                            );
                        })}
                    </div>
                </div>
            )}

            {/* Inline Error Alert */}
            {error && (
                <div className="ph-alert ph-alert-error mb-4">
                    <XCircle size={18} className="shrink-0 mt-0.5 text-ph-crimson-700" />
                    <div className="flex-1">
                        <p className="font-semibold text-ph-crimson-800 text-[13px] mb-0.5">Terjadi Kesalahan</p>
                        <p className="text-[12px] leading-relaxed opacity-90">{error}</p>
                    </div>
                    <button
                        onClick={() => setError(null)}
                        className="shrink-0 text-gray-500 hover:text-gray-900 transition-colors p-0.5"
                        aria-label="Tutup pesan error"
                    >
                        <X size={14} />
                    </button>
                </div>
            )}

            {/* MODULAR FORMS */}
            {view === 'login' && (
                <>
                    <LoginForm onSubmit={handleLoginSubmit} setView={setView} loading={loading} />
                </>
            )}

            {view === 'register' && (
                <RegisterForm onSubmit={handleRegisterSuccess} setView={setView} loading={loading} onError={setError} />
            )}

            {view === 'forgot' && (
                <ForgotPasswordForm onSubmit={() => {}} setView={setView} loading={loading} onError={setError} />
            )}

            {view === 'verify' && verifyUser && (
                <VerifyForm
                   username={verifyUser}
                   initialCooldown={initialCooldown}
                   deviceInfo={deviceInfo}
                   onVerifySuccess={(username, adminLvl, gold, isDiscordLinked) => {
                       clearPendingAuthState();
                       onLogin(username, adminLvl, undefined, true, isDiscordLinked);
                   }}
                   onDiscordRequired={(actualUsername) => {
                       setVerifyUser(actualUsername);
                       setView('discord');
                   }}
                   setView={setView}
                   onError={setError}
                />
            )}

            {view === 'discord' && verifyUser && (
                <DiscordLinkForm
                    username={verifyUser}
                    onLinkSuccess={(username, adminLvl, gold) => {
                        clearPendingAuthState();
                        onLogin(username, adminLvl, undefined, true, true);
                    }}
                    setView={setView}
                    onError={setError}
                />
            )}

           </div>
          </div>
          {/* Scroll-fade indicator — fades when scrolled to bottom */}
          <div className="ph-scroll-fade pointer-events-none absolute bottom-0 left-0 right-0 h-10 bg-gradient-to-t from-white to-transparent transition-opacity duration-300"></div>
          </div>
        </div>
      </div>

      {/* Dev-only preview shortcuts — floating corner panel, only on localhost */}
      {localAuthPreview && (
          <div className="fixed bottom-3 right-3 z-50 flex flex-col gap-1.5 opacity-60 hover:opacity-100 transition-opacity">
              {view === 'login' && (<>
                  <button
                      onClick={() => handleLoginSubmit('preview', 'preview123')}
                      className="rounded-md border border-gray-300/50 bg-white/90 backdrop-blur-sm px-2.5 py-1 text-[10px] font-mono text-gray-500 shadow-sm hover:bg-gray-100 hover:text-ph-crimson-700 transition-all"
                  >
                      Preview Login
                  </button>
                  <button
                      onClick={() => {
                          setVerifyUser("preview@pahlawan-rp.local");
                          setInitialCooldown(1800);
                          setView('verify');
                      }}
                      className="rounded-md border border-gray-300/50 bg-white/90 backdrop-blur-sm px-2.5 py-1 text-[10px] font-mono text-gray-500 shadow-sm hover:bg-gray-100 hover:text-ph-crimson-700 transition-all"
                  >
                      Preview OTP
                  </button>
                  <button
                      onClick={() => { setVerifyUser("PreviewPlayer"); setView('discord'); }}
                      className="rounded-md border border-gray-300/50 bg-white/90 backdrop-blur-sm px-2.5 py-1 text-[10px] font-mono text-gray-500 shadow-sm hover:bg-gray-100 hover:text-ph-crimson-700 transition-all"
                  >
                      Preview Discord
                  </button>
                  <button
                      onClick={() => setError(`Gagal menghubungi server. Details: Simulasi network error lokal | Pastikan API URL benar: ${API_URL}`)}
                      className="rounded-md border border-gray-300/50 bg-white/90 backdrop-blur-sm px-2.5 py-1 text-[10px] font-mono text-gray-500 shadow-sm hover:bg-gray-100 hover:text-ph-crimson-700 transition-all"
                  >
                      Preview Error
                  </button>
              </>)}
              {view !== 'login' && (
                  <button
                      onClick={() => setView('login')}
                      className="rounded-md border border-gray-300/50 bg-white/90 backdrop-blur-sm px-2.5 py-1 text-[10px] font-mono text-gray-500 shadow-sm hover:bg-gray-100 hover:text-ph-crimson-700 transition-all"
                  >
                      ← Back to Login
                  </button>
              )}
          </div>
      )}
    </div>
  );
};
