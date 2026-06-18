import React, { useEffect, useMemo, useState } from 'react';
import {
  AlertTriangle,
  BarChart3,
  Bot,
  Calendar,
  CheckCircle,
  Clock3,
  FileSearch,
  History,
  RefreshCw,
  Search,
  ShieldCheck,
} from 'lucide-react';
import {
  analyzeStory,
  getStoryMatches,
  getStoryReviews,
  StoryReview,
  StoryReviewMatch,
} from '../../../services/storyReviewService';

interface StoryReviewPanelProps {
  storyId: number;
  adminLevel: number;
}

type ActiveView = 'analysis' | 'matches';

const formatDateTime = (value: string) => {
  const date = new Date(value);
  return Number.isNaN(date.getTime()) ? value : date.toLocaleString('id-ID');
};

const ScoreCard: React.FC<{ label: string; value: number; accent: string }> = ({ label, value, accent }) => (
  <div className="rounded-xl border border-gray-200 bg-white p-3 dark:border-white/10 dark:bg-white/5">
    <div className="text-[10px] font-bold uppercase tracking-wider text-gray-500">{label}</div>
    <div className={`mt-1 text-2xl font-black ${accent}`}>{value.toFixed(2)}</div>
    <div className="mt-2 h-1.5 overflow-hidden rounded-full bg-gray-200 dark:bg-white/10">
      <div className={`h-full rounded-full ${accent.replace('text-', 'bg-')}`} style={{ width: `${value}%` }} />
    </div>
  </div>
);

export const StoryReviewPanel: React.FC<StoryReviewPanelProps> = ({ storyId, adminLevel }) => {
  const [history, setHistory] = useState<StoryReview[]>([]);
  const [selectedReviewId, setSelectedReviewId] = useState<number | null>(null);
  const [matches, setMatches] = useState<StoryReviewMatch[]>([]);
  const [activeView, setActiveView] = useState<ActiveView>('analysis');
  const [loading, setLoading] = useState(true);
  const [analyzing, setAnalyzing] = useState(false);
  const [matchesLoading, setMatchesLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const selectedReview = useMemo(
    () => history.find(review => review.id === selectedReviewId) ?? history[0] ?? null,
    [history, selectedReviewId]
  );

  const loadReviews = async (preferReviewId?: number) => {
    setLoading(true);
    setError(null);
    try {
      const result = await getStoryReviews(storyId);
      setHistory(result.history);
      setSelectedReviewId(preferReviewId ?? result.review?.id ?? result.history[0]?.id ?? null);
    } catch (requestError) {
      setError(requestError instanceof Error ? requestError.message : 'Gagal memuat Story Review.');
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    setHistory([]);
    setMatches([]);
    setActiveView('analysis');
    void loadReviews();
  }, [storyId]);

  useEffect(() => {
    setMatches([]);
  }, [selectedReviewId]);

  const handleAnalyze = async () => {
    if (adminLevel < 5 || analyzing) return;
    setAnalyzing(true);
    setError(null);
    try {
      const result = await analyzeStory(storyId);
      await loadReviews(result.review.id);
      setActiveView('analysis');
    } catch (requestError) {
      setError(requestError instanceof Error ? requestError.message : 'Analisis Story gagal.');
    } finally {
      setAnalyzing(false);
    }
  };

  const handleViewMatches = async () => {
    if (!selectedReview) return;
    setActiveView('matches');
    setMatchesLoading(true);
    setError(null);
    try {
      const result = await getStoryMatches(selectedReview.id);
      setMatches(result.matches);
    } catch (requestError) {
      setError(requestError instanceof Error ? requestError.message : 'Gagal memuat cerita serupa.');
    } finally {
      setMatchesLoading(false);
    }
  };

  if (adminLevel < 5) {
    return (
      <div className="rounded-xl border border-red-200 bg-red-50 p-4 text-sm text-red-700 dark:border-red-900/30 dark:bg-red-900/10 dark:text-red-300">
        Story Review hanya tersedia untuk admin level 5 atau lebih tinggi.
      </div>
    );
  }

  return (
    <section className="mb-8 rounded-2xl border border-gray-200 bg-gray-50/70 p-4 dark:border-white/10 dark:bg-black/20">
      <div className="flex flex-col gap-3 xl:flex-row xl:items-center xl:justify-between">
        <div>
          <h3 className="flex items-center gap-2 text-sm font-black uppercase tracking-wider text-gray-800 dark:text-white">
            <ShieldCheck size={17} className="text-indigo-500" /> Story Review
          </h3>
          <p className="mt-1 text-xs text-gray-500">
            Analisis bersifat rekomendasi. Status cerita tetap ditentukan melalui tombol manual di bawah.
          </p>
        </div>
        <div className="flex flex-wrap gap-2">
          <button
            onClick={handleAnalyze}
            disabled={analyzing}
            className="flex items-center gap-1.5 rounded-lg bg-indigo-600 px-3 py-2 text-xs font-bold text-white hover:bg-indigo-700 disabled:cursor-not-allowed disabled:opacity-50"
          >
            {analyzing ? <RefreshCw size={13} className="animate-spin" /> : <Bot size={13} />}
            {history.length > 0 ? 'Re-Analyze Story' : 'Analyze Story'}
          </button>
          {selectedReview && (
            <>
              <button
                onClick={() => setActiveView('analysis')}
                className={`flex items-center gap-1.5 rounded-lg px-3 py-2 text-xs font-bold ${
                  activeView === 'analysis'
                    ? 'bg-gray-900 text-white dark:bg-white dark:text-black'
                    : 'bg-white text-gray-700 dark:bg-white/10 dark:text-gray-200'
                }`}
              >
                <BarChart3 size={13} /> View Analysis
              </button>
              <button
                onClick={handleViewMatches}
                className={`flex items-center gap-1.5 rounded-lg px-3 py-2 text-xs font-bold ${
                  activeView === 'matches'
                    ? 'bg-red-600 text-white'
                    : 'bg-white text-gray-700 dark:bg-white/10 dark:text-gray-200'
                }`}
              >
                <Search size={13} /> View Similar Stories
              </button>
            </>
          )}
        </div>
      </div>

      {error && (
        <div className="mt-4 flex items-start gap-2 rounded-lg border border-red-200 bg-red-50 p-3 text-xs text-red-700 dark:border-red-900/30 dark:bg-red-900/10 dark:text-red-300">
          <AlertTriangle size={15} className="shrink-0" /> {error}
        </div>
      )}

      {loading ? (
        <div className="mt-5 flex items-center justify-center gap-2 py-8 text-sm text-gray-500">
          <RefreshCw size={16} className="animate-spin" /> Memuat review...
        </div>
      ) : !selectedReview ? (
        <div className="mt-5 rounded-xl border-2 border-dashed border-gray-200 p-8 text-center dark:border-white/10">
          <FileSearch size={30} className="mx-auto mb-3 text-gray-400" />
          <p className="text-sm font-bold text-gray-700 dark:text-gray-200">Belum ada review tersimpan</p>
          <p className="mt-1 text-xs text-gray-500">Gunakan Analyze Story untuk membuat review pertama.</p>
        </div>
      ) : (
        <div className="mt-5">
          <div className="mb-4 flex flex-col gap-3 rounded-xl border border-gray-200 bg-white p-3 dark:border-white/10 dark:bg-[#151515] md:flex-row md:items-center md:justify-between">
            <div className="flex flex-wrap items-center gap-2 text-xs">
              <span className="flex items-center gap-1 font-bold text-gray-700 dark:text-gray-200">
                <History size={13} /> Review #{selectedReview.id}
              </span>
              <span className="text-gray-400">•</span>
              <span className="flex items-center gap-1 text-gray-500">
                <Calendar size={13} /> {formatDateTime(selectedReview.created_at)}
              </span>
              {selectedReview.is_stale ? (
                <span className="rounded-full bg-orange-100 px-2 py-1 text-[10px] font-bold uppercase text-orange-700">
                  Stale
                </span>
              ) : (
                <span className="flex items-center gap-1 rounded-full bg-green-100 px-2 py-1 text-[10px] font-bold uppercase text-green-700">
                  <CheckCircle size={11} /> Current
                </span>
              )}
            </div>
            <label className="flex items-center gap-2 text-xs font-bold text-gray-500">
              Riwayat
              <select
                value={selectedReview.id}
                onChange={event => {
                  setSelectedReviewId(Number(event.target.value));
                  setActiveView('analysis');
                }}
                className="rounded-lg border border-gray-200 bg-white px-2 py-1.5 text-xs text-gray-800 outline-none dark:border-white/10 dark:bg-[#0a0a0a] dark:text-white"
              >
                {history.map((review, index) => (
                  <option key={review.id} value={review.id}>
                    {index === 0 ? 'Latest — ' : ''}#{review.id} · {formatDateTime(review.created_at)}
                  </option>
                ))}
              </select>
            </label>
          </div>

          {activeView === 'analysis' ? (
            <div className="space-y-4">
              <div className="grid grid-cols-2 gap-3 xl:grid-cols-4">
                <ScoreCard label="Grammar" value={selectedReview.grammar_score} accent="text-blue-600" />
                <ScoreCard label="Readability" value={selectedReview.readability_score} accent="text-cyan-600" />
                <ScoreCard label="Roleplay" value={selectedReview.roleplay_score} accent="text-purple-600" />
                <ScoreCard label="Overall" value={selectedReview.overall_score} accent="text-indigo-600" />
              </div>

              <div className="grid gap-3 xl:grid-cols-[1fr_auto]">
                <div className="rounded-xl border border-gray-200 bg-white p-4 dark:border-white/10 dark:bg-[#151515]">
                  <div className="mb-2 text-[10px] font-bold uppercase tracking-wider text-gray-500">Review Notes</div>
                  <p className="whitespace-pre-wrap text-sm leading-relaxed text-gray-700 dark:text-gray-200">
                    {selectedReview.review_notes || 'Tidak ada catatan.'}
                  </p>
                </div>
                <div className="min-w-[240px] rounded-xl border border-gray-200 bg-white p-4 text-xs dark:border-white/10 dark:bg-[#151515]">
                  <div className="mb-3 flex items-center gap-2 font-bold uppercase text-gray-500">
                    <Bot size={14} /> Provider Metadata
                  </div>
                  <dl className="space-y-2">
                    <div><dt className="text-gray-400">Provider</dt><dd className="font-bold">{selectedReview.ai_provider}</dd></div>
                    <div><dt className="text-gray-400">Model</dt><dd className="break-all font-mono text-[11px]">{selectedReview.ai_model}</dd></div>
                    <div><dt className="text-gray-400">Timestamp</dt><dd>{formatDateTime(selectedReview.created_at)}</dd></div>
                    <div><dt className="text-gray-400">Reviewer</dt><dd>{selectedReview.reviewer_username}</dd></div>
                  </dl>
                </div>
              </div>

              <div className={`rounded-xl border p-4 ${
                selectedReview.plagiarism_score >= selectedReview.plagiarism_threshold
                  ? 'border-red-200 bg-red-50 dark:border-red-900/30 dark:bg-red-900/10'
                  : 'border-green-200 bg-green-50 dark:border-green-900/30 dark:bg-green-900/10'
              }`}>
                <div className="flex items-center justify-between gap-4">
                  <div>
                    <div className="text-[10px] font-bold uppercase tracking-wider text-gray-500">
                      Local Deterministic Plagiarism
                    </div>
                    <p className="mt-1 text-xs text-gray-500">
                      Terpisah dari skor AI. Threshold: {selectedReview.plagiarism_threshold.toFixed(2)}%
                    </p>
                  </div>
                  <div className="text-right">
                    <div className="text-2xl font-black">{selectedReview.plagiarism_score.toFixed(2)}%</div>
                    <div className="text-[10px] font-bold uppercase">
                      {selectedReview.plagiarism_score >= selectedReview.plagiarism_threshold ? 'Flagged' : 'Below threshold'}
                    </div>
                  </div>
                </div>
              </div>
            </div>
          ) : (
            <div className="space-y-3">
              <div className="flex items-center justify-between">
                <h4 className="flex items-center gap-2 text-xs font-black uppercase text-gray-600 dark:text-gray-300">
                  <FileSearch size={15} /> Similar Stories
                </h4>
                <span className="text-[10px] text-gray-500">
                  Threshold {selectedReview.plagiarism_threshold.toFixed(2)}%
                </span>
              </div>
              {matchesLoading ? (
                <div className="flex items-center justify-center gap-2 py-8 text-sm text-gray-500">
                  <RefreshCw size={16} className="animate-spin" /> Memuat matches...
                </div>
              ) : matches.length === 0 ? (
                <div className="rounded-xl border-2 border-dashed border-gray-200 p-6 text-center text-xs text-gray-500 dark:border-white/10">
                  Tidak ada cerita serupa yang tersimpan untuk review ini.
                </div>
              ) : matches.map(match => (
                <div
                  key={match.id}
                  className={`rounded-xl border p-4 ${
                    match.is_flagged
                      ? 'border-red-300 bg-red-50 dark:border-red-900/40 dark:bg-red-900/10'
                      : 'border-gray-200 bg-white dark:border-white/10 dark:bg-[#151515]'
                  }`}
                >
                  <div className="flex items-center justify-between gap-4">
                    <div>
                      <div className="flex items-center gap-2">
                        <span className="text-xs font-black">Rank #{match.match_rank}</span>
                        {match.is_flagged && (
                          <span className="flex items-center gap-1 rounded-full bg-red-600 px-2 py-0.5 text-[9px] font-bold uppercase text-white">
                            <AlertTriangle size={10} /> Flagged
                          </span>
                        )}
                        {match.is_stale && (
                          <span className="flex items-center gap-1 rounded-full bg-orange-100 px-2 py-0.5 text-[9px] font-bold uppercase text-orange-700">
                            <Clock3 size={10} /> Stale match
                          </span>
                        )}
                      </div>
                      <p className="mt-1 text-sm font-bold text-gray-800 dark:text-gray-100">
                        {match.character_name || `Story #${match.matched_story_id}`}
                      </p>
                      <p className="text-[10px] text-gray-500">Story ID {match.matched_story_id}</p>
                    </div>
                    <div className={`text-2xl font-black ${match.is_flagged ? 'text-red-600' : 'text-gray-700 dark:text-gray-200'}`}>
                      {match.similarity_percentage.toFixed(2)}%
                    </div>
                  </div>
                </div>
              ))}
            </div>
          )}
        </div>
      )}
    </section>
  );
};
