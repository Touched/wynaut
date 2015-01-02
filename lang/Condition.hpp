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

        ~Condition();

    protected:
        Expression *lhs_, *rhs_;
        Operator condition_;
    };
}

#endif /* WYNAUT_LANG_CONDITION_HPP_ */