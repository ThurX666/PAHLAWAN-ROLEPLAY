const sensitiveTerm =
  /(?:password|passwd|pwd|token|secret|api[_-]?key|apikey|auth|authorization|bearer|webhook|client[_-]?secret|discord[_-]?token|mysql_password|db_password|smtp_pass|salt|email)/i;
const sensitiveObjectKey =
  /(?:^|[_-])(?:password|passwd|pwd|token|secret|api[_-]?key|apikey|auth|authorization|bearer|webhook|client[_-]?secret|discord[_-]?token|mysql_password|db_password|smtp_pass|salt|email)(?:$|[_-])/i;

const envAssignment = new RegExp(
  `(^|\\b)([A-Z0-9_]*${sensitiveTerm.source}[A-Z0-9_]*\\s*=\\s*)([^\\r\\n#]+)`,
  "gim",
);
const quotedAssignment = new RegExp(
  `(["']?[^"'\\n]*${sensitiveTerm.source}[^"'\\n]*["']?\\s*[:=]\\s*["'])([^"'\\n]+)(["'])`,
  "gim",
);
const authorizationHeader = /(Authorization\s*:\s*(?:Bearer|Bot)\s+)([^\r\n"']+)/gim;
const discordWebhook = /(https:\/\/discord\.com\/api\/webhooks\/)[^\s"']+/gim;

export function isSensitiveKey(key: string): boolean {
  return sensitiveObjectKey.test(key) ||
    /^(?:apiKey|clientSecret|discordToken|mysqlPassword|dbPassword|smtpPass)$/i.test(key);
}

export function redactText(input: string): string {
  let output = input;
  output = output.replace(/(sk-[A-Za-z0-9_-]{12,})/g, "[REDACTED_OPENAI_KEY]");
  output = output.replace(/([A-Za-z0-9_-]{20,}\.[A-Za-z0-9_-]{6,}\.[A-Za-z0-9_-]{20,})/g, "[REDACTED_DISCORD_TOKEN]");
  output = output.replace(envAssignment, "$1$2[REDACTED]");
  output = output.replace(quotedAssignment, "$1[REDACTED]$3");
  output = output.replace(authorizationHeader, "$1[REDACTED]");
  output = output.replace(discordWebhook, "$1[REDACTED]");
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
