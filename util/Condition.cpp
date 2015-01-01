#include "Condition.hpp"

util::Condition::Condition(util::Condition::Operator op, util::Expression *rhs, util::Expression *lhs) : lhs_(lhs), rhs_(rhs), condition_(op) {

}

util::Condition::Condition(util::Condition::Operator op, util::Expression *rhs) : lhs_(nullptr), rhs_(rhs), condition_(op) {

}

util::Condition::Condition(util::Expression *cond) : lhs_(cond), rhs_(nullptr), condition_(NONE) {

}

util::Condition::~Condition() {
    if (lhs_ != nullptr) delete lhs_;
    if (rhs_ != nullptr) delete rhs_;
}
