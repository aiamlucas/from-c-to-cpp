/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replacer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 17:29:18 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/20 11:07:47 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replacer.hpp"
#include <fstream>
#include <iostream>

// initializer list
Replacer::Replacer(const std::string &fileName, const std::string &s1,
                   const std::string &s2)
    : _fileName(fileName), _s1(s1), _s2(s2) {}

Replacer::~Replacer() {}

// find(_s1, pos) returns the index of the next match, npos if none is left
// copy and move to next match
// nos
std::string Replacer::_replaceLine(const std::string &line) {
    std::string result;
    size_t pos = 0;
    size_t found;

    while ((found = line.find(_s1, pos)) != std::string::npos) {
        result += line.substr(pos, found - pos); // text before the match
        result += _s2;                           // swap s1 with s2
        pos = found + _s1.length();              // update position
    }
    result += line.substr(pos);
    return result;
}

// opens the input and output files, reads line by line
// write replaced line to the output file
void Replacer::run() {
    std::string outName = _fileName + ".replace";

    // In C++98, ifstream/ofstream constructors expect a const char*
    // c_str() converts std::string into a const char*
    std::ifstream inFile(_fileName.c_str());
    if (!inFile.is_open()) {
        std::cerr << "Could not open file\n";
        return;
    }
    std::ofstream outFile(outName.c_str());
    if (!outFile.is_open()) {
        std::cerr << "Could not create output file\n";
        return;
    }
    std::string line;
    while (std::getline(inFile, line))
        outFile << _replaceLine(line) << "\n";
    inFile.close();
    outFile.close();
}
