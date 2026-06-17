import type { AppConfig } from "../config.js";
import { jsonText } from "../types.js";
import { isCompactMode, recordOutputMetric } from "./runtimeState.js";

interface ShrinkOptions {
  arrayLimit: number;
  stringLimit: number;
  depthLimit: number;
}

function shrinkValue(value: unknown, options: ShrinkOptions, depth = 0): unknown {
  if (typeof value === "string") {
    return value.length > options.stringLimit
      ? `${value.slice(0, options.stringLimit)}… [${value.length - options.stringLimit} chars omitted]`
      : value;
  }
  if (Array.isArray(value)) {
    const items = value
      .slice(0, options.arrayLimit)
      .map((item) => shrinkValue(item, options, depth + 1));
    if (value.length > options.arrayLimit) {
      items.push({ omittedItems: value.length - options.arrayLimit });
    }
    return items;
  }
  if (value && typeof value === "object") {
    if (depth >= options.depthLimit) return "[nested details omitted]";
    return Object.fromEntries(
      Object.entries(value).map(([key, item]) => [key, shrinkValue(item, options, depth + 1)]),
    );
  }
  return value;
}

function truncationEnvelope(toolName: string, data: unknown, config: AppConfig, originalChars: number, compact: boolean): string {
  const levels: ShrinkOptions[] = [
    { arrayLimit: Math.min(config.limits.maxSearchResults, compact ? 5 : 10), stringLimit: compact ? 500 : 800, depthLimit: 5 },
    { arrayLimit: 2, stringLimit: 240, depthLimit: 4 },
    { arrayLimit: 1, stringLimit: 120, depthLimit: 3 },
  ];
  for (const options of levels) {
    const text = jsonText({
      truncated: true,
      tool: toolName,
      maxOutputChars: config.limits.maxOutputChars,
      originalChars,
      omitted: "Nested details, long strings, or additional results were omitted to protect the model context window.",
      suggestedNextToolCall: `Re-run ${toolName} with a narrower keyword/module, lower limit, or nextCursor.`,
      data: shrinkValue(data, options),
    });
    if (text.length <= config.limits.maxOutputChars) return text;
  }
  return jsonText({
    truncated: true,
    tool: toolName,
    maxOutputChars: config.limits.maxOutputChars,
    originalChars,
    omitted: "Result was too large to return safely.",
    suggestedNextToolCall: `Re-run ${toolName} with a narrower filter and limit <= 5.`,
  });
}

export function applyOutputBudget(toolName: string, result: unknown, config: AppConfig): string {
  const compact = isCompactMode(config);
  const text = jsonText(result);
  const truncated = text.length > config.limits.maxOutputChars;
  const output = truncated
    ? truncationEnvelope(toolName, result, config, text.length, compact)
    : text;
  recordOutputMetric({
    tool: toolName,
    outputChars: output.length,
    truncated,
    at: new Date().toISOString(),
  });
  return output;
}
