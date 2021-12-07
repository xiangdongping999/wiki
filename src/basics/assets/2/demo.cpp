#include <iostream>
#include "Date.hpp"

int main() {
    int y, m, d;
    std::cin >> y >> m >> d;
    Date d1(y, m, d);
    std::cout << d1.get_days();
}
