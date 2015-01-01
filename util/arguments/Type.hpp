#ifndef WYNAUT_UTIL_ARGUMENTS_TYPE_HPP_
#define WYNAUT_UTIL_ARGUMENTS_TYPE_HPP_

#include "../Argument.hpp"
#include "../../language/Type.hpp"

namespace util {
    class Type : public Argument {
    public:
        Type(lang::Type *value);

        virtual bool isIdentifier();

        virtual ~Type();

    protected:
        lang::Type *data_;
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_TYPE_HPP_ */