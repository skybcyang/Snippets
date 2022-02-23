//
// Created by a9691 on 2022/2/18.
//

#ifndef TEMPO_OLD_DT_H
#define TEMPO_OLD_DT_H

#include "common.h"
#include <mutex>
#include <vector>

struct FieldInfo {
    uint32_t size;
    uint32_t len;
    uint32_t offset;
};
const std::vector<FieldInfo> FieldInfoTable {
        {
                sizeof(uint32_t),
                1,
                offsetof(InnerData, tag_0)
        },
        {
                sizeof(bool),
                1,
                offsetof(InnerData, tag_1)
        },
        {
                sizeof(char),
                10,
                offsetof(InnerData, tag_2)
        },
};

struct OldDataTable {
    template<typename T>
    bool SetData(uint32_t tag, T &t) {
        std::lock_guard<std::mutex> lock(m_mutex);
        const FieldInfo& info = FieldInfoTable[tag];
        if (info.len != 1) {
            return false;
        }
        uint8_t* addr = (reinterpret_cast<uint8_t*>(&data) + info.offset);
        *(reinterpret_cast<T*>(addr)) = t;
        return true;
    }

    template<typename T>
    bool GetData(uint32_t tag, T &t) {
        std::lock_guard<std::mutex> lock(m_mutex);
        const FieldInfo& info = FieldInfoTable[tag];
        if (info.len != 1) {
            return false;
        }
        uint8_t* addr = (reinterpret_cast<uint8_t*>(&data) + info.offset);
        t = *(reinterpret_cast<T*>(addr));
        return true;
    }

//    template<typename F>
//    bool WithData(uint32_t tag, F &&f) {
//        std::lock_guard<std::mutex> lock(m_mutex);
//        return true;
//    }

    template<typename T>
    bool SetArrayData(uint32_t tag, T* t, size_t len) {
        std::lock_guard<std::mutex> lock(m_mutex);
        const FieldInfo& info = FieldInfoTable[tag];
        T* addr = reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(&data) + info.offset);
        size_t new_len = std::min(static_cast<size_t>(info.len), len);
        for (size_t index = 0; index < new_len; index++) {
            addr[index] = t[index];
        }
        return true;
    }

    template<typename T>
    bool GetArrayData(uint32_t tag, T* t, size_t len) {
        std::lock_guard<std::mutex> lock(m_mutex);
        const FieldInfo& info = FieldInfoTable[tag];
        T* addr = reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(&data) + info.offset);
        size_t new_len = std::min(static_cast<size_t>(info.len), len);
        for (size_t index = 0; index < new_len; index++) {
            t[index] = addr[index];
        }
        return true;
    }

//    template<typename F>
//    bool WithArrayData(uint32_t tag, F &&f) {
//        std::lock_guard<std::mutex> lock(m_mutex);
//        return true;
//    }

private:
    std::mutex m_mutex;
    InnerData data;
};




#endif //TEMPO_OLD_DT_H
