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

namespace lang {
    class Expression {
    public:
        Expression(int value);

        Expression(const char *identifier);

        bool isConstant();

        bool isIdentifier();

        operator int();

        const char *toString();

        virtual ~Expression();

    private:
        bool constant_;
        std::string str_value_;
        int int_value_;
    };
}

#endif /* WYNAUT_LANG_EXPRESSION_HPP_ */