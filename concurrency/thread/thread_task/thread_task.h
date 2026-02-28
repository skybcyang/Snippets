//
// Created by skybcyang on 2021/11/13.
//

#ifndef SNIPPETS_THREAD_TASK_H
#define SNIPPETS_THREAD_TASK_H

#include <thread>

template<typename F, typename ...Ts>
struct thread_task {
    explicit thread_task(F&& f, Ts... ts) : m_thread(f, ts...) {}
    ~thread_task() {
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }
private:
    std::thread m_thread;
};

#endif //SNIPPETS_THREAD_TASK_H
