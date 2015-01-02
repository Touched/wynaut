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