/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 09:42:42 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/23 22:44:23 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

// initializer list
Fixed::Fixed(void) : _fixedPoint(0) {
    std::cout << "Default constructor called" << std::endl;
}

// copy constructor
Fixed::Fixed(const Fixed &other) : _fixedPoint(other._fixedPoint) {
    std::cout << "Copy constructor called" << std::endl;
}

// copy assign operator
Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this == &other)
        return *this;
    _fixedPoint = other._fixedPoint;
    return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return _fixedPoint;
}
void Fixed::setRawBits(int const raw) { _fixedPoint = raw; }
