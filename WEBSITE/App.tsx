
import React, { useState, useEffect } from 'react';
import { Layout } from './components/Layout';
import { Dashboard } from './components/Dashboard';
import { CharacterList } from './components/CharacterList';
import { CharacterDetail } from './components/CharacterDetail';
import { Donation } from './components/Donation';
import { Settings } from './components/Settings';
import { Auth } from './components/Auth';
import { AdminPanel } from './components/admin/AdminPanel';
import { TicketSystem } from './components/TicketSystem';
import { CharacterStoryPage } from './components/CharacterStory';
import { Requests } from './components/requests/RequestsPage';
import { ServerStats, Character, CharacterStory, PromoItem, InboxMessage, UserProfile } from './types';
import { AlertTriangle, CheckCircle } from 'lucide-react';
import { isPreviewEnv, API_URL, UPLOAD_BASE_URL, getResolvedApiUrl } from './config';

import { MOCK_TICKETS } from './data/mockData';

const MOCK_STATS: ServerStats = {
  hostname: "Pahlawan Roleplay [ID/SEA]",
  players: 482,
  maxPlayers: 1000,
  mode: "Roleplay",
  map: "San Andreas",
  weather: "Cerah",
  status: "Online",
  ip_address: "mainsamp.pahlawan-rp.com:7777"
};

const MOCK_CHARACTERS_DATA: Character[] = [
  { 
    id: 1, 
    name: "Carl_Johnson", 
    level: 42, 
    money: 15420, 
    bank: 2500000, 
    faction: "Grove Street", 
    lastLogin: "2024-03-10 14:30", 
    status: "Online", 
    skinId: 0,
    storyStatus: 'Active',
    logs: [
        { id: 101, timestamp: "2024-03-10 14:30", action: "Login", details: "Masuk kota dari IP 192.168.x.x" },
        { id: 102, timestamp: "2024-03-10 14:45", action: "Perintah", details: "/pay 2 (Ryder_Wilson) 500" },
        { id: 103, timestamp: "2024-03-09 20:00", action: "Pekerjaan", details: "Menyelesaikan misi Trucker (Dapat $250)" }
    ]
  },
  { 
    id: 2, 
    name: "Ryder_Wilson", 
    level: 5, 
    money: 500, 
    bank: 1200, 
    faction: "Warga Sipil", 
    lastLogin: "2024-03-09 09:15", 
    status: "Online", 
    skinId: 271,
    storyStatus: 'Revision',
    logs: [
        { id: 201, timestamp: "2024-03-09 09:15", action: "Login", details: "Masuk kota" }
    ]
  }
];

const INITIAL_PLAYER_STORIES: CharacterStory[] = [
    { id: 1, characterId: 1, characterName: "Carl_Johnson", content: "Lahir di Los Santos, CJ kembali dari Liberty City setelah ibunya meninggal. Ia berusaha membangun kembali Grove Street Families...", status: 'Active', lastUpdated: '2023-01-01' },
    { id: 2, characterId: 2, characterName: "Ryder_Wilson", content: "Ryder adalah teman masa kecil CJ. Dia selalu memakai kacamata hitam dan topi hijau.", status: 'Revision', adminFeedback: "Tolong tambahkan lebih banyak detail tentang latar belakang keluarganya dan bagaimana dia bisa terlibat dengan geng.", lastUpdated: '2024-03-10' },
];

const INITIAL_PROMO_ITEMS: PromoItem[] = [
  {
    id: 'p1',
    name: "Mansion Mulholland",
    type: "Property",
    priceGold: 5000,
    originalPriceGold: 7500,
    image: "https://static.wikia.nocookie.net/gtawiki/images/4/4c/MaddDogg%27sCrib-GTASA-exterior.jpg",
    description: "Rumah mewah dengan interior custom eksklusif, garasi 10 slot, dan helipad pribadi.",
    stats: [
      { label: "Lokasi", value: "Richman" },
      { label: "Garage", value: "10 Slots" },
      { label: "Interior", value: "Custom Luxury" }
    ],
    isLimited: true,
    isActive: true
  },
  {
    id: 'v1',
    name: "Infernus Neon Spec",
    type: "Vehicle",
    priceGold: 3500,
    image: "https://gta.com.ua/files/gta-sa/cars/Infernus.jpg",
    description: "Kendaraan tercepat di San Andreas dengan stiker neon eksklusif dan handling balap.",
    stats: [
      { label: "Kecepatan", value: "240 km/h" },
      { label: "Tipe", value: "Sport" },
      { label: "Mod", value: "Full Neon" }
    ],
    isLimited: true,
    isActive: true
  }
];

const INITIAL_INBOX: InboxMessage[] = [
  { 
    id: 'msg-1', 
    title: 'Welcome to Pahlawan Roleplay! 🎉', 
    type: 'System', 
    date: new Date().toISOString(), 
    read: false,
    template: 'Welcome'
  },
  {
    id: 'msg-char-1',
    title: 'Karakter Dibuat: Ucok_Slepbeuw',
    type: 'System',
    date: new Date(Date.now() - 3600000).toISOString(),
    read: true,
    template: 'CharacterCreated',
    metadata: {
        name: 'Ucok_Slepbeuw',
        gender: 'Laki-laki',
        age: 22,
        height: 175,
        weight: 65,
        origin: 'United States of America'
    }
  },
  {
    id: 'msg-discord-1',
    title: 'Discord Berhasil Ditautkan 🎉',
    type: 'System',
    date: new Date().toISOString(),
    read: false,
    template: 'DiscordLinked',
    metadata: {
      discordUsername: 'DiscordUser#1234'
    }
  },
  {
    id: 'msg-alert-1',
    title: 'Peringatan Keamanan: Login Baru Terdeteksi',
    type: 'System',
    date: new Date(Date.now() - 1800000).toISOString(),
    read: false,
    template: 'NewLoginDetected',
    metadata: {
        time: '03 Mei 2026, 22:50 WIB',
        device: 'Chrome on Windows',
        ip: '114.120.33.201',
        location: 'Jakarta, Indonesia'
    }
  },
  {
    id: 'msg-pw-1',
    title: 'Keamanan Akun: Kata Sandi Diubah',
    type: 'System',
    date: new Date(Date.now() - 3600000).toISOString(),
    read: true,
    template: 'PasswordChanged',
    metadata: {
        time: '03 Mei 2026, 21:00 WIB'
    }
  },
  {
    id: 'msg-ooc-1',
    title: 'Pemberitahuan: Hasil Tinjauan Data OOC',
    type: 'System',
    date: new Date(Date.now() - 86400000).toISOString(), // 1 day ago
    read: true,
    template: 'OocProfileReview',
    metadata: {
        type: 'Ganti Nama Asli (OOC)',
        status: 'Diizinkan',
        message: 'Data sudah sesuai, di-acc bro!'
    }
  },
  {
    id: 'msg-cs-1',
    title: 'Pemberitahuan: Character Story Ucok_Slepbeuw',
    type: 'System',
    date: new Date(Date.now() - 172800000).toISOString(),
    read: true,
    template: 'CharacterStoryReview',
    metadata: {
        characterName: 'Ucok_Slepbeuw',
        status: 'Disetujui',
        message: 'Cerita bagus dan sesuai lore, enjoy!'
    }
  },
  {
    id: 'msg-don-1',
    title: 'Status Donasi Diperbarui: Berhasil',
    type: 'System',
    date: new Date(Date.now() - 259200000).toISOString(), // 3 days ago
    read: true,
    template: 'PaymentProcessed',
    metadata: {
        transactionId: '#DON-1',
        itemName: '5000 GC',
        amount: 'Rp 50.000',
        status: 'Berhasil'
    }
  },
  {
    id: 'msg-ticket-1',
    title: 'Pemberitahuan: Tiket Bantuan "Bug Kendaraan Hilang" Ditutup',
    type: 'System',
    date: new Date(Date.now() - 400000000).toISOString(), // ~4+ days ago
    read: true,
    template: 'TicketClosed',
    metadata: {
        ticketId: '#TICKET-1',
        ticketTitle: 'Bug Kendaraan Hilang',
        category: 'Bug In-Game',
        status: 'Closed'
    }
  },
  {
    id: 'msg-voucher-1',
    title: 'Hadiah Spesial: Voucher Event Lebaran',
    message: 'Selamat! Kamu mendapatkan hadiah spesial dari kami atas partisipasi dalam event Lebaran Mabar 2026. Jangan lupa diklaim ya bro!',
    type: 'Voucher',
    date: new Date(Date.now() - 500000000).toISOString(), 
    read: true,
    code: 'LEBARAN2026',
    itemName: 'Mobil Infernus Eksklusif',
    itemDescription: 'Kendaraan mewah 2 pintu tercepat di kota. Lengkap dengan full modif.',
    itemPrice: 500000
  },
  {
    id: 'msg-admin-1',
    title: 'Informasi: Update Kota Versi 2.5',
    message: 'Halo warga Pahlawan Roleplay,\n\nMalam ini akan ada maintenance pada jam 00:00 WIB untuk deploy update versi 2.5. Update meliputi:\n- Penambahan job Mekanik versi baru.\n- Optimasi ekonomi server.\n- Perbaikan bug kendaraan hilang.\n\nHarap simpan semua kendaraan sebelum maintenance.\n\nTerima kasih,\nAdmin UCP',
    type: 'Admin',
    date: new Date(Date.now() - 600000000).toISOString(),
    read: true,
  },
  {
    id: 'msg-warn-1',
    title: 'Peringatan Server: Pelanggaran Rules (Deathmatching)',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 700000000).toISOString(),
    read: true,
    template: 'ServerWarning',
    metadata: {
        characterName: 'Ucok_Slepbeuw',
        adminName: 'Admin_Brave',
        reason: 'Deathmatching (Pasal 4)',
        currentWarn: 1
    }
  },
  {
    id: 'msg-vip-1',
    title: 'Pemberitahuan: Status VIP Bronze Berakhir',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 800000000).toISOString(),
    read: true,
    template: 'VipExpired',
    metadata: {
        vipTier: 'Bronze'
    }
  },
  {
    id: 'msg-admin-2',
    title: 'Informasi: Pendaftaran Angkatan Kepolisian Dibuka',
    message: 'Kabar Gembira!\n\nKami membuka penerimaan angkatan Police Academy ke-23. Jika Anda merasa terpanggil untuk melindungi dan melayani warga kota, segera cek persyaratannya di Forum atau akses menu Discord Factions kami. Pendaftaran ditutup lusa jam 12:00 WIB. \n\n#ServeAndProtect',
    type: 'Admin',
    date: new Date(Date.now() - 900000000).toISOString(),
    read: true,
  },
  {
    id: 'msg-voucher-2',
    title: 'Kompensasi: Gangguan Jaringan Kemarin',
    message: 'Mohon maaf atas ketidaknyamanan yang terjadi akibat downtime server kemarin. Sebagai bentuk permohonan maaf, kami memberikan 1000 Gold Coin gratis kepada setiap Player aktif. Terima kasih atas kesabaran Anda.',
    type: 'Voucher',
    code: 'SORRYDOWN2026',
    itemName: '1000 Gold Coins (GC)',
    itemDescription: 'Dapat digunakan untuk membeli kebutuhan di Donation Shop.',
    itemPrice: 0,
    date: new Date(Date.now() - 1000000000).toISOString(),
    read: true,
  },
  {
    id: 'msg-unban-1',
    title: 'Pemberitahuan: Permohonan Unban Disetujui',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 1200000000).toISOString(),
    read: true,
    template: 'UnbanApproved',
    metadata: {
        adminName: 'High_Staff'
    }
  },
  {
    id: 'msg-prop-1',
    title: 'Peringatan Sistem: Inaktivitas Properti (Rumah)',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 1300000000).toISOString(),
    read: true,
    template: 'PropertyInactivityWarning',
    metadata: {
        propertyType: 'Rumah',
        propertyId: 105,
        propertyZone: 'Vinewood',
        inactiveDays: 10,
        daysRemaining: 4
    }
  },
  {
    id: 'msg-cn-1',
    title: 'Informasi Nama Baru Karakter Sukses',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 1400000000).toISOString(),
    read: true,
    template: 'NamechangeSuccess',
    metadata: {
        oldName: 'Ucok_Slepbeuw',
        newName: 'Albert_Wesker'
    }
  },
  {
    id: 'msg-event-1',
    title: 'Undangan: Event Server Akhir Pekan (Live Music)',
    message: 'Warga Pahlawan Roleplay!\n\nJangan lewatkan Event Konser Musik spesial akhir pekan ini di Pantai Santa Maria. Akan ada banyak artis lokal kota, doorprize kendaraan, dan uang tunai jutaan dollar. Acara dimulai hari Sabtu, pukul 20:00 WIB. Datang bersama teman-temanmu dan ramaikan!\n\nSalam,\nEvent Management Team',
    type: 'Admin',
    date: new Date(Date.now() - 1900000000).toISOString(),
    read: true,
  },
  {
    id: 'msg-report-1',
    title: 'Laporan Pemain Ditanggapi',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 2200000000).toISOString(),
    read: true,
    template: 'PlayerReportResponded',
    metadata: {
        reportedPlayer: 'John_Doe',
        violation: 'Car Ramming',
        adminAction: 'Jail 60 menit & Warn 1'
    }
  },
  {
    id: 'msg-admin-3',
    title: 'Pengumuman: Rekrutmen Anggota Staff Baru',
    message: 'Warga Pahlawan Roleplay yang terhormat,\n\nKami mencari beberapa individu yang berdedikasi tinggi untuk bergabung sebagai Tim Relawan (Helper). Jika Anda aktif bermain, memiliki pemahaman luas tentang RP, dan ingin membantu pemain baru, segera ajukan lamaran Anda di Forum. Pendaftaran akan dibuka dari tanggal 01 Mei hingga 10 Mei 2026.\n\nTerima kasih,\nHigh Staff Team',
    type: 'Admin',
    date: new Date(Date.now() - 2800000000).toISOString(),
    read: true,
  },
  {
    id: 'msg-promo-1',
    title: 'Flash Sale Donasi Akhir Bulan!',
    message: 'Halo semuanya!\n\nJangan lewatkan promo Flash Sale akhir bulan ini! Semua paket VIP dan Gold Coins (GC) mendapatkan DISKON 40%. Promo hanya berlaku di hari Sabtu dan Minggu (Pukul 00:00 s.d 23:59 WIB). Gunakan kesempatan emas ini untuk upgrade karaktermu!\n\nSilakan cek Menu Donasi.',
    type: 'Admin',
    date: new Date(Date.now() - 3100000000).toISOString(),
    read: true,
  },
  {
    id: 'msg-refund-1',
    title: 'Informasi: Request Refund Disetujui',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 3400000000).toISOString(),
    read: true,
    template: 'RefundApproved',
    metadata: {
        assetName: 'Kendaraan Bug Meledak (Sultan)',
        command: '/autorefund',
        locationToClaim: 'Insurance'
    }
  },
  {
    id: 'msg-sec-2',
    title: 'Peringatan Server: Account Sharing (Share UCP)',
    message: '',
    type: 'System',
    date: new Date(Date.now() - 3700000000).toISOString(),
    read: true,
    template: 'ServerWarning',
    metadata: {
        characterName: 'Ucok_Slepbeuw',
        adminName: 'High_Staff',
        reason: 'Account Sharing (Share UCP)',
        currentWarn: 2
    }
  },
  {
    id: 'msg-fac-1',
    title: 'Informasi Faction: Anda Diterima!',
    message: `<div style="font-family:'Inter',system-ui,sans-serif;max-width:100%;"><div style="text-align:center;margin-bottom:24px;background:linear-gradient(135deg, rgba(59,130,246,0.1) 0%, rgba(59,130,246,0.05) 100%);border:1px solid rgba(59,130,246,0.2);padding:24px;border-radius:16px;"><div style="display:inline-flex;align-items:center;justify-content:center;width:64px;height:64px;background-color:#3b82f6;color:white;border-radius:16px;margin-bottom:16px;box-shadow:0 8px 16px -4px rgba(59,130,246,0.4);"><svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M16 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2"></path><circle cx="8.5" cy="7" r="4"></circle><polyline points="17 11 19 13 23 9"></polyline></svg></div><h2 style="font-size:20px;font-weight:800;margin:0 0 8px 0;letter-spacing:-0.5px;color:#3b82f6;text-transform:uppercase;">Aplikasi Faction Disetujui</h2><p style="font-size:14px;opacity:0.8;margin:0;line-height:1.5;">Lamaran Anda ke instansi resmi telah diterima.</p></div><div style="margin-bottom:24px;line-height:1.6;font-size:15px;"><p style="margin:0 0 12px 0;">Halo,</p><p style="margin:0;">Selamat! Karakter Anda telah diterima bekerja di faksi <strong>Los Santos Medical Department (LSMD)</strong>. Silakan segera menghubungi High Rank faksi tersebut in-game atau gabung di Discord Faksi mereka untuk prosedur penerimaan seragam medis Anda.</p></div></div>`,
    type: 'System',
    date: new Date(Date.now() - 4000000000).toISOString(),
    read: true,
  }
];

interface UserData {
  username: string;
  isAdmin: boolean;
  adminLevel?: number;
  vipStatus: { tier: string; expiredAt: string; } | null;
  gold: number;
}

const MOCK_USERS: UserData[] = [
  {
    username: 'Admin',
    isAdmin: true,
    adminLevel: 10,
    vipStatus: { tier: 'Diamond', expiredAt: '31 Des 2026, 23:59 WIB' },
    gold: 15000
  },
  {
    username: 'Player',
    isAdmin: false,
    vipStatus: null,
    gold: 2500
  }
];

const MOCK_ADMIN_PROFILE: UserProfile = {
  oocName: 'Udin Samsudin',
  address: 'Jakarta Selatan',
  phoneNumber: '081233546976',
  discordId: '',
  birthDate: '2025-03-22',
  gender: 'Male',
  isLocked: true
};

const MOCK_PLAYER_PROFILE: UserProfile = {
  oocName: '',
  address: '',
  phoneNumber: '',
  discordId: '',
  birthDate: '',
  gender: 'Male',
  isLocked: false
};

const App: React.FC = () => {
  // Ambil state dari cookie/localStorage (biar ga usah login ulang pas refresh)
  const getSession = () => {
    try {
      const sessionStr = localStorage.getItem('prp_session');
      return sessionStr ? JSON.parse(sessionStr) : null;
    } catch (e) {
      return null;
    }
  };
  
  const initSession = getSession();

  const [isAuthenticated, setIsAuthenticated] = useState(initSession !== null);
  const [currentUser, setCurrentUser] = useState<string>(initSession ? initSession.username : '');
  const [isDiscordLinked, setIsDiscordLinked] = useState<boolean>(initSession ? initSession.isDiscordLinked : false);
  const [activeTab, setActiveTab] = useState('dashboard');
  const INITIAL_SERVER_STATS: ServerStats = isPreviewEnv() ? MOCK_STATS : {
    hostname: "Fetching Server Data...",
    players: 0,
    maxPlayers: 0,
    mode: "-",
    map: "-",
    weather: "-",
    status: "Loading",
    ip_address: "Fetching..."
  };

  const [serverStats, setServerStats] = useState<ServerStats>(INITIAL_SERVER_STATS);
  const [characters, setCharacters] = useState<Character[]>(MOCK_CHARACTERS_DATA);
  const [userStories, setUserStories] = useState<CharacterStory[]>(INITIAL_PLAYER_STORIES);
  const [selectedCharacter, setSelectedCharacter] = useState<Character | null>(null);
  const [isAdmin, setIsAdmin] = useState(initSession ? initSession.isAdmin : false);
  const [adminLevel, setAdminLevel] = useState<number | undefined>(initSession ? initSession.adminLevel : undefined);
  const [vipStatus, setVipStatus] = useState<{ tier: string; expiredAt: string; } | null>(initSession ? initSession.vipStatus : null);
  const [userGold, setUserGold] = useState(initSession ? initSession.gold : 0);
  const [userProfile, setUserProfile] = useState<UserProfile | null>(null);

  // Inbox System State
  const [inboxMessages, setInboxMessages] = useState<InboxMessage[]>(INITIAL_INBOX);
  const [tickets, setTickets] = useState<any[]>(MOCK_TICKETS);

  // Promo Config State
  const [promoConfig, setPromoConfig] = useState({
    isActive: true,
    title: "Promo Spesial!",
    message: "Dapatkan Bonus Gold +20% untuk setiap donasi di atas Rp 100.000. Hanya hari ini!"
  });

  // Promo Items State (Shared)
  const [promoItems, setPromoItems] = useState<PromoItem[]>(INITIAL_PROMO_ITEMS);

  const [isDarkMode, setIsDarkMode] = useState(false);

  const [donationSubTab, setDonationSubTab] = useState<'exclusive' | 'vip' | 'gold'>('vip');
  const [ticketSystemTab, setTicketSystemTab] = useState<'inbox' | 'tickets'>('inbox');
  const [alertConfig, setAlertConfig] = useState<{title: string, message: string, type: 'warning' | 'success'} | null>(null);

  useEffect(() => {
    if (isPreviewEnv() || !initSession) return;

    fetch(`${API_URL}/session.php`, { credentials: 'include' })
      .then(async response => {
        if (!response.ok) throw new Error('invalid_session');
        return response.json();
      })
      .then(result => {
        if (result.status !== 'success') throw new Error('invalid_session');
        const sessionLevel = Number(result.data.admin_level || 0);
        setCurrentUser(result.data.username);
        setAdminLevel(sessionLevel);
        setIsAdmin(sessionLevel > 0);
      })
      .catch(() => {
        localStorage.removeItem('prp_session');
        setIsAuthenticated(false);
        setCurrentUser('');
        setIsAdmin(false);
        setAdminLevel(undefined);
      });
  }, []);

  // Periodic Server Stats Polling
  useEffect(() => {
    if (!isPreviewEnv()) {
      const fetchServerInfo = async () => {
        try {
           const res = await fetch(`${API_URL}/api_overview.php?action=server_info`);
           const data = await res.json();
           if (data && data.status === 'success') {
               setServerStats({
                   ...data.data
               });
           } else {
               setServerStats(prev => ({
                   ...prev,
                   status: 'Offline',
                   players: 0
               }));
           }
        } catch (e) {
           // Suppress "Failed to fetch" log to avoid console spam due to Mixed Content / CORS errors locally
           // console.error("Error fetching server info:", e);
           setServerStats(prev => ({
               ...prev,
               status: 'Offline',
               players: 0
           }));
        }
      };

      fetchServerInfo();
      const interval = setInterval(fetchServerInfo, 10000); // Poll every 10 seconds
      return () => clearInterval(interval);
    }
  }, []);

  // Fetch Inbox Messages
  useEffect(() => {
    if (!isPreviewEnv() && currentUser) {
      const fetchInbox = async () => {
        try {
          const res = await fetch(`${API_URL}/api_inbox.php?username=${encodeURIComponent(currentUser)}`);
          if (res.ok) {
            const data = await res.json();
            if (data.status === 'success' && Array.isArray(data.data)) {
              setInboxMessages(data.data);
            }
          }
        } catch (e) {
          console.error("Error fetching inbox messages:", e);
        }
      };
      
      fetchInbox();
    }
  }, [currentUser]);

  useEffect(() => {
    const handleNavigate = (e: any) => {
        if (e.detail && e.detail.tab) {
            handleTabChange(e.detail.tab);
        }
    };
    window.addEventListener('navigate-tab', handleNavigate);
    return () => window.removeEventListener('navigate-tab', handleNavigate);
  }, []);

  useEffect(() => {
    const root = window.document.documentElement;
    if (isDarkMode) {
      root.classList.add('dark');
    } else {
      root.classList.remove('dark');
    }
  }, [isDarkMode]);

  // Check for successful discord link redirect
  useEffect(() => {
    const urlParams = new URLSearchParams(window.location.search);
    if (urlParams.get('discord_success') === '1' && isAuthenticated) {
        const roleSuccess = urlParams.get('roleSuccess') !== '0';
        window.history.replaceState({}, document.title, window.location.pathname);
        setActiveTab('settings');
        setAlertConfig({
            title: "Discord Berhasil Ditautkan 🎉",
            message: roleSuccess 
                ? "Akun Discord Anda telah terhubung. Role Warga telah diberikan dan nickname telah diperbarui." 
                : "Akun Discord Anda telah terhubung. Namun, limitasi role mencegah perubahan nama dan pemberian role otomatis.",
            type: "success"
        });
    }
  }, [isAuthenticated]);

  useEffect(() => {
    if (isAuthenticated && currentUser) {
      if (!isPreviewEnv()) {
        const fetchCharacters = async () => {
          try {
            const res = await fetch(`${API_URL}/api_characters.php?username=${encodeURIComponent(currentUser)}`);
            const data = await res.json();
            if (data && data.status === 'success') {
                const mappedChars = data.data.map((char: any) => ({
                    id: parseInt(char.id),
                    name: char.name,
                    level: parseInt(char.level),
                    money: parseInt(char.money),
                    bank: parseInt(char.bank),
                    faction: char.faction,
                    jobName: char.job_name,
                    skinId: parseInt(char.skin_id),
                    status: char.status,
                    lastLogin: char.last_login,
                    storyStatus: char.story_status,
                    phoneNumber: char.phone_number,
                    playingHours: parseInt(char.playing_hours) || 0,
                    warns: parseInt(char.warns) || 0,
                    needsHunger: parseInt(char.needs_hunger) || 100,
                    needsThirsty: parseInt(char.needs_thirsty) || 100,
                    needsMood: parseInt(char.needs_mood) || 100,
                    licenseDriveExp: char.license_drive_exp,
                    licenseFlyExp: char.license_fly_exp,
                    licenseBoatExp: char.license_boat_exp,
                    licenseGunExp: char.license_gun_exp,
                    photoUrl: char.photoUrl,
                    logs: []
                }));
                setCharacters(mappedChars);
            }
          } catch (e) {
            console.error("Error fetching characters:", e);
          }
        };

        const fetchStories = async () => {
          try {
             const res = await fetch(`${API_URL}/api_stories.php?username=${encodeURIComponent(currentUser)}`);
             const data = await res.json();
             if (data && data.status === 'success') {
                 const mappedStories = data.data.map((story: any) => ({
                     id: parseInt(story.id),
                     characterId: parseInt(story.character_id),
                     characterName: story.character_name,
                     photoUrl: story.photoUrl || story.photo_url || story.photo_path || null,
                     skinId: parseInt(story.skin_id),
                     content: story.content,
                     status: story.status,
                     adminFeedback: story.admin_feedback,
                     reviewedBy: story.reviewed_by,
                     reviewedAt: story.reviewed_at,
                     plagiarismScore: parseInt(story.plagiarism_score),
                     lastUpdated: story.last_updated
                 }));
                 setUserStories(mappedStories);
             }
          } catch (e) {
             console.error("Error fetching stories:", e);
          }
        };

        const fetchInbox = async () => {
          try {
             const res = await fetch(`${API_URL}/api_inbox.php?username=${encodeURIComponent(currentUser)}`);
             const data = await res.json();
             if (data && data.status === 'success') {
                 setInboxMessages(data.data);
             }
          } catch (e) {
             console.error("Error fetching inbox:", e);
          }
        };

        const fetchDonationsData = async () => {
            try {
                const configRes = await fetch(`${API_URL}/api_admin_donations.php?action=get_promo`);
                const configText = await configRes.text();
                try {
                    const configData = JSON.parse(configText);
                    setPromoConfig({
                        isActive: configData.is_active == 1,
                        title: configData.title || '',
                        message: configData.description || ''
                    });
                } catch (e) {}

                const itemsRes = await fetch(`${API_URL}/api_admin_donations.php?action=get_items`);
                const itemsText = await itemsRes.text();
                try {
                    const itemsData = JSON.parse(itemsText);
                    if (Array.isArray(itemsData)) {
                        setPromoItems(itemsData.map(item => ({
                            id: item.id.toString(),
                            name: item.name,
                            type: item.type,
                            priceGold: parseInt(item.price_gold),
                            image: item.image_path ? (UPLOAD_BASE_URL ? `${UPLOAD_BASE_URL.endsWith('/') ? UPLOAD_BASE_URL : UPLOAD_BASE_URL + '/'}uploads/items/${item.image_path}` : `uploads/items/${item.image_path}`) : 'https://picsum.photos/seed/promo/400/200',
                            description: item.description,
                            stats: [],
                            isLimited: item.qty > 0,
                            isActive: item.is_active == 1
                        })));
                    }
                } catch (e) {}
            } catch (e) {
                console.error("Error fetching donations data:", e);
            }
        };

        const fetchUserStats = async () => {
            try {
                const res = await fetch(`${API_URL}/api_user_stats.php?username=${encodeURIComponent(currentUser)}&_t=${Date.now()}`);
                const data = await res.json();
                if (data.status === 'success') {
                    if (data.vipStatus && data.vipStatus !== 'None') {
                        setVipStatus({ tier: data.vipStatus.replace('VIP ', ''), expiredAt: data.vipExpired });
                    } else {
                        setVipStatus(null);
                    }
                    setUserGold(parseInt(String(data.gold || '0').replace(/\\D/g, '')) || 0);
                    
                    if (data.isDiscordLinked !== undefined) {
                        setIsDiscordLinked(data.isDiscordLinked);
                        // Also update localStorage
                        try {
                            const sessionStr = localStorage.getItem('prp_session');
                            if (sessionStr) {
                                const session = JSON.parse(sessionStr);
                                session.isDiscordLinked = data.isDiscordLinked;
                                localStorage.setItem('prp_session', JSON.stringify(session));
                            }
                        } catch(e) {}
                    }
                }
            } catch (e) {
                console.error("Error fetching user stats:", e);
            }
        };

        const fetchProfile = async () => {
            try {
                const res = await fetch(`${API_URL}/api_profile.php?username=${encodeURIComponent(currentUser)}&_t=${Date.now()}`);
                const data = await res.json();
                if (data && data.status === 'success') {
                    setUserProfile({
                        oocName: data.data.ooc_name || '',
                        birthDate: data.data.birth_date || '',
                        address: data.data.address || '',
                        phoneNumber: data.data.phone_number || '',
                        discordId: data.data.discord_id || '',
                        gender: data.data.gender || '',
                        isLocked: data.data.is_locked === '1' || data.data.is_locked === 1 || data.data.is_locked === true
                    });
                }
            } catch (e) {
                console.error("Error fetching profile:", e);
            }
        };

        fetchCharacters();
        fetchStories();
        fetchInbox();
        fetchDonationsData();
        fetchUserStats();
        fetchProfile();
      } else {
        setCharacters(MOCK_CHARACTERS_DATA);
        setUserStories(INITIAL_PLAYER_STORIES);
        setServerStats(MOCK_STATS);
        setInboxMessages(INITIAL_INBOX);
      }
    }
  }, [isAuthenticated, currentUser]);

  const toggleTheme = () => {
    setIsDarkMode(!isDarkMode);
  };

  const handleLogin = (username: string, overrideAdminLevel?: number, password?: string, isLoginEvent?: boolean, isDiscordLinkedParam?: boolean) => {
    // KONDISI PREVIEW (MOCK) ATAU JIKA LOGIN BERHASIL DARI API
    const user = MOCK_USERS.find(u => u.username.toLowerCase() === username.toLowerCase()) || {
      username: username || 'Player',
      isAdmin: username.toLowerCase() === 'admin' || (overrideAdminLevel && overrideAdminLevel > 0) ? true : false,
      adminLevel: overrideAdminLevel !== undefined ? overrideAdminLevel : (username.toLowerCase() === 'admin' ? 10 : undefined),
      vipStatus: null,
      gold: 0,
      isDiscordLinked: isDiscordLinkedParam || false
    };

    setIsAdmin(user.isAdmin);
    setAdminLevel(user.adminLevel);
    setCurrentUser(user.username);
    setVipStatus(user.vipStatus);
    setUserGold(user.gold);
    setIsDiscordLinked(user.isDiscordLinked);
    setIsAuthenticated(true);
    
    // Simpan ke localStorage
    localStorage.setItem('prp_session', JSON.stringify({
       username: user.username,
       isAdmin: user.isAdmin,
       adminLevel: user.adminLevel,
       vipStatus: user.vipStatus,
       gold: user.gold,
       isDiscordLinked: user.isDiscordLinked
    }));

    if (isLoginEvent && isPreviewEnv()) {
       setInboxMessages(prev => [{
           id: `msg-login-${Date.now()}`,
           title: 'Peringatan Keamanan: Login Baru Terdeteksi',
           type: 'System',
           date: new Date().toISOString(),
           read: false,
           template: 'NewLoginDetected',
           metadata: {
               time: new Date().toLocaleString('id-ID', {day: '2-digit', month: 'short', year: 'numeric', hour: '2-digit', minute: '2-digit'}) + ' WIB',
               device: 'Mock Browser on AI Studio',
               ip: '127.0.0.1',
               location: 'Localhost / Preview'
           }
       }, ...prev]);
    }
  };

  const handleLogout = () => {
    if (!isPreviewEnv()) {
      fetch(`${API_URL}/session.php`, {
        method: 'POST',
        credentials: 'include',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ action: 'logout' })
      }).catch(() => undefined);
    }

    // Hapus sesi
    localStorage.removeItem('prp_session');
    
    setIsAuthenticated(false);
    setCurrentUser('');
    setIsAdmin(false);
    setAdminLevel(undefined);
  };

  const handleTabChange = (tab: string) => {
    if (tab.startsWith('donation:')) {
      const subTab = tab.split(':')[1] as 'exclusive' | 'vip' | 'gold';
      setDonationSubTab(subTab);
      setActiveTab('donation');
    } else if (tab.startsWith('tickets:')) {
      const subTab = tab.split(':')[1] as 'inbox' | 'tickets';
      setTicketSystemTab(subTab);
      setActiveTab('tickets');
    } else {
      if (tab === 'donation') {
        setDonationSubTab('vip'); // Reset to default when clicking the main menu
      }
      if (tab === 'tickets') {
        setTicketSystemTab('inbox');
      }
      setActiveTab(tab);
    }
    setSelectedCharacter(null);
  };

  const handleUpdateCharacter = (updatedChar: Character) => {
      setCharacters(prev => prev.map(c => c.id === updatedChar.id ? updatedChar : c));
      setSelectedCharacter(updatedChar);
  };

  const handleSubmitStory = (charId: number, content: string) => {
      const charName = characters.find(c => c.id === charId)?.name || 'Unknown';
      const existingStoryIndex = userStories.findIndex(s => s.characterId === charId);
      const newStory: CharacterStory = {
          id: existingStoryIndex > -1 ? userStories[existingStoryIndex].id : Date.now(),
          characterId: charId,
          characterName: charName,
          content: content,
          status: 'Pending',
          lastUpdated: new Date().toISOString()
      };

      if (existingStoryIndex > -1) {
          const updated = [...userStories];
          updated[existingStoryIndex] = newStory;
          setUserStories(updated);
      } else {
          setUserStories([...userStories, newStory]);
      }
      setCharacters(prev => prev.map(c => c.id === charId ? {...c, storyStatus: 'Pending'} : c));
      
      setAlertConfig({
          title: "Berhasil",
          message: "Cerita berhasil dikirim untuk direview!",
          type: "success"
      });
  };

  const handleSendNotification = async (msg: InboxMessage) => {
    if (isPreviewEnv()) {
        setInboxMessages(prev => [msg, ...prev]);
        return;
    }
    
    try {
        const res = await fetch(`${API_URL}/api_inbox.php`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                action: 'send_message',
                // For admin sending notifications, they usually target a specific user.
                // Currently msg doesn't have a 'username' field to specify the target,
                // so we will default to `currentUser` unless the caller provides a way.
                // NOTE: Let's assume Admin Panel passes target username as a property if needed,
                // otherwise it sends to the current user (e.g. self purchase).
                username: (msg as any).targetUsername || currentUser,
                title: msg.title,
                message: msg.message,
                type: msg.type,
                code: msg.code,
                itemName: msg.itemName,
                itemDescription: msg.itemDescription,
                itemPrice: msg.itemPrice,
                template: msg.template,
                metadata: msg.metadata
            })
        });
        const data = await res.json();
        if (data.status === 'success') {
            msg.id = data.id.toString(); // Update ID to match backend
            const targetUser = (msg as any).targetUsername || currentUser;
            if (targetUser === currentUser) {
                setInboxMessages(prev => [msg, ...prev]);
            }
        }
    } catch (e) {
        console.error(e);
    }
  };

  const handleReadMessage = async (id: string) => {
      setInboxMessages(prev => prev.map(msg => String(msg.id) === String(id) ? { ...msg, read: true } : msg));
      if (!isPreviewEnv()) {
          fetch(`${API_URL}/api_inbox.php`, {
              method: 'PUT',
              headers: { 'Content-Type': 'application/json' },
              body: JSON.stringify({ message_id: id })
          }).catch(e => {
              console.error("Error updating message read status:", e);
          });
      }
  };

  const handleRedeemGoldItem = async (characterId: number, item: { name: string; price: number; description?: string }) => {
      if (userGold < item.price) {
          setAlertConfig({
              title: "Gagal",
              message: "Saldo Gold tidak mencukupi!",
              type: "warning"
          });
          return false;
      }

      const character = characters.find(c => c.id === characterId);
      if (!character) return false;

      // Generate Voucher Code (16 random alphanumeric characters)
      const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
      let randomCode = '';
      for (let i = 0; i < 16; i++) {
          randomCode += chars.charAt(Math.floor(Math.random() * chars.length));
      }
      // Format as XXXX-XXXX-XXXX-XXXX
      const voucherCode = randomCode.match(/.{1,4}/g)?.join('-') || randomCode;

      // Create Inbox Message payload
      const newMessage: InboxMessage = {
          id: `msg-${Date.now()}`,
          title: `Pembelian ${item.name} Berhasil`,
          message: `Anda telah menukarkan ${item.price} Gold untuk ${item.name}. Silakan redeem di dalam game menggunakan command pada karakter ${character.name}.`,
          type: 'Voucher',
          code: voucherCode,
          itemName: item.name,
          itemPrice: item.price,
          itemDescription: item.description,
          date: new Date().toISOString(),
          read: false
      };

      if (!isPreviewEnv()) {
          try {
              // Deduct gold from backend
              const deductRes = await fetch(`${API_URL}/api_donations.php`, {
                  method: 'POST',
                  headers: { 'Content-Type': 'application/json' },
                  body: JSON.stringify({
                      action: 'deduct_gold',
                      username: currentUser,
                      amount: item.price,
                      itemId: (item as any).id || null
                  })
              });
              const deductData = await deductRes.json();
              
              if (deductData.status !== 'success') {
                  setAlertConfig({
                      title: "Gagal",
                      message: deductData.message || "Gagal memotong saldo Gold.",
                      type: "warning"
                  });
                  return false;
              }
              setUserGold(deductData.new_gold);

              const res = await fetch(`${API_URL}/api_inbox.php`, {
                  method: 'POST',
                  headers: { 'Content-Type': 'application/json' },
                  body: JSON.stringify({
                      action: 'send_message',
                      username: currentUser,
                      title: newMessage.title,
                      message: newMessage.message,
                      type: newMessage.type,
                      code: newMessage.code,
                      itemName: newMessage.itemName,
                      itemDescription: newMessage.itemDescription,
                      itemPrice: newMessage.itemPrice
                  })
              });
              const data = await res.json();
              if (data.status === 'success') {
                  newMessage.id = data.id.toString();
              }
          } catch(e) {
              console.error(e);
              return false;
          }
      } else {
          setUserGold(prev => prev - item.price);
      }

      setInboxMessages(prev => [newMessage, ...prev]);
      
      setAlertConfig({
          title: "Berhasil",
          message: `Berhasil menukarkan ${item.name}! Cek inbox Anda untuk kode voucher.`,
          type: "success"
      });
      return true;
  };

  const renderContent = () => {
    if (activeTab === 'characters' && selectedCharacter) {
        return (
            <CharacterDetail 
                character={selectedCharacter} 
                onBack={() => setSelectedCharacter(null)}
                onUpdateCharacter={handleUpdateCharacter}
            />
        );
    }

    switch (activeTab) {
      case 'dashboard':
        return <Dashboard stats={serverStats} userName={currentUser} onNavigate={handleTabChange} vipStatus={vipStatus} userGold={userGold} profile={isAdmin ? MOCK_ADMIN_PROFILE : MOCK_PLAYER_PROFILE} is2FAEnabled={isAdmin} />;
      case 'characters':
        return (
            <CharacterList 
                userName={currentUser}
                characters={characters} 
                setCharacters={setCharacters} 
                onSelectCharacter={(char) => setSelectedCharacter(char)}
                isDiscordLinked={isDiscordLinked}
                onRequireSync={() => {
                   setActiveTab('settings');
                   setAlertConfig({
                       title: 'Aksi Ditolak',
                       message: 'Anda wajib melakukan sinkronisasi akun Discord pada halaman pengaturan sebelum dapat membuat karakter baru.',
                       type: 'warning'
                   });
                }}
                onCharacterCreated={(name, metadata) => {
                    setInboxMessages(prev => [{
                        id: `msg-char-${Date.now()}`,
                        title: `Karakter Dibuat: ${name}`,
                        type: 'System',
                        date: new Date().toISOString(),
                        read: false,
                        template: 'CharacterCreated',
                        metadata
                    }, ...prev]);
                }}
            />
        );
      case 'story':
        return (
            <CharacterStoryPage 
                characters={characters} 
                userStories={userStories} 
                onSubmitStory={handleSubmitStory} 
                username={currentUser}
                onNavigate={handleTabChange}
            />
        );
      case 'donation':
        return (
            <Donation 
                initialTab={donationSubTab}
                promoConfig={promoConfig} 
                promoItems={promoItems}
                userGold={userGold}
                characters={characters}
                userName={currentUser}
                vipStatus={vipStatus}
                onRedeem={handleRedeemGoldItem}
                onNavigate={handleTabChange}
                onSendNotification={handleSendNotification}
            />
        );
      case 'tickets':
        return (
            <TicketSystem 
                userName={currentUser} 
                isAdmin={isAdmin} 
                messages={inboxMessages} 
                onReadMessage={handleReadMessage}
                onNavigate={handleTabChange}
                tickets={tickets}
                setTickets={setTickets}
                initialTab={ticketSystemTab}
                onSendNotification={handleSendNotification}
            />
        );
      case 'settings':
        return <Settings 
            userName={currentUser} 
            initialProfile={userProfile || (isAdmin ? MOCK_ADMIN_PROFILE : MOCK_PLAYER_PROFILE)} 
            is2FAEnabled={isAdmin} 
            onDiscordLinked={(discordUsername) => {
                setInboxMessages(prev => [{
                    id: `msg-discord-${Date.now()}`,
                    title: 'Discord Berhasil Ditautkan 🎉',
                    type: 'System',
                    date: new Date().toISOString(),
                    read: false,
                    template: 'DiscordLinked',
                    metadata: {
                        discordUsername
                    }
                }, ...prev]);
            }}
            onPasswordChanged={(time) => {
                setInboxMessages(prev => [{
                    id: `msg-pw-${Date.now()}`,
                    title: 'Keamanan Akun: Kata Sandi Diubah',
                    type: 'System',
                    date: new Date().toISOString(),
                    read: false,
                    template: 'PasswordChanged',
                    metadata: {
                        time
                    }
                }, ...prev]);
            }}
        />;
      case 'admin':
        return isAdmin ? (
          <AdminPanel 
            promoConfig={promoConfig} 
            onUpdatePromo={setPromoConfig}
            promoItems={promoItems}
            onUpdatePromoItems={setPromoItems}
            onSendNotification={handleSendNotification}
            onMainNavigate={handleTabChange}
            adminLevel={adminLevel}
            tickets={tickets}
            onOocReviewed={(username, type, status, feedback) => {
                setInboxMessages(prev => [{
                    id: `msg-ooc-${Date.now()}`,
                    title: 'Pemberitahuan: Hasil Tinjauan Data OOC',
                    type: 'System',
                    date: new Date().toISOString(),
                    read: false,
                    template: 'OocProfileReview',
                    metadata: { type, status, message: feedback }
                }, ...prev]);
            }}
            onStoryReviewed={(characterName, status, feedback) => {
                setInboxMessages(prev => [{
                    id: `msg-cs-${Date.now()}`,
                    title: `Pemberitahuan: Character Story ${characterName}`,
                    type: 'System',
                    date: new Date().toISOString(),
                    read: false,
                    template: 'CharacterStoryReview',
                    metadata: {
                        characterName,
                        status,
                        message: feedback
                    }
                }, ...prev]);
            }}
          />
        ) : <Dashboard stats={serverStats} userName={currentUser} onNavigate={handleTabChange} vipStatus={vipStatus} userGold={userGold} profile={isAdmin ? MOCK_ADMIN_PROFILE : MOCK_PLAYER_PROFILE} is2FAEnabled={isAdmin} />;
      case 'requests':
        return <Requests userName={currentUser} />;
      default:
        return <Dashboard stats={serverStats} userName={currentUser} onNavigate={handleTabChange} vipStatus={vipStatus} userGold={userGold} profile={isAdmin ? MOCK_ADMIN_PROFILE : MOCK_PLAYER_PROFILE} is2FAEnabled={isAdmin} />;
    }
  };

  if (!isAuthenticated) {
    return <Auth onLogin={handleLogin} serverStats={serverStats} />;
  }

  // Calculate Unread Messages
  const unreadCount = inboxMessages.filter(m => !m.read || m.read === '0' || m.read === 0 || m.read === false).length;

  return (
    <Layout 
      activeTab={activeTab} 
      onTabChange={handleTabChange} 
      onLogout={handleLogout}
      isDarkMode={isDarkMode}
      toggleTheme={toggleTheme}
      isAdmin={isAdmin}
      adminLevel={adminLevel}
      userName={currentUser}
      unreadCount={unreadCount}
      discordId={userProfile?.discordId}
    >
      {renderContent()}

      {/* Custom Alert Modal */}
      {alertConfig && (
          <div className="fixed inset-0 z-[100] flex items-center justify-center p-4 bg-black/60 backdrop-blur-sm animate-in fade-in duration-200">
              <div className="bg-white dark:bg-[#1a1a1a] rounded-2xl p-6 max-w-sm w-full shadow-2xl border border-gray-200 dark:border-white/10 text-center animate-in zoom-in-95 duration-200">
                  <div className={`w-16 h-16 rounded-full flex items-center justify-center mx-auto mb-4 ${
                      alertConfig.type === 'success' 
                          ? 'bg-green-100 dark:bg-green-500/20 text-green-500' 
                          : 'bg-yellow-100 dark:bg-yellow-500/20 text-yellow-500'
                  }`}>
                      {alertConfig.type === 'success' ? <CheckCircle size={32} /> : <AlertTriangle size={32} />}
                  </div>
                  <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase mb-2">{alertConfig.title}</h3>
                  <p className="text-sm text-gray-600 dark:text-gray-400 mb-6 leading-relaxed">
                      {alertConfig.message}
                  </p>
                  <button 
                      onClick={() => setAlertConfig(null)}
                      className="w-full bg-gray-900 hover:bg-gray-800 dark:bg-white dark:hover:bg-gray-200 text-white dark:text-gray-900 font-bold py-3 rounded-xl transition-colors uppercase tracking-widest text-sm"
                  >
                      Tutup
                  </button>
              </div>
          </div>
      )}
    </Layout>
  );
};

export default App;
