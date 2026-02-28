//
// Created by skybcyang on 2026/2/23.
//

#ifndef SNIPPETS_SINGLETON_H
#define SNIPPETS_SINGLETON_H

#include <mutex>
#include <memory>

// Meyer's Singleton - C++11 thread-safe
#define DEFINE_SINGLETON(ClassName) \
    public: \
        static ClassName& Instance() { \
            static ClassName instance; \
            return instance; \
        } \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete; \
    private: \
        ClassName() = default; \
        ~ClassName() = default;

// Template base class for singleton
template<typename T>
class singleton {
public:
    static T& Instance() {
        static T instance;
        return instance;
    }
    
    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;

protected:
    singleton() = default;
    ~singleton() = default;
};

// Double-checked locking singleton (for dynamic allocation scenarios)
template<typename T>
class singleton_dcl {
public:
    static T& Instance() {
        if (!m_instance) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (!m_instance) {
                m_instance.reset(new T());
            }
        }
        return *m_instance;
    }
    
    singleton_dcl(const singleton_dcl&) = delete;
    singleton_dcl& operator=(const singleton_dcl&) = delete;

protected:
    singleton_dcl() = default;
    ~singleton_dcl() = default;

private:
    static std::unique_ptr<T> m_instance;
    static std::mutex m_mutex;
};

template<typename T>
std::unique_ptr<T> singleton_dcl<T>::m_instance = nullptr;

template<typename T>
std::mutex singleton_dcl<T>::m_mutex;

#endif //SNIPPETS_SINGLETON_H
