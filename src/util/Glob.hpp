/*
This file is part of Wynaut.

Wynaut is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Wynaut is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wynaut.  If not, see <http://www.gnu.org/licenses/>.
*/

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