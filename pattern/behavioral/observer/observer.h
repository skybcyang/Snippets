//
// Created by skybcyang on 2026/2/23.
//

#ifndef SNIPPETS_OBSERVER_H
#define SNIPPETS_OBSERVER_H

#include <vector>
#include <functional>
#include <algorithm>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <atomic>

// Non-thread-safe observer (for single-threaded scenarios)
template<typename EventT>
class observer {
public:
    using callback_t = std::function<void(const EventT&)>;
    using subscription_id = size_t;

    subscription_id subscribe(callback_t callback) {
        subscription_id id = m_next_id++;
        m_callbacks.emplace(id, std::move(callback));
        return id;
    }

    void unsubscribe(subscription_id id) {
        m_callbacks.erase(id);
    }

    void notify(const EventT& event) {
        for (auto& [id, callback] : m_callbacks) {
            if (callback) {
                callback(event);
            }
        }
    }

    void clear() {
        m_callbacks.clear();
    }

    size_t count() const {
        return m_callbacks.size();
    }

private:
    std::atomic<size_t> m_next_id{0};
    std::unordered_map<subscription_id, callback_t> m_callbacks;
};

// Thread-safe observer
template<typename EventT>
class observer_threadsafe {
public:
    using callback_t = std::function<void(const EventT&)>;
    using subscription_id = size_t;

    subscription_id subscribe(callback_t callback) {
        std::lock_guard<std::mutex> lock(m_mutex);
        subscription_id id = m_next_id++;
        m_callbacks.emplace(id, std::move(callback));
        return id;
    }

    void unsubscribe(subscription_id id) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_callbacks.erase(id);
    }

    void notify(const EventT& event) {
        std::unordered_map<subscription_id, callback_t> callbacks_copy;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            callbacks_copy = m_callbacks;
        }
        for (auto& [id, callback] : callbacks_copy) {
            if (callback) {
                callback(event);
            }
        }
    }

    void clear() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_callbacks.clear();
    }

    size_t count() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_callbacks.size();
    }

private:
    mutable std::mutex m_mutex;
    std::atomic<size_t> m_next_id{0};
    std::unordered_map<subscription_id, callback_t> m_callbacks;
};

// RAII subscription guard - auto unsubscribe when destroyed
template<typename ObserverT>
class subscription_guard {
public:
    using callback_t = typename ObserverT::callback_t;
    using subscription_id = typename ObserverT::subscription_id;

    subscription_guard(ObserverT& observer, callback_t callback)
        : m_observer(&observer), m_id(observer.subscribe(std::move(callback))) {}

    ~subscription_guard() {
        if (m_observer) {
            m_observer->unsubscribe(m_id);
        }
    }

    // Movable but not copyable
    subscription_guard(subscription_guard&& other) noexcept
        : m_observer(other.m_observer), m_id(other.m_id) {
        other.m_observer = nullptr;
    }

    subscription_guard& operator=(subscription_guard&& other) noexcept {
        if (this != &other) {
            if (m_observer) {
                m_observer->unsubscribe(m_id);
            }
            m_observer = other.m_observer;
            m_id = other.m_id;
            other.m_observer = nullptr;
        }
        return *this;
    }

    subscription_guard(const subscription_guard&) = delete;
    subscription_guard& operator=(const subscription_guard&) = delete;

private:
    ObserverT* m_observer;
    subscription_id m_id;
};

#endif //SNIPPETS_OBSERVER_H
