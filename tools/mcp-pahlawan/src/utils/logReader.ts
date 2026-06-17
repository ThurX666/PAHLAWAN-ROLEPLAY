import fs from "node:fs/promises";
import path from "node:path";
import fg from "fast-glob";
import type { AppConfig } from "../config.js";
import { safeResolve, relativePath } from "./pathSafety.js";
import { redactText } from "./redact.js";

const logPatterns: Record<string, string[]> = {
  gamemode: ["GAMEMODE/**/*.log", "GAMEMODE/**/*_log.txt", "GAMEMODE/**/server_log.txt", "GAMEMODE/**/svlog.txt"],
  crashdetect: ["GAMEMODE/**/crash*.log", "GAMEMODE/**/crashdetect*.txt"],
  mysql: ["GAMEMODE/**/*mysql*.log", "WEBSITE/**/*mysql*.log", "BOT/**/*mysql*.log"],
  ucp: ["WEBSITE/**/*.log", "WEBSITE/.runtime-logs/*.log"],
  bot: ["BOT/**/*.log"],
  all: ["GAMEMODE/**/*.log", "GAMEMODE/**/*.txt", "WEBSITE/**/*.log", "BOT/**/*.log"],
};

export async function readRecentLogs(
  config: AppConfig,
  filter: keyof typeof logPatterns,
  options: {
    maxBytes?: number;
    maxLines?: number;
    level?: "error" | "warn" | "all";
    keyword?: string;
    since?: string;
    includeInfo?: boolean;
    cursor?: number;
    offset?: number;
  } = {},
): Promise<unknown> {
  const patterns = logPatterns[filter] ?? logPatterns.all;
  const files = await fg(patterns, {
    cwd: config.projectRoot,
    absolute: true,
    onlyFiles: true,
    dot: true,
    ignore: ["**/node_modules/**", "**/.git/**", "**/dist/**"],
  });

  const stats = await Promise.all(files.map(async (file) => ({ file, stat: await fs.stat(file) })));
  stats.sort((a, b) => b.stat.mtimeMs - a.stat.mtimeMs);
  const maxLines = Math.min(options.maxLines ?? config.limits.maxLogLines, config.limits.maxLogLines);
  const maxBytes = Math.min(options.maxBytes ?? 12_000, 65_536);
  const sinceMs = options.since ? Date.parse(options.since) : Number.NaN;
  const keyword = options.keyword?.toLowerCase();
  const collected: Array<{ file: string; modifiedAt: string; line: string }> = [];
  for (const { file, stat } of stats.slice(0, 20)) {
    if (Number.isFinite(sinceMs) && stat.mtimeMs < sinceMs) continue;
    const fullPath = safeResolve(config, file);
    const handle = await fs.open(fullPath, "r");
    try {
      const bytes = Math.min(stat.size, maxBytes);
      const buffer = Buffer.alloc(bytes);
      await handle.read(buffer, 0, bytes, Math.max(0, stat.size - bytes));
      const rawText = config.safety.redactSecrets ? redactText(buffer.toString("utf8")) : buffer.toString("utf8");
      const lines = rawText.split(/\r?\n/);
      for (const line of lines) {
        const isError = /error|fatal|exception|crash|failed/i.test(line);
        const isWarn = /warn|warning/i.test(line);
        const relevantLevel = options.includeInfo || options.level === "all"
          ? true
          : options.level === "error"
            ? isError
            : isError || isWarn;
        if (!relevantLevel || (keyword && !line.toLowerCase().includes(keyword))) continue;
        collected.push({
          file: relativePath(config, fullPath),
          modifiedAt: stat.mtime.toISOString(),
          line: line.trim().slice(0, 1_000),
        });
      }
    } finally {
      await handle.close();
    }
  }
  const offset = Math.max(options.offset ?? options.cursor ?? 0, 0);
  const recent = collected.reverse().slice(offset, offset + maxLines + 1);
  const page = recent.slice(0, maxLines);
  const grouped = new Map<string, { message: string; count: number; files: Set<string>; latestModifiedAt: string }>();
  for (const entry of page) {
    const key = entry.line
      .replace(/\b\d{4}-\d{2}-\d{2}[T ][0-9:.+-Z]+\b/g, "[timestamp]")
      .replace(/\b\d+\b/g, "#");
    const existing = grouped.get(key);
    if (existing) {
      existing.count += 1;
      existing.files.add(entry.file);
      if (entry.modifiedAt > existing.latestModifiedAt) existing.latestModifiedAt = entry.modifiedAt;
    } else {
      grouped.set(key, {
        message: entry.line,
        count: 1,
        files: new Set([entry.file]),
        latestModifiedAt: entry.modifiedAt,
      });
    }
  }
  return {
    filter,
    level: options.level ?? "warn",
    keyword: options.keyword ?? null,
    groups: [...grouped.values()].map((group) => ({
      message: group.message,
      count: group.count,
      files: [...group.files].slice(0, 5),
      latestModifiedAt: group.latestModifiedAt,
    })),
    matchedLines: page.length,
    offset,
    limit: maxLines,
    truncated: recent.length > maxLines,
    nextCursor: recent.length > maxLines ? offset + page.length : null,
    omitted: "Informational lines are omitted by default; duplicate warning/error messages are grouped.",
  };
}

export async function listLogCandidates(config: AppConfig): Promise<string[]> {
  const files = await fg(logPatterns.all, {
    cwd: config.projectRoot,
    absolute: true,
    onlyFiles: true,
    dot: true,
    ignore: ["**/node_modules/**", "**/.git/**", "**/dist/**"],
  });
  return files.slice(0, 50).map((file) => relativePath(config, file));
}
