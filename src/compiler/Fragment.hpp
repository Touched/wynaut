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