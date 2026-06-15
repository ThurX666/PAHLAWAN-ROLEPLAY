
export interface Ticket {
    id: number;
    subject: string;
    category: 'Masalah Donasi' | 'Lapor Bug UCP' | 'Lainnya';
    status: 'Open' | 'Proses' | 'Dijawab' | 'Ditutup';
    lastUpdate: string; // ISO String format expected
    messages: { sender: string, text: string, time: string }[];
}
