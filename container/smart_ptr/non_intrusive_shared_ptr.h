//
// Created by skybcyang on 2020/11/25.
// 参考C++沉思录实现UserCount
//

#ifndef TEMPO_NON_INTRUSIVE_SHARED_PTR_H
#define TEMPO_NON_INTRUSIVE_SHARED_PTR_H

#include <iostream>
#include <atomic>

struct UserCount {
public:
    UserCount() : user_count(new std::atomic_size_t(1)) {}
    UserCount(const UserCount& uc) : user_count(uc.user_count) {
        ++(*user_count);
    }
    ~UserCount() {
        if (--(*user_count) == 0) {
            delete user_count;
        }
    }

    bool Only() {
        return *user_count == 1;
    }
    bool reattach(const UserCount& uc) {
        ++(*uc.user_count);
        if (--(*user_count) == 0) {
            delete user_count;
            user_count = uc.user_count;
            return true;
        }
        user_count = uc.user_count;
        return false;
    }
    size_t GetUserCount() {
        return *user_count;
    }

private:
    UserCount& operator=(const UserCount& uc);
private:
    std::atomic_size_t* user_count;
};

template <typename T>
struct MyNonIntrusivePtr {
public:
    MyNonIntrusivePtr() : t(new T) {}
    MyNonIntrusivePtr(std::nullptr_t rhs) : t(rhs) {}
    template<typename ...Ts>
    MyNonIntrusivePtr(Ts... args) : t(new T(args...)) {}
    MyNonIntrusivePtr(const MyNonIntrusivePtr& rhs) : t(rhs.t), uc(rhs.uc) {}
    MyNonIntrusivePtr(const T& tt) : t(new T(std::move(tt))) {}
    MyNonIntrusivePtr& operator=(const MyNonIntrusivePtr& rhs) {
        if (uc.reattach(rhs.uc)) {
            delete t;
        }
        t = rhs.t;
        return *this;
    }
    ~MyNonIntrusivePtr() {
        if (uc.Only()) {
            delete t;
        }
    }
    T* Get() { return t; }
    size_t GetUserCount() { return uc.GetUserCount(); }
private:
    T* t;
    UserCount uc;
};


template <typename T, typename ...Ts>
MyNonIntrusivePtr<T> MakeShared(Ts... args) {
    return MyNonIntrusivePtr<T>(args...);
}

#endif //TEMPO_NON_INTRUSIVE_SHARED_PTR_H
