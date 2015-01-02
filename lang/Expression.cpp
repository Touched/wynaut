#include "Expression.hpp"

lang::Expression::Expression(int value) : constant_(true), int_value_(value) {

}

lang::Expression::Expression(const char *identifier) : constant_(false), str_value_(identifier) {

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

const char *lang::Expression::toString() {
    return str_value_.c_str();
}
