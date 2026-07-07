#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name) {
    Zombie *horde = new Zombie[N]; // single allocation -> N zombies on the heap
    for (int i = 0; i < N; i++)
        horde[i].setName(name);
    return horde; // returning a pointer to the first element
}
