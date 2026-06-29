# vps-pterodactyl-infrastructure Specification

> **Phase:** Alpha (ROADMAP Pre-Alpha → Alpha Test)
> **Deadline:** 31 Juli 2026 (setup selesai sebelum Alpha 1 Agustus 2026)

## Purpose

Define the complete VPS infrastructure setup using Pterodactyl panel as the central control plane for all three PAHLAWAN ROLEPLAY services (SA-MP server, UCP website, Discord bot), so that any operator can deploy, manage, and troubleshoot services without direct SSH access after initial setup.

## Requirements

### Requirement: VPS procurement specification is explicit and versioned

The infrastructure SHALL define the minimum VPS hardware specification, operating system, and region selection criteria that are sufficient to run all three services plus Pterodactyl panel and shared MySQL within resource constraints.

#### Scenario: Operator orders a new VPS
- **WHEN** an operator needs to provision a new VPS for PAHLAWAN ROLEPLAY
- **THEN** the specification identifies the required CPU cores, RAM, storage type/size, network bandwidth, OS distribution/version, and recommended region, along with the rationale for each choice

#### Scenario: VPS resource budget is exceeded
- **WHEN** the combined service memory usage approaches the VPS RAM limit
- **THEN** the specification identifies which services have configurable memory caps and the recommended upgrade path

### Requirement: Host OS security baseline is enforced before panel installation

The infrastructure SHALL enforce a security baseline on the host OS before installing Pterodactyl, including non-root user creation, SSH key authentication, password login disabled, firewall rules for all required ports, and system package updates.

#### Scenario: Operator secures a freshly provisioned VPS
- **WHEN** a new VPS is provisioned with root SSH access
- **THEN** the setup procedure walks through user creation, SSH hardening, firewall configuration, and package updates in a specific order that prevents lockout

#### Scenario: Firewall ports must match service requirements
- **WHEN** the operator configures the host firewall
- **THEN** the specification lists every required port with its purpose (SSH, HTTP, SA-MP/open.mp TCP+UDP, Pterodactyl Panel) and the exact `ufw` commands to open them

#### Scenario: Operator enables advanced firewall and DDoS hardening
- **WHEN** the selected provider includes Anti-DDoS protection (for example VibeGames vServer) or the server is being prepared for public exposure
- **THEN** the setup procedure documents host-level hardening for SSH allowlisting/rate-limiting, MySQL access restricted to Docker bridge, SA-MP/open.mp TCP+UDP port exposure, optional iptables rate-limits, and Nginx rate limits without making those steps mandatory for first-time internal Alpha setup

### Requirement: Shared MySQL instance is accessible to all services

The infrastructure SHALL install MySQL 8.0 on the host OS (not in a Docker container), create separate databases and users for Pterodactyl panel and PAHLAWAN services, and configure bind-address and connection limits appropriate for the Alpha scale.

#### Scenario: All three services connect to the same database
- **WHEN** the SA-MP server, UCP website, and Discord bot all need database access
- **THEN** the MySQL setup provides a single shared instance with a dedicated user and database (`arivena`), accessible from the host (`localhost`) and from Docker containers (`172.17.0.1`)

#### Scenario: Pterodactyl panel has its own isolated database
- **WHEN** Pterodactyl panel is installed
- **THEN** the MySQL setup provides a separate `panel` database with a dedicated user, isolated from the PAHLAWAN game database

#### Scenario: Database schema is imported for first-time setup
- **WHEN** the operator sets up the VPS for the first time
- **THEN** the setup procedure includes importing the PAHLAWAN database schema from `DATABASE/phrp.sql` and verifying table presence

### Requirement: Pterodactyl Panel is fully operational with Wings node connected

The infrastructure SHALL install Pterodactyl Panel (latest stable), configure its web server (Nginx), database connection, queue worker, cron scheduler, and Wings daemon, and verify that the admin panel UI and node connection are both functional.

#### Scenario: Operator accesses Pterodactyl admin panel
- **WHEN** the Pterodactyl installation is complete
- **THEN** the panel UI is accessible via HTTP on a designated port, the admin can log in, and the Wings node shows as connected (green status)

#### Scenario: Wings daemon auto-restarts after VPS reboot
- **WHEN** the VPS is rebooted
- **THEN** both the Pterodactyl queue worker and Wings daemon auto-start via systemd, and any running game servers configured with auto-restart resume automatically

### Requirement: Three custom Pterodactyl eggs are defined for PAHLAWAN services

The infrastructure SHALL define three custom Pterodactyl egg JSON files — one for SA-MP/open.mp server, one for UCP website (Nginx + PHP-FPM + Vite build), and one for Discord bot (Node.js) — each with appropriate base images or install scripts, startup commands, configurable environment variables, and resource defaults.

#### Scenario: SA-MP server starts from Pterodactyl panel
- **WHEN** an operator clicks Start on the SA-MP server in Pterodactyl
- **THEN** the server container launches with the correct gamemode files, plugins, and `server.cfg`, connects to the shared MySQL database, and binds to the SA-MP port

#### Scenario: UCP website builds and serves from Pterodactyl panel
- **WHEN** an operator clicks Start on the UCP website in Pterodactyl
- **THEN** the container runs `npm install`, builds the Vite frontend, starts PHP-FPM for the API backend, starts Nginx, and serves the website on the assigned HTTP port

#### Scenario: Discord bot starts from Pterodactyl panel
- **WHEN** an operator clicks Start on the Discord bot in Pterodactyl
- **THEN** the container runs `npm install --production`, starts `node index.js`, connects to the Discord gateway, and connects to the shared MySQL database

#### Scenario: Service environment variables are managed through panel
- **WHEN** a service needs database credentials or API keys
- **THEN** the egg exposes environment variables as configurable fields in the Pterodactyl UI, so the operator can update them without SSH or file editing

### Requirement: Repository deployment from Git or local upload to Pterodactyl volumes is documented

The infrastructure SHALL define a deployment flow from either Git repository or local project upload to Pterodactyl server volumes, including target source location, upload methods, environment file setup, gamemode compilation (if needed), and copy/sync strategy.

#### Scenario: Operator deploys the repository to VPS for the first time
- **WHEN** the VPS is set up and Pterodactyl is operational
- **THEN** the deployment procedure covers: preparing `/opt/pahlawan-roleplay`, using either `git clone`, `rsync`, `tar + scp`, or SFTP to place the project on the VPS, creating environment files from templates, compiling the gamemode, and copying/syncing files to Pterodactyl server volumes

#### Scenario: Operator updates the deployed code
- **WHEN** new code changes are pushed to the repository or refreshed local files are available
- **THEN** the update procedure covers: pulling changes or uploading refreshed local files, syncing the affected service directory to the correct Pterodactyl volume with `rsync`, rebuilding if needed (Vite, gamemode), and restarting affected services from the Pterodactyl panel

#### Scenario: Operator uploads project files from a local laptop
- **WHEN** the operator does not want to rely only on `git clone` from the VPS
- **THEN** the setup procedure provides beginner-friendly upload methods using `rsync`, `tar + scp`, and SFTP, including excludes for `.git`, `.hermes`, `.codex`, `.playwright-cli`, `.codex-plugin`, `node_modules`, logs, caches, and private SQL dumps

### Requirement: Smoke test validates all services are operational

The infrastructure SHALL define a smoke test sequence that verifies all three services are running, connected, and responsive after deployment, without exposing sensitive data.

#### Scenario: Operator validates a fresh deployment
- **WHEN** all three services have been started for the first time
- **THEN** the smoke test verifies: MySQL connectivity, SA-MP server console output (no fatal errors, port bound), UCP website HTTP response (200 OK), Discord bot online status, and stop/restart functionality from the panel

#### Scenario: Operator troubleshoots a failed service
- **WHEN** a service fails to start or crashes
- **THEN** the documentation provides troubleshooting steps for common issues: OOM kill, MySQL connection refused, missing plugins, npm install failure, Docker daemon down

### Requirement: Operational documentation is maintained outside the repository secrets

The infrastructure SHALL produce operational documentation (`docs/VPS_SETUP_GUIDE.md`, `docs/PTERODACTYL_OPERATIONS.md`) that covers setup steps, daily operations, and troubleshooting, while keeping all credentials and secrets in a separate secure store (not in the repo, not in the docs).

#### Scenario: New operator needs to manage the VPS
- **WHEN** a new operator joins the team and needs to manage the infrastructure
- **THEN** the operational docs provide enough information to start/stop/restart services, deploy updates, check logs, and troubleshoot common issues — without needing to read the OpenSpec change itself

#### Scenario: Credentials must never appear in documentation
- **WHEN** the operator records setup information
- **THEN** passwords, tokens, API keys, and SSH keys are stored in a secure credential manager (not in Markdown files, not in Git), and documentation references placeholder names only
