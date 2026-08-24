/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 10:50:25 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/24 12:27:17 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int main(void) {

    Fixed a;               // default constructor
    Fixed const b(10);     // int constructor
    Fixed const c(42.42f); // float constructor
    Fixed const d(b);      // copy constructor

    a = Fixed(
        1234.4321f); // 1) float constructor builds a temporary Fixed
                     // 2) copy assignment: assigns the temporary value into a
                     // 3) the temporary Fixed is destroyed (Destructor called)

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return 0;
}
