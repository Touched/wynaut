#include "Constant.hpp"

lang::Constant::Constant(int value) : data_(value) {

}

lang::Constant::~Constant() {

}

bool lang::Constant::isConstant() {
    return true;
}
