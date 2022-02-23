//
// Created by skybcyang on 2021/8/15.
//

#include <iostream>
#include "static_crtp.h"
#include <catch2/catch_test_macros.hpp>

namespace details
{
    class A_mock {
    public:
        void foo()
        { std::cout << "mocked foo\n"; }
    };
}

using A_mock = type<interface::A, details::A_mock>;

TEST_CASE("test static_crtp") {
    B<A_mock> b;
    b.bar();
}