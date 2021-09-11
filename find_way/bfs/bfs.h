//
// Created by 杨斌诚 on 2021/9/11.
//

#ifndef SNIPPETS_BFS_H
#define SNIPPETS_BFS_H

#include "../base.h"
#include <iostream>
#include <queue>
#include <vector>

template<typename T, int row, int col>
void bfs(T(&map)[row][col], Position& start, Position& aim, std::vector<Position>& result) {
    std::queue<Position> que;
    bool used[row][col] = {false};
    int stepMap[row][col] = {};

    que.push(start);
    used[start.x][start.y] = true;
    stepMap[start.x][start.y] = 0;
    std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while(!que.empty()) {
        size_t queueSize = que.size();
        while(queueSize > 0) {
            Position& cur = que.front();
            for (auto& direction: directions) {
                Position newPos{cur.x + direction.first, cur.y + direction.second};
                if (newPos.x < 0 || newPos.x >= row || newPos.y < 0 || newPos.y >= col) continue;
                if (used[newPos.x][newPos.y] || map[newPos.x][newPos.y] == BARRIER) continue;
                if (newPos == aim) {std::cout << "find" << std::endl;}
                if (stepMap[newPos.x][newPos.y] < stepMap[newPos.x][newPos.y] + 1) {
                    que.push(newPos);
                    stepMap[newPos.x][newPos.y] = stepMap[cur.x][cur.y] + 1;
                    used[newPos.x][newPos.y] = true;
                }
            }
            que.pop();
            queueSize--;
        }
    }
}

#endif //SNIPPETS_BFS_H
