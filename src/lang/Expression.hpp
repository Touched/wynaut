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

#ifndef WYNAUT_LANG_EXPRESSION_HPP_
#define WYNAUT_LANG_EXPRESSION_HPP_

#include <string>
#include "Type.hpp"

namespace lang {
    class Expression {
    public:
        Expression(int value);

        Expression(lang::Type *type);

        bool isConstant();

        bool isIdentifier();

        operator int();

        lang::Type *getType();

        virtual ~Expression();

    private:
        bool constant_;
        lang::Type *type_;
        int int_value_;
    };
}

#endif /* WYNAUT_LANG_EXPRESSION_HPP_ */