import type { AppConfig } from "../config.js";

export interface OutputMetric {
  tool: string;
  outputChars: number;
  truncated: boolean;
  at: string;
}

let compactModeOverride: boolean | undefined;
const outputMetrics = new Map<string, OutputMetric>();

export function isCompactMode(config: AppConfig): boolean {
  return compactModeOverride ?? config.defaults.compactMode;
}

export function setCompactMode(enabled: boolean): boolean {
  compactModeOverride = enabled;
  return enabled;
}

export function recordOutputMetric(metric: OutputMetric): void {
  outputMetrics.set(metric.tool, metric);
}

export function getOutputMetrics(): OutputMetric[] {
  return [...outputMetrics.values()].sort((a, b) => b.at.localeCompare(a.at));
}
