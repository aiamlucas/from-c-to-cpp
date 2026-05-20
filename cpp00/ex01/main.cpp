/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:24:47 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/05/20 10:57:03 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <string>

static std::string waitInput(std::string text) {
    std::string input;
    while (input.empty()) {
        std::cout << text;
        std::getline(std::cin, input);
    }
    return input;
}

// Populating Contact attributes via public setters (encapsulation)
static void fillContact(Contact &newContact) {
    newContact.setFirstName(waitInput("First Name: "));
    newContact.setLastName(waitInput("Last Name: "));
    newContact.setNickName(waitInput("Nick Name: "));
    newContact.setPhoneNumber(waitInput("Phone Number: "));
    newContact.setDarkestSecret(waitInput("Darkest Secret: "));
}

int main(void) {
    PhoneBook phonebook; //  PhoneBook instance -> default constructor sets
                         //  _count to 0
    std::string command;

    while (true) {
        std::cout << "Enter command: ";
        if (!std::getline(std::cin, command)) {
            std::cout << "Error: input stream closed (EOF). No further input "
                         "possible."
                      << std::endl;
            break;
        }
        if (command == "ADD") {
            Contact newContact; // Create Contact instance
            fillContact(newContact);
            phonebook.addContact(newContact);
        } else if (command == "SEARCH")
            phonebook.searchContact(); // method for acessing private _contacts
        else if (command == "EXIT")
            break;
    }
    return 0;
}
