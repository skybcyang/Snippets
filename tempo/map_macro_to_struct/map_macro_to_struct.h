//
// Created by skybcyang on 2022/6/24.
//

#ifndef SNIPPETS_MAP_MACRO_TO_STRUCT_H
#define SNIPPETS_MAP_MACRO_TO_STRUCT_H

#include <cstdlib>
#include <type_traits>

namespace Details {
    template<typename T, size_t dim>
    struct ArrayType {
        unsigned int len;
        T data[dim];
    };
    template<typename T, size_t dim>
    using Type = std::conditional_t<dim == 1, T, ArrayType<T, dim>>;
}

#define DEFINE_STRUCT(clsName) \
struct clsName

#define DEFINE_FILED(filedName, type, dim) \
Details::Type<type, dim> filedName;

#endif //SNIPPETS_MAP_MACRO_TO_STRUCT_H
