# ex00 — BraiiiiiiinnnzzzZ

Concepts: stack vs heap, `new` / `delete`, object lifetime, destructors, multi-file class layout

---

## Where objects live: stack vs heap

Every object you create lives in one of two regions of memory.

```
┌───────────────────────────────────────────────────────────┐
│                     PROCESS MEMORY                        │
│                                                           │
│   ┌────────────────────────────┐                          │
│   │   STACK                    │                          │
│   │                            │                          │
│   │   local variables          │                          │
│   │   Zombie z("Foo");         │                          │
│   │                            │                          │
│   │   automatic lifetime       │                          │
│   │   fast, no manual work     │                          │
│   │   limited size (~MB)       │                          │
│   └────────────────────────────┘                          │
│                                                           │
│   ┌────────────────────────────┐                          │
│   │   HEAP                     │                          │
│   │                            │                          │
│   │   `new` allocates here     │                          │
│   │   Zombie* z = new Zombie.. │                          │
│   │                            │                          │
│   │   manual lifetime          │                          │
│   │   you `delete` or leak     │                          │
│   │   large (~GB)              │                          │
│   └────────────────────────────┘                          │
└───────────────────────────────────────────────────────────┘
```

The two regions are independent. A stack object can hold a pointer to heap data, and that's extremely common — `std::string s` lives on the stack but its character data lives on the heap. The location of the object is not the location of everything it owns.

### Stack — automatic lifetime

```cpp
void scareSomeone() {
    Zombie z("Foo");      // created here
    z.announce();
}                         // destroyed automatically at the closing brace
```

The destructor fires the moment the variable goes out of scope. No `delete`, no leak possible.
The catch: once the function returns, the object is gone. You cannot return it (well, you can, but you'd be copying it out — that's another module).

### Heap — manual lifetime

```cpp
Zombie* z = new Zombie("Foo");   // created on the heap
z->announce();
delete z;                         // YOU decide when it dies
```

The object survives across scopes. It exists until you explicitly `delete` it.
Forget that `delete` and the memory leaks: still allocated, no longer reachable.

### When to use which

```
Need the object only inside this function?        →  STACK
Size known at compile time, small object?         →  STACK
Need it to outlive the function that creates it?  →  HEAP
Size unknown, or very large?                      →  HEAP
```

This exercise gives you both situations side by side:

- `randomChump(name)` — creates a zombie, uses it, throws it away. --> **Stack**
- `newZombie(name)` — creates a zombie and returns it to the caller. The zombie must outlive the function. --> **Heap**

> If `newZombie` allocated on the stack and returned a pointer to it, the pointer would point to memory that no longer exists the moment the function returns. Undefined behavior. Classic mistake.

---

## new and delete

These are the C++ replacements for `malloc` and `free`. They look similar but do more.

| Operation        | C                              | C++                       |
|------------------|--------------------------------|---------------------------|
| Allocate one     | `malloc(sizeof(T))`            | `new T(...)`              |
| Allocate array   | `malloc(n * sizeof(T))`        | `new T[n]`                |
| Free one         | `free(ptr)`                    | `delete ptr`              |
| Free array       | `free(ptr)`                    | `delete[] ptr`            |

The crucial difference: **`new` calls the constructor, `delete` calls the destructor.** `malloc` and `free` only move bytes around. They have no idea a class exists.

```
malloc(sizeof(Zombie))     →  raw bytes, no constructor, _name is garbage
new Zombie("Foo")          →  bytes allocated + constructor runs + _name set
```

### What `new` actually does

`new T(args)` is **two operations fused into one expression**:

```
new T(args)   ≡   1. allocate sizeof(T) raw bytes on the heap
                  2. run T's constructor on those bytes
                  3. return a typed T* pointer

delete ptr    ≡   1. run T's destructor on the object
                  2. release the bytes back to the heap
```

Step 1 of `new` is essentially what `malloc` does. Step 2 is what `malloc` can't do. That's the whole story — `new` is `malloc` + constructor, `delete` is destructor + `free`.

Visually, after `Zombie* z = new Zombie("Foo");`:

```
STACK frame:              HEAP:
┌──────────────┐          ┌────────────────────────┐
│ z: 0x7f3a... │ ───────► │ _name → "Foo"          │
└──────────────┘          │ (other members...)     │
 just a pointer           └────────────────────────┘
 (8 bytes on 64-bit)       the actual Zombie object
```

The pointer `z` lives on the stack. What it points to lives on the heap. Two separate places in memory.

### The matching rule

```
new T       pairs with   delete T
new T[n]    pairs with   delete[] T
```

**Why two forms?** When you allocate an array, the runtime needs to remember how many elements there are, so `delete[]` knows how many destructors to call. The count is usually stored in a hidden header right before the pointer you got back:

```
HEAP after new Zombie[5]:

  ┌──────┬───────┬───────┬───────┬───────┬───────┐
  │  5   │  z0   │  z1   │  z2   │  z3   │  z4   │
  └──────┴───────┴───────┴───────┴───────┴───────┘
  hidden  ↑
  header  pointer you got back

delete[] p   →  reads "5", calls ~Zombie() 5 times, frees the block
delete   p   →  assumes 1 object, calls ~Zombie() once, frees from
                the wrong address. Undefined behavior.
```

Mismatched forms are UB. Often it crashes. Sometimes it silently leaks the rest of the array. Don't mix them.

### Allocation can fail

In C, `malloc` returns `NULL` on failure. In C++ (by default), `new` **throws** `std::bad_alloc` — you don't check the return value.
For C++98 with the default allocator, you can assume `new` either succeeds or throws. (You'll meet exceptions properly in Module 05.)

---

## Destructors

A destructor is the mirror of the constructor: a special method that runs automatically when an object is destroyed. Its job is to **undo whatever the constructor set up** — that might mean releasing memory, closing a file, releasing a lock, or simply printing a debug message.

```cpp
class Zombie {
private:
    std::string _name;

public:
    Zombie(std::string name);
    ~Zombie();                          // destructor — note the ~
    void announce(void);
};

// constructor
Zombie::Zombie(std::string name) : _name(name) {}

```
Zombie::Zombie(std::string name) : _name(name) {}
  │       │           │              │     │   │
  │       │           │              │     │   └─ empty body, nothing else to do
  │       │           │              │     └─── initialize WITH this value (the parameter)
  │       │           │              └───────── initialize THIS attribute
  │       │           └──────────────────────── the parameter coming in
  │       └──────────────────────────────────── constructor (same name as class)
  └──────────────────────────────────────────── class scope — "this belongs to Zombie"
```



Zombie::~Zombie() {
    std::cout << _name << " destroyed" << std::endl;
}
```

Rules of the destructor:

- Same name as the class, prefixed with `~`
- **No return type, no parameters**
- Exactly one per class
- Runs automatically, you never call it directly

### The destructor always fires — for stack *and* heap objects

A common misconception: that destructors are "for heap cleanup". They're not — they run for every object, no matter where it lives. The only difference is **who triggers the call**:

```
┌─────────────────────────────────────────────────────────┐
│  STACK object                                           │
│  ─────────────                                          │
│  Zombie z("Foo");                                       │
│                                                         │
│  destructor fires AUTOMATICALLY when the scope ends     │
│  the compiler inserts the call for you                  │
│  you cannot forget, you cannot skip it                  │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│  HEAP object                                            │
│  ────────────                                           │
│  Zombie* z = new Zombie("Foo");                         │
│  delete z;                                              │
│                                                         │
│  destructor fires when YOU write `delete`               │
│  forget `delete` → destructor never runs → leak         │
└─────────────────────────────────────────────────────────┘
```

A small experiment that makes it concrete:

```cpp
{
    Zombie  stackZombie("Foo");
    Zombie* heapZombie = new Zombie("Bar");
    delete heapZombie;
}
```

Output:

```
Bar destroyed     ← heap zombie, destructor fired by `delete`
Foo destroyed     ← stack zombie, destructor fired by closing `}`
```

Both destructors ran. Neither location is privileged.

### Do you always need to write one?

No. The compiler generates a default destructor for you if you don't write one. It calls the destructor of every member, in reverse order of declaration. For `Zombie`, that means `_name.~string()` — and `std::string` cleans up its own heap data correctly.

So strictly speaking, the default destructor would already work for this exercise. You write one for two reasons:

1. **Debug visibility** — the subject asks you to print a message so you can *see* when zombies die. That's a teaching device: making the invisible visible.
2. **Practicing the syntax** — before you can write a destructor that releases a raw pointer (which is coming soon), you need to know how to write one at all.

The rule for the future: **write a destructor when your class owns a raw resource the default doesn't know how to release** — a `new`-allocated pointer, a file handle, a socket. For classes that only hold well-behaved members (like `std::string`), the default is fine. Module 02 turns this into the strict "Orthodox Canonical Form".

---

## Pointers and the arrow operator

When you have a pointer to an object, you can't use `.` directly — you'd be calling a method on the pointer itself, not the object it points to. Two equivalent syntaxes:

```cpp
Zombie* z = new Zombie("Foo");

(*z).announce();    // dereference, then call    — works but ugly
z->announce();      // arrow operator             — same thing, idiomatic
```

```
z          →  [ address ]
*z         →  the Zombie object at that address
z->member  ≡  (*z).member
```

Stack objects use `.`:

```cpp
Zombie z("Foo");
z.announce();
```

---

## Multi-file class layout

This is the first exercise where the file structure starts to matter. The convention:

```
Zombie.hpp        ← class DECLARATION (the blueprint)
Zombie.cpp        ← class DEFINITION  (the method bodies)
newZombie.cpp     ← free function (not a member of Zombie)
randomChump.cpp   ← free function
main.cpp          ← your tests
```

### The header

```cpp
// Zombie.hpp
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
private:
    std::string _name;

public:
    Zombie(std::string name);
    ~Zombie();
    void announce(void);
};

#endif
```

### Free functions vs member functions

`newZombie` and `randomChump` are **not** part of the `Zombie` class — they're free functions that happen to work with zombies. No `Zombie::` prefix in their definition:

```cpp
// newZombie.cpp
#include "Zombie.hpp"

Zombie* newZombie(std::string name) {
    return new Zombie(name);
}
```

```cpp
// randomChump.cpp
#include "Zombie.hpp"

void randomChump(std::string name) {
    Zombie z(name);     // stack — dies at end of function
    z.announce();
}
```

---

## Putting it together

The exercise is essentially asking you to demonstrate, in code, that you understand the trade-off:

```
randomChump("Bob")
─────────────────────────────────────────────
   Zombie z("Bob")        ← constructor on stack
   z.announce()           ← "Bob: BraiiiiiiinnnzzzZ..."
   (function returns)     ← destructor automatic
                              "Bob destroyed"

newZombie("Alice")
─────────────────────────────────────────────
   return new Zombie("Alice")   ← constructor on heap
                                  pointer returned to caller
   (caller's responsibility now)
   ...later...
   delete alice                 ← destructor
                                  "Alice destroyed"
```

If your destructor doesn't print for every zombie you created, you have a leak.

---

## Checking for leaks

The subject mentions checking for leaks. Two tools you'll meet repeatedly:

- **valgrind** (Linux): `valgrind ./a.out` — reports any block allocated and not freed.
- **leaks** (macOS): `leaks --atExit -- ./a.out`.

A clean run with `valgrind` ends with `All heap blocks were freed -- no leaks are possible`. Anything else means a `new` somewhere has no matching `delete`.

Counting destructor prints against constructor calls is a quick sanity check on the stdout — if you created 5 zombies and only see 4 "destroyed" lines, one leaked.

---

## Edge cases & traps

- **Double delete.** Calling `delete` twice on the same pointer is undefined behavior. After `delete z`, the pointer still holds the old address but the memory is gone. Setting `z = NULL` after deleting is a defensive habit (deleting `NULL` is a no-op and safe).
- **Returning a pointer to a stack object.** Compiles, runs, sometimes even appears to work — but it's UB. The object died when the function returned.
- **`delete` vs `delete[]`.** Don't mix them. `new[]` always pairs with `delete[]`. Coming up in ex01.
- **Mixing `malloc`/`new` with `free`/`delete`.** Never `free` something allocated with `new`, never `delete` something allocated with `malloc`. They may use different allocators, and you'd skip the constructor/destructor calls — corrupting the object's invariants.
- **Forgetting `delete` entirely.** The OS reclaims memory when the process exits, so a small leaky program may seem fine. In a long-running program (a server, a game loop), leaks accumulate until the process is killed by the OS.
