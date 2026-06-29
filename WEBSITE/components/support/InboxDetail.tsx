
import React from 'react';
import { XCircle, Tag, Copy, ChevronLeft } from 'lucide-react';
import { InboxMessage } from '../../types';
import { formatTime } from './utils';
import { WelcomeGuide } from './WelcomeGuide';
import { CharacterCreatedMessage, DiscordLinkedMessage, NewLoginDetectedMessage, PasswordChangedMessage, OocProfileReviewMessage, CharacterStoryReviewMessage, PaymentProcessedMessage, TicketClosedMessage, ServerWarningMessage, VipExpiredMessage, UnbanRequestApprovedMessage, PropertyInactivityWarningMessage, NamechangeSuccessMessage, PlayerReportRespondedMessage, RefundApprovedMessage } from './SystemMessageTemplates';

interface InboxDetailProps {
  message: InboxMessage;
  onClose: () => void;
  userName: string;
}

export const InboxDetail: React.FC<InboxDetailProps> = ({ message, onClose, userName }) => {
  const copyToClipboard = (text: string) => {
      navigator.clipboard.writeText(text);
      alert("Kode disalin ke clipboard!");
  };

  const handleContentClick = (e: React.MouseEvent<HTMLDivElement>) => {
      const target = e.target as HTMLElement;
      const anchor = target.closest('a');
      if (anchor && anchor.getAttribute('href')?.startsWith('#nav:')) {
          e.preventDefault();
          const tab = anchor.getAttribute('href')?.replace('#nav:', '');
          if (tab) {
              window.dispatchEvent(new CustomEvent('navigate-tab', { detail: { tab } }));
              onClose(); 
          }
      }
  };

  return (
    <div className="flex flex-col h-full animate-[fadeIn_0.3s_ease-out] bg-white dark:bg-ph-surface-card">
        <div className="p-4 md:p-5 border-b border-gray-200 dark:border-white/5 flex items-center bg-gray-50 dark:bg-ph-surface-panel sticky top-0 z-10">
            <button onClick={onClose} className="md:hidden text-gray-500 hover:text-red-500 p-2 -ml-2 mr-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors active:scale-95">
                <ChevronLeft size={24}/>
            </button>
            <div className="flex-1 min-w-0">
                <h3 className="text-base md:text-lg font-black text-gray-900 dark:text-white uppercase italic leading-tight whitespace-pre-wrap">{message.title}</h3>
                <div className="flex items-center gap-2 mt-1">
                    <span className="text-[10px] bg-gray-200 dark:bg-white/10 px-2 py-0.5 rounded text-gray-600 dark:text-gray-300">{formatTime(message.date)}</span>
                    <span className={`text-[10px] px-2 py-0.5 rounded font-bold uppercase ${message.type === 'Voucher' ? 'text-green-600 bg-green-100' : 'text-blue-600 bg-blue-100'}`}>{message.type}</span>
                </div>
            </div>
            <button onClick={onClose} className="hidden md:block text-gray-500 hover:text-red-500 p-2 hover:bg-gray-200 dark:hover:bg-white/10 rounded-full transition-colors"><XCircle size={24}/></button>
        </div>
        
        <div className="flex-1 p-4 md:p-6 pb-[calc(16px+env(safe-area-inset-bottom))] md:pb-6 overflow-y-auto custom-scrollbar">
            {message.template === 'Welcome' ? (
                <WelcomeGuide userName={userName} onClose={onClose} />
            ) : message.template === 'CharacterCreated' ? (
                <CharacterCreatedMessage metadata={message.metadata} />
            ) : message.template === 'DiscordLinked' ? (
                <DiscordLinkedMessage metadata={message.metadata} />
            ) : message.template === 'NewLoginDetected' ? (
                <NewLoginDetectedMessage metadata={message.metadata} />
            ) : message.template === 'PasswordChanged' ? (
                <PasswordChangedMessage metadata={message.metadata} />
            ) : message.template === 'OocProfileReview' ? (
                <OocProfileReviewMessage metadata={message.metadata} />
            ) : message.template === 'CharacterStoryReview' ? (
                <CharacterStoryReviewMessage metadata={message.metadata} />
            ) : message.template === 'PaymentProcessed' ? (
                <PaymentProcessedMessage metadata={message.metadata} />
            ) : message.template === 'TicketClosed' ? (
                <TicketClosedMessage metadata={message.metadata} />
            ) : message.template === 'ServerWarning' ? (
                <ServerWarningMessage metadata={message.metadata} />
            ) : message.template === 'VipExpired' ? (
                <VipExpiredMessage metadata={message.metadata} />
            ) : message.template === 'UnbanApproved' ? (
                <UnbanRequestApprovedMessage metadata={message.metadata} />
            ) : message.template === 'PropertyInactivityWarning' ? (
                <PropertyInactivityWarningMessage metadata={message.metadata} />
            ) : message.template === 'NamechangeSuccess' ? (
                <NamechangeSuccessMessage metadata={message.metadata} />
            ) : message.template === 'PlayerReportResponded' ? (
                <PlayerReportRespondedMessage metadata={message.metadata} />
            ) : message.template === 'RefundApproved' ? (
                <RefundApprovedMessage metadata={message.metadata} />
            ) : (
                <div 
                    onClick={handleContentClick}
                    className="text-sm md:text-base text-gray-800 dark:text-gray-300 leading-relaxed whitespace-pre-wrap"
                    dangerouslySetInnerHTML={{ __html: message.message || '' }}
                />
            )}

            {message.type === 'Voucher' && message.code && (
            <div className="mt-8 bg-gray-100 dark:bg-ph-surface-deep border-2 border-dashed border-gray-300 dark:border-gray-700 rounded-xl p-4 md:p-6 flex flex-col items-center justify-center group relative overflow-hidden">
                <div className="absolute top-0 right-0 p-2 opacity-10">
                    <Tag size={80} className="md:w-[100px] md:h-[100px]" />
                </div>
                
                {message.itemName && (
                    <div className="mb-6 w-full max-w-md z-10">
                        <div className="bg-white dark:bg-ph-surface-panel border border-blue-200 dark:border-blue-500/50 rounded-xl p-4 flex items-center gap-4 shadow-lg shadow-blue-500/10 relative overflow-hidden group">
                            {/* Blue Glow Effect */}
                            <div className="absolute inset-0 bg-blue-500/5 opacity-0 group-hover:opacity-100 transition-opacity pointer-events-none"></div>
                            
                            {/* Icon Container */}
                            <div className="w-12 h-12 bg-blue-50 dark:bg-ph-surface-elevated rounded-lg flex items-center justify-center shrink-0 border border-blue-100 dark:border-white/5">
                                <Tag className="text-blue-500 dark:text-blue-400" size={24} />
                            </div>
                            
                            {/* Content */}
                            <div className="flex-1 min-w-0">
                                <h4 className="text-base font-bold text-gray-900 dark:text-white truncate">{message.itemName}</h4>
                                {message.itemDescription && (
                                    <p className="text-xs text-gray-500 dark:text-gray-400 mt-0.5 line-clamp-2 leading-relaxed">
                                        {message.itemDescription}
                                    </p>
                                )}
                                {message.itemPrice && (
                                    <div className="mt-2 inline-flex items-center px-2 py-0.5 rounded bg-blue-50 dark:bg-blue-500/20 border border-blue-100 dark:border-blue-500/30">
                                        <span className="text-[10px] font-bold text-blue-600 dark:text-blue-400 uppercase tracking-wider">
                                            HARGA: {message.itemPrice} GC
                                        </span>
                                    </div>
                                )}
                            </div>
                        </div>
                    </div>
                )}

                <p className="text-xs text-gray-500 uppercase font-bold mb-2">Kode Voucher Anda</p>
                <div className="flex items-center gap-3 bg-white dark:bg-ph-surface-panel p-2 pr-3 rounded-lg border border-gray-200 dark:border-white/10 shadow-sm relative z-10 w-full max-w-md justify-between">
                    <code className="text-sm sm:text-base md:text-2xl font-mono font-black text-gray-900 dark:text-white tracking-wider md:tracking-widest px-2 truncate">
                        {message.code}
                    </code>
                    <button 
                        onClick={() => copyToClipboard(message.code!)}
                        className="p-2 hover:bg-gray-100 dark:hover:bg-white/10 rounded-md text-gray-400 hover:text-green-500 transition-colors shrink-0"
                        title="Salin"
                    >
                        <Copy size={20} />
                    </button>
                </div>
                <p className="text-[10px] text-gray-400 mt-3 italic text-center">
                    Gunakan command <span className="text-red-500 font-mono font-bold">/redeem {message.code}</span> di dalam game.
                </p>
            </div>
            )}
        </div>
    </div>
  );
};
