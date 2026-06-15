
import React, { useState, useEffect } from 'react';
import { AreaChart, Area, XAxis, YAxis, Tooltip, ResponsiveContainer, CartesianGrid, Legend } from 'recharts';
import { TrendingUp } from 'lucide-react';
import { ECONOMY_DATA } from '../../../data/mockData';
import { isPreviewEnv, API_URL } from '../../../config';

export const EconomyChart: React.FC = () => {
  const [chartData, setChartData] = useState<any[]>(ECONOMY_DATA);
  const [totalCash, setTotalCash] = useState<string>("$2.6M");

  useEffect(() => {
    const fetchData = async () => {
      if (!isPreviewEnv()) {
        try {
          const res = await fetch(`${API_URL}/api_overview.php?action=chart`);
          const data = await res.json();
          if (data && data.status === 'success') {
            setChartData(data.data.chartData);
            setTotalCash(data.data.totalCash);
          }
        } catch (error) {
          console.error("Error fetching economy data:", error);
        }
      }
    };
    fetchData();
  }, []);

  return (
    <div className="bg-white dark:bg-[#121212] rounded-2xl border border-gray-100 dark:border-white/5 p-6 relative overflow-hidden flex flex-col shadow-sm hover:shadow-md transition-shadow duration-300 h-full">
        <div className="flex flex-row justify-between items-center mb-6 gap-2">
            <div>
                <h3 className="text-gray-900 dark:text-white font-black uppercase flex items-center text-sm tracking-widest">
                    <TrendingUp className="mr-2 text-red-500" size={20} /> Inflasi Server
                </h3>
                <p className="text-[10px] text-gray-400 font-medium mt-1">Perbandingan Uang Beredar vs Nilai Aset</p>
            </div>
            <div className="text-right">
                <span className="text-[10px] text-gray-400 font-bold uppercase tracking-widest">Total Cash</span>
                <span className="text-2xl font-black text-transparent bg-clip-text bg-gradient-to-r from-red-500 to-orange-500 block leading-none tracking-tight">{totalCash}</span>
            </div>
        </div>
        <div className="w-full h-[250px] md:h-[300px] min-h-[250px]">
            <ResponsiveContainer width="100%" height="100%">
                <AreaChart data={chartData} margin={{ top: 10, right: 10, left: 0, bottom: 0 }}>
                    <defs>
                        <linearGradient id="colorCirculation" x1="0" y1="0" x2="0" y2="1">
                            <stop offset="5%" stopColor="#ef4444" stopOpacity={0.2}/>
                            <stop offset="95%" stopColor="#ef4444" stopOpacity={0}/>
                        </linearGradient>
                        <linearGradient id="colorAssets" x1="0" y1="0" x2="0" y2="1">
                            <stop offset="5%" stopColor="#22c55e" stopOpacity={0.2}/>
                            <stop offset="95%" stopColor="#22c55e" stopOpacity={0}/>
                        </linearGradient>
                    </defs>
                    <CartesianGrid strokeDasharray="3 3" vertical={false} stroke="#333" opacity={0.1} />
                    <XAxis 
                        dataKey="day" 
                        stroke="#9ca3af" 
                        tick={{fontSize: 10, fontWeight: 600}} 
                        tickLine={false} 
                        axisLine={false} 
                        dy={10}
                    />
                    <YAxis 
                        stroke="#9ca3af" 
                        tick={{fontSize: 10, fontWeight: 600}} 
                        tickLine={false} 
                        axisLine={false} 
                        width={40}
                        tickFormatter={(value) => {
                            if (value >= 1000000) return `${(value / 1000000).toFixed(1)}M`;
                            if (value >= 1000) return `${(value / 1000).toFixed(0)}K`;
                            return value;
                        }}
                    />
                    <Tooltip 
                        contentStyle={{ 
                            backgroundColor: 'rgba(255, 255, 255, 0.8)', 
                            backdropFilter: 'blur(8px)',
                            borderColor: 'rgba(0,0,0,0.05)', 
                            color: '#000', 
                            fontSize: '12px',
                            borderRadius: '12px',
                            boxShadow: '0 10px 15px -3px rgba(0, 0, 0, 0.1)'
                        }} 
                        itemStyle={{ fontWeight: 700 }}
                        cursor={{ stroke: '#ef4444', strokeWidth: 1, strokeDasharray: '5 5' }}
                        formatter={(value: number) => new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', maximumFractionDigits: 0 }).format(value)}
                    />
                    <Legend iconType="circle" wrapperStyle={{ fontSize: '11px', fontWeight: 600, paddingTop: '20px' }} />
                    <Area 
                        type="monotone" 
                        dataKey="circulation" 
                        name="Uang Beredar (Cash)" 
                        stroke="#ef4444" 
                        strokeWidth={3}
                        fillOpacity={1} 
                        fill="url(#colorCirculation)" 
                        activeDot={{ r: 6, strokeWidth: 0 }}
                    />
                    <Area 
                        type="monotone" 
                        dataKey="assets" 
                        name="Nilai Aset (Properti)" 
                        stroke="#22c55e" 
                        strokeWidth={3}
                        fillOpacity={1} 
                        fill="url(#colorAssets)" 
                        activeDot={{ r: 6, strokeWidth: 0 }}
                    />
                </AreaChart>
            </ResponsiveContainer>
        </div>
    </div>
  );
};
