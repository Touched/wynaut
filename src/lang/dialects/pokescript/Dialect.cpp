#include "Dialect.hpp"
#include "../../../compiler/Blob.hpp"
#include "../../../compiler/Reference.hpp"

lang::pokescript::Dialect::~Dialect() {

}

lang::Type *lang::pokescript::Dialect::createType(const char *name, int value) {
    return nullptr;
}

lang::ImportHandler *lang::pokescript::Dialect::importer(lang::ImporterContext &context) {
    return nullptr;
}

void lang::pokescript::Dialect::gotoFragment(compiler::Fragment *where, compiler::Fragment *to) {
    // TODO: Binary goto
    where->push_back(new compiler::Blob());
    where->push_back(new compiler::Reference(*to));
}

const char *lang::pokescript::Dialect::getName() const {
    return "pokescript";
}

void lang::pokescript::Dialect::conditionalJump(compiler::Fragment *where, lang::Condition when, compiler::Fragment *to) {

}
