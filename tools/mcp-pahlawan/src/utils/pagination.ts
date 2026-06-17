export interface Page<T> {
  items: T[];
  offset: number;
  limit: number;
  returned: number;
  truncated: boolean;
  nextCursor: number | null;
}

export function boundedLimit(value: number | undefined, fallback: number, maximum: number): number {
  return Math.min(Math.max(value ?? fallback, 1), maximum);
}

export function resolveOffset(cursor?: number, offset?: number): number {
  return Math.max(offset ?? cursor ?? 0, 0);
}

export function pageItems<T>(items: T[], offset: number, limit: number, hasMore?: boolean): Page<T> {
  const page = items.slice(0, limit);
  const truncated = hasMore ?? items.length > limit;
  return {
    items: page,
    offset,
    limit,
    returned: page.length,
    truncated,
    nextCursor: truncated ? offset + page.length : null,
  };
}
