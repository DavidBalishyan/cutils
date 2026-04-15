# Cutils

A from-scratch reimplementation of select GNU coreutils in C, built for fun and learning.

Powered by [`clibx.h`](clibx.h) - a single-header utility library with macros for memory, math, logging, type introspection, and more.

---

## Implemented tools

| Tool     | Description                              | GNU equivalent |
|----------|------------------------------------------|----------------|
| `ccat`  | Print the contents of a file to stdout   | `cat`          |
| `cecho` | Print arguments to stdout                | `echo`         |
| `cps`   | List running processes from `/proc`      | `ps`           |

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

---

## clibx.h

A single-header C utility library included across all tools, developed at [github.com/DavidBalishyan/clibx](https://github.com/DavidBalishyan/clibx). Highlights:

- **Array helpers** - `ARRAY_SIZE`, `print_int_array`, `print_double_array`
- **Math macros** - `MIN`, `MAX`, `CLAMP`, `ABS`, `LERP`, `IS_POWER_OF_2`
- **Memory macros** - `NEW`, `NEW_ARRAY`, `NEW_ZEROED`, `FREE`
- **Debug/logging** - `LOG`, `ERROR`, `ASSERT`, `UNIMPLEMENTED`, `UNREACHABLE`
- **Loop helpers** - `FOR(i, n)`, `FOR_RANGE(i, start, end)`
- **Boolean shim** - `clibx_bool`, `clibx_true`, `clibx_false` for C99/C11
- **String macros** - `STREQ`, `STR_EMPTY`, `STR_STARTS_WITH`
- **Generic printing** - `PRINT(x)` dispatches on type via `_Generic`
- **GCC/Clang extras** - `SWAP`, `LIKELY`, `UNLIKELY`, `UNUSED`, `DEPRECATED`, `NODISCARD`

---

## License

This project is licensed under the [MIT](https://opensource.org/license/MIT) license<br>
[See the LICENSE file](LICENSE)