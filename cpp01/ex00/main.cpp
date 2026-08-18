/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:16:29 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/18 15:53:54 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main(void) {

    // Test 1: stack zombie
    // {} scope block forces the zombie to be destroyed automatically
    std::cout << "--- stack zombie---" << std::endl;
    {
        Zombie stackZombie("Stack Zombie");
        stackZombie.announce();
    } // destructor is called here (end of block) {}
    std::cout << "--- stack zombie is already gone ---" << std::endl;

    // Test 2: heap zombie
    // newZombie() returns a pointer that outlives this scope
    // need to call delete
    std::cout << "\n--- heap zombie ---" << std::endl;
    Zombie *heapZombie = newZombie("Heap Zombie");
    heapZombie->announce();
    std::cout << "--- heap zombie still alive here ---" << std::endl;
    delete heapZombie; // cleaning from the heap memory
    std::cout << "--- heap zombie now gone---" << std::endl;

    // Test 3: stack random chump
    std::cout << "\n--- stack random chump ---" << std::endl;
    randomChump("random Chump");
    std::cout << "--- after randomChump ---" << std::endl;

    return 0;
}
