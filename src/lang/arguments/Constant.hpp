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

#ifndef WYNAUT_LANG_ARGUMENTS_CONSTANT_HPP_
#define WYNAUT_LANG_ARGUMENTS_CONSTANT_HPP_

#include <slang.h>
#include "../Argument.hpp"

namespace lang {
    class Constant : public Argument {
    public:
        Constant(int value);

        virtual ~Constant();

        virtual bool isConstant();

    protected:
        int data_;
    };
}

#endif /* WYNAUT_LANG_ARGUMENTS_CONSTANT_HPP_ */