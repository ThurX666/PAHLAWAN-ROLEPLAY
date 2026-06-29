
import React, { useState, useEffect } from 'react';
import { MapPin, Box, TrendingUp, Users } from 'lucide-react';
import { BarChart, Bar, XAxis, YAxis, Tooltip, ResponsiveContainer, CartesianGrid } from 'recharts';
import { MOCK_HOUSES, MOCK_BUSINESSES, MOCK_FACTIONS, MOCK_FAMILIES } from '../../../data/mockData';
import { isPreviewEnv, API_URL } from '../../../config';

interface AssetDetailProps {
    category: string | null;
    detailId: number | null;
}

export const AssetDetail: React.FC<AssetDetailProps> = ({ category, detailId }) => {
    const [detailData, setDetailData] = useState<any>(null);

    useEffect(() => {
        const fetchDetail = async () => {
            if (isPreviewEnv()) {
                if (category === 'houses') setDetailData(MOCK_HOUSES.find(h => h.id === detailId));
                else if (category === 'businesses') setDetailData(MOCK_BUSINESSES.find(h => h.id === detailId));
                else if (category === 'factions') setDetailData(MOCK_FACTIONS.find(h => h.id === detailId));
                else if (category === 'families') setDetailData(MOCK_FAMILIES.find(h => h.id === detailId));
                return;
            }

            if (category && detailId) {
                try {
                    const res = await fetch(`${API_URL}/api_overview.php?action=detail&type=${category}&id=${detailId}`);
                    const data = await res.json();
                    if (data && data.status === 'success') {
                        setDetailData(data.data);
                    }
                } catch (e) {
                    console.error("Error fetching detail:", e);
                }
            }
        };
        fetchDetail();
    }, [category, detailId]);

    const house = category === 'houses' ? detailData : null;
    const biz = category === 'businesses' ? detailData : null;
    const data = category === 'factions' || category === 'families' ? detailData : null;

    if(category === 'houses') {
        if(!house) return <div>Data tidak ditemukan.</div>;
        return (
            <div className="p-6 space-y-6">
                <div className="flex justify-between items-start">
                    <div>
                        <h3 className="text-2xl font-black text-gray-900 dark:text-white uppercase italic">Rumah #{house.id}</h3>
                        <p className="text-sm text-gray-500 flex items-center gap-2"><MapPin size={14}/> {house.location}</p>
                    </div>
                    <div className="text-right">
                        <p className="text-xs font-bold uppercase text-gray-500">Harga Properti</p>
                        <p className="text-xl font-black text-green-500">${house.price.toLocaleString()}</p>
                    </div>
                </div>
                
                <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
                    <div className="bg-gray-50 dark:bg-ph-surface-deep p-4 rounded-xl border border-gray-200 dark:border-white/5">
                        <h4 className="font-bold text-gray-900 dark:text-white mb-2 uppercase text-xs">Informasi Pemilik</h4>
                        <p className="text-sm">Pemilik: <span className="font-bold">{house.owner}</span></p>
                        <p className="text-sm mt-1">Status Pintu: <span className={`font-bold ${house.locked ? 'text-red-500' : 'text-green-500'}`}>{house.locked ? 'Terkunci' : 'Terbuka'}</span></p>
                    </div>
                    
                    <div className="bg-gray-50 dark:bg-ph-surface-deep p-4 rounded-xl border border-gray-200 dark:border-white/5">
                        <h4 className="font-bold text-gray-900 dark:text-white mb-2 uppercase text-xs flex items-center gap-2"><Box size={14}/> Isi Lemari Penyimpanan</h4>
                        {house.storage.length > 0 ? (
                            <ul className="space-y-1">
                                {house.storage.map((item, idx) => (
                                    <li key={idx} className="flex justify-between text-xs border-b border-gray-200 dark:border-white/5 pb-1 last:border-0">
                                        <span>{item.item}</span>
                                        <span className="font-mono font-bold text-gray-500">x{item.qty}</span>
                                    </li>
                                ))}
                            </ul>
                        ) : <p className="text-xs text-gray-500 italic">Lemari kosong.</p>}
                    </div>
                </div>
            </div>
        )
    }

    if(category === 'businesses') {
        if(!biz) return <div>Data tidak ditemukan.</div>;
        return (
            <div className="p-6 space-y-6">
                <div className="flex justify-between items-start">
                    <div>
                        <h3 className="text-2xl font-black text-gray-900 dark:text-white uppercase italic">{biz.name}</h3>
                        <span className="bg-blue-500/20 text-blue-500 px-2 py-0.5 rounded text-[10px] uppercase font-bold">{biz.type}</span>
                        <p className="text-sm text-gray-500 mt-1 flex items-center gap-2"><MapPin size={14}/> {biz.location} | Owner: {biz.owner}</p>
                    </div>
                    <div className="text-right">
                            <p className="text-xs font-bold uppercase text-gray-500">Saldo Kas</p>
                            <p className="text-xl font-black text-green-500">${biz.balance.toLocaleString()}</p>
                    </div>
                </div>

                <div className="bg-gray-50 dark:bg-ph-surface-deep p-4 rounded-xl border border-gray-200 dark:border-white/5">
                    <h4 className="font-bold text-gray-900 dark:text-white mb-4 uppercase text-xs flex items-center gap-2"><TrendingUp size={14} className="text-green-500"/> Pendapatan 7 Hari Terakhir (Inflasi Check)</h4>
                    <div className="h-[200px] w-full min-h-[200px]">
                        <ResponsiveContainer width="100%" height="100%">
                            <BarChart data={biz.revenueHistory}>
                                <CartesianGrid strokeDasharray="3 3" vertical={false} stroke="#333" opacity={0.2} />
                                <XAxis dataKey="day" stroke="#666" tick={{fontSize: 10}} axisLine={false} tickLine={false} />
                                <YAxis stroke="#666" tick={{fontSize: 10}} axisLine={false} tickLine={false} />
                                <Tooltip contentStyle={{ backgroundColor: '#111', borderColor: '#333', color: '#fff', fontSize: '12px' }} cursor={{fill: 'rgba(255,255,255,0.05)'}} />
                                <Bar dataKey="amount" fill="#22c55e" radius={[4, 4, 0, 0]} />
                            </BarChart>
                        </ResponsiveContainer>
                    </div>
                </div>
            </div>
        )
    }

    if(category === 'factions' || category === 'families') {
        if(!data) return <div>Data tidak ditemukan.</div>;

        return (
            <div className="p-6 space-y-6">
                <div className="flex justify-between items-start">
                    <div>
                        <h3 className="text-2xl font-black text-gray-900 dark:text-white uppercase italic">{data.name}</h3>
                        <p className="text-sm text-gray-500 mt-1">Leader: <span className="font-bold text-amber-500">{data.leader}</span></p>
                    </div>
                    <div className="text-right">
                            <p className="text-xs font-bold uppercase text-gray-500">Saldo Bank Organisasi</p>
                            <p className="text-xl font-black text-green-500">${data.bank.toLocaleString()}</p>
                    </div>
                </div>

                <div className="bg-gray-50 dark:bg-ph-surface-deep rounded-xl border border-gray-200 dark:border-white/5 overflow-hidden">
                        <div className="p-3 border-b border-gray-200 dark:border-white/5 bg-gray-100 dark:bg-white/5">
                            <h4 className="font-bold text-gray-900 dark:text-white uppercase text-xs flex items-center gap-2"><Users size={14}/> Daftar Anggota</h4>
                        </div>
                        <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                            <thead className="bg-white dark:bg-ph-surface-deep border-b border-gray-200 dark:border-white/5">
                                <tr>
                                    <th className="px-4 py-2">Nama</th>
                                    <th className="px-4 py-2">Pangkat</th>
                                    <th className="px-4 py-2">Duty Hours</th>
                                    <th className="px-4 py-2 text-right">Terakhir Login</th>
                                </tr>
                            </thead>
                            <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                                {data.members.map((member, idx) => (
                                    <tr key={idx}>
                                        <td className="px-4 py-2 font-bold text-gray-900 dark:text-white">{member.name}</td>
                                        <td className="px-4 py-2">{member.rank}</td>
                                        <td className="px-4 py-2 font-mono text-blue-500">{member.dutyHours} Jam</td>
                                        <td className="px-4 py-2 text-right">{member.lastLogin}</td>
                                    </tr>
                                ))}
                            </tbody>
                        </table>
                </div>
            </div>
        )
    }

    return <div>Detail not implemented for this category.</div>
};
