# Cutils

A from-scratch reimplementation of selected GNU core utilities in C, built for learning and experimentation.

This repository contains a small toolchain of command-line utilities that mimic common Unix behavior with minimal external dependencies.
All programs are compiled with [`clibx.h`](https://davidbalishyan.github.io/clibx), a lightweight single-header utility library that centralizes common helpers for error handling, strings, dynamic arrays, file paths, and more.

---

## Project goals

- Recreate classic Unix tools in readable, idiomatic C.
- Keep implementations small and understandable.
- Preserve Unix-style CLI behavior wherever practical.
- Make the codebase easy to extend with additional tools later.

---

## Implemented tools

Sources are organized by GNU coreutils category:

| Category     | Directory             | Tools                         |
|--------------|-----------------------|-------------------------------|
| File utils   | `src/fileutils/`      | `cat`, `cp`, `ls`, `mv`       |
| Text utils   | `src/textutils/`      | `head`, `sort`, `tail`, `wc`  |
| Shell utils  | `src/shellutils/`     | `echo`, `ps`                  |

### Tool reference

| Tool   | Primary behavior                                                   |
|--------|--------------------------------------------------------------------|
| `cat`  | Print a file to stdout character-by-character; adds trailing newline. |
| `echo` | Print command arguments separated by spaces. No special escape handling. |
| `ps`   | List running Linux processes from `/proc`. Linux-only.             |
| `ls`   | List directory contents. Supports `-l`, `-a`, and `-la`.           |
| `wc`   | Count lines, words, and bytes. Accepts stdin or one or more files. |
| `head` | Print the first N lines of input. Supports `-nN` and `-n N`.       |
| `tail` | Print the last N lines of input. Uses a dynamic line buffer.       |
| `sort` | Sort lines lexicographically. Supports reverse order.              |
| `cp`   | Copy files. Preserves filename when destination is a directory.    |
| `mv`   | Move/rename files. Wraps `rename()`.                               |

---

## Build & install

### Requirements

- C11-compatible compiler such as `gcc` or `clang`
- `make`

### Build

```sh
make
```

This compiles each utility into the `bin/` directory.

By default binaries are named `cat`, `cp`, `ls`, etc. (no prefix). To build with a `c` prefix:

```sh
make TARGET_PREFIX=c
```

This produces `ccat`, `ccp`, `cls`, etc.

### Cleaning

```sh
make clean
```

### Install

```sh
make install
```

Install to an alternate directory:

```sh
make install INSTALL_PREFIX=/usr/local
```

### Uninstall

```sh
make uninstall
```

---

## Usage

### cat

```sh
./bin/cat file.txt
```

Prints the file contents to stdout and appends a final newline.

### echo

```sh
./bin/echo Hello world
```

Prints each argument separated by a single space.

### ps

```sh
./bin/ps
```

Lists processes by reading `/proc` and printing PID + command line.
This utility is intended for Linux systems only.

### ls

```sh
./bin/ls [options] [directory]
```

Options:
- `-l`, `--long` - use long listing format.
- `-a`, `--all` - show hidden files.
- `-la`, `-al`, `--long-all` - combine long format and hidden files.

### wc

```sh
./bin/wc [files...]
```

Counts lines, words, and bytes.
If no filename is provided, it reads from stdin.

### head

```sh
./bin/head [-n N] [file]
```

Prints the first `N` lines of a file or stdin. Defaults to `10` lines.
Supports both `-n10` and `-n 10` forms.

### tail

```sh
./bin/tail [-n N] [file]
```

Prints the last `N` lines of a file or stdin. Defaults to `10` lines.

### sort

```sh
./bin/sort [options] [file]
```

Options:
- `-r`, `--reverse` - sort in reverse order.

### cp

```sh
./bin/cp <source> <destination>
```

Copies a file to the destination path. If the destination is a directory,
`cp` copies the file into that directory while preserving the source filename.

### mv

```sh
./bin/mv <source> <destination>
```

Moves or renames a file using the POSIX `rename()` syscall.

---

## Implementation notes

- Most utilities are intentionally minimal: they focus on readable control flow rather than handling every edge case.
- `clibx.h` provides shared helpers for memory, strings, error reporting, and dynamic arrays.
- `head` and `tail` use `getline()` to support arbitrary-length input lines.
- `sort` loads the entire input into memory before sorting, which is fine for small to moderate text but not optimized for very large files.
- `ps` enumerates numeric directories in `/proc`, so it is only usable on Linux-like systems.

---

## License

This project is licensed under the [GPL-3.0](https://opensource.org/license/gpl-3.0) license.
See the [LICENSE](LICENSE) file for details.
