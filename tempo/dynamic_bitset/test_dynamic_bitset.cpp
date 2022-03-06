//
// Created by skybcyang on 2022/3/6.
//

#include "dynamic_bitset.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <nanobench.h>

TEST_CASE("test dynamic bitset function") {
    DynamicBitset db;
    db.Init(200);
    REQUIRE(db.Empty());
    REQUIRE(db.Size() == 200);

    REQUIRE(!db[0]);
    REQUIRE(!db[100]);
    REQUIRE(!db[199]);

    db.Set(10);
    db.Set(80);
    db.Set(130);
    db.Set(180);
    REQUIRE(db[10]);
    REQUIRE(db[80]);
    REQUIRE(db[130]);
    REQUIRE(db[180]);

    db.Reset(10);
    REQUIRE(!db[10]);

    REQUIRE(!db.Empty());
    db.Reset();
    REQUIRE(db.Empty());

    for (size_t index = db.FindFirst(); index < db.Size(); index = db.FindNext(index)) {
        std::cout << index << std::endl;
    }

}


TEST_CASE("test dynamic bitset performance") {
    ankerl::nanobench::Bench().epochs(100).run("dynamic bitset", [&] {
        DynamicBitset db;
        db.Init(1000000);
        for (uint32_t index = 0; index < 1000000; index ++) {
            db.Set(index);
            if (index % 5) {
                db.Reset(index);
            }
        }
        ankerl::nanobench::doNotOptimizeAway(db);
    });
    ankerl::nanobench::Bench().epochs(100).run("stl bitset", [&] {
        std::bitset<1000000> db;
        for (uint32_t index = 0; index < 1000000; index ++) {
            db.set(index);
            if (index % 5) {
                db.reset(index);
            }
        }
        ankerl::nanobench::doNotOptimizeAway(db);
    });
}
