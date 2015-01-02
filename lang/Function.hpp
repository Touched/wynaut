#ifndef WYNAUT_LANGUAGE_FUNCTION_HPP_
#define WYNAUT_LANGUAGE_FUNCTION_HPP_

#include <list>

#include "Type.hpp"
#include "Arguments.hpp"

namespace compiler {
    class Script;
}

namespace lang {
    class Function {
    public:
        Function();

        virtual ~Function();

        virtual void compile(compiler::Script *target, lang::Arguments &args) = 0;

        virtual const char *getName() = 0;
    };
}

#endif /* WYNAUT_LANGUAGE_FUNCTION_HPP_ */