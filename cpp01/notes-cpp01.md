# cpp01 — ex00 — BraiiiiiiinnnzzzZ

---

## Index

1. [Memory: stack vs heap](#1-memory-stack-vs-heap)
2. [new and delete](#2-new-and-delete)
3. [Constructors and initialization lists](#3-constructors-and-initialization-lists)
4. [Destructors](#4-destructors)
5. [Pointers and the arrow operator](#5-pointers-and-the-arrow-operator)
6. [Multi-file class layout](#6-multi-file-class-layout)
7. [Traps and edge cases](#7-traps-and-edge-cases)

---

## 1. Memory: stack vs heap

When a program runs, the OS gives it a block of memory. 
That memory is divided into regions: The stack and the heap.

```
┌──────────────────────────────────────────────────────┐
│                   PROCESS MEMORY                     │
│                                                      │
│  ┌──────────────────────────────────────────────┐    │
│  │  STACK                                       │    │
│  │                                              │    │
│  │  - local variables                           │    │
│  │  - function call frames                      │    │
│  │  - fixed size at compile time (~MB)          │    │
│  │  - lifetime = scope                          │    │
│  │  - managed by the compiler                   │    │
│  └──────────────────────────────────────────────┘    │
│                                                      │
│  ┌──────────────────────────────────────────────┐    │
│  │  HEAP                                        │    │
│  │                                              │    │
│  │  - dynamic allocations (`new`)               │    │
│  │  - large (~GB, limited by RAM)               │    │
│  │  - lifetime = until you `delete`             │    │
│  │  - managed by YOU                            │    │
│  └──────────────────────────────────────────────┘    │
│                                                      │
│  (+ code segment, data segment — not relevant here)  │
└──────────────────────────────────────────────────────┘
```

### Stack — automatic lifetime

Every time a function is called, the CPU pushes a **stack frame** onto the stack: space for all the local variables of that function. 
When the function returns, the frame is popped, all local variables are destroyed automatically.

```cpp
void scareSomeone() {
    Zombie z("Foo");      // z lives inside this frame
    z.announce();
}                         // frame popped → z destroyed automatically
```

The compiler knows the exact size of every local variable at compile time. 
It reserves the space before the function even runs. No runtime allocation cost — just a pointer bump. This is why stack allocation is fast.


```cpp
Zombie *dangling() {
    Zombie z("Foo");
    return &z;           // ← NEVER do this
}                        // z dies here — caller gets a pointer to dead memory
```

### Heap — manual lifetime

The heap is a large pool of memory managed at runtime. 
You request a block with `new`, use it as long as you need, and release it with `delete`. 
The object survives across any number of function calls and scopes.

```cpp
Zombie *z = new Zombie("Foo");   // allocated on the heap
z->announce();                    // still alive
someOtherFunction(z);             // still alive
delete z;                         // YOU decide when it dies
```

### The key decision

```
Object needed only inside this function?               →  STACK
Object must survive past the function that made it?    →  HEAP
```

In this exercise:
- `randomChump` — creates a zombie, uses it, done. → Stack.
- `newZombie`   — creates a zombie and *returns it to the caller*. The caller needs it after `newZombie` has returned. → Heap.

### Stack objects can own heap data

The location of an object and the location of its *contents* are independent. A `std::string` on the stack allocates its character data on the heap:

```
std::string str("hello");

STACK:              HEAP:
┌──────────────┐    ┌───────────────────┐
│ str          │    │'h','e','l','l','o'│
│  size: 5     │    └───────────────────┘
│  data: ──────────►
└──────────────┘
```

`str` lives on the stack. Its text lives on the heap. When `str` goes out of scope, its destructor frees the heap data automatically. This is the correct model — a stack object *owning* heap resources and cleaning them up through its **destructor**.

---

## 2. new and delete

In C, you manage heap memory with `malloc` and `free`.
In C++, you use `new` and `delete`. 
They look similar but do fundamentally more: **`new` calls the constructor, `delete` calls the destructor**. `malloc` and `free` are ignorant of classes, they only move raw bytes.

```
malloc(sizeof(Zombie))   →  raw uninitialized bytes. _name is garbage.
new Zombie("Foo")        →  bytes allocated + constructor runs + _name = "Foo"
```

### What happens under the hood

`new T(args)` is two operations fused into one:

```
new T(args)
  step 1: call operator new(sizeof(T))
          → asks the heap allocator for sizeof(T) raw bytes
          → returns a void* to that memory
  step 2: call T's constructor on those bytes
          → this pointer inside the constructor = address from step 1
          → constructor sets up the object's state
  step 3: return a typed T* to the caller

delete ptr
  step 1: call T's destructor on the object at ptr
          → cleanup runs (free owned resources, print debug messages, etc.)
  step 2: call operator delete(ptr)
          → bytes returned to the heap allocator
```

Visually, after `Zombie *z = new Zombie("Foo")`:

```
STACK frame:              HEAP:
┌──────────────┐          ┌──────────────────────┐
│ z: 0x7f3a... │ ───────► │ _name → "Foo"        │
└──────────────┘          └──────────────────────┘
 8-byte pointer            the actual Zombie object
 (lives here)              (lives here)
```

The pointer `z` is on the stack. What it *points to* is on the heap. Two separate regions.

### The matching rule

```
new T        pairs with    delete T
new T[n]     pairs with    delete[] T
```

**Never mix these.** `new T[n]` stores a hidden element count just before the pointer it returns:

```
HEAP after new Zombie[5]:

  ┌──────┬─────────┬─────────┬─────────┬─────────┬─────────┐
  │  5   │Zombie[0]│Zombie[1]│Zombie[2]│Zombie[3]│Zombie[4]│
  └──────┴─────────┴─────────┴─────────┴─────────┴─────────┘
  hidden   ↑
  count    pointer you received

delete[] p   →  reads "5", calls ~Zombie() × 5, frees the whole block
delete   p   →  calls ~Zombie() × 1, tries to free from the wrong address
                → heap corruption, undefined behavior
```

### C vs C++ comparison

| Operation      | C                       | C++                  |
|----------------|-------------------------|----------------------|
| Allocate one   | `malloc(sizeof(T))`     | `new T(...)`         |
| Allocate array | `malloc(n * sizeof(T))` | `new T[n]`           |
| Free one       | `free(ptr)`             | `delete ptr`         |
| Free array     | `free(ptr)`             | `delete[] ptr`       |
| On failure     | returns `NULL`          | throws `std::bad_alloc` |
| Calls ctor/dtor| no                      | yes                  |

> Never mix allocators: `free` something allocated with `new` → undefined behavior. `delete` something from `malloc` → undefined behavior. They may use different underlying allocators, and you'd skip constructor/destructor calls either way.

---
 
## 3. Constructors and initialization lists
 
A constructor runs automatically when an object is created. Its job: **put the object into a valid state before anything outside the class can touch it**. Without it, the object's memory starts as garbage.
 
```cpp
Zombie::Zombie(std::string name) : _name(name) {}
//                                 ──────────────
//                                 initialization list — sets _name DURING construction
//                                 body runs after — empty here, nothing else to do
```
 
### What "creating an object" means in memory
 
```
Zombie z("Foo");                   // stack
  1. compiler reserves sizeof(Zombie) bytes on the stack  →  raw garbage bytes
  2. constructor runs on those bytes                      →  _name = "Foo"
  3. z is a valid Zombie
 
Zombie *z = new Zombie("Foo");     // heap
  1. operator new reserves sizeof(Zombie) bytes on the heap  →  raw garbage bytes
  2. constructor runs on those bytes                         →  _name = "Foo"
  3. returns pointer to a valid Zombie
```
 
Same constructor, both cases. The only difference is who reserved the memory.
 
### Initialization list vs body assignment
 
```cpp
// WITH init list — one operation
Zombie::Zombie(std::string name) : _name(name) {}
// _name is constructed directly with "Foo"
 
// WITHOUT init list — two operations
Zombie::Zombie(std::string name) {
    _name = name;   // _name was first default-constructed to ""
}                   // then overwritten — wasteful
```
 
For `std::string` the cost difference is small. The rule matters more for `const` and reference members, which **can only be set in the initialization list** — they cannot be assigned in the body:
 
```cpp
class Foo {
    const int _id;   // const — set once, never changed
public:
    Foo(int id) : _id(id) {}   // ✓ only option
};
```

### Multiple constructors

A class can have more than one constructor — each with a different parameter list. The compiler picks the right one based on what you pass:

```cpp
Zombie();                      // default constructor — no arguments
Zombie(std::string name);      // parameterized constructor

Zombie a;                      // → default constructor
Zombie b("Foo");               // → parameterized constructor
Zombie *c = new Zombie("Bar"); // → parameterized constructor
Zombie *horde = new Zombie[5]; // → default constructor × 5 (arrays need this)
```

> Once you write *any* constructor, the compiler stops generating the default one for you. If you want both, write both.

---

## 4. Destructors

A destructor is the mirror of the constructor: a method that runs automatically when an object is destroyed. Its job: **undo whatever the constructor set up**.

```cpp
Zombie::~Zombie() {
    std::cout << _name << " destroyed" << std::endl;
}
```

Rules:
- Same name as the class, prefixed with `~`
- No return type, no parameters
- Exactly one per class
- You never call it directly — the compiler inserts the call

### When does it fire?

```
┌─────────────────────────────────────────────────────────────┐
│  STACK object                                               │
│                                                             │
│  {                                                          │
│      Zombie z("Foo");   ← constructor                       │
│      z.announce();                                          │
│  }                      ← destructor — compiler inserts it  │
│                           automatically at the closing }    │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────┐
│  HEAP object                                                │
│                                                             │
│  Zombie *z = new Zombie("Foo");   ← constructor             │
│  z->announce();                                             │
│  delete z;                        ← destructor — fires here │
│                                     ONLY because you wrote  │
│                                     delete                  │
│                                                             │
│  if you forget delete:                                      │
│      destructor NEVER runs                                  │
│      memory leaks for the life of the process               │
└─────────────────────────────────────────────────────────────┘
```

**The destructor runs for both stack and heap objects.** The difference is not whether it runs, it's who triggers it:

```
stack  →  compiler triggers it automatically at scope end
heap   →  you trigger it by calling delete
```

Concrete proof — run this and read the output order:

```cpp
{
    Zombie  stackZ("Foo");
    Zombie *heapZ = new Zombie("Bar");
    delete heapZ;
}
// output:
// Bar destroyed   ← heap: fired by delete, inside the block
// Foo destroyed   ← stack: fired by }, also inside the block
```

### Do you always need to write one?

No. If you don't write a destructor, the compiler generates a default one that calls the destructor of every member in reverse order of declaration. For `Zombie` with just `std::string _name`, the default destructor calls `_name.~string()` and `std::string` correctly frees its own heap data.

**Write a destructor when your class directly owns a raw resource** that the default won't know how to release:

```
owns a raw pointer from new       →  destructor must delete it
opens a file                      →  destructor must close it
acquires a lock                   →  destructor must release it
only holds std::string, int, etc. →  default destructor is fine
```

In this exercise, the destructor exists for **debug visibility** — you write it so you can see when zombies die. Module 02 will formalize the rules (Orthodox Canonical Form).

---

## 5. Pointers and the arrow operator

When you have a pointer to an object, you need a different syntax to call its methods.

```cpp
Zombie  z("Foo");    // z IS the object
Zombie *p = &z;      // p POINTS TO the object

z.announce();        // dot   — z is the object directly
p->announce();       // arrow — p is a pointer to the object
(*p).announce();     // same as arrow — ugly, avoid
```

```
z          →  the Zombie object itself
p          →  an address (where z lives)
*p         →  the Zombie at that address (same as z)
p->member  ≡  (*p).member
```

Arrow is just syntactic sugar for "dereference, then access member". Use `->` always — it's idiomatic C++.

### With heap allocation

```cpp
Zombie *z = new Zombie("Foo");

z->announce();      // ✓ correct — z is a pointer
(*z).announce();    // ✓ same thing
z.announce();       // ✗ compiler error — z is not an object
```

The type tells you which to use:
```
Zombie  z  →  dot operator  →  z.announce()
Zombie *z  →  arrow operator → z->announce()
```

---

## 6. Multi-file class layout

C++ class code is split across two files. This is not optional — it is the standard convention, and 42 enforces it strictly.

```
ClassName.hpp    DECLARATION — what the class looks like
                 (the blueprint: attributes, method signatures)

ClassName.cpp    DEFINITION  — how the methods actually work
                 (the bodies)
```

Any extra free functions related to the class get their own `.cpp` files.

### The header — declarations only

```cpp
// Zombie.hpp
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie(std::string name);
    ~Zombie();
    void announce(void);
};

// free functions related to Zombie
Zombie *newZombie(std::string name);
void    randomChump(std::string name);

#endif
```



### The .cpp — definitions

Every method defined in `.cpp` needs the `ClassName::` prefix. Without it, you're defining a free function, not a class member:

```cpp
// Zombie.cpp
#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name) {}   // constructor
Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }
void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
```

```cpp
// newZombie.cpp
#include "Zombie.hpp"

Zombie *newZombie(std::string name) {   // free function — NO Zombie:: prefix
    return new Zombie(name);
}
```

```cpp
// randomChump.cpp
#include "Zombie.hpp"

void randomChump(std::string name) {    // free function — NO Zombie:: prefix
    Zombie z(name);
    z.announce();
}
```

### Member function vs free function

```
Member function                    Free function
─────────────────────────────      ─────────────────────────────
declared inside the class {}       declared outside the class
defined with ClassName:: prefix    defined without any prefix
has access to private members      no access to private members
called on an object: z.announce()  called standalone: newZombie("Foo")
```

`newZombie` and `randomChump` work *with* zombies but are not *part of* the Zombie class. They're free functions. The subject puts them in separate files to make this explicit.

---

## 7. Traps and edge cases

**Double delete — undefined behavior**
```cpp
delete z;
delete z;   // ← UB — memory already freed, pointer is dangling
```
After deleting, set the pointer to `NULL`. Deleting `NULL` is a safe no-op.

**Returning a pointer to a stack object — undefined behavior**
```cpp
Zombie *f() {
    Zombie z("Foo");
    return &z;       // z dies when f() returns
}                    // caller holds a pointer to dead memory
```
Compiles. Sometimes appears to work. Always wrong.

**Mixing allocators — undefined behavior**
```cpp
Zombie *z = (Zombie *)malloc(sizeof(Zombie));
delete z;    // ✗ — constructor never ran, delete calls destructor on garbage
```
`malloc`/`free` pair together. `new`/`delete` pair together. Never cross them.

**Forgetting delete**
```cpp
Zombie *z = new Zombie("Foo");
// ... forgot delete z
```
The OS reclaims everything when the process exits, so small programs appear fine. In a server or game loop running for hours, forgotten `delete` calls accumulate until the process is killed. Always verify with `valgrind`.

**Leak check**
```bash
valgrind ./zombie
# clean output ends with:
# All heap blocks were freed -- no leaks are possible
# ERROR SUMMARY: 0 errors from 0 contexts
```
