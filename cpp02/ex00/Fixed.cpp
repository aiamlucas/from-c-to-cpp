/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 09:42:42 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/31 13:10:27 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

// initializer list
Fixed::Fixed(void) : _fixedPoint(0) {
    std::cout << "Default constructor called" << std::endl;
}

// copy constructor - builds a new Fixed copying other's raw value
Fixed::Fixed(const Fixed &other) : _fixedPoint(other._fixedPoint) {
    std::cout << "Copy constructor called" << std::endl;
}

// copy assign operator - overwrite an existing Fixed with other's value
Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called" << std::endl;
    // this = current object's address
    // &other = address of the object passed in
    if (this == &other) // guard against self-assignment (a = a);
        return *this;
    _fixedPoint = other._fixedPoint;
    return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

// return the raw store value
int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return _fixedPoint;
}
// overwrite the raw stored value
void Fixed::setRawBits(int const raw) { _fixedPoint = raw; }
