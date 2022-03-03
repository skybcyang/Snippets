//
// Created by skybcyang on 2022/3/3.
//

#include "intrusive_shared_ptr.h"
#include <queue>
#include <thread>
#include <catch2/catch_test_macros.hpp>

class Data : public intrusive_ptr_base<Data> {
public:
    Data() : intrusive_ptr_base<Data>() {std::cout<<"ctor"<<std::endl;}
    ~Data() {std::cout<<"dtor"<<std::endl;}
    Data(int x, double y) : i(x), d(y) {std::cout<<"ctor2"<<std::endl;}
    int GetI() const {return i;}
    double GetD() const {return d;}
    int i = 0;
    double d = 0.0;
};

TEST_CASE("Test Intrusive Shared Ptr") {
    Data* t = new Data();
    intrusive_ptr<Data> data = t;
    intrusive_ptr<Data> data1 = t;
    Data* ttt = data.Get();
    REQUIRE(data.Get()->GetI() == 0);
    REQUIRE(data.Get()->GetD() == 0);
}

TEST_CASE("Test Intrusive Make Shared") {
    intrusive_ptr<Data> data = new Data(1, 2.22);
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}

TEST_CASE("Test Intrusive Shared Ptr Get User Count") {
    intrusive_ptr<Data> data = new Data(1, 2.22);
    REQUIRE(data.GetUserCount() == 1);
    intrusive_ptr<Data> datacopy = data;
    REQUIRE(data.GetUserCount() == 2);
    data = nullptr;
    REQUIRE(datacopy.GetUserCount() == 1);
}

TEST_CASE("Test Intrusive Shared Ptr Changed") {
    intrusive_ptr<Data> data = new Data();
    REQUIRE(data.Get()->GetI() == 0);
    REQUIRE(data.Get()->GetD() == 0);
    data = new Data(1, 2.22);
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}

void CreateCopy(intrusive_ptr<Data> copy, std::queue<intrusive_ptr<Data>>& q) {
    for(int i=0; i<10000000; i++) {
        q.push(copy);
    }
}

TEST_CASE("TEST Intrusive Shared Ptr Multi Thread") {
    intrusive_ptr<Data> data = new Data();
    std::queue<intrusive_ptr<Data>> q1;
    std::queue<intrusive_ptr<Data>> q2;
    std::thread t1 {CreateCopy, data, std::ref(q1)};
    std::thread t2 {CreateCopy, data, std::ref(q2)};
    t1.join();
    t2.join();
    REQUIRE(data.GetUserCount() == 20000001);
}