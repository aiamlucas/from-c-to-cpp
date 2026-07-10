/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:49:09 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/10 16:33:56 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon)
    : _name(name), _weapon(weapon) {}

void HumanA::attack() const {
    std::cout << _name << " attacks with their " << _weapon.getType()
              << std::endl;
}
