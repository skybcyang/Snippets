//
// Created by skybcyang on 2023/1/31.
//

#ifndef SNIPPETS_MUTEX_WITH_COUNT_H
#define SNIPPETS_MUTEX_WITH_COUNT_H

#include <mutex>
#include <atomic>
#include <iostream>

struct MutexGuard;

struct MutexWithCount {
    explicit MutexWithCount() {
        mutex_num++;
    }
    ~MutexWithCount() {
        mutex_num--;
    }

    // for conditional_variable wait_for
    MutexGuard GetGuard();

    void lock() {
        ref_num++;
        m_mutex.lock();
        // cout is not thread-safe
        std::cout << "ref_num = " << ref_num << std::endl;
    }

    void unlock() {
        m_mutex.unlock();
        ref_num--;
    }

private:
    friend struct MutexGuard;
    std::mutex m_mutex;
    std::atomic_uint32_t ref_num = 0;
    static std::atomic_uint32_t mutex_num;
};

struct MutexGuard {
    explicit MutexGuard(MutexWithCount& mwc) : m_mwc(mwc) {}
    ~MutexGuard() {
        m_mwc.ref_num--;
    }
    std::mutex& GetMutex() {
        m_mwc.ref_num++;
        return m_mwc.m_mutex;
    }
    MutexWithCount& m_mwc;
};

#endif //SNIPPETS_MUTEX_WITH_COUNT_H
