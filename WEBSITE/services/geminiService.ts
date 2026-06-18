type AiMessage = {
  role: 'system' | 'user' | 'assistant';
  content: string;
};

type AiRequestOptions = {
  responseFormat?: 'json';
  task: 'server-news' | 'roleplay-evaluation';
};

export type AiProvider = {
  sendMessage: (messages: AiMessage[], options: AiRequestOptions) => Promise<string>;
};

let activeProvider: AiProvider | null = null;

export const setAiProvider = (provider: AiProvider | null) => {
  activeProvider = provider;
};

const sendMessage = async (messages: AiMessage[], options: AiRequestOptions) => {
  if (!activeProvider) {
    throw new Error("AI provider is not configured");
  }

  return activeProvider.sendMessage(messages, options);
};

export const generateServerNews = async (): Promise<{ title: string; content: string; tags: string[] }> => {
  const prompt = `
    Buatkan berita "In-Character" (IC) singkat dan imersif untuk server GTA San Andreas Roleplay berbahasa Indonesia.
    Berita harus mengenai kejadian acak di Los Santos (contoh: balap liar, perampokan bank, pemilihan walikota, perang geng).
    Gunakan gaya bahasa reporter berita Indonesia yang dramatis (seperti "Pemirsa, terjadi kekacauan di...").
    Panjang maksimal 100 kata.
  `;

  try {
    const text = await sendMessage(
      [{ role: 'user', content: prompt }],
      { task: 'server-news', responseFormat: 'json' }
    );
    if (!text) throw new Error("No response from AI");
    return JSON.parse(text);
  } catch (error) {
    console.error("News Generation Error:", error);
    return {
      title: "Gangguan Sinyal",
      content: "Tidak dapat terhubung ke satelit San News saat ini. Silakan coba lagi nanti.",
      tags: ["Sistem", "Error"]
    };
  }
};

export const evaluateRoleplayApp = async (app: { characterName: string; story: string; faction: string }) => {
  const prompt = `
    Kamu adalah Admin Roleplay yang tegas untuk server GTA SA-MP "Pahlawan Roleplay" (Server Indonesia).
    Evaluasi aplikasi karakter/faksi berikut.
    
    Nama Karakter: ${app.characterName}
    Target Faksi/Tujuan: ${app.faction}
    Cerita Latar Belakang (Backstory): "${app.story}"
    
    Analisis cerita tersebut berdasarkan:
    1. Tata bahasa Indonesia (EYD) dan penggunaan huruf kapital.
    2. Realisme Roleplay (Cek Powergaming/Metagaming). Karakter tidak boleh terlalu sakti.
    3. Kreativitas cerita.
    
    Berikan respons JSON dengan:
    - score (0-100)
    - feedback (kritik/saran singkat dalam Bahasa Indonesia yang sopan namun tegas)
    - approved (true jika score > 70)
  `;

  try {
    const text = await sendMessage(
      [{ role: 'user', content: prompt }],
      { task: 'roleplay-evaluation', responseFormat: 'json' }
    );
    if (!text) throw new Error("No response from AI");
    return JSON.parse(text);
  } catch (error) {
    console.error("Evaluation Error:", error);
    throw error;
  }
};
