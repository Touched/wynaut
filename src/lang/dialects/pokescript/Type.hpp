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

#ifndef WYNAUT_LANG_POKESCRIPT_TYPE_HPP_
#define WYNAUT_LANG_POKESCRIPT_TYPE_HPP_

#include "../../Type.hpp"

namespace lang {
    namespace pokescript {
        class Type : public lang::Type {
        public:
            enum Types {
                Variable,
                Bank,
                Buffer,
                Pointer,
                HiddenVar,
                Flag
            };

            Type(Types type, int value);

            virtual Types getType();

        protected:
            Types type_;
        };
    }
}

#endif /* WYNAUT_LANG_POKESCRIPT_TYPE_HPP_ */