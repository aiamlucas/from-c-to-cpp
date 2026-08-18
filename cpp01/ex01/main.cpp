/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:16 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/18 21:58:25 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main(void) {

    // Test 1 (single zombie) -> check creation and destruction
    std::cout << "--- test 1 ---" << std::endl;
    Zombie *single = zombieHorde(1, "Alone");
    single[0].announce();
    delete[] single; // destructor for each zombie in the array

    // Test 2 (multiple zombies) -> check that all get named and can announce
    std::cout << "\n--- test 2 ---" << std::endl;
    Zombie *multiples = zombieHorde(5, "Chespirito");

    for (int i = 0; i < 5; i++)
        multiples[i].announce();
    delete[] multiples;

    // Test 3 (testing destructor only)
    std::cout << "\n--- test 3 ---" << std::endl;
    Zombie *trio = zombieHorde(3, "Sunra");
    delete[] trio;
    return 0;
}
