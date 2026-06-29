
import React from 'react';
import { LucideIcon } from 'lucide-react';

interface StatCardProps {
    title: string;
    value: string;
    icon: LucideIcon;
    color: string;
    subValue: React.ReactNode;
    isCurrency?: boolean;
}

export const StatCard: React.FC<StatCardProps> = ({ title, value, icon: Icon, color, subValue, isCurrency }) => {
    // Extract the 'to' color from the gradient for the hover border
    const hoverBorderColor = color.split(' ').find(c => c.startsWith('to-'))?.replace('to-', 'hover:border-') || 'hover:border-gray-300 dark:hover:border-gray-600';

    return (
        // ==================================================================================
        // 🎓 PANDUAN INTEGRASI PHP & MYSQL (GURU MODE)
        // ==================================================================================
        //
        // Komponen ini adalah "UI Component" murni.
        // Anda TIDAK PERLU melakukan fetch API di sini.
        //
        // Komponen ini menerima data melalui 'props' (title, value, subValue) 
        // yang dikirim dari StatsGrid.tsx.
        //
        // Jika Anda ingin mengubah datanya, lakukan perubahan di StatsGrid.tsx.
        // ==================================================================================
        <div className={`relative group rounded-xl md:rounded-2xl bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 shadow-sm md:shadow-lg overflow-hidden transition-all duration-300 hover:scale-[1.02] hover:shadow-md p-3 md:p-6 flex flex-col justify-between min-h-[100px] md:min-h-[140px] ${hoverBorderColor}`}>
            <div className="absolute top-0 right-0 p-2 md:p-3 opacity-5 pointer-events-none transform group-hover:scale-110 transition-transform duration-500">
                <Icon className="w-10 h-10 md:w-16 md:h-16" />
            </div>
            <div className="relative z-10">
                <div className="flex items-center gap-1.5 md:gap-2 mb-1.5 md:mb-2">
                    <div className={`p-1 md:p-1.5 rounded-md md:rounded-lg bg-gradient-to-br ${color} text-white`}>
                        <Icon className="w-3 h-3 md:w-4 md:h-4" />
                    </div>
                    <p className="text-[9px] md:text-xs font-bold text-gray-500 dark:text-gray-400 uppercase tracking-widest truncate">{title}</p>
                </div>
                <h3 className={`text-base md:text-2xl font-black text-gray-900 dark:text-white uppercase italic truncate leading-tight ${isCurrency ? 'font-mono tracking-tight' : ''}`}>
                    {value}
                </h3>
                <div className="text-[9px] md:text-xs text-gray-400 mt-2 md:mt-3 pt-1 md:pt-2 border-t border-gray-100 dark:border-white/5 truncate font-medium">
                    {subValue}
                </div>
            </div>
        </div>
    );
};
