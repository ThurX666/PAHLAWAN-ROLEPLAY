# PAHLAWAN ROLEPLAY

PAHLAWAN ROLEPLAY adalah monorepo untuk operasional dan pengembangan server roleplay yang menggabungkan gamemode Pawn/open.mp atau SA-MP, UCP web, Discord bot, dokumentasi OpenSpec, dan tooling MCP internal untuk analisis project yang aman.

## Status

- Status: active development
- Founder / core maintainer: ThurX666
- Repo publik ini sedang dirapikan untuk maintenance, code review, dokumentasi, testing, security hardening, dan workflow rilis yang lebih baik

## Kenapa Repo Ini Penting

Project ini menyatukan beberapa lapisan yang biasanya terpisah:

- `GAMEMODE` untuk source gamemode roleplay berbasis Pawn
- `WEBSITE` untuk UCP React/TypeScript dan backend PHP
- `BOT` untuk Discord bot komunitas dan tooling operasional
- `openspec` untuk requirement, change history, dan spec maintenance
- `tools/mcp-pahlawan` untuk context, diagnostics, dan workflow support lokal

Tujuannya bukan hanya menjalankan server, tetapi juga menjaga codebase campuran legacy dan modern tetap bisa dipelihara dengan disiplin spec, review, dan guardrail secret.

## Stack Teknologi

- Pawn / open.mp / SA-MP untuk gamemode server
- React + TypeScript + Vite untuk UCP frontend
- PHP native untuk API UCP
- Node.js + discord.js untuk Discord bot
- OpenSpec untuk source of truth requirement dan change workflow
- Pahlawan MCP untuk pencarian context, validasi, dan analisis aman

## Struktur Repo

- `GAMEMODE` - source gamemode, include, runtime server, plugins, compile output
- `WEBSITE` - frontend UCP, backend PHP, test kontrak, dan dokumen workflow
- `BOT` - Discord bot, command handler, event handler, dan modul PHRP-AI
- `DATABASE` - schema dan migration aman boleh direview, dump dan backup privat tidak boleh dipublish
- `openspec` - spec utama dan archive change
- `tools/mcp-pahlawan` - MCP lokal untuk analisis project terbatas dan compact
- `docs` - ringkasan project dan workflow pengembangan

## Local Development Ringkas

1. Siapkan database lokal privat. Jangan publish dump berisi data player, akun, inventory, IP, atau kredensial. Ikuti [docs/DATABASE_POLICY.md](docs/DATABASE_POLICY.md) untuk batas public vs private.
2. Isi konfigurasi privat lokal untuk bot, website, dan gamemode.
3. Jalankan website UCP dari folder `WEBSITE`.
4. Jalankan Discord bot dari folder `BOT`.
5. Compile gamemode dari `GAMEMODE/gamemodes/main.pwn`.
6. Gunakan OpenSpec sebelum perubahan fitur menengah/besar.
7. Gunakan Pahlawan MCP compact mode untuk context, trace, validasi, dan review terarah.

Dokumen pendukung:

- [docs/README.md](docs/README.md)
- [docs/PROJECT_OVERVIEW.md](docs/PROJECT_OVERVIEW.md)
- [docs/DEVELOPMENT.md](docs/DEVELOPMENT.md)
- [docs/LOCAL_VALIDATION_MATRIX.md](docs/LOCAL_VALIDATION_MATRIX.md)
- [WEBSITE/LOCAL_DEVELOPMENT_WORKFLOW.md](WEBSITE/LOCAL_DEVELOPMENT_WORKFLOW.md)
- [openspec/specs/ucp-local-development-workflow/spec.md](openspec/specs/ucp-local-development-workflow/spec.md)

## Security Warning

- Jangan commit `.env`, token, API key, credential database, SMTP secret, Discord secret, cookie, session, OTP, dump database, atau runtime log.
- File dump dan backup `DATABASE` bersifat privat. Hanya schema, migration, example SQL aman, dan fixture dummy/test yang boleh ada di repo public sesuai [docs/DATABASE_POLICY.md](docs/DATABASE_POLICY.md).
- File runtime lokal seperti `BOT/config.json`, `BOT/PHRP-AI/config/app.json`, `WEBSITE/.env`, dan `GAMEMODE/server.cfg` tidak boleh dipublish.
- Jika menemukan potensi secret leak atau celah keamanan, ikuti `SECURITY.md` dan [docs/SECRET_ROTATION_PLAYBOOK.md](docs/SECRET_ROTATION_PLAYBOOK.md).

## Kontribusi

Kontribusi kecil dan terarah lebih diutamakan daripada perubahan besar sekaligus.

- Baca `CONTRIBUTING.md` sebelum membuka PR
- Cek OpenSpec aktif lebih dulu
- Hindari perubahan di luar scope
- Validasi diff dan pastikan tidak ada file sensitif ikut staged

## Roadmap Singkat

- Alpha: rapikan repo publik, secret guardrail, dan local development workflow
- Beta: stabilkan auth UCP, integrasi database, testing kontrak, dan smoke validation
- RC: perkuat review workflow, release checklist, dan dokumentasi operasional
- Launch: publikasi repo yang aman, terdokumentasi, dan siap menerima kontribusi bertahap

Detail milestone ada di `ROADMAP.md`.

## Codex, OpenSpec, dan Maintenance

Repo ini dipublikasikan dengan fokus maintenance modern untuk codebase campuran:

- Codex dipakai untuk code review, dokumentasi, validasi perubahan, testing assistance, dan release workflow
- OpenSpec dipakai untuk menjaga scope requirement tetap jelas sebelum coding
- Pahlawan MCP dipakai untuk context gathering, trace feature, schema overview, dan validasi aman dengan compact mode

Pendekatan ini membantu mengurangi perubahan liar, mempercepat review, dan menjaga repo publik tetap aman untuk komunitas serta maintainer.
