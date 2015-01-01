#ifndef WYNAUT_GRAMMAR_WYNAUT_H_
#define WYNAUT_GRAMMAR_WYNAUT_H_

#include "../util/Expression.hpp"
#include "../util/Arguments.hpp"
#include "../util/Condition.hpp"

struct funcname {
    char *module;
    char *function;
};

enum operator_type {
    OP_PLUS,
    OP_MINUS,
    OP_DIVIDE,
    OP_MULTIPLY
};

enum condition_type {
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_LEQ,
    OP_GT,
    OP_GEQ
};

#endif