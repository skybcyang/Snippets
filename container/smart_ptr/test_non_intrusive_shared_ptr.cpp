//
// Created by skybcyang on 2020/11/25.
//

#include "intrusive_shared_ptr.h"
#include "non_intrusive_shared_ptr.h"
#include <queue>
#include <thread>
#include <catch2/catch_test_macros.hpp>

class Data {
public:
    Data() {std::cout<<"ctor"<<std::endl;}
    ~Data() {std::cout<<"dtor"<<std::endl;}
    Data(int x, double y) : i(x), d(y) {std::cout<<"ctor"<<std::endl;}
    int GetI() const {return i;}
    double GetD() const {return d;}
private:
    int i{};
    double d{};
};


TEST_CASE("Test Non Intrusive Shared Ptr") {
    MyNonIntrusivePtr<Data> data{};
    REQUIRE(data.Get()->GetI() == 0);
    REQUIRE(data.Get()->GetD() == 0);
}

TEST_CASE("Test Non Intrusive Make Shared") {
    MyNonIntrusivePtr<Data> data = MakeShared<Data>(1, 2.22);
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}

TEST_CASE("Test Non Intrusive Shared Ptr Get User Count") {
    MyNonIntrusivePtr<Data> data = MakeShared<Data>(1, 2.22);
    REQUIRE(data.GetUserCount() == 1);
    MyNonIntrusivePtr<Data> datacopy = data;
    REQUIRE(data.GetUserCount() == 2);
    data = nullptr;
    REQUIRE(datacopy.GetUserCount() == 1);
}

TEST_CASE("Test Non Intrusive Shared Ptr Changed") {
    MyNonIntrusivePtr<Data> data = MakeShared<Data>();
    REQUIRE(data.Get()->GetI() == 0);
    REQUIRE(data.Get()->GetD() == 0);
    data = MakeShared<Data>(1, 2.22);
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}

void CreateCopy(MyNonIntrusivePtr<int> copy, std::queue<MyNonIntrusivePtr<int>>& q) {
    for(int i=0; i<10000000; i++) {
        q.push(copy);
    }
}

TEST_CASE("TEST Non Intrusive Shared Ptr Multi Thread") {
    MyNonIntrusivePtr<int> data{};
    std::queue<MyNonIntrusivePtr<int>> q1;
    std::queue<MyNonIntrusivePtr<int>> q2;
    std::thread t1 {CreateCopy, data, std::ref(q1)};
    std::thread t2 {CreateCopy, data, std::ref(q2)};
    t1.join();
    t2.join();
    REQUIRE(data.GetUserCount() == 20000001);
}