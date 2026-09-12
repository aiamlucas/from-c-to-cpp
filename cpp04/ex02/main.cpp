/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:07:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/12 19:31:37 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

int main(void) {

    // AAnimal a; // this will break! Cannot instantiate an abstract class

    // subject example -> no leak on simple new/delete
    {
        const AAnimal *j = new Dog();
        const AAnimal *i = new Cat();

        // deleting through AAnimal* (virtual destructor)
        delete j; // should not create a leak
        delete i;
    }
    // half Dog and half Cat
    std::cout << "\n--- array: Cat/Dog half half ---" << std::endl;
    AAnimal *animals[8];
    for (int i = 0; i < 8; i++) {
        if (i < 4) // half of Dogs
            animals[i] = new Dog();
        else // half of Cats
            animals[i] = new Cat();
    }
    for (int i = 0; i < 8; i++)
        delete animals[i]; // delete through AAnimal* (virtual destructor)
    // deep copy
    std::cout << "\n--- deep copy ---" << std::endl;
    {
        Cat juanCarlos;
        juanCarlos.getBrain()->setIdea(0, "I am hungry!");
        Cat cloneCat(juanCarlos); // copy constructor --> allocates a new Brain
        juanCarlos.getBrain()->setIdea(0, "I wanna sleep!");
        std::cout << "juanCarlos: " << juanCarlos.getBrain()->getIdea(0)
                  << std::endl; // "I wanna sleep!"
        std::cout << "cloneCat: " << cloneCat.getBrain()->getIdea(0)
                  << std::endl; // "I am hungry!" // deep copy!
    }

    return 0;
}
