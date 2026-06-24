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

// return a pointer to the heap-allocated Zombie
Zombie *newZombie(std::string name);
// stack Zombie
void randomChump(std::string name);

#endif
