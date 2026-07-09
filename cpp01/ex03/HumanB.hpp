/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:34:25 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/08 19:48:14 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB {
private:
    std::string _name;
    Weapon *_weapon; // it can be NULL (in case no weapon)

public:
    HumanB(std::string name);
    void attack() const; // const at the end here means a promise --> this
                         // method only reads, never writes
    void setWeapon(Weapon &weapon);
};

#endif
