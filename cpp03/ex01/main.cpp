/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 23:33:42 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/03 00:27:37 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

int main(void) {
    std::cout << "\n--- constructor / destructor ---" << std::endl;
    {
        ScavTrap space("Space"); // ClapTrap constructor first, then ScavTrap
    } // here Scavtrap destructor fires first then ClapTrap destructor

    std::cout << "\n--- ScavTrap own attack and guardGate ---" << std::endl;
    ScavTrap cat("Cat");
    cat.attack("Tiger");
    cat.guardGate();

    std::cout << "\n--- inherited functions ---" << std::endl;
    cat.beRepaired(10);
    cat.takeDamage(20);

    std::cout << "\n--- copy constructor and copy assignment ---" << std::endl;
    ScavTrap copiaCat(cat); // copy constructor
    ScavTrap otherCat;      // default constructor
    otherCat = cat;         // copy assignment

    std::cout << "\n--- destruction ---" << std::endl;

    return 0;
}
