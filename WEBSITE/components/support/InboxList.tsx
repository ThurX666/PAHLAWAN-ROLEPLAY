
import React, { useState } from 'react';
import { Inbox, Tag, AlertCircle, ChevronLeft, ChevronRight, Loader2 } from 'lucide-react';
import { InboxMessage } from '../../types';
import { formatTime } from './utils';

interface InboxListProps {
  messages: InboxMessage[];
  selectedMessageId: string | undefined;
  onSelectMessage: (msg: InboxMessage) => void;
  isHiddenOnMobile: boolean;
  isLoading?: boolean;
}

export const InboxList: React.FC<InboxListProps> = ({ messages, selectedMessageId, onSelectMessage, isHiddenOnMobile, isLoading }) => {
  const [currentPage, setCurrentPage] = useState(1);
  const itemsPerPage = 7;
  const totalPages = Math.ceil(messages.length / itemsPerPage);
  
  const currentMessages = messages.slice(
      (currentPage - 1) * itemsPerPage,
      currentPage * itemsPerPage
  );

  return (
    <div className={`${isHiddenOnMobile ? 'hidden md:flex' : 'flex'} w-full flex-1 h-full flex-col bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-2xl overflow-hidden shadow-sm`}>
        <div className="p-5 bg-gray-50 dark:bg-ph-surface-panel border-b border-gray-200 dark:border-white/5 font-black text-gray-400 dark:text-gray-500 uppercase text-[10px] tracking-widest flex items-center justify-between flex-shrink-0">
            <div className="flex items-center">
                <Inbox size={14} className="mr-2" /> Daftar Pesan
            </div>
            {isLoading && <Loader2 size={14} className="animate-spin text-gray-400" />}
        </div>
        <div className="flex-1 overflow-y-auto p-3 space-y-2 custom-scrollbar">
            {isLoading && messages.length === 0 ? (
                <div className="text-center py-20 text-gray-500 flex flex-col items-center justify-center">
                    <Loader2 size={32} className="animate-spin mb-3 text-red-500" />
                    <p className="text-xs uppercase font-bold opacity-70">Memuat Pesan...</p>
                </div>
            ) : messages.length === 0 ? (
                <div className="text-center py-20 text-gray-500">
                    <Inbox size={48} className="mx-auto mb-3 opacity-30" />
                    <p className="text-xs uppercase font-bold opacity-70">Inbox kosong.</p>
                </div>
            ) : (
                currentMessages.map(msg => (
                    <div 
                        key={msg.id} 
                        onClick={() => onSelectMessage(msg)}
                        className={`p-4 md:p-3.5 rounded-xl cursor-pointer border transition-all relative group hover:shadow-md active:scale-[0.98] ${
                            selectedMessageId === msg.id 
                            ? 'bg-red-50 dark:bg-red-900/10 border-red-500/50 shadow-sm' 
                            : msg.read 
                                ? 'bg-white dark:bg-ph-surface-deep border-gray-100 dark:border-white/5 hover:border-red-500/30 hover:bg-gray-50 dark:hover:bg-[#111]' 
                                : 'bg-white dark:bg-ph-surface-panel border-gray-200 dark:border-white/10 shadow-sm'
                        }`}
                    >
                        {!msg.read && (
                            <div className="absolute top-4 right-4 w-2.5 h-2.5 bg-red-500 rounded-full animate-pulse shadow-[0_0_8px_rgba(239,68,68,0.6)]"></div>
                        )}
                        <div className="flex justify-between items-start mb-2">
                            <div className="flex items-center gap-2">
                                <span className={`p-1.5 rounded-lg ${msg.type === 'Voucher' ? 'bg-green-100 text-green-600' : 'bg-blue-100 text-blue-600'}`}>
                                    {msg.type === 'Voucher' ? <Tag size={12} /> : <AlertCircle size={12} />}
                                </span>
                                <span className={`text-[10px] md:text-[11px] uppercase font-bold tracking-wide ${!msg.read ? 'text-gray-900 dark:text-white' : 'text-gray-500'}`}>
                                    {msg.type}
                                </span>
                            </div>
                            <span className="text-[10px] text-gray-400 font-mono mt-0.5">{formatTime(msg.date)}</span>
                        </div>
                        <h4 className={`text-sm md:text-base whitespace-pre-wrap mb-1 ${!msg.read ? 'font-black text-gray-900 dark:text-white' : 'font-bold text-gray-600 dark:text-gray-400'} ${selectedMessageId === msg.id ? 'text-red-600 dark:text-red-400' : ''}`}>
                            {msg.title}
                        </h4>
                        <p className="text-[11px] md:text-xs text-gray-500 truncate font-medium">
                            {msg.message ? String(msg.message).replace(/<[^>]+>/g, ' ') : ''}
                        </p>
                    </div>
                ))
            )}
        </div>
        {totalPages > 1 && (
            <div className="flex items-center justify-between px-4 py-3 border-t border-gray-200 dark:border-white/5 bg-gray-100/50 dark:bg-ph-surface-deep/50">
                <button 
                    onClick={() => setCurrentPage(prev => Math.max(prev - 1, 1))}
                    disabled={currentPage === 1}
                    className="p-1.5 rounded-md text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10 disabled:opacity-30 disabled:cursor-not-allowed transition-colors"
                >
                    <ChevronLeft size={18} />
                </button>
                <span className="text-[10px] md:text-xs font-bold text-gray-500 uppercase tracking-wider">
                    Halaman {currentPage} dari {totalPages}
                </span>
                <button 
                    onClick={() => setCurrentPage(prev => Math.min(prev + 1, totalPages))}
                    disabled={currentPage === totalPages}
                    className="p-1.5 rounded-md text-gray-600 dark:text-gray-400 hover:bg-gray-200 dark:hover:bg-white/10 disabled:opacity-30 disabled:cursor-not-allowed transition-colors"
                >
                    <ChevronRight size={18} />
                </button>
            </div>
        )}
    </div>
  );
};
