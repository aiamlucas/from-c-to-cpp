# cpp01 — ex03 — Unnecessary violence

Concepts: const reference return, reference member, pointer member, getter/setter, when to use reference vs pointer as class member

---

## Index

1. [Getter and setter](#1-getter-and-setter)
2. [Returning a const reference](#2-returning-a-const-reference)
3. [Reference as class member](#3-reference-as-class-member)
4. [Pointer as class member](#4-pointer-as-class-member)
5. [Reference member vs pointer member](#5-reference-member-vs-pointer-member)
6. [The design question — HumanA vs HumanB](#6-the-design-question--humana-vs-humanb)

---

## 1. Getter and setter

A **getter** reads a private attribute. A **setter** writes it. They are the controlled interface between the private data and the outside world.

```cpp
class Weapon {
private:
    std::string _type;   // private — nobody touches this directly

public:
    const std::string &getType() const;   // getter — read _type
    void setType(std::string type);        // setter — write _type
};
```

Without getter/setter, anyone could do `weapon._type = "rubber duck"` — bypassing any validation or logic the class needs. With them, the class controls access.

```
outside world          Weapon class
─────────────          ─────────────────────────────
weapon.getType()  →    reads _type, returns it safely
weapon.setType(x) →    validates x if needed, sets _type
weapon._type      →    ✗ compiler error — private
```

---

## 2. Returning a const reference

`getType()` returns `const std::string &` — a constant reference to `_type`:

```cpp
const std::string &Weapon::getType() const {
    return _type;
}
```

Breaking it down:

```
const std::string &getType() const
─────                                →  the returned reference cannot be modified
      ──────────                     →  type of what we refer to
                 &                   →  return a reference, not a copy
                   ─────             →  this method doesn't modify the object
```

### Why return a reference instead of a value?

```cpp
std::string  getType();    // returns a COPY — new string created every call
std::string &getType();    // returns a REFERENCE — no copy, direct access
```

Returning by reference is faster — no copy is made. The caller reads directly from `_type`.

### Why const?

Without `const`, the caller could modify `_type` through the reference:

```cpp
std::string &getType() { return _type; }   // dangerous
weapon.getType() = "rubber duck";           // modifies _type directly — bypasses setter
```

With `const std::string &`, the caller can read but not modify:

```cpp
const std::string &getType() { return _type; }
weapon.getType() = "rubber duck";   // ✗ compiler error — const reference
```

### The `const` at the end

```cpp
const std::string &getType() const { ... }
//                            ─────
//                            this method promises not to modify
//                            any attribute of the object
//                            required for getters — they only read
```

A method marked `const` can be called on `const` objects. Without it, passing a `const Weapon &` to a function and calling `getType()` would fail to compile.

---

## 3. Reference as class member

`HumanA` always has a weapon — it's given one at construction and keeps it forever. This is a perfect case for a **reference member**:

```cpp
class HumanA {
private:
    std::string _name;
    Weapon      &_weapon;   // reference member — always refers to a Weapon

public:
    HumanA(std::string name, Weapon &weapon);
    void attack() const;
};
```

### Initialization — must use the init list

Reference members **must** be initialized in the constructor's initialization list. A reference cannot be default-constructed (it must always refer to something):

```cpp
HumanA::HumanA(std::string name, Weapon &weapon)
    : _name(name), _weapon(weapon) {}
//                 ───────────────
//                 reference bound here — cannot be done in the body
```

### What this means in memory

```
HumanA bob("Bob", club);

STACK:
┌──────────────────────┐
│ bob                  │
│   _name = "Bob"      │
│   _weapon ───────────────────► club (the actual Weapon object)
└──────────────────────┘
```

`_weapon` is not a copy of `club` — it IS `club`. When `club.setType("new type")` is called, `bob._weapon` reflects the change immediately because they're the same object.

### The consequence

```cpp
Weapon club("crude spiked club");
HumanA bob("Bob", club);
bob.attack();                        // "Bob attacks with their crude spiked club"

club.setType("some other type of club");
bob.attack();                        // "Bob attacks with their some other type of club"
```

The weapon type updated — `bob` didn't need to do anything. The reference always reflects the current state of `club`.

---

## 4. Pointer as class member

`HumanB` may or may not have a weapon. A reference can't represent "no weapon" — it must always refer to something. A **pointer** can be `NULL`:

```cpp
class HumanB {
private:
    std::string _name;
    Weapon      *_weapon;   // pointer member — can be NULL (no weapon)

public:
    HumanB(std::string name);
    void setWeapon(Weapon &weapon);
    void attack() const;
};
```

### Initialization

The pointer starts as `NULL` — HumanB is created without a weapon:

```cpp
HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {}
```

A weapon can be assigned later via `setWeapon`:

```cpp
void HumanB::setWeapon(Weapon &weapon) {
    _weapon = &weapon;   // store the address of the weapon
}
```

### What this means in memory

```
HumanB jim("Jim");        // no weapon yet

STACK:
┌──────────────────────┐
│ jim                  │
│   _name = "Jim"      │
│   _weapon = NULL     │  ← no weapon
└──────────────────────┘

jim.setWeapon(club);      // weapon assigned

┌──────────────────────┐
│ jim                  │
│   _name = "Jim"      │
│   _weapon ───────────────────► club
└──────────────────────┘
```

### The attack check

Since `_weapon` can be `NULL`, `attack()` must check before using it:

```cpp
void HumanB::attack() const {
    if (_weapon)
        std::cout << _name << " attacks with their "
                  << _weapon->getType() << std::endl;
    else
        std::cout << _name << " has no weapon" << std::endl;
}
```

---

## 5. Reference member vs pointer member

```
                    REFERENCE MEMBER           POINTER MEMBER
                    ────────────────────────   ────────────────────────
declaration         Weapon &_weapon;           Weapon *_weapon;
can be NULL         no                         yes
must init at birth  yes (init list)            no (can start as NULL)
can be rebound      no                         yes (_weapon = &other)
access syntax       _weapon.getType()          _weapon->getType()
represents          "always has one"           "may or may not have one"
```

---

## 6. The design question — HumanA vs HumanB

The subject is teaching you to choose the right tool based on the semantic meaning:

```
HumanA — always armed
──────────────────────────────────────────────────
"HumanA will always be armed"
→ weapon is guaranteed at construction
→ cannot exist without a weapon
→ reference member: Weapon &_weapon
→ weapon passed in constructor

HumanB — optionally armed
──────────────────────────────────────────────────
"HumanB may not always have a weapon"
→ weapon is optional
→ can exist without one, armed later
→ pointer member: Weapon *_weapon (can be NULL)
→ weapon set via setWeapon()
```

The code difference is small — `&` vs `*`, init list vs setter. The design reasoning is the exercise. Choosing `Weapon &` for HumanA communicates to anyone reading the code: "this object always has a weapon, guaranteed." Choosing `Weapon *` for HumanB communicates: "this might not have a weapon — check before using."

Code is documentation. The type you choose tells the story.
