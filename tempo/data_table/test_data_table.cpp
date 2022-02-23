//
// Created by skybcyang on 2022/1/18.
//

#include "old_dt.h"
#include "new_dt.h"
#include <catch2/catch_test_macros.hpp>
#include "nanobench.h"

TEST_CASE("test old dt") {
    OldDataTable dt;
    uint32_t a = 233;
    REQUIRE(dt.SetData(TAG_0, a));
    uint32_t a_ = 0;
    REQUIRE(dt.GetData(TAG_0, a_));
    REQUIRE(a_ == a);

    bool b = true;
    REQUIRE(dt.SetData(TAG_1, b));
    bool b_ = false;
    REQUIRE(dt.GetData(TAG_1, b_));
    REQUIRE(b_);

    char c[10] = "skybcyang";
    REQUIRE(dt.SetArrayData(TAG_2, c, 10));
    char c_[10] = "";
    REQUIRE(dt.GetArrayData(TAG_2, c_, 10));
    REQUIRE(std::string(c_) == "skybcyang");
}

TEST_CASE("test new dt") {
    NewDataTable dt;
    uint32_t a = 233;
    REQUIRE(dt.SetData<TAG_0>(a));
    uint32_t a_ = 0;
    REQUIRE(dt.GetData<TAG_0>(a_));
    REQUIRE(a_ == a);
    dt.WithData<TAG_0>([=](auto x) {
        REQUIRE(x == a);
    });

    bool b = true;
    REQUIRE(dt.SetData<TAG_1>(b));
    bool b_ = false;
    REQUIRE(dt.GetData<TAG_1>(b_));
    REQUIRE(b_);
    dt.WithData<TAG_1>([=](auto x) {
        REQUIRE(x);
    });

    char c[10] = "skybcyang";
    REQUIRE(dt.SetArrayData<TAG_2>(c, 10));
    char c_[10] = "";
    REQUIRE(dt.GetArrayData<TAG_2>(c_, 10));
    REQUIRE(std::string(c_) == "skybcyang");
    dt.WithArrayData<TAG_2>([](auto x) {
        REQUIRE(std::string(x) == "skybcyang");
    });
}

TEST_CASE("test data table speed") {
    OldDataTable old_dt;
    NewDataTable new_dt;

    ankerl::nanobench::Bench().epochs(1000).run("test old data table speed", [&] {
        uint32_t a = 233;
        old_dt.SetData(TAG_0, a);
        uint32_t a_ = 0;
        old_dt.GetData(TAG_0, a_);
        ankerl::nanobench::doNotOptimizeAway(a_);

        bool b = true;
        old_dt.SetData(TAG_1, b);
        bool b_ = false;
        old_dt.GetData(TAG_1, b_);
        ankerl::nanobench::doNotOptimizeAway(b_);

        char c[10] = "skybcyang";
        old_dt.SetArrayData(TAG_2, c, 10);
        char c_[10] = "";
        old_dt.GetArrayData(TAG_2, c_, 10);
        ankerl::nanobench::doNotOptimizeAway(c_);
    });

    ankerl::nanobench::Bench().epochs(1000).run("test new data table speed", [&] {
        uint32_t a = 233;
        new_dt.SetData<TAG_0>(a);
        uint32_t a_ = 0;
        new_dt.GetData<TAG_0>(a_);
        ankerl::nanobench::doNotOptimizeAway(a_);

        bool b = true;
        new_dt.SetData<TAG_1>(b);
        bool b_ = false;
        new_dt.GetData<TAG_1>(b_);
        ankerl::nanobench::doNotOptimizeAway(b_);

        char c[10] = "skybcyang";
        new_dt.SetArrayData<TAG_2>(c, 10);
        char c_[10] = "";
        new_dt.GetArrayData<TAG_2>(c_, 10);
        ankerl::nanobench::doNotOptimizeAway(c_);
    });

}