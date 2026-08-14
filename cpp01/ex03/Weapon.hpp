/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:59:53 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 21:22:41 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
    std::string _type;

public:
    Weapon(const std::string &type); // constructor, takes the type const ref
    void setType(const std::string &type);
    const std::string &getType() const; // return alias to _type no copy
    // const at the end -> promise: won't modify the object
};

#endif
