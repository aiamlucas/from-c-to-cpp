/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/18 23:11:50 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

// initializer list
Zombie::Zombie() : _name("") {}

Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }

// const promise that this function won't modify "name"
// &name -> reference (is an alias to the original string) avoids copying
void Zombie::setName(const std::string &name) { _name = name; }

void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
