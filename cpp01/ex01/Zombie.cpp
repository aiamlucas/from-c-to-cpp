#include "Zombie.hpp"

// default constructor - no make yet (used by new Zombie[N])
Zombie::Zombie() : _name("") {}
// parameterized constructor - name set at creation
Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }
void Zombie::setName(std::string name) { _name = name; }

void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
