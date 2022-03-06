//
// Created by skybcyang on 2022/3/3.
//

#include "intrusive_shared_ptr.h"
#include <queue>
#include <thread>
#include <catch2/catch_test_macros.hpp>

class TestData : public intrusive_ptr_base<TestData> {
public:
    TestData() : intrusive_ptr_base<TestData>() {std::cout<<"ctor"<<std::endl;}
    ~TestData() {std::cout<<"dtor"<<std::endl;}
    TestData(int x, double y) : i(x), d(y) {std::cout<<"ctor2"<<std::endl;}
    int GetI() const {return i;}
    double GetD() const {return d;}
    int i = 0;
    double d = 0.0;
};

TEST_CASE("Test Intrusive Shared Ptr") {
    auto* t = new TestData();
    intrusive_ptr<TestData> data(t);
    REQUIRE(data.Get()->GetI() == 0);
    REQUIRE(data.Get()->GetD() == 0);
}

TEST_CASE("Test Intrusive Make Shared") {
    intrusive_ptr<TestData> data(new TestData(1, 2.22));
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}

TEST_CASE("Test Intrusive Shared Ptr Get User Count") {
    intrusive_ptr<TestData> data(new TestData(1, 2.22));
    REQUIRE(data.GetUserCount() == 1);
    intrusive_ptr<TestData> datacopy(data.Get());
    REQUIRE(data.GetUserCount() == 2);
    data.Reset();
    REQUIRE(datacopy.GetUserCount() == 1);
}

TEST_CASE("Test Intrusive Shared Ptr Changed") {
    intrusive_ptr<TestData> data(new TestData());
    REQUIRE(data.Get()->GetI() == 0);
    REQUIRE(data.Get()->GetD() == 0);
    data = new TestData(1, 2.22);
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}

void TestCreateCopy(TestData* copy, std::queue<intrusive_ptr<TestData>>& q) {
    for(int i=0; i<10000000; i++) {
        q.push(intrusive_ptr<TestData>(copy));
    }
}

TEST_CASE("TEST Intrusive Shared Ptr Multi Thread") {
    TestData* testData = new TestData();
    intrusive_ptr<TestData> data = testData;
    std::queue<intrusive_ptr<TestData>> q1;
    std::queue<intrusive_ptr<TestData>> q2;
    std::thread t1 {TestCreateCopy, testData, std::ref(q1)};
    std::thread t2 {TestCreateCopy, testData, std::ref(q2)};
    t1.join();
    t2.join();
    REQUIRE(data.GetUserCount() == 20000001);
}