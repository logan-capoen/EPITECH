# My Teams

> Collaborative Communication Application — Epitech

A Microsoft Teams–style collaborative communication server (`myteams_server`) and CLI client (`myteams_cli`), built on a custom TCP protocol, organizing discussions into teams, channels, threads and personal messages.

## Table of Contents

- [Overview](#overview)
- [Compilation](#compilation)
- [Server](#server)
- [CLI client](#cli-client)
- [Data model](#data-model)
- [Security](#security)

## Overview

Communication is organized into teams, each containing channels, each containing threads (an initial post plus comments), alongside personal, one-to-one discussions between users. The server and client exchange data over TCP sockets, using a custom protocol documented in RFC style, and rely on a shared logging library to display every event.

## Compilation

```bash
make          # builds `myteams_server` and `myteams_cli`
make clean    # removes object files
make fclean   # removes object files and the binaries
make re       # fclean then rebuild
```

## Server

```bash
./myteams_server port
```

The server handles multiple clients at once using `poll` (no forking or threading). Its state — users, teams, channels, threads and comments, along with personal discussions — is saved to the current folder on shutdown (including on `Ctrl-C`) and reloaded automatically on startup if a save file is found.

## CLI client

```bash
./myteams_cli ip port
```

Commands, read from standard input:

- `/help` — show help
- `/login "user_name"` — set the client's user name
- `/logout` — disconnect from the server
- `/users` — list all users on the domain
- `/user "user_uuid"` — show details about a user
- `/send "user_uuid" "message_body"` — send a personal message
- `/messages "user_uuid"` — list messages exchanged with a user
- `/subscribe "team_uuid"` — subscribe to a team's events
- `/subscribed [team_uuid]` — list subscribed teams, or users subscribed to a team
- `/unsubscribe "team_uuid"` — unsubscribe from a team
- `/use [team_uuid] [channel_uuid] [thread_uuid]` — set the current team/channel/thread context
- `/create` — create a resource in the current context (see below)
- `/list` — list resources in the current context (see below)
- `/info` — show details about the current context (see below)

All command arguments are double-quoted; a missing quote is treated as an error. Names are limited to 32 characters, descriptions to 255, and message/comment bodies to 512.

### `/create`

| Context | Creates |
|---|---|
| none | a team — `/create "team_name" "team_description"` |
| team | a channel — `/create "channel_name" "channel_description"` |
| team + channel | a thread — `/create "thread_title" "thread_message"` |
| team + channel + thread | a comment — `/create "comment_body"` |

### `/list`

| Context | Lists |
|---|---|
| none | all teams |
| team | all channels |
| team + channel | all threads |
| team + channel + thread | all comments |

### `/info`

| Context | Shows |
|---|---|
| none | the logged-in user |
| team | the selected team |
| team + channel | the selected channel |
| team + channel + thread | the selected thread |

## Data model

The logging library (pushed at `libs/myteams/` at the root of the repository) is used to print every server event and to display data received from the server.

## Security

A user must be logged in to see the list of connected users. Only users subscribed to a team can create threads in it or receive its events.