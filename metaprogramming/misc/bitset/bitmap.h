//
// Created by skybcyang on 2022/3/13.
//

#ifndef SNIPPETS_BITMAP_H
#define SNIPPETS_BITMAP_H

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <type_traits>

enum MemoryType {
    MEM_BIT_32,
    MEM_BIT_64,
};

template<size_t N, MemoryType type>
struct BitLen {};

template<size_t N>
struct BitLen<N, MEM_BIT_64>{
    static constexpr size_t value = (N + 63) >> 6;
};

template<size_t N>
struct BitLen<N, MEM_BIT_32>{
    static constexpr size_t value = (N + 31) >> 5;
};

#define CLAC_BIT64_LEN(n) (n + 31) >> 5

template<size_t N, MemoryType type>
struct Bitmap {
public:
    using BitType = std::conditional_t<type == MEM_BIT_32, uint32_t, uint64_t>;
    static constexpr size_t BIT_SIZE = sizeof(BitType) * 8;

    Bitmap(size_t real_len) : real_len(real_len), bits{} {}
    ~Bitmap() = default;

    bool operator[](size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        return (bits[pos / BIT_SIZE] & (BitType(1) << (pos % BIT_SIZE))) != 0;
    }

    inline size_t Size() const {
        return real_len;
    }

    bool Empty() {
        for (size_t index = 0; index < bits_len; index++) {
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
        bits[pos / BIT_SIZE] |= (BitType(1) << (pos % BIT_SIZE));
        return true;
    }

    void Reset() {
        std::fill_n(bits, bits_len, 0);
    }

    bool Reset(size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        bits[pos / BIT_SIZE] &= ~(BitType(1) << (pos % BIT_SIZE));
        return true;
    }

    size_t FindFirst() {
        for (size_t index = 0; index < bits_len; index++) {
            if constexpr (type == MEM_BIT_64) {
                size_t offset = __builtin_ffsll(bits[index]);
                if (offset != 0) {
                    return (index << 6) + offset - 1;
                }
            } else {
                size_t offset = __builtin_ffs(bits[index]);
                if (offset != 0) {
                    return (index << 5) + offset - 1;
                }
            }
        }
        return real_len;
    }

    size_t FindNext(size_t pos) {
        if (pos >= real_len) {
            return real_len;
        }
        for (size_t index = ((pos + 1) / BIT_SIZE); index < bits_len; index++) {
            size_t offset = 0;
            if (index == ((pos + 1) / BIT_SIZE)) {
                BitType new_bit = (bits[index] >> ((pos + 1) % BIT_SIZE)) << ((pos + 1) % BIT_SIZE);
                if constexpr (type == MEM_BIT_64) {
                    offset = __builtin_ffsll(new_bit);
                } else {
                    offset = __builtin_ffs(new_bit);
                }
            }
            else {
                if constexpr (type == MEM_BIT_64) {
                    offset = __builtin_ffsll(bits[index]);
                } else {
                    offset = __builtin_ffs(bits[index]);
                }
            }
            if (offset != 0) {
                return (index * BIT_SIZE) + offset - 1;
            }
        }
        return real_len;
    }

private:
    const size_t real_len;

    static constexpr size_t bits_len = BitLen<N, type>::value;
    BitType bits[bits_len];
};

#endif //SNIPPETS_BITMAP_H
