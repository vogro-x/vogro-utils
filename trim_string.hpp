/************************************************************************ 
 * Copyright (c) 2018- , Andrewpqc <andrewpqc@mails.ccnu.edu>           *
 * All rights reserved.                                                 * 
 *                                                                      *
 * Apache License, Version 2.0                                          *
 * See http://www.apache.org/licenses/ for terms and contions for use,  *
 * reproduction, and distribution.                                      *
 *                                                                      *
 ************************************************************************/

#include <string>

#ifndef __TRIM_STRING_HPP__
#define __TRIM_STRING_HPP__

std::string ltrim(std::string str) {
    auto length = str.length();
    while(str.length()) {
        if (str[0] == ' ')
            str.erase(0, 1);
        else
            return str;
    }
    return str;
}

std::string rtrim(std::string str) {
    auto length = str.length();
    for (auto i = length - 1; i >= 0; i--) {
        if (str[i] == ' ')
            str.pop_back();
        else
            return str;
    }
    return str;
}

std::string trim(std::string str) {
    return rtrim(ltrim(str));
}

#endif