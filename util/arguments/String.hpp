#ifndef WYNAUT_UTIL_ARGUMENTS_STRING_HPP_
#define WYNAUT_UTIL_ARGUMENTS_STRING_HPP_

#include <string>

#include "../Argument.hpp"

namespace util {
    class String : public Argument {
    public:
        String(const char *value);

        virtual ~String();

        virtual bool isString();

    protected:
        std::string data_;
    };
}

#endif /* WYNAUT_UTIL_ARGUMENTS_STRING_HPP_ */