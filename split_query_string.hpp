/************************************************************************ 
 * Copyright (c) 2018- , Andrewpqc <andrewpqc@mails.ccnu.edu>           *
 * All rights reserved.                                                 * 
 *                                                                      *
 * Apache License, Version 2.0                                          *
 * See http://www.apache.org/licenses/ for terms and contions for use,  *
 * reproduction, and distribution.                                      *
 *                                                                      *
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