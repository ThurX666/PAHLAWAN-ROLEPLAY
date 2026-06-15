/**
 * PHRP-AI AI Provider
 * Abstraction layer untuk API AI (LLM).
 * 
 * Konfigurasi ada di: PHRP-AI/config/app.json
 * 
 * Cara ganti provider:
 * 1. Edit PHRP-AI/config/app.json → ganti "activeProvider"
 * 2. Isi apiKey provider yang dipilih
 * 3. Restart bot (atau panggil phrp.setProvider("openai") runtime)
 */

const fs = require("fs");
const path = require("path");

const APP_CONFIG_PATH = path.join(__dirname, "..", "config", "app.json");

// ============================================================
// 1. LOAD KONFIGURASI DARI FILE
// ============================================================

let appConfig = null;

function loadAppConfig() {
  if (!fs.existsSync(APP_CONFIG_PATH)) {
    throw new Error(
      "File PHRP-AI/config/app.json tidak ditemukan! " +
      "Buat file tersebut dengan format:\n" +
      JSON.stringify({
        ai: {
          activeProvider: "groq",
          model: "openai/gpt-oss-20b",
          maxTokens: 1024,
          temperature: 0.2,
          reasoningEffort: "medium",
          apiKeys: {
            groq: "YOUR_GROQ_API_KEY",
            openai: "YOUR_OPENAI_API_KEY",
            custom: "xxx"
          }
        }
      }, null, 2)
    );
  }

  const raw = fs.readFileSync(APP_CONFIG_PATH, "utf-8");
  appConfig = JSON.parse(raw);
  return appConfig;
}

function getConfig() {
  if (!appConfig) {
    loadAppConfig();
  }
  return appConfig;
}

// ============================================================
// 2. IMPLEMENTASI PROVIDER
// ============================================================

// --- GROQ PROVIDER ---
async function groqSendMessage(messages, options = {}) {
  const config = getConfig();
  const GroqImport = require("groq-sdk");
  const Groq = GroqImport.default ?? GroqImport;

  const apiKey = config.ai.apiKeys.groq;
  if (!apiKey || apiKey === "YOUR_GROQ_API_KEY") {
    throw new Error(
      "GROQ API Key belum diisi! Buka PHRP-AI/config/app.json dan isi ai.apiKeys.groq"
    );
  }

  const groq = new Groq({ apiKey });

  const completion = await groq.chat.completions.create({
    messages,
    model: options.model || config.ai.model,
    max_tokens: options.maxTokens || config.ai.maxTokens || 1024,
    temperature: options.temperature ?? config.ai.temperature ?? 0.2,
  });

  return completion.choices?.[0]?.message?.content ?? "";
}

// --- OPENAI PROVIDER ---
async function openaiSendMessage(messages, options = {}) {
  const config = getConfig();
  const OpenAI = require("openai");

  const apiKey = config.ai.apiKeys.openai;
  if (!apiKey || apiKey === "YOUR_OPENAI_API_KEY") {
    throw new Error(
      "OPENAI API Key belum diisi! Buka PHRP-AI/config/app.json dan isi ai.apiKeys.openai"
    );
  }

  const openai = new OpenAI({ apiKey });

  const completion = await openai.chat.completions.create({
    messages,
    model: options.model || config.ai.model || "gpt-4o-mini",
    max_tokens: options.maxTokens || config.ai.maxTokens,
    temperature: options.temperature ?? config.ai.temperature,
  });

  return completion.choices?.[0]?.message?.content ?? "";
}

// --- NVIDIA NIM PROVIDER (OpenAI-compatible) ---
async function nvidiaSendMessage(messages, options = {}) {
  const config = getConfig();
  const OpenAI = require("openai");
  const apiKey = config.ai.apiKeys.nvidia;

  if (!apiKey || apiKey === "YOUR_NVIDIA_API_KEY") {
    throw new Error(
      "NVIDIA API Key belum diisi! Buka PHRP-AI/config/app.json dan isi ai.apiKeys.nvidia"
    );
  }

  const nvidia = new OpenAI({
    apiKey,
    baseURL: "https://integrate.api.nvidia.com/v1",
  });

  const completion = await nvidia.chat.completions.create({
    messages,
    model: options.model || config.ai.model || "deepseek-ai/deepseek-v4-flash",
    max_tokens: options.maxTokens || config.ai.maxTokens || 16384,
    temperature: options.temperature ?? config.ai.temperature ?? 0.7,
    top_p: 0.95,
    stream: false,
  });

  // Kadang ada reasoning_content di response
  const msg = completion.choices?.[0]?.message;
  return msg?.content || msg?.reasoning_content || "";
}

// --- CUSTOM PROVIDER (template untuk API endpoint lain) ---
async function customSendMessage(messages, options = {}) {
  const config = getConfig();
  const apiKey = config.ai.apiKeys.custom;

  if (!apiKey || apiKey === "your-custom-api-key-here" || apiKey === "YOUR_CUSTOM_API_KEY") {
    throw new Error(
      "CUSTOM API Key belum diisi! Buka PHRP-AI/config/app.json dan isi ai.apiKeys.custom"
    );
  }

  throw new Error(
    "Custom provider belum diimplementasikan. " +
    "Edit fungsi customSendMessage() di PHRP-AI/utils/aiProvider.js"
  );
}

// ============================================================
// 3. ROUTER — Pilih provider berdasarkan konfigurasi
// ============================================================

const providerMap = {
  groq: groqSendMessage,
  openai: openaiSendMessage,
  nvidia: nvidiaSendMessage,
  custom: customSendMessage,
};

/**
 * Kirim pesan ke AI provider yang aktif.
 * 
 * @param {Array} messages - Array of {role, content} messages
 * @param {Object} options - Opsional override: { model, maxTokens, temperature }
 * @returns {Promise<string>} Response dari AI
 */
async function sendMessage(messages, options = {}) {
  const config = getConfig();
  const providerName = config.ai.activeProvider;
  const provider = providerMap[providerName];

  if (!provider) {
    throw new Error(
      `Provider "${providerName}" tidak dikenal. ` +
      `Pilihan: ${Object.keys(providerMap).join(", ")}\n` +
      `Edit "activeProvider" di PHRP-AI/config/app.json`
    );
  }

  console.log(`[PHRP-AI] Sending to ${providerName}...`);
  return provider(messages, options);
}

/**
 * Ganti provider aktif (runtime).
 * @param {string} providerName - "groq" | "openai" | "custom"
 */
function setProvider(providerName) {
  const config = getConfig();
  if (!providerMap[providerName]) {
    throw new Error(
      `Provider "${providerName}" tidak tersedia. ` +
      `Pilihan: ${Object.keys(providerMap).join(", ")}`
    );
  }

  config.ai.activeProvider = providerName;
  console.log(`[PHRP-AI] AI provider switched to: ${providerName}`);
}

/**
 * Dapatkan nama provider yang sedang aktif.
 */
function getActiveProvider() {
  const config = getConfig();
  return config.ai.activeProvider;
}

/**
 * Daftar provider yang tersedia.
 */
function getAvailableProviders() {
  return Object.keys(providerMap);
}

/**
 * Reload konfigurasi dari file (setelah edit app.json).
 */
function reloadConfig() {
  appConfig = null;
  console.log("[PHRP-AI] Config reloaded from app.json");
}

module.exports = {
  sendMessage,
  setProvider,
  getActiveProvider,
  getAvailableProviders,
  reloadConfig,
};
