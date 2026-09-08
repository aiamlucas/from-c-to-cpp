/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:07:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/07 20:00:42 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main(void) {

    std::cout << " \n--- subject main ---" << std::endl;
    {
        // declared as Animal*, but each points at different (derived) types
        const Animal *meta = new Animal();
        const Animal *j = new Dog();
        const Animal *i = new Cat();
        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;
        i->makeSound();    // Cat's sound
        j->makeSound();    // Dog's sound
        meta->makeSound(); // Animal sound
        delete meta;
        delete j; // ~Dog() then ~Animal()
        delete i; // ~Cat() then ~Animal()
    }

    std::cout << " \n--- subject main Wrong Class ---" << std::endl;
    {
        const WrongAnimal *meta = new WrongAnimal();
        const Animal *j = new Dog();
        const WrongAnimal *i = new WrongCat();
        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;
        i->makeSound(); // Wrong -> print WrongAnimal's sound (and not WrongCat
                        // sound) - makeSound() is not virtual!
        j->makeSound();
        meta->makeSound();
        delete meta;
        delete j; // ~Dog() then ~Animal()
        delete i; // only ~WrongAnimal() runs -- ~WrongCat() never fires (not
                  // virtual)
    }

    std::cout << " \n--- extra tests ---" << std::endl;

    std::cout
        << "\n --- construction Animal=capivara, Dog=laica, Cat=oblomov ---"
        << std::endl;
    Animal capivara;
    Dog laica;
    Cat oblomov;

    std::cout << "\n --- makesound() test ---" << std::endl;
    capivara.makeSound(); //  type is know at compile time, virtual is not
                          //  needed here
    laica.makeSound();
    oblomov.makeSound();

    std::cout << "\n--- iterating in an array of different animals "
                 "animals[capivara, laica, oblomov] ---"
              << std::endl;

    Animal *animals[3];
    animals[0] = new Animal();
    animals[1] = new Dog();
    animals[2] = new Cat();

    for (int i = 0; i < 3;
         i++) // the declared type is Animal* for all 3, but
              // the real type differs (virtual is here necessary)
        animals[i]->makeSound(); // should have different sound

    std::cout << "\n--- deleting Animals* ---" << std::endl;
    for (int i = 0; i < 3; i++)
        delete animals[i]; // virtual destructor!

    std::cout << "\n--- destructor (from what is remain in the stack) ---"
              << std::endl;
    return 0;
}
