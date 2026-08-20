/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replacer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 17:20:01 by lbueno-m          #+#    #+#             */
/*   Updated: 2026/08/20 10:06:50 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <string>

class Replacer {
private:
    std::string _fileName;
    std::string _s1;
    std::string _s2;
    // builds a new string with s1 replaced by s2
    std::string _replaceLine(const std::string &line);

public:
    Replacer(const std::string &fileName, const std::string &s1,
             const std::string &s2);
    ~Replacer();
    void run(); // opens the files, processes line by line
};

#endif
