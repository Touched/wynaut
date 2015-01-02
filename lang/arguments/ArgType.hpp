#ifndef WYNAUT_LANG_ARGUMENTS_TYPE_HPP_
#define WYNAUT_UTIL_ARGUMENTS_TYPE_HPP_

#include "../Argument.hpp"
#include "../../lang/Type.hpp"

namespace lang {
    class ArgType : public Argument {
    public:
        ArgType(lang::Type *value);

        virtual bool isIdentifier();

        virtual ~ArgType();

    protected:
        lang::Type *data_;
    };
}

#endif /* WYNAUT_LANG_ARGUMENTS_TYPE_HPP_ */