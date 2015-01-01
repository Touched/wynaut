#include "Expression.hpp"

util::Expression::Expression(int value) : constant_(true), int_value_(value) {

}

util::Expression::Expression(const char *identifier) : constant_(false), str_value_(identifier) {

}

bool util::Expression::isConstant() {
    return constant_;
}

bool util::Expression::isIdentifier() {
    return !constant_;
}

util::Expression::~Expression() {
}

util::Expression::operator int() {
    if (constant_)
        return int_value_;
    else
        throw "Not a constant";
}

const char *util::Expression::toString() {
    return str_value_.c_str();
}
