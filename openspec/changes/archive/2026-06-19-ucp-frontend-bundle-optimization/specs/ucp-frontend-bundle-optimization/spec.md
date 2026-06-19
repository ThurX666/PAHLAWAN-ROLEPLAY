# ucp-frontend-bundle-optimization Specification

## Purpose
Define the approved approach for reducing the UCP frontend's initial production bundle through safe code splitting and lazy loading without changing auth flow, PHP behavior, or user-visible production outcomes.

## ADDED Requirements

### Requirement: Bundle analysis records the current production warning and entry structure
The optimization workflow SHALL record the current `npm run build` warning, including the oversized emitted bundle and the single-entry frontend structure that eagerly loads the application from `WEBSITE/index.tsx` and `WEBSITE/App.tsx`.

#### Scenario: Production bundle is analyzed before implementation
- **WHEN** the frontend bundle optimization change is prepared
- **THEN** the analysis records the emitted oversized chunk warning and identifies the main entry files that load the current application bundle

### Requirement: Optimization planning preserves existing auth and API behavior
The optimization plan SHALL keep PHP API logic, auth flow, session behavior, request credential behavior, and production-visible feature behavior unchanged while introducing code-splitting boundaries.

#### Scenario: Safe optimization boundaries are selected
- **WHEN** lazy-loading or code-splitting candidates are proposed
- **THEN** the proposal excludes PHP API edits, auth logic changes, session changes, and production behavior changes

### Requirement: Major secondary frontend areas are eligible for screen-level lazy loading
The optimization plan SHALL treat non-bootstrap frontend areas such as donation, tickets, character story, character detail, admin, and requests screens as approved candidates for screen-level lazy loading when they are not required for initial application startup.

#### Scenario: Screen-level split points are identified
- **WHEN** the current `App.tsx` navigation flow is reviewed
- **THEN** the plan identifies major secondary screens that can load on demand instead of being eagerly imported into the initial bundle

### Requirement: Heavy optional dependencies are isolated behind interaction-level boundaries
The optimization plan SHALL isolate heavy optional dependencies such as charting, image cropping, and similar feature-specific modules behind lazy boundaries at the screen, panel, or modal level whenever they are not needed for the first rendered view.

#### Scenario: Heavy nested modules are reviewed
- **WHEN** feature-specific dependencies are analyzed
- **THEN** the plan identifies chart and image-cropping modules as candidates to load only when the related screen or modal is used

### Requirement: Future implementation validation is defined by build output and regression checks
The optimization plan SHALL require future implementation work to validate reduced bundle structure through `npm run build` and SHALL require regression checks for auth, navigation, and affected frontend screens instead of suppressing the warning through configuration alone.

#### Scenario: Implementation readiness is evaluated
- **WHEN** the optimization proposal is converted into implementation work
- **THEN** the validation plan includes production build verification and focused navigation checks across the affected frontend areas
