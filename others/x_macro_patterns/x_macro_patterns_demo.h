//
// Created by skybcyang on 2022/2/15.
// refer to https://en.wikipedia.org/wiki/X_Macro
//

#ifndef SNIPPETS_X_MACRO_PATTERNS_DEMO_H
#define SNIPPETS_X_MACRO_PATTERNS_DEMO_H

#include <stdio.h>

#define LIST_OF_VARIABLES \
    X(value1)             \
    X(value2)             \
    X(value3)


#define X(name) int name;
LIST_OF_VARIABLES
#undef X

void print_variables(void) {
#define X(name) printf(#name " = %d\n", name);
    LIST_OF_VARIABLES
#undef X
}

#endif //SNIPPETS_X_MACRO_PATTERNS_DEMO_H
