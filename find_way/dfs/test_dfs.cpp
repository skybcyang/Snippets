//
// Created by 杨斌诚 on 2021/9/11.
//

#include "dfs.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("test dfs find way") {
    TYPE map[5][5] {
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, BARRIER, BARRIER, EMPTY,
        EMPTY, BARRIER, EMPTY, EMPTY, EMPTY,
        EMPTY, BARRIER, EMPTY, BARRIER, BARRIER,
        BARRIER, EMPTY, EMPTY, EMPTY, EMPTY,
    };
    bool used[5][5] {
        false, false, false, false, false,
        false, false, false, false, false,
        false, false, false, false, false,
        false, false, false, false, false,
        false, false, false, false, false,
    };
    Position start{0,0};
    Position aim{4, 4};
    std::vector<Position> que;
    std::vector<Position> result;
    used[start.x][start.y] = true;
    que.push_back(start);
    dfs(map, used, start, aim, que, result);
    for (auto& pos: result) {
        std::cout << pos.x << " " << pos.y << std::endl;
    }
}