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

| Tool     | Binary   | Primary behavior | Notes |
|----------|----------|------------------|-------|
| `ccat`   | `bin/ccat` | Print a file to stdout character-by-character | Simple file reader; adds a trailing newline. |
| `cecho`  | `bin/cecho` | Print command arguments separated by spaces | No special escape handling. |
| `cps`    | `bin/cps` | List running Linux processes from `/proc` | Reads `/proc/<pid>/cmdline`. Linux-only. |
| `cls`    | `bin/cls` | List directory contents | Supports `-l`, `-a`, and `-la`. |
| `cwc`    | `bin/cwc` | Count lines, words, and bytes | Accepts either stdin or one or more files. |
| `chead`  | `bin/chead` | Print the first N lines of input | Supports `-nN` and `-n N`. |
| `ctail`  | `bin/ctail` | Print the last N lines of input | Uses a dynamic line buffer. |
| `csort`  | `bin/csort` | Sort lines lexicographically | Supports reverse order. |
| `ccp`    | `bin/ccp` | Copy files | Preserves filename when destination is a directory. |
| `cmv`    | `bin/cmv` | Move/rename files | Wraps `rename()`. |

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
make install PREFIX=/usr/local
```

### Uninstall

```sh
make uninstall
```

---

## Usage

### ccat

```sh
./bin/ccat file.txt
```

Prints the file contents to stdout and appends a final newline.

### cecho

```sh
./bin/cecho Hello world
```

Prints each argument separated by a single space.

### cps

```sh
./bin/cps
```

Lists processes by reading `/proc` and printing PID + command line.
This utility is intended for Linux systems only.

### cls

```sh
./bin/cls [options] [directory]
```

Options:
- `-l`, `--long` - use long listing format.
- `-a`, `--all` - show hidden files.
- `-la`, `-al`, `--long-all` - combine long format and hidden files.

### cwc

```sh
./bin/cwc [files...]
```

Counts lines, words, and bytes.
If no filename is provided, it reads from stdin.

### chead

```sh
./bin/chead [-n N] [file]
```

Prints the first `N` lines of a file or stdin. Defaults to `10` lines.
Supports both `-n10` and `-n 10` forms.

### ctail

```sh
./bin/ctail [-n N] [file]
```

Prints the last `N` lines of a file or stdin. Defaults to `10` lines.

### csort

```sh
./bin/csort [options] [file]
```

Options:
- `-r`, `--reverse` - sort in reverse order.

### ccp

```sh
./bin/ccp <source> <destination>
```

Copies a file to the destination path. If the destination is a directory,
`ccp` copies the file into that directory while preserving the source filename.

### cmv

```sh
./bin/cmv <source> <destination>
```

Moves or renames a file using the POSIX `rename()` syscall

---

## Implementation notes

- Most utilities are intentionally minimal: they focus on readable control flow rather than handling every edge case.
- `clibx.h` provides shared helpers for memory, strings, error reporting, and dynamic arrays.
- `chead` and `ctail` use `getline()` to support arbitrary-length input lines.
- `csort` loads the entire input into memory before sorting, which is fine for small to moderate text but not optimized for very large files.
- `cps` enumerates numeric directories in `/proc`, so it is only usable on Linux-like systems.

---

## License

This project is licensed under the [MIT](https://opensource.org/license/MIT) license.
See the [LICENSE](LICENSE) file for details.
