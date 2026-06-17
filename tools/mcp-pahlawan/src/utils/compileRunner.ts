import { spawn } from "node:child_process";
import fs from "node:fs";
import path from "node:path";
import type { AppConfig } from "../config.js";
import { safeResolve, relativePath } from "./pathSafety.js";
import { redactText } from "./redact.js";

export interface CompileIssue {
  file?: string;
  line?: number;
  severity: "warning" | "error";
  code?: string;
  message: string;
}

function splitArgs(input: string): string[] {
  const args: string[] = [];
  const regex = /"([^"]*)"|'([^']*)'|([^\s]+)/g;
  let match: RegExpExecArray | null;
  while ((match = regex.exec(input)) !== null) {
    args.push(match[1] ?? match[2] ?? match[3] ?? "");
  }
  return args;
}

export function parsePawnCompileOutput(output: string): CompileIssue[] {
  const issues: CompileIssue[] = [];
  for (const line of output.split(/\r?\n/)) {
    const match =
      line.match(/^(.*?)\((\d+)\)\s*:\s*(warning|error)\s*([0-9]+)?\s*:?\s*(.*)$/i) ||
      line.match(/^(.*?):(\d+):\s*(warning|error)\s*([0-9]+)?\s*:?\s*(.*)$/i);
    if (!match) continue;
    issues.push({
      file: match[1]?.trim(),
      line: Number(match[2]),
      severity: match[3]?.toLowerCase() === "warning" ? "warning" : "error",
      code: match[4]?.trim() || undefined,
      message: match[5]?.trim() || line.trim(),
    });
  }
  return issues;
}

export async function compileGamemode(config: AppConfig): Promise<unknown> {
  if (!config.pawn.compilerPath) {
    return {
      configured: false,
      message: "PAWN_COMPILER_PATH is not configured.",
    };
  }

  const compilerPath = safeResolve(config, config.pawn.compilerPath);
  if (!fs.existsSync(compilerPath)) {
    throw new Error(`Configured compiler does not exist: ${relativePath(config, compilerPath)}`);
  }

  const args = config.pawn.compileArgs
    ? splitArgs(config.pawn.compileArgs)
    : ["gamemodes/main.pwn"];

  return new Promise((resolve) => {
    const child = spawn(compilerPath, args, {
      cwd: config.dirs.gamemode,
      shell: false,
      windowsHide: true,
    });
    let stdout = "";
    let stderr = "";
    const timeout = setTimeout(() => child.kill("SIGKILL"), 60_000);

    child.stdout.on("data", (chunk) => {
      stdout += chunk.toString();
    });
    child.stderr.on("data", (chunk) => {
      stderr += chunk.toString();
    });
    child.on("close", (code) => {
      clearTimeout(timeout);
      const output = redactText(`${stdout}\n${stderr}`);
      resolve({
        configured: true,
        compiler: relativePath(config, compilerPath),
        args,
        exitCode: code,
        output,
        issues: parsePawnCompileOutput(output),
      });
    });
  });
}

export async function parseCompileLog(config: AppConfig, input: { content?: string; filePath?: string }): Promise<unknown> {
  let content = input.content ?? "";
  if (input.filePath) {
    const fullPath = safeResolve(config, input.filePath);
    content = fs.readFileSync(fullPath, "utf8");
  }
  const redacted = config.safety.redactSecrets ? redactText(content) : content;
  return {
    issues: parsePawnCompileOutput(redacted),
    lineCount: redacted.split(/\r?\n/).length,
  };
}
