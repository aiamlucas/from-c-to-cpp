/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:10 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/18 21:58:04 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie();
    ~Zombie();
    // alias to the caller's string, no copy made
    void setName(const std::string &name);
    void announce(void);
};

// free function (not a class member) - create an array of zombies
Zombie *zombieHorde(int N, const std::string &name);

#endif
