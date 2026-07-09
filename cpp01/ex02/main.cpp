/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:41 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/09 19:17:44 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(void) {
    std::string brain = "HI THIS IS BRAIN";
    std::string *stringPTR = &brain;
    std::string &stringREF = brain;

    std::cout << &brain << std::endl;     // adress of brain
    std::cout << stringPTR << std::endl;  // adress stored in stringPTR
    std::cout << &stringREF << std::endl; // adress of what stringREF refers to
    std::cout << brain << std::endl;      // value of brain
    std::cout << *stringPTR << std::endl; // value pointed to by stringPTR
    std::cout << stringREF << std::endl;  // value of stringREF

    return 0;
}
