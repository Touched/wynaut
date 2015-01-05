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

#include <iostream>
#include "Condition.hpp"

lang::Condition::Condition(lang::Condition::Operator op, lang::Expression *rhs, lang::Expression *lhs) : lhs_(lhs), rhs_(rhs), condition_(op) {
}

lang::Condition::Condition(lang::Condition::Operator op, lang::Expression *rhs) : lhs_(nullptr), rhs_(rhs), condition_(op) {
}

lang::Condition::Condition(lang::Expression *cond) : lhs_(cond) {
    // essentially LHS != 0
    condition_ = NEQ;
    rhs_ = new Expression(0);
}

lang::Condition::~Condition() {
    if (lhs_ != nullptr) delete lhs_;
    if (rhs_ != nullptr) delete rhs_;
}

lang::Condition::Operator lang::Condition::getOperator() {
    return condition_;
}

lang::Expression *lang::Condition::rhs() {
    return rhs_;
}

lang::Expression *lang::Condition::lhs() {
    return lhs_;
}

lang::Condition *lang::Condition::opposite() {
    // TODO: Clone this and construct new object
    return nullptr;
}
