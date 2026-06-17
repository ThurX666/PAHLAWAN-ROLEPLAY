#!/usr/bin/env node
import { Server } from "@modelcontextprotocol/sdk/server/index.js";
import { StdioServerTransport } from "@modelcontextprotocol/sdk/server/stdio.js";
import { CallToolRequestSchema, ListToolsRequestSchema } from "@modelcontextprotocol/sdk/types.js";
import { loadConfig } from "./config.js";
import { jsonText } from "./types.js";
import { tools } from "./tools/index.js";
import { redactText } from "./utils/redact.js";

const config = loadConfig();
const toolMap = new Map(tools.map((tool) => [tool.name, tool]));

const server = new Server(
  {
    name: "mcp-pahlawan",
    version: "0.1.0",
  },
  {
    capabilities: {
      tools: {},
    },
  },
);

function withOutputBudget(text: string): string {
  if (text.length <= config.limits.maxOutputChars) return text;
  return jsonText({
    truncated: true,
    maxOutputChars: config.limits.maxOutputChars,
    note: "Output exceeded MCP_MAX_OUTPUT_CHARS. Re-run with narrower filters, lower maxResults, or pagination cursor.",
    preview: text.slice(0, config.limits.maxOutputChars),
  });
}

server.setRequestHandler(ListToolsRequestSchema, async () => ({
  tools: tools.map((tool) => ({
    name: tool.name,
    description: tool.description,
    inputSchema: tool.inputSchema,
  })),
}));

server.setRequestHandler(CallToolRequestSchema, async (request) => {
  const tool = toolMap.get(request.params.name);
  if (!tool) {
    throw new Error(`Unknown tool: ${request.params.name}`);
  }

  try {
    const parsed = tool.schema.parse(request.params.arguments ?? {});
    const result = await tool.handler(parsed, { config });
    return {
      content: [
        {
          type: "text",
          text: withOutputBudget(jsonText(result)),
        },
      ],
    };
  } catch (error) {
    const message = error instanceof Error ? error.message : String(error);
    return {
      isError: true,
      content: [
        {
          type: "text",
          text: jsonText({
            ok: false,
            error: config.safety.redactSecrets ? redactText(message) : message,
          }),
        },
      ],
    };
  }
});

const transport = new StdioServerTransport();
await server.connect(transport);
