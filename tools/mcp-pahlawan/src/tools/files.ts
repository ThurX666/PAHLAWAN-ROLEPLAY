import fs from "node:fs";
import fsp from "node:fs/promises";
import path from "node:path";
import { z } from "zod";
import { applyPatch } from "diff";
import type { ToolDefinition } from "../types.js";
import { readTextFile } from "../utils/fileSearch.js";
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
    }),
    inputSchema: {
      type: "object",
      required: ["filePath"],
      properties: {
        filePath: { type: "string" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const fullPath = safeResolve(config, input.filePath);
      const content = await readTextFile(config, fullPath);
      return {
        file: relativePath(config, fullPath),
        content,
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
