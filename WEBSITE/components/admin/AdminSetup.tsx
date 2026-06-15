import React, { useState, useEffect } from 'react';
import { Settings, Server, MessageSquare, Activity, Mail, Save, CheckCircle, Database, ShieldAlert, Monitor, Terminal, RefreshCw, Eye, X } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

export const AdminSetup: React.FC = () => {
    const [activeTab, setActiveTab] = useState<'general' | 'discord' | 'pusher' | 'smtp'>('general');
    const [settings, setSettings] = useState<Record<string, string>>({
        server_name: 'Pahlawan Roleplay',
        maintenance_mode: '0',
        discord_bot_token: '',
        discord_guild_id: '',
        discord_webhook_url: '',
        discord_client_id: '',
        discord_client_secret: '',
        discord_role_warga_id: '',
        pusher_app_id: '',
        pusher_key: '',
        pusher_secret: '',
        pusher_cluster: 'ap1',
        smtp_host: 'smtp.gmail.com',
        smtp_port: '587',
        smtp_user: '',
        smtp_pass: '',
    });
    const [isLoading, setIsLoading] = useState(true);
    const [isSaving, setIsSaving] = useState(false);
    const [alertMsg, setAlertMsg] = useState<{title: string, message: string, type: 'success' | 'error'} | null>(null);
    const [emailPreviewType, setEmailPreviewType] = useState<'welcome' | 'verification_register' | 'verification_login' | 'verification_device' | 'forgot_password' | 'reset_success' | null>(null);

    const fetchSettings = async () => {
        setIsLoading(true);
        if (!isPreviewEnv()) {
            try {
                const res = await fetch(`${API_URL}/api_admin_setup.php?action=get_settings`);
                if (res.ok) {
                    const data = await res.json();
                    if (data.status === 'success' && data.settings) {
                        setSettings(prev => ({...prev, ...data.settings}));
                    }
                }
            } catch (err) {
                console.error("Gagal fetch settings", err);
            }
        }
        setIsLoading(false);
    };

    useEffect(() => {
        fetchSettings();
    }, []);

    const handleSave = async (e: React.FormEvent) => {
        e.preventDefault();
        setIsSaving(true);
        setAlertMsg(null);

        if (isPreviewEnv()) {
            setTimeout(() => {
                setAlertMsg({ title: "Tersimpan", message: "Simulasi simpan konfigurasi berhasil (Preview Mode).", type: 'success' });
                setIsSaving(false);
            }, 800);
        } else {
            try {
                const res = await fetch(`${API_URL}/api_admin_setup.php`, {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({
                        action: 'save_settings',
                        settings: settings
                    })
                });
                const data = await res.json();
                if (data.status === 'success') {
                    setAlertMsg({ title: "Berhasil", message: "Konfigurasi sistem berhasil tersimpan.", type: 'success' });
                } else {
                    setAlertMsg({ title: "Error", message: "Gagal menyimpan: " + data.message, type: 'error' });
                }
            } catch (err) {
                setAlertMsg({ title: "Koneksi Error", message: "Gagal menyambung ke server API.", type: 'error' });
            }
            setIsSaving(false);
        }
        setTimeout(() => setAlertMsg(null), 4000);
    };

    const handleChange = (key: string, value: string) => {
        setSettings(prev => ({ ...prev, [key]: value }));
    };

    return (
        <div className="flex flex-col h-full animate-[fadeIn_0.5s_ease-out]">
            {/* Header */}
            <div className="mb-6">
                <h2 className="text-2xl font-bold text-gray-900 dark:text-white flex items-center gap-2">
                    <Settings className="text-blue-500" />
                    System Server Setup
                </h2>
                <p className="text-sm text-gray-500 dark:text-gray-400 mt-1">
                    Konfigurasi kredensial global, API Keys, dan pengaturan utama sistem situs web. Mengelola modul-modul dinamis yang saling terintegrasi.
                </p>
            </div>

            {alertMsg && (
                <div className={`mb-6 p-4 rounded-xl border flex items-start gap-3 ${
                    alertMsg.type === 'success' 
                    ? 'bg-green-50 border-green-200 text-green-800 dark:bg-green-900/20 dark:border-green-800 dark:text-green-300'
                    : 'bg-red-50 border-red-200 text-red-800 dark:bg-red-900/20 dark:border-red-800 dark:text-red-300'
                }`}>
                    {alertMsg.type === 'success' ? <CheckCircle size={20} className="mt-0.5" /> : <ShieldAlert size={20} className="mt-0.5" />}
                    <div>
                        <h4 className="font-bold text-sm">{alertMsg.title}</h4>
                        <p className="text-sm opacity-90">{alertMsg.message}</p>
                    </div>
                </div>
            )}

            <div className="flex flex-col lg:flex-row gap-6 flex-1">
                {/* Sidebar Tabs */}
                <div className="w-full lg:w-64 flex-shrink-0 space-y-1">
                    {[
                        { id: 'general', label: 'General / Server', icon: Server },
                        { id: 'discord', label: 'Discord / Bot API', icon: MessageSquare },
                        { id: 'pusher', label: 'Pusher (Real-time)', icon: Activity },
                        { id: 'smtp', label: 'SMTP & Email', icon: Mail }
                    ].map(tab => (
                        <button
                            key={tab.id}
                            onClick={() => setActiveTab(tab.id as any)}
                            className={`w-full flex items-center gap-3 px-4 py-3 rounded-xl text-sm font-medium transition-colors ${
                                activeTab === tab.id
                                ? 'bg-blue-500 text-white shadow-md'
                                : 'bg-white dark:bg-[#1a1a1a] text-gray-600 dark:text-gray-400 hover:bg-gray-50 dark:hover:bg-white/5 border border-gray-200 dark:border-white/5'
                            }`}
                        >
                            <tab.icon size={18} />
                            {tab.label}
                        </button>
                    ))}
                </div>

                {/* Main Form Area */}
                <div className="flex-1 bg-white dark:bg-[#1a1a1a] rounded-2xl border border-gray-200 dark:border-white/10 shadow-sm overflow-hidden min-h-[500px]">
                    <form onSubmit={handleSave} className="p-6 md:p-8 flex flex-col h-full">
                        <div className="flex-1 space-y-6">
                            {isLoading ? (
                                <div className="flex justify-center items-center h-32 text-gray-500">
                                    <RefreshCw size={24} className="animate-spin" />
                                    <span className="ml-2">Memuat Konfigurasi...</span>
                                </div>
                            ) : (
                                <>
                                    {activeTab === 'general' && (
                                        <div className="space-y-4 animate-[fadeIn_0.3s_ease-out]">
                                            <h3 className="text-lg font-bold text-gray-900 dark:text-white mb-4 border-b border-gray-200 dark:border-gray-800 pb-2">General Settings</h3>
                                            
                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Nama Server / Komunitas</label>
                                                <input 
                                                    type="text" 
                                                    value={settings.server_name}
                                                    onChange={(e) => handleChange('server_name', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white"
                                                />
                                            </div>

                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Maintenance Mode (UCP)</label>
                                                <select 
                                                    value={settings.maintenance_mode}
                                                    onChange={(e) => handleChange('maintenance_mode', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white"
                                                >
                                                    <option value="0">Non-Aktif (Online)</option>
                                                    <option value="1">Aktif (Maintenance)</option>
                                                </select>
                                                <p className="text-xs text-gray-500 mt-2">Jika diaktifkan, pemain biasa tidak dapat mengakses sistem UCP.</p>
                                            </div>
                                        </div>
                                    )}

                                    {activeTab === 'discord' && (
                                        <div className="space-y-4 animate-[fadeIn_0.3s_ease-out]">
                                            <h3 className="text-lg font-bold text-gray-900 dark:text-white mb-4 border-b border-gray-200 dark:border-gray-800 pb-2">Discord Bot Setup</h3>
                                            
                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Discord Webhook URL (Log Aktivitas UCP)</label>
                                                <input 
                                                    type="text" 
                                                    value={settings.discord_webhook_url}
                                                    onChange={(e) => handleChange('discord_webhook_url', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                />
                                            </div>

                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Discord Bot Token (SAMP Verify Sync)</label>
                                                <input 
                                                    type="password" 
                                                    value={settings.discord_bot_token}
                                                    onChange={(e) => handleChange('discord_bot_token', e.target.value)}
                                                    placeholder="MTAx..."
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                />
                                            </div>
                                            
                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Discord Guild (Server) ID</label>
                                                <input 
                                                    type="text" 
                                                    value={settings.discord_guild_id}
                                                    onChange={(e) => handleChange('discord_guild_id', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                />
                                            </div>

                                            <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Discord OAuth Client ID</label>
                                                    <input 
                                                        type="text" 
                                                        value={settings.discord_client_id}
                                                        onChange={(e) => handleChange('discord_client_id', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Discord OAuth Client Secret</label>
                                                    <input 
                                                        type="password" 
                                                        value={settings.discord_client_secret}
                                                        onChange={(e) => handleChange('discord_client_secret', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                            </div>

                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Discord Role "Warga" ID</label>
                                                <input 
                                                    type="text" 
                                                    value={settings.discord_role_warga_id}
                                                    onChange={(e) => handleChange('discord_role_warga_id', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    placeholder="Role ID yang diberikan saat member link Discord"
                                                />
                                            </div>
                                        </div>
                                    )}

                                    {activeTab === 'pusher' && (
                                        <div className="space-y-4 animate-[fadeIn_0.3s_ease-out]">
                                            <h3 className="text-lg font-bold text-gray-900 dark:text-white mb-4 border-b border-gray-200 dark:border-gray-800 pb-2">Pusher Real-time Chat</h3>
                                            
                                            <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">App ID</label>
                                                    <input 
                                                        type="text" 
                                                        value={settings.pusher_app_id}
                                                        onChange={(e) => handleChange('pusher_app_id', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Cluster</label>
                                                    <input 
                                                        type="text" 
                                                        value={settings.pusher_cluster}
                                                        onChange={(e) => handleChange('pusher_cluster', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                            </div>

                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">App Key</label>
                                                <input 
                                                    type="text" 
                                                    value={settings.pusher_key}
                                                    onChange={(e) => handleChange('pusher_key', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                />
                                            </div>

                                            <div>
                                                <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">App Secret</label>
                                                <input 
                                                    type="password" 
                                                    value={settings.pusher_secret}
                                                    onChange={(e) => handleChange('pusher_secret', e.target.value)}
                                                    className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                />
                                            </div>
                                        </div>
                                    )}

                                    {activeTab === 'smtp' && (
                                        <div className="space-y-4 animate-[fadeIn_0.3s_ease-out]">
                                            <h3 className="text-lg font-bold text-gray-900 dark:text-white mb-4 border-b border-gray-200 dark:border-gray-800 pb-2">SMTP Mailer (Verifikasi OTP)</h3>
                                            
                                            <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                                                <div className="md:col-span-2">
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Host Server</label>
                                                    <input 
                                                        type="text" 
                                                        value={settings.smtp_host}
                                                        onChange={(e) => handleChange('smtp_host', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                                
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Email / Username</label>
                                                    <input 
                                                        type="email" 
                                                        value={settings.smtp_user}
                                                        onChange={(e) => handleChange('smtp_user', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white"
                                                    />
                                                </div>
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">App Password / Secret</label>
                                                    <input 
                                                        type="password" 
                                                        value={settings.smtp_pass}
                                                        onChange={(e) => handleChange('smtp_pass', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                                <div>
                                                    <label className="block text-sm font-medium text-gray-700 dark:text-gray-300 mb-1">Port SSL/TLS</label>
                                                    <input 
                                                        type="number" 
                                                        value={settings.smtp_port}
                                                        onChange={(e) => handleChange('smtp_port', e.target.value)}
                                                        className="w-full px-4 py-2.5 bg-gray-50 dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-xl text-sm focus:ring-2 focus:ring-blue-500 dark:text-white font-mono"
                                                    />
                                                </div>
                                            </div>

                                            <div className="mt-6 pt-6 border-t border-gray-200 dark:border-gray-800">
                                                <h4 className="text-sm font-bold text-gray-900 dark:text-white mb-2">Email Templates Tools</h4>
                                                <div className="flex flex-wrap gap-3">
                                                    <button 
                                                        type="button" 
                                                        onClick={(e) => { e.preventDefault(); setEmailPreviewType('welcome'); }}
                                                        className="flex items-center gap-2 px-4 py-2 bg-emerald-50 dark:bg-emerald-900/20 text-emerald-600 dark:text-emerald-400 rounded-lg text-sm font-medium hover:bg-emerald-100 dark:hover:bg-emerald-900/40 transition-colors border border-emerald-200 dark:border-emerald-800/30"
                                                    >
                                                        <Eye size={16} />
                                                        Welcome Email
                                                    </button>
                                                    <button 
                                                        type="button" 
                                                        onClick={(e) => { e.preventDefault(); setEmailPreviewType('verification_register'); }}
                                                        className="flex items-center gap-2 px-4 py-2 bg-blue-50 dark:bg-blue-900/20 text-blue-600 dark:text-blue-400 rounded-lg text-sm font-medium hover:bg-blue-100 dark:hover:bg-blue-900/40 transition-colors border border-blue-200 dark:border-blue-800/30"
                                                    >
                                                        <Eye size={16} />
                                                        OTP Verification (Register)
                                                    </button>
                                                    <button 
                                                        type="button" 
                                                        onClick={(e) => { e.preventDefault(); setEmailPreviewType('verification_login'); }}
                                                        className="flex items-center gap-2 px-4 py-2 bg-indigo-50 dark:bg-indigo-900/20 text-indigo-600 dark:text-indigo-400 rounded-lg text-sm font-medium hover:bg-indigo-100 dark:hover:bg-indigo-900/40 transition-colors border border-indigo-200 dark:border-indigo-800/30"
                                                    >
                                                        <Eye size={16} />
                                                        OTP Verification (Login / Resend)
                                                    </button>
                                                    <button 
                                                        type="button" 
                                                        onClick={(e) => { e.preventDefault(); setEmailPreviewType('verification_device'); }}
                                                        className="flex items-center gap-2 px-4 py-2 bg-amber-50 dark:bg-amber-900/20 text-amber-600 dark:text-amber-400 rounded-lg text-sm font-medium hover:bg-amber-100 dark:hover:bg-amber-900/40 transition-colors border border-amber-200 dark:border-amber-800/30"
                                                    >
                                                        <Eye size={16} />
                                                        OTP Verification (New Device)
                                                    </button>
                                                    <button 
                                                        type="button" 
                                                        onClick={(e) => { e.preventDefault(); setEmailPreviewType('forgot_password'); }}
                                                        className="flex items-center gap-2 px-4 py-2 bg-purple-50 dark:bg-purple-900/20 text-purple-600 dark:text-purple-400 rounded-lg text-sm font-medium hover:bg-purple-100 dark:hover:bg-purple-900/40 transition-colors border border-purple-200 dark:border-purple-800/30"
                                                    >
                                                        <Eye size={16} />
                                                        Lupa Sandi (Forgot Password)
                                                    </button>
                                                    <button 
                                                        type="button" 
                                                        onClick={(e) => { e.preventDefault(); setEmailPreviewType('reset_success'); }}
                                                        className="flex items-center gap-2 px-4 py-2 bg-green-50 dark:bg-green-900/20 text-green-600 dark:text-green-400 rounded-lg text-sm font-medium hover:bg-green-100 dark:hover:bg-green-900/40 transition-colors border border-green-200 dark:border-green-800/30"
                                                    >
                                                        <Eye size={16} />
                                                        Reset Sandi Berhasil
                                                    </button>
                                                </div>
                                            </div>
                                        </div>
                                    )}
                                </>
                            )}
                        </div>

                        <div className="mt-8 pt-4 border-t border-gray-200 dark:border-gray-800 flex justify-end">
                            <button 
                                type="submit" 
                                disabled={isLoading || isSaving}
                                className="bg-blue-600 hover:bg-blue-700 text-white px-6 py-2.5 rounded-xl text-sm font-bold transition-all flex items-center justify-center gap-2 disabled:opacity-50 min-w-[140px]"
                            >
                                {isSaving ? <RefreshCw size={18} className="animate-spin" /> : <Save size={18} />}
                                {isSaving ? 'Menyimpan...' : 'Simpan Konfigurasi'}
                            </button>
                        </div>
                    </form>
                </div>
            </div>

            {/* Email Preview Modal */}
            {emailPreviewType !== null && (
                <div className="fixed inset-0 z-50 flex items-center justify-center bg-black/60 backdrop-blur-sm animate-[fadeIn_0.3s_ease-out]">
                    <div className="bg-white dark:bg-[#121212] rounded-2xl md:rounded-3xl shadow-2xl w-full max-w-3xl max-h-[90vh] overflow-hidden flex flex-col m-4 animate-[slideInUp_0.3s_ease-out]">
                        <div className="flex justify-between items-center p-4 md:p-6 border-b border-gray-200 dark:border-white/10">
                            <h3 className="text-lg md:text-xl font-bold flex items-center gap-2 text-gray-900 dark:text-white">
                                <Mail className="text-blue-500" />
                                Preview: {emailPreviewType === 'welcome' ? 'Welcome Email' : emailPreviewType === 'verification_register' ? 'OTP Verification (Register)' : emailPreviewType === 'verification_login' ? 'OTP Verification (Login/Resend)' : emailPreviewType === 'forgot_password' ? 'Forgot Password (OTP)' : emailPreviewType === 'reset_success' ? 'Password Reset Success' : 'OTP Verification (New Device)'}
                            </h3>
                            <button 
                                onClick={() => setEmailPreviewType(null)}
                                className="w-8 h-8 flex items-center justify-center rounded-full bg-gray-100 dark:bg-white/5 text-gray-500 hover:bg-red-50 hover:text-red-500 transition-colors"
                            >
                                <X size={20} />
                            </button>
                        </div>
                        <div className="flex-1 overflow-auto bg-gray-100 dark:bg-black p-4 md:p-8 flex items-center justify-center">
                            {emailPreviewType === 'welcome' && (
                                <div className="w-full max-w-[600px] mx-auto bg-white rounded-2xl overflow-hidden shadow-xl border border-gray-100" style={{fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif", borderTop: "8px solid #dc2626"}}>
                                    <div style={{padding: "32px 24px", textAlign: "center", borderBottom: "1px solid #f3f4f6"}}>
                                      <img src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} alt="Pahlawan Roleplay Logo" style={{width: "160px", margin: "0 auto", display: "block"}} />
                                      {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
                                    </div>
                                    <div style={{padding: "32px 24px", color: "#1f2937"}}>
                                      <div style={{textAlign: "center", marginBottom: "24px"}}>
                                        <span style={{display: "inline-block", backgroundColor: "#fee2e2", color: "#ef4444", padding: "6px 16px", borderRadius: "9999px", fontSize: "12px", fontWeight: 800, letterSpacing: "1px", textTransform: "uppercase"}}>Akun Berhasil Dibuat</span>
                                        <h1 style={{margin: "16px 0 0 0", fontSize: "24px", color: "#111827", fontWeight: 900, letterSpacing: "-0.5px"}}>SELAMAT DATANG! 🎉</h1>
                                      </div>
                                      <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 16px 0"}}>Halo, <strong style={{color: "#dc2626"}}>PlayerName</strong>!</p>
                                      <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 24px 0", color: "#4b5563"}}>Pendaftaran akun UCP Anda telah berhasil dikonfirmasi. Selamat bergabung di komunitas <strong style={{color: "#111827"}}>Pahlawan Roleplay</strong>!</p>
                                      
                                      <div style={{backgroundColor: "#fef2f2", border: "1px solid #fee2e2", borderRadius: "12px", padding: "24px", margin: "32px 0"}}>
                                        <h3 style={{margin: "0 0 16px 0", color: "#b91c1c", fontSize: "16px", fontWeight: 700, textTransform: "uppercase", letterSpacing: "0.5px"}}>🚀 Mulai Petualanganmu</h3>
                                        <ul style={{margin: 0, paddingLeft: "16px", fontSize: "15px", lineHeight: "1.8", color: "#7f1d1d"}}>
                                          <li>Buat Karakter In-Game pertamamu.</li>
                                          <li>Lengkapi profil identitas OOC.</li>
                                          <li>Selesaikan Character Story untuk membuka fitur.</li>
                                          <li>Bergabunglah di server Discord kami.</li>
                                        </ul>
                                      </div>
                                      
                                      <div style={{textAlign: "center", marginTop: "32px"}}>
                                        <a href="#" style={{display: "inline-block", padding: "14px 32px", backgroundColor: "#dc2626", color: "#ffffff", textDecoration: "none", borderRadius: "8px", fontWeight: 600, fontSize: "16px", letterSpacing: "0.5px", boxShadow: "0 4px 6px -1px rgba(220, 38, 38, 0.2)"}}>Dashboard UCP</a>
                                      </div>
                                    </div>
                                    <div style={{backgroundColor: "#f9fafb", padding: "24px", textAlign: "center", borderTop: "1px solid #f3f4f6"}}>
                                      <p style={{margin: 0, fontSize: "13px", color: "#6b7280"}}>&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
                                    </div>
                                </div>
                            )}

                            {(emailPreviewType === 'verification_register' || emailPreviewType === 'verification_login' || emailPreviewType === 'verification_device') && (
                                <div className="w-full max-w-[600px] mx-auto bg-white rounded-2xl overflow-hidden shadow-xl border border-gray-100" style={{fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif", borderTop: "8px solid #dc2626"}}>
                                    <div style={{padding: "32px 24px", textAlign: "center", borderBottom: "1px solid #f3f4f6"}}>
                                      <img src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} alt="Pahlawan Roleplay Logo" style={{width: "160px", margin: "0 auto", display: "block"}} />
                                      {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
                                    </div>

                                    <div style={{padding: "32px 24px", color: "#1f2937"}}>
                                        <div style={{textAlign: "center", marginBottom: "24px"}}>
                                            <span style={{display: "inline-block", backgroundColor: "#fee2e2", color: "#ef4444", padding: "6px 16px", borderRadius: "9999px", fontSize: "12px", fontWeight: 800, letterSpacing: "1px", textTransform: "uppercase"}}>Otentikasi Keamanan</span>
                                            <h1 style={{margin: "16px 0 0 0", fontSize: "24px", color: "#111827", fontWeight: 900, letterSpacing: "-0.5px"}}>VERIFIKASI AKUN 🔐</h1>
                                        </div>
                                        
                                        <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 16px 0"}}>Halo, <strong style={{color: "#dc2626"}}>PlayerName</strong>!</p>
                                        <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 24px 0", color: "#4b5563"}}>
                                            {emailPreviewType === 'verification_register' 
                                                ? 'Terima kasih telah mendaftar di Pahlawan Roleplay. Silakan gunakan kode OTP (One Time Password) 6 digit di bawah ini untuk mengaktifkan akun Anda.'
                                                : emailPreviewType === 'verification_login'
                                                ? 'Kami menerima permintaan untuk mengirim ulang kode OTP, atau Anda mencoba masuk menggunakan akun yang belum sepenuhnya aktif. Silakan gunakan kode OTP di bawah ini untuk melanjutkan.'
                                                : 'Sistem mendeteksi aktivitas login dari Perangkat Baru. Demi keamanan akun Anda, silakan masukkan kode OTP di bawah ini untuk masuk.'}
                                        </p>
                                        
                                        {emailPreviewType === 'verification_device' && (
                                            <div style={{backgroundColor: "#faf5ff", border: "1px solid #f3e8ff", borderRadius: "12px", padding: "20px", marginBottom: "24px" }}>
                                                <h4 style={{margin: "0 0 12px 0", color: "#6b21a8", fontSize: "14px", textTransform: "uppercase", letterSpacing: "0.5px"}}>📍 Detail Aktivitas</h4>
                                                <div style={{fontSize: "14px", color: "#7e22ce", lineHeight: "1.6"}}>
                                                    <strong style={{display: "inline-block", width: "80px"}}>Perangkat:</strong> Windows / Chrome 123.0<br/>
                                                    <strong style={{display: "inline-block", width: "80px"}}>Lokasi:</strong> 192.168.1.1 (Jakarta, Indonesia)
                                                </div>
                                            </div>
                                        )}

                                        <div style={{backgroundColor: "#f3f4f6", borderRadius: "16px", padding: "24px 16px", textAlign: "center", margin: "24px 0"}}>
                                            <span style={{fontSize: "12px", color: "#6b7280", textTransform: "uppercase", letterSpacing: "2px", fontWeight: 700, display: "block", marginBottom: "12px"}}>KODE OTP ANDA</span>
                                            <div style={{fontSize: "36px", fontFamily: "'Courier New', Courier, monospace", fontWeight: 900, color: "#111827", letterSpacing: "8px", margin: 0, textShadow: "2px 2px 0px rgba(0,0,0,0.05)", paddingLeft: "8px", wordBreak: "break-all"}}>123456</div>
                                        </div>
                                        
                                        <div style={{backgroundColor: "#fffbeb", border: "1px solid #fef3c7", borderRadius: "12px", padding: "20px", display: "flex", gap: "16px", alignItems: "flex-start"}}>
                                            <div style={{fontSize: "20px"}}>🛡️</div>
                                            <div>
                                                <strong style={{display: "block", color: "#92400e", fontSize: "14px", marginBottom: "6px"}}>Perhatian Keamanan</strong>
                                                <p style={{margin: 0, color: "#b45309", fontSize: "13px", lineHeight: "1.5"}}>Kode ini hanya berlaku <strong>30 menit</strong>. Jangan pernah membagikan kode ini kepada siapapun (termasuk Admin/Staff kami). Jika aktivitas ini bukan Anda yang melakukan, segera amankan akun Anda dengan <a href="https://pahlawanrp.com" style={{color: "#ea580c", fontWeight: "bold", textDecoration: "underline"}}>membuat tiket bantuan</a>.</p>
                                            </div>
                                        </div>
                                    </div>
                                    <div style={{backgroundColor: "#f9fafb", padding: "24px", textAlign: "center", borderTop: "1px solid #f3f4f6"}}>
                                        <p style={{margin: 0, fontSize: "13px", color: "#6b7280"}}>&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
                                    </div>
                                </div>
                            )}

                            {emailPreviewType === 'forgot_password' && (
                                <div className="w-full max-w-[600px] mx-auto bg-white rounded-2xl overflow-hidden shadow-xl border border-gray-100" style={{fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif", borderTop: "8px solid #dc2626"}}>
                                    <div style={{padding: "32px 24px", textAlign: "center", borderBottom: "1px solid #f3f4f6"}}>
                                      <img src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} alt="Pahlawan Roleplay Logo" style={{width: "160px", margin: "0 auto", display: "block"}} />
                                      {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
                                    </div>

                                    <div style={{padding: "32px 24px", color: "#1f2937"}}>
                                        <div style={{textAlign: "center", marginBottom: "24px"}}>
                                            <span style={{display: "inline-block", backgroundColor: "#fee2e2", color: "#ef4444", padding: "6px 16px", borderRadius: "9999px", fontSize: "12px", fontWeight: 800, letterSpacing: "1px", textTransform: "uppercase"}}>Permintaan Reset Kata Sandi</span>
                                            <h1 style={{margin: "16px 0 0 0", fontSize: "24px", color: "#111827", fontWeight: 900, letterSpacing: "-0.5px"}}>LUPA KATA SANDI 🔑</h1>
                                        </div>
                                        
                                        <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 16px 0"}}>Halo, <strong style={{color: "#dc2626"}}>PlayerName</strong>!</p>
                                        <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 24px 0", color: "#4b5563"}}>Kami menerima permintaan untuk melakukan setel ulang kata sandi pada akun UCP Anda. Untuk melanjutkan proses penggantian kata sandi, silakan gunakan kode OTP berikut:</p>

                                        <div style={{backgroundColor: "#f3f4f6", borderRadius: "16px", padding: "24px 16px", textAlign: "center", margin: "24px 0"}}>
                                            <span style={{fontSize: "12px", color: "#6b7280", textTransform: "uppercase", letterSpacing: "2px", fontWeight: 700, display: "block", marginBottom: "12px"}}>KODE OTP ANDA</span>
                                            <div style={{fontSize: "36px", fontFamily: "'Courier New', Courier, monospace", fontWeight: 900, color: "#111827", letterSpacing: "8px", margin: 0, textShadow: "2px 2px 0px rgba(0,0,0,0.05)", paddingLeft: "8px", wordBreak: "break-all"}}>123456</div>
                                        </div>
                                        
                                        <div style={{backgroundColor: "#fffbeb", border: "1px solid #fef3c7", borderRadius: "12px", padding: "20px", display: "flex", gap: "16px", alignItems: "flex-start"}}>
                                            <div style={{fontSize: "20px"}}>🛡️</div>
                                            <div>
                                                <strong style={{display: "block", color: "#92400e", fontSize: "14px", marginBottom: "6px"}}>Perhatian Keamanan</strong>
                                                <p style={{margin: 0, color: "#b45309", fontSize: "13px", lineHeight: "1.5"}}>Kode ini hanya berlaku <strong>30 menit</strong>. Jangan pernah membagikan kode ini kepada siapapun (termasuk Admin/Staff kami). Jika Anda tidak meminta pengaturan ulang kata sandi, abaikan email ini atau amankan akun Anda dengan <a href="https://pahlawanrp.com" style={{color: "#ea580c", fontWeight: "bold", textDecoration: "underline"}}>membuat tiket bantuan</a>.</p>
                                            </div>
                                        </div>
                                    </div>
                                    <div style={{backgroundColor: "#f9fafb", padding: "24px", textAlign: "center", borderTop: "1px solid #f3f4f6"}}>
                                        <p style={{margin: 0, fontSize: "13px", color: "#6b7280"}}>&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
                                    </div>
                                </div>
                            )}

                            {emailPreviewType === 'reset_success' && (
                                <div className="w-full max-w-[600px] mx-auto bg-white rounded-2xl overflow-hidden shadow-xl border border-gray-100" style={{fontFamily: "'Segoe UI', Tahoma, Geneva, Verdana, sans-serif", borderTop: "8px solid #16a34a"}}>
                                    <div style={{padding: "32px 24px", textAlign: "center", borderBottom: "1px solid #f3f4f6"}}>
                                      <img src={`${import.meta.env.BASE_URL}assets/images/logo1.png`} alt="Pahlawan Roleplay Logo" style={{width: "160px", margin: "0 auto", display: "block"}} />
                                      {/* https://i.ibb.co.com/d4zTLfM6/logo1.png */}
                                    </div>

                                    <div style={{padding: "32px 24px", color: "#1f2937"}}>
                                        <div style={{textAlign: "center", marginBottom: "24px"}}>
                                            <span style={{display: "inline-block", backgroundColor: "#bbf7d0", color: "#16a34a", padding: "6px 16px", borderRadius: "9999px", fontSize: "12px", fontWeight: 800, letterSpacing: "1px", textTransform: "uppercase"}}>Keamanan Akun</span>
                                            <h1 style={{margin: "16px 0 0 0", fontSize: "24px", color: "#111827", fontWeight: 900, letterSpacing: "-0.5px"}}>SANDI TELAH DIRESET ✔️</h1>
                                        </div>
                                        
                                        <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 16px 0"}}>Halo, <strong style={{color: "#16a34a"}}>PlayerName</strong>!</p>
                                        <p style={{fontSize: "16px", lineHeight: "1.6", margin: "0 0 24px 0", color: "#4b5563"}}>Memberitahukan bahwa kata sandi akun UCP Anda baru saja berhasil diubah atau disetel ulang. Anda kini dapat masuk menggunakan kata sandi yang baru.</p>

                                        <div style={{backgroundColor: "#fffbeb", border: "1px solid #fef3c7", borderRadius: "12px", padding: "20px", display: "flex", gap: "16px", alignItems: "flex-start"}}>
                                            <div style={{fontSize: "20px"}}>🚨</div>
                                            <div>
                                                <strong style={{display: "block", color: "#92400e", fontSize: "14px", marginBottom: "6px"}}>Bukan Anda yang melakukan?</strong>
                                                <p style={{margin: 0, color: "#b45309", fontSize: "13px", lineHeight: "1.5"}}>Jika Anda tidak merasa mengubah kata sandi Anda hari ini, segera hubungi tim kami dengan <a href="https://pahlawanrp.com" style={{color: "#ea580c", fontWeight: "bold", textDecoration: "underline"}}>membuat tiket bantuan</a> untuk mengamankan akun Anda.</p>
                                            </div>
                                        </div>
                                    </div>
                                    <div style={{backgroundColor: "#f9fafb", padding: "24px", textAlign: "center", borderTop: "1px solid #f3f4f6"}}>
                                        <p style={{margin: 0, fontSize: "13px", color: "#6b7280"}}>&copy; 2026 Pahlawan Roleplay UCP.<br/>All rights reserved.</p>
                                    </div>
                                </div>
                            )}
                        </div>
                    </div>
                </div>
            )}
        </div>
    );
};
