
import React, { useState } from 'react';
import { User, Lock, ArrowRight, Loader2 } from 'lucide-react';
import { InputGroup } from './InputGroup';

interface LoginFormProps {
    onSubmit: (username: string, password?: string) => void;
    setView: (view: 'login' | 'register' | 'forgot') => void;
    loading: boolean;
}

export const LoginForm: React.FC<LoginFormProps> = ({ onSubmit, setView, loading }) => {
    const [identifier, setIdentifier] = useState('');
    const [password, setPassword] = useState('');
    const [errors, setErrors] = useState({ identifier: '', password: '' });

    const validate = () => {
        const newErrors = { identifier: '', password: '' };
        let isValid = true;

        if(!identifier.trim()) { newErrors.identifier = 'Username/Email required'; isValid = false; }
        if(!password.trim()) { newErrors.password = 'Password required'; isValid = false; }

        setErrors(newErrors);
        return isValid;
    };

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        if(validate()) {
            onSubmit(identifier, password);
        }
    };

    return (
        <div className="animate-[fadeIn_0.3s_ease-out]">
            <div className="text-center mb-8">
               <h2 className="text-3xl font-black text-gray-900 dark:text-white mb-2 uppercase italic tracking-tighter">
                 Welcome Back
               </h2>
               <p className="text-gray-500 text-xs uppercase tracking-widest font-bold">
                 User Control Panel Access
               </p>
            </div>

            <form onSubmit={handleSubmit} className="space-y-4" noValidate>
                <InputGroup 
                    icon={User} 
                    type="text" 
                    placeholder="Username / Email" 
                    autoComplete="username"
                    value={identifier} 
                    onChange={e => {
                        setIdentifier(e.target.value);
                        if(errors.identifier) setErrors(prev => ({...prev, identifier: ''}));
                    }}
                    error={errors.identifier}
                />
                
                <InputGroup 
                    icon={Lock} 
                    type="password" 
                    placeholder="Password"
                    autoComplete="current-password"
                    value={password}
                    onChange={e => {
                        setPassword(e.target.value);
                        if(errors.password) setErrors(prev => ({...prev, password: ''}));
                    }}
                    error={errors.password}
                />

                <div className="flex justify-end mt-2 mb-6">
                    <button 
                        type="button" 
                        onClick={() => setView('forgot')} 
                        className="text-xs text-gray-500 dark:text-gray-400 hover:text-gray-900 dark:hover:text-white transition-colors font-medium"
                    >
                        Forgot Password?
                    </button>
                </div>

                <button 
                    type="submit" 
                    disabled={loading}
                    className="w-full bg-gradient-to-r from-red-600 to-red-700 hover:from-red-500 hover:to-red-600 text-white font-bold py-4 rounded-xl transition-all transform hover:scale-[1.02] active:scale-[0.98] shadow-lg shadow-red-600/20 disabled:opacity-70 disabled:cursor-not-allowed flex items-center justify-center group"
                >
                    {loading ? <Loader2 className="animate-spin" size={20} /> : (
                        <span className="flex items-center text-sm uppercase tracking-widest">
                            Login to UCP 
                            <ArrowRight size={16} className="ml-2 group-hover:translate-x-1 transition-transform" />
                        </span>
                    )}
                </button>
            </form>

            <div className="mt-8 text-center">
                <p className="text-gray-600 dark:text-gray-400 text-sm">
                    New to the city?{' '}
                    <button 
                        onClick={() => setView('register')} 
                        type="button"
                        className="text-gray-900 dark:text-white font-bold hover:text-red-600 dark:hover:text-red-500 transition-colors"
                    >
                        Create Account
                    </button>
                </p>
            </div>
        </div>
    );
};
