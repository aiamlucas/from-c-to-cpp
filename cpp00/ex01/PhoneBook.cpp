/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:53:31 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/05/19 00:43:22 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <strings.h>

std::string truncate(const std::string &str, int width) {
    if ((int)str.length() > width)
        return str.substr(0, width - 1) + ".";
    return str;
}

PhoneBook::PhoneBook() : _count(0) {}

void PhoneBook::addContact(Contact contact) {
    if (_count < 8) {
        _contacts[_count] = contact;
        _count++;
    } else {
        for (int i = 0; i < 7; i++)
            _contacts[i] = _contacts[i + 1];
        _contacts[7] = contact;
    }
}

void PhoneBook::searchContact() {
    std::string index;

    std::cout << std::setw(10) << std::right << "index" << "|" << std::setw(10)
              << std::right << "firstame" << "|" << std::setw(10) << std::right
              << "lastname" << "|" << std::setw(10) << std::right << "nickname"
              << "|" << std::setw(10) << std::right << "phonenumber"
              << std::endl;

    for (int i = 0; i < _count; i++) {
        std::intStream intStream;
        std::string firstName;
        std::string lastName;
        std::string nickName;
        std::string phoneNumber;
        std::string darkestSecret;
        std::string pickIndex;

        firstName = _contacts[i].getFirstName();
        firstName = truncate(firstName, 10);
        lastName = _contacts[i].getLastName();
        lastName = truncate(lastName, 10);
        nickName = _contacts[i].getNickName();
        nickName = truncate(nickName, 10);
        phoneNumber = _contacts[i].getPhoneNumber();
        phoneNumber = truncate(phoneNumber, 10);

        std::string index = stringStream.str();
        std::cout << std::setw(10) << std::right << i << "|" << std::setw(10)
                  << std::right << firstName << "|" << std::setw(10)
                  << std::right << lastName << "|" << std::setw(10)
                  << std::right << nickName << "|" << std::setw(10)
                  << std::right << phoneNumber << "|" << std::endl;
    }
    std::cout << "Enter index:";
    std::string input;
    std::getline(std::cin, input);

    stringStream << input;
    int index;
    if (!(stringStream >> index)) {
        std::cout << "Invalid input" << std::endl;
        return;
    }
    if (index > 0 || index >= _count) {
        std::cout << "Invalid index" << std::endl;
        return;
    } else {
        std::cout << std::setw(10) << std::right << i << "|" << std::setw(10)
                  << std::right << firstName << "|" << std::setw(10)
                  << std::right << lastName << "|" << std::setw(10)
                  << std::right << nickName << "|" << std::setw(10)
                  << std::right << phoneNumber << "|" << std::setw(10)
                  << std::right << darkest secret << "|" << std::endl;
    }
}
