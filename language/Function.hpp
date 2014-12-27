#ifndef WYNAUT_LANGUAGE_FUNCTION_HPP_
#define WYNAUT_LANGUAGE_FUNCTION_HPP_

#include <list>

#include "Type.hpp"

namespace lang {
    class Function {
    public:
        typedef std::list<lang::Type *> Arguments;

        Function();

        virtual ~Function();

        const char *getName();
    };
}

#endif /* WYNAUT_LANGUAGE_FUNCTION_HPP_ */