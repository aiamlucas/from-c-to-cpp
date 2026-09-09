/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 18:46:51 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/09 18:47:12 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include <iostream>
#include <string>

AAnimal::AAnimal(void) : _type("") {
    std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : _type(other._type) {
    std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other) {
    std::cout << "AAnimal copy assignment operator called" << std::endl;
    if (this == &other)
        return *this;
    _type = other._type;
    return *this;
}

AAnimal::~AAnimal() { std::cout << "AAnimal destructor called" << std::endl; }

std::string AAnimal::getType(void) const { return _type; }
