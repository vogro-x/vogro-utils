#include <iostream>
#include <assert.h>
#include "../trim_string.hpp"

int main(void) {

    std::string s0 = "";
    std::string s1 = "abc  ";
    std::string s2 = "  bugbugbug";
    std::string s3 = "   balabala   ";

    s0 = trim(s0);
    s1 = rtrim(s1);
    s2 = ltrim(s2);
    s3 = trim(s3);

    assert(s0=="");
    assert(s1=="abc");
    assert(s2=="bugbugbug");
    assert(s3=="balabala");
    return 0;
}