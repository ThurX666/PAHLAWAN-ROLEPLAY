import type { ToolDefinition } from "../types.js";
import { botTools } from "./bot.js";
import { codeSearchTools } from "./codeSearch.js";
import { clientTools } from "./clients.js";
import { databaseTools } from "./database.js";
import { diagnosticTools } from "./diagnostics.js";
import { fileTools } from "./files.js";
import { gamemodeTools } from "./gamemode.js";
import { logTools } from "./logs.js";
import { projectTools } from "./project.js";
import { ucpTools } from "./ucp.js";
import { workflowTools } from "./workflow.js";

export const tools: ToolDefinition[] = [
  ...projectTools,
  ...clientTools,
  ...diagnosticTools,
  ...codeSearchTools,
  ...fileTools,
  ...gamemodeTools,
  ...ucpTools,
  ...botTools,
  ...databaseTools,
  ...logTools,
  ...workflowTools,
];
