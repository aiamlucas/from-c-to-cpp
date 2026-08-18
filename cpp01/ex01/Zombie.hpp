/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/18 23:11:27 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie(); // default constructor
    ~Zombie();
    void setName(const std::string &name);
    void announce(void);
};

// Creates an array of objects (Zombies) -- single allocation
Zombie *zombieHorde(int N, const std::string &name);

#endif
