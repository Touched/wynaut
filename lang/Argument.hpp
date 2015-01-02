#ifndef WYNAUT_UTIL_ARGUMENT_HPP_
#define WYNAUT_UTIL_ARGUMENT_HPP_

#include "Type.hpp"

namespace lang {
    class Argument {
    public:
        Argument();

        virtual bool isString();

        virtual bool isConstant();

        virtual bool isIdentifier();

        static Argument *create(const char *value);

        static Argument *create(lang::Type *value);

        static Argument *create(int value);

        virtual ~Argument();
    };
}

#endif /* WYNAUT_UTIL_ARGUMENT_HPP_ */