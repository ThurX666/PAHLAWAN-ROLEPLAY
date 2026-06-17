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
  for (const file of files) {
    if (isBlockedForSearch(config, file) && !options.includeLogs) continue;
    if (!extensionMatches(file, options.extensions)) continue;
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

export async function findFiles(
  config: AppConfig,
  query: string,
  options: ListFilesOptions = {},
): Promise<Array<{ file: string; size: number }>> {
  const lower = query.toLowerCase();
  const files = await listProjectFiles(config, { ...options, limit: options.limit ? options.limit * 4 : 400 });
  const matches: Array<{ file: string; size: number }> = [];
  for (const file of files) {
    const rel = relativePath(config, file);
    if (rel.toLowerCase().includes(lower)) {
      const stat = await fs.stat(file);
      matches.push({ file: rel, size: stat.size });
      if (options.limit && matches.length >= options.limit) break;
    }
  }
  return matches;
}

export async function searchCode(
  config: AppConfig,
  keyword: string,
  options: ListFilesOptions & { caseSensitive?: boolean; contextLines?: number } = {},
): Promise<SearchHit[]> {
  const files = await listProjectFiles(config, {
    ...options,
    limit: options.limit ? Math.max(options.limit * 10, 100) : 1000,
  });
  const needle = options.caseSensitive ? keyword : keyword.toLowerCase();
  const contextLines = options.contextLines ?? 1;
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
      if (options.limit && hits.length >= options.limit) return hits;
    }
  }
  return hits;
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
