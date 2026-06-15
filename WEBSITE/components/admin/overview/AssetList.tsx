
import React, { useState, useEffect } from 'react';
import { MOCK_HOUSES, MOCK_BUSINESSES, MOCK_JOBS, MOCK_FACTIONS, MOCK_FAMILIES } from '../../../data/mockData';
import { isPreviewEnv, API_URL } from '../../../config';

interface AssetListProps {
    category: string | null;
    onSelectDetail: (id: number) => void;
}

export const AssetList: React.FC<AssetListProps> = ({ category, onSelectDetail }) => {
    const [assets, setAssets] = useState<any[]>([]);

    useEffect(() => {
        const fetchAssets = async () => {
            if (isPreviewEnv()) {
                if (category === 'houses') setAssets(MOCK_HOUSES);
                else if (category === 'businesses') setAssets(MOCK_BUSINESSES);
                else if (category === 'jobs' || category === 'sidejobs') {
                    setAssets(MOCK_JOBS.filter(j => j.type.toLowerCase() === (category === 'jobs' ? 'job' : 'sidejob')));
                }
                else if (category === 'factions') setAssets(MOCK_FACTIONS);
                else if (category === 'families') setAssets(MOCK_FAMILIES);
                return;
            }

            if (category) {
                try {
                    const res = await fetch(`${API_URL}/api_overview.php?action=assets&type=${category}`);
                    const data = await res.json();
                    if (data && data.status === 'success') {
                        setAssets(data.data);
                    }
                } catch (e) {
                    console.error("Error fetching assets:", e);
                }
            }
        };
        fetchAssets();
    }, [category]);

    switch(category) {
        case 'houses':
            return (
                <div className="overflow-x-auto">
                    <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                        <thead className="bg-gray-100 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500">
                            <tr><th className="px-4 py-3">ID</th><th className="px-4 py-3">Lokasi</th><th className="px-4 py-3">Pemilik</th><th className="px-4 py-3">Harga</th><th className="px-4 py-3 text-right">Aksi</th></tr>
                        </thead>
                        <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                            {assets.map((house: any) => (
                                <tr key={house.id} className="hover:bg-gray-50 dark:hover:bg-white/5 cursor-pointer" onClick={() => onSelectDetail(house.id)}>
                                    <td className="px-4 py-3 font-mono">#{house.id}</td>
                                    <td className="px-4 py-3 font-bold text-gray-900 dark:text-white">{house.location}</td>
                                    <td className="px-4 py-3">{house.owner}</td>
                                    <td className="px-4 py-3 text-green-500">${house.price.toLocaleString()}</td>
                                    <td className="px-4 py-3 text-right text-blue-500 font-bold hover:underline">Detail</td>
                                </tr>
                            ))}
                        </tbody>
                    </table>
                </div>
            );
        case 'businesses':
             return (
                <div className="overflow-x-auto">
                    <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                        <thead className="bg-gray-100 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500">
                            <tr><th className="px-4 py-3">ID</th><th className="px-4 py-3">Bisnis</th><th className="px-4 py-3">Tipe</th><th className="px-4 py-3">Lokasi</th><th className="px-4 py-3">Pemilik</th><th className="px-4 py-3 text-right">Aksi</th></tr>
                        </thead>
                        <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                            {assets.map((biz: any) => (
                                <tr key={biz.id} className="hover:bg-gray-50 dark:hover:bg-white/5 cursor-pointer" onClick={() => onSelectDetail(biz.id)}>
                                    <td className="px-4 py-3 font-mono">#{biz.id}</td>
                                    <td className="px-4 py-3 font-bold text-gray-900 dark:text-white">{biz.name}</td>
                                    <td className="px-4 py-3"><span className="bg-blue-500/20 text-blue-400 px-2 py-0.5 rounded text-[10px] uppercase font-bold">{biz.type}</span></td>
                                    <td className="px-4 py-3">{biz.location}</td>
                                    <td className="px-4 py-3">{biz.owner}</td>
                                    <td className="px-4 py-3 text-right text-blue-500 font-bold hover:underline">Pantau</td>
                                </tr>
                            ))}
                        </tbody>
                    </table>
                </div>
            );
        case 'jobs':
        case 'sidejobs':
             return (
                <div className="overflow-x-auto">
                    <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                        <thead className="bg-gray-100 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500">
                            <tr><th className="px-4 py-3">Pekerjaan</th><th className="px-4 py-3">Lokasi</th><th className="px-4 py-3">Rata2 Pekerja/Hari</th><th className="px-4 py-3">Perputaran Uang</th><th className="px-4 py-3">Jam Kerja Avg</th></tr>
                        </thead>
                        <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                            {assets.map((job: any) => (
                                <tr key={job.id} className="hover:bg-gray-50 dark:hover:bg-white/5">
                                    <td className="px-4 py-3 font-bold text-gray-900 dark:text-white">{job.name}</td>
                                    <td className="px-4 py-3">{job.location}</td>
                                    <td className="px-4 py-3">{job.avgWorkers} Orang</td>
                                    <td className="px-4 py-3 text-green-500">${job.avgCirculation.toLocaleString()}</td>
                                    <td className="px-4 py-3">{job.avgHours} Jam</td>
                                </tr>
                            ))}
                        </tbody>
                    </table>
                </div>
            );
         case 'factions':
             return (
                <div className="overflow-x-auto">
                    <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                        <thead className="bg-gray-100 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500">
                            <tr><th className="px-4 py-3">ID</th><th className="px-4 py-3">Nama Fraksi</th><th className="px-4 py-3">Leader</th><th className="px-4 py-3">Anggota</th><th className="px-4 py-3">Saldo Bank</th><th className="px-4 py-3 text-right">Aksi</th></tr>
                        </thead>
                        <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                            {assets.map((fac: any) => (
                                <tr key={fac.id} className="hover:bg-gray-50 dark:hover:bg-white/5 cursor-pointer" onClick={() => onSelectDetail(fac.id)}>
                                    <td className="px-4 py-3 font-mono">#{fac.id}</td>
                                    <td className="px-4 py-3 font-bold text-gray-900 dark:text-white">{fac.name}</td>
                                    <td className="px-4 py-3 text-amber-500">{fac.leader}</td>
                                    <td className="px-4 py-3">{fac.members.length} Personil</td>
                                    <td className="px-4 py-3 text-green-500">${fac.bank.toLocaleString()}</td>
                                    <td className="px-4 py-3 text-right text-blue-500 font-bold hover:underline">Kelola</td>
                                </tr>
                            ))}
                        </tbody>
                    </table>
                </div>
            );
         case 'families':
             return (
                <div className="overflow-x-auto">
                    <table className="w-full text-left text-xs text-gray-600 dark:text-gray-400">
                        <thead className="bg-gray-100 dark:bg-[#0f0f0f] uppercase font-bold text-[10px] text-gray-500">
                            <tr><th className="px-4 py-3">ID</th><th className="px-4 py-3">Nama Family</th><th className="px-4 py-3">Leader</th><th className="px-4 py-3">Level</th><th className="px-4 py-3">Saldo Bank</th><th className="px-4 py-3 text-right">Aksi</th></tr>
                        </thead>
                        <tbody className="divide-y divide-gray-100 dark:divide-white/5">
                            {assets.map((fam: any) => (
                                <tr key={fam.id} className="hover:bg-gray-50 dark:hover:bg-white/5 cursor-pointer" onClick={() => onSelectDetail(fam.id)}>
                                    <td className="px-4 py-3 font-mono">#{fam.id}</td>
                                    <td className="px-4 py-3 font-bold text-gray-900 dark:text-white">{fam.name}</td>
                                    <td className="px-4 py-3 text-red-500">{fam.leader}</td>
                                    <td className="px-4 py-3"><span className="bg-gray-700 text-white px-2 py-0.5 rounded text-[10px]">Lvl {fam.level}</span></td>
                                    <td className="px-4 py-3 text-green-500">${fam.bank.toLocaleString()}</td>
                                    <td className="px-4 py-3 text-right text-blue-500 font-bold hover:underline">Detail</td>
                                </tr>
                            ))}
                        </tbody>
                    </table>
                </div>
            );
        default: return <div className="p-4 text-center">Pilih kategori aset.</div>
    }
};
