# Popeye

> Set Sail for the Amazing World of Containers — Epitech

A Dockerized, multi-container deployment of a simple web poll application, orchestrated with Docker Compose.

## Table of Contents

- [Goal](#goal)
- [Application components](#application-components)
- [Configuration](#configuration)
- [Docker images](#docker-images)
- [Docker Compose](#docker-compose)
- [End result](#end-result)
- [Environment variables and security](#environment-variables-and-security)

## Goal

This project containerizes and deploys a web poll application made of 5 components, using Docker and Docker Compose. The application code itself is provided and does not need to be written.

## Application components

- **Poll** — a Flask Python web application that gathers votes and pushes them into a Redis queue.
- **Redis** — a queue holding the votes sent by Poll, waiting to be consumed by the Worker.
- **Worker** — a Java application that consumes votes from the Redis queue and stores them in a PostgreSQL database.
- **PostgreSQL** — a database that persistently stores the votes.
- **Result** — a Node.js web application that fetches votes from the database and displays the results.

## Configuration

Poll, Worker and Result are configured through environment variables, set via Docker Compose only (never hardcoded in the Dockerfiles):

**Poll**

- `REDIS_HOST` — hostname of the Redis service

**Result**

- `POSTGRES_HOST` — hostname of the database service
- `POSTGRES_PORT` — port the database service listens on
- `POSTGRES_DB` — name of the PostgreSQL database
- `POSTGRES_USER` — user used to connect to the database
- `POSTGRES_PASSWORD` — password of that user

**Worker**

Uses the same environment variables as both Poll and Result.

## Docker images

Three images are built.

### Poll

- Based on an official Python image.
- Dependencies installed with `pip3 install -r requirements.txt`.
- Exposes and runs on port 80: `flask run --host=0.0.0.0 --port=80`.

### Result

- Based on an official Node.js 20 Alpine image.
- Exposes and runs on port 80.
- Dependencies installed with `npm install` (run from the correct location).
- `node_modules` must be excluded from the build context.

### Worker

Built with a multi-stage build.

- **Stage 1 — `builder`**, based on `maven:3.9.6-eclipse-temurin-21-alpine`:
  - `mvn dependency:resolve` (from the directory containing `pom.xml`)
  - `mvn package` (from the directory containing `src`)
  - produces `target/worker-jar-with-dependencies.jar`
- **Stage 2 — run**, based on `eclipse-temurin:21-jre-alpine`:
  - runs `java -jar worker-jar-with-dependencies.jar`

Images must stay simple and lightweight. The `ENTRYPOINT` instruction must not be used.

## Docker Compose

A `docker-compose.yml` file runs and links all containers.

**Services**

- `poll` — builds the Poll image, maps host port `5000` to container port `80`, sets the required environment variable.
- `redis` — uses an official Redis 7 image, opens port `6379`.
- `worker` — builds the Worker image, sets the same environment variables as `poll` and `result`.
- `db` — uses an official PostgreSQL 16 image, has its schema created on first start, sets the required environment variables. Must start before any service depending on it.
- `result` — builds the Result image, maps host port `5001` to container port `80`, sets the required environment variables.

**Networks**

- `poll-tier` — lets `poll` communicate with `redis`.
- `result-tier` — lets `result` communicate with `db`.
- `back-tier` — lets `worker` communicate with `redis` and `db`.

The `links` property is forbidden; networks must be used instead.

**Volumes**

- `db-data` — a named volume for persisting PostgreSQL data, mounted at the path documented on Docker Hub for the official image.

No unnecessary volumes, networks, inter-container dependencies, or container commands/entrypoints should be added.

## End result

Once `docker-compose.yml` is complete, all services can be started and accessed at:

- Poll: `http://localhost:5000`
- Result: `http://localhost:5001`

Voting on Poll's page must be reflected on Result's page. Containers must restart automatically if they stop unexpectedly.

## Environment variables and security

Apart from `POSTGRES_PASSWORD`, all environment variables and their values must be present in the repository (in environment files or directly in `docker-compose.yml`). `ENV` instructions in Dockerfiles, or environment files not referenced in `docker-compose.yml`, are ignored.

No password may be pushed to the repository. `POSTGRES_PASSWORD` must be passed through a mechanism that avoids hardcoding it in the repository.


`poll`, `result` and `worker` are the service directories provided with the project; `schema.sql` is also provided.