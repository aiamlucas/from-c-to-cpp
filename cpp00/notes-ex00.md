# ex00 — Megaphone

Concepts: `iostream`, `std::string`, `argc`/`argv`, character manipulation

---

## Output — std::cout

A **stream** is an abstraction for a sequence of data flowing in one direction: to a file, to the terminal, to a network socket. 
You write into it without caring about what is on the other end.

```
your code  →  std::cout  →  [ stdout stream ]  →  terminal
your code  →  std::cerr  →  [ stderr stream ]  →  terminal (unbuffered)
```

`<<` is the insertion operator: it pushes data into the stream and can be chained:

```cpp
std::cout << "hello" << " " << "world" << std::endl;
```

`std::endl` flushes the buffer and adds `\n`. 
Use `"\n"` when you don't need the flush.

`std::cout` is **type-safe**: the compiler knows the type of what you are printing and will error if something is wrong. `printf` has no such check (a format/argument mismatch is undefined behavior caught only at runtime).

---

## argc and argv

Identical to C. `argv[i]` can be assigned directly to a `std::string`, which converts automatically.

---

## std::string

`std::string` owns its memory, knows its length, and handles copying correctly.

In C a string is a pointer to a null-terminated char array, you manage the memory, track the size, and free it yourself.
Copying a `char *` copies only the pointer:

```
C:
  a ──► [ h | e | l | l | o | \0 ]
  b ──►  same block          ← one change affects both

C++:
  a ──► [ h | e | l | l | o ]
  b ──► [ h | e | l | l | o ]  ← independent copy
```

### Key operations

| Operation   | C                          | C++                        |
|-------------|----------------------------|----------------------------|
| Length      | `strlen(s)`                | `s.length()`               |
| Concatenate | `malloc` + `strcat`        | `s1 + s2` / `s += "..."`  |
| Compare     | `strcmp(a, b) == 0`        | `a == b`                   |
| Substring   | `strncpy` / ptr arithmetic | `s.substr(start, len)`     |
| Search      | `strstr` / `strchr`        | `s.find("...")`            |
| Empty check | `s[0] == '\0'`             | `s.empty()`                |
| Single char | `s[i]`                     | `s[i]` — same, type `char` |

### find and npos

`s.find("word")` returns the start index, or `std::string::npos` if not found — the sentinel value meaning "no position", equivalent to `NULL` for pointers.

### Edge cases

- `std::string` can hold null bytes mid-string — it tracks length separately, unlike C strings which terminate at the first `\0`.
- `s[i]` out of bounds is undefined behavior. Use `s.at(i)` for bounds-checked access (throws on invalid index).
- `s.length()` returns `size_t` (unsigned). Comparing with a signed `int` in a loop can cause subtle bugs, cast explicitly: `(int)s.length()`.

---

## Character manipulation — cctype

`<cctype>` is the C++ name for C's `<ctype.h>`. Same functions: `toupper`, `tolower`, `isalpha`, `isdigit`, `isspace`.

`toupper(c)` returns the uppercase version of a char. Non-letter characters pass through unchanged.

**The correct cast:** `toupper` expects `unsigned char`. On platforms where `char` is signed, passing a negative char value is undefined behavior. Safe form:

```cpp
str[i] = toupper((unsigned char)str[i]);
```

For ASCII-only input this never surfaces, but it is the correct pattern.
