#include "ImportError.hpp"

lang::ImportError::ImportError(std::string const &module) : std::runtime_error(module), module_(module) {
}

lang::ImportError::~ImportError() {

}


const char *lang::ImportError::what() const throw() {
    return ("Unable to find module: " + module_).c_str();
}
