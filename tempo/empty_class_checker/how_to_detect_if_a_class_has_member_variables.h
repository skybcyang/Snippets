//
// Created by skybcyang on 2022/1/17.
// ref: https://stackoverflow.com/a/52208389
//

#ifndef TEMPO_HOW_TO_DETECT_IF_A_CLASS_HAS_MEMBER_VARIABLES_H
#define TEMPO_HOW_TO_DETECT_IF_A_CLASS_HAS_MEMBER_VARIABLES_H
#include <type_traits>
#include <cstddef>

namespace detail
{
    template<size_t NumBases, typename T, typename Base1 = void, typename... Rest>
    struct IsDerivedFrom
    {
        inline static constexpr bool value = std::is_base_of_v<Base1, T> && IsDerivedFrom<sizeof...(Rest), T, Rest...>::value;
    };

    template<typename T, typename Base1>
    struct IsDerivedFrom<1, T, Base1>
    {
        inline static constexpr bool value = std::is_base_of_v<Base1, T>;
    };

    template<typename T>
    struct IsDerivedFrom<0, T, void> : std::true_type {};
}

template<typename T, typename... BaseClasses>
struct IsDerivedFrom : detail::IsDerivedFrom<sizeof...(BaseClasses), T, BaseClasses...> {};

template<typename T, typename... BaseClasses>
class IsEmpty
{
    static_assert(IsDerivedFrom<T, BaseClasses...>::value);

    struct NonDerived : BaseClasses... { virtual ~NonDerived() = default; };
    struct Derived : T { virtual ~Derived() = default; };

public:
    inline static constexpr bool value = (sizeof(NonDerived) == sizeof(Derived));
};

// Example:

struct Base { virtual ~Base() = default; };
struct Base2 { virtual ~Base2() = default; };

struct EmptyDerived : Base {};
struct NonEmptyDerived : Base { int member; };

// Multiple inheritance:
struct EmptyDerivedMI : Base, Base2 {};
struct NonEmptyDerivedMI : Base, Base2 { int member; };

struct EmptyPOD {};
struct NonEmptyPOD { char m; };

static_assert(IsEmpty<EmptyDerived>::value);
static_assert(!IsEmpty<NonEmptyDerived>::value);

static_assert(IsEmpty<EmptyPOD>::value);
static_assert(!IsEmpty<NonEmptyPOD>::value);

static_assert(IsEmpty<EmptyDerivedMI, Base, Base2>::value);
static_assert(!IsEmpty<NonEmptyDerivedMI, Base, Base2>::value);

#endif //TEMPO_HOW_TO_DETECT_IF_A_CLASS_HAS_MEMBER_VARIABLES_H
