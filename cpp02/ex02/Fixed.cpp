/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:21:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/28 00:07:04 by lbueno-m         ###   ########.fr       */
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

std::ostream &operator<<(std::ostream &stream, const Fixed &fix) {
    stream << fix.toFloat();
    return stream;
}

bool Fixed::operator>(const Fixed &other) const {
    return _fixedPoint > other._fixedPoint;
}
bool Fixed::operator<(const Fixed &other) const {
    return _fixedPoint < other._fixedPoint;
}
bool Fixed::operator>=(const Fixed &other) const {
    return _fixedPoint >= other._fixedPoint;
}
bool Fixed::operator<=(const Fixed &other) const {
    return _fixedPoint <= other._fixedPoint;
}
bool Fixed::operator==(const Fixed &other) const {
    return _fixedPoint == other._fixedPoint;
}
bool Fixed::operator!=(const Fixed &other) const {
    return _fixedPoint != other._fixedPoint;
}

Fixed Fixed::operator+(const Fixed &other) const {
    Fixed result;
    result.setRawBits(_fixedPoint + other._fixedPoint);
    return result;
}

Fixed Fixed::operator-(const Fixed &other) const {
    Fixed result;
    result.setRawBits(_fixedPoint - other._fixedPoint);
    return result;
}
Fixed Fixed::operator*(const Fixed &other) const {
    return Fixed(this->toFloat() * other.toFloat());
}
Fixed Fixed::operator/(const Fixed &other) const {
    return Fixed(this->toFloat() / other.toFloat());
}

Fixed &Fixed::operator++() {
    _fixedPoint += 1;
    return *this;
}
Fixed Fixed::operator++(int) {
    Fixed old = *this;
    _fixedPoint += 1;
    return old;
}
Fixed &Fixed::operator--() {
    _fixedPoint -= 1;
    return *this;
}
Fixed Fixed::operator--(int) {
    Fixed old = *this;
    _fixedPoint -= 1;
    return old;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    if (a < b)
        return a;
    return b;
}
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    if (a < b)
        return a;
    return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    if (a > b)
        return a;
    return b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    if (a > b)
        return a;
    return b;
}
