#include "String.hpp"

lang::String::String(const char *value) : data_(value) {
}

lang::String::~String() {
}

bool lang::String::isString() {
    return true;
}
