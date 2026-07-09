/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/09 19:17:05 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// default constructor - no make yet (used by new Zombie[N])
Zombie::Zombie() : _name("") {}
// parameterized constructor - name set at creation
Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }
void Zombie::setName(std::string name) { _name = name; }

void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
