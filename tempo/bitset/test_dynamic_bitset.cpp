//
// Created by skybcyang on 2022/3/6.
//

#include "static_bitset.h"
#include "static_bitset_32bit.h"
#include "dynamic_bitset.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <nanobench.h>

TEST_CASE("test static bitset function") {
    StaticBitset<200> db(200);
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

    for (size_t index = db.FindFirst(); index < db.Size(); index = db.FindNext(index)) {
        std::cout << index << std::endl;
    }

    REQUIRE(!db.Empty());
    db.Reset();
    REQUIRE(db.Empty());

}

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
    ankerl::nanobench::Bench().epochs(1000).run("dynamic bitset", [&] {
        DynamicBitset db;
        db.Init(1000000);
        for (size_t index = 0; index < 1000000; index += 18) {
            db.Set(index);
            if (index % 5) {
                db.Reset(index);
            }
        }
//        for(size_t index = db.FindFirst(); index < 1000000; index = db.FindNext(index)){
//            db.Reset(index);
//        }
    });
    ankerl::nanobench::Bench().epochs(1000).run("static bitset", [&] {
        StaticBitset<1000000> db(1000000);
        for (size_t index = 0; index < 1000000; index += 18) {
            db.Set(index);
            if (index % 5) {
                db.Reset(index);
            }
        }
//        for(size_t index = db.FindFirst(); index < 1000000; index = db.FindNext(index)){
//            db.Reset(index);
//        }
    });
    ankerl::nanobench::Bench().epochs(1000).run("static bitset 32bit", [&] {
        StaticBitset32Bit<1000000> db(1000000);
        for (size_t index = 0; index < 1000000; index += 18) {
            db.Set(index);
            if (index % 5) {
                db.Reset(index);
            }
        }
//        for(size_t index = db.FindFirst(); index < 1000000; index = db.FindNext(index)){
//            db.Reset(index);
//        }
    });
    ankerl::nanobench::Bench().epochs(1000).run("stl bitset", [&] {
        std::bitset<1000000> db;
        for (size_t index = 0; index < 1000000; index += 18) {
            db.set(index);
            if (index % 5) {
                db.reset(index);
            }
        }
//        for(size_t index = db._Find_first(); index < 1000000; index = db._Find_next(index)){
//            db.reset(index);
//        }
    });
}
