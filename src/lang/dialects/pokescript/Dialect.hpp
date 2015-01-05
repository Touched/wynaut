#ifndef WYNAUT_LANG_POKESCRIPT_DIALECT_HPP_
#define WYNAUT_LANG_POKESCRIPT_DIALECT_HPP_

#include "../../Dialect.hpp"
#include "Type.hpp"

namespace lang {
    namespace pokescript {
        class Dialect : public lang::Dialect {
        public:
            virtual ~Dialect();

            virtual lang::Type *createType(const char *name, int value);

            virtual lang::ImportHandler *importer(lang::ImporterContext &context);

            virtual void gotoFragment(compiler::Fragment *where, compiler::Fragment *to);

            virtual const char *getName() const;

            virtual void conditionalJump(compiler::Fragment *where, lang::Condition *when, compiler::Fragment *to);

        protected:
            Type::Types typeEnumFromString(std::string const &name);

            uint8_t relationalOperatorFromEnum(Condition::Operator op);

            bool compare(compiler::Fragment *where, lang::Expression *lhs, lang::Expression *rhs);

            bool compare(compiler::Fragment *where, lang::Expression *lhs, int rhs);

            bool compare(compiler::Fragment *where, Condition::Operator op, int lhs, int rhs);
        };
    }
}

#endif /* WYNAUT_LANG_POKESCRIPT_DIALECT_HPP_ */