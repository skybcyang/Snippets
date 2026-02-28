//
// Created by skybcyang on 2022/7/27.
//

#include "class_unity.h"
#include <catch2/catch_test_macros.hpp>


TEST_CASE("test class unity") {
//    static_assert(std::is_base_of_v<ABCro, ABCrw>);


    Arw arw;
    arw.SetA(1);
    arw.GetA();
    Aro<Arw>* aro = &arw;
    aro->GetA();




}