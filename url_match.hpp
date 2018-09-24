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
#include <map>
#include <locale>
#include <codecvt>

#ifndef __URL_MATCH_HPP__
#define __URL_MATCH_HPP__


inline static std::string url_encode(const std::string &value) noexcept {
    static auto hex_chars = "0123456789ABCDEF";

    std::string result;
    result.reserve(value.size()); // Minimum size of result

    for (auto &chr : value) {
        if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '-' || chr == '.' || chr == '_' || chr == '~'))
            result += std::string("%") + hex_chars[static_cast<unsigned char>(chr) >> 4] + hex_chars[static_cast<unsigned char>(chr) & 15];
        else
            result += chr;
    }

    return result;
}

inline static std::string url_decode(const std::string &value) noexcept {
    std::string result;
    result.reserve(value.size() / 3 + (value.size() % 3)); // Minimum size of result

    for (std::size_t i = 0; i < value.size(); ++i) {
        auto &chr = value[i];
        if (chr == '%' && i + 2 < value.size()) {
            auto hex = value.substr(i + 1, 2);
            auto decoded_chr = static_cast<char>(std::strtol(hex.c_str(), nullptr, 16));
            result += decoded_chr;
            i += 2;
        }
        else if (chr == '+')
            result += ' ';
        else
            result += chr;
    }

    return result;
}

inline static  std::string u8wstring_to_string(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

inline static std::wstring u8string_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.from_bytes(str);
}



/***
 *  pair(a,b)
 *  if(!a&&!b) not match
 *  if(a&&!b) a normal match
 *  if(!a&&b) a match to request static files
 */ 
std::pair<bool,bool> urlMatch(std::wstring requestUrl, std::wstring handlerUrl, std::map<std::string, std::string> &storeMap) {
    // whether request serve template file or static file
    if (requestUrl.find(L"/static")==0){ return std::make_pair(false,true); }
    

    if (handlerUrl.back() != '/') { handlerUrl += '/'; }

    if (requestUrl.back() != '/') { requestUrl += '/'; }

    std::wstring type, name, dynamicParam;

    auto handlerUrlLength=handlerUrl.length();
    auto requestUrlLength=requestUrl.length();
    auto max_length = (handlerUrlLength > requestUrlLength) ? handlerUrlLength : requestUrlLength;
    for (auto i = 0, j = 0; (i < max_length)&&(j < max_length); ++i, ++j) {
        if (handlerUrl[i] == L'{') {
            auto tempIndex = i + 1;
            bool flag = true; //true代表当前在type域中
            do {
                if (handlerUrl[tempIndex] == L':') {
                    flag = false;
                    ++tempIndex;
                }

                if (!flag) name += handlerUrl[tempIndex];
                else type += handlerUrl[tempIndex];

                ++tempIndex;
            } while (handlerUrl[tempIndex] != L'}');

            i = tempIndex + 1;

            if (flag == true)  type = L"int"; // default type is int
            
            do {
                // if type is int, every char in dynamicParam should be in [48,57]
                if ((type == L"int") && (requestUrl[j] < 48 || requestUrl[j] > 57)) {
                    return std::make_pair(false,false);
                }
                dynamicParam += requestUrl[j];
                ++j;
            } while (requestUrl[j] != L'/');

            // store the dynamic parameters to storeMap
            storeMap[u8wstring_to_string(name)] = u8wstring_to_string(dynamicParam);

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