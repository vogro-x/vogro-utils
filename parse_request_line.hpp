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