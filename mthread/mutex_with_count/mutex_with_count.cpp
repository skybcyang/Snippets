//
// Created by skybcyang on 2023/1/31.
//

#include "mutex_with_count.h"

std::atomic_uint32_t MutexWithCount::mutex_num = 0;

MutexGuard MutexWithCount::GetGuard() {
    return MutexGuard{*this};
}