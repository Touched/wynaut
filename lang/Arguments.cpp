#include <sys/wait.h>
#include <iostream>
#include "Arguments.hpp"

lang::Arguments::Arguments() {
}

lang::Arguments::Arguments(size_t n) : args_(n) {
}

lang::Arguments::~Arguments() {
    // Clean up all allocated memory
    for (iterator it = args_.begin(); it != args_.end(); ++it) {
        delete *it;
    }
}

void lang::Arguments::add(const char *value) {
    args_.push_back(lang::Argument::create(value));
}

void lang::Arguments::add(int value) {
    args_.push_back(lang::Argument::create(value));
}

void lang::Arguments::add(lang::Type *type) {
    args_.push_back(lang::Argument::create(type));
}

lang::Arguments::iterator lang::Arguments::end() {
    return args_.end();
}

lang::Arguments::iterator lang::Arguments::begin() {
    return args_.begin();
}

size_t lang::Arguments::size() {
    return args_.size();
}

lang::Argument *lang::Arguments::back() {
    return args_.back();
}

lang::Argument *lang::Arguments::operator[](size_t index) {
    return args_[index];
}

lang::Argument *lang::Arguments::at(size_t index) {
    return args_.at(index);
}

lang::Argument *lang::Arguments::front() {
    return args_.front();
}

void lang::Arguments::add(lang::Argument *arg) {
    args_.push_back(arg);
}
