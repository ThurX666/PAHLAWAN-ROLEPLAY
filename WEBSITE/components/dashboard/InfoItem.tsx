
import React from 'react';
import { LucideIcon } from 'lucide-react';

interface InfoItemProps {
    icon: LucideIcon;
    label: string;
    value: string;
    color?: string;
    rightElement?: React.ReactNode;
}

export const InfoItem: React.FC<InfoItemProps> = ({ icon: Icon, label, value, color, rightElement }) => (
    // ==================================================================================
    // 🎓 PANDUAN INTEGRASI PHP & MYSQL (GURU MODE)
    // ==================================================================================
    //
    // Komponen ini adalah "UI Component" murni untuk menampilkan baris informasi.
    // Anda TIDAK PERLU melakukan fetch API di sini.
    //
    // Komponen ini menerima data melalui 'props' (label, value) 
    // yang dikirim dari AccountInfo.tsx.
    //
    // Jika Anda ingin mengubah datanya, lakukan perubahan di AccountInfo.tsx.
    // ==================================================================================
    <div className="flex items-center p-2 md:p-3 rounded-lg md:rounded-xl bg-gray-50 dark:bg-white/5 border border-gray-100 dark:border-white/5 hover:border-gray-200 dark:hover:border-white/10 transition-colors group">
        <div className="p-1.5 md:p-2 bg-white dark:bg-black/30 rounded md:rounded-lg mr-2 md:mr-3 text-gray-400 group-hover:text-red-500 transition-colors shadow-sm shrink-0">
            <Icon className="w-3.5 h-3.5 md:w-4 md:h-4" />
        </div>
        <div className="overflow-hidden min-w-0 flex-1">
            <p className="text-[9px] md:text-[10px] font-bold uppercase text-gray-500 dark:text-gray-400 tracking-wider truncate mb-0 md:mb-0.5">{label}</p>
            <p className={`font-mono text-xs md:text-sm font-bold break-all whitespace-pre-line ${color ? color : 'text-gray-900 dark:text-white'}`}>{value}</p>
        </div>
        {rightElement && (
            <div className="ml-2 shrink-0">
                {rightElement}
            </div>
        )}
    </div>
);
