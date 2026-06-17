import { z } from "zod";
import type { AppConfig } from "./config.js";

export type JsonObject = Record<string, unknown>;

export interface ToolContext {
  config: AppConfig;
}

export interface ToolDefinition {
  name: string;
  description: string;
  inputSchema: JsonObject;
  schema: z.ZodTypeAny;
  handler: (input: any, context: ToolContext) => Promise<unknown> | unknown;
}

export type ProjectModule =
  | "gamemode"
  | "website"
  | "bot"
  | "database"
  | "docs"
  | "logs"
  | "all";

export const moduleSchema = z
  .enum(["gamemode", "website", "bot", "database", "docs", "logs", "all"])
  .default("all");

export function jsonText(data: unknown): string {
  if (typeof data === "string") return data;
  return JSON.stringify(data, null, 2);
}

export function ok(data: unknown): JsonObject {
  return {
    ok: true,
    data,
  };
}

export function fail(message: string, details?: unknown): JsonObject {
  return {
    ok: false,
    error: message,
    ...(details === undefined ? {} : { details }),
  };
}
