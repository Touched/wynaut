#ifndef WYNAUT_COMPILER_PIECE_HPP_
#define WYNAUT_COMPILER_PIECE_HPP_

#include <iostream>

namespace compiler {
    /**
    * Polymorphic base class for components of a script fragment.
    */
    class Piece {
    public:
        Piece();

        /**
        * The actual output size of this piece
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