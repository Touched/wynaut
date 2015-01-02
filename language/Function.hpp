#ifndef WYNAUT_LANGUAGE_FUNCTION_HPP_
#define WYNAUT_LANGUAGE_FUNCTION_HPP_

#include <list>

#include "Type.hpp"
#include "../compiler/Fragment.hpp"
#include "../util/Arguments.hpp"

namespace lang {
    class Function {
    public:
        Function();

        void compile(compiler::Fragment *where, util::Arguments &args);

        virtual ~Function();

        const char *getName();
    };
}

#endif /* WYNAUT_LANGUAGE_FUNCTION_HPP_ */