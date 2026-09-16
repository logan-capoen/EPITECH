# EpyTodo

> Build an API to Create a Todo App — Epitech

A REST API, built with TypeScript, Express and MySQL, powering a Todo List application: user registration/authentication and CRUD management of tasks.

## Table of Contents

- [Overview](#overview)
- [Project structure](#project-structure)
- [Environment variables](#environment-variables)
- [Database](#database)
- [Installation](#installation)
- [Authentication](#authentication)
- [Error format](#error-format)
- [Routes](#routes)

## Overview

The API is a CRUD system exchanging JSON data over HTTP, backed by a MySQL database with two tables: `user` and `todo`.

## Project structure

```
.
├── .env
├── package.json
├── tsconfig.json
├── epytodo.sql
└── src
    ├── config
    │   └── db.ts
    ├── index.ts
    ├── middleware
    │   ├── auth.ts
    │   └── notFound.ts
    └── routes
        ├── auth
        │   └── auth.ts
        ├── todos
        │   ├── todos.ts
        │   └── todos.query.ts
        └── user
            ├── user.ts
            └── user.query.ts
```

- `config` — database connection setup.
- `index.ts` — entry point, starts the app.
- `middleware` — middlewares (authentication, not-found handling, ...).
- `routes` — route handlers, grouped by resource.

## Environment variables

Defined in `.env`:

- `MYSQL_DATABASE`
- `MYSQL_HOST`
- `MYSQL_USER`
- `MYSQL_ROOT_PASSWORD`
- `PORT` — port used by the Express server
- `SECRET` — used to sign JSON Web Tokens

## Database

`epytodo.sql`, at the root of the repository, contains the schema for the `epytodo` database, with two tables:

**`user`**

- `id` — auto-increment, primary key
- `email` — unique, not null
- `password` — not null (stored hashed, never in plain text)
- `name` — not null
- `firstname` — not null
- `created_at` — defaults to the current datetime

**`todo`**

- `id` — auto-increment, primary key
- `title` — not null
- `description` — not null
- `created_at` — defaults to the current datetime
- `due_time` — not null, datetime
- `status` — `not started` (default), `todo`, `in progress`, or `done`
- `user_id` — references the assigned user's `id`

Importing the schema:

```bash
cat epytodo.sql | mysql -u root -p
```

## Installation

```bash
npm install
npm run start   # tsx src/index.ts
```

## Authentication

`/register` and `/login` are open; every other route requires a valid JWT in the `Authorization` header.

## Error format

| Case | Response |
|---|---|
| No token provided | `{ "msg": "No token, authorization denied" }` |
| Invalid token | `{ "msg": "Token is not valid" }` |
| Resource not found | `{ "msg": "Not found" }` |
| Bad parameters | `{ "msg": "Bad parameter" }` |
| Other error | `{ "msg": "Internal server error" }` |

## Routes

| Route | Method | Protected | Description |
|---|---|---|---|
| `/register` | POST | no | register a new user |
| `/login` | POST | no | connect a user |
| `/user` | GET | yes | view logged-in user information |
| `/user/todos` | GET | yes | view all user tasks |
| `/users/:id` or `/users/:email` | GET | yes | view user information |
| `/users/:id` | PUT | yes | update user information |
| `/users/:id` | DELETE | yes | delete user |
| `/todos` | GET | yes | view all todos |
| `/todos/:id` | GET | yes | view a todo |
| `/todos` | POST | yes | create a todo |
| `/todos/:id` | PUT | yes | update a todo |
| `/todos/:id` | DELETE | yes | delete a todo |

### `POST /register`

Request:

```json
{
  "email": "nao.marvin@epitech.eu",
  "name": "Marvin",
  "firstname": "Nao",
  "password": "3paulbec"
}
```

Response:

```json
{ "token": "Token of the newly registered user" }
```

If the account already exists:

```json
{ "msg": "Account already exists" }
```

### `POST /login`

Request:

```json
{
  "email": "username",
  "password": "password"
}
```

Response:

```json
{ "token": "Token of the newly logged in user" }
```

If the credentials are incorrect:

```json
{ "msg": "Invalid Credentials" }
```

### `GET /user`

```json
{
  "id": 1,
  "email": "email@test.eu",
  "password": "hashed password",
  "created_at": "2021-03-03 19:24:00",
  "firstname": "test",
  "name": "test"
}
```

### `GET /user/todos`

```json
[
  {
    "id": 1,
    "title": "title",
    "description": "desc",
    "created_at": "2021-03-03 19:24:00",
    "due_time": "2021-03-04 19:24:00",
    "user_id": 3,
    "status": "done"
  },
  {
    "id": 2,
    "title": "title",
    "description": "desc",
    "created_at": "2021-03-05 19:24:00",
    "due_time": "2021-03-06 19:24:00",
    "user_id": 3,
    "status": "in progress"
  }
]
```

### `GET /users/:id` and `GET /users/:email`

```json
{
  "id": 1,
  "email": "email@test.eu",
  "password": "hashed password",
  "created_at": "2021-03-03 19:24:00",
  "firstname": "test",
  "name": "test"
}
```

### `PUT /users/:id`

Request:

```json
{
  "email": "updated_email@test.eu",
  "password": "updated_password",
  "firstname": "updated_test",
  "name": "updated_test"
}
```

Response: the updated user (same shape as `GET /users/:id`).

### `DELETE /users/:id`

```json
{ "msg": "Successfully deleted record number: ${id}" }
```

### `GET /todos`

```json
[
  {
    "id": 1,
    "title": "title",
    "description": "desc",
    "created_at": "2021-03-03 19:24:00",
    "due_time": "2021-03-04 19:24:00",
    "user_id": 1,
    "status": "done"
  },
  {
    "id": 2,
    "title": "title",
    "description": "desc",
    "created_at": "2021-03-05 19:24:00",
    "due_time": "2021-03-06 19:24:00",
    "user_id": 2,
    "status": "in progress"
  }
]
```

### `GET /todos/:id`

```json
{
  "id": 2,
  "title": "title",
  "description": "desc",
  "created_at": "2021-03-05 19:24:00",
  "due_time": "2021-03-06 19:24:00",
  "user_id": 3,
  "status": "in progress"
}
```

### `POST /todos`

Request:

```json
{
  "title": "title",
  "description": "desc",
  "due_time": "2021-03-06 19:24:00",
  "user_id": 3,
  "status": "todo"
}
```

Response: the created todo (same shape as `GET /todos/:id`).

### `PUT /todos/:id`

Request:

```json
{
  "title": "Updated title",
  "description": "Updated desc",
  "due_time": "2021-03-07 19:24:00",
  "user_id": 1,
  "status": "in progress"
}
```

Response: the updated todo (same shape as `GET /todos/:id`).

### `DELETE /todos/:id`

```json
{ "msg": "Successfully deleted record number: ${id}" }
```

Every response uses an appropriate HTTP status code.