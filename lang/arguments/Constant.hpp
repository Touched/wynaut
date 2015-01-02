#ifndef WYNAUT_LANG_ARGUMENTS_CONSTANT_HPP_
#define WYNAUT_LANG_ARGUMENTS_CONSTANT_HPP_

#include <slang.h>
#include "../Argument.hpp"

namespace lang {
    class Constant : public Argument {
    public:
        Constant(int value);

        virtual ~Constant();

        virtual bool isConstant();

    protected:
        int data_;
    };
}

#endif /* WYNAUT_LANG_ARGUMENTS_CONSTANT_HPP_ */