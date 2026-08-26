/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 10:34:19 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/26 16:13:31 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>

// initializer list
Fixed::Fixed(void) : _fixedPoint(0) {
    std::cout << "Default constructor called" << std::endl;
}
Fixed::Fixed(const int num) : _fixedPoint(num << fractionalBits) {
    std::cout << "Int constructor called" << std::endl;
}
Fixed::Fixed(const float num)
    : _fixedPoint(roundf(num * (1 << fractionalBits))) {
    std::cout << "Float constructor called" << std::endl;
}

// copy constructor - builds a new Fixed copying other's raw value
Fixed::Fixed(const Fixed &other) : _fixedPoint(other._fixedPoint) {
    std::cout << "Copy constructor called" << std::endl;
}

// copy assign operator - overwrite an existing Fixed with other's value
Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called" << std::endl;
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

float Fixed::toFloat(void) const {
    return static_cast<float>(_fixedPoint) / (1 << fractionalBits);
}
int Fixed::toInt(void) const { return _fixedPoint >> fractionalBits; }

// example: stream=std::cout, fix=b (a Fixed holding a raw value of 2560)
//          "b is " << b  ->  fix = b  ->  fix.toFloat() = 2560/256 = 10.0
//          prints: b is 10
std::ostream &operator<<(std::ostream &stream, const Fixed &fix) {
    stream << fix.toFloat();
    return stream;
}
