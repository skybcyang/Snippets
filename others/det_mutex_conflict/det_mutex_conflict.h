//
// Created by skybcyang on 2022/6/29.
//

#ifndef SNIPPETS_DET_MUTEX_CONFLICT_H
#define SNIPPETS_DET_MUTEX_CONFLICT_H

#include <mutex>
#include <atomic>
#include <iostream>

struct MutexConflictCtx {
    static std::atomic_size_t count;
};

std::atomic_size_t MutexConflictCtx::count = 0;

struct MutexLock {
    explicit MutexLock(std::mutex& mutex) : mtx(mutex) {
        MutexConflictCtx::count++;
        std::cout << MutexConflictCtx::count << std::endl;
        mtx.lock();
    }
    ~MutexLock() {
        mtx.unlock();
        MutexConflictCtx::count--;
    }
private:
    std::mutex& mtx;
};

#endif //SNIPPETS_DET_MUTEX_CONFLICT_H
