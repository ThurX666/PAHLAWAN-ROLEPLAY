
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
                <Icon
                    className={`absolute left-3.5 top-1/2 transform -translate-y-1/2 transition-colors duration-200 z-10 ${
                        error
                            ? 'text-ph-crimson-700'
                            : 'text-gray-400 group-focus-within:text-ph-crimson-700'
                    }`}
                    size={17}
                />
                <input
                    type={inputType}
                    className={`ph-input-focus w-full bg-[#fbfaf8] border rounded-lg pl-11 pr-11 py-3.5 text-gray-900 placeholder-gray-400 transition-all duration-200 text-sm font-medium shadow-sm
                        ${error
                            ? 'border-ph-crimson-600/60 bg-ph-crimson-600/[0.04] shadow-[0_0_0_3px_rgba(215,25,32,0.08)]'
                            : 'border-gray-200 hover:border-gray-300'
                        }
                    `}
                    {...props}
                />

                {/* Password Toggle */}
                {isPassword && (
                    <button
                        type="button"
                        onClick={() => setShowPassword(!showPassword)}
                        className="absolute right-2 top-1/2 flex h-10 w-10 transform -translate-y-1/2 items-center justify-center text-gray-400 hover:text-ph-crimson-700 transition-colors duration-200 rounded-md hover:bg-ph-crimson-600/[0.06] z-10"
                        tabIndex={-1}
                        aria-label={showPassword ? 'Sembunyikan password' : 'Tampilkan password'}
                    >
                        {showPassword ? <EyeOff size={17} /> : <Eye size={17} />}
                    </button>
                )}

                {/* Error Icon (if not password) */}
                {error && !isPassword && (
                    <div className="absolute right-3 top-1/2 transform -translate-y-1/2 text-ph-crimson-700 z-10">
                        <AlertCircle size={17} />
                    </div>
                )}
            </div>
            {error && (
                <p className="text-[11px] text-ph-crimson-700 mt-1.5 ml-1 font-semibold animate-auth-slide-down flex items-center gap-1.5">
                    <span className="w-1 h-1 bg-ph-crimson-700 rounded-full inline-block shrink-0"></span>
                    {error}
                </p>
            )}
        </div>
    );
};
