# The `virtual` keyword

## The core idea

Every function call needs to answer one question: **which actual block of code do I jump to?**

- **Without `virtual`** → the compiler answers it once, while compiling your code, based on the **declared type**
- **With `virtual`** → the answer is postponed until the program is actually running, and it's based on the **real type** of the object.

## A concrete example

```cpp
class Animal {
public:
    virtual void makeSound() const { std::cout << "..." << std::endl; }
};

class Dog : public Animal {
public:
    void makeSound() const { std::cout << "au au auu" << std::endl; }
};
```

```cpp
Animal *a = new Dog();
a->makeSound();
```

***`a` is *declared* as `Animal*`. But it *really* points to a `Dog`.***

- If `makeSound()` is **not** virtual → `Animal::makeSound()`.
- If `makeSound()` **is** virtual `"au au auu"` correct.

## Why this matters — the whole point of polymorphism

Without `virtual`, you could never write one function or one loop that correctly handles many different derived types through a single base pointer — you'd have to know the real type in advance every time, which defeats the purpose of inheritance.

```cpp
Animal *animals[3] = { new Animal(), new Dog(), new Cat() };
for (int i = 0; i < 3; i++)
    animals[i]->makeSound(); // each one correctly plays its own sound
```

This loop only works correctly because `makeSound()` is virtual. That's the entire mechanism polymorphism is built on.

## How it actually works, under the hood

Any class with at least one virtual function gets a hidden extra member inserted by the compiler: the **vptr** (virtual table pointer). 

- Every class that has virtual functions gets its own **vtable** -> a small table of real function addresses, one copy shared by every instance of that class.
- The object's `vptr` points at its own class's vtable.
- A virtual call means: **read the object's vptr → follow it to the vtable → read the correct slot → call whatever address is sitting there.**
- A non-virtual call skips all of that: the target address is written directly into the instruction at compile time, no lookup at all.

This is genuinely measurable — a virtual call compiles to about twice as many instructions as a non-virtual one, because of those two extra memory reads (object → vptr, vptr → real address).

## Virtual on a destructor — the one that actually prevents bugs

```cpp
class Animal {
public:
    virtual ~Animal() { std::cout << "Animal destructor" << std::endl; }
};
class Dog : public Animal {
public:
    ~Dog() { std::cout << "Dog destructor" << std::endl; }
};
```

```cpp
Animal *a = new Dog();
delete a;
```

- If `~Animal()` is **not** virtual → `delete a` only calls `~Animal()`. `~Dog()` never runs. If `Dog` owns any heap-allocated resource (like a `Brain*`), that resource is never freed — a real, guaranteed memory leak, every time.
- If `~Animal()` **is** virtual → `delete a` correctly chains through `~Dog()` first, then `~Animal()` — the full destructor sequence runs, resources get freed properly.

**Rule of thumb:** if a class is ever going to be inherited from and might be deleted through a base pointer, its destructor should be virtual. This is true even if the base class itself doesn't manage any resources — the danger is entirely about what *derived* classes might own.

## Pure virtual — `virtual ... = 0;`

```cpp
virtual void makeSound() const = 0;
```

This is `virtual`'s strictest form. It means: *this class provides no implementation at all for this function, and any class that doesn't override it also can't be instantiated.*

A class with at least one pure virtual function is called **abstract**. The compiler will refuse to compile `AAnimal a;` or `new AAnimal()` — not a warning, a hard error, naming the exact function that's still unimplemented.

This is deliberate design enforcement, not just style: it forces every derived class to actually decide what its own version does, checked by the compiler, not left as a convention someone could forget.

---

# Checking it live with gdb

Everything above, confirmed against a real compiled binary rather than taken on faith.

## Step 1 — compile with debug symbols

Normal `-Wall -Wextra -Werror` builds strip out the information gdb needs to map instructions back to source lines. Add `-g`:

```bash
c++ -g -Wall -Wextra -Werror -std=c++98 Animal.cpp Cat.cpp Dog.cpp WrongAnimal.cpp WrongCat.cpp main.cpp -o animal_dbg
```

## Step 2 — start gdb, set the syntax flavor, break, run

```
$ gdb ./animal_dbg
(gdb) set disassembly-flavor intel
(gdb) break main
(gdb) run
```

**Why set the flavor at all?** gdb's *default* output is **AT&T syntax**, which writes operands as `src, dst` and prefixes registers with `%` (e.g. `mov %rax,%rdx`). **Intel syntax** writes `dst, src` with no `%` prefix (e.g. `mov rdx, rax`) which is closer to how most textbooks

## Step 3 — `disassemble /s`: source and assembly together

```
(gdb) disassemble /s
```

`disassemble /r` is a different modifier, it adds the *raw opcode bytes* (the literal hex machine code) next to each instruction
`disassemble /s` (source-interleaved) comparing C++ lines to their assembly

---

A **register** is a tiny storage slot inside the CPU. 
On this architecture (x86-64), every register is exactly **8 bytes (64 bits)** —> big enough to hold one address.
 
| Register | Holds |
|---|---|
| `rax` | a temporary value or address |
| `rdi` | the object (`this`) |
| `rdx` | the function's address, right before it's called |
 
`QWORD PTR` 
x86 has fixed size names left over from when a "word" meant 2 bytes: `BYTE` = 1,
`WORD` = 2,
`DWORD` = 4
`QWORD` = 8.
`QWORD PTR [rax]` means "go to the address in `rax`, read exactly 8 bytes from there." 
--> Every address on x86-64 is 8 bytes



**Non-virtual** — `i->makeSound();` — 2 instructions
 
```
mov    rdi,rax              // copy value from rax into rdi
call   0x555...<name>       // call the function
```
 
1. copy the object into `rdi` —> this is `this`
2. call the function — its address was already known
**Virtual** — `i->makeSound();` — 3 instructions
 
```
mov    rax,QWORD PTR [rax]  // follow rax -> get the object's function table
mov    rdx,QWORD PTR [rax]  // follow that table -> get the real function
call   rdx
```
 
1. `rax` holds the object's address. 
Follow it and what's stored there is the object's function table. 
Now `rax` holds the table's address instead.
2. Follow the table — what's stored there is the real function to call. Store it in `rdx`
3. call whatever address is in `rdx`
 
 
---

# vptr and vtable — how a virtual call finds the real function

`i` is declared as `Animal*`, but it really points to a `Dog`. 
A virtual call follows two hidden pointers to find `Dog`'s real `makeSound()` before it can
call it.

```
                 i (pointer)
                      |
                      v
   +------------------------------------+
   |             Dog object              |
   |  +------------+   +---------------+ |
   |  |    vptr    |   |     _type     | |
   |  |  (hidden)  |   |     "Dog"     | |
   |  +-----+------+   +---------------+ |
   +--------|-----------------------------+
            |  follow the vptr
            v
   +------------------------------------+
   |            Dog's vtable             |
   |  +------------+   +---------------+ |
   |  | ~Dog() slot|   |  makeSound    | |
   |  | -> ~Dog()  |   |  -> real code | |
   |  +------------+   +------+--------+ |
   +--------------------------|-----------+
                              |  follow the slot
                              v
                     +-----------------------+
                     |       call rdx        |
                     |  lands on Dog::make-  |
                     |  Sound's real code    |
                     +-----------------------+
```

## What each arrow means

1. `i` holds the object's address — an ordinary pointer, nothing hidden yet.
2. Follow it into the object. Alongside its real data (`_type`) sits a
   hidden field the compiler added: the **vptr**.
3. Follow the vptr. It points at `Dog`'s **vtable** — one shared table of
   function addresses, the same for every `Dog` that exists.
4. Follow the `makeSound` slot in that table. It holds the real address of
   `Dog::makeSound`.
5. `call` that address. This is why it's `call rdx` instead of a fixed name
   — the address wasn't known until this exact moment, at runtime.

A non-virtual call skips all of this — no vptr, no vtable, no following.
The function's address is written directly into the instruction back when
the program was compiled.
