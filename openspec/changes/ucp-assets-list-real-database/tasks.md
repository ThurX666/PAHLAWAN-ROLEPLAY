## 1. Verify Data Contract

- [ ] 1.1 Reconfirm safe columns for `houses`, `biz`, and `families` using read-only schema or existing code references.
- [ ] 1.2 Confirm the existing `AssetList.tsx` response fields and safe placeholders.

## 2. Implement Read-Only Asset Lists

- [ ] 2.1 Replace house list mapping with confirmed columns and null-safe price, locked, and location values.
- [ ] 2.2 Return only approved safe business list fields with a safe location.
- [ ] 2.3 Return safe family list fields with `level: null` and without `DirtyMoney`.
- [ ] 2.4 Add validated asset-type handling and safe API errors.

## 3. Frontend Safety

- [ ] 3.1 Update `AssetList.tsx` only as needed for loading, error, empty, null, and unknown values.

## 4. Verification

- [ ] 4.1 Run PHP syntax lint for the changed API.
- [ ] 4.2 Run the Vite production build.
- [ ] 4.3 Run `git diff --check` and confirm no asset-detail, Pawn, migration, or deletion changes.
