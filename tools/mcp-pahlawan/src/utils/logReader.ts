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
  maxBytes: number,
): Promise<unknown> {
  const patterns = logPatterns[filter] ?? logPatterns.all;
  const files = await fg(patterns, {
    cwd: config.projectRoot,
    absolute: true,
    onlyFiles: true,
    dot: true,
    ignore: ["**/node_modules/**", "**/.git/**", "**/dist/**"],
  });

  const entries = [];
  for (const file of files.slice(0, 20)) {
    const fullPath = safeResolve(config, file);
    const stat = await fs.stat(fullPath);
    const handle = await fs.open(fullPath, "r");
    try {
      const bytes = Math.min(stat.size, maxBytes);
      const buffer = Buffer.alloc(bytes);
      await handle.read(buffer, 0, bytes, Math.max(0, stat.size - bytes));
      const text = config.safety.redactSecrets ? redactText(buffer.toString("utf8")) : buffer.toString("utf8");
      entries.push({
        file: relativePath(config, fullPath),
        size: stat.size,
        modifiedAt: stat.mtime.toISOString(),
        tail: text,
        warnings: text.split(/\r?\n/).filter((line) => /warn|error|fatal|exception|crash|failed/i.test(line)).slice(-30),
      });
    } finally {
      await handle.close();
    }
  }
  return entries;
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
