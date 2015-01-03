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

#include <cstring>
#include <iostream>

#include "Module.hpp"

lang::Module::Module(const char *name) : name_(name) {
}

lang::Module::~Module() {
    for (std::map<std::string, lang::Function*>::iterator it = functions_.begin(); it != functions_.end(); ++it) {
        delete it->second;
    }
}

const char *lang::Module::getName() {
    return name_.c_str();
}

void lang::Module::add(lang::Function *fn) {
    functions_[fn->getName()] = fn;
}

lang::Function *lang::Module::operator[](std::string const &key) {
    return functions_.at(key);
}

bool lang::Module::exists(std::string const &key) {
    return functions_.count(key) > 0;
}
