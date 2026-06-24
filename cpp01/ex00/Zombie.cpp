#include "Zombie.hpp"

// constructor definition -> telling the compiler how to build a Zombie
Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }

void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
