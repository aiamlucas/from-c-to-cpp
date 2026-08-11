/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:23:53 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/07/14 14:27:41 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    if (argc != 2)
        return 1;

    std::string s1 = argv[1];
    std::string s2 = argv[2];

    return 0;
}
