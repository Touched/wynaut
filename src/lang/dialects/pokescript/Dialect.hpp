#ifndef WYNAUT_LANG_POKESCRIPT_DIALECT_HPP_
#define WYNAUT_LANG_POKESCRIPT_DIALECT_HPP_

#include "../../Dialect.hpp"

namespace lang {
    namespace pokescript {
        class Dialect : public lang::Dialect {
        public:
            virtual ~Dialect();

            virtual Type *createType(const char *name, int value);

            virtual lang::ImportHandler *importer(lang::ImporterContext &context);

            virtual void gotoFragment(compiler::Fragment *where, compiler::Fragment *to);

            virtual const char *getName() const;

            virtual void conditionalJump(compiler::Fragment *where, lang::Condition when, compiler::Fragment *to);
        };
    }
}

#endif /* WYNAUT_LANG_POKESCRIPT_DIALECT_HPP_ */