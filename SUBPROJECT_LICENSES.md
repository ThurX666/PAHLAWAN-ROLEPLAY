# Subproject License Policy

The repository root `LICENSE` applies to tracked project source code and documentation unless a narrower file or folder-specific license says otherwise.

## Folder Policy

| Path | Policy |
| --- | --- |
| `GAMEMODE/` tracked Pawn source and includes | MIT under the root `LICENSE`. Runtime binaries, plugins, generated `.amx`, logs, `server.cfg`, and private `scriptfiles` are excluded from tracked distribution. |
| `WEBSITE/` tracked React/TypeScript/PHP source, tests, and docs | MIT under the root `LICENSE`. Private `.env`, uploads, runtime logs, generated builds, and local migration markers are excluded. |
| `BOT/` tracked bot source and docs | MIT under the root `LICENSE`. Private config, tokens, cache, uploads, ticket transcripts, runtime data, and generated artifacts are excluded. |
| `tools/mcp-pahlawan/` tracked MCP source | MIT under the root `LICENSE`; package metadata also declares MIT. |
| `openspec/` tracked specs and archived change docs | MIT under the root `LICENSE`. |
| `docs/` tracked documentation | MIT under the root `LICENSE`. |
| `DATABASE/` tracked migrations and dummy/example-safe files | MIT under the root `LICENSE` only for tracked migration/example files. Private dumps, backups, exports, player data, credentials, and local database files are not licensed for redistribution and must not be committed. |

## Third-Party Material

Third-party dependencies, plugins, libraries, SA-MP/open.mp assets, and vendored tools keep their own upstream licenses. Do not assume the project MIT license overrides upstream terms.

## Private and Runtime Data

The MIT license does not grant permission to publish or redistribute secrets, credentials, tokens, cookies, OTPs, private player data, database dumps, runtime logs, local config, generated server artifacts, or files ignored by project safety policy.

## Adding Exceptions

If a future subproject needs a different license, add a folder-local `LICENSE` or `LICENSE.md` and update this policy in the same change.
