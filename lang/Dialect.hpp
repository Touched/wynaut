#ifndef WYNAUT_LANGUAGE_DIALECT_HPP_
#define WYNAUT_LANGUAGE_DIALECT_HPP_

#include "Type.hpp"
#include "Module.hpp"
#include "../compiler/Fragment.hpp"
#include "Condition.hpp"
#include "ImporterContext.hpp"
#include "ImportHandler.hpp"

namespace lang {
    class Dialect {
    public:
        Dialect();

        // TODO: Make these all pure virtuals

        virtual Type *createType(const char *name, int value);

        lang::ImportHandler *importer(lang::ImporterContext &context);

        virtual void gotoFragment(compiler::Fragment *where, compiler::Fragment *to);

        virtual const char *getName() const;

        virtual void conditionalJump(compiler::Fragment *where, lang::Condition when, compiler::Fragment *to);

    protected:
    };
}

#endif