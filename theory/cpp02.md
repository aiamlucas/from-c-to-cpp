# The Orthodox Canonical Form — a complete introduction

*A guide for someone who has never heard this term before, and wants to come out the other end able to write it themselves.*

---

## 1. What it is

> **Orthodox Canonical Form means: every class explicitly writes four specific member functions**
> - default constructor
> - copy constructor
> - copy assignment operator
> - destructor
>
> **instead of silently relying on the versions C++ writes for you automatically.**

That's the whole idea. Everything below unpacks *how* to write each of these, and then *why* it actually matters — which turns out to be the more interesting half.

---

## 2. How it's made — a first example

Here's a small class with all four written out, as plainly as possible:

```cpp
class Counter {
private:
    int _value;

public:
    Counter();                                  // default constructor
    Counter(const Counter &other);               // copy constructor
    Counter &operator=(const Counter &rhs);       // copy assignment operator
    ~Counter();                                  // destructor
};
```

```cpp
Counter::Counter() : _value(0) {}

Counter::Counter(const Counter &other) : _value(other._value) {}

Counter &Counter::operator=(const Counter &rhs) {
    _value = rhs._value;
    return *this;
}

Counter::~Counter() {}
```

Each one answers a different question:

```
┌───────────────────────────┬─────────────────────────┬───────────────────────────┐
│ Function                    │ Question it answers      │ Fires on...                │
├───────────────────────────┼─────────────────────────┼───────────────────────────┤
│ Default constructor         │ "What's a blank one       │ Counter a;                  │
│                              │  supposed to look like?"  │                             │
│ Copy constructor             │ "How do I build a NEW     │ Counter b( a );             │
│                              │  one from an existing one?"│                             │
│ Copy assignment operator     │ "How do I make an EXISTING│ b = a;                      │
│                              │  one match another?"      │                             │
│ Destructor                   │ "What happens when it     │ } // scope ends             │
│                              │  dies?"                   │                             │
└───────────────────────────┴─────────────────────────┴───────────────────────────┘
```

For `Counter`, every one of these is almost too simple to be interesting — copying one `int` around has exactly one sensible meaning, and it's obvious what it is. Keep that feeling in mind, because the next section is going to break it.

---

## 3. Why this actually matters: shallow copy vs. deep copy

This is the concept that makes the whole topic click. Once you understand this, every rule about the canonical form stops being an arbitrary requirement and starts being an obvious necessity.

### The setup: a class that owns something on the heap

```cpp
class Name {
private:
    char *_data;

public:
    Name(const char *str) {
        _data = new char[std::strlen(str) + 1];
        std::strcpy(_data, str);
    }
    ~Name() {
        delete[] _data;
    }
    // no copy constructor, no copy assignment operator written
};
```

This class allocates a buffer on the heap in its constructor, and frees it in its destructor. Looks fine so far. But this class was never given a copy constructor or copy assignment operator — so C++ silently generated its own, automatic versions, same as always.

### What the automatic version actually does: a shallow copy

The compiler's automatic copying does exactly one thing, always: **copy each member's value, byte for byte.** `_data` is a `char*` — an address. So the automatic copy copies *the address itself*, not the data sitting at that address.

```
Name a("Alexander");
Name b( a );          // uses the COMPILER'S automatic copy constructor

BEFORE THE COPY                        AFTER THE COPY

  a                                      a                     b
  ┌─────────────┐                        ┌─────────────┐       ┌─────────────┐
  │ _data ──────┼──┐                     │ _data ──────┼──┐    │ _data ──────┼──┐
  └─────────────┘  │                     └─────────────┘  │    └─────────────┘  │
                    ▼                                      ▼                     ▼
              "Alexander"                             a AND b now BOTH point
              (one heap buffer)                        at the exact same buffer
```

This is called a **shallow copy** — the pointer got copied, but not what it points to. Two objects now believe they each own that memory. Nothing warns you. The program will very likely run fine, right up until:

```cpp
// a and b both go out of scope here
```

`a`'s destructor runs `delete[] _data;` and frees the buffer. Then `b`'s destructor runs, and tries to `delete[]` **the exact same memory a second time** — a double-free. This is undefined behavior: sometimes a crash, sometimes silent corruption, sometimes nothing visible at all until much later.

### The fix: a deep copy

A **deep copy** means: don't just copy the address — allocate *new*, independent memory, and copy the actual *contents* into it.

```cpp
Name::Name(const Name &other) {
    _data = new char[std::strlen(other._data) + 1];   // NEW buffer
    std::strcpy(_data, other._data);                    // copy the CONTENTS into it
}
```

```
Name a("Alexander");
Name b( a );           // now uses OUR hand-written, deep copy constructor

  a                                      b
  ┌─────────────┐                        ┌─────────────┐
  │ _data ──────┼──┐                     │ _data ──────┼──┐
  └─────────────┘  │                     └─────────────┘  │
                    ▼                                      ▼
              "Alexander"                             "Alexander"
              (a's OWN buffer)                        (b's OWN, separate buffer)
```

Now `a` and `b` are genuinely independent. Each one's destructor only ever frees memory it alone owns. No double-free, no shared state, no surprise.

### So — why write a copy constructor at all?

Now the earlier fact makes sense: **a copy constructor only ever runs once per object, at the exact moment it's built.** That single moment is your *only* chance to decide how the new object's data comes into existence. If you don't write your own, C++ makes that decision for you — and its decision is always "shallow copy," regardless of whether that's safe for your class.

For `Counter`, shallow copying an `int` is completely fine — there's nothing to go wrong. For `Name`, shallow copying a `char*` is a ticking bug. **The compiler cannot tell the difference between these two cases.** It applies the same naive rule either way. Writing your own copy constructor is the only way to tell C++ "for this specific class, copying needs to mean something more careful than that."

---

## 4. The four members, now that you know why

### 4.1 — Default constructor

Unaffected by all of the above — there's no "other object" involved, so there's no shallow/deep question here. Its only job is choosing a sensible starting state.

```cpp
Counter::Counter() : _value(0) {}
```

### 4.2 — Copy constructor

```cpp
ClassName(const ClassName &other);
```

Now you know exactly why this exists: **it's your one opportunity, at the moment a new object is born from an existing one, to choose deep copying over the compiler's automatic shallow copying** — whenever your class owns something a shallow copy would put at risk.

```cpp
Name::Name(const Name &other) {
    _data = new char[std::strlen(other._data) + 1];
    std::strcpy(_data, other._data);
}
```

For a class with no pointers to manage (like `Counter`), the "deep" and "shallow" versions look identical — you write it anyway, so the habit is already there the day it stops being identical.

### 4.3 — Copy assignment operator

```cpp
ClassName &operator=(const ClassName &rhs);
```

This solves the *same* shallow-vs-deep problem, but for a trickier situation: the destination object **already exists**, and might already own its own resource that needs to be dealt with *before* taking on a copy of someone else's.

```cpp
Name &Name::operator=(const Name &rhs) {
    if (this == &rhs)          // guard: assigning an object to itself
        return *this;

    delete[] _data;             // free what THIS object already owned
    _data = new char[std::strlen(rhs._data) + 1];   // allocate fresh memory
    std::strcpy(_data, rhs._data);                    // deep copy the new content
    return *this;
}
```

Here's exactly why the self-assignment guard (`if (this == &rhs)`) is not just a stylistic habit: without it, `n = n;` would `delete[]` `_data`, and then immediately try to read from that same, now-freed `_data` on the next line — reading memory that was just deallocated. The guard exists to protect against a case that's easy to trigger by accident (e.g. `a = getSomeReference();` where the reference happens to alias `a` itself).

For `Counter`, there's no old resource to free, so the assignment operator stays simple — but the shape (guard, then copy) is the same shape you'll need the day a class does own something.

### 4.4 — Destructor

```cpp
~ClassName();
```

Releases whatever the object was responsible for. For `Counter`, nothing — an empty body is the fully correct answer. For `Name`, `delete[] _data;` — the destructor is what makes the deep-copy discipline from the constructor and assignment operator actually pay off: each object safely cleans up only the memory it alone owns.

---

## 5. The confusing part: constructor vs. assignment, precisely

Both the copy constructor and copy assignment operator "copy data." The one question that tells them apart, every time:

> **Did the object on the left already exist, the instant before this line ran?**

```
Counter a;         ← a doesn't exist yet → DEFAULT constructor
Counter b( a );    ← b doesn't exist yet → COPY constructor (built from a)
Counter c = a;     ← c doesn't exist yet → COPY constructor too! (the = is misleading here)
Counter d;         ← d doesn't exist yet → DEFAULT constructor
d = a;             ← d ALREADY exists    → COPY ASSIGNMENT (d gets overwritten)
```

Line 3 is the trap: `Counter c = a;` has an `=` sign, and is still the copy constructor — because `c` is being created on that exact line. The `=` in a declaration is just alternate syntax for direct construction, not a call to `operator=` at all.

```
COPY CONSTRUCTOR                         COPY ASSIGNMENT
Counter b( a );                          d = a;
b did not exist a moment ago             d already existed, gets overwritten

  a                                        a
  ┌───────────────┐                        ┌───────────────┐
  │ _value = 42    │                        │ _value = 42    │
  └───────────────┘                        └───────────────┘
          │                                         │
          ▼                                         ▼
  b  (brand new)                            d  (pre-existing)
  ┌───────────────┐                        ┌───────────────┐
  │ _value = 42    │                        │ _value = 42    │  ← was 0, now overwritten
  └───────────────┘                        └───────────────┘
```

---

## 6. Building a complete example from scratch

Two classes, side by side — one where the canonical form is trivial, one where it's essential — to see the same four-step process apply to both.

### 6.1 — `Fraction`: no pointers, canonical form is straightforward

```cpp
class Fraction {
private:
    int _num;
    int _den;

public:
    Fraction();
    Fraction(const Fraction &other);
    Fraction &operator=(const Fraction &rhs);
    ~Fraction();
};

Fraction::Fraction() : _num(0), _den(1) {}

Fraction::Fraction(const Fraction &other)
    : _num(other._num), _den(other._den) {}

Fraction &Fraction::operator=(const Fraction &rhs) {
    if (this == &rhs)
        return *this;
    _num = rhs._num;
    _den = rhs._den;
    return *this;
}

Fraction::~Fraction() {}
```

Nothing here can go wrong — every member is a plain `int`, so shallow and deep copying are literally the same operation. The canonical form is written purely as good discipline.

### 6.2 — `Name`: owns a heap resource, canonical form is essential

Already built piece by piece in section 3–4 above. Put together as one class:

```cpp
class Name {
private:
    char *_data;

public:
    Name(const char *str) {
        _data = new char[std::strlen(str) + 1];
        std::strcpy(_data, str);
    }
    Name(const Name &other) {
        _data = new char[std::strlen(other._data) + 1];
        std::strcpy(_data, other._data);
    }
    Name &operator=(const Name &rhs) {
        if (this == &rhs)
            return *this;
        delete[] _data;
        _data = new char[std::strlen(rhs._data) + 1];
        std::strcpy(_data, rhs._data);
        return *this;
    }
    ~Name() {
        delete[] _data;
    }
};
```

Here, every line of the canonical form is load-bearing. Delete any one of these four and copying a `Name` becomes unsafe.

---

## 7. Checklist before you consider a class "canonical"

- [ ] Declared all four members in the header (`.hpp`)
- [ ] Defined all four in the source file (`.cpp`) — never inline in the header
- [ ] Default constructor gives every member a sensible starting value
- [ ] Copy constructor uses an initializer list, takes `const ClassName &`
- [ ] If the class owns a pointer to heap memory: the copy constructor allocates *new* memory and copies contents, not just the address
- [ ] Copy assignment operator takes `const ClassName &`, returns `ClassName &`
- [ ] If the class owns a pointer to heap memory: the copy assignment operator guards against self-assignment, and frees its own old resource before copying the new one
- [ ] Destructor releases anything the class is responsible for (or is correctly empty, if it owns nothing)

---

## 8. Quick reference card

```
┌────────────────────────────┬───────────────────────┬─────────────────────────┐
│ Member                      │ Signature              │ Fires when...            │
├────────────────────────────┼───────────────────────┼─────────────────────────┤
│ Default constructor         │ ClassName();            │ ClassName obj;            │
│ Copy constructor             │ ClassName(const CN &o);│ ClassName b( a );         │
│                              │                         │ ClassName b = a;          │
│ Copy assignment operator     │ CN &operator=(const CN&)│ b = a;   (b already exists)│
│ Destructor                   │ ~ClassName();           │ scope ends / delete       │
└────────────────────────────┴───────────────────────┴─────────────────────────┘
```

**The question that resolves every ambiguous case:** did the object on the left already exist, the instant before this line ran?
- No → constructor (default or copy, depending on whether arguments were given)
- Yes → assignment operator

**The question that explains why any of this is required at all:** does this class own a pointer to something? If yes, the compiler's automatic copying (shallow — copies the address) will eventually break something. Writing the copy constructor and copy assignment operator by hand is how you replace that with a deep copy — independent memory, independent lifetime, no shared ownership.
