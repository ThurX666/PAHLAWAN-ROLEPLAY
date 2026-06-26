# Gamemode Health Checklist

Last checked: 2026-06-26

## Status

| Area | Status | Notes |
| --- | --- | --- |
| Main Pawn file | OK | `GAMEMODE/gamemodes/main.pwn` detected. |
| Local Pawn compiler | OK | `GAMEMODE/pawno/pawncc.exe` exists. |
| MCP compiler config | Not configured | `PAWN_COMPILER_PATH` is not configured for MCP yet. |
| Safe compile check | OK with warnings | Compile succeeded to a temporary output path. |
| Runtime files | Untouched | No `.amx` runtime output was written into the project. |

## Safe Compile Command

Run from `GAMEMODE` and write output to a temporary path, not directly to runtime files:

```powershell
$outDir = Join-Path $env:TEMP ('phrp-pawn-compile-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Force $outDir | Out-Null
.\pawno\pawncc.exe .\gamemodes\main.pwn -i.\pawno\include -i.\gamemodes -o"$outDir\main.amx"
Remove-Item -LiteralPath $outDir -Recurse -Force
```

## Current Compile Evidence

- Compiler: Pawn compiler 3.10.8.
- Result: success.
- Warnings: 19.
- Notable warning class: unused symbols and YSI semicolon re-enable warning.
- Output location: temporary folder only, deleted after check.

## Recommended Next Setup

1. Configure MCP `PAWN_COMPILER_PATH` to `GAMEMODE/pawno/pawncc.exe`.
2. Configure MCP compile args to include `-iGAMEMODE/pawno/include` and `-iGAMEMODE/gamemodes`.
3. Keep compile output outside tracked/runtime paths for validation checks.
4. Only write/update the production `.amx` when explicitly preparing a server runtime package.
