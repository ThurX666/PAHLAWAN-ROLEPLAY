
import React, { useState, useEffect, useCallback } from 'react';
import { createPortal } from 'react-dom';
import { LifeBuoy, Mail, MessageSquare, ChevronLeft } from 'lucide-react';
import { InboxMessage } from '../types';
import { Ticket } from './support/types';
import { TicketList } from './support/TicketList';
import { TicketDetail } from './support/TicketDetail';
import { CreateTicketForm } from './support/CreateTicketForm';
import { InboxList } from './support/InboxList';
import { InboxDetail } from './support/InboxDetail';
import { isPreviewEnv, API_URL } from '../config';

interface TicketSystemProps {
    userName: string;
    isAdmin: boolean;
    messages?: InboxMessage[];
    onReadMessage?: (id: string) => void;
    onNavigate?: (tab: string) => void;
    tickets: Ticket[];
    setTickets: React.Dispatch<React.SetStateAction<Ticket[]>>;
    initialTab?: 'tickets' | 'inbox';
    onSendNotification?: (msg: InboxMessage) => void;
}

export const TicketSystem: React.FC<TicketSystemProps> = ({ userName, isAdmin, messages = [], onReadMessage, onNavigate, tickets, setTickets, initialTab = 'inbox', onSendNotification }) => {
    const [activeTab, setActiveTab] = useState<'tickets' | 'inbox'>(initialTab); 
    const [selectedTicket, setSelectedTicket] = useState<Ticket | null>(null);
    const [selectedMessage, setSelectedMessage] = useState<InboxMessage | null>(null); 
    const [isCreating, setIsCreating] = useState(false);
    
    // Internal state for API fetched data
    const [localTickets, setLocalTickets] = useState<Ticket[]>(tickets);
    // Messages are purely driven by props now so badges stay in sync
    const [isLoadingInbox, setIsLoadingInbox] = useState(false);

    const loadTickets = useCallback(async () => {
        if (isPreviewEnv()) return;
        try {
            const res = await fetch(`${API_URL}/api_tickets.php?username=${userName}`);
            const data = await res.json();
            if (data.status === 'success') {
                setLocalTickets(data.data);
                if (setTickets) setTickets(data.data);
            }
        } catch (e) {
            console.error(e);
        }
    }, [userName, setTickets]);

    useEffect(() => {
        if (!isPreviewEnv()) {
            loadTickets();
        }
    }, [userName, loadTickets]);

    useEffect(() => {
        if (isPreviewEnv()) {
            setLocalTickets(tickets);
        }
    }, [tickets]);

    useEffect(() => {
        setActiveTab(initialTab);
    }, [initialTab]);
    
    // Ticket Form State
    const [newMessage, setNewMessage] = useState('');

    // Force re-render every minute to update relative times
    const [, setTick] = useState(0);
    useEffect(() => {
        const timer = setInterval(() => setTick(t => t + 1), 60000);
        return () => clearInterval(timer);
    }, []);

    const handleCreateTicket = async (subject: string, category: string, initialMessage: string) => {
        if (isPreviewEnv()) {
            const now = new Date().toISOString();
            const newTicket: Ticket = {
                id: Math.floor(Math.random() * 10000),
                subject: subject,
                category: category as any,
                status: 'Open',
                lastUpdate: now,
                messages: [{ sender: userName, text: initialMessage, time: now }]
            };
            const newTickets = [newTicket, ...localTickets];
            setLocalTickets(newTickets);
            setTickets(newTickets);
            setIsCreating(false);
            return;
        }

        try {
            const res = await fetch(`${API_URL}/api_tickets.php`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ 
                    action: 'create_ticket', 
                    username: userName, 
                    subject, 
                    category, 
                    initial_message: initialMessage 
                })
            });
            if (res.ok) {
                loadTickets();
                setIsCreating(false);
            }
        } catch (e) {
            console.error(e);
        }
    };

    const handleReply = async (e: React.FormEvent) => {
        e.preventDefault();
        if (!selectedTicket || !newMessage) return;

        const senderName = isAdmin ? 'Admin' : userName;
        const newStatus = isAdmin ? 'Dijawab' : 'Open';

        if (isPreviewEnv()) {
            const now = new Date().toISOString();
            const updatedTicket = {
                ...selectedTicket,
                status: newStatus as Ticket['status'],
                lastUpdate: now,
                messages: [...selectedTicket.messages, { sender: senderName, text: newMessage, time: now }]
            };
            
            const updatedList = localTickets.map(t => t.id === selectedTicket.id ? updatedTicket : t);
            setLocalTickets(updatedList);
            setTickets(updatedList);
            setSelectedTicket(updatedTicket);
            setNewMessage('');
            return;
        }

        try {
            const res = await fetch(`${API_URL}/api_tickets.php`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    action: 'reply_ticket',
                    ticket_id: selectedTicket.id,
                    sender: senderName,
                    text: newMessage,
                    status: newStatus
                })
            });
            if (res.ok) {
                // optimistically update view or simply reload
                loadTickets();
                // To keep selected ticket updated, we fetch it or update locally:
                const now = new Date().toISOString();
                setSelectedTicket({
                    ...selectedTicket,
                    status: newStatus as Ticket['status'],
                    lastUpdate: now,
                    messages: [...selectedTicket.messages, { sender: senderName, text: newMessage, time: now }]
                });
                setNewMessage('');
            }
        } catch (e) {
            console.error(e);
        }
    };

    const handleUpdateStatus = async (status: Ticket['status']) => {
        if (!selectedTicket) return;

        if (isPreviewEnv()) {
            const now = new Date().toISOString();
            const updatedTicket = {
                ...selectedTicket,
                status: status,
                lastUpdate: now
            };
            const updatedList = localTickets.map(t => t.id === selectedTicket.id ? updatedTicket : t);
            setLocalTickets(updatedList);
            setTickets(updatedList);
            setSelectedTicket(updatedTicket);
            
            if ((status === 'Ditutup' || status === 'Resolved') && onSendNotification) {
                 const statusDisplay = status === 'Resolved' ? 'Selesai (Resolved)' : 'Ditutup (Closed)';
                 onSendNotification({
                     id: `msg-ticket-${Date.now()}`,
                     title: `Pemberitahuan: Tiket Bantuan "${selectedTicket.subject}" ${statusDisplay}`,
                     type: 'System',
                     date: new Date().toISOString(),
                     read: false,
                     template: 'TicketClosed',
                     metadata: {
                         ticketId: `#TICKET-${selectedTicket.id}`,
                         ticketTitle: selectedTicket.subject,
                         category: selectedTicket.category,
                         status: statusDisplay
                     }
                 });
            }
            return;
        }

        try {
            const res = await fetch(`${API_URL}/api_tickets.php`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    action: 'update_status',
                    ticket_id: selectedTicket.id,
                    status: status
                })
            });
            if (res.ok) {
                loadTickets();
                setSelectedTicket({
                    ...selectedTicket,
                    status: status,
                    lastUpdate: new Date().toISOString()
                });
            }
        } catch (e) {
            console.error(e);
        }
    };

    const handleSelectMessage = async (msg: InboxMessage) => {
        setSelectedMessage(msg);
        const isUnread = !msg.read || msg.read === '0' || msg.read === 0 || msg.read === false;
        if(isUnread) {
            if (onReadMessage) {
                onReadMessage(msg.id);
            }
        }
    };

    const headerConfig = activeTab === 'inbox' ? {
        title: "KOTAK MASUK",
        icon: Mail,
        description: "Pesan sistem & kode voucher",
        color: "bg-red-600"
    } : {
        title: "TIKET BANTUAN",
        icon: LifeBuoy,
        description: "Layanan bantuan & laporan masalah",
        color: "bg-blue-600"
    };

    const HeaderIcon = headerConfig.icon;

    return (
        <div className="flex flex-col flex-1 animate-[fadeIn_0.3s_ease-out]">
            
            {/* 1. Page Header (Dynamic) */}
            <div className="flex flex-col md:flex-row justify-between items-start md:items-end mb-4 md:mb-6 flex-shrink-0 border-b border-gray-200 dark:border-white/5 md:border-none pb-4 md:pb-0">
                <div className="w-full">
                    <div className="flex items-center gap-3 mb-1 md:mb-2">
                        <div className={`p-2 ${headerConfig.color} rounded-lg shadow-lg shadow-red-600/20`}>
                            <HeaderIcon className="text-white" size={24} />
                        </div>
                        <h2 className="text-xl md:text-4xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter flex items-center gap-2">
                            {headerConfig.title}
                        </h2>
                    </div>
                    <p className="text-xs md:text-sm text-gray-500 dark:text-gray-400 font-medium max-w-lg leading-relaxed">
                        {headerConfig.description}
                    </p>
                </div>
            </div>

            {/* 2. Main Content Area */}
            <div className="flex-1 flex flex-col md:flex-row gap-4 md:gap-8 lg:gap-10 overflow-hidden h-full md:px-0">
                {activeTab === 'tickets' && (
                    <>
                    <div className="w-full md:w-[350px] lg:w-[400px] flex-shrink-0 h-full flex flex-col gap-4">
                        {/* Tabs (Moved here) */}
                        <div className="flex gap-3">
                            <button 
                                onClick={() => setActiveTab('inbox')}
                                className={`flex-1 py-3 rounded-xl text-xs font-bold uppercase tracking-wider transition-all flex items-center justify-center gap-2 border ${
                                    activeTab === 'inbox' 
                                    ? 'bg-red-600 text-white border-red-600 shadow-lg shadow-red-600/20' 
                                    : 'bg-white dark:bg-ph-surface-card text-gray-500 border-gray-200 dark:border-white/10 hover:border-red-500/50'
                                }`}
                            >
                                <Mail size={16} /> PESAN
                                {messages.filter(m => !m.read || m.read === '0' || m.read === 0 || m.read === false).length > 0 && (
                                    <span className={`ml-1 px-1.5 py-0.5 rounded-md text-[9px] font-black min-w-[18px] text-center ${activeTab === 'inbox' ? 'bg-white text-red-600' : 'bg-red-500 text-white'}`}>{messages.filter(m => !m.read || m.read === '0' || m.read === 0 || m.read === false).length}</span>
                                )}
                            </button>
                            <button 
                                onClick={() => setActiveTab('tickets')}
                                className={`flex-1 py-3 rounded-xl text-xs font-bold uppercase tracking-wider transition-all flex items-center justify-center gap-2 border ${
                                    activeTab === 'tickets' 
                                    ? 'bg-blue-600 text-white border-blue-600 shadow-lg shadow-blue-600/20' 
                                    : 'bg-white dark:bg-ph-surface-card text-gray-500 border-gray-200 dark:border-white/10 hover:border-blue-500/50'
                                }`}
                            >
                                <LifeBuoy size={16} /> TIKET
                            </button>
                        </div>

                        <div className="flex-1 min-h-0 flex flex-col">
                            <TicketList 
                                tickets={localTickets} 
                                selectedTicketId={selectedTicket?.id} 
                                onSelectTicket={(ticket) => { setSelectedTicket(ticket); setIsCreating(false); }}
                                isAdmin={isAdmin}
                                isHiddenOnMobile={!!selectedTicket || isCreating}
                            />
                        </div>
                        
                        {/* Create Button (Desktop) */}
                        {!isCreating && !selectedTicket && !isAdmin && (
                             <button 
                                onClick={() => setIsCreating(true)}
                                className="hidden md:flex w-full py-3 bg-blue-600 hover:bg-blue-700 text-white font-bold uppercase tracking-wider text-xs rounded-xl shadow-lg shadow-blue-600/20 transition-all active:scale-95 items-center justify-center gap-2"
                             >
                                <LifeBuoy size={16} /> Buat Tiket Baru
                             </button>
                        )}
                    </div>

                    <div className={`hidden md:flex flex-1 min-w-0 bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-2xl shadow-sm flex-col overflow-hidden relative transition-all ${!selectedTicket && !isCreating ? 'items-center justify-center' : ''}`}>
                        
                        {!selectedTicket && !isCreating && (
                            <div className="text-center p-8 opacity-50 select-none">
                                <div className="w-24 h-24 bg-gray-100 dark:bg-white/5 rounded-full flex items-center justify-center mx-auto mb-6">
                                    <LifeBuoy size={48} className="text-gray-400" />
                                </div>
                                <h3 className="text-xl font-black text-gray-300 dark:text-gray-600 uppercase tracking-widest">Pilih Tiket</h3>
                                <p className="text-sm text-gray-400 mt-2 max-w-xs mx-auto">Pilih tiket dari daftar di sebelah kiri untuk melihat detail percakapan.</p>
                            </div>
                        )}
                        
                        {isCreating && (
                            <CreateTicketForm 
                                onClose={() => setIsCreating(false)} 
                                onSubmit={handleCreateTicket} 
                            />
                        )}

                        {selectedTicket && !isCreating && (
                            <TicketDetail 
                                ticket={selectedTicket} 
                                isAdmin={isAdmin}
                                onClose={() => setSelectedTicket(null)}
                                onReply={handleReply}
                                replyMessage={newMessage}
                                setReplyMessage={setNewMessage}
                                onUpdateStatus={handleUpdateStatus}
                            />
                        )}
                    </div>

                    {/* Mobile Portals for Ticket Tab */}
                    {isCreating && createPortal(
                        <div className="fixed inset-0 z-[9999] flex flex-col bg-white dark:bg-ph-surface-card md:hidden animate-[slideInUp_0.3s_ease-out]">
                            <div className="w-full flex-1 overflow-hidden flex flex-col">
                                <CreateTicketForm 
                                    onClose={() => setIsCreating(false)} 
                                    onSubmit={handleCreateTicket} 
                                />
                            </div>
                        </div>,
                        document.body
                    )}

                    {selectedTicket && !isCreating && createPortal(
                        <div className="fixed inset-0 z-[9999] flex flex-col bg-white dark:bg-ph-surface-card md:hidden animate-[slideInUp_0.3s_ease-out]">
                            <div className="w-full flex-1 overflow-hidden flex flex-col">
                                <TicketDetail 
                                    ticket={selectedTicket} 
                                    isAdmin={isAdmin}
                                    onClose={() => setSelectedTicket(null)}
                                    onReply={handleReply}
                                    replyMessage={newMessage}
                                    setReplyMessage={setNewMessage}
                                    onUpdateStatus={handleUpdateStatus}
                                />
                            </div>
                        </div>,
                        document.body
                    )}

                    {/* FAB for Create Ticket (Mobile) */}
                    {!isCreating && !selectedTicket && !isAdmin && activeTab === 'tickets' && (
                        <button
                            onClick={() => setIsCreating(true)}
                            className="md:hidden fixed bottom-28 right-6 w-14 h-14 bg-blue-600 text-white rounded-full shadow-lg shadow-blue-600/30 flex items-center justify-center active:scale-90 transition-transform z-50"
                        >
                            <LifeBuoy size={24} />
                        </button>
                    )}
                    </>
                )}

                {activeTab === 'inbox' && (
                     <>
                     <div className="w-full md:w-[350px] lg:w-[400px] flex-shrink-0 h-full flex flex-col gap-4">
                        {/* Tabs (Moved here) */}
                        <div className="flex gap-3">
                            <button 
                                onClick={() => setActiveTab('inbox')}
                                className={`flex-1 py-3 rounded-xl text-xs font-bold uppercase tracking-wider transition-all flex items-center justify-center gap-2 border ${
                                    activeTab === 'inbox' 
                                    ? 'bg-red-600 text-white border-red-600 shadow-lg shadow-red-600/20' 
                                    : 'bg-white dark:bg-ph-surface-card text-gray-500 border-gray-200 dark:border-white/10 hover:border-red-500/50'
                                }`}
                            >
                                <Mail size={16} /> PESAN
                                {messages.filter(m => !m.read || m.read === '0' || m.read === 0 || m.read === false).length > 0 && (
                                    <span className={`ml-1 px-1.5 py-0.5 rounded-md text-[9px] font-black min-w-[18px] text-center ${activeTab === 'inbox' ? 'bg-white text-red-600' : 'bg-red-500 text-white'}`}>{messages.filter(m => !m.read || m.read === '0' || m.read === 0 || m.read === false).length}</span>
                                )}
                            </button>
                            <button 
                                onClick={() => setActiveTab('tickets')}
                                className={`flex-1 py-3 rounded-xl text-xs font-bold uppercase tracking-wider transition-all flex items-center justify-center gap-2 border ${
                                    activeTab === 'tickets' 
                                    ? 'bg-blue-600 text-white border-blue-600 shadow-lg shadow-blue-600/20' 
                                    : 'bg-white dark:bg-ph-surface-card text-gray-500 border-gray-200 dark:border-white/10 hover:border-blue-500/50'
                                }`}
                            >
                                <LifeBuoy size={16} /> TIKET
                            </button>
                        </div>

                        <div className="flex-1 min-h-0 flex flex-col">
                            <InboxList 
                                messages={messages} 
                                selectedMessageId={selectedMessage?.id} 
                                onSelectMessage={handleSelectMessage}
                                isHiddenOnMobile={!!selectedMessage}
                                isLoading={isLoadingInbox}
                            />
                        </div>
                     </div>

                     <div className={`hidden md:flex flex-1 min-w-0 bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-2xl shadow-sm flex-col overflow-hidden relative transition-all ${!selectedMessage ? 'items-center justify-center' : ''}`}>
                         {!selectedMessage ? (
                            <div className="text-center p-8 opacity-50 select-none">
                                <div className="w-24 h-24 bg-gray-100 dark:bg-white/5 rounded-full flex items-center justify-center mx-auto mb-6">
                                    <Mail size={48} className="text-gray-400" />
                                </div>
                                <h3 className="text-xl font-black text-gray-300 dark:text-gray-600 uppercase tracking-widest">Baca Pesan</h3>
                                <p className="text-sm text-gray-400 mt-2 max-w-xs mx-auto">Pilih pesan dari kotak masuk untuk membaca detail informasi.</p>
                            </div>
                         ) : (
                             <InboxDetail 
                                message={selectedMessage} 
                                onClose={() => setSelectedMessage(null)} 
                                userName={userName}
                             />
                         )}
                     </div>

                     {/* Mobile Portal for Inbox */}
                     {selectedMessage && createPortal(
                        <div className="fixed inset-0 z-[9999] flex flex-col bg-white dark:bg-ph-surface-card md:hidden animate-[slideInUp_0.3s_ease-out]">
                            <div className="w-full flex-1 overflow-hidden flex flex-col">
                                 <InboxDetail 
                                    message={selectedMessage} 
                                    onClose={() => setSelectedMessage(null)} 
                                    userName={userName}
                                 />
                            </div>
                        </div>,
                        document.body
                     )}
                     </>
                )}
            </div>
        </div>
    );
};
