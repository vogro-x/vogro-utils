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

#ifndef __SPLIT_QUERY_STRING_HPP
#define __SPLIT_QUERY_STRING_HPP

#include <map>
#include <string>

std::map<std::string,std::string> split_query_string(std::string str) {
    std::map<std::string,std::string> results;
    std::string key,val;
    auto flag = true;
    if(str.length()==0){
        return results;
    }

    for (auto i = 0; i <= str.length(); i++) {
        if (i == str.length() || str[i] == '&') {
            flag = true;
            results[key]=val;
            key.clear();
            val.clear();
            continue;
        }
        else if (str[i] == '=') {
            flag = false;
            continue;
        }

        if (flag) {
            key += str[i];
        }
        else {
            val += str[i];
        }
    }
    return results;
}

#endif