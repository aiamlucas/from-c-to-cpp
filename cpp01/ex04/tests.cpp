/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 18:31:23 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/20 11:40:05 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replacer.hpp"
#include <fstream>
#include <iostream>

// write the content in a new file
static void createFile(const std::string &name, const std::string &content) {
    std::ofstream file(name.c_str());
    file << content;
}

// reads the file line by line and print it
static void printFile(const std::string &name) {
    std::ifstream file(name.c_str());
    std::string line;
    while (std::getline(file, line))
        std::cout << " " << line << "\n";
}

int main(void) {
    std::cout << "--- test 1: single occurrence ---\n";
    std::cout << "input:  \"space is the place\" s1 = space, s2 = earth\n";
    createFile("t1", "space is the place\n");
    Replacer("t1", "space", "earth").run();
    std::cout << "output: ";
    printFile("t1.replace");

    std::cout << "\n--- test 2: multiple occurrences same line ---\n";
    std::cout << "input:  \"space is space\" s1 = space, s2 = earth\n";
    createFile("t2", "space is space\n");
    Replacer("t2", "space", "earth").run();
    std::cout << "output: ";
    printFile("t2.replace");

    std::cout << "\n--- test 3: multiline ---\n";
    createFile("t3",
               "space is the place\nthe place is space\nspace is space\n");
    std::cout << "input:\n";
    printFile("t3");
    Replacer("t3", "space", "earth").run();
    std::cout << "output:\n";
    printFile("t3.replace");

    std::cout << "\n--- test 4: s1 not in file ---\n";
    std::cout << "input:  \"space is the place\" s1 = chair, s2 = repair\n";
    createFile("t4", "space is the place\n");
    Replacer("t4", "chair", "repair").run();
    std::cout << "output: ";
    printFile("t4.replace");

    std::cout << "\n--- test 5: s2 empty (deletes s1) ---\n";
    std::cout << "input:  \"space is the place\" s1 = \"space \", s2 = \"\"\n";
    createFile("t5", "space is the place\n");
    Replacer("t5", "space ", "").run();
    std::cout << "output: ";
    printFile("t5.replace");

    std::cout << "\n--- test 6: file not found ---\n";
    std::cout << "input:  doesnotexist.txt s1 = space, s2 = earth\n";
    std::cout << "output: ";
    Replacer("doesnotexist.txt", "space", "earth").run();
    return 0;
}
