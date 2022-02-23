//
// Created by skybcyang on 2021/12/17.
//

#ifndef TEMPO_EMPTY_CLASS_CHECKER_H
#define TEMPO_EMPTY_CLASS_CHECKER_H

#include <type_traits>
#include <cstddef>

template<typename T, typename ...Ts>
class IsEmpty
{
    struct NonDerived: Ts... { virtual ~NonDerived() = default; };
    struct Derived : T { virtual ~Derived() = default; };

public:
    inline static constexpr bool value = (sizeof(NonDerived) == sizeof(Derived));
};

struct ActionFlag {};

struct ActionBase : ActionFlag {};

struct ActionsFlag {};

template<typename T>
struct IsSingleActionEmpty {
    // 判断是不是从ActionBase派生来的 && (如果是Actions，那么不用进一步判断 || 如果是Action，判空)
    // static constexpr bool value = std::is_base_of_v<ActionFlag, T> && (std::is_base_of_v<ActionsFlag, T> || IsEmpty<T>::value);
    // 考虑到EmptyActions的情况，去掉第一个条件"判断是不是从ActionBase派生来的"
    static constexpr bool value = std::is_base_of_v<ActionsFlag, T> || IsEmpty<T>::value;
    static_assert(value);
};

template<typename ...Ts>
struct ActionsTemplate : virtual public ActionsFlag, public Ts... {
    // 错误情况下，如果不拆出IsSingleActionEmpty单独判断，那么没办法分清楚是哪个类出错了
    static constexpr bool value = ((IsSingleActionEmpty<Ts>::value) && ...);
    static_assert(value);
};

#define DEFINE_ACTIONS_AGGREGATES(actions, ...) \
using actions = ActionsTemplate<__VA_ARGS__>;

#endif
