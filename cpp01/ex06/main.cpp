/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 10:51:13 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/17 11:15:46 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    Harl harl;

    if (argc != 2) {
        std::cerr << "Usage: ./harlFilter [DEBUG | INFO | WARNING | ERROR]\n";
        return 1;
    }
    std::string complainAbout = argv[1];
    harl.complain(complainAbout);
    return 0;
}
