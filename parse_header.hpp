/************************************************************************ 
 Copyright 2018 andrewpqc@mails.ccnu.edu.cn
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.                                                                                                        
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