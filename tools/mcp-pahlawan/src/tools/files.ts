import fs from "node:fs";
import fsp from "node:fs/promises";
import path from "node:path";
import { z } from "zod";
import { applyPatch } from "diff";
import type { ToolDefinition } from "../types.js";
import { readTextFileSlice } from "../utils/fileSearch.js";
import { relativePath, safeResolve } from "../utils/pathSafety.js";
import { redactText } from "../utils/redact.js";

function assertWriteAllowed(confirmWrite: boolean, allowWriteFiles: boolean): void {
  if (!confirmWrite) throw new Error("confirmWrite must be true for file writes.");
  if (!allowWriteFiles) throw new Error("MCP_ALLOW_WRITE_FILES is false. File writes are disabled.");
}

export const fileTools: ToolDefinition[] = [
  {
    name: "read_project_file",
    description: "Read a file inside the project directory with path validation and secret redaction.",
    schema: z.object({
      filePath: z.string().min(1),
      startLine: z.number().int().min(1).default(1),
      cursor: z.number().int().min(0).optional(),
      offset: z.number().int().min(0).optional(),
      limit: z.number().int().min(1).max(2000).optional(),
      maxLines: z.number().int().min(1).max(2000).optional(),
      maxBytes: z.number().int().min(512).optional(),
      includeContent: z.boolean().default(false),
      includeSnippets: z.boolean().optional(),
      symbolName: z.string().min(1).optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["filePath"],
      properties: {
        filePath: { type: "string" },
        startLine: { type: "number", default: 1 },
        cursor: { type: "number", description: "Zero-based line offset alias." },
        offset: { type: "number", description: "Zero-based line offset alias." },
        limit: { type: "number", default: 120 },
        maxLines: { type: "number", description: "Deprecated alias for limit." },
        maxBytes: { type: "number" },
        includeContent: { type: "boolean", default: false },
        includeSnippets: { type: "boolean", default: false },
        symbolName: { type: "string" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const fullPath = safeResolve(config, input.filePath);
      let startLine = input.offset !== undefined
        ? input.offset + 1
        : input.cursor !== undefined
          ? input.cursor + 1
          : input.startLine;
      let symbolFound = false;
      if (input.symbolName) {
        const text = await fsp.readFile(fullPath, "utf8");
        const lines = text.split(/\r?\n/);
        const found = lines.findIndex((line) => line.toLowerCase().includes(input.symbolName.toLowerCase()));
        if (found >= 0) {
          startLine = found + 1;
          symbolFound = true;
        }
      }
      const slice = await readTextFileSlice(config, fullPath, {
        startLine,
        maxLines: input.limit ?? input.maxLines,
        maxBytes: input.maxBytes,
        includeContent: input.includeContent,
      });
      const stat = await fsp.stat(fullPath);
      return {
        file: relativePath(config, fullPath),
        metadata: {
          sizeBytes: stat.size,
          modifiedAt: stat.mtime.toISOString(),
          extension: path.extname(fullPath).toLowerCase(),
        },
        mode: input.includeContent ? "bounded-content" : "outline",
        ...(input.symbolName ? { symbolName: input.symbolName, symbolFound } : {}),
        ...slice,
      };
    },
  },
  {
    name: "write_project_patch",
    description: "Apply a small unified patch inside the project only. Requires confirmWrite and MCP_ALLOW_WRITE_FILES=true.",
    schema: z.object({
      filePath: z.string().min(1),
      patch: z.string().min(1),
      confirmWrite: z.boolean().default(false),
    }),
    inputSchema: {
      type: "object",
      required: ["filePath", "patch", "confirmWrite"],
      properties: {
        filePath: { type: "string" },
        patch: { type: "string", description: "Unified diff patch for this single file." },
        confirmWrite: { type: "boolean" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      assertWriteAllowed(input.confirmWrite, config.safety.allowWriteFiles);
      const fullPath = safeResolve(config, input.filePath);
      const before = fs.readFileSync(fullPath, "utf8");
      const patched = applyPatch(before, input.patch);
      if (patched === false) throw new Error("Patch did not apply cleanly.");

      const backupPath = `${fullPath}.bak.${new Date().toISOString().replace(/[:.]/g, "-")}`;
      await fsp.copyFile(fullPath, backupPath);
      await fsp.writeFile(fullPath, patched, "utf8");
      return {
        changedFile: relativePath(config, fullPath),
        backupFile: relativePath(config, backupPath),
        summary: "Patch applied after creating a backup.",
      };
    },
  },
  {
    name: "create_project_file",
    description: "Create a new project file only if it does not already exist. Requires confirmWrite and MCP_ALLOW_WRITE_FILES=true.",
    schema: z.object({
      filePath: z.string().min(1),
      content: z.string().default(""),
      confirmWrite: z.boolean().default(false),
    }),
    inputSchema: {
      type: "object",
      required: ["filePath", "confirmWrite"],
      properties: {
        filePath: { type: "string" },
        content: { type: "string" },
        confirmWrite: { type: "boolean" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      assertWriteAllowed(input.confirmWrite, config.safety.allowWriteFiles);
      const fullPath = safeResolve(config, input.filePath);
      if (fs.existsSync(fullPath)) throw new Error("File already exists.");
      await fsp.mkdir(path.dirname(fullPath), { recursive: true });
      await fsp.writeFile(fullPath, input.content, "utf8");
      return {
        createdFile: relativePath(config, fullPath),
        preview: config.safety.redactSecrets ? redactText(input.content).slice(0, 1000) : input.content.slice(0, 1000),
      };
    },
  },
];
