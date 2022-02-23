//
// Created by a9691 on 2022/2/18.
//

#ifndef TEMPO_COMMON_H
#define TEMPO_COMMON_H

#include <cstdint>

enum TAG {
    TAG_0 = 0, // uint32_t
    TAG_1 = 1, // bool
    TAG_2 = 2, // char[10]
};

struct InnerData {
    uint32_t tag_0;
    bool tag_1;
    char tag_2[10];
};

#endif //TEMPO_COMMON_H
