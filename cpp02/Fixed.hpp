/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 09:42:48 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/23 22:43:55 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

// Orthodox Canonical Form

class Fixed {
private:
    int _fixedPoint;
    static const int fractionalBits = 8;

public:
    Fixed(void);                          // 1) constructor
    Fixed(const Fixed &other);            // 2) copy constructor
    Fixed &operator=(const Fixed &other); // 3) copy assignment operator
    ~Fixed();                             // 4) destructor

    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif
