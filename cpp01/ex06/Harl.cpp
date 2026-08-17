/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 10:46:23 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/17 11:28:26 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

void Harl::debug(void) {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my "
                 "7XL-double-cheese-triple-pickle-special-ketchup burger. I "
                 "really do!"
              << std::endl;
}
void Harl::info(void) {
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You "
                 "didn’t put enough bacon in my burger! If you did, I wouldn’t "
                 "be asking for more!"
              << std::endl;
}
void Harl::warning(void) {
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I’ve "
                 "been coming "
                 "for years, whereas you started working here just last month."
              << std::endl;
}
void Harl::error(void) {
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now."
              << std::endl;
}
void Harl::complain(std::string level) {
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    int index = -1;
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            index = i;
            break;
        }
    }
    switch (index) {
    case 0:
        debug();
        __attribute__((fallthrough));
    case 1:
        info();
        __attribute__((fallthrough));
    case 2:
        warning();
        __attribute__((fallthrough));
    case 3:
        error();
        break;
    default:
        std::cout << " [ Probably complaining about insignificant problems ]"
                  << std::endl;
    }
}
