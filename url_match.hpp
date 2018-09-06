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
#include <map>

#ifndef __URL_MATCH_HPP__
#define __URL_MATCH_HPP__

/***
 *  pair(a,b)
 *  if(!a&&!b) not match
 *  if(a&&!b) a normal match
 *  if(!a&&b) a match to request static files
 */ 
std::pair<bool,bool> urlMatch(std::string requestUrl, std::string handlerUrl, std::map<std::string, std::string> &storeMap) {
    // whether request serve template file or static file
    if (requestUrl.find("/static")==0){ return std::make_pair(false,true); }
    

    if (handlerUrl.back() != '/') { handlerUrl += '/'; }

    if (requestUrl.back() != '/') { requestUrl += '/'; }

    std::string type, name, dynamicParam;

    auto handlerUrlLength=handlerUrl.length();
    auto requestUrlLength=requestUrl.length();
    auto max_length = (handlerUrlLength > requestUrlLength) ? handlerUrlLength : requestUrlLength;
    for (auto i = 0, j = 0; (i < max_length)&&(j < max_length); ++i, ++j) {
        if (handlerUrl[i] == '{') {
            auto tempIndex = i + 1;
            bool flag = true; //true代表当前在type域中
            do {
                if (handlerUrl[tempIndex] == ':') {
                    flag = false;
                    ++tempIndex;
                }

                if (!flag) name += handlerUrl[tempIndex];
                else type += handlerUrl[tempIndex];

                ++tempIndex;
            } while (handlerUrl[tempIndex] != '}');

            i = tempIndex + 1;

            if (flag == true)  type = "int"; // default type is int
            
            do {
                // if type is int, every char in dynamicParam should be in [48,57]
                if ((type == "int") && (requestUrl[j] < 48 || requestUrl[j] > 57)) {
                    return std::make_pair(false,false);
                }
                dynamicParam += requestUrl[j];
                ++j;
            } while (requestUrl[j] != '/');

            // store the dynamic parameters to storeMap
            storeMap[name] = dynamicParam;

            // clear name, type, dynamicParam
            name.clear();
            type.clear();
            dynamicParam.clear();
        }

        if ((i>=handlerUrlLength) ||(j>=requestUrlLength) || (handlerUrl[i] != requestUrl[j])) {
            return std::make_pair(false,false);
        }
    }
    return std::make_pair(true,false);
}

#endif