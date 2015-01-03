#include <glob.h>
#include <stdexcept>
#include "Glob.hpp"

util::Glob::Glob(std::string const &pattern) {
#if defined(__linux__)
    glob_t result;
    switch (glob(pattern.c_str(), GLOB_TILDE, NULL, &result)) {
        case GLOB_NOSPACE:
            throw std::bad_alloc();
        case GLOB_ABORTED:
            throw std::runtime_error("Inusfficient permissions");
        case GLOB_NOMATCH:
            break;
        default:
            for (size_t i = 0; i < result.gl_pathc; ++i) {
                paths_.push_back(new util::Path(result.gl_pathv[i]));
            }
    }
    globfree(&result);
#endif
}

util::Glob::~Glob() {
    for (std::list<util::Path *>::iterator it = paths_.begin(); it != paths_.end(); ++it) {
        delete *it;
    }
}
