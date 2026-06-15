
import React from 'react';
import { LucideIcon, AlertCircle } from 'lucide-react';

interface InputGroupProps extends React.InputHTMLAttributes<HTMLInputElement> {
    label: string;
    icon: LucideIcon;
    error?: string;
}

export const InputGroup: React.FC<InputGroupProps> = ({ label, icon: Icon, error, type = "text", className, ...props }) => (
    <div className={className}>
        <div className="flex justify-between items-center mb-1.5 ml-1">
            <label className={`block text-[10px] md:text-xs font-bold uppercase transition-colors ${error ? 'text-red-500' : 'text-gray-500'}`}>
                {label}
            </label>
            {error && (
                <span className="text-[9px] font-bold text-red-500 flex items-center gap-1 animate-[fadeIn_0.2s_ease-out]">
                    {error}
                </span>
            )}
        </div>
        <div className="relative group">
            <Icon className={`absolute left-4 top-1/2 -translate-y-1/2 transition-colors ${error ? 'text-red-500' : 'text-gray-400 dark:text-gray-500 group-focus-within:text-red-500'}`} size={18} />
            <input 
                type={type}
                className={`w-full bg-gray-50 dark:bg-black/20 border rounded-xl pl-12 pr-10 py-3 md:py-3.5 text-gray-900 dark:text-white text-xs md:text-sm placeholder-gray-400 dark:placeholder-gray-600 outline-none transition-all dark:[color-scheme:dark]
                    ${error 
                        ? 'border-red-500 focus:border-red-600 focus:ring-1 focus:ring-red-500/20 bg-red-50/10 dark:bg-red-900/10' 
                        : 'border-gray-200 dark:border-white/10 focus:border-red-500 focus:bg-white dark:focus:bg-black/40'
                    }
                `}
                {...props}
            />
            {error ? (
                <div className="absolute right-3 top-1/2 -translate-y-1/2 text-red-500 animate-pulse">
                    <AlertCircle size={18} />
                </div>
            ) : (
                // Optional: Success state indicator or just empty
                null 
            )}
        </div>
    </div>
);
