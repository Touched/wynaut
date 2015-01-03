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

#ifndef WYNAUT_COMPILER_PIECE_HPP_
#define WYNAUT_COMPILER_PIECE_HPP_

#include <iostream>

namespace compiler {
    /**
    * Polymorphic base class for the immutable components of a script fragment.
    */
    class Piece {
    public:
        Piece();

        /**
        * The actual output size of this piece. Must remain constant.
        */
        virtual size_t length() = 0;

        /**
        * Output the piece to a binary stream
        */
        virtual std::ostream &operator<<(std::ostream &out) = 0;

        virtual ~Piece();
    };
}

#endif /* WYNAUT_COMPILER_PIECE_HPP_ */