# ROADMAP

> **OpenSpec Governance:** Setiap OpenSpec change baru **wajib** merujuk ke satu
> milestone di ROADMAP ini. Jika tidak ada milestone yang relevan, buat task
> `housekeeping` atau `tech-debt` yang tetap menunjuk fase terdekat. Jangan
> buat OpenSpec yang "mengambang" tanpa anchor ke ROADMAP.

---

## Pre-Alpha — Infrastructure & Auth Foundation

**Deadline:** Sekarang → 31 Juli 2026
**Goal:** Pondasi deployment dan auth flow siap sebelum Alpha dimulai.

### Infrastructure

- [ ] Provisioning VPS dan install Pterodactyl panel — [setup lengkap](openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md)
- [ ] Beli dan konfigurasi domain/DNS/SSL — [domain guide](docs/DOMAIN_PROVIDER_GUIDE.md)
- [ ] Pilih dan order VPS provider — [VPS provider guide](docs/VPS_PROVIDER_GUIDE.md)
- [ ] Buat Pterodactyl egg untuk SA-MP/open.mp server — [egg JSON](docs/eggs/egg-samp-server.json)
- [ ] Buat Pterodactyl egg untuk web (Nginx + PHP-FPM) — [egg JSON](docs/eggs/egg-ucp-website.json)
- [ ] Buat Pterodactyl egg untuk Discord bot (Node.js) — [egg JSON](docs/eggs/egg-discord-bot.json)
- [ ] Setup shared MySQL instance yang bisa diakses ketiga service
- [ ] Dokumentasi env variable dan secret management per service — [operations guide](docs/PTERODACTYL_OPERATIONS.md)
- [ ] OpenSpec: [`vps-pterodactyl-infrastructure`](openspec/changes/vps-pterodactyl-infrastructure/) / [spec](openspec/specs/vps-pterodactyl-infrastructure/spec.md)

**Dokumen cepat untuk infrastructure:**

- [VPS Setup Guide ringkas](docs/VPS_SETUP_GUIDE.md)
- [VPS + Pterodactyl Setup Guide lengkap](openspec/changes/vps-pterodactyl-infrastructure/SETUP_GUIDE.md)
- [Pterodactyl Operations Guide](docs/PTERODACTYL_OPERATIONS.md)
- [Bootstrap helper script](docs/scripts/bootstrap-vps.sh)

### Auth & Character Flow

- [ ] End-to-end: Register → Verify OTP → Login di web UCP
- [ ] Create Character di web, tersimpan ke `player_characters`
- [ ] Login in-game di SA-MP server pakai akun UCP yang sama
- [ ] Database sync: `player_ucp` + `player_characters` konsisten antara web dan gamemode
- [ ] Bot Discord bisa connect dan merespons command dasar
- [ ] OpenSpec: `cross-service-auth-flow`

### Deployment Automation

- [ ] Deploy script dari git push sampai service jalan di Pterodactyl
- [ ] Environment config terpisah per service (`.env` web, `config.json` bot, `server.cfg` gamemode)
- [ ] Restart policy dan health check dasar di Pterodactyl
- [ ] OpenSpec: `deployment-automation`

---

## Alpha Test — Internal Team

**Deadline:** 1 Agustus 2026
**Stability:** Rendah — masih banyak bug, khusus tim internal.
**Trigger:** Bot countdown mencapai `Launch: 90d remaining`

### Definition of Done

- [ ] Tim internal bisa register akun dan verifikasi via OTP
- [ ] Tim internal bisa login ke web UCP
- [ ] Tim internal bisa buat karakter baru
- [ ] Tim internal bisa login ke SA-MP server dan memainkan karakter yang dibuat
- [ ] Bot Discord aktif di guild dan merespons command
- [ ] Ketiga service jalan di VPS via Pterodactyl
- [ ] Database shared dan konsisten lintas service

### Developer Tasks

- [ ] Stabilkan auth flow UCP (register, OTP, login)
- [ ] Compile gamemode dan deploy ke VPS tanpa error blocker
- [ ] Setup karakter creation flow: web → database → in-game spawn
- [ ] Basic bot commands: welcome, help, status
- [ ] Smoke test: 5 user internal berhasil full cycle
- [ ] OpenSpec yang relevan: `cross-service-auth-flow`, `vps-pterodactyl-infrastructure`, `deployment-automation`

---

## Beta Test — Pemain Terpilih

**Deadline:** 1 September 2026
**Stability:** Sedang — sedikit bug, untuk pemain terpilih.
**Trigger:** Bot countdown mencapai `Launch: 60d remaining`

### Definition of Done

- [ ] Bug critical dari Alpha sudah di-fix
- [ ] Fitur UCP tambahan jalan: donation, ticket, story, character detail
- [ ] Endpoint API punya contract test
- [ ] Security hardening dasar (rate limit, input validation, SQL injection guard)
- [ ] Bot punya command moderation dan ticket integration

### Developer Tasks

- [ ] Fix semua bug critical yang ditemukan di Alpha
- [ ] Stabilkan fitur UCP: donation, ticket system, story review, character detail
- [ ] Contract testing untuk endpoint penting (auth, character, donation)
- [ ] Rate limiting dan input validation di PHP API
- [ ] Bot moderation commands dan ticket system
- [ ] Review dan perjelas integrasi database website ↔ gamemode
- [ ] OpenSpec yang relevan: `ucp-testing-contracts`, `bot-command-hardening`, `ucp-database-gamemode-sync`

---

## RC (Release Candidate) — Slot Terbatas

**Deadline:** 1 Oktober 2026
**Stability:** Tinggi — minim bug, terbuka untuk warga dengan slot terbatas.
**Trigger:** Bot countdown mencapai `Launch: 30d remaining`

### Definition of Done

- [ ] Load test berhasil untuk target player count
- [ ] Release checklist dan smoke validation lengkap
- [ ] Cross-module review workflow (gamemode ↔ web ↔ bot)
- [ ] GitHub issue/PR triage dan readiness
- [ ] Hardening area sensitif (auth, payment, admin)

### Developer Tasks

- [ ] Load testing SA-MP server + web + bot bersamaan
- [ ] Susun release checklist dan smoke validation script
- [ ] Review workflow lintas gamemode, website, dan bot
- [ ] Rapikan GitHub issue template, PR template, dan triage
- [ ] Evaluasi hardening: auth, donation validation, admin access
- [ ] OpenSpec yang relevan: `ucp-production-deployment-runbook`, `ucp-local-smoke-runbook`

---

## Stable (Grand Opening) — Public Launch

**Deadline:** 1 November 2026
**Stability:** Sangat tinggi — bebas bug critical, terbuka untuk publik.
**Trigger:** Bot countdown mencapai `Launch: 0d remaining`

### Definition of Done

- [ ] Semua smoke test pass
- [ ] Repo publik aman untuk reviewer eksternal
- [ ] Community health files lengkap (README, CONTRIBUTING, SECURITY, CODE_OF_CONDUCT)
- [ ] Dokumentasi setup dan kontribusi jelas
- [ ] OpenSpec utama sinkron dengan kondisi repo
- [ ] Baseline release/tag publik pertama siap

### Developer Tasks

- [ ] Final security audit (secret exposure, config leak)
- [ ] Community health files review dan update
- [ ] OpenSpec sync: semua spec harus match implementation
- [ ] Public release tag dan changelog
- [ ] Monitoring dan alerting dasar untuk production
- [ ] OpenSpec yang relevan: `license-subproject-clarification`, housekeeping

---

## Post-Launch Technical Milestones

Task teknis setelah Grand Opening, dikerjakan sesuai prioritas:

- [ ] Audit file config tracked yang berpotensi sensitif
- [ ] Tambah public GitHub issue untuk task prioritas komunitas
- [ ] Perjelas lisensi subproject yang masih `UNLICENSED`
- [ ] Tingkatkan coverage validasi non-runtime (docs, spec, readiness)
- [ ] CI/CD pipeline terpadu (Pawn compile, Vite build, Bot lint, DB migration)
- [ ] Admin panel UCP: feature roadmap dan access governance

---

## OpenSpec ↔ ROADMAP Alignment

Cara memastikan OpenSpec selalu selaras dengan ROADMAP:

1. **Buat OpenSpec baru** → Cek fase mana yang paling relevan di atas.
2. **Tag fase** di header spec, contoh: `phase: alpha` atau `phase: beta`.
3. **Jika tidak ada fase yang cocok** → Buat sebagai `housekeeping` atau `tech-debt` dan tag `phase: post-launch`.
4. **Review berkala** → Setiap kali OpenSpec change di-archive, cek apakah ROADMAP perlu update.
5. **Jangan buat spec yang overlap** → Cek spec yang sudah ada di `openspec/specs/` dan `openspec/changes/archive/` sebelum buat baru.
