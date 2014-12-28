#ifndef WYNAUT_LANGUAGE_DIALECT_HPP_
#define WYNAUT_LANGUAGE_DIALECT_HPP_

#include "Type.hpp"
#include "Module.hpp"
#include "ImportHandler.hpp"

namespace lang {
    class Dialect {
    public:
        Dialect();
        virtual Type createType(const char *name, int value);
        virtual Module import(const char *module);

    protected:
        lang::ImportHandler *importer_;
    };
}

#endif