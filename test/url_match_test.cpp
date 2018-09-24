#include <string>
#include <assert.h>
#include <iostream>
#include "../url_match.hpp"

int main(void) {
    std::map<std::string, std::string> pathParam;

    std::string reqUrl1 = "/";
    std::string handlerUrl1 = "/";
    auto result1 = urlMatch(u8string_to_wstring(reqUrl1), u8string_to_wstring(handlerUrl1), pathParam);
    assert(result1.first && !result1.second);
    pathParam.clear();

    std::string reqUrl2 = "/abc/dd/kk";
    std::string handlerUrl2 = "/abc/{int:id}/kk";
    auto result2 = urlMatch(u8string_to_wstring(reqUrl2),u8string_to_wstring(handlerUrl2), pathParam);
    assert(!result2.first && !result2.second);
    pathParam.clear();

    std::string reqUrl3 = "/abc/25/kk";
    std::string handlerUrl3 = "/abc/{int:id}/kk";
    auto result3 = urlMatch(u8string_to_wstring(reqUrl3), u8string_to_wstring(handlerUrl3), pathParam);
    assert(result3.first && !result3.second);
    assert(pathParam.at("id") == "25");
    pathParam.clear();

    std::string reqUrl4 = "/abc/andrew/kk";
    std::string handlerUrl4 = "/abc/{str:name}/kk";
    auto result4 = urlMatch(u8string_to_wstring(reqUrl4), u8string_to_wstring(handlerUrl4), pathParam);
    assert(result4.first && !result4.second);
    assert(pathParam.at("name") == "andrew");
    pathParam.clear();

    std::string reqUrl5 = "/abc/andrew/kk";
    std::string handlerUrl5 = "/abc/{id}/kk"; //default is int
    auto result5 = urlMatch(u8string_to_wstring(reqUrl5), u8string_to_wstring(handlerUrl5), pathParam);
    assert(!result5.first && !result5.second);
    pathParam.clear();

    std::string reqUrl6 = "/abc/100/kk/andrew/";
    std::string handlerUrl6 = "/abc/{int:id}/kk/{str:name}/";
    auto result6 = urlMatch(u8string_to_wstring(reqUrl6), u8string_to_wstring(handlerUrl6), pathParam);
    assert(result6.first && !result6.second);
    assert(pathParam.at("id") == "100");
    assert(pathParam.at("name") == "andrew");
    pathParam.clear();

    std::string reqUrl7 = "/fdg";
    std::string handlerUrl7 = "/";
    auto result7 = urlMatch(u8string_to_wstring(reqUrl7),u8string_to_wstring(handlerUrl7), pathParam);
    assert(!result7.first && !result7.second);

    std::string reqUrl8 = "/static/js/index.js";
    std::string handlerUrl8 = "/";
    auto result8 = urlMatch(u8string_to_wstring(reqUrl8), u8string_to_wstring(handlerUrl8), pathParam);
    assert(!result8.first && result8.second);

    std::string reqUrl9 = "/abc/阿超/kk";
    std::string handlerUrl9 = "/abc/{str:name}/kk";
    auto result9 = urlMatch(u8string_to_wstring(reqUrl9), u8string_to_wstring(handlerUrl9), pathParam);
    assert(result9.first && !result9.second);
    // std::cout<<pathParam.at("name")<<std::endl;
    assert(pathParam.at("name") == "阿超");
    pathParam.clear();

    std::string reqUrl10 = "/username/addddd/kk/jjj";
    std::string handlerUrl10= "/username/{str:name}/kk/";
    auto result10 = urlMatch(u8string_to_wstring(reqUrl10), u8string_to_wstring(handlerUrl10), pathParam);
    assert(!result10.first && !result10.second);
    return 0;
}