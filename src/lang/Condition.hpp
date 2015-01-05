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

#ifndef WYNAUT_LANG_CONDITION_HPP_
#define WYNAUT_LANG_CONDITION_HPP_

#include "Expression.hpp"

namespace lang {
    class Condition {
    public:
        enum Operator {
            EQ,
            NEQ,
            LT,
            LEQ,
            GT,
            GEQ,
            NONE
        };

        Condition(Operator op, Expression *rhs, Expression *lhs);

        Condition(Operator op, Expression *rhs);

        Condition(Expression *cond);

        Expression *lhs();

        Expression *rhs();

        Operator getOperator();

        /**
        * Clones the condition, with the opposite operator
        */
        Condition *opposite();

        ~Condition();

    protected:
        Expression *lhs_, *rhs_;
        Operator condition_;
    };
}

#endif /* WYNAUT_LANG_CONDITION_HPP_ */