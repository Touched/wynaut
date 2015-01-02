#include "ArgType.hpp"

lang::ArgType::ArgType(lang::Type *value) : data_(value) {
}

lang::ArgType::~ArgType() {
    delete data_;
}

bool lang::ArgType::isIdentifier() {
    return true;
}
