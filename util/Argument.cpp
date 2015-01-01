#include "Argument.hpp"

#include "arguments/Constant.hpp"
#include "arguments/Type.hpp"
#include "arguments/String.hpp"

util::Argument::Argument() {
}

bool util::Argument::isString() {
    return false;
}

bool util::Argument::isConstant() {
    return false;
}

bool util::Argument::isIdentifier() {
    return false;
}

util::Argument::~Argument() {
}

util::Argument *util::Argument::create(int value) {
    return new util::Constant(value);
}

util::Argument *util::Argument::create(lang::Type *value) {
    return new util::Type(value);
}

util::Argument *util::Argument::create(const char *value) {
    return new util::String(value);
}
