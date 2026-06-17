const sensitiveKey =
  /(password|passwd|pwd|token|secret|api[_-]?key|apikey|auth|authorization|bearer|webhook|client[_-]?secret|discord[_-]?token|mysql_password|db_password|smtp_pass|salt|email)/i;

const assignmentPatterns = [
  new RegExp(`(^|\\b)([A-Z0-9_]*${sensitiveKey.source}[A-Z0-9_]*\\s*=\\s*)([^\\r\\n#]+)`, "gim"),
  new RegExp(`(["']?[^"'\\n]*${sensitiveKey.source}[^"'\\n]*["']?\\s*[:=]\\s*["'])([^"'\\n]+)(["'])`, "gim"),
  new RegExp(`(Authorization\\s*:\\s*(?:Bearer|Bot)\\s+)([^\\r\\n"']+)`, "gim"),
  new RegExp(`(https://discord\\.com/api/webhooks/)[^\\s"']+`, "gim"),
];

export function isSensitiveKey(key: string): boolean {
  return sensitiveKey.test(key);
}

export function redactText(input: string): string {
  let output = input;
  output = output.replace(/(sk-[A-Za-z0-9_-]{12,})/g, "[REDACTED_OPENAI_KEY]");
  output = output.replace(/([A-Za-z0-9_-]{20,}\.[A-Za-z0-9_-]{6,}\.[A-Za-z0-9_-]{20,})/g, "[REDACTED_DISCORD_TOKEN]");
  for (const pattern of assignmentPatterns) {
    output = output.replace(pattern, (...parts: string[]) => {
      if (parts.length >= 4 && parts[3] === undefined) return `${parts[1]}[REDACTED]`;
      if (parts.length >= 5) return `${parts[1]}${parts[2]}[REDACTED]${parts[4] ?? ""}`;
      return "[REDACTED]";
    });
  }
  return output;
}

export function redactObject<T>(value: T): T {
  if (Array.isArray(value)) {
    return value.map((item) => redactObject(item)) as T;
  }
  if (value && typeof value === "object") {
    const output: Record<string, unknown> = {};
    for (const [key, item] of Object.entries(value)) {
      output[key] = isSensitiveKey(key) ? "[REDACTED]" : redactObject(item);
    }
    return output as T;
  }
  if (typeof value === "string") {
    return redactText(value) as T;
  }
  return value;
}
