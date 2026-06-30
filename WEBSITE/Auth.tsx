
import React, { useState, useEffect } from 'react';
import { Hexagon, Star, Shield, AlertCircle, X, Smartphone, Map, Mic, Globe, TrendingUp, Users, Wifi, Radio, XCircle } from 'lucide-react';
import { LoginForm } from './auth/LoginForm';
import { RegisterForm } from './auth/RegisterForm';
import { ForgotPasswordForm } from './auth/ForgotPasswordForm';
import { VerifyForm } from './auth/VerifyForm';
import { DiscordLinkForm } from './auth/DiscordLinkForm';
import { API_URL } from '../config';
import { ServerStats } from '../types';

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
        localStorage.removeItem('pending_discord_username');
        localStorage.removeItem('pending_discord_password');
        
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
  }, [view]);

  // Handler for Login Logic
  const handleLoginSubmit = async (usernameInput: string, passwordInput?: string) => {
    setLoading(true);
    setError(null);

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
            onLogin(data.username, data.admin_level || 0, passwordInput, true, data.is_discord_linked);
        } else if (data.status === 'discord_required') {
            localStorage.setItem('pending_discord_username', data.username || usernameInput);
            localStorage.setItem('pending_discord_password', passwordInput || '');
            setVerifyUser(data.username || usernameInput);
            setView('discord');
        } else if (data.status === 'unverified') {
            localStorage.setItem('pending_discord_username', data.registered_user || usernameInput);
            localStorage.setItem('pending_discord_password', passwordInput || '');
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
        if (errorMessage === "Failed to fetch") {
            setError(`Server lokal tidak merespon (API URL: ${API_URL}). Pastikan server PHP jalan.`);
        } else {
            setError(`Gagal menghubungi server. Details: ${errorMessage}`);
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
  const SlideIcon = activeSlide.icon;
  const activeFlowIndex = AUTH_FLOW_STEPS.findIndex(step => step.view === view);

  return (
    <div className="min-h-[100dvh] flex items-center justify-center relative overflow-hidden font-sans bg-ph-surface-deep ph-page-vignette px-3 py-3 md:px-6 md:py-6 ph-safe-top ph-safe-bottom">

      {/* Dynamic Background â€” strong PHRP identity */}
      <div className="absolute inset-0 z-0">
         <div className="absolute top-[-25%] left-[-15%] w-[70%] h-[70%] rounded-full bg-ph-crimson-700/[0.20] blur-[180px] animate-pulse-slow"></div>
         <div className="absolute bottom-[-15%] right-[-10%] w-[55%] h-[55%] rounded-full bg-ph-gold-600/[0.12] blur-[160px] animate-pulse-slow" style={{animationDelay: '1.5s'}}></div>
         <div className="absolute top-[20%] right-[10%] w-[35%] h-[35%] rounded-full bg-ph-crimson-600/[0.10] blur-[140px] animate-pulse-slow" style={{animationDelay: '3s'}}></div>
         <div className="absolute inset-0 bg-dot-pattern-light dark:bg-dot-pattern opacity-70"></div>
         <div className="absolute inset-0 bg-grid-pattern-light dark:bg-grid-pattern opacity-40"></div>
         <div className="absolute inset-x-0 top-0 h-px bg-gradient-to-r from-transparent via-ph-gold-600/40 to-transparent"></div>
         <div className="absolute inset-x-0 bottom-0 h-px bg-gradient-to-r from-transparent via-ph-crimson-700/40 to-transparent"></div>
      </div>

      <div className="relative z-10 w-full max-w-6xl min-h-[calc(100dvh-24px)] md:min-h-0 md:h-[720px] md:max-h-[calc(100dvh-48px)] flex md:rounded-[24px] overflow-hidden shadow-[0_25px_70px_rgba(0,0,0,0.25),0_10px_30px_rgba(127,29,29,0.18)] dark:shadow-[0_30px_80px_rgba(0,0,0,0.65),0_15px_40px_rgba(127,29,29,0.30)] border border-ph-gold-600/20 md:border-ph-gold-600/30 dark:border-ph-crimson-900/40 bg-white dark:bg-ph-surface-card animate-auth-fade-in">
        
        {/* Cinematic corner accents on the card */}
        <span className="ph-card-corner tl"></span>
        <span className="ph-card-corner tr"></span>
        <span className="ph-card-corner bl"></span>
        <span className="ph-card-corner br"></span>
        
        {/* LEFT SIDE: Showcase Slideshow (Hidden on mobile) */}
        <div className="hidden md:flex md:w-[52%] lg:w-[56%] relative bg-black flex-col justify-between p-8 lg:p-12 overflow-hidden">
             {/* Layered overlays for cinematic feel */}
             <div className="absolute inset-0 bg-gradient-to-br from-ph-crimson-950/30 via-transparent to-ph-gold-900/20 z-[5] mix-blend-overlay pointer-events-none"></div>
             <div className="absolute inset-0 bg-gradient-to-r from-black/65 via-black/20 to-transparent z-[6] pointer-events-none"></div>
             
             {SLIDES.map((slide, index) => (
                 <div 
                    key={slide.id}
                    className={`absolute inset-0 transition-opacity duration-1000 ease-in-out ${index === currentSlide ? 'opacity-100' : 'opacity-0'}`}
                 >
                    <img 
                        src={slide.image} 
                        className={`w-full h-full object-cover transition-transform duration-[10000ms] ease-linear ${index === currentSlide ? 'scale-110' : 'scale-100'}`}
                        alt={slide.title}
                    />
                 </div>
             ))}
             
             {/* Cinematic gradient overlay */}
             <div className="absolute inset-0 bg-gradient-to-t from-black via-black/60 to-black/10 z-10"></div>
             <div className="absolute inset-x-0 bottom-0 h-2/3 bg-gradient-to-t from-black via-black/70 to-transparent z-10"></div>
             
             {/* Top brand bar on slideshow */}
             <div className="relative z-20 flex items-center justify-between">
                <div className="flex items-center gap-2">
                    <div className="w-8 h-8 rounded-lg bg-gradient-to-br from-ph-gold-400 to-ph-gold-600 flex items-center justify-center shadow-lg border border-white/20">
                        <Star size={16} className="text-white" fill="currentColor" />
                    </div>
                    <div>
                        <p className="text-white text-[11px] font-black uppercase tracking-[0.2em] leading-none drop-shadow">PHRP</p>
                        <p className="text-ph-gold-400/90 text-[9px] font-bold uppercase tracking-[0.18em] mt-1 leading-none">Est. 2020</p>
                    </div>
                </div>
                <div className="px-2.5 py-1 rounded-full bg-white/10 backdrop-blur-sm border border-white/15">
                    <span className="text-[9px] font-bold uppercase tracking-[0.18em] text-white/90">{String(currentSlide + 1).padStart(2, '0')} / {String(SLIDES.length).padStart(2, '0')}</span>
                </div>
             </div>
             
             <div className="relative z-20 mt-auto">
                 <div key={activeSlide.id} className="animate-auth-fade-in">
                     <div className={`w-14 h-14 rounded-2xl flex items-center justify-center mb-5 shadow-2xl bg-gradient-to-br ${activeSlide.color} border border-white/25 ring-1 ring-black/20`}>
                        <SlideIcon className="text-white" fill="currentColor" size={26} />
                     </div>
                     <div className="inline-flex items-center gap-1.5 px-2.5 py-1 rounded-full bg-ph-gold-500/20 border border-ph-gold-400/30 backdrop-blur-sm mb-3">
                        <span className="w-1.5 h-1.5 rounded-full bg-ph-gold-400 animate-pulse"></span>
                        <span className="text-[9px] font-black uppercase tracking-[0.2em] text-ph-gold-400">Feature Highlight</span>
                     </div>
                     <h1 className="text-4xl font-black text-white uppercase italic tracking-tight leading-[0.95] mb-4 drop-shadow-2xl">
                        {activeSlide.title}
                     </h1>
                     <p className="text-gray-200/95 text-[13px] max-w-sm leading-relaxed drop-shadow-lg border-l-[3px] border-ph-gold-500 pl-4 py-1">
                        {activeSlide.subtitle}
                     </p>
                 </div>
             </div>
             
             {/* Premium slide indicators */}
             <div className="relative z-20 flex items-center gap-2 mt-7">
                 {SLIDES.map((slide, index) => (
                     <button 
                        key={slide.id}
                        onClick={() => setCurrentSlide(index)}
                        className="group relative"
                        aria-label={`Slide ${index + 1}`}
                     >
                        <div className={`h-1 rounded-full transition-all duration-500 ${index === currentSlide ? 'w-12 bg-gradient-to-r from-ph-gold-400 to-ph-crimson-500' : 'w-3 bg-white/25 hover:bg-white/45 group-hover:w-6'}`}></div>
                        {index === currentSlide && (
                            <span className="absolute -top-1 left-0 right-0 h-0.5 bg-ph-gold-400/60 blur-[2px]"></span>
                        )}
                     </button>
                 ))}
                 <div className="ml-auto text-[10px] font-mono font-bold text-white/50 tracking-widest">
                    AUTO
                 </div>
             </div>
        </div>

        {/* RIGHT SIDE: Auth Form Container */}
        <div className="w-full md:w-[48%] lg:w-[44%] flex flex-col relative h-full ph-auth-surface overflow-hidden">
          
          {/* Top Accent Line */}
          <div className="absolute top-0 left-0 right-0 h-[3px] ph-auth-accent-line z-20 shadow-[0_1px_6px_rgba(220,38,38,0.35)]"></div>
          
          {/* Eyebrow micro text (left of status) */}
          <div className="shrink-0 flex items-center justify-between px-5 md:px-7 pt-5 md:pt-6 pb-1.5">
              <span className="ph-eyebrow text-[9px] md:text-[10px]">User Control Panel</span>
              <span className="text-[9px] font-mono font-bold tracking-widest text-gray-500 dark:text-gray-500 uppercase">v1.0</span>
          </div>

          {/* Mobile-only compact brand strip */}
          <div className="md:hidden shrink-0 px-5 pb-3">
              <div className="rounded-2xl border border-ph-gold-600/15 bg-white/75 px-4 py-3 shadow-sm backdrop-blur">
                  <div className="flex items-center gap-3">
                      <div className="w-9 h-9 rounded-xl bg-gradient-to-br from-ph-gold-500 to-ph-crimson-600 flex items-center justify-center text-white shadow-md">
                          <Star size={17} fill="currentColor" />
                      </div>
                      <div className="min-w-0">
                          <p className="text-[12px] font-black uppercase tracking-[0.18em] text-gray-950 leading-none">Pahlawan RP</p>
                          <p className="text-[11px] text-gray-500 mt-1 leading-none">UCP aman untuk warga kota</p>
                      </div>
                  </div>
              </div>
          </div>
          
          {/* Server Status Bar â€” premium */}
          <div className="shrink-0 flex justify-center pt-1 pb-2.5 px-4">
              <div className="flex items-center gap-2 md:gap-2.5 ph-status-pill rounded-full px-3.5 py-1.5">
                  {/* Status */}
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
                      <span className={`text-[10px] font-bold uppercase tracking-wider ${serverStats?.status === 'Online' ? 'text-green-600 dark:text-green-400' : serverStats?.status === 'Loading' ? 'text-yellow-600 dark:text-yellow-400' : 'text-red-600 dark:text-red-400'}`}>
                          {serverStats?.status === 'Online' ? 'Online' : serverStats?.status === 'Loading' ? 'Memuat...' : 'Offline'}
                      </span>
                  </div>

                  {/* Divider */}
                  <div className="w-px h-3 bg-gray-300 dark:bg-white/10"></div>

                  {/* Players */}
                  <div className="flex items-center gap-1.5">
                      <Users size={11} className="text-gray-500 dark:text-gray-400" />
                      <span className="text-[10px] font-bold text-gray-700 dark:text-white font-mono">{serverStats?.players || 0}</span>
                  </div>

                  {/* Divider */}
                  <div className="hidden sm:block w-px h-3 bg-gray-300 dark:bg-white/10"></div>

                  {/* IP */}
                  <div className="hidden sm:flex items-center gap-1.5">
                      <Wifi size={11} className="text-ph-gold-600 dark:text-ph-gold-500" />
                      <span className="text-[10px] font-semibold text-gray-600 dark:text-gray-300 font-mono tracking-wide">{serverStats?.ip_address || "pahlawan-rp.com:7777"}</span>
                  </div>
              </div>
          </div>

          {/* Scrollable Form Area â€” wrapped in inner card section for premium feel */}
          <div className="flex-1 overflow-y-auto overflow-x-hidden px-2 xs:px-3 md:px-5 pb-8 md:pb-5 pt-1 ph-scroll-thin ph-safe-bottom">
           <div className="ph-auth-panel-inner max-w-[420px] mx-auto w-full rounded-2xl px-4 xs:px-5 md:px-6 py-4 md:py-5 my-1">
            
            {/* Logo + sub-brand */}
            <div className="flex flex-col items-center mb-3 mt-0">
                <div className="relative">
                    <img 
                        src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} 
                        alt="Pahlawan Roleplay" 
                        className="w-28 md:w-32 max-h-12 md:max-h-14 object-contain hover:scale-[1.04] transition-transform duration-500 relative z-10" 
                    />
                    <div className="absolute inset-0 bg-ph-gold-400/20 blur-2xl -z-10"></div>
                </div>
            </div>

            {activeFlowIndex >= 0 && (
                <div className="mb-4 rounded-xl border border-gray-200/80 dark:border-white/10 bg-white/80 dark:bg-ph-surface-input p-2.5 shadow-sm dark:shadow-none" aria-label="Progress pendaftaran akun">
                    <div className="flex items-center justify-between gap-1.5">
                        {AUTH_FLOW_STEPS.map((step, index) => {
                            const isActive = index === activeFlowIndex;
                            const isDone = index < activeFlowIndex;
                            const stepCircleClass = isActive
                                ? 'border-ph-gold-500/50 bg-ph-gold-500/15 text-ph-gold-600 dark:text-ph-gold-400'
                                : isDone
                                    ? 'border-ph-crimson-500/40 bg-ph-crimson-600/10 text-ph-crimson-600 dark:text-ph-crimson-400'
                                    : 'border-gray-200 dark:border-white/10 bg-gray-50 dark:bg-ph-surface-panel text-gray-400';
                            const stepLabelClass = isActive
                                ? 'text-gray-900 dark:text-white'
                                : isDone
                                    ? 'text-gray-500 dark:text-gray-300'
                                    : 'text-gray-400 dark:text-gray-500';
                            const connectorClass = index < activeFlowIndex ? 'bg-ph-crimson-500/50' : 'bg-gray-200 dark:bg-white/10';
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
                    <XCircle size={18} className="shrink-0 mt-0.5 text-ph-crimson-600 dark:text-ph-crimson-400" />
                    <div className="flex-1">
                        <p className="font-semibold text-ph-crimson-700 dark:text-ph-crimson-400 text-[13px] mb-0.5">Terjadi Kesalahan</p>
                        <p className="text-[12px] leading-relaxed opacity-90">{error}</p>
                    </div>
                    <button 
                        onClick={() => setError(null)}
                        className="shrink-0 text-gray-400 hover:text-gray-700 dark:hover:text-white transition-colors p-0.5"
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
                       // Bypass layar login, langsung hubungkan ke state App.js
                       onLogin(username, adminLvl, undefined, true, isDiscordLinked);
                   }}
                   onDiscordRequired={(actualUsername) => {
                       // Update verifyUser to actual username so Discord workflow runs correctly
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
                    onLinkSuccess={(username, adminLvl, gold) => onLogin(username, adminLvl, undefined, true, true)}
                    setView={setView}
                    onError={setError}
                />
            )}

           </div>
          </div>
        </div>
      </div>
    </div>
  );
};
