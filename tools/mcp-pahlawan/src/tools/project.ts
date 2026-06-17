import fs from "node:fs";
import path from "node:path";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { moduleSchema } from "../types.js";
import { findFiles, listProjectFiles, summarizeImportantFiles } from "../utils/fileSearch.js";
import { boundedLimit, pageItems, resolveOffset } from "../utils/pagination.js";
import { relativePath } from "../utils/pathSafety.js";

function exists(target: string): boolean {
  return fs.existsSync(target);
}

async function countByExtension(files: string[]): Promise<Record<string, number>> {
  const counts: Record<string, number> = {};
  for (const file of files) {
    const ext = path.extname(file).toLowerCase() || "(none)";
    counts[ext] = (counts[ext] ?? 0) + 1;
  }
  return counts;
}

export const projectTools: ToolDefinition[] = [
  {
    name: "project_overview",
    description: "Detect and summarize PAHLAWAN ROLEPLAY project structure.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const modules = {
        gamemode: exists(config.dirs.gamemode),
        website: exists(config.dirs.website),
        bot: exists(config.dirs.bot),
        database: exists(config.dirs.database),
        docs: exists(path.join(config.projectRoot, "docs")),
      };
      const files = await listProjectFiles(config, { module: "all", limit: 500 });
      return {
        projectRoot: config.projectRoot,
        modules,
        fileCountSampled: files.length,
        samplingNote: "Extension counts are based on a bounded 500-file sample.",
        extensionSummary: await countByExtension(files),
        importantFiles: {
          gamemode: await summarizeImportantFiles(config, "gamemode"),
          website: await summarizeImportantFiles(config, "website"),
          bot: await summarizeImportantFiles(config, "bot"),
          database: await summarizeImportantFiles(config, "database"),
        },
        safety: {
          writeFilesEnabled: config.safety.allowWriteFiles,
          writeDbEnabled: config.safety.allowWriteDb,
          maxFileSizeBytes: config.safety.maxFileSizeBytes,
          redactionEnabled: config.safety.redactSecrets,
        },
      };
    },
  },
  {
    name: "list_project_modules",
    description: "List detected project modules and important files per module.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const modules = [
        { name: "gamemode", root: config.dirs.gamemode },
        { name: "website", root: config.dirs.website },
        { name: "bot", root: config.dirs.bot },
        { name: "database", root: config.dirs.database },
        { name: "logs", root: config.dirs.logs },
        { name: "docs", root: path.join(config.projectRoot, "docs") },
      ];
      return Promise.all(
        modules.map(async (moduleInfo) => ({
          ...moduleInfo,
          exists: exists(moduleInfo.root),
          relativeRoot: exists(moduleInfo.root) ? relativePath(config, moduleInfo.root) : null,
          importantFiles: exists(moduleInfo.root)
            ? await summarizeImportantFiles(config, moduleInfo.name as never)
            : [],
        })),
      );
    },
  },
  {
    name: "find_project_file",
    description: "Find files by name, extension, or keyword while ignoring dependencies, git, builds, caches, and binaries.",
    schema: z.object({
      query: z.string().min(1),
      module: moduleSchema,
      extension: z.string().optional(),
      limit: z.number().int().min(1).max(200).optional(),
      maxResults: z.number().int().min(1).max(200).optional(),
      cursor: z.number().int().min(0).default(0),
      offset: z.number().int().min(0).optional(),
    }),
    inputSchema: {
      type: "object",
      required: ["query"],
      properties: {
        query: { type: "string" },
        module: { type: "string", enum: ["gamemode", "website", "bot", "database", "docs", "logs", "all"] },
        extension: { type: "string" },
        limit: { type: "number", default: 10 },
        maxResults: { type: "number", description: "Deprecated alias for limit." },
        cursor: { type: "number", default: 0 },
        offset: { type: "number" },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const extensions = input.extension ? [input.extension.startsWith(".") ? input.extension : `.${input.extension}`] : undefined;
      const limit = boundedLimit(input.limit ?? input.maxResults, config.limits.maxSearchResults, config.limits.maxSearchResults);
      const offset = resolveOffset(input.cursor, input.offset);
      const items = await findFiles(config, input.query, {
        module: input.module,
        extensions,
        limit: limit + 1,
        offset,
      });
      return pageItems(items, offset, limit, items.length > limit);
    },
  },
];
