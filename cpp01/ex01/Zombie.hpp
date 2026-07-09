/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/09 19:17:12 by lbueno-m         ###   ########.fr       */
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
    Zombie();                       // default constructor - new Zombie[N]
    Zombie(std::string name);       // parameterized
    ~Zombie();                      // destructor
    void setName(std::string name); // setter for the Zombies names
    void announce(void);
};

Zombie *zombieHorde(int N, std::string name);

#endif
