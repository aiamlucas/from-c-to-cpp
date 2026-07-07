# ex02 — HI THIS IS BRAIN (reference)

---

## Reference — alias for an existing variable (C++ only)

```cpp
std::string  brain     = "HI THIS IS BRAIN";
std::string *stringPTR = &brain;   // pointer  — stores address of brain
std::string &stringREF = brain;    // reference — alias for brain
```

```
rules:
  must be initialized at declaration   →  std::string &ref = brain;  ✓
  cannot be rebound                    →  always refers to brain
  cannot be null                       →  always valid
```

---

## Pointer vs reference

```
                  POINTER              REFERENCE
declaration       string *p = &s;      string &r = s;
get value         *p                   r
get address       p                    &r
can be null       yes                  no
can be rebound    yes                  no
```

---

## & — two meanings

```cpp
std::string &ref = brain;   // & in type  →  reference declaration
std::string *p   = &brain;  // & on value →  address-of operator
std::cout        << &brain;  // & on value →  address-of operator
```

---

## Printing addresses and values

```cpp
// addresses — all three print the same value
std::cout << &brain     << std::endl;  // address of brain
std::cout << stringPTR  << std::endl;  // address stored in pointer = &brain
std::cout << &stringREF << std::endl;  // address of what ref refers to = &brain

// values — all three print the same string
std::cout << brain      << std::endl;  // "HI THIS IS BRAIN"
std::cout << *stringPTR << std::endl;  // dereference pointer
std::cout << stringREF  << std::endl;  // use reference directly
```

---

## Why all three addresses are the same

```
&brain      →  address of brain
stringPTR   →  stores address of brain
&stringREF  →  reference IS brain → gives address of brain
```

A reference has no address of its own — it's another name for the same memory location.
