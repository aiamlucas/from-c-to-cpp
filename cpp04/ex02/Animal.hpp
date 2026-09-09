/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 12:03:01 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/09 12:06:48 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal {
protected:
    std::string _type;

public:
    Animal(void);
    Animal(const Animal &other);
    Animal &operator=(const Animal &other);
    virtual ~Animal();

    std::string getType(void) const;
    // virtual void makeSound(void) const; --> virtual -> it's instatiable
    // (Animal a -> still compiles)
    virtual void makeSound(void)
        const = 0; // pure virtual, abstract class (Animal a -> dons't compile)
};

#endif
