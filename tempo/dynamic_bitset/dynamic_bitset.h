//
// Created by skybcyang on 2022/3/6.
//

#ifndef SNIPPETS_DYNAMIC_BITSET_H
#define SNIPPETS_DYNAMIC_BITSET_H

#include <vector>
#include <atomic>
#include <bitset>

struct DynamicBitset {
    DynamicBitset() = default;
    ~DynamicBitset() {
        delete[] bits;
    }
    bool Init(size_t len) {
        if (!m_init) {
            size = len;
            bits = new (std::nothrow) uint64_t[(len+63) >> 6];
            if (bits == nullptr) {
                return false;
            }
            for (size_t index = 0; index < ((size+63) >> 6); index++) { // memset
                bits[index] = 0;
            }
            m_init = true;
            return m_init;
        }
        return false;
    }
    bool operator[](size_t pos) {
        if (bits == nullptr || pos >= size) {
            return false;
        }
        return (bits[pos >> 6] & (Bit << (pos%64))) != 0;
    }
    bool operator|=(const DynamicBitset& other) {
        if (size != other.size) {
            return false;
        }
        // todo
        return true;
    }
    bool operator&=(const DynamicBitset& other) {
        if (size != other.size) {
            return false;
        }
        // todo
        return true;
    }
    inline size_t Size() const {
        return size;
    }
    bool Empty() {
        for (size_t index = 0; index < ((size+63) >> 6); index++) {
            if (bits[index] != 0) {
                return false;
            }
        }
        return true;
    }
    bool Set(size_t pos) {
        if (bits == nullptr || pos >= size) {
            return false;
        }
        bits[pos >> 6] |= (Bit << (pos%64));
        return true;
    }
    bool Reset() {
         if (bits == nullptr) {
             return false;
         }
        for (size_t index = 0; index < ((size+63) >> 6); index++) {
            bits[index] = 0;
        }
        return true;
    }
    bool Reset(size_t pos) {
        if (bits == nullptr || pos >= size) {
            return false;
        }
        bits[pos >> 6] &= ~(Bit << (pos%64));
        return true;
    }
    size_t FindFirst() {
        if (bits == nullptr) {
            return size;
        }
        for (size_t index = 0; index < ((size+63) >> 6); index++) {
            size_t offset = __builtin_ffsll(bits[index]); // __builtin_ffsll GCC的，建议自己实现，算法原理和二分差不多
            // 但是标准库是针对平台优化的，有些可能就一条指令，要是自己实现的话可能会很慢
            if (offset != 0) {
                return (index << 6) + offset -1;
            }
        }
        return size;
    }
    size_t FindNext(size_t pos) {
        if (bits == nullptr || pos >= size) {
            return size;
        }
        for (size_t index = (pos >> 6); index < ((size+63) >> 6); index++) {
            size_t offset = 0;
            if (index == (pos >> 6)) {
                uint64_t newBit = (bits[index] >> ((pos+1)%64)) << ((pos+1)%64);
                offset = __builtin_ffsll(newBit);
            }
            else {
                offset = __builtin_ffsll(bits[index]);
            }
            if (offset != 0) {
                return (index << 6) + offset - 1;
            }
        }
        return size;
    }

private:
    static constexpr uint64_t Bit = 1;
    std::atomic_bool m_init = false;
    size_t size = 0;
    uint64_t* bits;
};


#endif //SNIPPETS_DYNAMIC_BITSET_H
