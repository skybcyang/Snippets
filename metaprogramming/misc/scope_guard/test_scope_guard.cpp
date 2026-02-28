#include "ScopeGuard.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("test scope guard") {
    ON_SCOPE_EXIT{
                     std::cout << 1 << std::endl;
                 };
}
TEST_CASE("test scope guard dismiss") {
    ON_SCOPE_EXIT{
                     std::cout << 2 << std::endl;
                 };
    CANCEL_SCOPE_EXIT{};
}