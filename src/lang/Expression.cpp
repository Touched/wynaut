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

#include "Expression.hpp"

lang::Expression::Expression(int value) : constant_(true), int_value_(value) {

}

bool lang::Expression::isConstant() {
    return constant_;
}

bool lang::Expression::isIdentifier() {
    return !constant_;
}

lang::Expression::~Expression() {
}

lang::Expression::operator int() {
    if (constant_)
        return int_value_;
    else
        throw "Not a constant";
}

lang::Expression::Expression(lang::Type *type) : constant_(false), type_(type) {
}

lang::Type *lang::Expression::getType() {
    return type_;
}
