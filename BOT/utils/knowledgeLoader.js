const fs = require("fs");
const path = require("path");

const KNOWLEDGE_DIR = path.join(__dirname, "..", "knowledge");

/**
 * Load semua file .md dari folder knowledge/ dan parse menjadi chunks.
 * Setiap file dipisah per section (## heading) sebagai satu chunk.
 */
function loadKnowledge() {
  const knowledge = [];

  if (!fs.existsSync(KNOWLEDGE_DIR)) {
    console.warn("[KnowledgeLoader] Folder knowledge/ tidak ditemukan.");
    return knowledge;
  }

  const files = fs.readdirSync(KNOWLEDGE_DIR).filter((f) => f.endsWith(".md"));

  for (const file of files) {
    const filePath = path.join(KNOWLEDGE_DIR, file);
    const content = fs.readFileSync(filePath, "utf-8");
    const topic = path.basename(file, ".md").replace(/-/g, " ");

    // Parse sections berdasarkan ## heading
    const sections = content.split(/(?=^## )/gm);

    for (const section of sections) {
      const trimmed = section.trim();
      if (!trimmed) continue;

      // Ambil judul section (dari ## atau #)
      const titleMatch = trimmed.match(/^#{1,3}\s+(.+)$/m);
      const sectionTitle = titleMatch ? titleMatch[1].trim() : topic;

      // Ekstrak keywords dari konten (ambil kata unik)
      const keywords = extractKeywords(trimmed);

      knowledge.push({
        topic,
        section: sectionTitle,
        content: trimmed,
        keywords,
        source: file,
      });
    }
  }

  console.log(`[KnowledgeLoader] ${knowledge.length} knowledge chunks loaded from ${files.length} files.`);
  return knowledge;
}

/**
 * Extract keywords penting dari teks markdown.
 * Ambil kata benda penting, nama, singkatan.
 */
function extractKeywords(text) {
  // Hapus formatting markdown
  const clean = text
    .replace(/[#*`_~>|\[\]()]/g, " ")
    .replace(/\s+/g, " ")
    .toLowerCase()
    .trim();

  // Ambil kata dengan panjang > 3 karakter
  const words = clean.split(" ").filter((w) => w.length > 3);

  // Filter stop words
  const stopWords = new Set([
    "yang", "dengan", "untuk", "tidak", "akan", "dapat", "dari", "serta",
    "anda", "kami", "kita", "mereka", "dalam", "pada", "adalah", "telah",
    "sudah", "bisa", "jika", "saat", "juga", "baik", "lebih", "sangat",
    "secara", "tanpa", "antara", "demi", "oleh", "sebab", "karena", "maka",
  ]);

  const keywords = [...new Set(words.filter((w) => !stopWords.has(w)))];

  return keywords;
}

/**
 * Cari knowledge chunks yang relevan dengan query user.
 * Menggunakan simple keyword matching + scoring.
 */
function retrieveRelevantKnowledge(query, knowledgeDB, maxResults = 5) {
  if (!knowledgeDB || knowledgeDB.length === 0) return [];

  const queryLower = query.toLowerCase();
  const queryKeywords = extractKeywords(queryLower);

  // Scoring tiap chunk berdasarkan keyword match dan direct match
  const scored = knowledgeDB.map((chunk) => {
    let score = 0;

    // 1. Direct text match di content
    if (chunk.content.toLowerCase().includes(queryLower)) {
      score += 10;
    }

    // 2. Direct match di section title
    if (chunk.section.toLowerCase().includes(queryLower)) {
      score += 8;
    }

    // 3. Direct match di topic
    if (chunk.topic.toLowerCase().includes(queryLower)) {
      score += 5;
    }

    // 4. Keyword overlap
    const matchCount = queryKeywords.filter((kw) =>
      chunk.keywords.includes(kw)
    ).length;
    score += matchCount * 3;

    // 5. Bonus untuk partial match keyword
    const partialMatch = queryKeywords.filter((kw) =>
      chunk.keywords.some((ckw) => ckw.includes(kw) || kw.includes(ckw))
    ).length;
    score += partialMatch;

    return { ...chunk, score };
  });

  // Sort descending by score, filter yang score > 0
  const relevant = scored
    .filter((c) => c.score > 0)
    .sort((a, b) => b.score - a.score)
    .slice(0, maxResults);

  return relevant;
}

/**
 * Format hasil retrieval menjadi string konteks untuk system prompt.
 */
function formatKnowledgeContext(results) {
  if (!results || results.length === 0) return "";

  let context = "\n\n=== PENGETAHUAN SERVER YANG RELEVAN ===\n";

  for (const r of results) {
    context += `\n[Sumber: ${r.topic} - ${r.section}]\n`;
    // Ambil teks bersih (hapus formatting markdown heading untuk hemat token)
    const cleanContent = r.content
      .replace(/^#{1,3}\s+/gm, "")
      .trim();
    context += cleanContent + "\n";
  }

  context += "\n=== AKHIR PENGETAHUAN SERVER ===\n";
  return context;
}

// Inisialisasi database (load sekali di startup)
let knowledgeDB = null;

function getKnowledgeDB() {
  if (!knowledgeDB) {
    knowledgeDB = loadKnowledge();
  }
  return knowledgeDB;
}

module.exports = {
  loadKnowledge,
  retrieveRelevantKnowledge,
  formatKnowledgeContext,
  getKnowledgeDB,
};