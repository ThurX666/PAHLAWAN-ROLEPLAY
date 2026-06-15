/**
 * PHRP-AI Knowledge Loader
 * Load dan retrieve knowledge dari file markdown di folder knowledge/
 */

const fs = require("fs");
const path = require("path");

const KNOWLEDGE_DIR = path.join(__dirname, "..", "knowledge");

function loadKnowledge() {
  const knowledge = [];

  if (!fs.existsSync(KNOWLEDGE_DIR)) {
    console.warn("[PHRP-AI/utils/knowledgeLoader.js] Folder knowledge/ tidak ditemukan.");
    return knowledge;
  }

  const files = fs.readdirSync(KNOWLEDGE_DIR).filter((f) => f.endsWith(".md"));

  for (const file of files) {
    const filePath = path.join(KNOWLEDGE_DIR, file);
    const content = fs.readFileSync(filePath, "utf-8");
    const topic = path.basename(file, ".md").replace(/-/g, " ");

    const sections = content.split(/(?=^## )/gm);

    for (const section of sections) {
      const trimmed = section.trim();
      if (!trimmed) continue;

      const titleMatch = trimmed.match(/^#{1,3}\s+(.+)$/m);
      const sectionTitle = titleMatch ? titleMatch[1].trim() : topic;
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

    console.log(`[PHRP-AI/utils/knowledgeLoader.js] ${knowledge.length} knowledge chunks loaded from ${files.length} files.`);
  return knowledge;
}

function extractKeywords(text) {
  const clean = text
    .replace(/[#*`_~>|\[\]()]/g, " ")
    .replace(/\s+/g, " ")
    .toLowerCase()
    .trim();

  const words = clean.split(" ").filter((w) => w.length > 3);

  const stopWords = new Set([
    "yang", "dengan", "untuk", "tidak", "akan", "dapat", "dari", "serta",
    "anda", "kami", "kita", "mereka", "dalam", "pada", "adalah", "telah",
    "sudah", "bisa", "jika", "saat", "juga", "baik", "lebih", "sangat",
    "secara", "tanpa", "antara", "demi", "oleh", "sebab", "karena", "maka",
  ]);

  return [...new Set(words.filter((w) => !stopWords.has(w)))];
}

function retrieveRelevantKnowledge(query, knowledgeDB, maxResults = 5) {
  if (!knowledgeDB || knowledgeDB.length === 0) return [];

  const queryLower = query.toLowerCase();
  const queryKeywords = extractKeywords(queryLower);

  const scored = knowledgeDB.map((chunk) => {
    let score = 0;

    if (chunk.content.toLowerCase().includes(queryLower)) score += 10;
    if (chunk.section.toLowerCase().includes(queryLower)) score += 8;
    if (chunk.topic.toLowerCase().includes(queryLower)) score += 5;

    const matchCount = queryKeywords.filter((kw) => chunk.keywords.includes(kw)).length;
    score += matchCount * 3;

    const partialMatch = queryKeywords.filter((kw) =>
      chunk.keywords.some((ckw) => ckw.includes(kw) || kw.includes(ckw))
    ).length;
    score += partialMatch;

    return { ...chunk, score };
  });

  return scored
    .filter((c) => c.score > 0)
    .sort((a, b) => b.score - a.score)
    .slice(0, maxResults);
}

function formatKnowledgeContext(results) {
  if (!results || results.length === 0) return "";

  let context = "\n\n=== PENGETAHUAN SERVER YANG RELEVAN ===\n";

  for (const r of results) {
    context += `\n[Sumber: ${r.topic} - ${r.section}]\n`;
    const cleanContent = r.content.replace(/^#{1,3}\s+/gm, "").trim();
    context += cleanContent + "\n";
  }

  context += "\n=== AKHIR PENGETAHUAN SERVER ===\n";
  return context;
}

let knowledgeDB = null;

function getKnowledgeDB() {
  if (!knowledgeDB) {
    knowledgeDB = loadKnowledge();
  }
  return knowledgeDB;
}

module.exports = {
  loadKnowledge,
  getKnowledgeDB,
  retrieveRelevantKnowledge: (query, db) => {
    if (!query) return "Respon AI tidak dapat spesifik karena query kosong.";
    return db.filter(entry => entry.content.includes(query));
  },
  formatKnowledgeContext,
  getKnowledgeDB,
};