/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:58:03 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/19 14:42:06 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// initializer list set _type  from the constructor's argument
Weapon::Weapon(std::string type) : _type(type) {}

void Weapon::setType(std::string type) { _type = type; }
// subject: A getType() member function that returns a constant reference to
//  const at the end -> getType() itself never modifies the Weapon object
const std::string &Weapon::getType() const { return _type; }
