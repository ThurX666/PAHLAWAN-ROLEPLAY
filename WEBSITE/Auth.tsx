
import React, { useState, useEffect } from 'react';
import { Hexagon, Star, Shield, AlertCircle, X, Smartphone, Map, Mic, Globe, TrendingUp, Users, Wifi, Radio } from 'lucide-react';
import { LoginForm } from './auth/LoginForm';
import { RegisterForm } from './auth/RegisterForm';
import { ForgotPasswordForm } from './auth/ForgotPasswordForm';
import { VerifyForm } from './auth/VerifyForm';
import { DiscordLinkForm } from './auth/DiscordLinkForm';
import { isPreviewEnv, API_URL } from '../config';
import { ServerStats } from '../types';

interface AuthProps {
  onLogin: (username: string, adminLevel?: number, password?: string) => void;
  serverStats?: ServerStats;
}

type AuthView = 'login' | 'register' | 'forgot' | 'verify' | 'discord';

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

    if (isPreviewEnv()) {
        // MODE PREVIEW (DUMMY)
        setTimeout(() => {
            const normalizedUser = usernameInput.toLowerCase().trim();
            // SIMULATION VALIDATION LOGIC
            if (normalizedUser === 'admin' || normalizedUser === 'player') {
                setLoading(false);
                onLogin(usernameInput, undefined, undefined, true); // password is not needed for dummy
            } else {
                setLoading(false);
                setError("Kredensial Login tidak valid. Silakan periksa kembali username dan password Anda.");
            }
        }, 1000);
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
            if (errorMessage === "Failed to fetch") {
                setError(`Server lokal tidak merespon (API URL: ${API_URL}). Pastikan server PHP jalan.`);
            } else {
                setError(`Gagal menghubungi server. Details: ${errorMessage}`);
            }
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

  return (
    <div className="min-h-[100dvh] flex items-center justify-center relative overflow-hidden font-sans bg-gray-50 dark:bg-[#050505]">
      
      {/* POPUP NOTIFICATION (Modal) */}
      {error && (
        <div className="fixed inset-0 z-[100] flex items-center justify-center p-4 bg-black/60 backdrop-blur-sm animate-[fadeIn_0.3s_ease-out]">
            <div className="bg-white dark:bg-[#1a1a1a] border border-red-500/30 max-w-md w-full rounded-2xl shadow-2xl relative overflow-hidden animate-[slideInUp_0.3s_ease-out]">
                {/* Decorative */}
                <div className="absolute top-0 left-0 w-full h-1 bg-red-500"></div>
                <div className="absolute -left-10 -top-10 w-32 h-32 bg-red-600/20 rounded-full blur-3xl pointer-events-none"></div>
                
                <div className="p-6 relative z-10">
                    <div className="flex items-center gap-4 mb-4">
                        <div className="bg-red-500/20 p-3 rounded-full text-red-500 shrink-0">
                            <AlertCircle size={32} />
                        </div>
                        <div>
                           <h4 className="font-black text-xl text-gray-900 dark:text-white uppercase tracking-wider">Akses Ditolak</h4>
                           <p className="text-sm text-red-500 font-medium">Terjadi Kesalahan</p>
                        </div>
                    </div>
                    
                    <div className="bg-gray-100 dark:bg-black/40 p-4 rounded-xl border border-gray-200 dark:border-white/5 mb-6">
                        <p className="text-gray-700 dark:text-gray-200 text-sm leading-relaxed">
                            {error}
                        </p>
                    </div>

                    <button 
                        onClick={() => setError(null)} 
                        className="w-full py-3.5 bg-red-600 hover:bg-red-500 text-white rounded-xl font-bold transition-all transform hover:scale-[1.02] active:scale-[0.98] shadow-lg shadow-red-600/20 flex items-center justify-center gap-2 uppercase tracking-wider text-sm"
                    >
                        <X size={18} /> Tutup Pesan
                    </button>
                </div>
            </div>
        </div>
      )}

      {/* Dynamic Background */}
      <div className="absolute inset-0 z-0">
         <div className="absolute top-[-10%] left-[-10%] w-[60%] h-[60%] rounded-full bg-red-600/20 blur-[150px] animate-pulse-slow"></div>
         <div className="absolute bottom-[-10%] right-[-10%] w-[60%] h-[60%] rounded-full bg-amber-600/10 blur-[150px] animate-pulse-slow" style={{animationDelay: '1s'}}></div>
         <div className="absolute inset-0 bg-grid-pattern-light dark:bg-grid-pattern opacity-[0.05]"></div>
      </div>

      <div className="relative z-10 w-full max-w-5xl h-[100dvh] md:h-[650px] flex md:rounded-3xl overflow-hidden shadow-2xl dark:shadow-black/80 border-0 md:border border-gray-200 dark:border-white/10 bg-white/90 md:bg-white/90 dark:bg-[#121212]/80 dark:md:bg-[#121212]/80 backdrop-blur-xl animate-[fadeIn_0.5s_ease-out]">
        
        {/* LEFT SIDE: Showcase Slideshow (Hidden on mobile) */}
        <div className="hidden md:flex w-1/2 relative bg-black flex-col justify-between p-12 overflow-hidden">
             {SLIDES.map((slide, index) => (
                 <div 
                    key={slide.id}
                    className={`absolute inset-0 transition-opacity duration-1000 ease-in-out ${index === currentSlide ? 'opacity-100' : 'opacity-0'}`}
                 >
                    {/* Darker overlay for text readability */}
                    <div className="absolute inset-0 bg-black/20 z-10"></div>
                    <img 
                        src={slide.image} 
                        className={`w-full h-full object-cover transition-transform duration-[10000ms] ease-linear ${index === currentSlide ? 'scale-110' : 'scale-100'}`}
                        alt={slide.title}
                    />
                 </div>
             ))}
             
             {/* Gradient Overlay bottom */}
             <div className="absolute inset-0 bg-gradient-to-t from-black via-black/40 to-transparent z-10"></div>
             
             <div className="relative z-20 mt-auto mb-10">
                 <div key={activeSlide.id} className="animate-[fadeIn_0.5s_ease-out]">
                     <div className={`w-14 h-14 rounded-2xl flex items-center justify-center mb-6 shadow-lg bg-gradient-to-br ${activeSlide.color} backdrop-blur-md border border-white/20`}>
                        <SlideIcon className="text-white" fill="currentColor" size={28} />
                     </div>
                     <h1 className="text-4xl font-black text-white uppercase italic tracking-tighter leading-none mb-3 drop-shadow-lg">
                        {activeSlide.title}
                     </h1>
                     <p className="text-gray-300 text-sm max-w-sm leading-relaxed drop-shadow-md border-l-4 border-white/30 pl-4 py-1 bg-black/20 rounded-r-lg backdrop-blur-sm">
                        {activeSlide.subtitle}
                     </p>
                 </div>
             </div>
             
             {/* Indicators */}
             <div className="relative z-20 flex space-x-2">
                 {SLIDES.map((slide, index) => (
                     <button 
                        key={slide.id}
                        onClick={() => setCurrentSlide(index)}
                        className={`h-1.5 rounded-full transition-all duration-300 ${index === currentSlide ? 'w-12 bg-white' : 'w-2 bg-white/20 hover:bg-white/40'}`}
                     />
                 ))}
             </div>
        </div>

        {/* RIGHT SIDE: Auth Form Container */}
        <div className="w-full md:w-1/2 flex flex-col bg-white/5 backdrop-blur-sm relative h-full overflow-y-auto">
          
          {/* Top Center Decoration - UNIFIED Server Status Bar (CENTERED) */}
          <div className="absolute top-0 left-0 w-full p-4 md:p-6 z-20 flex justify-center pointer-events-none">
              <div className="flex items-center gap-2 md:gap-3 bg-black/60 backdrop-blur-md border border-white/10 rounded-full px-3 py-1.5 md:px-4 md:py-2 pointer-events-auto">
                  {/* Status */}
                  <div className="flex items-center gap-1.5 md:gap-2">
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
                      <span className={`text-[8px] md:text-[9px] font-black uppercase tracking-wider ${serverStats?.status === 'Online' ? 'text-white' : serverStats?.status === 'Loading' ? 'text-yellow-400' : 'text-red-400'}`}>
                          {serverStats?.status === 'Online' ? 'Online' : serverStats?.status === 'Loading' ? 'Loading' : 'Offline'}
                      </span>
                  </div>

                  {/* Divider */}
                  <div className="w-px h-3 bg-white/20"></div>

                  {/* Players */}
                  <div className="flex items-center gap-1 md:gap-1.5">
                      <Users size={10} className="text-gray-400 md:w-3 md:h-3" />
                      <span className="text-[8px] md:text-[9px] font-bold text-white font-mono">{serverStats?.players || 0}</span>
                  </div>

                  {/* Divider */}
                  <div className="w-px h-3 bg-white/20"></div>

                  {/* IP */}
                  <div className="flex items-center gap-1 md:gap-1.5">
                      <Wifi size={10} className="text-amber-500 md:w-3 md:h-3" />
                      <span className="text-[8px] md:text-[9px] font-bold text-gray-300 font-mono tracking-wide">{serverStats?.ip_address || "pahlawan-rp.com:7777"}</span>
                  </div>
              </div>
          </div>

          {/* Top Spacer to prevent overlap with absolute status bar */}
          <div className="shrink-0 h-[100px] md:h-[120px] pb-0 -mb-9"></div>

          <div className="max-w-sm mx-auto w-full shrink-0 px-6 md:px-8 py-2">
            
            {/* Logo */}
            <div className="flex justify-center mb-8 mt-0">
                {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
                <img 
                    src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} 
                    alt="Pahlawan Roleplay" 
                    className="w-56 md:w-64 max-h-28 md:max-h-32 object-contain hover:scale-105 transition-transform duration-500" 
                />
            </div>

            {/* MODULAR FORMS */}
            {view === 'login' && (
                <>
                    <LoginForm onSubmit={handleLoginSubmit} setView={setView} loading={loading} />
                    {isPreviewEnv() && (
                        <button 
                            onClick={() => { setVerifyUser("PreviewPlayer"); setView('discord'); }} 
                            className="mt-4 w-full bg-white/5 border border-white/10 text-white rounded-lg py-2 text-xs opacity-75 hover:opacity-100 transition-all font-mono hover:bg-white/10"
                        >
                            👁️ Preview Tampilan Wajib Discord
                        </button>
                    )}
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

          {/* Bottom Spacer */}
          <div className="flex-1 min-h-[80px] shrink-0"></div>
        </div>
      </div>
    </div>
  );
};
