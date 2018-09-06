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

#ifndef __PARSE_REQUEST_LINE_HPP__
#define __PARSE_REQUEST_LINE_HPP__

std::pair<std::string,std::pair<std::string,std::string>> parse_request_line(std::string request_line) {
    std::string method, url, version;

    url.reserve(50);// pre alloc 50 byte
    
    char flag = 'm';
    bool versionNumberStart = false;
    for (auto i = 0; i < request_line.length(); i++) {
        if (flag == 'm'){
            if (request_line[i] == ' ') {
                flag = 'u';
                continue;
            }
            method += request_line[i];
        }
        if (flag == 'u'){
            if (request_line[i] == ' ') {
                flag = 'v';
                continue;
            }
            url += request_line[i];
        }
        if (flag == 'v'){
            if (request_line[i] == '/') {
                versionNumberStart = true;
                ++i;
            }
            if (versionNumberStart)
                version += request_line[i];
        }
    }

    // for return three value
    auto url_version_pair=std::make_pair(url,version);
    return std::make_pair(method,url_version_pair); 
}

#endif