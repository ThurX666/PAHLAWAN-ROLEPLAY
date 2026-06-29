import React, { useEffect, useMemo, useState } from 'react';
import { CheckCircle, Loader2, Search, XCircle } from 'lucide-react';
import { API_URL, isPreviewEnv } from '../../config';

type UserRequest = {
  id: number;
  username: string;
  request_type: 'Feature' | 'Unban' | 'Namechange' | 'Refund';
  content: string;
  metadata: string | Record<string, unknown> | null;
  status: 'Pending' | 'Approved' | 'Rejected';
  admin_feedback?: string;
  created_at: string;
};

export const AdminUserRequests: React.FC = () => {
  const [requests, setRequests] = useState<UserRequest[]>([]);
  const [selected, setSelected] = useState<UserRequest | null>(null);
  const [feedback, setFeedback] = useState('');
  const [search, setSearch] = useState('');
  const [loading, setLoading] = useState(true);
  const [processing, setProcessing] = useState(false);

  const load = async () => {
    setLoading(true);
    try {
      if (isPreviewEnv()) {
        setRequests([]);
        return;
      }
      const response = await fetch(`${API_URL}/api_user_requests.php?action=get_requests`);
      const payload = await response.json();
      if (payload.status === 'success') setRequests(payload.data || []);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => { load(); }, []);

  const filtered = useMemo(() => requests.filter(request =>
    request.username.toLowerCase().includes(search.toLowerCase()) ||
    request.request_type.toLowerCase().includes(search.toLowerCase())
  ), [requests, search]);

  const review = async (status: 'Approved' | 'Rejected') => {
    if (!selected) return;
    if (status === 'Rejected' && feedback.trim() === '') {
      alert('Alasan penolakan wajib diisi.');
      return;
    }
    setProcessing(true);
    try {
      const response = await fetch(`${API_URL}/api_user_requests.php`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          action: 'process_request',
          id: selected.id,
          status,
          adminFeedback: feedback,
        }),
      });
      const payload = await response.json();
      if (payload.status !== 'success') throw new Error(payload.message || 'Gagal memproses permohonan.');
      setSelected(null);
      setFeedback('');
      await load();
    } catch (error) {
      alert(error instanceof Error ? error.message : 'Gagal memproses permohonan.');
    } finally {
      setProcessing(false);
    }
  };

  return (
    <section className="mt-8 border-t border-gray-200 dark:border-white/10 pt-8">
      <div className="mb-4">
        <h2 className="text-xl font-bold text-gray-900 dark:text-white">Permohonan Gameplay</h2>
        <p className="text-sm text-gray-500">Unban, namechange, refund, dan usulan fitur.</p>
      </div>
      <div className="relative mb-4">
        <Search className="absolute left-3 top-1/2 -translate-y-1/2 text-gray-400" size={16} />
        <input value={search} onChange={event => setSearch(event.target.value)}
          className="w-full rounded-xl border border-gray-200 bg-white py-3 pl-10 pr-4 text-sm dark:border-white/10 dark:bg-ph-surface-card"
          placeholder="Cari UCP atau tipe permohonan..." />
      </div>
      {loading ? <Loader2 className="animate-spin" /> : (
        <div className="grid gap-3 lg:grid-cols-2">
          {filtered.map(request => (
            <button key={request.id} onClick={() => { setSelected(request); setFeedback(request.admin_feedback || ''); }}
              className="rounded-xl border border-gray-200 bg-white p-4 text-left dark:border-white/10 dark:bg-ph-surface-card">
              <div className="flex justify-between gap-3">
                <strong>{request.request_type} #{request.id}</strong>
                <span className="text-xs">{request.status}</span>
              </div>
              <p className="mt-1 text-xs text-gray-500">{request.username}</p>
              <p className="mt-3 line-clamp-2 text-sm">{request.content}</p>
            </button>
          ))}
        </div>
      )}
      {selected && (
        <div className="mt-5 rounded-2xl border border-gray-200 bg-white p-5 dark:border-white/10 dark:bg-ph-surface-card">
          <h3 className="font-bold">{selected.request_type} — {selected.username}</h3>
          <p className="my-3 whitespace-pre-wrap text-sm">{selected.content}</p>
          <pre className="mb-4 overflow-auto rounded-lg bg-gray-100 p-3 text-xs dark:bg-black/30">
            {JSON.stringify(typeof selected.metadata === 'string' ? JSON.parse(selected.metadata || '{}') : selected.metadata, null, 2)}
          </pre>
          <textarea value={feedback} onChange={event => setFeedback(event.target.value)}
            className="min-h-24 w-full rounded-xl border border-gray-200 p-3 text-sm dark:border-white/10 dark:bg-black/20"
            placeholder="Catatan admin..." />
          <div className="mt-3 flex gap-3">
            <button disabled={processing} onClick={() => review('Approved')}
              className="flex items-center gap-2 rounded-lg bg-green-600 px-4 py-2 text-white">
              <CheckCircle size={16} /> Setujui
            </button>
            <button disabled={processing} onClick={() => review('Rejected')}
              className="flex items-center gap-2 rounded-lg bg-red-600 px-4 py-2 text-white">
              <XCircle size={16} /> Tolak
            </button>
          </div>
        </div>
      )}
    </section>
  );
};
