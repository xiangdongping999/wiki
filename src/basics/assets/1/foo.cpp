#include "foo.h"

static int f(int a, int b) { return a - b; }

int foo(int a, int b) {
    
    a = f(a, b);

    A inst_1;  // 使用了 foo.h 中的 A 类型，因此需要引用 foo.h
    inst_1.set_num(2 * a);
    inst_1.add(b);

    return inst_1.get_num();
}

void A::add(int n) {
    this->num += n;
}
