//
// Created by skybcyang on 2021/11/13.
//

#ifndef SNIPPETS_THREAD_GUARD_H
#define SNIPPETS_THREAD_GUARD_H

#include <thread>

class thread_guard
{
public:
    explicit thread_guard(std::thread& thread_) : m_thread(thread_) {}
    ~thread_guard() {
        if(m_thread.joinable()) {
            m_thread.join();
        }
    }
    thread_guard(thread_guard const&)=delete;   // 3
    thread_guard& operator=(thread_guard const&)=delete;
private:
    std::thread& m_thread;
};
#endif //SNIPPETS_THREAD_GUARD_H
