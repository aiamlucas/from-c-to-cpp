/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 09:42:42 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/21 10:32:49 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
    int fixedPoint;
    static constant fractionalBits;

public:
    Fixed(void); // don't know the parameters yet...
    ~Fixed();
    int getRawBits(void) const;
    void setRawBits(int const raw);
}

#endif
