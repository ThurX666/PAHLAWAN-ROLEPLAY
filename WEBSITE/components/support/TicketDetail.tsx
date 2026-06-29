
import React, { useRef, useEffect } from 'react';
import { XCircle, Send, ChevronLeft, CheckCircle, Clock, RefreshCw } from 'lucide-react';
import { Ticket } from './types';
import { formatTime } from './utils';

interface TicketDetailProps {
  ticket: Ticket;
  isAdmin: boolean;
  onClose: () => void;
  onReply: (e: React.FormEvent) => void;
  replyMessage: string;
  setReplyMessage: (msg: string) => void;
  onUpdateStatus?: (status: Ticket['status']) => void;
}

export const TicketDetail: React.FC<TicketDetailProps> = ({ ticket, isAdmin, onClose, onReply, replyMessage, setReplyMessage, onUpdateStatus }) => {
  const messagesEndRef = useRef<HTMLDivElement>(null);

  const scrollToBottom = () => {
    messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
  };

  useEffect(() => {
    scrollToBottom();
  }, [ticket.messages]);

  return (
    <div className="flex flex-col h-full animate-[fadeIn_0.3s_ease-out] bg-white dark:bg-ph-surface-card">
        <div className="p-4 md:p-5 border-b border-gray-200 dark:border-white/5 flex items-center bg-gray-50 dark:bg-ph-surface-panel sticky top-0 z-10">
            <button onClick={onClose} className="md:hidden text-gray-500 hover:text-red-500 p-2 -ml-2 mr-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors active:scale-95">
                <ChevronLeft size={24} />
            </button>
            <div className="flex-1 min-w-0 mr-2">
                <div className="flex items-center gap-2">
                    <h3 className="font-black text-gray-900 dark:text-white text-sm md:text-base italic uppercase truncate">{ticket.subject}</h3>
                    <span className={`text-[10px] font-bold px-2 py-0.5 rounded-full ${
                        ticket.status === 'Open' ? 'bg-amber-100 text-amber-600 dark:bg-amber-500/20 dark:text-amber-400' :
                        ticket.status === 'Proses' ? 'bg-blue-100 text-blue-600 dark:bg-blue-500/20 dark:text-blue-400' :
                        ticket.status === 'Dijawab' ? 'bg-green-100 text-green-600 dark:bg-green-500/20 dark:text-green-400' :
                        'bg-gray-100 text-gray-600 dark:bg-white/10 dark:text-gray-400'
                    }`}>
                        {ticket.status}
                    </span>
                </div>
                <span className="text-[9px] md:text-[10px] text-gray-500 uppercase">#{ticket.id}</span>
            </div>
            <button onClick={onClose} className="hidden md:block text-gray-500 p-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors"><XCircle size={24} /></button>
        </div>

        <div className="flex-1 overflow-y-auto p-4 space-y-4 bg-white dark:bg-ph-surface-deep custom-scrollbar">
            {ticket.messages.map((msg, idx) => {
                const isMe = isAdmin ? msg.sender === 'Admin' : msg.sender !== 'Admin';
                return (
                    <div key={idx} className={`flex ${isMe ? 'justify-end' : 'justify-start'}`}>
                        <div className={`max-w-[85%] md:max-w-[75%] rounded-2xl p-3 md:p-4 shadow-sm relative ${isMe ? 'bg-red-600 text-white rounded-tr-sm' : 'bg-gray-100 dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 rounded-tl-sm'}`}>
                            <div className="flex justify-between items-center mb-1.5 gap-3">
                                <span className={`text-[10px] font-bold uppercase ${isMe ? 'text-white/80' : 'text-red-500'}`}>{msg.sender}</span>
                                <span className={`text-[9px] ${isMe ? 'text-white/60' : 'text-gray-500'}`}>{formatTime(msg.time)}</span>
                            </div>
                            <p className={`text-xs md:text-sm leading-relaxed ${isMe ? 'text-white' : 'text-gray-800 dark:text-gray-300'}`}>{msg.text}</p>
                        </div>
                    </div>
                );
            })}
            <div ref={messagesEndRef} />
        </div>

        <div className="p-3 md:p-6 bg-gray-50 dark:bg-ph-surface-input border-t border-gray-200 dark:border-white/5 pb-[calc(12px+env(safe-area-inset-bottom))] md:pb-[calc(24px+env(safe-area-inset-bottom))]">
            {isAdmin && onUpdateStatus && (
                <div className="flex flex-wrap gap-2 mb-3">
                    {ticket.status !== 'Proses' && ticket.status !== 'Ditutup' && (
                        <button 
                            onClick={() => onUpdateStatus('Proses')}
                            className="flex items-center gap-1.5 px-3 py-1.5 bg-blue-100 text-blue-600 dark:bg-blue-500/20 dark:text-blue-400 hover:bg-blue-200 dark:hover:bg-blue-500/30 rounded-lg text-xs font-bold transition-colors"
                        >
                            <Clock size={14} />
                            Proses Tiket
                        </button>
                    )}
                    {ticket.status !== 'Ditutup' && (
                        <button 
                            onClick={() => onUpdateStatus('Ditutup')}
                            className="flex items-center gap-1.5 px-3 py-1.5 bg-gray-200 text-gray-700 dark:bg-white/10 dark:text-gray-300 hover:bg-gray-300 dark:hover:bg-white/20 rounded-lg text-xs font-bold transition-colors"
                        >
                            <CheckCircle size={14} />
                            Tutup Tiket
                        </button>
                    )}
                    {ticket.status === 'Ditutup' && (
                        <button 
                            onClick={() => onUpdateStatus('Open')}
                            className="flex items-center gap-1.5 px-3 py-1.5 bg-amber-100 text-amber-600 dark:bg-amber-500/20 dark:text-amber-400 hover:bg-amber-200 dark:hover:bg-amber-500/30 rounded-lg text-xs font-bold transition-colors"
                        >
                            <RefreshCw size={14} />
                            Buka Kembali
                        </button>
                    )}
                </div>
            )}
            <form onSubmit={onReply} className="flex gap-2 md:gap-4 items-end">
                <textarea 
                    rows={1}
                    className={`flex-1 bg-white dark:bg-ph-surface-deep border border-gray-200 dark:border-white/10 rounded-2xl md:rounded-xl p-3 md:p-4 focus:border-red-600 outline-none text-gray-900 dark:text-white text-sm resize-none max-h-32 min-h-[44px] md:min-h-[52px] ${ticket.status === 'Ditutup' ? 'opacity-50 cursor-not-allowed' : ''}`}
                    placeholder={ticket.status === 'Ditutup' ? "Tiket telah ditutup..." : "Ketik pesan..."}
                    value={replyMessage}
                    onChange={e => setReplyMessage(e.target.value)}
                    disabled={ticket.status === 'Ditutup'}
                    onKeyDown={(e) => {
                        if (e.key === 'Enter' && !e.shiftKey) {
                            e.preventDefault();
                            if (ticket.status !== 'Ditutup') {
                                onReply(e);
                            }
                        }
                    }}
                />
                <button 
                    type="submit" 
                    disabled={!replyMessage.trim() || ticket.status === 'Ditutup'}
                    className={`p-3 md:p-4 rounded-full md:rounded-xl shadow-lg transition-all flex-shrink-0 flex items-center justify-center ${
                        replyMessage.trim() && ticket.status !== 'Ditutup'
                        ? 'bg-red-600 text-white hover:bg-red-500 active:scale-95' 
                        : 'bg-gray-300 dark:bg-gray-800 text-gray-500 cursor-not-allowed'
                    }`}
                >
                    <Send size={20} className={replyMessage.trim() && ticket.status !== 'Ditutup' ? 'translate-x-0.5' : ''} />
                </button>
            </form>
        </div>
    </div>
  );
};
