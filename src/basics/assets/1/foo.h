#ifndef FOO_H
#define FOO_H

int foo(int, int);

inline void func() { return; }  // 内联函数

class A {  // A 类型的声明
    int num;
public:
    A() = default;
    int get_num() {  // 直接写在类中的函数也是内联的
        return this->num;
    }
    void set_num(int num_) {
        this->num = num_;
    }
    void add(int m);  // 成员函数的实现也可以放在 cpp 中（类外实现）
};

#endif  // FOO_H
