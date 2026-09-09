/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 18:46:20 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/09 18:46:41 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>

class AAnimal {
protected:
    std::string _type;

public:
    AAnimal(void);
    AAnimal(const AAnimal &other);
    AAnimal &operator=(const AAnimal &other);
    virtual ~AAnimal();

    std::string getType(void) const;
    // virtual void makeSound(void) const; --> virtual -> it's instatiable
    // (Animal a -> still compiles)
    virtual void makeSound(void)
        const = 0; // pure virtual, abstract class (AAnimal a -> dons't compile)
};

#endif
