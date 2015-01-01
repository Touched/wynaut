#include <sys/wait.h>
#include <iostream>
#include "Arguments.hpp"

util::Arguments::Arguments() {
}

util::Arguments::Arguments(size_t n) : args_(n) {
}

util::Arguments::~Arguments() {
    // Clean up all allocated memory
    for (iterator it = args_.begin(); it != args_.end(); ++it) {
        delete *it;
    }
}

void util::Arguments::add(const char *value) {
    args_.push_back(util::Argument::create(value));
}

void util::Arguments::add(int value) {
    args_.push_back(util::Argument::create(value));
}

void util::Arguments::add(lang::Type *type) {
    args_.push_back(util::Argument::create(type));
}

util::Arguments::iterator util::Arguments::end() {
    return args_.end();
}

util::Arguments::iterator util::Arguments::begin() {
    return args_.begin();
}

size_t util::Arguments::size() {
    return args_.size();
}

util::Argument *util::Arguments::back() {
    return args_.back();
}

util::Argument *util::Arguments::operator[](size_t index) {
    return args_[index];
}

util::Argument *util::Arguments::at(size_t index) {
    return args_.at(index);
}

util::Argument *util::Arguments::front() {
    return args_.front();
}

void util::Arguments::add(util::Argument *arg) {
    args_.push_back(arg);
}
