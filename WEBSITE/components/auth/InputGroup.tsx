
import React, { useState } from 'react';
import { LucideIcon, AlertCircle, Eye, EyeOff } from 'lucide-react';

interface InputGroupProps extends React.InputHTMLAttributes<HTMLInputElement> {
    icon: LucideIcon;
    error?: string;
}

export const InputGroup: React.FC<InputGroupProps> = ({ icon: Icon, error, type, ...props }) => {
    const [showPassword, setShowPassword] = useState(false);
    const isPassword = type === 'password';
    const inputType = isPassword ? (showPassword ? 'text' : 'password') : type;

    return (
        <div className="relative group">
            <div className="relative">
                <Icon className={`absolute left-4 top-1/2 transform -translate-y-1/2 transition-colors ${error ? 'text-red-500' : 'text-gray-500 group-focus-within:text-red-500'}`} size={20} />
                <input 
                    type={inputType}
                    className={`w-full bg-white dark:bg-black/40 border rounded-xl pl-12 pr-12 py-4 text-gray-900 dark:text-white placeholder-gray-400 dark:placeholder-gray-600 focus:outline-none transition-all text-base md:text-sm font-medium
                        ${error 
                            ? 'border-red-500 focus:bg-gray-50 dark:focus:bg-black/60 placeholder-red-500/50' 
                            : 'border-gray-200 dark:border-white/10 focus:border-red-500/50 focus:bg-gray-50 dark:focus:bg-black/60'
                        }
                    `}
                    {...props}
                />
                
                {/* Password Toggle */}
                {isPassword && (
                    <button 
                        type="button"
                        onClick={() => setShowPassword(!showPassword)}
                        className="absolute right-4 top-1/2 transform -translate-y-1/2 text-gray-400 hover:text-gray-700 dark:text-gray-500 dark:hover:text-white transition-colors"
                    >
                        {showPassword ? <EyeOff size={20} /> : <Eye size={20} />}
                    </button>
                )}
                
                {/* Error Icon (if not password) */}
                {error && !isPassword && (
                    <div className="absolute right-4 top-1/2 transform -translate-y-1/2 text-red-500">
                        <AlertCircle size={20} />
                    </div>
                )}
            </div>
            {error && (
                <p className="text-[10px] text-red-400 mt-1.5 ml-1 font-bold animate-[slideInDown_0.2s_ease-out] flex items-center gap-1">
                    <span className="w-1 h-1 bg-red-400 rounded-full inline-block"></span>
                    {error}
                </p>
            )}
        </div>
    );
};
