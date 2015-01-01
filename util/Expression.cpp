#include "Expression.hpp"

grammar::Expression::Expression(int value) : constant_(true), int_value_(value) {

}

grammar::Expression::Expression(const char *identifier) : constant_(false), str_value_(identifier) {

}

bool grammar::Expression::isConstant() {
    return constant_;
}

bool grammar::Expression::isIdentifier() {
    return !constant_;
}

grammar::Expression::~Expression() {
}

grammar::Expression::operator int() {
    if (constant_)
        return int_value_;
    else
        throw "Not a constant";
}

const char *grammar::Expression::toString() {
    return str_value_.c_str();
}
