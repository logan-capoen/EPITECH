# Hack & Juice

> A Pentest a Day Keeps the Hackers Away

A collection of penetration-testing write-ups produced while hacking [OWASP Juice Shop](https://owasp-juice.shop/), a deliberately vulnerable web application showcasing the OWASP Top 10 security risks.

## Table of Contents

- [Overview](#overview)
- [Repository structure](#repository-structure)
- [Report contents](#report-contents)

## Overview

Each report documents a vulnerability found and exploited in Juice Shop: how it was discovered, how it was exploited, why it matters, and how it could be fixed.

## Repository structure

Each solved challenge has its own Markdown file at the root of the repository, named:

```
categoryName-difficultyLevel-challengeName.md
```

For example: `Broken Access Control-3-CSRF.md`, `Broken authentication-4-Login Bjoern.md`.

## Report contents

Each report covers:

- **Methodology** — numbered steps, the techniques used (OSINT, enumeration, scanning, brute force, ...), and the tools involved (search engines, SQLmap, Burp, scripts, wordlists, ...).
- **Vulnerability** — its name (injection, XSS, misconfiguration, CWE reference, ...), the affected component, and an estimated severity.
- **Risk** — the potential business impact (data leak, reputational damage, ...).
- **Remediation** — mitigation strategies, suggested fixes, and related security best practices.

Some reports also include supporting evidence, such as screenshots, logs, scripts, or traffic captures.