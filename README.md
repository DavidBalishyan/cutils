# Cutils

A from-scratch reimplementation of select GNU coreutils in C, built for fun and learning.

Powered by [`clibx.h`](clibx.h) - a single-header utility library with macros for memory, math, logging, type introspection, dynamic arrays, hash maps, and more.

---

## Implemented tools

| Tool     | Description                              | GNU equivalent |
|----------|------------------------------------------|----------------|
| `ccat`  | Print the contents of a file to stdout   | `cat`          |
| `cecho` | Print arguments to stdout                | `echo`         |
| `cps`   | List running processes from `/proc`      | `ps`           |
| `cls`   | List directory contents                  | `ls`           |
| `cwc`   | Count lines, words, and bytes            | `wc`           |
| `chead` | Print first N lines of a file            | `head`         |
| `ctail` | Print last N lines of a file             | `tail`         |
| `csort` | Sort lines of text                       | `sort`         |
| `ccp`   | Copy files                               | `cp`           |
| `cmv`   | Move or rename files                     | `mv`           |

---

## Building

Requires a C11-compatible compiler (`gcc` or `clang`) and `make`.

```sh
make          # builds all tools into ./bin/
make clean    # removes ./bin/
make test     # runs a quick smoke-test for each tool
```

### Install to `~/.local/bin`

```sh
make install
```

Override the prefix to install elsewhere:

```sh
make install PREFIX=/usr/local   # installs to /usr/local/bin (may need sudo)
```

Uninstall:

```sh
make uninstall
```

---

## Usage

### ccat

```sh
./bin/ccat <file>
```

Reads a file character by character and prints it to stdout. Exits with an error if the file cannot be opened.

### cecho

```sh
./bin/cecho [args...]
```

Prints all arguments separated by spaces, followed by a newline.

### cps

```sh
./bin/cps
```

Reads `/proc` to list all running processes with their PID and command line. Linux only.

### cls

```sh
./bin/cls [options] [directory]
```

Lists directory contents. Options:
- `-l` / `--long` - Long format (permissions, size, date)
- `-a` / `--all` - Show hidden files (dotfiles)
- `-la` - Combined long format with hidden files

### cwc

```sh
./bin/cwc [files...]
```

Counts lines, words, and bytes. Reads from stdin if no file is given.

### chead

```sh
./bin/chead [-n N] [file]
```

Prints the first N lines (default: 10). Reads from stdin if no file is given.

### ctail

```sh
./bin/ctail [-n N] [file]
```

Prints the last N lines (default: 10). Reads from stdin if no file is given.

### csort

```sh
./bin/csort [options] [file]
```

Sorts lines alphabetically. Options:
- `-r` / `--reverse` - Reverse order
- Reads from stdin if no file is given.

### ccp

```sh
./bin/ccp <source> <destination>
```

Copies a file. If destination is a directory, copies into it preserving the filename.

### cmv

```sh
./bin/cmv <source> <destination>
```

Moves or renames a file.

---

## clibx.h

A single-header C utility library included across all tools, developed at [github.com/DavidBalishyan/clibx](https://github.com/DavidBalishyan/clibx). Highlights:

- **Array helpers** - `ARRAY_SIZE`, `print_int_array`, `print_double_array`
- **Math macros** - `MIN`, `MAX`, `CLAMP`, `ABS`, `LERP`, `IS_POWER_OF_2`, `NEXT_POWER_OF_2`
- **Memory macros** - `NEW`, `NEW_ARRAY`, `NEW_ZEROED`, `FREE`
- **Debug/logging** - `LOG`, `ERROR`, `ASSERT`, `UNIMPLEMENTED`, `UNREACHABLE`
- **Loop helpers** - `FOR(i, n)`, `FOR_RANGE(i, start, end)`
- **Boolean shim** - `clibx_bool`, `clibx_true`, `clibx_false` for C99/C11
- **String macros** - `STREQ`, `STR_EMPTY`, `STR_STARTS_WITH`, `STR_CONTAINS`
- **String functions** - `strtrim`, `strsplit`, `strjoin`, `str_to_lower`, `str_to_upper`
- **Generic printing** - `PRINT(x)` dispatches on type via `_Generic`
- **GCC/Clang extras** - `SWAP`, `LIKELY`, `UNLIKELY`, `UNUSED`, `DEPRECATED`, `NODISCARD`
- **Dynamic arrays** - `str_vec` with `vec_init`, `vec_push`, `vec_free`
- **Path utilities** - `path_basename`, `path_dirname`, `path_extension`, `path_join`, `path_exists`, `path_is_dir`, `path_is_file`, `path_file_size`
- **Hash map** - `clibx_hashmap` with `hashmap_init`, `hashmap_put`, `hashmap_get`, `hashmap_contains`, `hashmap_free`
- **I/O utilities** - `read_line`

---

## License

This project is licensed under the [MIT](https://opensource.org/license/MIT) license<br>
[See the LICENSE file](LICENSE)
