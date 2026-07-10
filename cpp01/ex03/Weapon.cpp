/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:58:03 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/10 16:02:00 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// constructor -- initializes the _type with the value passed in
Weapon::Weapon(std::string type) : _type(type) {}
// setter, ovewrites _type with new value
void Weapon::setType(std::string type) { _type = type; }
// getter return const reference to _type (no copy, caller can't modify)
const std::string &Weapon::getType() const { return _type; }
