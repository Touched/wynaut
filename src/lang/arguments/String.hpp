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

#ifndef WYNAUT_LANG_ARGUMENTS_STRING_HPP_
#define WYNAUT_LANG_ARGUMENTS_STRING_HPP_

#include <string>

#include "../Argument.hpp"

namespace lang {
    class String : public Argument {
    public:
        String(const char *value);

        virtual ~String();

        virtual bool isString();

    protected:
        std::string data_;
    };
}

#endif /* WYNAUT_LANG_ARGUMENTS_STRING_HPP_ */