
import React, { useState } from 'react';
import { Clock, AlertCircle, ChevronLeft, ChevronRight } from 'lucide-react';
import { Ticket } from './types';
import { formatTime, getStatusColor } from './utils';

interface TicketListProps {
  tickets: Ticket[];
  selectedTicketId: number | undefined;
  onSelectTicket: (ticket: Ticket) => void;
  isAdmin: boolean;
  isHiddenOnMobile: boolean;
}

export const TicketList: React.FC<TicketListProps> = ({ tickets, selectedTicketId, onSelectTicket, isAdmin, isHiddenOnMobile }) => {
  const [currentPage, setCurrentPage] = useState(1);
  const itemsPerPage = 7;
  const totalPages = Math.ceil(tickets.length / itemsPerPage);
  
  const currentTickets = tickets.slice(
      (currentPage - 1) * itemsPerPage,
      currentPage * itemsPerPage
  );

  return (
    <div className={`${isHiddenOnMobile ? 'hidden md:flex' : 'flex'} w-full flex-1 h-full flex-col bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-2xl overflow-hidden shadow-sm`}>
        <div className="p-5 bg-gray-50 dark:bg-[#1a1a1a] border-b border-gray-200 dark:border-white/5 font-black text-gray-400 dark:text-gray-500 uppercase text-[10px] tracking-widest flex items-center flex-shrink-0">
            <Clock size={14} className="mr-2" /> {isAdmin ? 'Inbox Tiket' : 'Riwayat Tiket'}
        </div>
        <div className="flex-1 overflow-y-auto p-3 space-y-2 custom-scrollbar">
            {tickets.length === 0 ? (
                <div className="text-center py-20 text-gray-500">
                    <Clock size={48} className="mx-auto mb-3 opacity-30" />
                    <p className="text-xs uppercase font-bold opacity-70">Belum ada tiket.</p>
                </div>
            ) : (
                currentTickets.map(ticket => (
                    <div 
                        key={ticket.id}
                        onClick={() => onSelectTicket(ticket)}
                        className={`p-4 md:p-3.5 rounded-xl cursor-pointer border transition-all relative group active:scale-[0.98] ${selectedTicketId === ticket.id ? 'bg-red-50 dark:bg-red-900/10 border-red-500/50 shadow-sm' : 'bg-white dark:bg-[#0a0a0a] border-gray-100 dark:border-white/5 hover:border-red-500/30 hover:bg-gray-50 dark:hover:bg-[#111]'}`}
                    >
                        <div className="flex justify-between items-start mb-2">
                            <span className={`text-[9px] md:text-[10px] font-bold px-2 py-0.5 rounded border uppercase tracking-wider ${getStatusColor(ticket.status)}`}>{ticket.status}</span>
                            <span className="text-[10px] text-gray-400 font-mono mt-0.5">{formatTime(ticket.lastUpdate)}</span>
                        </div>
                        <h4 className={`font-bold text-sm md:text-base truncate mb-1.5 ${selectedTicketId === ticket.id ? 'text-red-600 dark:text-red-400' : 'text-gray-800 dark:text-gray-200'}`}>{ticket.subject}</h4>
                        <div className="flex items-center text-[10px] md:text-[11px] text-gray-500 uppercase tracking-wide font-medium">
                            <AlertCircle size={12} className="mr-1.5" /> {ticket.category}
                        </div>
                    </div>
                ))
            )}
        </div>
        {totalPages > 1 && (
            <div className="flex items-center justify-between px-4 py-3 border-t border-gray-200 dark:border-white/5 bg-gray-100/50 dark:bg-[#111]/50">
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
