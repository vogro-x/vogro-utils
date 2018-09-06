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