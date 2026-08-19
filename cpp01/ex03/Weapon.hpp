/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:59:53 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/19 14:39:54 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
    std::string _type;

public:
    Weapon(std::string type);           // constructor
    void setType(std::string type);     // setter to overwrite _type
    const std::string &getType() const; // return alias to _type no copy
    // const at the end -> promise: won't modify the object
};

#endif
