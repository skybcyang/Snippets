//
// Created by skybcyang on 2021/9/11.
//

#ifndef SNIPPETS_BASE_H
#define SNIPPETS_BASE_H

struct Position {
    int x;
    int y;
    bool operator==(const Position& pos) const {
        return x == pos.x && y == pos.y;
    }
    bool operator!=(const Position& pos) const {
        return x != pos.x || y != pos.y;
    }
};

enum TYPE {
    EMPTY,
    AIM,
    BARRIER,
};

#endif //SNIPPETS_BASE_H
