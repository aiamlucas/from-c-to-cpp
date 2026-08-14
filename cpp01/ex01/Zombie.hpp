/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 19:28:40 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie();  // default constructor - new Zombie[N]
    ~Zombie(); // destructor
    void setName(
        const std::string &name); // alias to the caller's string, no copy made
    void announce(void);
};

// free function (not a class member) - create an array of zombies
Zombie *zombieHorde(int N, const std::string &name);

#endif
