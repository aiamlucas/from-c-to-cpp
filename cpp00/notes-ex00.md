# ex00 — Megaphone

Concepts needed: `iostream`, `std::string`, `argc`/`argv`, character manipulation

---

## 1. Output in C++

The first thing to drop from C is `printf`. In C++ output goes through `std::cout`,
which lives in the `iostream` header.

```cpp
#include <iostream>

int main()
{
    std::cout << "hello" << std::endl;
    return 0;
}
// OUTPUT: hello
```

`<<` sends data into the stream. You can chain as many as you want:

```cpp
std::cout << "hello" << " " << "world" << std::endl;
// OUTPUT: hello world
```

`std::endl` adds a newline and flushes the output. You can also just use `"\n"` if you
do not need to flush.

---

## 2. argc and argv — same as C, slightly different type

You already know `argc` and `argv` from C. In C++ they work exactly the same way.
The only difference you will notice is that you can store each argument as a
`std::string` instead of working with raw `char *`:

```cpp
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "no arguments" << std::endl;
        return 0;
    }

    std::string word = argv[1];   // argv[1] converts to std::string automatically
    std::cout << word << std::endl;

    return 0;
}
```

To loop over all arguments:

```cpp
int main(int argc, char *arv[])
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		std::cout << arg << std::endl;
	}
	return 0;
}
```

---

## 3. std::string — the C++ string
 
`std::string` is the C++ replacement for `char *`. It manages its own memory, knows
its own length, and gives you a clean interface to work with text.
 
### The basics
 
```cpp
#include <string>
 
std::string str = "hello";
 
str.length();       // number of characters — like strlen, no need to count manually
str[0];             // access a single character — like str[0] in C
str += " world";    // concatenation — no strcat, no buffer, no size calculation
```
 
You can loop over every character with a standard index loop:
 
```cpp
std::string str = "hello";
 
for (int i = 0; i < (int)str.length(); i++)
    std::cout << str[i] << std::endl;   // prints one character per line
```
 
Each `str[i]` is a `char`. The same `char` you know from C. You can read it, modify it,
and pass it to any C character function.
 
### Concatenation — no malloc, no strcat, no size tracking
 
In C, joining two strings is an operation. You have to allocate enough memory, track
the sizes and call `strcat`. One mistake and you have a buffer overflow or a leak.
 
```c
// C
char *result = malloc(strlen(s1) + strlen(s2) + 1);
strcpy(result, s1);
strcat(result, s2);
// ... use result ...
free(result);
```
 
```cpp
// C++
std::string s1 = "hello";
std::string s2 = " world";
std::string result = s1 + s2;   // "hello world" — memory handled automatically
```
 
`+=` appends in place:
 
```cpp
std::string str = "hello";
str += " world";    // str is now "hello world"
str += "!";         // str is now "hello world!"
```
 
### Comparison — no strcmp
 
In C you cannot use `==` to compare strings. This compares pointers, not content.
You have to call `strcmp` and check if the result is 0. In C++ `==` just works:
 
```cpp
// C
if (strcmp(s1, s2) == 0)
    printf("equal\n");
 
// C++
std::string s1 = "hello";
std::string s2 = "hello";
 
if (s1 == s2)
    std::cout << "equal" << std::endl;
 
if (s1 != s2)
    std::cout << "not equal" << std::endl;
```
 
### Substring — extracting part of a string
 
In C you use `strncpy` or pointer arithmetic to get a piece of a string. In C++:
 
```cpp
std::string str = "hello world";
 
std::string sub = str.substr(6, 5);   // start at index 6, take 5 characters
std::cout << sub << std::endl;      // "world"
 
std::string from = str.substr(6);     // from index 6 to the end
std::cout << from << std::endl;     // "world"
```
 
### Finding — searching inside a string
 
In C you use `strstr` or `strchr`. In C++ strings have `find` built in:
 
```cpp
std::string str = "hello world";
 
int pos = str.find("world");    // returns the index where "world" starts
std::cout << pos << std::endl;  // 6
 
if (str.find("world") != std::string::npos)   // npos means "not found"
    std::cout << "found" << std::endl;
 
if (str.find("xyz") == std::string::npos)
    std::cout << "not found" << std::endl;
```
 
`std::string::npos` is a special value that means "no position" — returned when `find`
finds nothing. Think of it as the `NULL` of string positions.
 
### Empty check
 
```cpp
std::string str = "";
 
if (str.empty())
    std::cout << "string is empty" << std::endl;
 
if (str.length() == 0)   // same thing, two ways to check
    std::cout << "string is empty" << std::endl;
```
 
### Copying — it just works
 
In C, copying a string means allocating memory and calling `strcpy`. Assigning a
`char *` to another `char *` just copies the pointer, both point to the same memory,
one change affects both.
 
```c
// C — this does NOT copy the string, just the pointer
char *a = "hello";
char *b = a;       // b and a point to the same place
```
 
```cpp
// C++ — this actually copies the string content
std::string a = "hello";
std::string b = a;    // b is a full independent copy
b += " world";        // modifying b does NOT affect a
 
std::cout << a << std::endl;   // hello
std::cout << b << std::endl;   // hello world
```
 
---
 
## 4. Character manipulation — toupper
 
To convert a character to uppercase you use `toupper` from `<cctype>`.
This is the C++ version of the C header `<ctype.h>` — same function, different header name.
 
```cpp
#include <cctype>
 
char c = 'a';
char upper = toupper(c);   // 'A'
```
 
`toupper` works on a single `char`. Non-letter characters (spaces, dots, `!`) are
returned unchanged — you do not need to check before calling it.
 
To uppercase an entire string, loop over it and apply `toupper` to each character:
 
```cpp
#include <iostream>
#include <string>
#include <cctype>
 
int main()
{
    std::string str = "hello world";
 
    for (int i = 0; i < (int)str.length(); i++)
        str[i] = toupper(str[i]);
 
    std::cout << str << std::endl;   // HELLO WORLD
    return 0;
}
```
