#include <iostream>

template <typename Derived>
struct Interface {
    void Func() { GetDerived().FuncImpl(); }
private:
    inline Derived& GetDerived() {
        return static_cast<Derived&>(*this);
    }
};


struct AImpl : public Interface<AImpl> {
private:
    friend Interface;
    void FuncImpl() {
        std::cout << "AImpl" << std::endl;
    }
};

struct BImpl : public Interface<BImpl> {
private:
    friend Interface;
    void FuncImpl() {
        std::cout << "BImpl" << std::endl;
    }
};
