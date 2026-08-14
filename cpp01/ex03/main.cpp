/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 15:45:41 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 21:38:50 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"

int main() {
    // HumanA test
    {
        Weapon club("crude spiked club");
        // club is passed by reference
        // bob hold an alias to the original club
        // when club changes, bob see the change too
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club"); // modify the original
        bob.attack();
    }
    // HumamB test
    {
        Weapon club("crude spiked club");
        // Jim start with no weapon
        HumanB jim("Jim");
        // setWeapon takes club by reference, stores its address in _weapon
        // pointer
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club"); // modify the original
        jim.attack();                            // jim see the change too
    }
    return 0;
}
