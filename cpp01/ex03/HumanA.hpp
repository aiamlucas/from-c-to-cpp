/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:23:30 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/10 16:02:18 by lbueno-m         ###   ########.fr       */
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

public:
    HumanA(std::string name, Weapon &weapon);
    void attack() const;
};

#endif
