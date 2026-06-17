import fs from "node:fs";
import path from "node:path";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { findFiles, listProjectFiles, searchCode } from "../utils/fileSearch.js";
import { relativePath } from "../utils/pathSafety.js";

function maybePackage(root: string): unknown {
  const packagePath = path.join(root, "package.json");
  if (!fs.existsSync(packagePath)) return null;
  return JSON.parse(fs.readFileSync(packagePath, "utf8"));
}

export const botTools: ToolDefinition[] = [
  {
    name: "bot_overview",
    description: "Detect Discord bot entry file, command/event folders, DB connector, config, and features.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const pkg = maybePackage(config.dirs.bot) as { main?: string; scripts?: Record<string, string>; dependencies?: Record<string, string> } | null;
      const jsFiles = await listProjectFiles(config, { module: "bot", extensions: [".js", ".cjs", ".mjs", ".ts"], limit: 300 });
      return {
        package: pkg,
        entryCandidates: [
          ...(pkg?.main ? [pkg.main] : []),
          ...jsFiles.filter((file) => /(^|[\\/])(index|bot|main)\.(js|ts|cjs|mjs)$/i.test(file)).map((file) => relativePath(config, file)),
        ],
        commandFolders: await findFiles(config, "command", { module: "bot", limit: 60 }),
        eventFolders: await findFiles(config, "event", { module: "bot", limit: 60 }),
        configCandidates: await findFiles(config, "config", { module: "bot", limit: 80 }),
        dbHits: await searchCode(config, "mysql", { module: "bot", extensions: [".js", ".ts", ".json"], limit: 50 }),
        discordHits: await searchCode(config, "discord", { module: "bot", extensions: [".js", ".ts", ".json"], limit: 50 }),
      };
    },
  },
  {
    name: "list_discord_commands",
    description: "List slash/prefix command candidates with file path and command declarations.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const patterns = ["SlashCommandBuilder", ".setName(", "name:", "commandName", "prefix", "client.on('message", 'client.on("message'];
      const results = [];
      for (const pattern of patterns) {
        results.push({
          pattern,
          hits: await searchCode(config, pattern, { module: "bot", extensions: [".js", ".ts", ".json"], limit: 60, contextLines: 1 }),
        });
      }
      return results;
    },
  },
  {
    name: "analyze_discord_interaction_flow",
    description: "Analyze Discord interaction defer/reply/editReply logic for Unknown interaction and double reply issues.",
    schema: z.object({
      keyword: z.string().default("interaction"),
    }),
    inputSchema: {
      type: "object",
      properties: { keyword: { type: "string", default: "interaction" } },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms = Array.from(new Set([input.keyword, "deferReply", "reply(", "editReply", "followUp", "replied", "deferred", "interactionCreate"]));
      const results = [];
      for (const term of terms) {
        results.push({
          term,
          hits: await searchCode(config, term, { module: "bot", extensions: [".js", ".ts"], limit: 80, contextLines: 2 }),
        });
      }
      return {
        results,
        checklist: [
          "Defer within 3 seconds for slow commands.",
          "Do not call reply twice on the same interaction.",
          "Use editReply after deferReply.",
          "Guard long DB/API calls with try/catch and final user response.",
          "Check permission failures before executing command logic.",
        ],
      };
    },
  },
  {
    name: "generate_bot_feature_plan",
    description: "Generate a safe implementation plan for a Discord bot feature request without editing files.",
    schema: z.object({
      feature: z.string().min(2),
    }),
    inputSchema: {
      type: "object",
      required: ["feature"],
      properties: { feature: { type: "string" } },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const related = await searchCode(config, input.feature, { module: "bot", extensions: [".js", ".ts", ".json"], limit: 60, contextLines: 1 });
      return {
        feature: input.feature,
        related,
        plan: [
          "Find existing command/event structure.",
          "Reuse existing config and DB connector.",
          "Define interaction timing: reply, deferReply, editReply, or followUp.",
          "Add permission and role checks before side effects.",
          "Test with a local command or dry-run path before production.",
        ],
        risks: [
          "Unknown interaction from slow command without deferReply.",
          "Double reply if error handler replies after success path.",
          "Role sync mistakes if guild/member cache is stale.",
        ],
      };
    },
  },
];
