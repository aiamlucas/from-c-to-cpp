/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 19:26:43 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// initialize name to an empty string
// ":" -> syntax for the initializer list
Zombie::Zombie() : _name("") {}

// the destructor is called automatically when delete[]
// prints which zombie is being destroied
Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }
void Zombie::setName(const std::string &name) { _name = name; }

void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
