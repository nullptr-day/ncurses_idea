# STL syntax highlighting and grammar reference

**Date:** 2026-04-23
**Source branch:** `feat/term-component` derivative
**Status (as of 2026-04-26):** all four patches still pending — none merged on `origin/main` or `origin/feat/term-component`.

## What this session did

Adds first-class editor and tooling support for the **Sen Type Language (STL)**:

- **0001 — `docs[stl]: add formal grammar reference and fill user guide`.** Writes the formal grammar of STL into the user guide and fills in supporting prose.
- **0002 — `tools: add editor support for STL syntax highlighting`.** TextMate-style grammar plus a small VS Code extension scaffolding.
- **0003 — `tools: add GitHub Linguist submission materials`.** Files needed for the GitHub Linguist PR so STL renders with the right colors on github.com.
- **0004 — `docs[stl]: refactor user guide for clarity and completeness`.** Polishes the user guide that 0001 expanded.

## Apply

```sh
git am sessions/2026-04-23-stl-highlight/*.patch
```

The four patches form a sequence; apply in order (filename order works).
