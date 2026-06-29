import React, { useState, useEffect } from 'react';
import { Search, Server, User, Wifi, Hash } from 'lucide-react';
import { isPreviewEnv, API_URL } from '../../config';

interface OnlinePlayer {
  id: number;
  name: string;
  color?: string;
  score: number;
  ping: number;
}

export const PlayerTable: React.FC = () => {
    const [players, setPlayers] = useState<OnlinePlayer[]>([]);
    const [loading, setLoading] = useState(true);
    const [searchTerm, setSearchTerm] = useState('');

    useEffect(() => {
        let isMounted = true;
        
        const fetchPlayers = async () => {
            if (isPreviewEnv()) {
                // Mock data for preview
                if (isMounted) {
                    // Generate more mock data for scrolling test
                    const mockPlayers = [];
                    const mockColors = ['#FF0000', '#00FF00', '#0000FF', '#FFFFFF', '#FFFF00', '#00FFFF', '#FF00FF'];
                    for(let i=0; i<50; i++) {
                        mockPlayers.push({ 
                            id: i, 
                            name: `Player_${i}`, 
                            color: mockColors[Math.floor(Math.random() * mockColors.length)],
                            score: Math.floor(Math.random() * 500), 
                            ping: Math.floor(Math.random() * 150) + 10 
                        });
                    }
                    setPlayers(mockPlayers);
                    setLoading(false);
                }
                return;
            }

            try {
                const res = await fetch(`${API_URL}/api_overview.php?action=players`);
                const data = await res.json();
                if (data && data.status === 'success' && Array.isArray(data.data)) {
                    if (isMounted) {
                        setPlayers(data.data);
                        setLoading(false);
                    }
                } else {
                    if (isMounted) {
                        setPlayers([]);
                        setLoading(false);
                    }
                }
            } catch (err) {
                console.error("Error fetching player list:", err);
                if (isMounted) {
                    setPlayers([]);
                    setLoading(false);
                }
            }
        };

        fetchPlayers();
        
        const interval = setInterval(fetchPlayers, 20000); // refresh every 20s
        return () => {
            isMounted = false;
            clearInterval(interval);
        };
    }, []);

    const filteredPlayers = players.filter(p => (p.name || (p as any).nickname || (p as any).playername || '').toLowerCase().includes(searchTerm.toLowerCase()) || p.id.toString() === searchTerm);

    return (
        <div className="bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-[1.25rem] shadow-sm overflow-hidden flex flex-col h-full">
            <div className="p-4 md:p-6 border-b border-gray-200 dark:border-white/5 flex flex-col sm:flex-row justify-between items-start sm:items-center gap-4 md:gap-6">
                <div className="flex flex-col gap-1">
                    <h3 className="text-lg md:text-xl font-black text-gray-900 dark:text-white uppercase italic tracking-wide flex items-center gap-2">
                        <User className="text-red-500" size={22} fill="currentColor" />
                        Live Player List
                    </h3>
                    <p className="text-[13px] md:text-sm text-gray-500 dark:text-gray-400 font-medium">Menampilkan pemain yang sedang online.</p>
                </div>
                <div className="relative w-full sm:w-72">
                    <div className="absolute inset-y-0 left-0 pl-3.5 flex items-center pointer-events-none">
                        <Search className="h-4 w-4 text-gray-400" />
                    </div>
                    <input
                        type="text"
                        className="block w-full pl-10 pr-4 py-2.5 md:py-2 border border-gray-200 dark:border-white/10 rounded-xl leading-5 bg-gray-50 dark:bg-ph-surface-panel text-gray-900 dark:text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-red-500/50 focus:border-red-500 text-sm transition-colors"
                        placeholder="Cari ID / Nama..."
                        value={searchTerm}
                        onChange={(e) => setSearchTerm(e.target.value)}
                    />
                </div>
            </div>

            <div className="overflow-auto flex-1 min-h-[200px] sm:min-h-[300px] max-h-[350px] md:max-h-[500px]">
                {loading ? (
                    <div className="flex space-x-2 justify-center items-center h-full min-h-[200px] sm:min-h-[300px]">
                        <span className="sr-only">Loading...</span>
                        <div className="h-2.5 w-2.5 bg-red-500 rounded-full animate-[bounce_1s_infinite_-0.3s]"></div>
                        <div className="h-2.5 w-2.5 bg-red-500 rounded-full animate-[bounce_1s_infinite_-0.15s]"></div>
                        <div className="h-2.5 w-2.5 bg-red-500 rounded-full animate-[bounce_1s_infinite]"></div>
                    </div>
                ) : players.length === 0 ? (
                    <div className="flex flex-col items-center justify-center h-full min-h-[200px] sm:min-h-[300px] text-gray-500">
                        <Server size={48} className="mb-4 opacity-20" />
                        <p className="font-medium text-sm">Tidak dapat memuat list atau server kosong.</p>
                    </div>
                ) : (
                    <table className="min-w-full divide-y divide-gray-200 dark:divide-white/5">
                        <thead className="bg-[#f9fafb] dark:bg-ph-surface-panel sticky top-0 z-10">
                            <tr>
                                <th scope="col" className="px-3 sm:px-6 py-3 text-left text-[11px] sm:text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-widest w-12 sm:w-16">
                                    ID
                                </th>
                                <th scope="col" className="px-3 sm:px-6 py-3 text-left text-[11px] sm:text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-widest">
                                    NAME
                                </th>
                                <th scope="col" className="px-2 sm:px-6 py-3 text-center text-[11px] sm:text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-widest w-16 sm:w-24">
                                    Score
                                </th>
                                <th scope="col" className="px-3 sm:px-6 py-3 text-right text-[11px] sm:text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-widest w-16 sm:w-24">
                                    Ping
                                </th>
                            </tr>
                        </thead>
                        <tbody className="bg-white dark:bg-ph-surface-card divide-y divide-gray-200 dark:divide-white/5">
                            {filteredPlayers.length > 0 ? (
                                filteredPlayers.map((player) => (
                                    <tr key={player.id} className="even:bg-gray-50 dark:even:bg-white/[0.02] hover:bg-gray-100 dark:hover:bg-white/[0.05] transition-colors">
                                        <td className="px-3 sm:px-6 py-3 whitespace-nowrap text-xs md:text-sm font-semibold text-gray-900 dark:text-gray-300">
                                            {player.id}
                                        </td>
                                        <td className="px-3 sm:px-6 py-3 whitespace-nowrap text-xs md:text-sm text-gray-900 dark:text-white font-bold max-w-[120px] sm:max-w-xs truncate">
                                            <span style={player.color ? { color: player.color, textShadow: '0 0 1px rgba(0,0,0,0.3)' } : {}}>
                                                {player.name || (player as any).nickname || (player as any).playername || 'Unknown'}
                                            </span>
                                        </td>
                                        <td className="px-2 sm:px-6 py-3 whitespace-nowrap text-xs md:text-sm font-medium text-gray-500 dark:text-gray-400 text-center">
                                            {player.score}
                                        </td>
                                        <td className="px-3 sm:px-6 py-3 whitespace-nowrap text-xs md:text-sm text-right font-medium">
                                            <span className={`inline-flex items-center justify-center min-w-[36px] px-2 py-1 rounded-[4px] text-[11px] md:text-xs font-bold ${
                                                player.ping < 50 ? 'bg-green-100 text-green-700 dark:bg-green-500/15 dark:text-green-500' :
                                                player.ping < 100 ? 'bg-yellow-100 text-yellow-700 dark:bg-yellow-500/15 dark:text-yellow-500' :
                                                'bg-red-100 text-red-700 dark:bg-red-500/15 dark:text-red-500'
                                            }`}>
                                                {player.ping}
                                            </span>
                                        </td>
                                    </tr>
                                ))
                            ) : (
                                <tr>
                                    <td colSpan={4} className="px-6 py-10 text-center text-sm text-gray-500 dark:text-gray-400">
                                        Pemain tidak ditemukan.
                                    </td>
                                </tr>
                            )}
                        </tbody>
                    </table>
                )}
            </div>
        </div>
    );
};
