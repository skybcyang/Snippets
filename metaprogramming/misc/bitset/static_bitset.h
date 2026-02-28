//
// Created by skybcyang on 2022/3/7.
//

#ifndef SNIPPETS_STATIC_BITSET_H
#define SNIPPETS_STATIC_BITSET_H

#include <cstddef>
#include <cstdint>
#include <algorithm>

template<size_t N>
struct StaticBitset {
public:
    StaticBitset(size_t real_len) : real_len(real_len), bits{} {}
    ~StaticBitset() = default;

    bool operator[](size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        return (bits[pos >> 6] & (Bit << (pos%64))) != 0;
    }

    bool operator|=(const StaticBitset& other) {
        // todo
        return true;
    }

    bool operator&=(const StaticBitset& other) {
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
        bits[pos >> 6] |= (Bit << (pos%64));
        return true;
    }

    void Reset() {
        std::fill_n(bits, bit_len, 0);
    }

    bool Reset(size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        bits[pos >> 6] &= ~(Bit << (pos%64));
        return true;
    }

    size_t FindFirst() {
        for (size_t index = 0; index < bit_len; index++) {
            size_t offset = __builtin_ffsll(bits[index]);
            if (offset != 0) {
                return (index << 6) + offset -1;
            }
        }
        return real_len;
    }

    size_t FindNext(size_t pos) {
        if (pos >= real_len) {
            return real_len;
        }
        for (size_t index = ((pos + 1) >> 6); index < bit_len; index++) {
            size_t offset = 0;
            if (index == ((pos + 1) >> 6)) {
                uint64_t newBit = (bits[index] >> ((pos + 1)%64)) << ((pos + 1)%64);
                offset = __builtin_ffsll(newBit);
            }
            else {
                offset = __builtin_ffsll(bits[index]);
            }
            if (offset != 0) {
                return (index << 6) + offset - 1;
            }
        }
        return real_len;
    }

private:
    static constexpr uint64_t Bit = 1;
    const size_t real_len;
    static constexpr size_t bit_len = (N + 63) >> 6;
    uint64_t bits[bit_len];
};

#endif //SNIPPETS_STATIC_BITSET_H
