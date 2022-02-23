//
// Created by skybcyang on 2021/8/19.
//

#ifndef TEMPO_TUPLE_FOR_EACH_H
#define TEMPO_TUPLE_FOR_EACH_H

#include <tuple>
#include <cstddef>

// 折叠表达式
// 如果想在折叠表达式中使用分支语句，可以用逻辑运算符进行短路操作
template <typename T, typename F, size_t ...Ts>
void ForEach(T&& t, F&& f, std::index_sequence<Ts...>) {
    (f(std::get<Ts>(t)), ...);
}

template <typename T, typename F, size_t ...Ts>
void ForEach(T&& t, F&& f) {
    ForEach(std::forward<T>(t), std::forward<F>(f), std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>());
}

#endif //TEMPO_TUPLE_FOR_EACH_H
