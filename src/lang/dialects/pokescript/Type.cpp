#include "Type.hpp"

lang::pokescript::Type::Type(lang::pokescript::Type::Types type, int value) : lang::Type(value), type_(type) {

}

lang::pokescript::Type::Types lang::pokescript::Type::getType() {
    return type_;
}