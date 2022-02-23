//
// Created by skybcyang on 2021/8/15.
//

#ifndef TEMPO_STATIC_CRTP_H
#define TEMPO_STATIC_CRTP_H

template<template<typename> typename INTERFACE, typename DETAILS>
class type : public INTERFACE<type<INTERFACE, DETAILS>> {
    using details_type = DETAILS;

    DETAILS d;
    friend class INTERFACE<type<INTERFACE, DETAILS>>;

    constexpr static DETAILS*
    details(INTERFACE<type<INTERFACE, DETAILS>> *i)
    { return &(static_cast<type<INTERFACE, DETAILS> *>(i)->d); }

    constexpr static const DETAILS*
    details(const INTERFACE<type<INTERFACE, DETAILS>> *i)
    { return &(static_cast<const type<INTERFACE, DETAILS> *>(i)->d); }
};

namespace interface
{
    template<typename T>
    struct A {
        constexpr void foo()
        { T::details(this)->foo(); }
    };

    template<typename T>
    struct B {
        constexpr void bar()
        { T::details(this)->bar(); }
    };
}

namespace details
{
    class A {
    public:
        void foo() { }
    };

    template<typename T>
    class B {
    public:
        void bar()
        { m_a.foo(); }

    private:
        interface::A<T> m_a;
    };
}

using A = type<interface::A, details::A>;

template<typename T>
using B = type<interface::B, details::B<T>>;

#endif //TEMPO_STATIC_CRTP_H
