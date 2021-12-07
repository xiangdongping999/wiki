#include "foo.h"

static int f(int a, int b) { return a + b; }

int main() {
    int result = foo(2, 3);
    int t = f(4, 5);
}
