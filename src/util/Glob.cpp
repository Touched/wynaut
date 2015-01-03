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
                //paths_.push_back(new util::Path(result.gl_pathv[i]));
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
