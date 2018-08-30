#include <string>
#include <assert.h>
#include "../parse_header.hpp"

using namespace std;

int main(void) {

    std::string header1 = "Accept: */*";
    std::string header2 = "Accept-Encoding: gzip, deflate, br";
    std::string header3 = "Accept-Language: en,zh-CN;q=0.9,zh;q=0.8";
    std::string header4 = "Connection: keep-alive";
    std::string header5 = "Host: statistic.csdn.net";
    std::string header6 = "Origin: https://blog.csdn.net";
    std::string header7 = "Referer: https://blog.csdn.net/Aquester/article/details/27680643";
    std::string header8 = "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36 Query String Parameters";
    std::string badHeader = " BadHeader   :   bad header content ";
    
    auto header1_pair = parse_header(header1);
    auto header2_pair = parse_header(header2);
    auto header3_pair = parse_header(header3);
    auto header4_pair = parse_header(header4);
    auto header5_pair = parse_header(header5);
    auto header6_pair = parse_header(header6);
    auto header7_pair = parse_header(header7);
    auto header8_pair = parse_header(header8);
    auto badHeader_pair = parse_header(badHeader);

    assert(header1_pair.first == "Accept");
    assert(header1_pair.second == "*/*");

    assert(header2_pair.first == "Accept-Encoding");
    assert(header2_pair.second == "gzip, deflate, br");

    assert(header3_pair.first == "Accept-Language");
    assert(header3_pair.second == "en,zh-CN;q=0.9,zh;q=0.8");

    assert(header4_pair.first == "Connection");
    assert(header4_pair.second == "keep-alive");

    assert(header5_pair.first == "Host");
    assert(header5_pair.second == "statistic.csdn.net");

    assert(header6_pair.first == "Origin");
    assert(header6_pair.second == "https://blog.csdn.net");

    assert(header7_pair.first == "Referer");
    assert(header7_pair.second == "https://blog.csdn.net/Aquester/article/details/27680643");

    assert(header8_pair.first == "User-Agent");
    assert(header8_pair.second == "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36 Query String Parameters");

    assert(badHeader_pair.first == "BadHeader");
    assert(badHeader_pair.second == "bad header content");

    return 0;
}