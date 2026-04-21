#pragma once
#include <string>
#include <iostream>

namespace Util {

class Bint {
    long long v = 0;
public:
    Bint() = default;
    Bint(long long x) : v(x) {}
    Bint(const Bint&) = default;
    Bint& operator=(const Bint&) = default;

    friend Bint operator*(const Bint &a, long long b) { return Bint(a.v * b); }
    friend bool operator==(const Bint &a, const Bint &b) { return a.v == b.v; }
};

}

