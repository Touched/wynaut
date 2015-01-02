#include "Argument.hpp"

#include "arguments/Constant.hpp"
#include "arguments/ArgType.hpp"
#include "arguments/String.hpp"

lang::Argument::Argument() {
}

bool lang::Argument::isString() {
    return false;
}

bool lang::Argument::isConstant() {
    return false;
}

bool lang::Argument::isIdentifier() {
    return false;
}

lang::Argument::~Argument() {
}

lang::Argument *lang::Argument::create(int value) {
    return new lang::Constant(value);
}

lang::Argument *lang::Argument::create(lang::Type *value) {
    return new lang::ArgType(value);
}

lang::Argument *lang::Argument::create(const char *value) {
    return new lang::String(value);
}
