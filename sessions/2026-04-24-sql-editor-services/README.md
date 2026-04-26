# SQL editor services for `sen::lang` + term integration

**Date:** 2026-04-24
**Source branch:** off `feat/term-component`
**Status (as of 2026-04-26):** mixed. See per-patch breakdown below.

## What this session did

Built a `sen::lang::query` subsystem (tokenize / validate / complete / guideAt + WHERE-on-empty-optional evaluation) and wired it into the term component for a SQL-editor UX, plus three follow-on term-polish patches.

## Per-patch status against `feat/term-component`

| # | Patch | Status |
|---|---|---|
| 0001 | `feat[core,lang]: tolerant scanner, recoverable parser, scoped error reporter` | **Partial.** The scanner half landed on tc as `27403ab feat[core/lang]: tolerant scanning and scoped error reporter` (with the `diagnostic.{h,cpp}` files renamed to `error_reporter.{h,cpp}`). The **recoverable-parser half** of this patch — changes to `stl_parser.{h,cpp}` plus the 321-line `parser_test.cpp` — has not landed. Worth re-extracting the parser-only delta if you want to revive it. |
| 0002 | `feat[core/lang]: add query::tokenize() and query::validate()` | Pending. tc has no `libs/core/include/sen/core/lang/query/` subtree. |
| 0003 | `feat[core/lang]: add query::complete() with positional FSM` | Pending. tc's term-side completer (`99c3a07`) is a different, term-only implementation that does not use `sen::lang::query`. |
| 0004 | `feat[core/lang]: add query::guideAt() for cursor positions` | Pending. |
| 0005 | `feat[core/lang]: evaluate WHERE on empty optionals as false` | Pending. |
| ~~0006~~ | ~~`feat[term]: integrate sen::lang::query for SQL editor UX`~~ | **Dropped from this archive.** Superseded on tc by `99c3a07 feat[term]: extract query completion and highlighting into self-contained modules` and `29729b9 feat[term]: always-on query editing with live syntax highlight and validity`, which redesigned the term completer **without** depending on `sen::lang::query`. Reviving the lang-query approach is a separate decision. |
| 0007 | `fix[term]: SQL error UX and duplicate query-name rejection` | Pending. |
| 0008 | `chore[term]: misc cleanups and portability fixes` | Pending. |
| 0009 | `fix[term]: k9s-style ESC behavior with double-press confirm` | Pending. |
| 0010 | `feat[term]: add hidden easter-egg responses for common typos` | Pending. |

## Apply

```sh
git am sessions/2026-04-24-sql-editor-services/*.patch
```

Note the gap between `0005` and `0007` (no `0006` in this archive). The patches are independently numbered from `git format-patch`; `git am` in filename order is fine.

If you only want the work that hasn't landed in any form on `feat/term-component`, skip `0001` (or keep it and accept that the scanner half will fail to apply where `27403ab` already changed the same lines — `git am --3way` will prompt).
