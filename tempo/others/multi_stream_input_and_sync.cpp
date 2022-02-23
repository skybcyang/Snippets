//
// Created by skybcyang on 2020/11/15.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include <queue>
#include <mutex>
#include <catch2/catch_test_macros.hpp>

template <typename T>
class DataQueue{
public:
    void PushData(T data) {
        std::lock_guard<std::mutex> lock(mtx);
        dataqueue.push(data);
    }
    T GetAndPopData() {
        while(dataqueue.empty()){
        }
        std::lock_guard<std::mutex> lock(mtx);
        auto data = dataqueue.front();
        dataqueue.pop();
        return data;
    }
private:
    std::mutex mtx;
    std::queue<T> dataqueue;
};

using cam0stream = DataQueue<int>;
using cam1stream = DataQueue<float>;
using cam2stream = DataQueue<std::string>;
using DataSet = std::tuple<int, float, std::string>;


template <typename T, size_t ...Is>
auto foreach(T&& tuple, std::index_sequence<Is...>) -> DataSet {
    DataSet ds;
    ((std::get<Is>(ds) = std::get<Is>(tuple).GetAndPopData()), ...);
    return ds;
}

template <typename T>
auto foreach(T&& tuple) -> DataSet {
    return foreach(
            std::forward<T>(tuple),
            std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{}
    );
}

template <typename TUPLE>
class DataCenterT : public TUPLE {
public:
    static DataCenterT& GetDataCenterIns() {
        static DataCenterT dataCenter;
        return dataCenter;
    }
    auto SyncData() -> DataSet {
        return foreach(static_cast<TUPLE&>(*this));
    }
    template <typename T>
    T& GetDataQueue() {
        return std::get<T>(static_cast<TUPLE&>(*this));
    }
};

using DataCenter = DataCenterT<std::tuple<cam0stream, cam1stream, cam2stream>>;

void thread1() {
    DataCenter& dataCenter = DataCenter::GetDataCenterIns();
    int time = 0;
    while(time < 10) {
        dataCenter.GetDataQueue<cam0stream>().PushData(1);
        time++;
        usleep(1000);
    }
}

void thread2() {
    DataCenter& dataCenter = DataCenter::GetDataCenterIns();
    int time = 0;
    while(time < 10) {
        dataCenter.GetDataQueue<cam1stream>().PushData(5.20);
        time++;
        usleep(80);
    }
}

void thread3() {
    DataCenter& dataCenter = DataCenter::GetDataCenterIns();

    int time = 0;
    while(time < 10) {
        dataCenter.GetDataQueue<cam2stream>().PushData("sky");
        time++;
        usleep(3000);
    }
}

void thread4() {
    DataCenter& dataCenter = DataCenter::GetDataCenterIns();
    int time = 0;
    while(time < 10) {
        auto ds = dataCenter.SyncData();
        time++;
    }
}

TEST_CASE("test sync") {
    std::thread t1(thread1);
    std::thread t2(thread2);
    std::thread t3(thread3);
    std::thread t4(thread4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}