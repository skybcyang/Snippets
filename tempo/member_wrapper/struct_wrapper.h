//
// Created by skybcyang on 2021/8/7.
//

#ifndef TEMPO_STRUCT_WRAPPER_H
#define TEMPO_STRUCT_WRAPPER_H

#include <utility>

namespace Details {
    template <typename T, typename Then>
    struct StructWrapperBase {
        StructWrapperBase(T& t, Then then) : t(t), then(then) {}
        T& t;
        Then then;
    };

    template <typename T, typename Then, typename = void>
    struct StructWrapper : protected StructWrapperBase<T, Then> {
        using StructWrapperBase<T, Then>::StructWrapperBase;
        constexpr void operator()() {};
    };

    // SFINAE
    template <typename T, typename Then>
    struct StructWrapper<T, Then, std::void_t<decltype(std::declval<Then>()(std::declval<T>()))>>
        : protected StructWrapperBase<T, Then> {
        using Base = StructWrapperBase<T, Then>;
        using Base::Base;
        constexpr void operator()() {
            Base::then(Base::t);
        }
    };

    template <typename T, typename Then>
    StructWrapper(T, Then) -> StructWrapper<T, Then>;
}

#define IfFieldExistExec(value, field, then);         \
    Details::StructWrapper(value,                      \
        [&](auto&& val) -> decltype(val.field)& {   \
            then(val.field);                        \
            return val.field;                       \
        })();                                       \

#endif //TEMPO_STRUCT_WRAPPER_H
