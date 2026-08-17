/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 10:15:13 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/17 10:40:24 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(void) {
    Harl harl;

    std::cout << " --- Debug complain ---" << std::endl;
    harl.complain("DEBUG");
    std::cout << "\n --- Info complain ---" << std::endl;
    harl.complain("INFO");
    std::cout << "\n --- Warning complain ---" << std::endl;
    harl.complain("WARNING");
    std::cout << "\n --- Error complain ---" << std::endl;
    harl.complain("ERROR");

    return 0;
}
