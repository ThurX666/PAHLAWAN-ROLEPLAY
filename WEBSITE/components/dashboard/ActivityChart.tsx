
import React, { useState, useEffect } from 'react';
import { AreaChart, Area, ResponsiveContainer, Tooltip, XAxis, YAxis, CartesianGrid } from 'recharts';

import { isPreviewEnv, API_URL } from '../../config';

type TimeRange = '24h' | '7d' | '4w';

const getCurrentFormattedTime = () => {
    const now = new Date();
    return `${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}`;
}

const MOCK_DATA = {
    '24h': [
        { name: '00:00', active: 120 },
        { name: '01:00', active: 110 },
        { name: '02:00', active: 90 },
        { name: '03:00', active: 75 },
        { name: '04:00', active: 80 },
        { name: '05:00', active: 100 },
        { name: '06:00', active: 150 },
        { name: '07:00', active: 200 },
        { name: '08:00', active: 250 },
        { name: '09:00', active: 300 },
        { name: '10:00', active: 320 },
        { name: '11:00', active: 400 },
        { name: '12:00', active: 480 },
        { name: '13:00', active: 500 },
        { name: '14:00', active: 620 },
        { name: '15:00', active: 700 },
        { name: '16:00', active: 750 },
        { name: '17:00', active: 820 },
        { name: '18:00', active: 880 },
        { name: '19:00', active: 900 },
        { name: '20:00', active: 920 },
        { name: '21:00', active: 850 },
        { name: '22:00', active: 750 },
        { name: getCurrentFormattedTime(), active: 610 },
    ],
    '7d': [
        { name: 'Senin', active: 400 },
        { name: 'Selasa', active: 300 },
        { name: 'Rabu', active: 550 },
        { name: 'Kamis', active: 450 },
        { name: 'Jumat', active: 800 },
        { name: 'Sabtu', active: 950 },
        { name: 'Minggu', active: 900 },
    ],
    '4w': [
        { name: 'Minggu 1', active: 850 },
        { name: 'Minggu 2', active: 920 },
        { name: 'Minggu 3', active: 880 },
        { name: 'Minggu 4', active: 980 },
    ]
};

export const ActivityChart: React.FC = () => {
  const [timeRange, setTimeRange] = useState<TimeRange>('7d');
  const [chartData, setChartData] = useState<any[]>([]);

  const [peak, setPeak] = useState(0);
  const [average, setAverage] = useState(0);

  useEffect(() => {
      const loadData = () => {
          if (isPreviewEnv()) {
              const dataToUse = JSON.parse(JSON.stringify(MOCK_DATA[timeRange]));
              // If it's 24h, always update the last item's time to exact current HH:MM
              if (timeRange === '24h' && dataToUse.length > 0) {
                  dataToUse[dataToUse.length - 1].name = getCurrentFormattedTime();
              }
              
              setChartData(dataToUse);
              const max = Math.max(...dataToUse.map((d: any) => d.active));
              const sum = dataToUse.reduce((a: number, b: any) => a + Number(b.active), 0);
              const avg = Math.floor(sum / dataToUse.length);
              setPeak(max);
              setAverage(avg);
              return;
          }

          fetch(`${API_URL}/api_activity_chart.php?range=${timeRange}`)
              .then(response => response.json())
              .then(data => {
                  if (data && data.length > 0) {
                      setChartData(data);
                      const max = Math.max(...data.map((d: any) => d.active));
                      const sum = data.reduce((a: number, b: any) => a + Number(b.active), 0);
                      const avg = Math.floor(sum / data.length);
                      setPeak(max);
                      setAverage(avg);
                  } else {
                      setChartData([]);
                      setPeak(0);
                      setAverage(0);
                  }
              })
              .catch(error => {
                  console.error("Error fetching activity data:", error);
                  setChartData([]);
                  setPeak(0);
                  setAverage(0);
              });
      };

      // Load initially
      loadData();

      // Set up interval to reload data every 1 minute
      const intervalId = setInterval(loadData, 60000);

      // Clean up interval on unmount or when timeRange changes
      return () => clearInterval(intervalId);
  }, [timeRange]);

  const getRangeLabel = () => {
      switch(timeRange) {
          case '24h': return '24 Jam Terakhir';
          case '7d': return '7 Hari Terakhir';
          case '4w': return '4 Minggu Terakhir';
      }
  };

  return (
    <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-xl md:rounded-2xl p-5 md:p-6 shadow-sm flex flex-col h-full min-h-[300px]">
         <div className="mb-6 flex flex-col xl:flex-row xl:items-start justify-between gap-4">
             <div className="flex flex-col md:flex-row md:items-center xl:items-start xl:flex-col gap-4">
                 <div>
                    <h3 className="text-sm md:text-base font-bold text-gray-900 dark:text-white uppercase tracking-wider mb-1">Aktivitas Server</h3>
                    <p className="text-[10px] text-gray-500 uppercase font-bold tracking-widest flex items-center gap-2">
                        <span className="w-1.5 h-1.5 rounded-full bg-red-500 animate-pulse"></span>
                        Live Traffic ({getRangeLabel()})
                    </p>
                 </div>
                 
                 {/* Time Range Selectors */}
                 <div className="flex items-center gap-1 bg-gray-100 dark:bg-white/5 p-1 rounded-lg w-fit md:ml-auto xl:ml-0">
                     <button 
                        onClick={() => setTimeRange('24h')}
                        className={`px-3 py-1.5 text-[10px] md:text-xs font-bold uppercase rounded-md transition-all ${timeRange === '24h' ? 'bg-white dark:bg-[#202020] text-red-500 shadow-sm' : 'text-gray-500 hover:text-gray-900 dark:hover:text-white'}`}
                     >
                        24 Jam
                     </button>
                     <button 
                        onClick={() => setTimeRange('7d')}
                        className={`px-3 py-1.5 text-[10px] md:text-xs font-bold uppercase rounded-md transition-all ${timeRange === '7d' ? 'bg-white dark:bg-[#202020] text-red-500 shadow-sm' : 'text-gray-500 hover:text-gray-900 dark:hover:text-white'}`}
                     >
                        7 Hari
                     </button>
                     <button 
                        onClick={() => setTimeRange('4w')}
                        className={`px-3 py-1.5 text-[10px] md:text-xs font-bold uppercase rounded-md transition-all ${timeRange === '4w' ? 'bg-white dark:bg-[#202020] text-red-500 shadow-sm' : 'text-gray-500 hover:text-gray-900 dark:hover:text-white'}`}
                     >
                        4 Minggu
                     </button>
                 </div>
             </div>
             
             <div className="grid grid-cols-2 w-full md:flex md:w-auto xl:w-auto xl:justify-end gap-0 md:gap-6 border-t md:border-t-0 border-gray-100 dark:border-white/5 pt-4 md:pt-0 divide-x divide-gray-200 dark:divide-white/10 md:divide-x-0 mt-2 md:mt-0">
                <div className="text-center md:text-right">
                    <p className="text-[10px] font-bold uppercase text-gray-400 tracking-widest">Puncak</p>
                    <p className="text-lg md:text-xl font-black text-gray-900 dark:text-white leading-none mt-1">{peak}</p>
                </div>
                <div className="text-center md:text-right md:border-l md:border-gray-200 md:dark:border-white/10 md:pl-6">
                    <p className="text-[10px] font-bold uppercase text-gray-400 tracking-widest">Rata-rata</p>
                    <p className="text-lg md:text-xl font-black text-gray-900 dark:text-white leading-none mt-1">{average}</p>
                </div>
             </div>
         </div>
         
         <div className="flex-1 w-full min-h-[200px] h-[250px]">
            <ResponsiveContainer width="100%" height="100%">
                <AreaChart data={chartData} margin={{ top: 10, right: 0, left: -20, bottom: 0 }}>
                    <defs>
                        <linearGradient id="colorActive" x1="0" y1="0" x2="0" y2="1">
                            <stop offset="5%" stopColor="#dc2626" stopOpacity={0.4}/>
                            <stop offset="95%" stopColor="#dc2626" stopOpacity={0}/>
                        </linearGradient>
                    </defs>
                    <CartesianGrid strokeDasharray="3 3" vertical={false} stroke="#333" opacity={0.1} />
                    <XAxis 
                        dataKey="name" 
                        tick={{fontSize: 10, fill: '#666', fontWeight: 'bold'}} 
                        axisLine={false} 
                        tickLine={false} 
                        dy={10}
                        minTickGap={10}
                        interval="preserveStartEnd"
                    />
                    <YAxis 
                        tick={{fontSize: 10, fill: '#666'}} 
                        axisLine={false} 
                        tickLine={false} 
                    />
                    <Tooltip 
                        contentStyle={{ 
                            backgroundColor: 'rgba(18, 18, 18, 0.95)', 
                            borderColor: 'rgba(255,255,255,0.1)', 
                            color: '#fff', 
                            fontSize: '12px',
                            borderRadius: '8px',
                            padding: '8px',
                            boxShadow: '0 4px 6px -1px rgba(0, 0, 0, 0.5)'
                        }} 
                        itemStyle={{ color: '#fff', fontWeight: 'bold', fontSize: '12px' }}
                        cursor={{ stroke: '#dc2626', strokeWidth: 1, strokeDasharray: '4 4' }}
                    />
                    <Area 
                        type="monotone" 
                        dataKey="active" 
                        name="Player Online"
                        stroke="#dc2626" 
                        strokeWidth={3} 
                        fillOpacity={1} 
                        fill="url(#colorActive)" 
                        activeDot={{ r: 6, strokeWidth: 2, stroke: '#fff', fill: '#dc2626' }}
                        animationDuration={500}
                    />
                </AreaChart>
            </ResponsiveContainer>
         </div>
    </div>
  );
};
