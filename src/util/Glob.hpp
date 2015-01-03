#ifndef WYNAUT_UTIL_GLOB_HPP_
#define WYNAUT_UTIL_GLOB_HPP_

#include <string>
#include <list>

#include "path.hpp"

#if defined(__linux__)
    #include <glob.h>
#elif defined(_WIN32)
    // TODO: Implement win32 glob
    #error "No Windows implementation yet"
#endif

namespace util {
    class Glob {
    public:
        Glob(std::string const &pattern);

        ~Glob();

    private:
        std::list<util::Path*> paths_;
    };
}

#endif /* WYNAUT_UTIL_GLOB_HPP_ */