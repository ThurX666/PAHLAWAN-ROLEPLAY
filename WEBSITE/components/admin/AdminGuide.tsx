import React, { useState } from 'react';
import { 
  BookOpen, 
  ChevronDown, 
  ChevronUp, 
  Database, 
  Settings, 
  Globe, 
  Mail, 
  CreditCard, 
  FileText, 
  Server,
  ShieldCheck,
  Code
} from 'lucide-react';
import { PageHeader } from '../ui/PageHeader';

interface GuideSection {
  id: string;
  title: string;
  icon: React.ElementType;
  content: React.ReactNode;
}

export const AdminGuide: React.FC = () => {
    const [openSection, setOpenSection] = useState<string | null>('intro');

    const toggleSection = (id: string) => {
        setOpenSection(openSection === id ? null : id);
    };

    const sections: GuideSection[] = [
        {
            id: 'intro',
            title: '1. Pendahuluan & Stack Teknologi',
            icon: BookOpen,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Selamat datang di Panduan Administrasi UCP Pahlawan Roleplay.</p>
                    <p>Aplikasi ini dibangun menggunakan arsitektur modern perpaduan antara <strong>Frontend (React + Vite + Tailwind CSS)</strong> dan <strong>Backend (PHP API + MySQL)</strong>.</p>
                    <ul className="list-disc pl-5 space-y-2">
                        <li><strong>Frontend:</strong> React 19, TypeScript, Tailwind CSS. Berfungsi sebagai antarmuka (User Interface) utama yang berjalan di sisi browser (Client-Side Rendering).</li>
                        <li><strong>Backend API:</strong> Native PHP 8+ dengan PDO. Berfungsi untuk menangani request database dan autentikasi. Semua logic berada di folder <code className="bg-gray-100 dark:bg-white/10 px-1.5 py-0.5 rounded text-red-500">/public/api/</code>.</li>
                        <li><strong>Database:</strong> MySQL / MariaDB yang diakses secara eksklusif oleh Backend API.</li>
                    </ul>
                </div>
            )
        },
        {
            id: 'database',
            title: '2. Setup Instalasi Database',
            icon: Database,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Untuk menjalankan UCP ini di server lokal (seperti XAMPP) atau Hosting cPanel, Anda wajib menyiapkan databasenya terlebih dahulu.</p>
                    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-xl border border-gray-200 dark:border-white/10">
                        <ol className="list-decimal pl-5 space-y-3 font-medium">
                            <li>Buka phpMyAdmin atau software SQL Client lainnya.</li>
                            <li>Buat database baru dengan nama <code className="bg-blue-100 dark:bg-blue-900/30 text-blue-700 dark:text-blue-400 px-1.5 py-0.5 rounded">ucp_samp</code> (atau sesuaikan dengan kebutuhan Anda).</li>
                            <li>Cari file ber-ekstensi <code className="text-red-500">.txt</code> (berisi query SQL) di folder <code className="bg-gray-100 dark:bg-white/10 px-1.5 py-0.5 rounded text-gray-900 dark:text-white">/public/api/</code>. File ini adalah struktur dasar tabel yang diperlukan.</li>
                            <li>Import kode SQL dari file-file berikut secara perlahan:
                                <ul className="list-disc pl-5 mt-2 space-y-1 text-gray-500">
                                    <li>setup_sql.txt (Pengaturan sistem global)</li>
                                    <li>characters_sql.txt (Data karakter in-game)</li>
                                    <li>story_sql.txt (Sistem Character Story)</li>
                                    <li>donations_sql.txt (Transaksi Donasi)</li>
                                    <li>support_sql.txt (Sistem Tiket Bantuan)</li>
                                    <li>logs_sql.txt (Riwayat Aktivitas UCP)</li>
                                    <li>overview_sql.txt (Tabel Asset game seperti rumah, bisnis, dll)</li>
                                    <li>players_sql.txt (Tabel akun utama)</li>
                                    <li>settings_sql.txt (Pengaturan OOC / Profil User)</li>
                                    <li>data_requests_sql.txt (Form Request OOC)</li>
                                </ul>
                            </li>
                        </ol>
                    </div>
                </div>
            )
        },
        {
            id: 'backend',
            title: '3. Konfigurasi Backend & Koneksi',
            icon: Code,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Setelah database dibuat, Anda wajib menghubungkan PHP Backend ke Database Anda.</p>
                    <ul className="list-disc pl-5 space-y-3">
                        <li>
                            <strong>Konfigurasi API:</strong> Buka file <code className="bg-gray-100 dark:bg-white/10 px-1.5 py-0.5 rounded">/public/api/config.php</code>.
                            Ubah bagian koneksi PDO dengan username, password, dan nama database server Anda.
<pre className="bg-gray-900 text-gray-300 p-3 rounded-lg mt-2 overflow-x-auto text-xs font-mono">
DB_HOST=localhost
DB_NAME=arivena
DB_USER=root
DB_PASS=
</pre>
                            <p className="text-xs text-gray-500 dark:text-gray-400 mt-2">
                                Nama database harus sama dengan <code className="bg-gray-100 dark:bg-white/10 px-1 rounded">DATABASE_NAME</code> di gamemode (<code className="bg-gray-100 dark:bg-white/10 px-1 rounded">utils_defines.inc</code>).
                            </p>
                        </li>
                        <li>
                            <strong>Konfigurasi Frontend (Development):</strong> Buka file <code className="bg-gray-100 dark:bg-white/10 px-1.5 py-0.5 rounded">.env</code> di root aplikasi.
                            Sesuaikan URL API menuju endpoint PHP server Anda.
<pre className="bg-gray-900 text-gray-300 p-3 rounded-lg mt-2 overflow-x-auto text-xs font-mono">
VITE_API_BASE_URL=http://localhost/ucp-backend/api
</pre>
                            <div className="bg-red-50 dark:bg-red-900/20 border-l-4 border-red-500 p-3 mt-3 rounded-r-lg">
                                <p className="text-xs text-red-700 dark:text-red-400 font-medium tracking-wide">
                                    ⚠️ PENTING UNTUK FRONTEND:
                                </p>
                                <p className="text-xs text-gray-600 dark:text-gray-300 mt-1">
                                    Pastikan Anda telah menginstal NodeJS. Sebelum menjalankan aplikasi React, Anda <strong>wajib</strong> membuka Terminal di folder UCP ini dan menjalankan perintah <code className="bg-white dark:bg-black px-1 py-0.5 rounded text-red-600 font-bold border border-red-200 dark:border-red-800">npm install</code> untuk mengunduh seluruh modul dependensi. Jika tidak, aplikasi tidak akan bisa berjalan atau di-build.
                                </p>
                            </div>
                        </li>
                    </ul>
                </div>
            )
        },
        {
            id: 'auth',
            title: '4. Akun Admin & Keamanan',
            icon: ShieldCheck,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Mendaftarkan akun menjadi Administrator agar bisa mengakses panel ini.</p>
                    <ol className="list-decimal pl-5 space-y-2">
                        <li>Pilih Menu <strong>Register</strong> di Halaman Login UCP, isi data pengguna dengan normal.</li>
                        <li>Buka Database (phpMyAdmin), buka tabel <code className="text-red-500 font-bold">player_ucp</code>.</li>
                        <li>Ubah kolom <strong>admin_level</strong> menjadi <code className="text-blue-500 font-bold">10</code> pada akun yang Anda buat.</li>
                        <li>Login ulang di UCP. Menu <strong>Admin Panel</strong> akan otomatis muncul di sudut kanan atas.</li>
                    </ol>
                    <div className="bg-blue-50 dark:bg-blue-900/20 border border-blue-200 dark:border-blue-800 p-4 rounded-xl mt-4">
                        <strong className="text-blue-700 dark:text-blue-400 block mb-1">Keamanan Tambahan:</strong>
                        <p className="text-xs text-blue-600 dark:text-blue-300">
                            Semua password pada database dienkripsi menggunakan metode algoritma <code className="font-bold">Bcrypt</code> bawaan PHP melalui fungsi `password_hash()`. Fitur 2FA Google Authenticator juga bisa dicek di `security.php`.
                        </p>
                    </div>
                </div>
            )
        },
        {
            id: 'story',
            title: '5. Mengelola Character Story',
            icon: FileText,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Character Story adalah tahap wajib bagi Player untuk bisa ber-Roleplay. Berikut adalah tahapan meninjaunya:</p>
                    <ol className="list-decimal pl-5 space-y-2">
                        <li>Player membuat / mengajukan cerita di UCP Dashboard.</li>
                        <li>Buka Tab <strong>Stories</strong> di Admin Panel. Sebuah notifikasi "Menunggu Review" akan otomatis masuk di sana.</li>
                        <li>Baca secara teliti alur cerita. Anda bisa memanfaatkan <strong>fitur Cek Plagiarisme (AI)</strong> dari Gemini API untuk memeriksa jika teks yang dibuat adalah hasil copy-paste atau buatan AI.</li>
                        <li>Berikan Tanggapan / Feedback dan status akhir:
                            <ul className="list-disc pl-5 mt-1 space-y-1 text-gray-500">
                                <li><strong className="text-green-500">Active (Disetujui):</strong> Cerita disetujui, Player bebas bermain.</li>
                                <li><strong className="text-yellow-500">Revision (Revisi):</strong> Cerita dikembalikan ke Player dengan catatan perbaikan dari admin.</li>
                                <li><strong className="text-red-500">Rejected (Ditolak):</strong> Cerita melanggar aturan dan dianggap hangus.</li>
                            </ul>
                        </li>
                    </ol>
                </div>
            )
        },
        {
            id: 'donation',
            title: '6. Mengelola Fitur Donasi & Promo',
            icon: CreditCard,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Bagaimana mengontrol Item Terbatas (Limited) dan verifikasi bukti donasi uang riil.</p>
                    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-xl border border-gray-200 dark:border-white/10 space-y-3">
                        <div>
                            <strong className="text-gray-900 dark:text-white block">Promo Global:</strong>
                            <p className="text-xs">Di Tab <strong>Donasi</strong>, klik "Pengaturan Promo". Anda dapat menghidupkan Banner Diskon / Event (misal: Diskon Ramadhan 20%) yang akan tampil mencolok di seluruh Dashboard Player secara Real-Time.</p>
                        </div>
                        <div>
                            <strong className="text-gray-900 dark:text-white block">Limited Edition Items:</strong>
                            <p className="text-xs">UCP ini memiliki Toko Donasi. Anda bisa menambah item seperti "Rumah Mansion" atau "Mobil Sport Custom" melalui menu "Manajemen Promo Item". Item yang ditambahkan akan muncul untuk Player dan siap dibeli dengan mata uang <strong>Gold</strong>.</p>
                        </div>
                        <div>
                            <strong className="text-gray-900 dark:text-white block">Verifikasi Manual Bukti Transfer:</strong>
                            <p className="text-xs">Jika player melakukan metode transfer bank / e-Wallet (bukan e-Payment instan), mereka akan melampirkan gambar resi. Anda harus memverifikasinya di menu "Transaksi Berjalan" lalu tombol "Terima Bukti Transaksi" agar status Donatur serta Gold player tersebut bertambah secara otomatis masuk Database.</p>
                        </div>
                    </div>
                </div>
            )
        },
        {
            id: 'deploy',
            title: '7. Build & Deployment (Hosting)',
            icon: Globe,
            content: (
                <div className="space-y-4 text-sm text-gray-700 dark:text-gray-300">
                    <p>Setelah pengujian di Local (XAMPP/WAMP) selesai, ini tahapan mempublish secara Online (Production).</p>
                    <ol className="list-decimal pl-5 space-y-3">
                        <li><strong>Install Dependensi (Wajib):</strong>
                            <p className="text-xs mt-1 text-gray-500">Jika ini adalah pertama kalinya Anda membuka folder UCP di laptop/server untuk di-build, pastikan NodeJS terinstal, kemudian jalankan ini untuk mengunduh folder `node_modules`:</p>
                            <pre className="bg-gray-900 text-gray-300 p-2 rounded mt-1 overflow-x-auto text-xs font-mono">npm install</pre>
                        </li>
                        <li><strong>Build Antarmuka React:</strong>
                            <p className="text-xs mt-1 text-gray-500">Setelah `npm install` tuntas, jalankan perintah ini di Terminal untuk me-render kode menjadi versi Production yang ringan:</p>
                            <pre className="bg-gray-900 text-gray-300 p-2 rounded mt-1 overflow-x-auto text-xs font-mono">npm run build</pre>
                            <p className="text-xs mt-1 text-gray-500">Proses kompilasi akan membuat sebuh folder baru bernama <code className="text-blue-500">dist/</code>. Semua file di folder inilah (HTML, JS, CSS statis) yang akan Anda upload ke cPanel.</p>
                        </li>
                        <li><strong>Konfigurasi API di Server (cPanel Server / VPS):</strong>
                            <p className="text-xs mt-1 text-gray-500">Buat folder <code className="text-blue-500">api/</code> sejajar dengan file <code>index.html</code> (dari folder dist). Lalu pindahkan SELURUH isi dari <strong>/public/api/</strong> yang ada di source code awal ke dalam bentuk folder online tersebut.</p>
                        </li>
                        <li><strong>Pastikan .htaccess Diset:</strong>
                            <p className="text-xs mt-1 text-gray-500">Karena ini adalah Single Page Application (SPA), pastikan Server Apache / Nginx selalu mengarahkan URL (Fallback Routing) ke <code>index.html</code> (kecuali URL yang mengandung <code>/api</code>).</p>
                        </li>
                    </ol>
                </div>
            )
        }
    ];

    return (
        <div className="flex flex-col h-full animate-[fadeIn_0.5s_ease-out]">
            <PageHeader 
                title="Panduan Instalasi & Manajemen" 
                icon={BookOpen}
                description="Dokumentasi lengkap panduan administrasi, konfigurasi koneksi, sistem donasi dan instruksi implementasi aplikasi Pahlawan Roleplay ke tahap siap Production."
            />

            <div className="bg-white dark:bg-[#1a1a1a] rounded-2xl border border-gray-200 dark:border-white/10 shadow-sm p-4 md:p-6 overflow-hidden">
                <div className="space-y-4">
                    {sections.map((section) => (
                        <div 
                            key={section.id} 
                            className="bg-gray-50 dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-xl overflow-hidden transition-all duration-300"
                        >
                            <button
                                onClick={() => toggleSection(section.id)}
                                className="w-full flex justify-between items-center p-4 md:p-5 text-left focus:outline-none focus:ring-2 focus:ring-red-500/50"
                            >
                                <div className="flex items-center gap-4">
                                    <div className={`p-2 rounded-lg transition-colors duration-300 ${openSection === section.id ? 'bg-red-500 text-white shadow-lg shadow-red-500/30' : 'bg-gray-200 dark:bg-white/10 text-gray-700 dark:text-gray-300'}`}>
                                        <section.icon size={20} />
                                    </div>
                                    <h3 className={`font-bold text-sm md:text-base uppercase tracking-wider transition-colors duration-300 ${openSection === section.id ? 'text-red-600 dark:text-red-400' : 'text-gray-900 dark:text-white'}`}>
                                        {section.title}
                                    </h3>
                                </div>
                                <div className="text-gray-400">
                                    {openSection === section.id ? <ChevronUp size={20} /> : <ChevronDown size={20} />}
                                </div>
                            </button>
                            
                            <div 
                                className={`transition-all duration-300 ease-in-out overflow-hidden ${openSection === section.id ? 'max-h-[1000px] opacity-100' : 'max-h-0 opacity-0'}`}
                            >
                                <div className="p-4 md:p-6 pt-0 border-t border-gray-200 dark:border-white/10">
                                    {section.content}
                                </div>
                            </div>
                        </div>
                    ))}
                </div>
            </div>
        </div>
    );
};
