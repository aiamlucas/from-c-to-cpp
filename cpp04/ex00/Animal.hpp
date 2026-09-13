/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:40:31 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/13 20:57:51 by lbueno-m         ###   ########.fr       */
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
    virtual ~Animal(); // virtual -> destructor call resolved at runtime via
                       // vtable

    std::string getType(void) const;
    // virtual -> call resolved at runtime via vtable
    // vtable lookup finds the true function
    virtual void makeSound(void) const;
};

#endif
