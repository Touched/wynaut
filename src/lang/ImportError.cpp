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

#include "ImportError.hpp"

lang::ImportError::ImportError(std::string const &module) : std::runtime_error(module), module_(module) {
}

lang::ImportError::~ImportError() {

}


const char *lang::ImportError::what() const throw() {
    return ("Unable to find module: " + module_).c_str();
}
