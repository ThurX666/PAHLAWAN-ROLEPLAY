
import React, { useState } from 'react';
import { Clock, ChevronLeft, ChevronRight } from 'lucide-react';

export interface Transaction {
  id: number;
  packageName: string;
  amount: string;
  price: string;
  status: 'Pending' | 'Success' | 'Rejected';
  date: string;
  method: string;
  proofUrl?: string;
}

interface TransactionHistoryProps {
    transactions: Transaction[];
}

export const TransactionHistory: React.FC<TransactionHistoryProps> = ({ transactions }) => {
  const [currentPage, setCurrentPage] = useState(1);
  const itemsPerPage = 5;
  const totalPages = Math.ceil(transactions.length / itemsPerPage);
  
  const currentTransactions = transactions.slice(
      (currentPage - 1) * itemsPerPage,
      currentPage * itemsPerPage
  );

  return (
      <section>
          <div className="flex items-center gap-2 mb-4 md:mb-6 px-1">
              <Clock className="text-gray-500" size={24} />
              <div>
                <h3 className="text-base md:text-lg font-black text-gray-900 dark:text-white uppercase italic tracking-wide leading-none">Riwayat Transaksi</h3>
                <p className="text-[10px] text-gray-500 font-bold uppercase tracking-wide mt-1">Status Pembayaran</p>
              </div>
          </div>
          
          <div className="bg-gray-50 dark:bg-ph-surface-panel border border-gray-200 dark:border-white/5 rounded-xl overflow-hidden">
              <div className="overflow-x-auto">
                <table className="w-full text-left text-[11px] md:text-sm text-gray-600 dark:text-gray-400">
                    <thead className="bg-gray-100 dark:bg-ph-surface-deep uppercase font-bold text-[9px] md:text-[10px] text-gray-500 border-b border-gray-200 dark:border-white/5">
                        <tr>
                            <th className="px-3 py-3 md:px-6 md:py-4">Item</th>
                            <th className="px-3 py-3 md:px-6 md:py-4">Harga</th>
                            <th className="hidden sm:table-cell px-3 py-3 md:px-6 md:py-4">Waktu</th>
                            <th className="hidden md:table-cell px-6 py-4">Metode</th>
                            <th className="px-3 py-3 md:px-6 md:py-4 text-right">Status</th>
                        </tr>
                    </thead>
                    <tbody className="divide-y divide-gray-200 dark:divide-white/5">
                        {currentTransactions.length > 0 ? (
                            currentTransactions.map((trx) => {
                                const dateParts = trx.date.split(', ');
                                const dateStr = dateParts[0];
                                const timeStr = dateParts[1] ? dateParts[1] + ' WIB' : '';
                                
                                const isRupiah = trx.price.includes('Rp');
                                const priceColorClass = isRupiah 
                                    ? 'text-emerald-600 dark:text-emerald-500' 
                                    : 'text-amber-500 dark:text-amber-400';
                                
                                return (
                                <tr key={trx.id} className="hover:bg-gray-100 dark:hover:bg-white/5 transition-colors">
                                    <td className="px-3 py-3 md:px-6 md:py-4 align-top">
                                        <div className="font-bold text-gray-900 dark:text-white whitespace-normal break-words max-w-[130px] sm:max-w-[160px] md:max-w-xs leading-tight">{trx.packageName}</div>
                                        {/* Mobile view date with time */}
                                        <div className="md:hidden text-[8px] text-gray-500 font-mono mt-1.5 leading-tight">
                                            {dateStr},<br/>{timeStr}
                                        </div>
                                    </td>
                                    <td className={`px-3 py-3 md:px-6 md:py-4 align-top font-mono font-bold whitespace-nowrap ${priceColorClass}`}>{trx.price}</td>
                                    <td className="hidden sm:table-cell px-3 py-3 md:px-6 md:py-4 align-top text-[10px] md:text-xs text-gray-500 font-mono">{trx.date} WIB</td>
                                    <td className="hidden md:table-cell px-6 py-4 align-top text-xs font-bold">{trx.method}</td>
                                    <td className="px-3 py-3 md:px-6 md:py-4 align-top text-right">
                                        <span className={`inline-block px-1.5 py-0.5 md:px-2 md:py-1 rounded text-[8px] md:text-[9px] font-bold uppercase border ${
                                            trx.status === 'Pending' ? 'bg-amber-100 dark:bg-amber-500/10 text-amber-600 dark:text-amber-500 border-amber-200 dark:border-amber-500/20' : 
                                            trx.status === 'Success' ? 'bg-green-100 dark:bg-green-500/10 text-green-600 dark:text-green-500 border-green-200 dark:border-green-500/20' : 
                                            'bg-red-100 dark:bg-red-500/10 text-red-600 dark:text-red-500 border-red-200 dark:border-red-500/20'
                                        }`}>
                                            {trx.status}
                                        </span>
                                    </td>
                                </tr>
                                );
                            })
                        ) : (
                            <tr>
                                <td colSpan={5} className="py-12 text-center text-xs opacity-50 italic">Belum ada transaksi terbaru</td>
                            </tr>
                        )}
                    </tbody>
                </table>
              </div>
              
              {/* Pagination Controls */}
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
      </section>
  );
};