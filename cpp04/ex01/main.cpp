/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:07:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/15 13:47:02 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main(void) {

    // subject example -> no leak on simple new/delete
    // virtual destructor still works with Brain added
    {
        const Animal *j = new Dog();
        const Animal *i = new Cat();

        // deleting through Animal* (virtual destructor)
        delete j; // ~Dog() -> delete it's brain -> ~Animal() no leak
        delete i;
    }
    // wrong wrong (no virtual destructor)!!!
    std::cout << "\n--- destructor (WrongAnimal - WrongCat)---" << std::endl;
    {
        const WrongAnimal *i = new WrongCat();
        delete i; // ~WrongAnimal() only, ~WrongCat() never fires -> delete
                  // brain never runs
    }
    // half Dog and half Cat
    std::cout << "\n--- array: Cat/Dog half half ---" << std::endl;
    Animal *animals[8];
    for (int i = 0; i < 8; i++) {
        if (i < 4)                  // half of Dogs
            animals[i] = new Dog(); // each one allocate its own Brain
        else                        // half of Cats
            animals[i] = new Cat();
    }
    for (int i = 0; i < 8; i++)
        delete animals[i]; // delete thorugh Animal* (virtual destructor)
    // deep copy -> Brain must not be shared between the original and copy
    std::cout << "\n--- deep copy with copy operator ---" << std::endl;
    {
        Cat juanCarlos;
        juanCarlos.getBrain()->setIdea(0, "I am hungry!");
        Cat cloneCat(juanCarlos); // copy constructor --> allocates a new Brain
                                  // (ideas are copied)
        juanCarlos.getBrain()->setIdea(0, "I wanna sleep!");
        std::cout << "juanCarlos: " << juanCarlos.getBrain()->getIdea(0)
                  << std::endl; // "I wanna sleep!"
        std::cout << "cloneCat: " << cloneCat.getBrain()->getIdea(0)
                  << std::endl; // "I am hungry!" // deep copy!
    }
    std::cout << "\n--- deep copy with assignment (=) ---" << std::endl;
    {
        Cat juanCarlos;
        juanCarlos.getBrain()->setIdea(0, "I am hungry!");
        Cat cloneCat;          // default constructed first (Brain allocated)
        cloneCat = juanCarlos; // assignment operator (deep copy)
        juanCarlos.getBrain()->setIdea(0, "I wanna sleep!");
        std::cout << "juanCarlos: " << juanCarlos.getBrain()->getIdea(0)
                  << std::endl; // "I wanna sleep!"
        std::cout << "cloneCat: " << cloneCat.getBrain()->getIdea(0)
                  << std::endl; // "I am hungry!" // deep copy!
    }

    return 0;
}
