import React from 'react';
import { ShieldCheck, UserPlus, AlertTriangle, Key, FileText } from 'lucide-react';

export const CharacterCreatedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-green-600/10 to-green-600/5 border border-green-600/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-green-600 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(22,163,74,0.4)]">
                    <UserPlus size={32} />
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-green-600 uppercase">Karakter Dibuat! 🎉</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Bersiaplah untuk memulai perjalanan hidup yang baru di Pahlawan Roleplay.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Karakter in-game Anda <strong>{metadata?.name || 'Player'}</strong> telah terdaftar. Berikut adalah detail identitas karakter Anda:</p>
            </div>
            
            <div className="bg-green-600/5 border border-green-600/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Nama</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.name || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Gender</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.gender || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Umur</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.age ? `${metadata.age} Tahun` : '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Tinggi / Berat</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.height ? `${metadata.height.toString().replace(/cm/i, '').trim()} cm` : '-'} / {metadata?.weight ? `${metadata.weight.toString().replace(/kg/i, '').trim()} kg` : '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Asal Negara</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.origin || '-'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
            
            <div className="border-l-4 border-blue-500 bg-blue-500/10 p-4 rounded-r-xl mb-2">
                <div className="flex items-center gap-2 mb-2">
                    <ShieldCheck className="text-blue-500" size={18} />
                    <h4 className="m-0 text-sm font-bold text-blue-500 uppercase tracking-wide">Langkah Selanjutnya</h4>
                </div>
                <p className="m-0 text-[13px] leading-relaxed opacity-85 text-gray-800 dark:text-gray-200">Silakan masuk (login) ke dalam In-Game menggunakan nama karakter yang telah kamu buat. Sampai jumpa di kota!</p>
            </div>
        </div>
    );
};

export const DiscordLinkedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-[#5865F2]/10 to-[#5865F2]/5 border border-[#5865F2]/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-[#5865F2] text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(88,101,242,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="currentColor">
                        <path d="M20.317 4.3698a19.7913 19.7913 0 00-4.8851-1.5152.0741.0741 0 00-.0785.0371c-.211.3753-.4447.8648-.6083 1.2495-1.8447-.2762-3.68-.2762-5.4868 0-.1636-.3933-.4058-.8742-.6177-1.2495a.077.077 0 00-.0785-.037 19.7363 19.7363 0 00-4.8852 1.515.0699.0699 0 00-.0321.0277C.5334 9.0458-.319 13.5799.0992 18.0578a.0824.0824 0 00.0312.0561c2.0528 1.5076 4.0413 2.4228 5.9929 3.0294a.0777.0777 0 00.0842-.0276c.4616-.6304.8731-1.2952 1.226-1.9942a.076.076 0 00-.0416-.1057c-.6528-.2476-1.2743-.5495-1.8722-.8923a.077.077 0 01-.0076-.1277c.1258-.0943.2517-.1923.3718-.2914a.0743.0743 0 01.0776-.0105c3.9278 1.7933 8.18 1.7933 12.0614 0a.0739.0739 0 01.0785.0095c.1202.099.246.1981.3728.2924a.077.077 0 01-.0066.1276 12.2986 12.2986 0 01-1.873.8914.0766.0766 0 00-.0407.1067c.3604.698.7719 1.3628 1.225 1.9932a.076.076 0 00.0842.0286c1.961-.6067 3.9495-1.5219 6.0023-3.0294a.077.077 0 00.0313-.0552c.5004-5.177-.8382-9.6739-3.5485-13.6604a.061.061 0 00-.0312-.0286zM8.02 15.3312c-1.1825 0-2.1569-1.0857-2.1569-2.419 0-1.3332.9555-2.4189 2.157-2.4189 1.2108 0 2.1757 1.0952 2.1568 2.419 0 1.3332-.9555 2.4189-2.1569 2.4189zm7.9748 0c-1.1825 0-2.1569-1.0857-2.1569-2.419 0-1.3332.9554-2.4189 2.1569-2.4189 1.2108 0 2.1757 1.0952 2.1568 2.419 0 1.3332-.946 2.4189-2.1568 2.4189z" />
                    </svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-[#5865F2] uppercase">Tautan Discord Berhasil</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Akun kamu telah resmi terhubung dengan Discord.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Selamat! Akun UCP Anda kini telah tertaut dengan akun Discord <strong>{metadata?.discordUsername || 'Simulated User'}</strong>. Hal ini memberikan Anda akses penuh ke server komunitas dan manfaat sebagai Warga di Pahlawan Roleplay.</p>
            </div>
            
            <div className="border-l-4 border-[#5865F2] bg-[#5865F2]/10 p-4 rounded-r-xl mb-2">
                <div className="flex items-center gap-2 mb-2">
                    <ShieldCheck className="text-[#5865F2]" size={18} />
                    <h4 className="m-0 text-sm font-bold text-[#5865F2] uppercase tracking-wide">Keamanan Ditingkatkan</h4>
                </div>
                <p className="m-0 text-[13px] leading-relaxed opacity-85 text-gray-800 dark:text-gray-200">Tautan Discord juga memberikan lapisan keamanan tambahan. Jangan pernah membagikan akses Discord Anda kepada siapa pun.</p>
            </div>
        </div>
    );
};

export const NewLoginDetectedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-red-500/10 to-red-500/5 border border-red-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-red-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(239,68,68,0.4)]">
                    <AlertTriangle size={32} />
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-red-500 uppercase">Aktivitas Baru Terdeteksi</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Sistem mendeteksi login baru ke akun UCP Anda.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Kami mendeteksi aktivitas akses yang berhasil menggunakan profil Anda. Berikut adalah detail dari sesi Anda saat ini:</p>
            </div>
            
            <div className="bg-red-500/5 border border-red-500/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Waktu Login</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.time || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Perangkat / Browser</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.device || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Alamat IP</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.ip || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Lokasi Terdeteksi</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.location || '-'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
            
            <div className="border-l-4 border-red-500 bg-red-500/10 p-4 rounded-r-xl mb-2">
                <div className="flex items-center gap-2 mb-2">
                    <AlertTriangle className="text-red-500" size={18} />
                    <h4 className="m-0 text-sm font-bold text-red-500 uppercase tracking-wide">Bukan Anda?</h4>
                </div>
                <p className="m-0 text-[13px] leading-relaxed opacity-85 text-gray-800 dark:text-gray-200">Jika Anda tidak merasa melakukan verifikasi login ini, segera navigasi ke halaman <strong>Pengaturan</strong> lalu lakukan ganti password UCP Anda, dan pertimbangkan untuk reset akses.</p>
            </div>
        </div>
    );
};

export const PasswordChangedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-blue-500/10 to-blue-500/5 border border-blue-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-blue-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(59,130,246,0.4)]">
                    <Key size={32} />
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-blue-500 uppercase">Kata Sandi Berhasil Diubah</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Kata sandi akun UCP Anda baru saja diperbarui.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Pesan ini menginformasikan bahwa kata sandi akun UCP Anda telah berhasil diperbarui pada <strong>{metadata?.time || new Date().toLocaleString()}</strong>. Jika Anda yang melakukan perubahan ini, Anda dapat mengabaikan pesan ini.</p>
            </div>
            
            <div className="border-l-4 border-red-500 bg-red-500/10 p-4 rounded-r-xl mb-2">
                <div className="flex items-center gap-2 mb-2">
                    <AlertTriangle className="text-red-500" size={18} />
                    <h4 className="m-0 text-sm font-bold text-red-500 uppercase tracking-wide">Bukan Anda?</h4>
                </div>
                <p className="m-0 text-[13px] leading-relaxed opacity-85 text-gray-800 dark:text-gray-200">Jika Anda merasa tidak mengubah kata sandi, akun Anda mungkin dalam bahaya. Segera hubungi Admin secepatnya.</p>
            </div>
        </div>
    );
};

export const OocProfileReviewMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-blue-500/10 to-blue-500/5 border border-blue-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-blue-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(59,130,246,0.4)]">
                    <FileText size={32} />
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-blue-500 uppercase">Tinjauan Data OOC Selesai</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Permintaan pembaruan profil Anda telah diperiksa oleh tim Admin.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Permohonan pembaruan data untuk <strong>{metadata?.type || 'Ganti Nama Asli (OOC)'}</strong> telah mendapatkan keputusan akhir.</p>
            </div>
            
            <div className="bg-blue-500/5 border border-blue-500/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Tipe Data</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.type || 'Ganti Nama Asli (OOC)'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Status Permohonan</td>
                                <td className={`py-3 px-4 font-semibold ${metadata?.status === 'Diizinkan' ? 'text-green-500' : 'text-red-500'}`}>{metadata?.status || 'Selesai'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Pesan Admin</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.message || 'Data sudah sesuai, di-acc bro!'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    );
};

export const CharacterStoryReviewMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-blue-500/10 to-blue-500/5 border border-blue-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-blue-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(59,130,246,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M2 3h6a4 4 0 0 1 4 4v14a3 3 0 0 0-3-3H2z"></path><path d="M22 3h-6a4 4 0 0 0-4 4v14a3 3 0 0 1 3-3h7z"></path></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-blue-500 uppercase">Tinjauan Character Story</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Hasil pemeriksaan Character Story untuk karakter <strong>{metadata?.characterName || 'Unknown'}</strong>.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Cerita karakter (Character Story) In-Game yang Anda kirimkan telah ditinjau oleh tim Admin.</p>
            </div>
            
            <div className="bg-blue-500/5 border border-blue-500/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Nama Karakter</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.characterName || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Status Cerita</td>
                                <td className={`py-3 px-4 font-semibold ${metadata?.status === 'Disetujui' ? 'text-green-500' : 'text-red-500'}`}>{metadata?.status || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Pesan Admin</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.message || '-'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    );
};

export const PaymentProcessedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-blue-500/10 to-blue-500/5 border border-blue-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-blue-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(59,130,246,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M22 11.08V12a10 10 0 1 1-5.93-9.14"></path><polyline points="22 4 12 14.01 9 11.01"></polyline></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-blue-500 uppercase">Pembayaran Diperiksa</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Transaksi donasi Anda telah diproses oleh Admin.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Pesan ini menginformasikan bahwa transaksi untuk <strong>{metadata?.itemName || '-'}</strong> telah selesai diperiksa.</p>
            </div>
            
            <div className="bg-blue-500/5 border border-blue-500/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">ID Transaksi</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.transactionId || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Item</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.itemName || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Nominal</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.amount || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Status Akhir</td>
                                <td className={`py-3 px-4 font-semibold ${metadata?.status === 'Berhasil' ? 'text-green-500' : 'text-red-500'}`}>{metadata?.status || '-'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    );
};

export const TicketClosedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-[#5865F2]/10 to-[#5865F2]/5 border border-[#5865F2]/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-[#5865F2] text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(88,101,242,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path><polyline points="14 2 14 8 20 8"></polyline><line x1="16" y1="13" x2="8" y2="13"></line><line x1="16" y1="17" x2="8" y2="17"></line><polyline points="10 9 9 9 8 9"></polyline></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-[#5865F2] uppercase">Tiket Bantuan Selesai</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Laporan Anda telah berhasil diselesaikan oleh tim dukungan.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Tiket bantuan Anda dengan judul <strong>"{metadata?.ticketTitle || '-'}"</strong> telah ditandai sebagai Selesai. Jika Anda masih mengalami kendala yang sama, silakan buat tiket baru.</p>
            </div>
            
            <div className="bg-[#5865F2]/5 border border-[#5865F2]/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">ID Tiket</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.ticketId || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Kategori</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.category || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Status Akhir</td>
                                <td className="py-3 px-4 font-semibold text-[#5865F2]">{metadata?.status || 'Closed'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    );
};

export const ServerWarningMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-red-500/10 to-red-500/5 border border-red-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-red-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(239,68,68,0.4)]">
                    <AlertTriangle size={32} />
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-red-500 uppercase">Peringatan Akun</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Karakter Anda telah diberikan peringatan oleh Admin.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Kami menghubungi Anda karena karakter Anda <strong>{metadata?.characterName || '-'}</strong> terbukti melanggar peraturan server ({metadata?.reason || '-'}). Jika mencapai 20 peringatan, akun akan di-Banned permanen.</p>
            </div>
            
            <div className="bg-red-500/5 border border-red-500/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-white dark:bg-[#1a1a1a] rounded-[14px] overflow-hidden">
                    <table className="w-full text-sm text-left border-collapse text-gray-800 dark:text-gray-200">
                        <tbody>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Admin</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.adminName || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60 w-[40%]">Alasan</td>
                                <td className="py-3 px-4 font-semibold">{metadata?.reason || '-'}</td>
                            </tr>
                            <tr className="border-b border-gray-500/10">
                                <td className="py-3 px-4 opacity-60">Total Warn</td>
                                <td className="py-3 px-4 font-semibold text-red-500">{metadata?.currentWarn || '1'} / 20</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    );
};

export const UnbanRequestApprovedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-green-600/10 to-green-600/5 border border-green-600/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-green-600 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(22,163,74,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path><polyline points="14 2 14 8 20 8"></polyline><line x1="16" y1="13" x2="8" y2="13"></line><line x1="16" y1="17" x2="8" y2="17"></line><polyline points="10 9 9 9 8 9"></polyline></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-green-600 uppercase">Unban Request Disetujui</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Status banned pada akun Anda telah dicabut oleh tim High Staff.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Permohonan banding <i>(Ban Appeal)</i> Anda telah diperiksa dan disetujui {metadata?.adminName ? `oleh ${metadata.adminName}` : ''}. Akun Anda kembali kami buka aksesnya ke dalam server. Mohon untuk mematuhi rules server dan tidak mengulangi kesalahan yang sama di kemudian hari.</p>
            </div>
        </div>
    );
};

export const PropertyInactivityWarningMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-yellow-500/10 to-yellow-500/5 border border-yellow-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-yellow-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(234,179,8,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M3 9l9-7 9 7v11a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2z"></path><polyline points="9 22 9 12 15 12 15 22"></polyline></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-yellow-500 uppercase">Property Auto-Sell Warning</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Tindakan diperlukan agar Anda tidak kehilangan properti ini.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">
                    Sistem mendeteksi bahwa karakter Anda belum melakukan interaksi atau login selama {metadata?.inactiveDays || '10'} hari terakhir. Jika tidak ada aktivitas In-Game dalam {metadata?.daysRemaining || '4'} hari ke depan, <strong>{metadata?.propertyType || 'Rumah'} #{metadata?.propertyId || '105'} di {metadata?.propertyZone || 'Vinewood'}</strong> Anda akan otomatis dijual oleh sistem (Asell).
                </p>
            </div>
        </div>
    );
};

export const NamechangeSuccessMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-purple-500/10 to-purple-500/5 border border-purple-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-purple-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(168,85,247,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2"></path><circle cx="12" cy="7" r="4"></circle></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-purple-500 uppercase">Character Namechange Sukses</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Pengajuan pergantian nama karakter / Character Kill (CK) disetujui.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Proses pergantian nama karakter In-Game Anda telah berhasil. Silakan login ke dalam game dengan nama karakter Anda yang baru.</p>
            </div>
            
            <div className="bg-purple-500/5 border border-purple-500/15 rounded-2xl p-0.5 mb-6">
                <div className="bg-gray-50 dark:bg-[#0a0a0a] rounded-xl overflow-hidden">
                    <table className="w-full border-collapse text-sm text-left">
                        <tbody>
                            <tr className="border-b border-gray-200 dark:border-white/10">
                                <td className="p-3 md:p-4 text-gray-500 dark:text-gray-400 w-2/5 font-medium">Nama Lama</td>
                                <td className="p-3 md:p-4 font-bold text-gray-900 dark:text-white"><span className="line-through">{metadata?.oldName || 'Ucok_Slepbeuw'}</span></td>
                            </tr>
                            <tr>
                                <td className="p-3 md:p-4 text-gray-500 dark:text-gray-400 font-medium">Nama Baru</td>
                                <td className="p-3 md:p-4 font-bold text-green-600 dark:text-green-500">{metadata?.newName || 'Albert_Wesker'}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    );
};

export const PlayerReportRespondedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-blue-500/10 to-blue-500/5 border border-blue-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-blue-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(59,130,246,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path><polyline points="14 2 14 8 20 8"></polyline><line x1="16" y1="13" x2="8" y2="13"></line><line x1="16" y1="17" x2="8" y2="17"></line><polyline points="10 9 9 9 8 9"></polyline></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-blue-500 uppercase">Laporan Pemain Selesai</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Laporan Forum mengenai Player Rulebreak telah ditutup.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Laporan Anda terhadap pemain <strong>{metadata?.reportedPlayer || 'Terlapor'}</strong> mengenai <span className="text-blue-500">{metadata?.violation || 'Pelanggaran'}</span> telah diperiksa oleh Admin. Pelaku telah diberikan sanksi sesuai dengan peraturan server ({metadata?.adminAction || 'Sanksi diberikan'}). Terima kasih telah membantu menjaga kualitas Roleplay di komunitas kita.</p>
            </div>
        </div>
    );
};

export const RefundApprovedMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {
    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-blue-500/10 to-blue-500/5 border border-blue-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-blue-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(59,130,246,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><polyline points="15 3 21 3 21 9"></polyline><polyline points="9 21 3 21 3 15"></polyline><line x1="21" y1="3" x2="14" y2="10"></line><line x1="3" y1="21" x2="10" y2="14"></line></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-blue-500 uppercase">Refund Dikabulkan</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Pengembalian aset in-game Anda telah dikonfirmasi.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Laporan Refund di forum mengenai <strong>"{metadata?.assetName || 'Aset'}"</strong> telah disetujui. Silakan gunakan perintah <i>{metadata?.command || '/autorefund'}</i> saat Anda login di dalam game di lokasi yang aman ({metadata?.locationToClaim || 'tempat pengambilan'}) untuk mengambil kembali aset Anda.</p>
            </div>
        </div>
    );
};

export const VipExpiredMessage: React.FC<{ metadata?: any }> = ({ metadata }) => {

    return (
        <div className="font-sans max-w-full">
            <div className="text-center mb-6 bg-gradient-to-br from-yellow-500/10 to-yellow-500/5 border border-yellow-500/20 p-6 rounded-2xl">
                <div className="inline-flex items-center justify-center w-16 h-16 bg-yellow-500 text-white rounded-2xl mb-4 shadow-[0_8px_16px_-4px_rgba(234,179,8,0.4)]">
                    <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"><path d="M11 4H4a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2v-7"></path><path d="M18.5 2.5a2.121 2.121 0 0 1 3 3L12 15l-4 1 1-4 9.5-9.5z"></path></svg>
                </div>
                <h2 className="text-xl font-black mb-2 tracking-tight text-yellow-500 uppercase">VIP Telah Berakhir</h2>
                <p className="text-sm opacity-80 m-0 leading-relaxed text-gray-800 dark:text-white">Status donatur Anda telah kedaluwarsa hari ini.</p>
            </div>
            
            <div className="mb-6 leading-relaxed text-[15px] text-gray-800 dark:text-gray-300">
                <p className="mb-3">Halo,</p>
                <p className="m-0">Terima kasih atas kontribusi Anda kepada server. Status <strong className="text-yellow-600 dark:text-yellow-400">VIP {metadata?.vipTier || 'Bronze'}</strong> Anda telah resmi berakhir. Anda dapat memperpanjang paket di halaman menu Donasi kapan saja untuk mendapatkan fitur premium kembali.</p>
            </div>
        </div>
    );
};
