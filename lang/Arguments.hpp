#ifndef WYNAUT_UTIL_ARGUMENTS_HPP_
#define WYNAUT_UTIL_ARGUMENTS_HPP_

#include "Argument.hpp"

#include <vector>
#include <cstdlib>

#include "../lang/Type.hpp"

namespace lang {
    class Arguments {
    public:
        typedef std::vector<lang::Argument *>::iterator iterator;

        Arguments();

        Arguments(size_t n);

        ~Arguments();

        void add(const char *value);

        void add(int value);

        void add(lang::Type *type);

        void add(lang::Argument *arg);

        iterator begin();

        iterator end();

        size_t size();

        lang::Argument *operator[](size_t index);

        lang::Argument *at(size_t index);

        lang::Argument *front();

        lang::Argument *back();

    protected:
        std::vector<lang::Argument *> args_;
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_HPP_ */