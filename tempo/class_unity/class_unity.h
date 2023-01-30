//
// Created by skybcyang on 2022/7/27.
//

#ifndef SNIPPETS_CLASS_UNITY_H
#define SNIPPETS_CLASS_UNITY_H

#include <type_traits>

template<typename Derived>
struct Base {
protected:
    inline Derived& GetDerived() {
        return static_cast<Derived&>(*this);
    }
};


template<typename RW>
struct Aro : Base<RW> {
public:
    [[nodiscard]] auto GetA() const {
        return a;
    }
protected:
    auto SetA(int ax) {
        this->a = ax;
    }
private:
    int a;
};

struct Arw : Aro<Arw> {
    using Aro<Arw>::SetA;
};

struct Bro {
public:
    [[nodiscard]] auto GetB() const {
        return b;
    }
protected:
    auto SetB(int bx) {
        this->b = bx;
    }
private:
    int b;
};
struct Brw : Bro{
    using Bro::SetB;
};

struct Cro {
public:
    [[nodiscard]] auto GetC() const {
        return c;
    }
protected:
    auto SetC(int cx) {
        this->c = cx;
    }
private:
    int c;
};
struct Crw : Cro {
    using Cro::SetC;
};

template<typename ...Ts>
struct Unity: Ts... {
};

using ABCro = Unity<Aro<Arw>>;
using ABCrw = Unity<Arw>;


#endif //SNIPPETS_CLASS_UNITY_H
