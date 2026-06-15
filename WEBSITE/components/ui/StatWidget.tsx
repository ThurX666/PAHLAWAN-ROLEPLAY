
import React from 'react';

export const StatWidget = ({ icon: Icon, label, value, color, className = '' }: any) => (
    <div className={`bg-white dark:bg-[#121212] border border-gray-100 dark:border-white/5 p-3.5 rounded-2xl flex items-center justify-between shadow-sm hover:shadow-lg hover:-translate-y-1 transition-all duration-300 group ${className}`}>
        <div>
            <p className="text-gray-400 text-[9px] uppercase font-bold tracking-widest mb-1">{label}</p>
            <p className="text-2xl font-black text-gray-900 dark:text-white tracking-tight">{value}</p>
        </div>
        <div className={`p-2.5 rounded-xl bg-gray-50 dark:bg-white/5 ${color} group-hover:scale-110 transition-transform duration-300`}>
            <Icon size={20} />
        </div>
    </div>
);

export const AssetStatWidget = ({ icon: Icon, label, value, color, onClick }: any) => (
    <button onClick={onClick} className="bg-white dark:bg-[#121212] border border-gray-100 dark:border-white/5 p-4 rounded-2xl flex flex-col items-center justify-center text-center shadow-sm hover:shadow-md hover:-translate-y-1 hover:border-gray-200 dark:hover:border-white/10 transition-all duration-300 group h-full w-full">
        <div className={`p-3 rounded-full bg-gray-50 dark:bg-white/5 mb-3 group-hover:bg-gray-100 dark:group-hover:bg-white/10 transition-colors`}>
            <Icon size={20} className={`${color} group-hover:scale-110 transition-transform duration-300`} />
        </div>
        <p className="text-2xl font-black text-gray-900 dark:text-white leading-none mb-1 tracking-tight">{value}</p>
        <p className="text-gray-400 text-[9px] uppercase font-bold tracking-widest">{label}</p>
    </button>
);
