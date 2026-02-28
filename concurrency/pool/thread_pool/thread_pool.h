//
// Created by skybcyang on 2026/2/23.
//

#ifndef SNIPPETS_THREAD_POOL_H
#define SNIPPETS_THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class thread_pool {
public:
    explicit thread_pool(size_t thread_count = std::thread::hardware_concurrency())
        : m_stop(false) {
        for (size_t i = 0; i < thread_count; ++i) {
            m_workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(m_queue_mutex);
                        m_condition.wait(lock, [this] {
                            return m_stop || !m_tasks.empty();
                        });
                        
                        if (m_stop && m_tasks.empty()) {
                            return;
                        }
                        
                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~thread_pool() {
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_stop = true;
        }
        m_condition.notify_all();
        
        for (auto& worker : m_workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using return_type = std::invoke_result_t<F, Args...>;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            if (m_stop) {
                throw std::runtime_error("cannot submit task to stopped thread pool");
            }
            m_tasks.emplace([task]() { (*task)(); });
        }
        
        m_condition.notify_one();
        return result;
    }

    size_t thread_count() const {
        return m_workers.size();
    }

private:
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_queue_mutex;
    std::condition_variable m_condition;
    bool m_stop;
};

#endif //SNIPPETS_THREAD_POOL_H
