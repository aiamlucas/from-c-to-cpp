/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:07:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/10 18:05:20 by lbueno-m         ###   ########.fr       */
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
        std::cout << j->getType() << " " << std::endl; // "Dog"
        std::cout << i->getType() << " " << std::endl; // "Cat"
        i->makeSound();    // "miauuu" -> virtual -> runtime lookup
        j->makeSound();    // "au au" -> virtual -> runtime lookup
        meta->makeSound(); // "brrrr br" -> virtual -> runtime lookup
        delete meta;       // ~Animal()
        delete j;          // ~Dog() then ~Animal()
        delete i;          // ~Cat() then ~Animal()
    }

    // WrongAnimal -> no virtual:
    std::cout << " \n--- Wrong Class ---" << std::endl;
    {
        // direct call: declared type -> WrongCat (static binding, compile time)
        // compiler sees WrongCat -> WrongCat::makeSound() -> correct sound
        WrongCat mafalda;
        mafalda.makeSound(); // "WrongCat -> miauuu "

        // through a base pointer:  declared type -> WrongAnimal
        // no virtual -> no vtable, no runtime lookup (just static binding)
        // compiler locks in WrongAnimal::makeSound() at compile time
        WrongCat oblomov;
        const WrongAnimal *ptr = &oblomov;
        ptr->makeSound(); // "WrongAnimal -> brrrr..."
    }

    std::cout << " \n--- subject main Wrong Class ---" << std::endl;
    {
        const WrongAnimal *meta = new WrongAnimal();
        const Animal *j = new Dog();
        const WrongAnimal *i = new WrongCat();
        std::cout << j->getType() << " " << std::endl; // "Dog"
        std::cout << i->getType() << " " << std::endl; //  "WrongCat"
        i->makeSound(); // "WrongAnimal: brrr" -> no virtual, declared type wins
                        // (was Cat sound before)

        j->makeSound();    // "au au au" -> Animal -> virtual -> runtime lookup
                           // (same as before)
        meta->makeSound(); // "WrongAnimal: brrr" -> no virtual, direct call
                           // (same as before)
        delete meta;       // ~WrongAnimal()
        delete j;          // ~Dog() then ~Animal()
        delete i; // only ~WrongAnimal()  -> no virtual ~WrongCat never fires
    }

    // array of Animal* with mixed types
    std::cout << "\n--- iterating in an array of different animals "
                 "animals[capivara, laica, oblomov] ---"
              << std::endl;

    Animal *animals[3];
    animals[0] = new Animal();
    animals[1] = new Dog();
    animals[2] = new Cat();

    // declared type -> Animal* - virtual select the correct sound
    for (int i = 0; i < 3; i++)
        animals[i]
            ->makeSound(); // virtual -> runtime lookup -> Animal, Dog, Cat

    std::cout << "\n--- deleting Animals* ---" << std::endl;
    for (int i = 0; i < 3; i++)
        delete animals[i]; // virtual destructor -> runtime lookup

    std::cout << "\n--- destructor (from what is remain in the stack) ---"
              << std::endl;
    return 0;
}
