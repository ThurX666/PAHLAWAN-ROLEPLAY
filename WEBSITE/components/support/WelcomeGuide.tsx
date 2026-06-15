import React, { useEffect, useState } from 'react';
import { isPreviewEnv, API_URL } from '../../config';

interface WelcomeGuideProps {
  userName: string;
  onClose: () => void;
}

export const WelcomeGuide: React.FC<WelcomeGuideProps> = ({ userName, onClose }) => {
    const [hasCharacter, setHasCharacter] = useState(false);
    const [hasOOCProfile, setHasOOCProfile] = useState(false);
    const [hasStory, setHasStory] = useState(false);
    const [hasDonated, setHasDonated] = useState(false);
    const [isDiscordLinked, setIsDiscordLinked] = useState(false);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        const fetchStatus = async () => {
            if (isPreviewEnv()) {
                setHasCharacter(true); 
                setHasOOCProfile(false);
                setHasStory(false);
                setHasDonated(false);
                setIsDiscordLinked(true);
                setLoading(false);
                return;
            }
            
            // Periksa prp_session untuk discord status terlebih dahulu
            try {
                const sessionStr = localStorage.getItem('prp_session');
                if (sessionStr) {
                    const session = JSON.parse(sessionStr);
                    if (session.isDiscordLinked) {
                        setIsDiscordLinked(true);
                    }
                }
            } catch (e) {}

            setLoading(true);
            try {
                // Fetch Characters
                const charRes = await fetch(`${API_URL}/api_characters.php?username=${encodeURIComponent(userName)}`);
                const charData = await charRes.json();
                if (charData.status === 'success' && charData.data.length > 0) {
                    setHasCharacter(true);
                }

                // Fetch Profile
                const profRes = await fetch(`${API_URL}/api_profile.php?username=${encodeURIComponent(userName)}`);
                const profData = await profRes.json();
                if (profData.status === 'success' && profData.data.ooc_name) {
                    setHasOOCProfile(true);
                }

                // Fetch Stories
                const storyRes = await fetch(`${API_URL}/api_stories.php?username=${encodeURIComponent(userName)}`);
                const storyData = await storyRes.json();
                if (storyData.status === 'success' && storyData.data.length > 0) {
                    setHasStory(true);
                }

                // Fetch Stats
                const statsRes = await fetch(`${API_URL}/api_user_stats.php?username=${encodeURIComponent(userName)}`);
                const statsData = await statsRes.json();
                if (statsData.status === 'success') {
                    const rawGoldStr = statsData.gold || '0';
                    const goldAmount = parseInt(String(rawGoldStr).replace(/\D/g, ''), 10) || 0;
                    if (goldAmount > 0 || (statsData.vipStatus && statsData.vipStatus !== 'None' && statsData.vipStatus !== '-')) {
                        setHasDonated(true);
                    }
                }

            } catch (e) {
                console.error("Error fetching welcome guide status", e);
            }
            setLoading(false);
        };
        fetchStatus();
    }, [userName]);

    const navigateTo = (tab: string) => {
        window.dispatchEvent(new CustomEvent('navigate-tab', { detail: { tab } }));
        onClose();
    };

    if (loading) {
        return <div className="text-center p-8 opacity-50 text-gray-500 dark:text-gray-400">Memuat panduan...</div>;
    }

    const steps = [
        {
            id: 'settings',
            title: 'Sinkronisasi Discord',
            desc: 'Wajib dilakukan sebelum memulai bermain.',
            isDone: isDiscordLinked,
            color: 'red'
        },
        {
            id: 'characters',
            title: 'Buat Karakter Baru',
            desc: 'Persiapkan identitas In-Game pertamamu.',
            isDone: hasCharacter,
            color: 'blue'
        },
        {
            id: 'story',
            title: 'Tulis Character Story',
            desc: 'Buka akses lisensi, faksi, & properti.',
            isDone: hasStory,
            color: 'purple'
        },
        {
            id: 'donation',
            title: 'Informasi Donasi',
            desc: 'Dapatkan fitur premium (VIP/Gold).',
            isDone: hasDonated,
            color: 'yellow'
        }
    ];

    return (
        <div className="font-sans max-w-2xl mx-auto py-4">
            <div className="text-center mb-8">
                <h2 className="text-2xl font-black mb-2 tracking-tight text-gray-900 dark:text-white">Selamat Datang!</h2>
                <p className="text-sm opacity-70 text-gray-600 dark:text-gray-300">Petualangan epikmu di kota ini dimulai di sini.</p>
            </div>
            
            <div className="mb-8">
                <p className="text-[15px] leading-relaxed mb-3 text-gray-800 dark:text-gray-200">Halo <strong>{userName}</strong>,</p>
                <p className="text-[15px] leading-relaxed opacity-90 m-0 text-gray-800 dark:text-gray-200">Agar pengalaman bermainmu maksimal, harap selesaikan langkah-langkah penting berikut:</p>
            </div>

            <div className="flex flex-col gap-4 mb-8">
                {steps.map((step, index) => {
                    const colorStyles = {
                        blue: 'text-blue-500 bg-blue-500/10 border-blue-500/20',
                        pink: 'text-pink-500 bg-pink-500/10 border-pink-500/20',
                        purple: 'text-purple-500 bg-purple-500/10 border-purple-500/20',
                        yellow: 'text-yellow-500 bg-yellow-500/10 border-yellow-500/20',
                        red: 'text-red-500 bg-red-500/10 border-red-500/20',
                        done: 'text-emerald-500 bg-emerald-500/5 border-emerald-500/20 text-opacity-50'
                    };

                    const IconNumOrCheck = step.isDone ? (
                        <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="3" strokeLinecap="round" strokeLinejoin="round"><polyline points="20 6 9 17 4 12"></polyline></svg>
                    ) : (
                        index + 1
                    );

                    return (
                        <div 
                            key={step.id}
                            onClick={() => !step.isDone && navigateTo(step.id)}
                            className={`flex items-center gap-4 border rounded-xl p-4 transition-all duration-300 ${
                                step.isDone 
                                ? 'bg-gray-50 dark:bg-white/5 border-gray-200 dark:border-white/10 opacity-70 grayscale-[50%]'
                                : 'cursor-pointer hover:bg-gray-100 dark:hover:bg-white/10 ' + colorStyles[step.color as keyof typeof colorStyles].split(' ')[2]
                            }`}
                        >
                            <div className={`w-10 h-10 rounded-lg flex items-center justify-center flex-shrink-0 font-black text-lg ${
                                step.isDone 
                                ? 'bg-emerald-500/10 text-emerald-500'
                                : colorStyles[step.color as keyof typeof colorStyles].split(' ').slice(0, 2).join(' ')
                            }`}>
                                {IconNumOrCheck}
                            </div>
                            
                            <div className="flex-grow">
                                <h4 className={`m-0 mb-1 text-[15px] font-bold ${step.isDone ? 'line-through text-gray-500 dark:text-gray-400 opacity-70' : 'text-gray-800 dark:text-gray-200'}`}>
                                    {step.title}
                                </h4>
                                <p className={`m-0 text-[13px] ${step.isDone ? 'text-gray-500 dark:text-gray-400 opacity-70' : 'text-gray-600 dark:text-gray-400'}`}>
                                    {step.desc}
                                </p>
                            </div>
                            
                            <div className="opacity-50 text-gray-800 dark:text-gray-200">
                                {step.isDone ? (
                                    <span className="text-emerald-500 font-bold text-xs uppercase tracking-wider px-2 py-1 bg-emerald-500/10 rounded">Selesai</span>
                                ) : (
                                    <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="m9 18 6-6-6-6"/></svg>
                                )}
                            </div>
                        </div>
                    );
                })}
            </div>

            <div className="border-t border-gray-200 dark:border-white/10 pt-6 flex flex-col items-center justify-center gap-4 mt-8">
                <p className="m-0 text-sm font-bold opacity-90 tracking-wide uppercase text-gray-800 dark:text-gray-300">Ikuti Komunitas Kami!</p>
                <div className="flex gap-6">
                    <a href="https://bit.ly/pahlawan-rp" target="_blank" className="opacity-70 hover:opacity-100 transition-opacity text-gray-800 dark:text-gray-300" title="Discord">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="currentColor"><path d="M20.317 4.3698a19.7913 19.7913 0 00-4.8851-1.5152.0741.0741 0 00-.0785.0371c-.211.3753-.4447.8648-.6083 1.2495-1.8447-.2762-3.68-.2762-5.4868 0-.1636-.3933-.4058-.8742-.6177-1.2495a.077.077 0 00-.0785-.037 19.7363 19.7363 0 00-4.8852 1.515.0699.0699 0 00-.0321.0277C.5334 9.0458-.319 13.5799.0992 18.0578a.0824.0824 0 00.0312.0561c2.0528 1.5076 4.0413 2.4228 5.9929 3.0294a.0777.0777 0 00.0842-.0276c.4616-.6304.8731-1.2952 1.226-1.9942a.076.076 0 00-.0416-.1057c-.6528-.2476-1.2743-.5495-1.8722-.8923a.077.077 0 01-.0076-.1277c.1258-.0943.2517-.1923.3718-.2914a.0743.0743 0 01.0776-.0105c3.9278 1.7933 8.18 1.7933 12.0614 0a.0739.0739 0 01.0785.0095c.1202.099.246.1981.3728.2924a.077.077 0 01-.0066.1276 12.2986 12.2986 0 01-1.873.8914.0766.0766 0 00-.0407.1067c.3604.698.7719 1.3628 1.225 1.9932a.076.076 0 00.0842.0286c1.961-.6067 3.9495-1.5219 6.0023-3.0294a.077.077 0 00.0313-.0552c.5004-5.177-.8382-9.6739-3.5485-13.6604a.061.061 0 00-.0312-.0286zM8.02 15.3312c-1.1825 0-2.1569-1.0857-2.1569-2.419 0-1.3332.9555-2.4189 2.157-2.4189 1.2108 0 2.1757 1.0952 2.1568 2.419 0 1.3332-.9555 2.4189-2.1569 2.4189zm7.9748 0c-1.1825 0-2.1569-1.0857-2.1569-2.419 0-1.3332.9554-2.4189 2.1569-2.4189 1.2108 0 2.1757 1.0952 2.1568 2.419 0 1.3332-.946 2.4189-2.1568 2.4189z" /></svg>
                    </a>
                    <a href="https://www.tiktok.com/@pahlawanroleplay?_r=1&_t=ZS-95tA12p3lPl" target="_blank" className="opacity-70 hover:opacity-100 transition-opacity text-gray-800 dark:text-gray-300" title="TikTok">
                        <svg width="24" height="24" viewBox="0 0 24 24" fill="currentColor"><path d="M12.525.02c1.31-.02 2.61-.01 3.91-.02.08 1.53.63 3.09 1.75 4.17 1.12 1.11 2.7 1.62 4.24 1.79v4.03c-1.44-.05-2.89-.35-4.2-.97-.57-.26-1.1-.59-1.62-.93-.01 2.92.01 5.84-.02 8.75-.08 2.78-1.5 5.54-3.76 7.18-2.26 1.63-5.26 1.99-7.83.99-2.58-1-4.51-3.23-5.22-5.96-.71-2.73 0-5.74 1.91-7.84 1.92-2.11 4.81-3.14 7.55-2.67v4.04c-1.3-.2-2.61-.09-3.8.46-1.19.55-2.17 1.56-2.53 2.82-.36 1.25-.13 2.67.62 3.73.74 1.05 2.01 1.65 3.32 1.59 1.3-.06 2.51-.78 3.12-1.92.62-1.14.73-2.52.48-3.79-.01-5.11-.02-10.23-.02-15.34z"/></svg>
                    </a>
                </div>
            </div>
        </div>
    );
};