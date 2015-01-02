#include <cstring>
#include <iostream>

#include "Module.hpp"

lang::Module::Module(const char *name) : name_(name) {
}

lang::Module::~Module() {
}

const char *lang::Module::getName() {
    return name_.c_str();
}

void lang::Module::add(lang::Function &fn) {
    functions_[fn.getName()] = fn;
}

lang::Function const &lang::Module::operator[](std::string const &key) {
    return functions_.at(key);
}

bool lang::Module::exists(std::string const &key) {
    return functions_.count(key) > 0;
}
