/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:25 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 21:01:33 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, const std::string &name) {
    Zombie *horde = new Zombie[N]; // single allocation -> N zombies on the heap
    for (int i = 0; i < N; i++)
        horde[i].setName(name);
    return horde; // returning a pointer to the first element
}
