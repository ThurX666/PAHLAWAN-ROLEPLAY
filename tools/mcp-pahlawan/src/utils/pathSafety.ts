import fs from "node:fs";
import path from "node:path";
import type { AppConfig } from "../config.js";

const blockedSegments = new Set([
  ".git",
  "node_modules",
  "dist",
  "dist-ssr",
  "build",
  ".cache",
  ".runtime-logs",
  "__pycache__",
]);

export const binaryExtensions = new Set([
  ".amx",
  ".dll",
  ".exe",
  ".so",
  ".zip",
  ".rar",
  ".7z",
  ".png",
  ".jpg",
  ".jpeg",
  ".gif",
  ".webp",
  ".ico",
  ".db",
  ".hmap",
  ".pdb",
]);

export function normalizeSlashes(value: string): string {
  return value.replace(/\\/g, "/");
}

export function assertInsideRoot(root: string, target: string): string {
  const resolvedRoot = path.resolve(root);
  const resolvedTarget = path.resolve(target);
  const relative = path.relative(resolvedRoot, resolvedTarget);
  if (relative === "" || (!relative.startsWith("..") && !path.isAbsolute(relative))) {
    return resolvedTarget;
  }
  throw new Error(`Blocked path outside project root: ${target}`);
}

export function safeResolve(config: AppConfig, inputPath: string): string {
  if (!inputPath || inputPath.includes("\0")) {
    throw new Error("Invalid path");
  }

  const segments = inputPath.split(/[\\/]+/);
  if (segments.includes("..")) {
    throw new Error("Blocked path traversal");
  }

  const resolved = path.isAbsolute(inputPath)
    ? path.resolve(inputPath)
    : path.resolve(config.projectRoot, inputPath);
  return assertInsideRoot(config.projectRoot, resolved);
}

export function relativePath(config: AppConfig, fullPath: string): string {
  return normalizeSlashes(path.relative(config.projectRoot, fullPath));
}

export function isBlockedForSearch(config: AppConfig, fullPath: string): boolean {
  const rel = relativePath(config, fullPath);
  const segments = rel.split("/");
  if (segments.some((segment) => blockedSegments.has(segment))) return true;
  return binaryExtensions.has(path.extname(fullPath).toLowerCase());
}

export function assertReadableTextFile(config: AppConfig, fullPath: string): void {
  assertInsideRoot(config.projectRoot, fullPath);
  const stat = fs.statSync(fullPath);
  if (!stat.isFile()) throw new Error("Path is not a file");
  if (stat.size > config.safety.maxFileSizeBytes) {
    throw new Error(`File is too large (${stat.size} bytes)`);
  }
  if (binaryExtensions.has(path.extname(fullPath).toLowerCase())) {
    throw new Error("Binary file reading is blocked");
  }
}

export function moduleRoot(config: AppConfig, moduleName: string): string {
  switch (moduleName) {
    case "gamemode":
      return config.dirs.gamemode;
    case "website":
      return config.dirs.website;
    case "bot":
      return config.dirs.bot;
    case "database":
      return config.dirs.database;
    case "logs":
      return config.dirs.logs;
    case "docs":
      return path.join(config.projectRoot, "docs");
    default:
      return config.projectRoot;
  }
}
