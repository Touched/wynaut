#include "Script.hpp"

compiler::Script::Script() : dialect_(NULL) {

}

void compiler::Script::import(std::string const &name) {

}

compiler::Script::~Script() {

}

void compiler::Script::declare(std::string const &name, std::string const &type, int value) {

}

int compiler::Script::resolveConstant(const char *identifier) {
    throw "Identifier is not a constant";
}
