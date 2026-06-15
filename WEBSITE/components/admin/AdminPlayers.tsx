
import React, { useState, useMemo, useEffect } from 'react';
import { Users, Search } from 'lucide-react';
import { Player } from '../../types';
import { MOCK_ALL_PLAYERS } from '../../data/mockData';
import { PlayerControlModal } from './players/PlayerControlModal';
import { isPreviewEnv, API_URL } from '../../config';

export const AdminPlayers: React.FC = () => {
  const [players, setPlayers] = useState<Player[]>([]);
  const [playerSearch, setPlayerSearch] = useState('');
  const [playerFilter, setPlayerFilter] = useState('All');
  
  // State for the Detailed Control Modal
  const [selectedPlayer, setSelectedPlayer] = useState<Player | null>(null);
  const [actionLoading, setActionLoading] = useState<string | null>(null);

  useEffect(() => {
    const fetchPlayers = async () => {
        if (isPreviewEnv()) {
            setPlayers(MOCK_ALL_PLAYERS);
            return;
        }

        try {
            const res = await fetch(`${API_URL}/api_players.php?action=list`);
            const data = await res.json();
            if (data && data.status === 'success') {
                setPlayers(data.data);
            }
        } catch (e) {
            console.error("Failed to fetch players", e);
        }
    };
    fetchPlayers();
  }, []);

  const handleQuickAction = async (action: string) => {
      if(!selectedPlayer) return;
      
      const confirmMsg = action === 'CK' 
        ? "PERINGATAN: Character Kill akan mereset Level, Uang, dan Aset. Lanjutkan?" 
        : `Apakah Anda yakin ingin melakukan tindakan: ${action} pada ${selectedPlayer.name}?`;

      if(confirm(confirmMsg)) {
          setActionLoading(action);
          
          if (isPreviewEnv()) {
              setTimeout(() => {
                  setActionLoading(null);
                  
                  if(action === 'Ban') {
                      setPlayers(prev => prev.map(p => p.id === selectedPlayer.id ? {...p, status: 'Banned'} : p));
                      setSelectedPlayer(prev => prev ? {...prev, status: 'Banned'} : null);
                  } else if (action === 'CK') {
                      setPlayers(prev => prev.map(p => p.id === selectedPlayer.id ? {...p, score: 1, money: 250, faction: 'Warga Sipil'} : p));
                      setSelectedPlayer(null);
                  }
                  
                  alert(`Tindakan ${action} berhasil dieksekusi (Preview).`);
              }, 1500);
              return;
          }

          try {
              const res = await fetch(`${API_URL}/api_players.php`, {
                  method: 'POST',
                  headers: { 'Content-Type': 'application/json' },
                  body: JSON.stringify({ action: action, playerId: selectedPlayer.id })
              });
              const data = await res.json();
              if (data && data.status === 'success') {
                  // Update state based on action
                  if(action === 'Ban') {
                      setPlayers(prev => prev.map(p => p.id === selectedPlayer.id ? {...p, status: 'Banned'} : p));
                      setSelectedPlayer(prev => prev ? {...prev, status: 'Banned'} : null);
                  } else if (action === 'CK') {
                      setPlayers(prev => prev.map(p => p.id === selectedPlayer.id ? {...p, score: 1, money: 250, faction: 'Warga Sipil'} : p));
                      setSelectedPlayer(null);
                  }
                  alert(`Tindakan ${action} berhasil dieksekusi.`);
              } else {
                  alert(data.message || 'Tindakan gagal.');
              }
          } catch(e) {
              console.error("Action error", e);
              alert("Terjadi kesalahan sistem.");
          } finally {
              setActionLoading(null);
          }
      }
  };

  const handleSaveData = async (e: React.FormEvent) => {
      e.preventDefault();
      
      const form = e.target as HTMLFormElement;
      const formData = new FormData(form);
      const updatedData = Object.fromEntries(formData);
      
      if (isPreviewEnv()) {
          alert("Data dasar disimpan (Preview). Log admin telah dicatat.");
          setSelectedPlayer(null);
          return;
      }

      setActionLoading('Save');
      try {
          const res = await fetch(`${API_URL}/api_players.php`, {
              method: 'POST',
              headers: { 'Content-Type': 'application/json' },
              body: JSON.stringify({ action: 'Save', playerId: selectedPlayer?.id, data: updatedData })
          });
          const data = await res.json();
          if (data && data.status === 'success') {
              alert("Data berhasil disimpan.");
              setPlayers(prev => prev.map(p => p.id === selectedPlayer?.id ? { ...p, name: updatedData.username as string || p.name } : p));
              setSelectedPlayer(null);
          } else {
              alert(data.message || 'Gagal menyimpan.');
          }
      } catch (e) {
          console.error("Save error", e);
          alert("Gagal menghubungi server.");
      } finally {
          setActionLoading(null);
      }
  };

  const filteredPlayers = useMemo(() => {
    return players.filter(p => {
        const matchesSearch = p.name.toLowerCase().includes(playerSearch.toLowerCase()) || 
                             p.id.toString().includes(playerSearch) ||
                             p.faction.toLowerCase().includes(playerSearch.toLowerCase());
        const matchesFilter = playerFilter === 'All' ? true : p.status === playerFilter;
        return matchesSearch && matchesFilter;
    });
  }, [players, playerSearch, playerFilter]);

  return (
    <div className="animate-[fadeIn_0.3s_ease-out]">
            <div className="bg-white dark:bg-[#0a0a0a] rounded-xl border border-gray-200 dark:border-white/5 overflow-hidden shadow-sm">
                <div className="p-4 border-b border-gray-200 dark:border-white/5 flex flex-col md:flex-row justify-between items-center gap-3">
                    <h3 className="font-bold text-gray-900 dark:text-white uppercase text-sm flex items-center gap-2">
                    <Users size={16} className="text-red-500"/> Manajemen Warga
                    </h3>
                    <div className="flex gap-2 w-full md:w-auto">
                        <select 
                        value={playerFilter}
                        onChange={(e) => setPlayerFilter(e.target.value)}
                        className="bg-gray-100 dark:bg-white/5 border border-gray-200 dark:border-white/10 rounded-lg px-3 py-1.5 text-xs text-gray-700 dark:text-gray-300 outline-none"
                        >
                            <option value="All">Semua Status</option>
                            <option value="Online">Online</option>
                            <option value="Offline">Offline</option>
                            <option value="Banned">Banned</option>
                        </select>
                        <div className="relative flex-1">
                        <Search size={14} className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-500" />
                        <input 
                            type="text" 
                            placeholder="Cari Nama/ID/Faksi..." 
                            value={playerSearch}
                            onChange={(e) => setPlayerSearch(e.target.value)}
                            className="w-full bg-gray-100 dark:bg-white/5 pl-8 pr-3 py-1.5 rounded-lg text-xs outline-none focus:border-red-500 border border-gray-200 dark:border-white/10" 
                        />
                        </div>
                    </div>
                </div>
                
                <div className="overflow-x-auto">
                <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                    <thead className="bg-gray-50 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500 border-b border-gray-200 dark:border-white/5">
                        <tr>
                            <th className="px-4 py-3">ID</th>
                            <th className="px-4 py-3">Nama Karakter</th>
                            <th className="px-4 py-3">Level</th>
                            <th className="px-4 py-3">Faksi</th>
                            <th className="px-4 py-3">Ping</th>
                            <th className="px-4 py-3">Status</th>
                            <th className="px-4 py-3 text-right">Aksi</th>
                        </tr>
                    </thead>
                    <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                        {filteredPlayers.length > 0 ? filteredPlayers.map((player) => (
                            <tr key={player.id} className="hover:bg-gray-50 dark:hover:bg-white/5 transition-colors">
                                <td className="px-4 py-3 font-mono text-gray-500">#{player.id}</td>
                                <td className="px-4 py-3 font-bold text-gray-900 dark:text-white">{player.name.replace('_', ' ')}</td>
                                <td className="px-4 py-3">{Math.floor(player.score / 100) + 1}</td>
                                <td className="px-4 py-3"><span className="bg-gray-100 dark:bg-white/5 px-1.5 py-0.5 rounded border border-gray-200 dark:border-white/10">{player.faction}</span></td>
                                <td className="px-4 py-3 font-mono text-green-500">{player.ping}ms</td>
                                <td className="px-4 py-3">
                                    <span className={`px-2 py-0.5 rounded-full text-[9px] font-bold uppercase border ${
                                        player.status === 'Online' ? 'text-green-600 border-green-200 bg-green-50 dark:bg-green-900/10' : 
                                        player.status === 'Banned' ? 'text-red-600 border-red-200 bg-red-50 dark:bg-red-900/10' :
                                        'text-gray-500 border-gray-200 bg-gray-50 dark:bg-gray-900/10'
                                    }`}>
                                        {player.status}
                                    </span>
                                </td>
                                <td className="px-4 py-3 text-right flex justify-end gap-2">
                                    <button 
                                        onClick={() => setSelectedPlayer(player)}
                                        className="bg-gray-100 dark:bg-white/10 hover:bg-gray-200 dark:hover:bg-white/20 text-gray-700 dark:text-gray-300 px-3 py-1 rounded text-[10px] font-bold uppercase"
                                    >
                                        Manage
                                    </button>
                                </td>
                            </tr>
                        )) : (
                            <tr><td colSpan={7} className="px-6 py-8 text-center text-gray-500">Tidak ada data pemain.</td></tr>
                        )}
                    </tbody>
                </table>
                </div>
            </div>

            {/* PLAYER CONTROL CENTER MODAL */}
            {selectedPlayer && (
                <PlayerControlModal 
                    player={selectedPlayer}
                    onClose={() => setSelectedPlayer(null)}
                    onAction={handleQuickAction}
                    onSave={handleSaveData}
                    actionLoading={actionLoading}
                />
            )}
    </div>
  );
};
