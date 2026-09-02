/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:52:16 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/03 00:55:55 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

int main(void) {
    std::cout << "\n--- constructor / destructor ---" << std::endl;
    {
        FragTrap orange("Orange"); // ClapTrap constructor first, then FragTrap
    } // here FragTrap destructor fires first then ClapTrap destructor

    std::cout << "\n--- FragTrap own attack and highFivesGuys ---" << std::endl;
    FragTrap apple("Apple");
    apple.attack("Strawberry");
    apple.highFivesGuys();

    std::cout << "\n--- inherited functions ---" << std::endl;
    apple.beRepaired(10);
    apple.takeDamage(20);

    std::cout << "\n--- copy constructor and copy assignment ---" << std::endl;
    FragTrap copyApple(apple); // copy constructor
    FragTrap otherApple;       // default constructor
    otherApple = apple;        // copy assignment

    std::cout << "\n--- destruction ---" << std::endl;

    return 0;
}
