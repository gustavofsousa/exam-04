<h1 align="center">exam-04 — microshell</h1>

<p align="center">
  <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-complete-brightgreen.svg" alt="Status">
</p>

<p align="center">
  A minimal shell implementation — written under exam conditions, from memory, in under 3 hours.
</p>

<p align="center">
  <a href="README.pt-br.md">🇧🇷 Leia em Português</a>
</p>

---

## Why this project matters

> "This project taught me how shells work at the operating system level — how fork and execve spawn processes, how pipes connect the stdout of one process to the stdin of another, and how file descriptors are duplicated and closed with dup2. These are the exact mechanisms behind every CI/CD pipeline, every shell script, and every container runtime."

The ability to implement `fork`, `execve`, `pipe`, and `dup2` under time pressure — without documentation — proves a solid understanding of UNIX process management.

---

## What was built

A minimal shell (`microshell`) that:

- Parses command-line arguments passed directly to `argv`
- Executes **external commands** via `execve`
- Handles the **built-in `cd`** command with proper error reporting
- Supports **pipes** (`|`) between commands
- Supports command **sequences** (`;`) on a single invocation
- Reports all errors to `stderr`

### Example usage

```bash
./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo done
```

---

## A standout technical detail

The `question_has_pipe()` function performs a lookahead scan on the argument list before forking — determining in advance whether a pipe is needed for the current command group. This avoids creating unnecessary file descriptors and mirrors how production shells optimize their execution model.

---

## How it works

```
argv[] = { "cmd1", "|", "cmd2", ";", "cmd3", NULL }
          └─ fork+pipe ─┘           └─ fork ─┘
```

1. Scan args until `;` or `NULL` — that's one "sentence"
2. Check if any `|` exists in the sentence
3. If yes: `pipe()` → `fork()` → child uses `dup2` to wire stdout to pipe write-end
4. Parent reads from pipe read-end and continues to next command
5. If no pipe: just `fork()` + `execve()`

---

## Getting Started

```bash
git clone https://github.com/gustavofsousa/exam-04.git
cd exam-04
gcc microshell.c -o microshell
```

### Running

```bash
./microshell /bin/echo "hello" "|" /usr/bin/tr 'a-z' 'A-Z'
# Output: HELLO
```

---

## Project structure

```
exam-04/
├── microshell.c    # Full implementation
├── microshell.h    # Header
└── base.c          # Practice/exploration files
```

---

## Skills demonstrated

- Process creation (`fork`, `execve`, `waitpid`)
- Pipes and file descriptor manipulation (`pipe`, `dup2`, `close`)
- UNIX signal and error handling
- Shell parsing and argument processing
- Writing correct, minimal C under time constraints

---

## License

This project was developed as part of the [42 School](https://42.fr) curriculum.

---

<p align="center">Made with ☕ at 42 Rio de Janeiro</p>
