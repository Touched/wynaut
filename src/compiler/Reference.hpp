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

#ifndef WYNAUT_COMPILER_REFERENCE_HPP_
#define WYNAUT_COMPILER_REFERENCE_HPP_

#include "Fragment.hpp"

namespace compiler {
    /**
    * A piece of a script fragment containing a reference to another fragment.
    */
    class Reference : public compiler::Piece {
    public:
        Reference(compiler::Fragment &target);

        virtual ~Reference();
    };
}

#endif /* WYNAUT_COMPILER_REFERENCE_HPP_ */