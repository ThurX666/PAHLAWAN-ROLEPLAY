import React, { useState, useRef, useEffect } from 'react';
import { Terminal, Search, Filter, Download, RefreshCw, Server, AlertCircle, FileText, Calendar } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

const LOG_CATEGORIES = [
    { id: 'player', label: 'Player Logs', requiresTarget: true, targetPlaceholder: 'Nama Karakter (Cth: Arthur_Clinton)' },
    { id: 'chat', label: 'Chat Logs', requiresTarget: false },
    { id: 'cmd_general', label: 'Command (Umum)', requiresTarget: false },
    { id: 'cmd_faction', label: 'Command (Fraksi)', requiresTarget: true, targetPlaceholder: 'ID/Nama Fraksi' },
    { id: 'cmd_family', label: 'Command (Family)', requiresTarget: true, targetPlaceholder: 'ID/Nama Family' },
    { id: 'biz', label: 'Business Logs', requiresTarget: true, targetPlaceholder: 'ID Bisnis' },
    { id: 'house', label: 'House Logs', requiresTarget: true, targetPlaceholder: 'ID Rumah' },
    { id: 'admin', label: 'Admin Logs', requiresTarget: false },
    { id: 'server', label: 'Server/System Logs', requiresTarget: false },
];

export const AdminLogs: React.FC = () => {
    const [activeCategory, setActiveCategory] = useState(LOG_CATEGORIES[0].id);
    const [targetInput, setTargetInput] = useState('');
    const [dateFilter, setDateFilter] = useState(new Date().toISOString().split('T')[0]);
    const [logs, setLogs] = useState<string[]>([
        "> SYSTEM: Server Log Viewer Initialized.",
        "> SYSTEM: Ready to fetch logs from VPS.",
        "> INFO: Select a category and click 'Fetch Logs' to begin."
    ]);
    const [isLoading, setIsLoading] = useState(false);
    const terminalRef = useRef<HTMLDivElement>(null);

    const currentCategory = LOG_CATEGORIES.find(c => c.id === activeCategory);

    const fetchLogs = async () => {
        if (currentCategory?.requiresTarget && !targetInput) {
            alert(`Harap isi ${currentCategory.targetPlaceholder} terlebih dahulu!`);
            return;
        }

        setIsLoading(true);
        setLogs(prev => [...prev, `> SYSTEM: Fetching ${activeCategory} logs from server...`]);
        
        if (isPreviewEnv()) {
            setTimeout(() => {
                const timePrefix = `[${dateFilter} 14:00:00]`;
                const mockLogs = [
                    `${timePrefix} [SYSTEM] Connection to VPS established.`,
                    `${timePrefix} [INFO] Reading file: /scriptfiles/logs/${activeCategory}/${currentCategory?.requiresTarget ? targetInput : 'all'}_${dateFilter}.txt`,
                    `[${dateFilter} 14:05:12] [LOG] ${targetInput || 'System'} performed an action in ${activeCategory}.`,
                    `[${dateFilter} 14:06:30] [LOG] Data entry recorded successfully.`,
                    `[${dateFilter} 14:10:05] [LOG] User requested data from module.`,
                    `[${dateFilter} 14:15:22] [SYSTEM] End of log file reached. Loaded 5 lines.`
                ];
                setLogs(prev => [...prev, ...mockLogs]);
                setIsLoading(false);
            }, 1000);
        } else {
            try {
                const res = await fetch(`${API_URL}/api_admin_logs.php?action=get_logs&category=${activeCategory}&target=${encodeURIComponent(targetInput)}&date=${dateFilter}`);
                if (res.ok) {
                    const data = await res.json();
                    if (data.status === 'success' && Array.isArray(data.logs)) {
                        setLogs(prev => [...prev, `> SYSTEM: Fetched ${data.logs.length} entries from database.`, ...data.logs]);
                    } else {
                        setLogs(prev => [...prev, `> SYSTEM: No logs found or error: ${data.message}`]);
                    }
                } else {
                    setLogs(prev => [...prev, `[ERROR] Failed to fetch logs from server.`]);
                }
            } catch (err) {
                 setLogs(prev => [...prev, `[ERROR] Connection error fetching logs.`]);
            }
            setIsLoading(false);
        }
    };

    const clearLogs = () => {
        setLogs(["> SYSTEM: Terminal cleared."]);
    };

    // Auto-scroll to bottom when logs update
    useEffect(() => {
        if (terminalRef.current) {
            terminalRef.current.scrollTop = terminalRef.current.scrollHeight;
        }
    }, [logs]);

    return (
        <div className="flex flex-col h-full min-h-[600px] animate-[fadeIn_0.5s_ease-out]">
            {/* Header */}
            <div className="flex flex-col md:flex-row justify-between items-start md:items-center mb-6 gap-4">
                <div>
                    <h2 className="text-2xl font-bold text-gray-900 dark:text-white flex items-center gap-2">
                        <Terminal className="text-blue-500" />
                        Server Log Viewer
                    </h2>
                    <p className="text-sm text-gray-500 dark:text-gray-400 mt-1">
                        Akses real-time ke file log Gamemode di VPS.
                    </p>
                </div>
                <div className="flex items-center gap-2 bg-green-50 dark:bg-green-900/20 text-green-600 dark:text-green-400 px-3 py-1.5 rounded-full text-xs font-medium border border-green-200 dark:border-green-800">
                    <Server size={14} />
                    VPS Connected (192.168.1.100)
                </div>
            </div>

            {/* Main Content Area */}
            <div className="grid grid-cols-1 lg:grid-cols-4 gap-6 flex-1">
                
                {/* Left Sidebar - Controls */}
                <div className="lg:col-span-1 space-y-6">
                    {/* Category Selection */}
                    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-xl border border-gray-200 dark:border-white/10">
                        <h3 className="text-sm font-bold text-gray-900 dark:text-white mb-3 flex items-center gap-2">
                            <Filter size={16} className="text-gray-500" />
                            Kategori Log
                        </h3>
                        <div className="space-y-1">
                            {LOG_CATEGORIES.map(category => (
                                <button
                                    key={category.id}
                                    onClick={() => {
                                        setActiveCategory(category.id);
                                        setTargetInput('');
                                    }}
                                    className={`w-full text-left px-3 py-2 rounded-lg text-sm transition-colors flex items-center gap-2 ${
                                        activeCategory === category.id
                                        ? 'bg-blue-500 text-white font-medium'
                                        : 'text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10'
                                    }`}
                                >
                                    <FileText size={14} />
                                    {category.label}
                                </button>
                            ))}
                        </div>
                    </div>

                    {/* Filters */}
                    <div className="bg-gray-50 dark:bg-white/5 p-4 rounded-xl border border-gray-200 dark:border-white/10 space-y-4">
                        <h3 className="text-sm font-bold text-gray-900 dark:text-white flex items-center gap-2">
                            <Search size={16} className="text-gray-500" />
                            Parameter Pencarian
                        </h3>
                        
                        {currentCategory?.requiresTarget && (
                            <div>
                                <label className="block text-xs text-gray-500 dark:text-gray-400 mb-1">Target</label>
                                <input 
                                    type="text" 
                                    value={targetInput}
                                    onChange={(e) => setTargetInput(e.target.value)}
                                    placeholder={currentCategory.targetPlaceholder}
                                    className="w-full px-3 py-2 bg-white dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-lg text-sm focus:ring-2 focus:ring-blue-500 focus:border-transparent dark:text-white"
                                />
                            </div>
                        )}

                        <div>
                            <label className="block text-xs text-gray-500 dark:text-gray-400 mb-1">Tanggal Log</label>
                            <div className="relative">
                                <Calendar size={14} className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" />
                                <input 
                                    type="date" 
                                    value={dateFilter}
                                    onChange={(e) => setDateFilter(e.target.value)}
                                    className="w-full pl-9 pr-3 py-2 bg-white dark:bg-[#121212] border border-gray-300 dark:border-gray-700 rounded-lg text-sm focus:ring-2 focus:ring-blue-500 focus:border-transparent dark:text-white"
                                />
                            </div>
                        </div>

                        <button 
                            onClick={fetchLogs}
                            disabled={isLoading}
                            className="w-full py-2 bg-blue-600 hover:bg-blue-700 text-white rounded-lg text-sm font-bold transition-colors flex items-center justify-center gap-2 disabled:opacity-50 disabled:cursor-not-allowed"
                        >
                            {isLoading ? <RefreshCw size={16} className="animate-spin" /> : <Search size={16} />}
                            {isLoading ? 'Mengambil Data...' : 'Fetch Logs'}
                        </button>
                    </div>
                </div>

                {/* Right Area - Terminal */}
                <div className="lg:col-span-3 flex flex-col bg-[#0c0c0c] rounded-xl border border-gray-800 overflow-hidden shadow-2xl relative">
                    {/* Terminal Header */}
                    <div className="bg-[#1a1a1a] px-4 py-2 border-b border-gray-800 flex justify-between items-center">
                        <div className="flex items-center gap-2">
                            <div className="flex gap-1.5">
                                <div className="w-3 h-3 rounded-full bg-red-500"></div>
                                <div className="w-3 h-3 rounded-full bg-yellow-500"></div>
                                <div className="w-3 h-3 rounded-full bg-green-500"></div>
                            </div>
                            <span className="text-xs text-gray-400 font-mono ml-2">
                                root@vps-pahlawan:~/{activeCategory}_logs
                            </span>
                        </div>
                        <div className="flex gap-2">
                            <button onClick={clearLogs} className="text-xs text-gray-400 hover:text-white transition-colors px-2 py-1 bg-white/5 rounded">
                                Clear
                            </button>
                            <button className="text-xs text-gray-400 hover:text-white transition-colors px-2 py-1 bg-white/5 rounded flex items-center gap-1">
                                <Download size={12} /> Export
                            </button>
                        </div>
                    </div>

                    {/* Terminal Body */}
                    <div 
                        ref={terminalRef}
                        className="flex-1 p-4 overflow-y-auto font-mono text-sm text-green-400 custom-scrollbar"
                        style={{ maxHeight: '600px', minHeight: '400px' }}
                    >
                        {logs.map((log, index) => (
                            <div key={index} className="mb-1 hover:bg-white/5 px-1 rounded">
                                {log.includes('[SYSTEM]') ? (
                                    <span className="text-blue-400">{log}</span>
                                ) : log.includes('[ERROR]') || log.includes('[WARNING]') ? (
                                    <span className="text-red-400">{log}</span>
                                ) : log.includes('[INFO]') ? (
                                    <span className="text-yellow-400">{log}</span>
                                ) : log.startsWith('>') ? (
                                    <span className="text-gray-400">{log}</span>
                                ) : (
                                    <span>{log}</span>
                                )}
                            </div>
                        ))}
                        {isLoading && (
                            <div className="mt-2 text-gray-500 animate-pulse">
                                _
                            </div>
                        )}
                    </div>
                </div>

            </div>
        </div>
    );
};
