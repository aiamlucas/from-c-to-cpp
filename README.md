# From C to C++

## Context

At this point in the 42 curriculum, after completing the C modules (Libft, ft_printf, 
get_next_line, push_swap, frac-tol, philosophers and minishell), 
we start learning C++ through the CPP modules.

This is the shift from procedural programming to **Object-Oriented Programming (OOP)**.

---

## Standard & Requirements

All code is written to the **C++98 standard** (`-std=c++98`), as required by 42.

**Why C++98?**
42 focuses on building a solid foundation. The core concepts like classes, memory management, inheritance, polymorphism are the same across all C++ standards.
Once you have those, moving to C++11 or later is just learning new features on top of a base you already understand.

### 42 Formatting Rules

| Rule                        | Detail                                               |
|-----------------------------|------------------------------------------------------|
| Classes                     | `UpperCamelCase`                                     |
| Files                       | Named after the class: `MyClass.hpp`, `MyClass.cpp`  |
| Headers                     | Must include guards (`#ifndef MYCLASS_HPP`)          |
| Output                      | Every message ends with `\n`, printed to stdout      |
| Implementation in headers   | Forbidden (except function templates)                |
| `using namespace`           | Forbidden                                            |
| `friend` keyword            | Forbidden unless explicitly stated                   |
| STL (containers/algorithms) | Only allowed from Module 08                          |
| `printf`, `malloc`, `free`  | Forbidden                                            |
| Memory leaks                | Must be avoided when using `new`                     |
| Orthodox Canonical Form     | Required from Module 02 onward                       |

**What is the Orthodox Canonical Form?**
The Orthodox Canonical Form (OCF) is a convention that requires every class to explicitly define four special member functions:

```
class MyClass
{
public:
    MyClass();                                // Default constructor
    MyClass(const MyClass &other);            // Copy constructor
    MyClass &operator=(const MyClass &other); // Copy assignment operator
    ~MyClass();                               // Destructor
};
```

In C++, if you do not define these, the compiler generates them automatically with a shallow copy, which breaks any class that manages heap memory.
Defining all four explicitly gives you full control over object lifecycle.

---

## Reference & Guide

The main learning guide used alongside the 42 subjects is:

**C++ Primer — Stanley B. Lippman, Josee Lajoie, Barbara E. Moo (5th edition)**

Although the book covers C++11, the core concepts like OOP, classes, memory management and templates, are identical in C++98. 
C++11-specific features (listed below) are skipped.

Online reference: [cppreference.com](https://en.cppreference.com)

---

## C++98 vs C++11

C++11 was a major revision released in 2011, over a decade after C++98.

### Language Features introduced in C++11  (not used in this repo)

These did not exist in C++98. Using them with `-std=c++98` will cause a compiler error.

| Feature                        | C++11 syntax                            |
|--------------------------------|-----------------------------------------|
| `auto` type deduction          | `auto x = 5;`                           |
| `nullptr`                      | use `NULL` or `0` instead               |
| Range-based for loop           | `for (int x : vec)`                     |
| Lambda functions               | `[](int x) { return x * 2; }`           |
| `decltype`                     | `decltype(x) y = x;`                    |
| `override` / `final`           | virtual function specifiers             |
| Delegating constructors        | constructor calling another constructor |
| `= default` / `= delete`       | for special member functions            |
| `enum class`                   | strongly typed enums                    |
| `constexpr`                    | compile-time constant expressions       |
| Variadic templates             | templates with variable argument count  |
| Move semantics / `&&`          | rvalue references                       |
| `noexcept`                     | exception specifier                     |
| Uniform initialization `{}`    | `int x{5};`                             |
| In-class member initialization | `int _x = 0;` directly in class body    |

### Standard Library additions introduced in C++11 — not used in this repo

These containers and utilities were added to the standard library in C++11 and are not available under C++98.

| Feature                                     | Header               |
|---------------------------------------------|----------------------|
| `std::array`                                | `<array>`            |
| `std::unordered_map` / `std::unordered_set` | `<unordered_map>`    |
| `std::tuple`                                | `<tuple>`            |
| Smart pointers (`unique_ptr`, `shared_ptr`) | `<memory>`           |
| `std::thread`                               | `<thread>`           |
| `std::regex`                                | `<regex>`            |
| `std::chrono`                               | `<chrono>`           |
| `std::function`                             | `<functional>`       |
| `std::initializer_list`                     | `<initializer_list>` |

---

## CPP Modules

| Module | Topic                                                              |
|--------|--------------------------------------------------------------------|
| CPP00  | Namespaces, classes, member functions, iostream, const             |
| CPP01  | Memory allocation, references, pointers to members, file streams   |
| CPP02  | Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form |
| CPP03  | Inheritance                                                        |
| CPP04  | Subtype polymorphism, abstract classes, interfaces                 |
| CPP05  | Repetition and Exceptions                                          |
| CPP06  | C++ casts                                                          |
| CPP07  | Templates                                                          |
| CPP08  | Templated containers, iterators, algorithms                        |
| CPP09  | STL                                                                |
