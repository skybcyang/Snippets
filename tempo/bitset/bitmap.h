//
// Created by skybcyang on 2022/3/13.
//

#ifndef SNIPPETS_BITMAP_H
#define SNIPPETS_BITMAP_H

#include <cstddef>
#include <cstdint>
#include <algorithm>

enum MemoryType {
    MEM_BIT_32,
    MEM_BIT_64,
};

template<size_t N, MemoryType type>
struct BitLen {};

template<size_t N>
struct BitLen<MEM_BIT_32>{
    static constexpr size_t value = (N + 63) >> 6;
};

#define CLAC_BIT64_LEN(n) (n + 31) >> 5

template<size_t N, MemoryType type>
struct Bitmap {
public:
    Bitmap(size_t real_len) : real_len(real_len), bits{} {}
    ~Bitmap() = default;

    bool operator[](size_t pos) {
        if (pos >= real_len) {
            return false;
        }
        return (bits[pos >> 6] & (Bit << (pos%64))) != 0;
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
                uint64_t new_bit = (bits[index] >> ((pos + 1)%64)) << ((pos + 1)%64);
                offset = __builtin_ffsll(new_bit);
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
    const size_t real_len;

    static constexpr uint64_t BIT = 1;
    static constexpr size_t bits_len = BitLen<N, >;
    std::conditional_t<type == MEM_BIT_32, uint32_t, uint64_t> bits[bits_len];
};

#endif //SNIPPETS_BITMAP_H
