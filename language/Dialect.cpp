#include "Dialect.hpp"

lang::Type *lang::Dialect::createType(const char *name, int value) {
}

lang::Dialect::Dialect() {
}

void lang::Dialect::gotoFragment(compiler::Fragment *where, compiler::Fragment *to) {

}

void lang::Dialect::conditionalJump(compiler::Fragment *where, util::Condition when, compiler::Fragment *to) {

}

lang::ImportHandler *lang::Dialect::importer(lang::ImporterContext &context) {
    // TODO: Change path to be read from an import handler

    return new ImportHandler(this, context);
}

const char *lang::Dialect::getName() const {
    return "default";
}
