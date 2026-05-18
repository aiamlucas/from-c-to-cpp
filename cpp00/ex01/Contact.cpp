/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:53:39 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/04/10 18:02:59 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::setFirstName(std::string firstName) { _firstName = firstName; }
void Contact::setLastName(std::string lastName) { _lastName = lastName; }
void Contact::setNickName(std::string nickName) { _nickName = nickName; }
void Contact::setPhoneNumber(std::string phoneNumber) {
    _phoneNumber = phoneNumber;
}
void Contact::setDarkestSecret(std::string darkestSecret) {
    _darkestSecret = darkestSecret;
}
std::string Contact::getFirstName() const { return _firstName; }
std::string Contact::getLastName() const { return _lastName; }
std::string Contact::getNickName() const { return _nickName; }
std::string Contact::getPhoneNumber() const { return _phoneNumber; }
std::string Contact::getDarkestSecret() const { return _darkestSecret; }
