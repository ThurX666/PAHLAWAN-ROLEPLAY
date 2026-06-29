
import React, { useState } from 'react';
import { ShieldCheck, Lock, XCircle, KeyRound, QrCode, AlertTriangle, ShieldAlert } from 'lucide-react';

interface SecurityCardProps {
    is2FAEnabled?: boolean;
    userName: string;
    onToggle2FA: () => void;
    onChangePassword: (oldPass: string, newPass: string) => Promise<boolean | string>;
}

export const SecurityCard: React.FC<SecurityCardProps> = ({ is2FAEnabled = false, userName, onToggle2FA, onChangePassword }) => {
  const [show2FAModal, setShow2FAModal] = useState(false);
  const [showPasswordModal, setShowPasswordModal] = useState(false);

  // States for password change
  const [oldPassword, setOldPassword] = useState('');
  const [newPassword, setNewPassword] = useState('');
  const [confirmPassword, setConfirmPassword] = useState('');
  const [passwordError, setPasswordError] = useState('');
  const [isChangingPass, setIsChangingPass] = useState(false);

  const handlePasswordSubmit = async () => {
      setPasswordError('');
      if (!oldPassword || !newPassword || !confirmPassword) {
          setPasswordError('Semua field sandi harus diisi');
          return;
      }
      if (newPassword !== confirmPassword) {
          setPasswordError('Sandi baru dan konfirmasi tidak cocok');
          return;
      }
      
      setIsChangingPass(true);
      const res = await onChangePassword(oldPassword, newPassword);
      setIsChangingPass(false);
      
      if (res === true) {
          setShowPasswordModal(false);
          setOldPassword('');
          setNewPassword('');
          setConfirmPassword('');
          alert('Sandi berhasil diubah');
      } else {
          setPasswordError(res as string);
      }
  };

  const handleToggle2FA = () => {
      onToggle2FA();
      setShow2FAModal(false);
  };

  return (
    <>
        <div className="h-full flex flex-col justify-center bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 p-6 md:p-8 rounded-2xl md:rounded-3xl relative overflow-hidden group">
            {/* Subtle glow effect */}
            <div className={`absolute -top-10 -right-10 w-40 h-40 ${is2FAEnabled ? 'bg-green-500/20' : 'bg-red-500/20'} rounded-full blur-[50px] opacity-0 group-hover:opacity-100 transition-opacity duration-700 pointer-events-none`}></div>

            <div className="flex items-center space-x-4 mb-5 md:mb-6 relative z-10">
                <div className={`w-12 h-12 md:w-16 md:h-16 rounded-2xl flex items-center justify-center border shadow-inner ${is2FAEnabled ? 'bg-green-500/10 text-green-500 border-green-500/20' : 'bg-red-500/10 text-red-500 border-red-500/20'}`}>
                    {is2FAEnabled ? <ShieldCheck size={28} className="md:w-8 md:h-8 w-6 h-6" /> : <ShieldAlert size={28} className="md:w-8 md:h-8 w-6 h-6" />}
                </div>
                <div>
                    <h3 className="text-lg md:text-xl font-black text-gray-900 dark:text-white uppercase tracking-tight">Keamanan</h3>
                    <p className="text-gray-500 text-[10px] md:text-xs mt-1 md:mt-1.5 font-medium">Status: <span className={`${is2FAEnabled ? 'text-green-500' : 'text-red-500'} font-bold`}>{is2FAEnabled ? 'Aman (2FA Aktif)' : 'Resiko Tinggi'}</span></p>
                </div>
            </div>
            
            <div className="space-y-3 relative z-10">
                <button 
                    onClick={() => setShow2FAModal(true)}
                    className={`w-full py-3.5 rounded-xl text-[10px] md:text-xs font-bold uppercase tracking-widest transition-all flex items-center justify-center space-x-2 transform hover:-translate-y-0.5 active:translate-y-0 ${is2FAEnabled ? 'bg-red-600 hover:bg-red-500 text-white shadow-[0_0_15px_rgba(220,38,38,0.2)] hover:shadow-[0_0_25px_rgba(220,38,38,0.4)]' : 'bg-green-600 hover:bg-green-500 text-white shadow-[0_0_15px_rgba(22,163,74,0.2)] hover:shadow-[0_0_25px_rgba(22,163,74,0.4)]'}`}
                >
                    <Lock size={14} />
                    <span>{is2FAEnabled ? 'Nonaktifkan 2FA' : 'Aktifkan 2FA'}</span>
                </button>
                <button 
                    onClick={() => setShowPasswordModal(true)}
                    className="w-full bg-ph-surface-panel hover:bg-ph-surface-elevated border border-ph-border-default text-white py-3.5 rounded-xl text-[10px] md:text-xs font-bold uppercase tracking-widest transition-all transform hover:-translate-y-0.5 active:translate-y-0"
                >
                    Ubah Kata Sandi
                </button>
            </div>
        </div>

        {/* 2FA Modal */}
        {show2FAModal && (
            <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
                <div className="bg-white dark:bg-ph-surface-card w-full max-w-md rounded-2xl border border-gray-200 dark:border-white/10 shadow-2xl overflow-hidden animate-[slideUp_0.3s_ease-out]">
                    <div className="p-4 md:p-6 border-b border-gray-200 dark:border-white/5 flex justify-between items-center bg-gray-50 dark:bg-white/5">
                        <div className="flex items-center gap-3">
                            <div className={`p-2 rounded-lg ${is2FAEnabled ? 'bg-red-500/20 text-red-500' : 'bg-green-500/20 text-green-500'}`}>
                                {is2FAEnabled ? <ShieldAlert size={20} /> : <QrCode size={20} />}
                            </div>
                            <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-tighter">{is2FAEnabled ? 'Nonaktifkan 2FA' : 'Setup 2FA'}</h3>
                        </div>
                        <button onClick={() => setShow2FAModal(false)} className="text-gray-500 hover:text-red-500 transition-colors">
                            <XCircle size={24} />
                        </button>
                    </div>
                    <div className="p-4 md:p-6 space-y-6">
                        {is2FAEnabled ? (
                            <>
                                <div className="text-center space-y-2">
                                    <p className="text-sm text-gray-600 dark:text-gray-300">Apakah Anda yakin ingin menonaktifkan Autentikasi Dua Faktor (2FA)? Akun Anda akan menjadi kurang aman.</p>
                                </div>
                                <div className="space-y-2">
                                    <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase ml-1">Sandi Saat Ini</label>
                                    <input 
                                        type="password" 
                                        placeholder="Masukkan sandi untuk konfirmasi" 
                                        className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-gray-900 dark:text-white text-sm focus:border-red-500 focus:bg-white dark:focus:bg-black/40 outline-none transition-all"
                                    />
                                </div>
                                <button 
                                    className="w-full bg-red-600 hover:bg-red-500 text-white font-bold py-3.5 rounded-xl uppercase text-xs tracking-widest shadow-lg shadow-red-600/20 transition-all active:scale-95"
                                    onClick={handleToggle2FA}
                                >
                                    Konfirmasi Nonaktifkan
                                </button>
                            </>
                        ) : (
                            <>
                                <div className="text-center space-y-2">
                                    <p className="text-sm text-gray-600 dark:text-gray-300">Scan QR code di bawah ini menggunakan aplikasi <strong className="text-gray-900 dark:text-white">Google Authenticator</strong> atau <strong className="text-gray-900 dark:text-white">Authy</strong>.</p>
                                </div>
                                
                                <div className="flex justify-center">
                                    <div className="w-48 h-48 bg-white p-2 rounded-xl border border-gray-200 flex items-center justify-center">
                                        <QrCode size={160} className="text-gray-800" />
                                    </div>
                                </div>

                                <div className="space-y-2">
                                    <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase ml-1">Kode Verifikasi</label>
                                    <input 
                                        type="text" 
                                        placeholder="Masukkan 6 digit kode" 
                                        className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-gray-900 dark:text-white text-center text-lg tracking-[0.5em] font-mono focus:border-green-500 focus:bg-white dark:focus:bg-black/40 outline-none transition-all"
                                        maxLength={6}
                                    />
                                </div>

                                <div className="bg-amber-50 dark:bg-amber-900/10 border border-amber-200 dark:border-amber-900/30 p-3 rounded-xl flex gap-3 items-start">
                                    <AlertTriangle size={16} className="text-amber-600 dark:text-amber-500 shrink-0 mt-0.5" />
                                    <p className="text-[10px] text-amber-800 dark:text-amber-200 leading-relaxed">Simpan kode backup (recovery code) di tempat yang aman. Jika Anda kehilangan akses ke aplikasi authenticator, Anda akan kesulitan login.</p>
                                </div>

                                <button 
                                    className="w-full bg-green-600 hover:bg-green-500 text-white font-bold py-3.5 rounded-xl uppercase text-xs tracking-widest shadow-lg shadow-green-600/20 transition-all active:scale-95"
                                    onClick={handleToggle2FA}
                                >
                                    Verifikasi & Aktifkan
                                </button>
                            </>
                        )}
                    </div>
                </div>
            </div>
        )}

        {/* Change Password Modal */}
        {showPasswordModal && (
            <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/80 backdrop-blur-sm animate-[fadeIn_0.2s_ease-out]">
                <div className="bg-white dark:bg-ph-surface-card w-full max-w-md rounded-2xl border border-gray-200 dark:border-white/10 shadow-2xl overflow-hidden animate-[slideUp_0.3s_ease-out]">
                    <div className="p-4 md:p-6 border-b border-gray-200 dark:border-white/5 flex justify-between items-center bg-gray-50 dark:bg-white/5">
                        <div className="flex items-center gap-3">
                            <div className="p-2 bg-red-500/20 text-red-500 rounded-lg">
                                <KeyRound size={20} />
                            </div>
                            <h3 className="text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-tighter">Ubah Sandi</h3>
                        </div>
                        <button onClick={() => setShowPasswordModal(false)} className="text-gray-500 hover:text-red-500 transition-colors">
                            <XCircle size={24} />
                        </button>
                    </div>
                    <div className="p-4 md:p-6 space-y-4">
                        {passwordError && (
                            <div className="bg-red-500/10 text-red-500 p-3 rounded-xl text-sm border border-red-500/20">
                                {passwordError}
                            </div>
                        )}
                        <div className="space-y-2">
                            <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase ml-1">Sandi Saat Ini</label>
                            <input 
                                value={oldPassword}
                                onChange={(e) => setOldPassword(e.target.value)}
                                type="password" 
                                placeholder="Masukkan sandi saat ini" 
                                className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-gray-900 dark:text-white text-sm focus:border-red-500 focus:bg-white dark:focus:bg-black/40 outline-none transition-all"
                            />
                        </div>
                        <div className="space-y-2">
                            <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase ml-1">Sandi Baru</label>
                            <input 
                                value={newPassword}
                                onChange={(e) => setNewPassword(e.target.value)}
                                type="password" 
                                placeholder="Masukkan sandi baru" 
                                className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-gray-900 dark:text-white text-sm focus:border-red-500 focus:bg-white dark:focus:bg-black/40 outline-none transition-all"
                            />
                        </div>
                        <div className="space-y-2">
                            <label className="block text-[10px] md:text-xs font-bold text-gray-500 uppercase ml-1">Konfirmasi Sandi Baru</label>
                            <input 
                                value={confirmPassword}
                                onChange={(e) => setConfirmPassword(e.target.value)}
                                type="password" 
                                placeholder="Ulangi sandi baru" 
                                className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl px-4 py-3 text-gray-900 dark:text-white text-sm focus:border-red-500 focus:bg-white dark:focus:bg-black/40 outline-none transition-all"
                            />
                        </div>

                        <div className="pt-4">
                            <button 
                                className={`w-full ${isChangingPass ? 'bg-red-400' : 'bg-red-600 hover:bg-red-500'} text-white font-bold py-3.5 rounded-xl uppercase text-xs tracking-widest shadow-lg shadow-red-600/20 transition-all active:scale-95`}
                                onClick={handlePasswordSubmit}
                                disabled={isChangingPass}
                            >
                                {isChangingPass ? 'Memproses...' : 'Simpan Sandi Baru'}
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        )}
    </>
  );
};

