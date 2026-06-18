import fs from "node:fs";
import { z } from "zod";
import type { ToolDefinition } from "../types.js";
import {
  listActiveOpenSpecChangeIds,
  listMainOpenSpecSpecs,
  openspecRoot,
  summarizeOpenSpecChange,
} from "../utils/openspec.js";

export const openspecTools: ToolDefinition[] = [
  {
    name: "openspec_overview",
    description: "List active OpenSpec changes and relevant main specs with compact summaries.",
    schema: z.object({}),
    inputSchema: { type: "object", properties: {}, additionalProperties: false },
    handler(_input, { config }) {
      const activeChangeIds = listActiveOpenSpecChangeIds(config);
      return {
        detected: fs.existsSync(openspecRoot(config)),
        sourceOfTruth: "OpenSpec is authoritative for feature planning and requirements.",
        activeChanges: activeChangeIds.map((changeId) => {
          const change = summarizeOpenSpecChange(config, changeId);
          return {
            changeId,
            proposalSummary: change.proposalSummary,
            taskCounts: change.taskCounts,
            paths: change.paths,
          };
        }),
        mainSpecs: listMainOpenSpecSpecs(config),
      };
    },
  },
  {
    name: "openspec_read_change",
    description: "Read one OpenSpec change and return compact proposal, requirements, tasks, design notes, and risks.",
    schema: z.object({
      changeId: z.string().regex(/^[a-z0-9][a-z0-9-]*$/),
    }),
    inputSchema: {
      type: "object",
      required: ["changeId"],
      properties: { changeId: { type: "string" } },
      additionalProperties: false,
    },
    handler(input, { config }) {
      return summarizeOpenSpecChange(config, input.changeId);
    },
  },
  {
    name: "openspec_task_status",
    description: "Show completed, pending, and blocked checklist tasks for one OpenSpec change.",
    schema: z.object({
      changeId: z.string().regex(/^[a-z0-9][a-z0-9-]*$/),
    }),
    inputSchema: {
      type: "object",
      required: ["changeId"],
      properties: { changeId: { type: "string" } },
      additionalProperties: false,
    },
    handler(input, { config }) {
      const change = summarizeOpenSpecChange(config, input.changeId);
      return {
        changeId: input.changeId,
        counts: change.taskCounts,
        completed: change.tasks.filter((task) => task.completed),
        pending: change.tasks.filter((task) => !task.completed && !task.blocked),
        blocked: change.tasks.filter((task) => task.blocked && !task.completed),
        nextStep: change.tasks.find((task) => !task.completed && !task.blocked) ?? null,
        tasksPath: change.paths.tasks,
      };
    },
  },
];
