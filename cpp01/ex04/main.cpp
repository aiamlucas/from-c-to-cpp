/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:23:53 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/15 16:15:37 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Create a program that takes three parameters in the following order: a
// filename and two strings, s1 and s2. It must open the file <filename> and
// copy its content into a new file <filename>.replace, replacing every
// occurrence of s1 with s2. Using C file manipulation functions is forbidden
// and will be considered cheating. All the member functions of the class
// std::string are allowed, except replace. Use them wisely! Of course, handle
// unexpected inputs and errors. You must create and turn in your own tests to
// ensure that your program works as expected.

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    if (argc != 4)
        return 1;

    std::string fileName = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    std::string outName = fileName + ".replace";

    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        size_t pos = 0;
        line.find(s1, pos);
    }

    return 0;
}
