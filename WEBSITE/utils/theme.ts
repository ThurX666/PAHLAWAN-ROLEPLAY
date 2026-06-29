/**
 * PHRP Design Token Utility
 * Reads CSS custom properties from :root at runtime.
 * Usage: import { tokens } from '@/utils/theme'; tokens.color.redBase
 */

type CSSValue = string;

interface TokenGroup {
  readonly [key: string]: CSSValue;
}

const root = () => getComputedStyle(document.documentElement);

function pick(keys: readonly string[]): TokenGroup {
  const s = root();
  return Object.freeze(
    Object.fromEntries(keys.map(k => [k, s.getPropertyValue(k).trim()]))
  );
}

// Static key lists — match :root in index.html
const COLOR_KEYS = [
  '--ph-red-base', '--ph-red-dark', '--ph-red-soft',
  '--ph-gold-accent', '--ph-gold-400',
  '--ph-success', '--ph-warning', '--ph-info',
] as const;

const SURFACE_KEYS = [
  '--ph-surface-deep', '--ph-surface-base', '--ph-surface-card',
  '--ph-surface-panel', '--ph-surface-input', '--ph-surface-elevated',
] as const;

const BORDER_KEYS = [
  '--ph-border-subtle', '--ph-border-default', '--ph-border-focus',
] as const;

const TEXT_KEYS = [
  '--ph-text-primary', '--ph-text-secondary', '--ph-text-muted', '--ph-text-inverse',
] as const;

const SPACING_KEYS = [
  '--ph-space-1', '--ph-space-2', '--ph-space-3', '--ph-space-4',
  '--ph-space-5', '--ph-space-6', '--ph-space-8', '--ph-space-10',
  '--ph-space-12', '--ph-space-16',
] as const;

const RADIUS_KEYS = [
  '--ph-radius-sm', '--ph-radius-input', '--ph-radius-card',
  '--ph-radius-btn', '--ph-radius-lg', '--ph-radius-xl', '--ph-radius-full',
] as const;

const SHADOW_KEYS = [
  '--ph-shadow-sm', '--ph-shadow-md', '--ph-shadow-lg',
  '--ph-shadow-card', '--ph-shadow-glow-crimson',
] as const;

const FONT_KEYS = [
  '--ph-font-sans', '--ph-font-mono',
] as const;

const FONTSIZE_KEYS = [
  '--ph-text-xs', '--ph-text-sm', '--ph-text-base', '--ph-text-md',
  '--ph-text-lg', '--ph-text-xl', '--ph-text-2xl', '--ph-text-3xl',
] as const;

const TRANSITION_KEYS = [
  '--ph-transition-fast', '--ph-transition-base',
  '--ph-transition-slow', '--ph-transition-spring',
] as const;

const Z_KEYS = [
  '--ph-z-base', '--ph-z-dropdown', '--ph-z-sticky',
  '--ph-z-overlay', '--ph-z-modal', '--ph-z-toast',
] as const;

const LAYOUT_KEYS = [
  '--ph-sidebar-w', '--ph-sidebar-w-collapsed',
  '--ph-content-max', '--ph-auth-form-w',
] as const;

/** Responsive breakpoints (match Tailwind config screens). */
export const breakpoints = {
  xs: 320,
  sm: 640,
  md: 768,
  lg: 1024,
  xl: 1280,
  '2xl': 1536,
} as const;

/** Check if current viewport is at least the given breakpoint. */
export function isMinBreakpoint(bp: keyof typeof breakpoints): boolean {
  return window.matchMedia(`(min-width: ${breakpoints[bp]}px)`).matches;
}

/** Get a single CSS var value by name (with -- prefix). */
export function cssVar(name: string): string {
  return root().getPropertyValue(name).trim();
}

/** Check if dark mode is active on <html>. */
export function isDarkMode(): boolean {
  return document.documentElement.classList.contains('dark');
}

/** Reactive token accessor — re-reads from DOM on each access. */
export const tokens = {
  get color()       { return pick(COLOR_KEYS); },
  get surface()     { return pick(SURFACE_KEYS); },
  get border()       { return pick(BORDER_KEYS); },
  get text()         { return pick(TEXT_KEYS); },
  get spacing()      { return pick(SPACING_KEYS); },
  get radius()       { return pick(RADIUS_KEYS); },
  get shadow()       { return pick(SHADOW_KEYS); },
  get font()         { return pick(FONT_KEYS); },
  get fontSize()     { return pick(FONTSIZE_KEYS); },
  get transition()   { return pick(TRANSITION_KEYS); },
  get zIndex()       { return pick(Z_KEYS); },
  get layout()       { return pick(LAYOUT_KEYS); },
} as const;