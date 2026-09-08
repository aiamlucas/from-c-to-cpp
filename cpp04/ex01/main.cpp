/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:07:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/08 19:53:36 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

int main(void) {

    {
        const Animal *j = new Dog();
        const Animal *i = new Cat();

        delete j; // should not create a leak
        delete i;
    }
    // half Dog and half Cat
    std::cout << "\n--- array: Cat/Dog half half ---" << std::endl;
    Animal *animals[8];
    for (int i = 0; i < 8; i++) {
        if (i < 8)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
    for (int i = 0; i < 8; i++)
        delete animals[i];
    // deep copy
    std::cout << "\n--- deep copy ---" << std::endl;
    {
        Cat juanCarlos;
        juanCarlos.getBrain()->setIdea(0, "I am hungry!");
        Cat cloneCat(juanCarlos);
        juanCarlos.getBrain()->setIdea(0, "I wanna sleep!");
        std::cout << "juanCarlos: " << juanCarlos.getBrain()->getIdea(0)
                  << std::endl; // "I wanna sleep!"
        std::cout << "cloneCat: " << cloneCat.getBrain()->getIdea(0)
                  << std::endl; // "I am hungry!" // deep copy!
    }

    return 0;
}
