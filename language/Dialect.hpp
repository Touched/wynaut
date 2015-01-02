#ifndef WYNAUT_LANGUAGE_DIALECT_HPP_
#define WYNAUT_LANGUAGE_DIALECT_HPP_

#include "Type.hpp"
#include "Module.hpp"
#include "ImportHandler.hpp"
#include "../compiler/Fragment.hpp"
#include "../util/Condition.hpp"

namespace lang {
    class Dialect {
    public:
        Dialect();

        // TODO: Make these all pure virtuals

        virtual Type *createType(const char *name, int value);

        lang::ImportHandler *importer(lang::ImporterContext &context);

        virtual void gotoFragment(compiler::Fragment *where, compiler::Fragment *to);

        virtual void conditionalJump(compiler::Fragment *where, util::Condition when, compiler::Fragment *to);

    protected:
        const char *name = "";
    };
}

#endif