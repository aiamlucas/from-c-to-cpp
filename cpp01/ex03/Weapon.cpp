/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:58:03 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 21:25:13 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// initializer list set _type directly, no copy since it's an alias
Weapon::Weapon(const std::string &type) : _type(type) {}
// setter, ovewrites _type with new value
void Weapon::setType(const std::string &type) { _type = type; }
// getter return const reference to _type (no copy, caller can't modify)
const std::string &Weapon::getType() const { return _type; }
