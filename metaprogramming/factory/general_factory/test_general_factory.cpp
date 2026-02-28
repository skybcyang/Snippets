//
// Created by skybcyang on 2021/11/12.
//

#include <iostream>
#include "general_factory.h"
#include "offline_register.h"
#include <catch2/catch_test_macros.hpp>

/** 可以定义在其他.h .cpp里面 **/
struct ITest {

};

struct Test: ITest {
    Test() : ITest() {
        std::cout << "test ctor" << std::endl;
    }

};

REGISTER_TEST(Test);
/****************************/

TEST_CASE("test general factory") {
    TestFactory::Instance().Create("Test");
}

