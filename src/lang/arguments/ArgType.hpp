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

#ifndef WYNAUT_LANG_ARGUMENTS_TYPE_HPP_
#define WYNAUT_UTIL_ARGUMENTS_TYPE_HPP_

#include "../Argument.hpp"
#include "../../lang/Type.hpp"

namespace lang {
    class ArgType : public Argument {
    public:
        ArgType(lang::Type *value);

        virtual bool isIdentifier();

        virtual ~ArgType();

    protected:
        lang::Type *data_;
    };
}

#endif /* WYNAUT_LANG_ARGUMENTS_TYPE_HPP_ */