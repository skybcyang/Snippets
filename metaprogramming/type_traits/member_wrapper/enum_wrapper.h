//
// Created by skybcyang on 2021/8/7.
//

#ifndef TEMPO_ENUM_WRAPPER_H
#define TEMPO_ENUM_WRAPPER_H

#include <utility>

namespace Details {
    template<typename T, typename Then>
    struct EnumWrapperBase {
        EnumWrapperBase(T val, Then then) : val(val), then(then) {}

        T val;
        Then then;
    };

    template<typename T, typename Then, typename = void>
    struct EnumWrapper : protected EnumWrapperBase<T, Then> {
        using EnumWrapperBase<T, Then>::EnumWrapperBase;

        constexpr void operator()() {}
    };

    // SFINAE
    template<typename T, typename Then>
    struct EnumWrapper<T, Then, std::void_t<decltype(std::declval<Then>()(std::declval<T>()))>>
        : protected EnumWrapperBase<T, Then> {
        using Base = EnumWrapperBase<T, Then>;
        using Base::Base;

        constexpr void operator()() {
            Base::then(Base::val);
        }
    };

    // C++17 deduction guide
    template<typename T, typename Then>
    EnumWrapper(T, Then) -> EnumWrapper<T, Then>;
}

#define IfEnumExistE(type, field, exec); \
{                                        \
    Details::EnumWrapper(type, [](auto type) -> decltype(decltype(type)::field) { \
                                    return exec(decltype(type)::field), decltype(type)::field;\
                                })();                                         \
}

#define IfEnumExistExec(type, field, exec); \
    {                                       \
        type t;                             \
        IfEnumExistE(t, field, exec);        \
    }

#endif //TEMPO_ENUM_WRAPPER_H
