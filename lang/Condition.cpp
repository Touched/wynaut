#include "Condition.hpp"

lang::Condition::Condition(lang::Condition::Operator op, lang::Expression *rhs, lang::Expression *lhs) : lhs_(lhs), rhs_(rhs), condition_(op) {

}

lang::Condition::Condition(lang::Condition::Operator op, lang::Expression *rhs) : lhs_(nullptr), rhs_(rhs), condition_(op) {

}

lang::Condition::Condition(lang::Expression *cond) : lhs_(cond), rhs_(nullptr), condition_(NONE) {

}

lang::Condition::~Condition() {
    if (lhs_ != nullptr) delete lhs_;
    if (rhs_ != nullptr) delete rhs_;
}
