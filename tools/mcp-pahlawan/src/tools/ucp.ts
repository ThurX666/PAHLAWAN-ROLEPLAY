import fs from "node:fs";
import path from "node:path";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import { findFiles, listProjectFiles, readTextFile, searchCode } from "../utils/fileSearch.js";
import { relativePath } from "../utils/pathSafety.js";
import { findRelatedOpenSpecChanges } from "../utils/openspec.js";

function readPackageJson(root: string): unknown {
  const packagePath = path.join(root, "package.json");
  if (!fs.existsSync(packagePath)) return null;
  return JSON.parse(fs.readFileSync(packagePath, "utf8"));
}

export const ucpTools: ToolDefinition[] = [
  {
    name: "ucp_overview",
    description: "Detect UCP framework, structure, API handlers, auth files, and database connection files.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const pkg = readPackageJson(config.dirs.website) as { dependencies?: Record<string, string>; devDependencies?: Record<string, string>; scripts?: Record<string, string> } | null;
      const deps = { ...(pkg?.dependencies ?? {}), ...(pkg?.devDependencies ?? {}) };
      const framework = {
        react: Boolean(deps.react),
        vite: Boolean(deps.vite),
        next: Boolean(deps.next),
        express: Boolean(deps.express),
        tailwind: Boolean(deps.tailwindcss) || fs.existsSync(path.join(config.dirs.website, "tailwind.config.js")),
      };
      const apiFiles = await listProjectFiles(config, { module: "website", extensions: [".php"], limit: 60 });
      return {
        framework,
        package: pkg ? { scripts: pkg.scripts, dependencies: Object.keys(deps).sort() } : null,
        entryFiles: await findFiles(config, "index", { module: "website", extensions: [".tsx", ".ts", ".js", ".html"], limit: config.limits.maxSearchResults }),
        apiFileCountSample: apiFiles.length,
        apiFileSamples: apiFiles.map((file) => relativePath(config, file)).slice(0, config.limits.maxSearchResults),
        authHits: (await searchCode(config, "auth", { module: "website", extensions: [".php", ".ts", ".tsx", ".js"], limit: config.limits.maxSearchResults, contextLines: 0 }))
          .map(({ context: _context, ...hit }) => hit),
        dbConfigCandidates: await findFiles(config, "config", { module: "website", extensions: [".php", ".ts", ".js", ".json"], limit: config.limits.maxSearchResults }),
      };
    },
  },
  {
    name: "list_ucp_routes",
    description: "List detected frontend pages/components and backend API routes.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const phpFiles = await listProjectFiles(config, { module: "website", extensions: [".php"], limit: config.limits.maxFeatureFiles });
      const frontendFiles = await listProjectFiles(config, { module: "website", extensions: [".tsx", ".ts", ".jsx", ".js"], limit: config.limits.maxFeatureFiles });
      return {
        apiRoutes: phpFiles.map((file) => {
          const rel = relativePath(config, file);
          const route = `/${rel.replace(/^WEBSITE\/public\//, "").replace(/\\/g, "/")}`;
          return { route, file: rel };
        }),
        frontendCandidates: frontendFiles
          .filter((file) => /(^|[\\/])(App|pages|components|routes|auth|dashboard|admin)/i.test(file))
          .map((file) => relativePath(config, file))
          .slice(0, 150),
      };
    },
  },
  {
    name: "analyze_ucp_auth",
    description: "Find login/session/auth middleware and summarize authentication flow with likely security concerns.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    async handler(_input, { config }) {
      const compactLimit = Math.min(5, config.limits.maxSearchResults);
      const authHits = await searchCode(config, "auth", { module: "website", extensions: [".php", ".ts", ".tsx", ".js"], limit: compactLimit, contextLines: 0 });
      const sessionHits = await searchCode(config, "session", { module: "website", extensions: [".php", ".ts", ".tsx", ".js"], limit: compactLimit, contextLines: 0 });
      const passwordHits = await searchCode(config, "password", { module: "website", extensions: [".php", ".ts", ".tsx", ".js"], limit: compactLimit, contextLines: 0 });
      const validationHits = await searchCode(config, "validate", { module: "website", extensions: [".php", ".ts", ".tsx", ".js"], limit: compactLimit, contextLines: 0 });
      return {
        authHits,
        sessionHits,
        passwordHits,
        validationHits,
        securityChecklist: [
          "Use parameterized SQL/PDO prepared statements.",
          "Keep config.php and .env ignored.",
          "Validate all user input server-side.",
          "Avoid trusting localStorage for admin authority without server verification.",
          "Check CORS and session/cookie handling before deployment.",
        ],
      };
    },
  },
  {
    name: "generate_ucp_feature_plan",
    description: "Generate a safe implementation plan for a requested UCP feature without editing files.",
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
      const relatedOpenSpecChanges = findRelatedOpenSpecChanges(config, input.feature);
      const related = await searchCode(config, input.feature, { module: "website", extensions: [".php", ".ts", ".tsx", ".js", ".sql", ".txt"], limit: config.limits.maxSearchResults, contextLines: 0 });
      if (relatedOpenSpecChanges.length > 0) {
        return {
          feature: input.feature,
          planningSource: "openspec",
          message: "A related OpenSpec change exists. Use it as the implementation plan; no competing MCP plan was generated.",
          relatedOpenSpecChanges: relatedOpenSpecChanges.map((change) => ({
            changeId: change.changeId,
            proposalSummary: change.proposalSummary,
            requirements: change.requirements,
            taskCounts: change.taskCounts,
            paths: change.paths,
          })),
          related,
        };
      }
      return {
        feature: input.feature,
        planningSource: "mcp-fallback",
        related,
        plan: [
          "Map existing API/data model for this feature.",
          "Identify frontend component or route that owns the workflow.",
          "Add server-side validation first, then UI wiring.",
          "Reuse existing API response shape where possible.",
          "Run build and browser smoke test after changes.",
        ],
        risks: [
          "Authentication/authorization bypass if frontend-only checks are used.",
          "Schema drift with gamemode/bot if database fields are renamed.",
          "Exposed config if PHP config files are copied into Git.",
        ],
      };
    },
  },
];
