import fs from "node:fs/promises";
import path from "node:path";
import fg from "fast-glob";
import type { AppConfig } from "../config.js";
import type { ProjectModule } from "../types.js";
import { assertReadableTextFile, isBlockedForSearch, moduleRoot, relativePath } from "./pathSafety.js";
import { redactText } from "./redact.js";

const defaultIgnore = [
  "**/.git/**",
  "**/node_modules/**",
  "**/dist/**",
  "**/dist-ssr/**",
  "**/build/**",
  "**/.cache/**",
  "**/.runtime-logs/**",
  "**/*.amx",
  "**/*.exe",
  "**/*.dll",
  "**/*.so",
  "**/*.zip",
  "**/*.rar",
  "**/*.7z",
  "**/*.png",
  "**/*.jpg",
  "**/*.jpeg",
  "**/*.gif",
  "**/*.webp",
  "**/*.ico",
  "**/*.db",
  "**/*.hmap",
  "**/*.pdb",
];

export interface SearchHit {
  file: string;
  line: number;
  text: string;
  context?: string[];
}

export interface ListFilesOptions {
  module?: ProjectModule;
  extensions?: string[];
  limit?: number;
  includeLogs?: boolean;
  offset?: number;
}

export function extensionMatches(filePath: string, extensions?: string[]): boolean {
  if (!extensions || extensions.length === 0) return true;
  const ext = path.extname(filePath).toLowerCase();
  return extensions.map((item) => item.toLowerCase()).includes(ext);
}

function patternForModule(config: AppConfig, moduleName: ProjectModule): string[] {
  if (moduleName === "all") {
    return ["GAMEMODE/**/*", "WEBSITE/**/*", "BOT/**/*", "DATABASE/**/*", "docs/**/*", "README.md"];
  }
  const root = moduleRoot(config, moduleName);
  const rel = relativePath(config, root);
  return [`${rel}/**/*`];
}

export async function listProjectFiles(config: AppConfig, options: ListFilesOptions = {}): Promise<string[]> {
  const moduleName = options.module ?? "all";
  const files = await fg(patternForModule(config, moduleName), {
    cwd: config.projectRoot,
    absolute: true,
    dot: true,
    onlyFiles: true,
    unique: true,
    ignore: options.includeLogs ? defaultIgnore.filter((item) => !item.includes(".runtime-logs")) : defaultIgnore,
  });

  const filtered: string[] = [];
  const offset = options.offset ?? 0;
  let skipped = 0;
  for (const file of files) {
    if (isBlockedForSearch(config, file) && !options.includeLogs) continue;
    if (!extensionMatches(file, options.extensions)) continue;
    if (skipped < offset) {
      skipped += 1;
      continue;
    }
    filtered.push(file);
    if (options.limit && filtered.length >= options.limit) break;
  }
  return filtered;
}

export async function readTextFile(config: AppConfig, filePath: string): Promise<string> {
  assertReadableTextFile(config, filePath);
  const text = await fs.readFile(filePath, "utf8");
  return config.safety.redactSecrets ? redactText(text) : text;
}

export async function readTextFileSlice(
  config: AppConfig,
  filePath: string,
  options: { startLine?: number; maxLines?: number; maxBytes?: number; includeContent?: boolean } = {},
): Promise<{
  content?: string;
  startLine: number;
  endLine: number;
  totalLines: number;
  nextCursor: number | null;
  outline?: string[];
}> {
  const text = await readTextFile(config, filePath);
  const lines = text.split(/\r?\n/);
  const startLine = Math.max(options.startLine ?? 1, 1);
  const maxLines = Math.min(options.maxLines ?? config.limits.maxFileReadLines, config.limits.maxFileReadLines);
  const startIndex = startLine - 1;
  const endIndex = Math.min(startIndex + maxLines, lines.length);
  const selected = lines.slice(startIndex, endIndex);
  let content = selected.map((line, offset) => `${startLine + offset}: ${line}`).join("\n");
  const maxBytes = options.maxBytes ?? config.safety.maxFileSizeBytes;
  if (Buffer.byteLength(content, "utf8") > maxBytes) {
    content = content.slice(0, maxBytes) + "\n[TRUNCATED_BY_MAX_BYTES]";
  }
  const outline = lines
    .map((line, index) => ({ line, number: index + 1 }))
    .filter(({ line }) =>
      /^\s*(export\s+)?(async\s+)?function\s+/.test(line) ||
      /^\s*(export\s+)?class\s+/.test(line) ||
      /^\s*(public|stock|forward|native)\s+/i.test(line) ||
      /^\s*(CMD|YCMD|COMMAND):/i.test(line) ||
      /^\s*#define\s+/i.test(line) ||
      /^\s*enum\b/i.test(line) ||
      /On[A-Z][A-Za-z0-9_]+\s*\(/.test(line),
    )
    .slice(0, 80)
    .map(({ line, number }) => `${number}: ${line.trim()}`);

  return {
    ...(options.includeContent === false ? {} : { content }),
    startLine,
    endLine: endIndex,
    totalLines: lines.length,
    nextCursor: endIndex < lines.length ? endIndex + 1 : null,
    ...(lines.length > maxLines ? { outline } : {}),
  };
}

export async function findFiles(
  config: AppConfig,
  query: string,
  options: ListFilesOptions = {},
): Promise<Array<{ file: string; size: number }>> {
  const lower = query.toLowerCase();
  const limit = options.limit ?? config.limits.maxSearchResults;
  const files = await listProjectFiles(config, { ...options, limit: limit * 4 });
  const matches: Array<{ file: string; size: number }> = [];
  for (const file of files) {
    const rel = relativePath(config, file);
    if (rel.toLowerCase().includes(lower)) {
      const stat = await fs.stat(file);
      matches.push({ file: rel, size: stat.size });
      if (matches.length >= limit) break;
    }
  }
  return matches;
}

export async function searchCode(
  config: AppConfig,
  keyword: string,
  options: ListFilesOptions & { caseSensitive?: boolean; contextLines?: number } = {},
): Promise<SearchHit[]> {
  const limit = options.limit ?? config.limits.maxSearchResults;
  const candidateLimit = Math.max(limit * 5, limit);
  const files = await listProjectFiles(config, {
    ...options,
    limit: Math.max(limit * 20, 100),
  });
  const needle = options.caseSensitive ? keyword : keyword.toLowerCase();
  const contextLines = Math.min(options.contextLines ?? 1, Math.max(0, Math.floor((config.limits.maxSnippetLines - 1) / 2)));
  const hits: SearchHit[] = [];

  for (const file of files) {
    let text: string;
    try {
      text = await readTextFile(config, file);
    } catch {
      continue;
    }
    const lines = text.split(/\r?\n/);
    for (let index = 0; index < lines.length; index += 1) {
      const line = lines[index] ?? "";
      const haystack = options.caseSensitive ? line : line.toLowerCase();
      if (!haystack.includes(needle)) continue;
      const from = Math.max(0, index - contextLines);
      const to = Math.min(lines.length, index + contextLines + 1);
      hits.push({
        file: relativePath(config, file),
        line: index + 1,
        text: line.trim(),
        context: lines.slice(from, to).map((ctx, offset) => `${from + offset + 1}: ${ctx}`),
      });
      if (hits.length >= candidateLimit) {
        return rankSearchHits(hits, keyword).slice(0, limit);
      }
    }
  }
  return rankSearchHits(hits, keyword).slice(0, limit);
}

function rankSearchHits(hits: SearchHit[], keyword: string): SearchHit[] {
  const lowerKeyword = keyword.toLowerCase();
  const score = (hit: SearchHit): number => {
    const file = hit.file.toLowerCase();
    const text = hit.text.toLowerCase();
    let value = 0;
    if (text === lowerKeyword) value += 10;
    if (text.includes(`${lowerKeyword}(`)) value += 8;
    if (file.includes(lowerKeyword)) value += 6;
    if (/^\s*(public|stock|function|export|class|const|let|var|#define|enum|CMD|YCMD|COMMAND)/i.test(hit.text)) value += 4;
    if (file.includes("/node_modules/") || file.includes("/dist/")) value -= 20;
    return value;
  };
  return [...hits].sort((a, b) => score(b) - score(a) || a.file.localeCompare(b.file) || a.line - b.line);
}

export async function summarizeImportantFiles(config: AppConfig, moduleName: ProjectModule): Promise<string[]> {
  const files = await listProjectFiles(config, { module: moduleName, limit: 500 });
  const important = files
    .map((file) => relativePath(config, file))
    .filter((file) =>
      /(^|\/)(package\.json|index\.(js|ts|tsx)|app\.(js|ts|tsx)|main\.pwn|server\.cfg|config\.(php|ts|js|json)|\.env|README\.md)$/i.test(file) ||
      /\/(commands|events|routes|api|gamemodes|filterscripts|include|includes|plugins)\//i.test(file),
    );
  return important.slice(0, 80);
}
