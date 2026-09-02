/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:03:17 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/02 19:03:37 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>
#include <string>

ClapTrap::ClapTrap(void)
    : _name(""), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap " << _name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
    : _name(other._name), _hitPoints(other._hitPoints),
      _energyPoints(other._energyPoints), _attackDamage(other._attackDamage) {
    std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    std::cout << "ClapTrap copy assignment operator called" << std::endl;
    if (this == &other)
        return *this;
    _name = other._name;
    _hitPoints = other._hitPoints;
    _energyPoints = other._energyPoints;
    _attackDamage = other._attackDamage;
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << _name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &target) {
    if (_energyPoints && _hitPoints) {
        _energyPoints--;
        std::cout << "ClapTrap " << _name << " attacks " << target
                  << ", causing " << _attackDamage << " points of damage!"
                  << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (_energyPoints && _hitPoints) {
        _energyPoints--;
        _hitPoints += amount;
        std::cout << "ClapTrap " << _name << " repairs itself for " << amount
                  << " hit points!" << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (_energyPoints && _hitPoints) {
        if (amount >= _hitPoints)
            _hitPoints = 0;
        else
            _hitPoints -= amount;
        std::cout << "ClapTrap " << _name << " takes " << amount
                  << " points of damage!" << std::endl;
    }
}
