/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 22:21:51 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/28 00:03:16 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

// Orthodox Canonical Form: default constructor, copy constructor
// copy assignment operator and destructor

class Fixed {
private:
    int _fixedPoint;                     // storing the raw fixed-point
    static const int fractionalBits = 8; // shared by all objects, never change

public:
    Fixed(void);                          // 1) default constructor
    Fixed(const int num);                 // constructor overloading (for int)
    Fixed(const float num);               // constructor overloading (for float)
    Fixed(const Fixed &other);            // 2) copy constructor
    Fixed &operator=(const Fixed &other); // 3) copy assignment operator
    ~Fixed();                             // 4) destructor

    float toFloat(void) const;
    int toInt(void) const;

    int getRawBits(void) const;
    void setRawBits(int const raw);

    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;

    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

    Fixed &operator++();   // pre-increment ++a;
    Fixed operator++(int); // pos-increment a++;
    Fixed &operator--();   //  pre-decrement --a;
    Fixed operator--(int); // pre-decrement a--;

    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);
};

// An overload of the insertion («) operator
std::ostream &operator<<(std::ostream &stream, const Fixed &fix);

#endif
