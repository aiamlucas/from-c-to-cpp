/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:23:53 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/16 18:32:33 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replacer.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./sedpp <filename> <s1> <s2>\n";
        return 1;
    }
    std::string fileName = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    if (s1.empty()) {
        std::cerr << "s1 cannot be empty\n";
        return 1;
    }
    Replacer sedpp(fileName, s1, s2);
    sedpp.run();
    return 0;
}
