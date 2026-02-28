//
// Created by skybcyang on 2021/10/26.
//

#include <iostream>
#include <catch2/catch_test_macros.hpp>

class Base {
public:
    virtual void Func(int a = 1) = 0;
};


class Derived: public Base {
public:
    void Func(int a = 2) override {
        std::cout << a << std::endl;
    }
};

TEST_CASE("test para binding") {
    Derived derived;
    Base& base = derived;

    base.Func(); // 1
    derived.Func(); // 2
}