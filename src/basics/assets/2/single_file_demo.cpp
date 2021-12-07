#include <iostream>

auto is_leap(int y) {
    return (y % 4 ==0 && y % 100 != 0) || y % 400 == 0;
}

struct Date
{
    int y;
    int m;
    int d;
    Date(int y_, int m_, int d_) : y(y_), m(m_), d(d_) {}
};

auto calc_days(Date const & date) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap(date.y)) {
        days[2] = 29;
    }
    auto cnt = 0;
    for (int i = 1; i < date.m; ++i) {
        cnt += days[i];
    }
    cnt += date.d;
    return cnt;
}

int main() {
    int y, m, d;
    std::cin >> y >> m >> d;
    Date d1(y, m, d);
    std::cout << calc_days(d1);
}
