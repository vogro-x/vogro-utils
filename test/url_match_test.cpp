#include <string>
#include <assert.h>
#include "../url_match.hpp"

int main (void){
    std::map<std::string, std::string> pathParam;

    std::string reqUrl1 = "/";
    std::string handlerUrl1 = "/";
    auto result1=urlMatch(reqUrl1, handlerUrl1, pathParam);
    assert(result1.first && !result1.second);
    pathParam.clear();

    std::string reqUrl2 = "/abc/dd/kk";
    std::string handlerUrl2 = "/abc/{int:id}/kk";
    auto result2=urlMatch(reqUrl2, handlerUrl2, pathParam);
    assert(!result2.first && !result2.second);
    pathParam.clear();

    std::string reqUrl3 = "/abc/25/kk";
    std::string handlerUrl3 = "/abc/{int:id}/kk";
    auto result3 = urlMatch(reqUrl3, handlerUrl3, pathParam);
    assert(result3.first && !result3.second);
    assert(pathParam.at("id") == "25");
    pathParam.clear();

    std::string reqUrl4 = "/abc/andrew/kk";
    std::string handlerUrl4 = "/abc/{str:name}/kk";
    auto result4 = urlMatch(reqUrl4, handlerUrl4, pathParam);
    assert(result4.first && !result4.second);
    assert(pathParam.at("name") == "andrew");
    pathParam.clear();

    std::string reqUrl5 = "/abc/andrew/kk";
    std::string handlerUrl5 = "/abc/{id}/kk"; //default is int
    auto result5 =urlMatch(reqUrl5, handlerUrl5, pathParam);
    assert(!result5.first && !result5.second);
    pathParam.clear();

    std::string reqUrl6 = "/abc/100/kk/andrew/";
    std::string handlerUrl6 = "/abc/{int:id}/kk/{str:name}/";
    auto result6 = urlMatch(reqUrl6, handlerUrl6, pathParam);
    assert(result6.first && !result6.second);
    assert(pathParam.at("id") == "100");
    assert(pathParam.at("name") == "andrew");
    pathParam.clear();
    
    std::string reqUrl7 = "/fdg";
    std::string handlerUrl7 = "/";
    auto result7 = urlMatch(reqUrl7, handlerUrl7, pathParam);
    assert( !result7.first && !result7.second);

    std::string reqUrl8 = "/static/js/index.js";
    std::string handlerUrl8 = "/";
    auto result8 = urlMatch(reqUrl8, handlerUrl8, pathParam);
    assert( !result8.first && result8.second);
    
    return 0;


}