/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 16:30:03 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/02 23:43:31 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main(void) {
    std::cout << "\n--- construction ---" << std::endl;
    ClapTrap insect("Mosquito");
    ClapTrap copyBicho(insect); // copy constructor
    ClapTrap spider;
    spider = insect; // copy assignment

    std::cout << "\n--- normal attack - repair - damage ---" << std::endl;
    insect.attack("Cat");
    insect.beRepaired(3);
    insect.takeDamage(2);

    std::cout << "\n--- takeDamage underflow ---" << std::endl;
    ClapTrap animal("Dog");
    animal.takeDamage(9999); // hitpoints must clamp to 0
    animal.attack("Human");  // should now do nothing.

    std::cout << "\n--- energy drain guard ---" << std::endl;
    ClapTrap drained("Drained");
    for (int i = 0; i < 12; i++)
        drained.attack("Target"); // only the first 10 should print
    std::cout << "\n--- destruction ---" << std::endl;
    return 0;
}
