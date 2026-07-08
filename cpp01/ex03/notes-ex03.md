# ex03 — Unnecessary violence (reference)

---

## Getter and setter

```cpp
class Weapon {
private:
    std::string _type;
public:
    const std::string &getType() const;  // read _type — returns const ref
    void setType(std::string type);       // write _type
};
```

---

## const reference return

```cpp
const std::string &Weapon::getType() const { return _type; }
─────                  →  caller cannot modify through this reference
              &        →  no copy made — direct access to _type
                ─────  →  method doesn't modify the object
```

---

## Reference member — HumanA (always armed)

```cpp
class HumanA {
    Weapon &_weapon;   // reference — always refers to something, cannot be NULL
public:
    HumanA(std::string name, Weapon &weapon);
};

// must initialize in init list — reference cannot be default-constructed
HumanA::HumanA(std::string name, Weapon &weapon)
    : _name(name), _weapon(weapon) {}
```

---

## Pointer member — HumanB (optionally armed)

```cpp
class HumanB {
    Weapon *_weapon;   // pointer — can be NULL (no weapon)
public:
    HumanB(std::string name);
    void setWeapon(Weapon &weapon);
};

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {}

void HumanB::setWeapon(Weapon &weapon) { _weapon = &weapon; }
```

Attack must check for NULL:

```cpp
void HumanB::attack() const {
    if (_weapon)
        std::cout << _name << " attacks with their " << _weapon->getType();
}
```

---

## Reference vs pointer member

```
                  REFERENCE &          POINTER *
can be NULL       no                   yes
init at birth     yes (init list)      no (NULL ok)
rebind            no                   yes
access            _weapon.getType()    _weapon->getType()
use when          always has one       may not have one
```

---

## The design rule

```
guaranteed at construction, always valid   →  reference member  (HumanA)
optional, assigned later, can be absent    →  pointer member    (HumanB)
```
