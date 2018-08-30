#include <string>
#include <assert.h>
#include "../parse_request_line.hpp"

int main(void) {
    auto line1 = parse_request_line("GET /abc/dd?a=1&b=2 HTTP/1.1");
    auto line2 = parse_request_line("POST /abc HTTP/1.1");
    auto line3 = parse_request_line("PUT / HTTP/1.1");

    assert(line1.first == "GET" && line1.second.first == "/abc/dd?a=1&b=2" && line1.second.second == "1.1");
    assert(line2.first == "POST" && line2.second.first == "/abc" && line2.second.second == "1.1");
    assert(line3.first == "PUT" && line3.second.first == "/" && line3.second.second == "1.1");

    return 0;
}