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

#include "Argument.hpp"

#include "arguments/Constant.hpp"
#include "arguments/ArgType.hpp"
#include "arguments/String.hpp"

lang::Argument::Argument() {
}

bool lang::Argument::isString() {
    return false;
}

bool lang::Argument::isConstant() {
    return false;
}

bool lang::Argument::isIdentifier() {
    return false;
}

lang::Argument::~Argument() {
}

lang::Argument *lang::Argument::create(int value) {
    return new lang::Constant(value);
}

lang::Argument *lang::Argument::create(lang::Type *value) {
    return new lang::ArgType(value);
}

lang::Argument *lang::Argument::create(const char *value) {
    return new lang::String(value);
}
