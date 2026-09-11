/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 17:48:58 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/11 09:21:45 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>
#include <string>

Dog::Dog(void) {
    _type = "Dog";
    brain = new Brain();
    std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
    brain = new Brain(*other.brain); // allocating a new brain for a deep-copy
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this == &other)
        return *this;
    Animal::operator=(other);
    *brain = *other.brain;
    return *this;
}

Dog::~Dog() {
    delete brain;
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const { std::cout << "au au auu" << std::endl; }

Brain *Dog::getBrain(void) const { return brain; }
