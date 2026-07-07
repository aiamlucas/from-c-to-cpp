# cpp01 — ex02 — HI THIS IS BRAIN

Concepts: references, pointers, address-of operator, memory addresses

---

## Index

1. [What a reference is](#1-what-a-reference-is)
2. [Pointer vs reference](#2-pointer-vs-reference)
3. [The & operator — two meanings](#3-the--operator--two-meanings)
4. [Printing memory addresses](#4-printing-memory-addresses)
5. [Why all three print the same address](#5-why-all-three-print-the-same-address)

---

## 1. What a reference is

A reference is an **alias** — another name for an existing variable. It's not a copy, not a new object. It's the same object, accessible through a different name.

> References are a C++ feature — they don't exist in C.

```cpp
std::string brain = "HI THIS IS BRAIN";
std::string &stringREF = brain;   // stringREF is another name for brain
```

```
MEMORY:
┌──────────────────────┐
│ "HI THIS IS BRAIN"   │  ← one object in memory
└──────────────────────┘
↑               ↑
brain        stringREF
(original)   (alias — same address, same data)
```

There is only **one object**. `brain` and `stringREF` both refer to it. Changing one changes the other:

```cpp
stringREF = "SOMETHING ELSE";
std::cout << brain;   // prints "SOMETHING ELSE"
```

### Rules of references

```
must be initialized at declaration     →  std::string &ref = brain;  ✓
                                           std::string &ref;          ✗ error

cannot be rebound after initialization →  ref always refers to brain
                                           you cannot make ref point elsewhere

cannot be null                         →  a reference always refers to something valid
```

---

## 2. Pointer vs reference

Both give you indirect access to a variable. The difference is in how they work and what rules they follow.

```cpp
std::string  brain     = "HI THIS IS BRAIN";
std::string *stringPTR = &brain;    // pointer — holds the address of brain
std::string &stringREF = brain;     // reference — alias for brain
```

```
MEMORY:
                         0x7fff1000
                        ┌──────────────────────┐
                        │ "HI THIS IS BRAIN"   │  ← brain
                        └──────────────────────┘
                        ↑               ↑
┌──────────────┐        │               │
│  0x7fff1000  │ ───────┘               │
└──────────────┘                        │
  stringPTR                          stringREF
  (stores address)                   (alias — no separate storage)
```

### Side by side

```
                    POINTER                    REFERENCE
                    ───────────────────────    ───────────────────────
declaration         std::string *p = &s;       std::string &r = s;
get the value       *p                         r   (no syntax needed)
get the address     p                          &r
can be null         yes  (p = NULL)            no  (always valid)
can be rebound      yes  (p = &other)          no  (fixed at init)
needs init          no   (can declare empty)   yes (must init now)
syntax to access    *p  or  p->member          r  or  r.member
```

### When to use which

```
need to reassign to different object later   →  pointer
need to represent "nothing" (null)           →  pointer
simple alias, always valid, cleaner syntax   →  reference
function parameter you want to modify        →  reference (coming in ex03)
```

---

## 3. The `&` operator — two meanings

`&` is one of C++'s overloaded symbols. Its meaning depends on context:

### Meaning 1 — address-of operator (right side of `=`)

```cpp
std::string *p = &brain;
//               ↑
//               & here means "give me the address of brain"
//               returns a pointer (std::string*)
```

### Meaning 2 — reference declaration (left side, in type)

```cpp
std::string &ref = brain;
//          ↑
//          & here is part of the TYPE — "reference to std::string"
//          not an operator, just syntax
```

### How to tell them apart

```cpp
std::string &ref = brain;    // & is part of the type declaration
                              // "ref is a reference to std::string"

std::string *p = &brain;     // & is the address-of operator
                              // "take the address of brain"

std::cout << &brain;         // & is the address-of operator
                              // "print the address of brain"
```

Rule of thumb:
```
& attached to a type  (std::string &)   →  reference declaration
& attached to a value (&brain)          →  address-of operator
```

---

## 4. Printing memory addresses

To print a memory address, use `std::cout` with the address-of operator:

```cpp
std::string brain = "HI THIS IS BRAIN";

std::cout << &brain;      // prints the address of brain
```

Output looks like: `0x7ffeeb123abc` — a hexadecimal memory address.

### Printing the address of a pointer

A pointer already IS an address — you print it directly:

```cpp
std::string *stringPTR = &brain;
std::cout << stringPTR;   // prints the address stored in the pointer
                           // same as &brain
```

### Printing the address held by a reference

A reference is an alias — `&ref` gives you the address of the original:

```cpp
std::string &stringREF = brain;
std::cout << &stringREF;  // prints the address of brain
                           // same as &brain
```

### Printing the value

```cpp
std::cout << brain;       // "HI THIS IS BRAIN"
std::cout << *stringPTR;  // dereference pointer  → "HI THIS IS BRAIN"
std::cout << stringREF;   // use reference directly → "HI THIS IS BRAIN"
```

---

## 5. Why all three print the same address

The exercise asks you to print the address of `brain`, `stringPTR`, and `stringREF`. All three will print the same value:

```cpp
std::string  brain     = "HI THIS IS BRAIN";
std::string *stringPTR = &brain;
std::string &stringREF = brain;

std::cout << &brain     << std::endl;  // 0x7fff1000
std::cout << stringPTR  << std::endl;  // 0x7fff1000
std::cout << &stringREF << std::endl;  // 0x7fff1000
```

Why:

```
&brain      →  address of brain                      →  0x7fff1000
stringPTR   →  stores the address of brain           →  0x7fff1000
&stringREF  →  stringREF IS brain, so &stringREF
               is the address of brain               →  0x7fff1000
```

This is the point of the exercise — to show that a reference is not a separate object. It has no address of its own. `&stringREF` gives you the address of whatever the reference refers to — which is `brain`.

A pointer has its own address (it's a variable that holds a value). A reference does not — it's just another name for the same memory location.

```
&stringPTR   →  address OF the pointer variable itself  →  different address
&stringREF   →  address of brain (what ref refers to)   →  same as &brain
```
