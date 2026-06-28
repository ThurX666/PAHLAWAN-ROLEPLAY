import fs from "node:fs";
import path from "node:path";
import type { AppConfig } from "../config.js";
import { normalizeSlashes } from "./pathSafety.js";

export interface OpenSpecTask {
  id: string;
  text: string;
  completed: boolean;
  blocked: boolean;
}

function readOptional(filePath: string): string {
  return fs.existsSync(filePath) ? fs.readFileSync(filePath, "utf8") : "";
}

function section(markdown: string, heading: string): string {
  const lines = markdown.split(/\r?\n/);
  const start = lines.findIndex((line) => line.trim().toLowerCase() === `## ${heading}`.toLowerCase());
  if (start < 0) return "";
  const collected: string[] = [];
  for (let index = start + 1; index < lines.length; index++) {
    if (/^##\s+/.test(lines[index])) break;
    collected.push(lines[index]);
  }
  return collected.join("\n").trim();
}

function compactText(value: string, max = 500): string {
  const normalized = value.replace(/<!--[\s\S]*?-->/g, "").replace(/\s+/g, " ").trim();
  return normalized.length > max ? `${normalized.slice(0, max - 1)}…` : normalized;
}

function markdownFiles(root: string): string[] {
  if (!fs.existsSync(root)) return [];
  const result: string[] = [];
  const visit = (current: string) => {
    for (const entry of fs.readdirSync(current, { withFileTypes: true })) {
      const fullPath = path.join(current, entry.name);
      if (entry.isDirectory()) visit(fullPath);
      else if (entry.isFile() && entry.name.endsWith(".md")) result.push(fullPath);
    }
  };
  visit(root);
  return result.sort();
}

export function openspecRoot(config: AppConfig): string {
  return path.join(config.projectRoot, "openspec");
}

export function listActiveOpenSpecChangeIds(config: AppConfig): string[] {
  const changesRoot = path.join(openspecRoot(config), "changes");
  if (!fs.existsSync(changesRoot)) return [];
  return fs.readdirSync(changesRoot, { withFileTypes: true })
    .filter((entry) => entry.isDirectory() && entry.name !== "archive")
    .map((entry) => entry.name)
    .sort();
}

export function parseOpenSpecTasks(markdown: string): OpenSpecTask[] {
  // Flexible regex menerima:
  //   - [ ] Task text           (tanpa ID)
  //   - [x] Task text           (completed tanpa ID)
  //   - [ ] 1.1 Task text       (numeric ID)
  //   - [ ] 1.1. Task text      (numeric ID + trailing dot)
  //   - [ ] **1.1** Task text   (bold ID)
  //   * [ ] Task text           (asterisk markdown)
  const CHECK_RE = /^\s*[-*]\s+\[([ xX])\]\s+(?:(?:\*\*)?(\d+(?:\.\d+)*)(?:\*\*)?\.?\s+)?(.+)$/;

  const BLOCKED_RE = /\b(?:blocked|blokir|terblokir|menunggu)\b/i;

  let autoId = 0;

  return markdown.split(/\r?\n/).flatMap((line) => {
    const match = line.match(CHECK_RE);
    if (!match) return [];
    const text = match[3].trim();
    autoId++;
    return [{
      id: match[2] ?? `task-${autoId}`,
      text,
      completed: match[1].toLowerCase() === "x",
      blocked: BLOCKED_RE.test(text),
    }];
  });
}

export function summarizeOpenSpecChange(config: AppConfig, changeId: string) {
  if (!/^[a-z0-9][a-z0-9-]*$/.test(changeId)) throw new Error("Invalid OpenSpec change ID.");
  const root = path.join(openspecRoot(config), "changes", changeId);
  if (!fs.existsSync(root)) throw new Error(`OpenSpec change not found: ${changeId}`);

  const proposal = readOptional(path.join(root, "proposal.md"));
  const design = readOptional(path.join(root, "design.md"));
  const tasksMarkdown = readOptional(path.join(root, "tasks.md"));
  const specFiles = markdownFiles(path.join(root, "specs"));
  const specs = specFiles.map((file) => readOptional(file));
  const requirements = specs.flatMap((markdown, fileIndex) =>
    Array.from(markdown.matchAll(/^### Requirement:\s*(.+)$/gmi)).map((match) => ({
      id: match[1].trim().toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-|-$/g, ""),
      title: match[1].trim(),
      path: normalizeSlashes(path.relative(config.projectRoot, specFiles[fileIndex])),
    })),
  );
  const tasks = parseOpenSpecTasks(tasksMarkdown);

  return {
    changeId,
    root: normalizeSlashes(path.relative(config.projectRoot, root)),
    proposalSummary: compactText(section(proposal, "Why") || proposal),
    changesSummary: compactText(section(proposal, "What Changes")),
    requirements,
    tasks,
    taskCounts: {
      completed: tasks.filter((task) => task.completed).length,
      pending: tasks.filter((task) => !task.completed && !task.blocked).length,
      blocked: tasks.filter((task) => task.blocked && !task.completed).length,
    },
    designNotes: compactText(section(design, "Decisions") || design),
    risks: compactText(section(design, "Risks / Trade-offs")),
    paths: {
      proposal: fs.existsSync(path.join(root, "proposal.md")) ? `${normalizeSlashes(path.relative(config.projectRoot, root))}/proposal.md` : null,
      design: fs.existsSync(path.join(root, "design.md")) ? `${normalizeSlashes(path.relative(config.projectRoot, root))}/design.md` : null,
      tasks: fs.existsSync(path.join(root, "tasks.md")) ? `${normalizeSlashes(path.relative(config.projectRoot, root))}/tasks.md` : null,
      specs: specFiles.map((file) => normalizeSlashes(path.relative(config.projectRoot, file))),
    },
    sourceOfTruth: "OpenSpec defines approved planning and requirements; MCP provides context and validation support.",
  };
}

function queryTerms(value: string): string[] {
  return Array.from(new Set(value.toLowerCase().split(/[^a-z0-9_]+/).filter((term) => term.length > 2))).slice(0, 12);
}

export function findRelatedOpenSpecChanges(config: AppConfig, query: string, limit = 5) {
  const terms = queryTerms(query);
  return listActiveOpenSpecChangeIds(config)
    .map((changeId) => {
      const summary = summarizeOpenSpecChange(config, changeId);
      const searchable = JSON.stringify(summary).toLowerCase();
      const matchedTerms = terms.filter((term) => searchable.includes(term));
      return { ...summary, matchedTerms, score: matchedTerms.length };
    })
    .filter((change) => change.score > 0)
    .sort((a, b) => b.score - a.score || a.changeId.localeCompare(b.changeId))
    .slice(0, limit);
}

export function listMainOpenSpecSpecs(config: AppConfig): string[] {
  return markdownFiles(path.join(openspecRoot(config), "specs"))
    .map((file) => normalizeSlashes(path.relative(config.projectRoot, file)));
}
