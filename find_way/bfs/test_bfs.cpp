//
// Created by 杨斌诚 on 2021/9/11.
//

#include "bfs.h"
#include <catch2/catch_test_macros.hpp>


TEST_CASE("test bfs") {

    TYPE map[5][5] {
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, BARRIER, EMPTY,
        EMPTY, BARRIER, EMPTY, EMPTY, EMPTY,
        EMPTY, BARRIER, EMPTY, BARRIER, BARRIER,
        BARRIER, EMPTY, EMPTY, EMPTY, EMPTY,
        };
    Position start{0,0};
    Position aim{4, 4};
    std::vector<Position> result;
    bfs(map,start, aim, result);

    std::cout << result.size() << std::endl;
    for (auto& pos: result) {
        std::cout << pos.x << " " << pos.y << std::endl;
    }
}