/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:16 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/09 19:17:18 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void) {

    // Test 1 (single zombie)
    std::cout << "--- test 1 ---" << std::endl;
    Zombie *single = zombieHorde(1, "Alone");
    single[0].announce();
    delete[] single;

    // Test 2 (multiple zombies):
    std::cout << "\n--- test 2 ---" << std::endl;
    Zombie *multiples = zombieHorde(5, "Chespirito");

    for (int i = 0; i < 5; i++)
        multiples[i].announce();
    delete[] multiples;

    // Test 3 (testing destructor only)
    std::cout << "\n--- test 3 ---" << std::endl;
    Zombie *ordered = zombieHorde(3, "Sunra");
    delete[] ordered;
    return 0;
}
