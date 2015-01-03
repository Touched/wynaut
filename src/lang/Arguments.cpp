/*
This file is part of Wynaut.

Wynaut is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Wynaut is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wynaut.  If not, see <http://www.gnu.org/licenses/>.
*/

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
