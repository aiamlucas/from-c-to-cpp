# OOP Basics — C++

---

## Declaration vs Definition

```
declaration  →  says WHAT exists       →  lives in .hpp
definition   →  says HOW it works      →  lives in .cpp
```

```cpp
// Zombie.hpp — DECLARATIONS
class Zombie {
private:
    std::string _name;       // attribute — exists
public:
    Zombie(std::string name); // constructor — exists
    ~Zombie();                // destructor  — exists
    void announce(void);      // method      — exists
};

// Zombie.cpp — DEFINITIONS
Zombie::Zombie(std::string name) : _name(name) {}  // constructor — here is how
Zombie::~Zombie() { std::cout << _name << " destroyed\n"; } // destructor 
void Zombie::announce(void) { // method 
    std::cout << _name << ": BraiiiiiiinnnzzzZ...\n";
}
```

---

## Constructor / Destructor
 
```
constructor  →  runs when object is CREATED   →  sets valid state
destructor   →  runs when object is DESTROYED →  cleans up
```
 
The definition in `Zombie.cpp` is the **recipe** — it does not create anything by itself.
The creation happens in `main.cpp` when someone calls it:
 
```cpp
// main.cpp
#include "Zombie.hpp"
 
int main(void) {
    // --- stack ---
    {
        Zombie z("Foo");    // constructor fires — _name = "Foo"
        z.announce();       // Foo: BraiiiiiiinnnzzzZ...
    }                       // destructor fires  — "Foo destroyed"
                            // automatic, you do nothing
 
    // --- heap ---
    Zombie *z = new Zombie("Bar");  // constructor fires — _name = "Bar"
    z->announce();                  // Bar: BraiiiiiiinnnzzzZ...
    delete z;                       // destructor fires  — "Bar destroyed"
                                    // YOU must call delete
    return 0;
}
```
 
Output:
```
Foo: BraiiiiiiinnnzzzZ...
Foo destroyed
Bar: BraiiiiiiinnnzzzZ...
Bar destroyed
```
 
Without a constructor, object memory starts as garbage.
 

## Access modifiers

```cpp
class Zombie {
private:
    std::string _name;   // only Zombie methods can touch this
public:
    void announce();     // anyone can call this
};
```

```
private    →  inside the class only
public     →  anywhere
protected  →  class + derived classes (inheritance — later)
```

Convention: prefix private attributes with `_`.

---

## Member function vs free function

```cpp
// member — declared inside class {}, has Zombie:: prefix, accesses private
void Zombie::announce(void) { std::cout << _name; }

// free — declared outside class {}, no prefix, no private access
Zombie *newZombie(std::string name) { return new Zombie(name); }
```

```
z.announce()        // member — called ON an object
newZombie("Foo")    // free   — called standalone
```

---

## `::` scope operator

```cpp
void Zombie::announce() { ... }
//   ───────
//   "this announce belongs to Zombie — not a free function"
```
