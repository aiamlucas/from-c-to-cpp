/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:16:16 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/09 19:16:18 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// constructor definition -> telling the compiler how to build a Zombie
Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie() { std::cout << _name << " destroyed" << std::endl; }

void Zombie::announce(void) {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
