/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:21:51 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/31 13:29:50 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

// Orthodox Canonical Form
class Fixed {
private:
    int _fixedPoint;                     // storing the raw fixed-point
    static const int fractionalBits = 8; // shared by all objects

public:
    Fixed(void);                          // default constructor
    Fixed(const int num);                 // int constructor
    Fixed(const float num);               // float constructor
    Fixed(const Fixed &other);            // copy constructor
    Fixed &operator=(const Fixed &other); // copy assignment operator
    ~Fixed();                             // destructor

    float toFloat(void) const; // raw / 256
    int toInt(void) const;     // raw >> 8

    int getRawBits(void) const;
    void setRawBits(int const raw);

    // comparison (made with raw bits)
    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;

    // + and - implemented with raw bits // * and / converts to float first
    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

    Fixed &operator++();   // ++a - modify then return *this
    Fixed operator++(int); // a++ - save copy, modify, return
    Fixed &operator--();   // --a - modify ten return *this
    Fixed operator--(int); // a-- - save copy, modify, return

    // min max takes two independent objects and compate then (no owner)
    // the function belongs to the class and not to any instance
    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);
};

// An overload of the insertion («) operator
std::ostream &operator<<(std::ostream &stream, const Fixed &fix);

#endif
