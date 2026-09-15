/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 13:25:02 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/15 13:26:37 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "Brain.hpp"
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
private:
    Brain *brain;

public:
    WrongCat(void);
    WrongCat(const WrongCat &other);
    WrongCat &operator=(const WrongCat &other);
    ~WrongCat();

    void makeSound(void) const;
    Brain *getBrain(void) const;
};

#endif
