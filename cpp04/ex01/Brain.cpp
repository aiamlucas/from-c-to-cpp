/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 08:50:03 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/09/08 19:30:14 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>
#include <string>

Brain::Brain(void) {
    std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain &other) {
    for (int i = 0; i < 100; i++)
        _ideas[i] = other._ideas[i];
    std::cout << "Brain copy constructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &other) {
    std::cout << "Brain copy assignment operator called" << std::endl;
    if (this == &other)
        return *this;
    for (int i = 0; i < 100; i++)
        _ideas[i] = other._ideas[i];
    return *this;
}

Brain::~Brain() { std::cout << "Brain destructor called" << std::endl; }

void Brain::setIdea(int index, const std::string &idea) {
    if (index >= 0 && index < 100)
        _ideas[index] = idea;
}
const std::string &Brain::getIdea(int index) const {
    if (index >= 0 && index < 100)
        return _ideas[index];
    return _ideas[0];
}
