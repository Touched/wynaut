#ifndef WYNAUT_LANGUAGE_FUNCTION_HPP_
#define WYNAUT_LANGUAGE_FUNCTION_HPP_

#include <list>

#include "Type.hpp"
#include "../util/Arguments.hpp"

namespace compiler {
    class Script;
}

namespace lang {
    class Function {
    public:
        Function();

        virtual void compile(compiler::Script *target, util::Arguments &args);

        virtual ~Function();

        const char *getName();
    };
}

#endif /* WYNAUT_LANGUAGE_FUNCTION_HPP_ */