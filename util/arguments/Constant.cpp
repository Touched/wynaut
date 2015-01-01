#include "Constant.hpp"

util::Constant::Constant(int value) : data_(value) {

}

util::Constant::~Constant() {

}

bool util::Constant::isConstant() {
    return true;
}
