//
// Created by skybcyang on 2021/9/11.
//

#ifndef SNIPPETS_DFS_H
#define SNIPPETS_DFS_H

#include "../base.h"
#include <iostream>
#include <vector>
#include <random>

template<typename T, int row, int col>
void dfs(T(&map)[row][col], bool(&used)[row][col], Position& cur, Position& aim, std::vector<Position>& que, std::vector<Position>& result) {
    if (cur == aim) {
        if (result.empty() || que.size() < result.size()) {
            result = que;
        }
        return;
    }
    std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));
    for (auto& direction: directions) {
        Position newPos{cur.x + direction.first, cur.y + direction.second};
        if (newPos.x < 0 || newPos.x >= row || newPos.y < 0 || newPos.y >= col) continue;
        if (used[newPos.x][newPos.y] || map[newPos.x][newPos.y] == BARRIER) continue;
        que.push_back(newPos);
        used[newPos.x][newPos.y] = true;
        dfs(map, used, newPos, aim, que, result);
        used[newPos.x][newPos.y] = false;
        que.pop_back();
    }

}

#endif //SNIPPETS_DFS_H
