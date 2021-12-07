// Date.cpp

// 由于需要实现 Date.hpp 中声明的函数，需要包含 Date.hpp

#include "Date.hpp"

int Date::get_days()
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap(this->y)) {
        days[2] = 29;
    }
    auto cnt = 0;
    for (int i = 1; i < this->m; ++i) {
        cnt += days[i];
    }
    cnt += this->d;
    return cnt;
}

