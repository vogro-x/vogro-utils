#include <string>
#include <assert.h>
#include "../split_query_string.hpp"

int main(void) {
    auto result1 = split_query_string("");
    assert(result1.size() == 0);

    auto result2 = split_query_string("a=1");
    assert(result2.at("a") == "1");

    auto result3 = split_query_string("id=25&name=andrewpqc");
    assert(result3.at("id") == "25");
    assert(result3.at("name") == "andrewpqc");

    return 0;
}