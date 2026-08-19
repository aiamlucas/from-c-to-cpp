/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:34:25 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/19 13:27:10 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB {
private:
    std::string _name;
    // here is a normal pointer
    Weapon *_weapon; // it can be NULL (in case no weapon)
                     // it can be assigned later via setWeapon()

public:
    // no weapon in the constructor -> HumanB starts unarmed
    HumanB(std::string name);
    void attack() const; // const -> only reads never writes

    void setWeapon(Weapon &weapon); // assigns a weapon later
};

#endif
