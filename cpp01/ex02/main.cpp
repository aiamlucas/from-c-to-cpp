/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 19:17:41 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/14 21:10:05 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(void) {
    std::string brain = "HI THIS IS BRAIN";
    std::string *stringPTR = &brain;
    std::string &stringREF = brain;

    std::cout << &brain << std::endl;     // address of brain
    std::cout << stringPTR << std::endl;  // address stored in stringPTR
    std::cout << &stringREF << std::endl; // address of what stringREF refers to
    std::cout << brain << std::endl;      // value of brain
    std::cout << *stringPTR << std::endl; // value pointed to by stringPTR
    std::cout << stringREF << std::endl;  // value of stringREF

    return 0;
}
