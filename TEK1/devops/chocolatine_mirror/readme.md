# Chocolatine

> Improve Integration and Testing with GitHub Actions — Epitech

A self-contained GitHub Actions workflow (`chocolatine.yml`) enforcing coding style checks, tests, and mirroring to an Epitech repository across Epitech projects.

## Table of Contents

- [Goal](#goal)
- [File location](#file-location)
- [Allowed actions](#allowed-actions)
- [Secrets](#secrets)
- [Trigger conditions](#trigger-conditions)
- [Environment variables](#environment-variables)
- [Jobs](#jobs)
- [Good practices](#good-practices)

## Goal

This workflow automates good development practices on a GitHub repository: checking compilation and coding style, running tests, and mirroring the repository to Epitech's servers.

## File location

A single YAML file, `chocolatine.yml`, placed either:

- at the root of the repository, or
- in `.github/workflows/`

The workflow must be self-contained (no external files) and reusable across different Epitech projects and technologies. Evaluation is done by copying only this file into a test repository's `.github/workflows` directory, with environment variables adjusted to the test environment.

## Allowed actions

Only two external actions are allowed:

- `actions/checkout`
- `pixta-dev/repository-mirroring-action`

Any other external action (e.g. from the GitHub Marketplace) is forbidden.

## Secrets

Any sensitive value must be passed through secrets, never hardcoded. A hardcoded sensitive value in the workflow file invalidates the entire project.

## Trigger conditions

The workflow runs on every push and every pull request creation, **except** when:

- the branch name starts with `no-ga/`
- the current repository is the mirror repository itself

In both cases, no job defined by this workflow may run — exiting with a positive value is not considered proper handling.

Each job must:

- start by checking out the repository on the relevant branch
- only run if the previous job succeeded

Jobs must run in the order they are defined below.

## Environment variables

Defined once, at the workflow level, and available to every job and step:

- `MIRROR_SSH_URL` — SSH URL of the Epitech mirror repository
- `EXECUTABLES` — comma-separated list of expected executable paths (e.g. `"mysh"` or `"directory1/subdirectory2/my_hunter"`, or `"directory1/executableA,directory2/executableB"`)

## Jobs

### `check_compilation_and_coding_style`

Runs in an `epitechcontent/epitest-docker` container. Each of the following is a separate step:

1. Run `banana-check-repo` at the repository root.
2. Run `make` at the repository root (2-minute timeout). `CC` must be set to `epiclang` for this step, so the Banana coding style plugin is loaded.
3. Display each coding style error as an error annotation, pointing to the offending line.
4. Fail the job if any coding style error was found.
5. Run `make clean` at the repository root.
6. Verify that every file listed in `EXECUTABLES` exists and is executable; fail the job otherwise.

### `run_tests`

Runs in an `epitechcontent/epitest-docker` container, and launches `make tests_run` at the repository root (2-minute timeout).

### `push_to_mirror`

Mirrors the repository to `MIRROR_SSH_URL`, using a secret named `GIT_SSH_PRIVATE_KEY` for the SSH private key. Only runs on push events.

## Good practices

- Give meaningful names to jobs and steps.
- Prefer built-in GitHub Actions features over custom shell commands whenever possible.
- Use the latest versions of actions.
- Only fetch what is necessary when checking out.
- Display missing or non-executable executables as error annotations.