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

#ifndef WYNAUT_COMPILER_FRAGMENT_HPP_
#define WYNAUT_COMPILER_FRAGMENT_HPP_

#include <deque>

#include "Piece.hpp"

namespace compiler {
    /**
    * Class representing a script fragment. It will contain various pieces which will eventually combine to form a
    * compiled script.
    */
    class Fragment {
    public:
        Fragment();

        virtual ~Fragment();

    protected:
        std::deque<compiler::Piece *> pieces_;
    };
}

#endif /* WYNAUT_COMPILER_FRAGMENT_HPP_ */