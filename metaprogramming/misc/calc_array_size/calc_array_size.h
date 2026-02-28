//
// Created by skybcyang on 2021/8/19.
//

#ifndef TEMPO_CALC_ARRAY_SIZE_H
#define TEMPO_CALC_ARRAY_SIZE_H

#include <iostream>

template <typename T, std::size_t N>
constexpr std::size_t arraySize(const T (&)[N]) noexcept
{
    return N;
}

#endif //TEMPO_CALC_ARRAY_SIZE_H
