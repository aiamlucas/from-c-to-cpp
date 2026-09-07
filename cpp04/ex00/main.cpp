/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:07:11 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/07 18:31:11 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

int main(void) {
    std::cout << " \n--- copy constructor and copy assignment ---" << std::endl;
    {
        Dog dog;
        Dog copyDog(dog); // copy constructor
        Cat cat;
        Cat copyCat;
        copyCat = cat; // copy assignment
    } // all four destructors should fire here
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
        delete animals[i];

    std::cout << "\n--- destructor (from what is remain in the stack) ---"
              << std::endl;
    return 0;
}
