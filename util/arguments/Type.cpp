#include "Type.hpp"

util::Type::Type(lang::Type *value) : data_(value) {
}

util::Type::~Type() {
    delete data_;
}

bool util::Type::isIdentifier() {
    return true;
}
