/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:34:21 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/19 15:44:29 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

// _weapon starts at NULL
HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {}

// store the address of the referenced Weapon into the _weapon pointer
// [Weapon &weapon] -> alias
// [_weapon = &weapon] ->   takes its addres, assing it into the pointer
void HumanB::setWeapon(Weapon &weapon) { _weapon = &weapon; }

// check if _weapon is NULL, because dereferencing a NULL pointer is undefined
// behavior
void HumanB::attack() const {
    if (_weapon)
        std::cout << _name << " attacks with their " << _weapon->getType()
                  << std::endl;
}
