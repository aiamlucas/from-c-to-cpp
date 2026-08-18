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

`<<`  insertion operator   (push data INTO the stream)
`>>`  extraction operator  (pull data OUT of the stream)

```cpp
std::cout << "hello" << " " << "world" << std::endl;
```

`std::endl` flushes the buffer and adds `\n`. 
Use `"\n"` when you don't need the flush.

`std::cout` is **type-safe**: the compiler knows the type of what you are printing and will error if something is wrong. `printf` has no such check (a format/argument mismatch is undefined behavior caught only at runtime).

> Type-safe: printf("%d", "hello") compiles and crashes at runtime. std::cout << someInt —> the compiler picks the right behavior for int automatically based on the type. No format specifier, no mismatch possible.

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

#### Null bytes in std::string vs C strings

```
C string  ("hello"):
─────────────────────
char *s = "hello";

  position:     0    1    2    3    4    5
              ┌────┬────┬────┬────┬────┬────┐
              │ h  │ e  │ l  │ l  │ o  │ \0 │
              └────┴────┴────┴────┴────┴────┘
                                          ↑
                                  string ENDS at \0
                                  strlen() reads until it hits \0

If you put \0 in the middle:
              ┌────┬────┬────┬────┬────┬────┬────┐
              │ h  │ e  │ \0 │ l  │ o  │ \0 │ ?  │
              └────┴────┴────┴────┴────┴────┴────┘
                       ↑
                  strlen() stops HERE → reports length 2
                  "llo" is invisible to all C string functions
                  data is technically there but unreachable
```
```
std::string  ("he\0llo"):
─────────────────────────
std::string s("he\0llo", 5);   // explicit length

  ┌─────────────────────────┐
  │ length: 5               │   ← stored separately
  │ data:                   │
  │   ┌────┬────┬────┬────┬────┐
  │   │ h  │ e  │ \0 │ l  │ o  │
  │   └────┴────┴────┴────┴────┘
  └─────────────────────────┘

  s.length()  →  5     (knows length independently)
  s[2]        →  \0    (you can read it)
  s[3]        →  l     (still accessible!)

  std::cout << s.length()  →  5
  std::cout << s           →  prints "he", terminal sees \0 and stops
                              but the data is all there
```

> WHY DOES THIS MATTER? BINARY DATA FILE CONTENTS, NETWORK PACKETS AND ENCRYPTED DATA CAN CONTAIN \0 BYTES NATURALLY. C STRINGS CAN'T HOLD THEM, BUT STD::STRING CAN.

---

## CHARACTER MANIPULATION — CCTYPE

`<CCTYPE>` IS THE C++ NAME FOR C'S `<CTYPE.H>`. SAME FUNCTIONS: `TOUPPER`, `TOLOWER`, `ISALPHA`, `ISDIGIT`, `ISSPACE`.

`TOUPPER(C)` RETURNS THE UPPERCASE VERSION OF A CHAR. NON-LETTER CHARACTERS PASS THROUGH UNCHANGED.

**THE CORRECT CAST:** `TOUPPER` EXPECTS `UNSIGNED CHAR`. ON PLATFORMS WHERE `CHAR` IS SIGNED, PASSING A NEGATIVE CHAR VALUE IS UNDEFINED BEHAVIOR. SAFE FORM:

```CPP
STR[I] = TOUPPER((UNSIGNED CHAR)STR[I]);
```

FOR ASCII-ONLY INPUT THIS NEVER SURFACES, BUT IT IS THE CORRECT PATTERN.
