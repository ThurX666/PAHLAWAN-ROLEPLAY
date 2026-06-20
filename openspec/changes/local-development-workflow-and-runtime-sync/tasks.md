## 1. Local workflow planning

- [x] 1.1 Audit the current local development paths, runtime assumptions, and repo-vs-XAMPP boundary without moving the repository.
- [x] 1.2 Define the standard local workflow for repo-based frontend/PHP development, production-build validation, and flattened XAMPP runtime validation.
- [x] 1.3 Define private `.env` handling, tracked env examples, and local secret-handling rules.

## 2. Runtime sync and reset planning

- [x] 2.1 Define the approved sync/copy strategy from the repository to `C:\\xampp\\htdocs\\pahlawan_roleplay`.
- [x] 2.2 Define the minimum local post-sync checks for frontend, API, and bounded smoke verification.
- [x] 2.3 Define the local rollback/reset procedure that restores a clean XAMPP runtime without altering the repository.

## 3. Testing and update workflow

- [x] 3.1 Define when to use `npm run dev` versus `npm run build`.
- [x] 3.2 Define when to use the PHP built-in server versus XAMPP Apache.
- [x] 3.3 Define the local testing checklist for repo development, build validation, and XAMPP runtime verification.

## 4. Final validation and handoff

- [ ] 4.1 Validate the OpenSpec artifacts and ensure proposal, design, spec delta, and tasks stay aligned.
- [ ] 4.2 Confirm the change remains planning-only and does not require BOT runtime, Pawn/gamemode, or database schema scope.
- [ ] 4.3 Prepare the change for implementation approval without starting runtime modifications.
