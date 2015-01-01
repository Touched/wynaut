#include "String.hpp"

util::String::String(const char *value) : data_(value) {
}

util::String::~String() {
}

bool util::String::isString() {
    return true;
}
