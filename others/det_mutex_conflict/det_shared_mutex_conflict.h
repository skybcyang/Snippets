//
// Created by skybcyang on 2022/6/29.
//

#ifndef SNIPPETS_DET_SHARED_MUTEX_CONFLICT_H
#define SNIPPETS_DET_SHARED_MUTEX_CONFLICT_H

#include <atomic>
#include <iostream>
#include <shared_mutex>

struct ReadWriteMutexConflictCtx {
    static std::atomic_size_t reader_count;
    static std::atomic_size_t writer_count;

};
std::atomic_size_t ReadWriteMutexConflictCtx::reader_count = 0;
std::atomic_size_t ReadWriteMutexConflictCtx::writer_count = 0;

struct ReadMutexLock {
    explicit ReadMutexLock(std::shared_mutex& shared_mutex) : shared_mtx(shared_mutex) {
        ReadWriteMutexConflictCtx::reader_count++;
        shared_mtx.lock_shared();
    }
    ~ReadMutexLock() {
        shared_mtx.unlock_shared();
        ReadWriteMutexConflictCtx::reader_count--;
    }

private:
    std::shared_mutex& shared_mtx;
};
struct WriteMutexLock {
    explicit WriteMutexLock(std::shared_mutex& shared_mutex) : shared_mtx(shared_mutex) {
        ReadWriteMutexConflictCtx::writer_count++;
        std::cout << ReadWriteMutexConflictCtx::reader_count << " " << ReadWriteMutexConflictCtx::writer_count << std::endl;
        shared_mtx.lock();
    }
    ~WriteMutexLock() {
        shared_mtx.unlock();
        ReadWriteMutexConflictCtx::writer_count--;
    }

private:
    std::shared_mutex& shared_mtx;
};

#endif //SNIPPETS_DET_SHARED_MUTEX_CONFLICT_H
