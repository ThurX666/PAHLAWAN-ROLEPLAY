import fs from "node:fs";
import path from "node:path";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { compileGamemode, parseCompileLog } from "../utils/compileRunner.js";
import { findFiles, listProjectFiles, searchCode } from "../utils/fileSearch.js";
import { relativePath } from "../utils/pathSafety.js";

const pawnExt = [".pwn", ".inc"];

export const gamemodeTools: ToolDefinition[] = [
  {
    name: "gamemode_overview",
    description: "Detect main Pawn file, includes, filterscripts, plugins, config files, and major systems.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const pawnFiles = await listProjectFiles(config, { module: "gamemode", extensions: [".pwn"], limit: 40 });
      const includeFiles = await listProjectFiles(config, { module: "gamemode", extensions: [".inc"], limit: 60 });
      const plugins = fs.existsSync(path.join(config.dirs.gamemode, "plugins"))
        ? fs.readdirSync(path.join(config.dirs.gamemode, "plugins")).slice(0, config.limits.maxSearchResults)
        : [];
      const systems = ["login", "register", "spawn", "business", "auction", "bid", "faction", "job", "inventory", "vehicle", "TextDraw", "mysql", "discord"];
      const detectedSystems = [];
      for (const system of systems) {
        const hits = await searchCode(config, system, { module: "gamemode", extensions: pawnExt, limit: 2, contextLines: 0 });
        if (hits.length > 0) detectedSystems.push({ system, hitCountSample: hits.length, topHit: hits[0] });
      }
      return {
        mainCandidates: pawnFiles.filter((file) => /gamemodes[\\/](main|.*gamemode).*\.pwn$/i.test(file)).map((file) => relativePath(config, file)),
        pawnFileSamples: pawnFiles.map((file) => relativePath(config, file)).slice(0, config.limits.maxSearchResults),
        includeCount: includeFiles.length,
        includeSamples: includeFiles.map((file) => relativePath(config, file)).slice(0, config.limits.maxSearchResults),
        filterscripts: await findFiles(config, "filterscripts", { module: "gamemode", extensions: [".pwn"], limit: config.limits.maxSearchResults }),
        plugins,
        configFiles: await findFiles(config, "server.cfg", { module: "gamemode", limit: 10 }),
        detectedSystems,
      };
    },
  },
  {
    name: "compile_gamemode",
    description: "Run the configured Pawn compiler only. Requires PAWN_COMPILER_PATH and optional PAWN_COMPILE_ARGS.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    handler(_input, { config }) {
      return compileGamemode(config);
    },
  },
  {
    name: "parse_pawn_compile_log",
    description: "Parse Pawn compile output or a compile log file into warnings/errors and line references.",
    schema: z.object({
      content: z.string().optional(),
      filePath: z.string().optional(),
    }),
    inputSchema: {
      type: "object",
      properties: {
        content: { type: "string" },
        filePath: { type: "string" },
      },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return parseCompileLog(config, input);
    },
  },
  {
    name: "analyze_pawn_callback_flow",
    description: "Find related Pawn callbacks and summarize flow for login, spawn, business menu, auction, TextDraw, etc.",
    schema: z.object({
      topic: z.string().min(1),
      limit: z.number().int().min(1).max(100).default(10),
    }),
    inputSchema: {
      type: "object",
      required: ["topic"],
      properties: {
        topic: { type: "string" },
        limit: { type: "number", default: 10 },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const callbacks = [
        "OnPlayerConnect",
        "OnPlayerRequestClass",
        "OnPlayerSpawn",
        "OnDialogResponse",
        "OnPlayerDisconnect",
        "OnGameModeInit",
        "OnPlayerCommandText",
      ];
      const limit = Math.min(input.limit, config.limits.maxSearchResults);
      const topicHits = await searchCode(config, input.topic, { module: "gamemode", extensions: pawnExt, limit, contextLines: 1 });
      const callbackHits = [];
      for (const callback of callbacks) {
        callbackHits.push({
          callback,
          hits: await searchCode(config, callback, { module: "gamemode", extensions: pawnExt, limit: 2, contextLines: 0 }),
        });
      }
      return {
        topic: input.topic,
        topicHits,
        callbackHits: callbackHits.filter((item) => item.hits.length > 0),
        risks: [
          "Verify callback order before patching login/spawn flow.",
          "Inspect MySQL callback functions before changing async behavior.",
          "Avoid adding unavailable Pawn natives; check includes first.",
        ],
      };
    },
  },
  {
    name: "find_dialog_ids",
    description: "Search dialog IDs, dialog names, ShowPlayerDialog calls, and OnDialogResponse branches.",
    schema: z.object({
      keyword: z.string().optional(),
      limit: z.number().int().min(1).max(200).default(10),
    }),
    inputSchema: {
      type: "object",
      properties: {
        keyword: { type: "string" },
        limit: { type: "number", default: 10 },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms = input.keyword ? [input.keyword] : ["DIALOG_", "ShowPlayerDialog", "OnDialogResponse", "dialogid"];
      const limit = Math.min(input.limit, config.limits.maxSearchResults);
      const results = [];
      for (const term of terms) {
        results.push({
          term,
          hits: await searchCode(config, term, { module: "gamemode", extensions: pawnExt, limit, contextLines: 1 }),
        });
      }
      return results;
    },
  },
  {
    name: "find_textdraw_usage",
    description: "Search TextDraw creation/show/hide/update logic to avoid duplicated UI updates and flicker.",
    schema: z.object({
      keyword: z.string().default("TextDraw"),
      limit: z.number().int().min(1).max(200).default(10),
    }),
    inputSchema: {
      type: "object",
      properties: {
        keyword: { type: "string", default: "TextDraw" },
        limit: { type: "number", default: 10 },
      },
      additionalProperties: false,
    },
    async handler(input, { config }) {
      const terms = Array.from(new Set([input.keyword, "TextDrawCreate", "TextDrawShowForPlayer", "TextDrawHideForPlayer", "PlayerTextDraw"]));
      const limit = Math.min(input.limit, config.limits.maxSearchResults);
      const results = [];
      for (const term of terms) {
        results.push({
          term,
          hits: await searchCode(config, term, { module: "gamemode", extensions: pawnExt, limit, contextLines: 0 }),
        });
      }
      return results;
    },
  },
];
