import { Type } from "@google/genai";

// Mock Database of existing stories to compare against
const EXISTING_STORIES_DB = [
    "Lahir di Los Santos, saya besar di lingkungan Ganton. Ayah saya seorang mekanik...",
    "Saya adalah seorang mantan polisi dari Vice City yang pindah karena korupsi...",
    "Datang dari desa kecil di Angel Pine, mencoba mengadu nasib di kota besar..."
];

export const checkStoryPlagiarism = async (newStory: string): Promise<{ score: number; details: string }> => {
  // Simulate API Latency
  await new Promise(resolve => setTimeout(resolve, 1500));

  // Simple simulation: Check if specific phrases exist (In real world, this uses Vector Embeddings)
  let similarityScore = 0;
  let details = "Cerita orisinal.";

  // Logic simulasi plagiarisme
  if (newStory.length < 50) {
      return { score: 0, details: "Cerita terlalu pendek untuk dianalisis." };
  }

  // Cek kemiripan kasar (Simulasi)
  const commonPhrases = ["lahir di los santos", "besar di ganton", "ayah saya mekanik"];
  let matchCount = 0;
  
  commonPhrases.forEach(phrase => {
      if(newStory.toLowerCase().includes(phrase)) matchCount++;
  });

  if (matchCount > 0) {
      similarityScore = 35 + (matchCount * 20); // Random logic for demo
      details = `Terdeteksi kemiripan struktur dengan cerita ID #105 (Ganton Arc).`;
  }
  
  // Force high plagiarism if exact copy of mock DB
  if (EXISTING_STORIES_DB.some(s => s.includes(newStory.substring(0, 20)))) {
      similarityScore = 95;
      details = "CRITICAL: Teks identik dengan cerita milik player 'Ucok_Slepbeuw'.";
  }

  return {
    score: Math.min(similarityScore, 100),
    details
  };
};