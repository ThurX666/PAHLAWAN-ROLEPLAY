import { API_URL } from '../config';

export interface StoryReview {
  id: number;
  story_id: number;
  character_id: number;
  character_name: string | null;
  reviewer_id: number;
  reviewer_username: string;
  ai_provider: string;
  ai_model: string;
  analysis_version: string;
  word_count: number;
  character_count: number;
  overall_score: number;
  grammar_score: number;
  readability_score: number;
  roleplay_score: number;
  plagiarism_score: number;
  plagiarism_threshold: number;
  review_notes: string | null;
  created_at: string;
  is_stale: boolean;
  is_deterministic_placeholder: boolean;
}

export interface StoryReviewMatch {
  id: number;
  review_id: number;
  matched_story_id: number;
  matched_character_id: number;
  character_name: string | null;
  similarity_percentage: number;
  match_rank: number;
  is_flagged: boolean;
  is_stale: boolean;
  created_at: string;
}

type ApiEnvelope<T> = {
  status: 'success' | 'error';
  data?: T;
  message?: string;
};

const request = async <T>(url: string, init?: RequestInit): Promise<T> => {
  const response = await fetch(url, {
    credentials: 'include',
    ...init,
  });
  const payload = await response.json() as ApiEnvelope<T>;
  if (!response.ok || payload.status !== 'success' || !payload.data) {
    throw new Error(payload.message || 'Story Review request failed.');
  }
  return payload.data;
};

export const getStoryReviews = async (storyId: number) => {
  const params = new URLSearchParams({
    action: 'get_story_review',
    story_id: String(storyId),
    include_history: '1',
  });
  return request<{ review: StoryReview | null; history: StoryReview[] }>(
    `${API_URL}/api_story_review.php?${params.toString()}`
  );
};

export const analyzeStory = async (storyId: number) => {
  return request<{
    review: StoryReview;
    match_count: number;
    manual_approval_required: boolean;
  }>(`${API_URL}/api_story_review.php`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ action: 'analyze_story', story_id: storyId }),
  });
};

export const getStoryMatches = async (reviewId: number) => {
  const params = new URLSearchParams({
    action: 'get_story_matches',
    review_id: String(reviewId),
  });
  return request<{
    review_id: number;
    plagiarism_threshold: number;
    matches: StoryReviewMatch[];
  }>(`${API_URL}/api_story_review.php?${params.toString()}`);
};
