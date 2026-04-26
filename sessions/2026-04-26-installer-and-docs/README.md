# Quick installer + install/build documentation rewrite

**Date:** 2026-04-26
**Source branch:** `feature/cli-cleanup`
**Status (as of 2026-04-26):** pending — not on `origin/main` or `origin/feat/term-component`.

## What this session did

Mbox file containing **four commits**:

1. **`feat[installer]: add curl|sh quick installer`** — single-file POSIX `sh` installer that drops a Sen release into `$HOME/.sen/<build-id>/` and writes activate scripts (bash/zsh and fish-native). Patterned after rustup / starship; no Conan, no sudo, Linux only. Includes 60+ bats tests and a GitHub Actions workflow.
2. **`fix[conan]: bundled profiles auto-detect arch and install system deps`** — `.conan/profiles/sen_gcc` and `sen_clang` now use `arch={{ detect_api.detect_arch() }}` (works on x86_64 CI runners and aarch64 Linux hosts) and set `tools.system.package_manager:mode=install` with `sudo=False` so Conan installs `libxext-dev` itself.
3. **`feat[installer]: UX polish, env-var fix, 'current' symlink, doc rename`** — banner with 6-color block bar mirroring the `term` component's style, status glyphs (`✓ ⚠ ℹ ✗`), step markers with cursor manipulation that collapses curl's progress bar into a single done line, deferred notes flushed as a single block at the end. Also fixes `LD_LIBRARY_PATH` to point at `<prefix>/bin` (where Sen actually installs its libs per `CMAKE_INSTALL_BINDIR`), drops `PKG_CONFIG_PATH` (Sen ships no `.pc` files), maintains `~/.sen/current` as a symlink to the latest install, and removes macOS support across the codebase. Renames `resources/installer/README.md` → `architecture.md` (Sen convention: README.md is user-facing only) with a developer-targeted rewrite.
4. **`docs[install]: rewrite install + build guides; remove macOS references`** — restructures `docs/getting_started/install.md` around three audiences (quick install, Conan dependency, manual zip), adds `docs/howto_guides/building_from_source.md` (linked from the Guides nav), polishes the root README with the `curl|sh` one-liner.

## Apply

The mbox preserves all four commits. Use `git am`:

```sh
git am sessions/2026-04-26-installer-and-docs/installer-and-docs.patch
```

Or, if you'd rather a single working-tree change:

```sh
git apply sessions/2026-04-26-installer-and-docs/installer-and-docs.patch
```

## Dependency notes

- The installer's `cache_completions` step calls `<prefix>/bin/sen completion <shell>`, which is added by the **2026-04-24 cli-cleanup** session. The step is best-effort (silently no-ops if the subcommand is missing) so this patch applies and works without that one — only shell completion is unavailable until both ship together.
- The Conan profile fix in commit 2 turned what used to be a CI-only profile (`sen_gcc` pinning `arch=x86_64` and assuming `libxext-dev` was pre-installed) into something usable on dev workstations and aarch64 hosts.
