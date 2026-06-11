#include "Zombie.hpp"

int main(void) {

    // Test 1: stack zombie
    std::cout << "--- stack zombie---" << std::endl;
    {
        Zombie stackZombie("StackFoo");
        stackZombie.announce();
    }
    std::cout << "--- stack zombie is already gone ---" << std::endl;

    // Test 2: heap zombie
    std::cout << "\n--- heap zombie ---" << std::endl;
    Zombie *heapZombie = newZombie("HeapFoo");
    heapZombie->announce();
    std::cout << "--- heap zombie still alive here ---" << std::endl;
    delete heapZombie;
    std::cout << "--- heap zombie now gone---" << std::endl;

    // Test 3: stack random chump
    std::cout << "\n--- stack random chump ---" << std::endl;
    randomChump("ChumpFoo");
    std::cout << "--- after randomChump ---" << std::endl;

    return 0;
}
