/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:34:21 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/19 13:27:22 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

// _weapon starts at NULL
HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {}
void HumanB::setWeapon(Weapon &weapon) { _weapon = &weapon; }

// must check _weapon before using it (it can be NULL)
// otherwise dereferencing a NULL pointer is undefined behavior
void HumanB::attack() const {
    if (_weapon)
        std::cout << _name << " attacks with their " << _weapon->getType()
                  << std::endl;
}
