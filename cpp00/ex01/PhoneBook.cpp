/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:53:31 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/05/19 11:01:11 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

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
    std::stringstream stringStream;

    std::cout << std::setw(10) << std::right << "index" << "|" << std::setw(10)
              << std::right << "firstname" << "|" << std::setw(10) << std::right
              << "lastname" << "|" << std::setw(10) << std::right << "nickname"
              << "|" << std::endl;

    for (int i = 0; i < _count; i++) {
        std::string firstName = truncate(_contacts[i].getFirstName(), 10);
        std::string lastName = truncate(_contacts[i].getLastName(), 10);
        std::string nickName = truncate(_contacts[i].getNickName(), 10);
        std::string phoneNumber = truncate(_contacts[i].getPhoneNumber(), 10);
        std::string darkestSecret;
        std::string pickIndex;

        std::cout << std::setw(10) << std::right << i << "|" << std::setw(10)
                  << std::right << firstName << "|" << std::setw(10)
                  << std::right << lastName << "|" << std::setw(10)
                  << std::right << nickName << "|" << std::endl;
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
    if (index < 0 || index >= _count) {
        std::cout << "Invalid index" << std::endl;
        return;
    } else {
        std::cout << "First name    : " << _contacts[index].getFirstName()
                  << std::endl;
        std::cout << "Last name     : " << _contacts[index].getLastName()
                  << std::endl;
        std::cout << "Nickname      : " << _contacts[index].getNickName()
                  << std::endl;
        std::cout << "Phone number  : " << _contacts[index].getPhoneNumber()
                  << std::endl;
        std::cout << "Darkest secret: " << _contacts[index].getDarkestSecret()
                  << std::endl;
    }
}
