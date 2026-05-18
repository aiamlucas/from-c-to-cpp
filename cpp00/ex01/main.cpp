/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:24:47 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/05/18 20:39:17 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <string>

void fillContact(Contact &newContact) {
    std::string input;

    std::cout << "First Name: ";
    std::getline(std::cin, input);
    newContact.setFirstName(input);
    std::cout << "Last Name: ";
    std::getline(std::cin, input);
    newContact.setLastName(input);
    std::cout << "Nick Name: ";
    std::getline(std::cin, input);
    newContact.setNickName(input);
    std::cout << "Phone Number : ";
    std::getline(std::cin, input);
    newContact.setPhoneNumber(input);
}

int main(void) {
    PhoneBook phonebook;
    Contact newContact;
    std::string command;

    while (true) {
        std::cout << "Enter command ";
        if (!std::getline(std::cin, command))
            break; // EOF
        if (command == "ADD") {
            fillContact(newContact);
            phonebook.addContact(newContact);
        } else if (command == "SEARCH")
            phonebook.searchContact();
        else if (command == "EXIT")
            break;
    }
    return 0;
}
