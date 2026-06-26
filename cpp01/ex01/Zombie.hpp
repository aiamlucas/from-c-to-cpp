#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie();                       // default constructor - new Zombie[N]
    Zombie(std::string name);       // parameterized
    ~Zombie();                      // destructor
    void setName(std::string name); // setter for the Zombies names
    void announce(void);
};

Zombie *zombieHorde(int N, std::string name);

#endif
