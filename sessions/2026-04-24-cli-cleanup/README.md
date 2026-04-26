# CLI audit, renames, and shell completion

**Date:** 2026-04-24
**Source branch:** `feature/cli-cleanup`
**Status (as of 2026-04-26):** pending — not on `origin/main` or `origin/feat/term-component`.

## What this session did

A single sweep over every `cli_*` binary:

- Help text normalised to imperative form ("Run a sen kernel", not "runs a sen kernel"); descriptions tightened.
- Subcommand and option renames matching the docker / gh / terraform conventions: `sen gen` → `sen generate`, `sen fileToArray` → `sen file-to-array`, `sen gen exp_package` → `sen generate cpp exports`, `--base_path` → `--base-path`. Old names kept as hidden aliases (`->group("")`) so existing scripts and CMake call-sites keep working; aliases are flagged deprecated in the spec so completion scripts omit them.
- A `sen completion <shell>` subcommand that prints the bash / zsh / fish completion script.
- Dead code removed: `getEnumerators` plus duplicated local `toSnakeCase` / `isUpperCamelCase` helpers across packages.
- Bracket-mismatch fix in `cli_remote_shell`'s positional hint.

## Apply

```sh
git am sessions/2026-04-24-cli-cleanup/0001-feat-cli-audit-renames-and-shell-completion-infrastr.patch
```

## Dependency note

The 2026-04-26 `installer-and-docs` session caches output of `sen completion <shell>` during install (the activate script sources the cached completion). That cache step degrades silently if `sen completion` is absent, so the installer applies cleanly on top of branches that lack this patch — but no shell completion will load until this patch also ships.
