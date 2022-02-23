//
// Created by skybcyang on 2022/1/18.
//

#ifndef TEMPO_NEW_DT_H
#define TEMPO_NEW_DT_H

#include <string.h>
#include <utility>
#include <mutex>
#include <bitset>
#include <iostream>

struct NewDataTable {
    template<TAG tag, typename T>
    inline bool SetData(const T& t) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return DataHolder<tag>::SetData(t, data);
    }

    template<TAG tag, typename T>
    inline bool GetData(T& t) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return DataHolder<tag>::GetData(t, data);
    }

    template<TAG tag, typename F>
    inline bool WithData(F&& f) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return DataHolder<tag>::WithData(std::forward<F>(f), data);
    }

    template<TAG tag, typename T>
    inline bool GetArrayData(T* t, size_t len) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return DataHolder<tag>::GetArrayData(t, len, data);
    }

    template<TAG tag, typename T>
    inline bool SetArrayData(T* t, size_t len) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return DataHolder<tag>::SetArrayData(t, len, data);
    }

    template<TAG tag, typename F>
    inline bool WithArrayData(F&& f) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return DataHolder<tag>::WithArrayData(std::forward<F>(f), data);
    }

    template<TAG tag>
    struct DataHolder {};

private:
    InnerData data {};
    std::mutex m_mutex;
};


template<>
struct NewDataTable::DataHolder<TAG_0> {
    template<typename T>
    static inline bool GetData(T& t, InnerData& data) {
        t = data.tag_0;
        return true;
    }
    template<typename T>
    static inline bool SetData(T& t, InnerData& data) {
        data.tag_0 = t;
        return true;
    }
    template<typename F>
    static inline bool WithData(F&& f, InnerData& data) {
        f(data.tag_0);
        return true;
    }
};

template<>
struct NewDataTable::DataHolder<TAG_1> {
    template<typename T>
    static inline bool GetData(T& t, InnerData& data) {
        t = data.tag_1;
        return true;
    }
    template<typename T>
    static inline bool SetData(T& t, InnerData& data) {
        data.tag_1 = t;
        return true;
    }
    template<typename F>
    static inline bool WithData(F&& f, InnerData& data) {
        f(data.tag_1);
        return true;
    }
};
template<>
struct NewDataTable::DataHolder<TAG_2> {
    template<typename T>
    static inline bool GetArrayData(T* t, size_t len, InnerData& data) {
        size_t new_len = std::min(len, sizeof(data.tag_2) / sizeof(InnerData::tag_2[0]));
        for (size_t index = 0; index < new_len; index++) {
            t[index] = data.tag_2[index];
        }
        return true;
    }
    template<typename T>
    static inline bool SetArrayData(T* t, size_t len, InnerData& data) {
        size_t new_len = std::min(len, sizeof(data.tag_2) / sizeof(InnerData::tag_2[0]));
        for (size_t index = 0; index < new_len; index++) {
            data.tag_2[index] = t[index];
        }
        return true;
    }
    template<typename F>
    static inline bool WithArrayData(F&& f, InnerData& data) {
        return true;
    }
};

#endif //TEMPO_NEW_DT_H
