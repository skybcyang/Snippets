//
// Created by skybcyang on 2022/3/3.
//

#ifndef TEMPO_INTRUSIVE_SHARED_PTR_H
#define TEMPO_INTRUSIVE_SHARED_PTR_H

#include <iostream>
#include <atomic>

template<typename T>
struct intrusive_ptr_base {
public:
    intrusive_ptr_base() : user_count(0) {}
    friend void intrusive_ptr_add_ref(intrusive_ptr_base<T>* base) {
        base->user_count++;
    }
    friend void intrusive_ptr_release(intrusive_ptr_base<T>* base) {
        if (--base->user_count == 0) {
            delete static_cast<T const*>(base);
        }
    }
    friend size_t intrusive_ptr_get_user_count(intrusive_ptr_base<T>* base) {
        return base->user_count;
    }
    size_t GetUserCount() {
        return user_count;
    }
private:
    std::atomic_size_t user_count;
};

template<typename T>
struct intrusive_ptr {
public:
     intrusive_ptr(T* t) : t(t) {
        if (t != nullptr) {
            intrusive_ptr_add_ref(t);
        }
    }

    intrusive_ptr(const intrusive_ptr& other) {
        t = other.t;
        if (t != nullptr) {
            intrusive_ptr_add_ref(t);
        }
    }

    intrusive_ptr& operator=(T* other) {
        if (t == other) {
            return *this;
        }
        if (t != nullptr) {
            intrusive_ptr_release(t);
        }
        t = other;
        if (t != nullptr) {
            intrusive_ptr_add_ref(t);
        }
        return *this;
    }

    intrusive_ptr& operator=(const intrusive_ptr& other) {
        if (this == &other) {
            return *this;
        }
        if (t != nullptr) {
            intrusive_ptr_release(t);
        }
        t = other.t;
        if (t != nullptr) {
            intrusive_ptr_add_ref(t);
        }
        return *this;
    }

    ~intrusive_ptr() {
        if (t != nullptr) {
            intrusive_ptr_release(t);
        }
        t = nullptr;
    }

    T* Get() {
         if (t == nullptr) {
             return nullptr;
         }
        return t;
    }

    void Reset() {
        if (t != nullptr) {
            intrusive_ptr_release(t);
            t = nullptr;
        }
    }

    size_t GetUserCount() {
        if (t != nullptr) {
            return intrusive_ptr_get_user_count(t);
        }
        return 0;
    }
private:
    T* t;
};

#endif //TEMPO_MY_INTRUSIVE_PTR_H
