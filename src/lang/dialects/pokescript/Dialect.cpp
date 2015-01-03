#include "Dialect.hpp"
#include "../../../compiler/Blob.hpp"
#include "../../../compiler/Reference.hpp"

lang::pokescript::Dialect::~Dialect() {

}

lang::Type *lang::pokescript::Dialect::createType(const char *name, int value) {
    // TODO: Maintain list of types and construct correct one for this dialect
    return nullptr;
}

lang::ImportHandler *lang::pokescript::Dialect::importer(lang::ImporterContext &context) {
    return new ImportHandler(this, context);
}

void lang::pokescript::Dialect::gotoFragment(compiler::Fragment *where, compiler::Fragment *to) {
    // TODO: Binary goto
    where->push_back(new compiler::Blob(NULL, 0));
    where->push_back(new compiler::Reference(*to));
}

const char *lang::pokescript::Dialect::getName() const {
    return "pokescript";
}

void lang::pokescript::Dialect::conditionalJump(compiler::Fragment *where, lang::Condition when, compiler::Fragment *to) {
    where->push_back(new compiler::Blob(NULL, 0));

    // Comparison function
    where->push_back(new compiler::Blob(NULL, 0));

    // Conditional (if1/if2)
    where->push_back(new compiler::Blob(NULL, 0));

    // Pointer to target piece
    where->push_back(new compiler::Reference(*to));
}
