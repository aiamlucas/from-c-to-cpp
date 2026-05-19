# ex01 — My Awesome PhoneBook

Concepts: classes, public/private, constructors, initialization lists, getters/setters, std::cin, iomanip

---

## Programming paradigms

Languages sit on two axes:

```
             HOW to do it                  WHAT you want
imperative ◄─────────────────────────────────────────► declarative
               C, C++, Python              SQL, Haskell
```

Within imperative languages:

```
procedural  →  organized around functions     (C)
                 data and behavior are separate

OOP         →  organized around objects       (C++)
                 data and behavior live together
```


### Class vs instance

A **class** is a blueprint. An **instance** is the concrete thing built from it.

```
class Dog { ... }          ← blueprint, exists once in code

Dog rex("Rex", 3);         ← instance, lives in memory
Dog luna("Luna", 5);       ← another instance, separate data
```

`rex` and `luna` share the same methods but have independent attributes — changing `rex._name` does not touch `luna._name`.

Two terms that appear everywhere:
- **Attributes** (data members) — the data fields inside a class: `_name`, `_age`
- **Methods** (member functions) — the functions inside a class: `bark()`, `eat()`

---

## Classes

In C, data and behavior are separate by convention. You define a struct, then write functions that take a pointer to it:

```c
typedef struct s_player {
    char  _name[50];
    int   _health;
    int   _score;
} t_player;

void player_take_damage(t_player *p, int dmg)
{ 
	p->_health -= dmg; 
}
void player_add_score(t_player *p, int pts)
{ 
	p->_score += pts; 
}
...
```

A class formalizes this. Data and the functions that operate on it are declared as one unit. The compiler knows what belongs to what, access can be restricted, and the object carries its own behavior, you do not pass it around explicitly:

```cpp
class Player {
private:
    std::string _name;
    int         _health;
    int         _score;

public:
    Player(std::string name, int health);
    void takeDamage(int dmg);
    void addScore(int pts);
    void print() const;
};

void Player::takeDamage(int dmg) { _health -= dmg; }
void Player::addScore(int pts)   { _score += pts; }
void Player::print() const {
    std::cout << _name << " — hp: " << _health << "  score: " << _score << std::endl;
}
```

Every member function gets an implicit `this` pointer, a pointer to the object it was called on. `_health -= dmg` is really `this->_health -= dmg`; the compiler adds it silently.

---

## public / private / protected

Access specifiers do not affect memory layout. A `private int` and a `public int` are identical in memory. They control which code is allowed to read or write them.

```
┌──────────────────────────────────────────────────────┐
│            Animal (base class)                       │
│  private    _dna          ← Animal only              │
│  protected  _age          ← Animal + derived classes │
│  public     eat()         ← everywhere               │
└──────────────────────────────────────────────────────┘
                    │ inherits
                    ▼
┌──────────────────────────────────────────┐
│            Dog (derived class)           │
│  can access: protected + public          │
│  cannot access: private                  │
└──────────────────────────────────────────┘

┌──────────────┐
│   main.cpp   │  can only access: public
└──────────────┘
```

`protected` is for inheritance -> covered in Module 03. 
For now: `private` for internals, `public` for the interface.

### class vs struct — the only real difference

```cpp
class Dog  { std::string _name; };  // private by default
struct Cat  { std::string name;  };  // public by default
```

Everything else is identical.

### The _ convention

Prefixing private attributes with `_` is a convention, not enforced by the language. It makes intent immediately readable:

```cpp
void Player::takeDamage(int damage) {
    _health -= damage;   // _health = attribute, damage = parameter — obvious
}
```

---

## Constructors and initialization lists

A constructor runs automatically when an object is created. Same name as the class, no return type.

```cpp
Engine::Engine(int cylinders) : _cylinders(cylinders), _running(false) {
    std::cout << "Engine created" << std::endl;
}
```

The `: _cylinders(cylinders), _running(false)` part is the **initialization list**. It initializes attributes directly at construction time, before the body runs.

Without it, what happens inside `{ }` is assignment — the attribute is first default-constructed (garbage for primitives), then assigned. Two steps instead of one.

For `const` members and references, the initialization list is not optional — it is the only way to set them. A `const` attribute cannot be assigned after construction.

### Default constructor

Takes no arguments. If you define no constructors at all, the compiler generates one — but it leaves primitives uninitialized. Once you define any constructor yourself, the compiler stops generating the default.

---

## Getters and setters

Private attributes are only reachable from outside the class through public member functions. Functions that read are **getters**, functions that write are **setters**.

```cpp
double getCelsius() const { return _celsius; }          // getter
void   setCelsius(double c) { if (c >= -273.15) _celsius = c; }  // setter with validation
```

### const on getters

The `const` after the parameter list is a promise: this function will not modify any attribute. The compiler enforces it — assigning to an attribute inside a `const` method is a compiler error.

This matters when objects are passed as `const &`:

```cpp
void print(const Temperature &t) {
    std::cout << t.getCelsius();  // only works if getCelsius() is marked const
}
```

Not every attribute needs a getter and setter. You only expose what the interface requires. Exposing everything defeats the purpose of private.

---

## ASCII diagrams

#### Class anatomy & lifecycle

```
┌─────────────────────────────────────────────┐
│  CLASS  (blueprint — no memory yet)         │
│                                             │
│  class Dog {                                │
│    std::string  _name;   ← attributes       │
│    int          _age;                       │
│    bark();               ← methods          │
│  };                                         │
└──────────────┬──────────────────────────────┘
               │  instantiate
       ┌───────┴────────┐
       ▼                ▼
┌─────────────┐  ┌──────────────┐
│  Dog  rex   │  │  Dog  laika  │  ← instances (real memory)
│  _name="Rex"│  │  _name="laika│
│  _age=3     │  │  _age=5      │
└─────────────┘  └──────────────┘
  independent        independent
  data               data

LIFECYCLE
─────────────────────────────────────────────▶  time
  Dog rex("Rex",3)      rex.bark()      }
       ↑                                ↑
  constructor fires                destructor fires
  (_name=name, _age=age)           (out of scope)

```


#### Encapsulation: private, public, getters & setters
```
┌──────────────────────────────────────────────────────┐
│  BankAccount                                         │
│                                                      │
│  ┌─── private ──────────────────────────────────┐    │
│  │  _balance  :  double                         │    │
│  │  _owner    :  string                         │    │
│  │  only this class can read/write directly     │    │
│  └──────────────────────────────────────────────┘    │
│                         ↑ reads       ↑ writes       │
│  ┌─── public ────────── │ ─────────── │ ─────────┐   │
│  │  getBalance()  ──────┘  (no arg)   │          │   │
│  │  deposit(amt)  ─────────────────── ┘          │   │
│  │  withdraw(amt) ────────────────── (validates) │   │
│  └───────────────────────────────────────────────┘   │
│                        ↑                             │
└────────────────────────│─────────────────────────────┘
                         │  only public is reachable
                  main.cpp / outside world

  account._balance = 999   ← COMPILER ERROR (private)
  account.getBalance()     ← OK  (public getter)
  account.deposit(100)     ← OK  (public setter — writes + validates)
```
---

## Fixed arrays as class attributes

A fixed-size array declared as an attribute lives inside the object itself — created and destroyed with it, no manual memory management:

```cpp
class PhoneBook {
private:
    Contact _contacts[8];   // 8 Contact objects live inside PhoneBook
    int     _count;
};
```

Size is fixed at compile time. No `new`, no `delete`, no destructor needed for the array itself.

---

## std::cin and std::getline

`std::cin` is the standard input stream. `>>` reads one token, stopping at whitespace:

```cpp
std::cin >> word;   // reads "hello" from "hello world" — stops at the space
```

`std::getline` reads the full line including spaces:

```cpp
std::getline(std::cin, line);
```

### The mixing problem

`>>` leaves the newline in the buffer. The next `std::getline` reads that leftover `\n` and returns an empty string:

```
input:  "25\n"
cin >> age        →  reads "25", buffer: "\n"
getline(cin, str)   →  reads "\n", str = ""   ← bug
```

Fix: flush the leftover newline after `>>`:

```cpp
std::cin >> age;
std::cin.ignore();
std::getline(std::cin, line);
```

### End of input

When the user presses Ctrl+D, `std::cin` enters a failed state:

```cpp
if (!std::getline(std::cin, line))
    return 0;   // stream closed — exit cleanly
```

---

## iomanip — formatted output
 
`<iomanip>` provides manipulators — objects inserted into a stream to change how the next value prints.
 
```
manipulator        sticky?   effect
─────────────────────────────────────────────────────────────
std::setw(n)         no      next value occupies at least n chars
std::setfill(c)      yes     padding character (default: space)
std::left            yes     pad on the right  (left-align text)
std::right           yes     pad on the left   (right-align text, default)
std::setprecision(n) yes     decimal digits for floats
std::fixed           yes     fixed-point notation for floats
```
 
Sticky means it stays active until you change it. `setw` is the exception — it resets after every single value.
 
### setw — field width
 
```
setw(10) with "hi"        →  "        hi"   (8 spaces + hi)
setw(10) with "hello"     →  "     hello"   (5 spaces + hello)
setw(10) with "Alexander" →  " Alexander"   (1 space  + Alexander)
setw(10) with 42          →  "        42"   (8 spaces + 42)
```
 
### left / right — alignment
 
```cpp
std::cout << std::setw(10) << std::right << "hi";  // "        hi"
std::cout << std::setw(10) << std::left  << "hi";  // "hi        "
```
 
`right` is the default. Once you set `left`, every subsequent `setw` pads on the right until you set `right` again.
 
### setfill — padding character
 
```cpp
std::cout << std::setfill('0') << std::setw(5) << 42;    // "00042"
std::cout << std::setfill('-') << std::setw(8) << "hi";  // "------hi"
```
 
Stays active until changed. Reset to space with `std::setfill(' ')`.
 
### setprecision + fixed — floats
 
```cpp
double pi = 3.14159265;
 
std::cout << std::setprecision(2) << pi;             // "3.1"   (2 sig figs)
std::cout << std::fixed << std::setprecision(2) << pi;  // "3.14"  (2 decimal places)
```
 
Without `fixed`, `setprecision` counts significant figures. With `fixed`, it counts decimal places.
 
### Combining manipulators
 
```cpp
// 10-char wide columns, right-aligned, pipe separated
std::cout << std::setw(10) << std::right << "index"    << "|"
          << std::setw(10) << std::right << "firstname" << "|"
          << std::setw(10) << std::right << "lastname"  << "|"
          << std::setw(10) << std::right << "nickname"  << std::endl;
```
 
Output:
```
     index| firstname|  lastname|  nickname
```
 
Note: `setw` resets after each `<<` value, so you must repeat it for every column.
 
### iomanip does not truncate
 
If the value is longer than `setw`, it prints in full — the width is ignored. Truncation is your responsibility before passing to the stream:
 
```cpp
std::string truncate(const std::string &s, int width)
{
    if ((int)s.length() > width)
        return s.substr(0, width - 1) + ".";
    return s;
}
```
 
So a full SEARCH row for this exercise:
 
```cpp
std::cout << std::setw(10) << std::right << truncate(firstName, 10) << "|"
          << std::setw(10) << std::right << truncate(lastName, 10)  << "|"
          << std::setw(10) << std::right << truncate(nickname, 10)  << std::endl;
```
