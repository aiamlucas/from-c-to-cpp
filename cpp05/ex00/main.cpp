/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 09:59:16 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/25 00:14:19 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(void) {
    std::cout << "juanCarlos: " << juanCarlos.getBrain()->getIdea(0)
              << std::endl; // "I wanna sleep!"
    std::cout << "cloneCat: " << cloneCat.getBrain()->getIdea(0)
              << std::endl; // "I am hungry!" // deep copy!

    return 0;
}
