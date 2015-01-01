#ifndef WYNAUT_UTIL_ARGUMENTS_HPP_
#define WYNAUT_UTIL_ARGUMENTS_HPP_

#include "Argument.hpp"

#include <vector>
#include <cstdlib>

#include "../language/Type.hpp"

namespace util {
    class Arguments {
    public:
        typedef std::vector<util::Argument *>::iterator iterator;

        Arguments();

        Arguments(size_t n);

        ~Arguments();

        void add(const char *value);

        void add(int value);

        void add(lang::Type *type);

        iterator begin();

        iterator end();

        size_t size();

        util::Argument *operator[](size_t index);

        util::Argument *at(size_t index);

        util::Argument *front();

        util::Argument *back();

    protected:
        std::vector<util::Argument *> args_;
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_HPP_ */