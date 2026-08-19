/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:23:30 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/19 13:26:08 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA {
private:
    std::string _name;
    Weapon &_weapon; // reference -> always armed, cannot be NULL
                     // reference cannot change to another weapon

public:
    // weapon is in the constructor because HumanA is always armed
    HumanA(std::string name, Weapon &weapon);
    void attack() const; // const -> promise: only reads
};

#endif
