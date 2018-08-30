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
#include "trim_string.hpp"

#ifndef __PARSE_HEADER_HPP__
#define __PARSE_HEADER_HPP__

std::pair<std::string, std::string> parse_header(std::string &header) {
    std::string header_key, header_val;

    header_val.reserve(50); //pre alloc space

    auto pos = header.find(":");
    header_key = trim(header.substr(0, pos));
    header_val = trim(header.substr(pos + 1));

    return std::make_pair(header_key, header_val);
}

#endif