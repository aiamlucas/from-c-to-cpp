/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 18:46:20 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/15 14:11:52 by lbueno-m         ###   ########.fr       */
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
    // pure virtual function
    // compiler refuses to construct an object of this time (AAnimal a;)
    virtual void makeSound(void)
        const = 0; // pure virtual, abstract class (AAnimal a -> dons't compile)
};

#endif
