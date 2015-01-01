#ifndef WYNAUT_UTIL_ARGUMENTS_CONSTANT_HPP_
#define WYNAUT_UTIL_ARGUMENTS_CONSTANT_HPP_

#include <slang.h>
#include "../Argument.hpp"

namespace util {
    class Constant : public Argument {
    public:
        Constant(int value);

        virtual ~Constant();

        virtual bool isConstant();

    protected:
        int data_;
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_CONSTANT_HPP_ */