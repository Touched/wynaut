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

#ifndef WYNAUT_UTIL_ARGUMENTS_HPP_
#define WYNAUT_UTIL_ARGUMENTS_HPP_

#include "Argument.hpp"

#include <vector>
#include <cstdlib>

#include "../lang/Type.hpp"

namespace lang {
    class Arguments {
    public:
        typedef std::vector<lang::Argument *>::iterator iterator;

        Arguments();

        Arguments(size_t n);

        ~Arguments();

        void add(const char *value);

        void add(int value);

        void add(lang::Type *type);

        void add(lang::Argument *arg);

        iterator begin();

        iterator end();

        size_t size();

        lang::Argument *operator[](size_t index);

        lang::Argument *at(size_t index);

        lang::Argument *front();

        lang::Argument *back();

    protected:
        std::vector<lang::Argument *> args_;
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_HPP_ */