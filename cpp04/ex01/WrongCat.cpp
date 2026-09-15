/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 13:26:00 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/15 13:27:32 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"
#include <iostream>
#include <string>

WrongCat::WrongCat(void) {
    _type = "WrongCat";
    brain = new Brain(); // own brain
    std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other) {
    brain = new Brain(*other.brain);
    std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other) {
    std::cout << "WrongCat copy assignment operator called" << std::endl;
    if (this == &other)
        return *this;
    WrongAnimal::operator=(other);
    *brain = *other.brain; // own brain (deep copy)
    return *this;
}

WrongCat::~WrongCat() {
    delete brain;
    std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound() const { std::cout << "miauuu" << std::endl; }

Brain *WrongCat::getBrain(void) const { return brain; }
