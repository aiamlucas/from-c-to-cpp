/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 09:26:27 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/31 13:48:43 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

// Orthodox Canonical Form
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

    float toFloat(void) const; // raw / 256
    int toInt(void) const;     // raw >> 8

    int getRawBits(void) const;
    void setRawBits(int const raw);
};

// An overload of the insertion («) operator
std::ostream &operator<<(std::ostream &stream, const Fixed &fixed);

#endif
