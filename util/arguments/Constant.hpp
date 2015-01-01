#ifndef WYNAUT_UTIL_ARGUMENTS_CONSTANT_HPP_
#define WYNAUT_UTIL_ARGUMENTS_CONSTANT_HPP_

#include "../Argument.hpp"

namespace util {
    class Constant : public Argument {
    public:
        Constant();

        virtual ~Constant();
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_CONSTANT_HPP_ */