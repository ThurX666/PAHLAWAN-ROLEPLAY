# Bot Health Checklist

Last checked: 2026-06-26

## Status

| Area | Status | Notes |
| --- | --- | --- |
| Node.js | OK | Local Node runtime is available. |
| Dependencies | OK | `BOT/node_modules` exists. |
| Syntax check | OK | `node --check` passed for 60 BOT JavaScript files. |
| Runtime login | Skipped | Bot was not started to avoid token/login side effects. |
| Database access | Skipped | No live DB connection was opened. |
| Discord interaction flow | Review needed | Some commands/registers use additional `interactionCreate` listeners; inspect before changing interaction behavior. |

## Safe Validation Used

- Parsed JavaScript files only; no Discord login.
- Did not read or print `BOT/config.json` values.
- Did not connect to MySQL.
- Did not send Discord messages or register commands.

## Interaction Review Notes

Before editing commands or events, inspect these areas first:

- `BOT/events/interactionCreate.js` for the main interaction dispatcher and safe reply helper.
- `BOT/commands/admin/lelang.js` because it registers an `InteractionCreate` listener from a command module.
- `BOT/commands/warga/story.js` because it registers a modal `interactionCreate` listener inside command flow.
- Any command using `deferReply`, `editReply`, or `followUp` must preserve Discord's single-response and 3-second timing rules.

## Recommended Next Checks

1. If BOT behavior changes, propose an OpenSpec change first.
2. For simple command edits, run `node --check` on touched files before handoff.
3. For interaction bugs, analyze `reply`, `deferReply`, `editReply`, `followUp`, `replied`, and `deferred` paths before patching.
4. Start the bot only when token safety and target Discord environment are confirmed.
