# Codename

> I'm Afraid I Can't Let You Do That

A prompt-engineering project exploring LLM security through adversarial prompting: a defending bot protects a hidden codeword behind a password, while an attacking bot tries to extract it through crafted prompts.

## Table of Contents

- [Overview](#overview)
- [Files](#files)

## Overview

The project is made of two prompts rather than code:

- a **defense** prompt, instructing a bot to protect a secret codeword and only reveal it when given the correct password
- an **attack** prompt, designed to extract the codeword from a defending bot as reliably as possible, across different kinds of defenses

It's a hands-on exploration of prompt injection and prompt hardening techniques, framed as an attack-versus-defense game between LLM bots.

## Files

### `defense.prompt`

The system prompt given to the defending bot. It protects a codeword behind a password and reveals the codeword only when presented with the correct password.

### `attack.prompt`

The prompt used to attack an opposing bot and try to make it reveal its codeword.