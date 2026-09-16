# 42sh – A Feature-Rich UNIX Shell

**42sh** is a robust recreation of the classic `tcsh` shell, developed as part of the Epitech curriculum. This shell aims to reproduce and modernize key functionalities of traditional Unix shells, with added usability features such as command history, dynamic autocompletion, and advanced line editing.

## 🌟 Features

### 🔧 Command Parsing & Execution
- Chained Execution with Separators:
  - `;` – execute sequentially
  - `&&` – execute next only if the previous succeeds
  - `||` – execute next only if the previous fails
  - `|` – classic pipe for command chaining
- Parentheses Support: Execute grouped commands in a subshell context.
- Quotes Handling: Full parsing of single `'` quotes.

### 🗂️ Environment & Variables
- Environment Variables: Full support for exporting and referencing env vars (with `$`).
- Local Shell Variables: Define and use internal shell-only variables.

### 🧠 Aliases & History
- `alias` and `unalias` commands to define and remove command shortcuts.
- Persistent command history support.

### ✨ Globbing
- Supports wildcard expansion (`*`, `?`, etc.) in command-line arguments.

### ⚙️ Built-in Commands (Reimplemented)
- `cd`, `exit`, `set`, `unset`, `env`, `setenv`, `unsetenv`

### 🧵 Line Editing (termios-based)
Real-time command line editing with:
- CTRL-A: Move to beginning of line  
- CTRL-E: Move to end of line  
- CTRL-B: Move one character left  
- CTRL-F: Move one character right  
- CTRL-T: Transpose characters  
- CTRL-L: Clear screen

### 🔀 Autocompletion
Dynamic autocompletion using filesystem entries. Trigger with Tab.

## 🚀 Usage

Run the binary directly to start the shell:

```sh
git clone https://github.com/EpitechPGEPromo2029/B-PSU-200-LIL-2-1-42sh-mato.urbanac/ 42sh && cd 42sh && make
./42sh
```

You'll enter an interactive shell that mirrors many familiar Unix behaviors with added enhancements.

## 📁 Project Structure

- `src/` – Source files  
- `include/` – Header files  
- `libs/` – All of our made libs
- `tests/` – Functional tests  
- `Makefile` – Project build script

## 🧪 Examples

```sh
ls | grep *.c && echo 'C files listed' || echo 'No C files'
(cd src && cd - && make) ; echo Done
alias ll='ls -la'
echo 'Hello' $USER
```

## Collaborators 🤝

[Noam Bouillet](https://github.com/NoamBouillet) - [Mato Urbanac](https://github.com/Mato-u) - [Naëlle Guérin](https://github.com/naelle-guerin) - [Logan Capoen](https://github.com/logan-capoen) - [Léandre Fouret](https://github.com/Leandre-Fouret)  

## 📜 License

This is a student project developed for educational use only.

