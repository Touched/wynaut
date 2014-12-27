#ifndef WYNAUT_COMPILER_BLOB_HPP_
#define WYNAUT_COMPILER_BLOB_HPP_

#include "Piece.hpp"

namespace compiler {
    /**
    * A piece of a script fragment containing raw binary.
    */
    class Blob : public Piece {
    public:
        Blob();

        virtual ~Blob();
    };
}

#endif /* WYNAUT_COMPILER_BLOB_HPP_ */