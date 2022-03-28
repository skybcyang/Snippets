//
// Created by skybcyang on 2022/3/7.
//

#ifndef SNIPPETS_STATIC_BITSET_32BIT_H
#define SNIPPETS_STATIC_BITSET_32BIT_H

#include <cstddef>
#include <cstdint>
#include <algorithm>

template<size_t N>
struct StaticBitset32Bit {
public:
    StaticBitset32Bit(size_t real_len) : real_len(real_len), bits{} {}
    ~StaticBitset32Bit() = default;

    bool operator[](size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        return (bits[pos >> 5] & (Bit << (pos%32))) != 0;
    }

    bool operator|=(const StaticBitset32Bit& other) {
        // todo
        return true;
    }

    bool operator&=(const StaticBitset32Bit& other) {
        // todo
        return true;
    }

    inline size_t Size() const {
        return real_len;
    }

    bool Empty() {
        for (size_t index = 0; index < bit_len; index++) {
            if (bits[index] != 0) {
                return false;
            }
        }
        return true;
    }
    bool Set(size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        bits[pos >> 5] |= (Bit << (pos%32));
        return true;
    }

    void Reset() {
        std::fill_n(bits, bit_len, 0);
    }

    bool Reset(size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        bits[pos >> 5] &= ~(Bit << (pos%32));
        return true;
    }

    size_t FindFirst() {
        for (size_t index = 0; index < bit_len; index++) {
            size_t offset = __builtin_ffs(bits[index]);
            // __builtin_ffsll GCC的，建议自己实现，算法原理和二分差不多
            // 但是标准库是针对平台优化的，有些可能就一条指令，要是自己实现的话可能会很慢
            if (offset != 0) {
                return (index << 5) + offset -1;
            }
        }
        return real_len;
    }

    size_t FindNext(size_t pos) {
        if (pos >= real_len) {
            return real_len;
        }
        for (size_t index = ((pos + 1) >> 5); index < bit_len; index++) {
            size_t offset = 0;
            if (index == ((pos + 1) >> 5)) {
                uint32_t newBit = (bits[index] >> ((pos+1)%32)) << ((pos+1)%32);
                offset = __builtin_ffs(newBit);
            }
            else {
                offset = __builtin_ffs(bits[index]);
            }
            if (offset != 0) {
                return (index << 5) + offset - 1;
            }
        }
        return real_len;
    }

private:
    static constexpr uint32_t Bit = 1;
    const size_t real_len;
    static constexpr size_t bit_len = (N + 31) >> 5;
    uint32_t bits[bit_len];
};

#endif //SNIPPETS_STATIC_BITSET_32BIT_H
