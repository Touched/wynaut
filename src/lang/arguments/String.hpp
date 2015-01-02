#ifndef WYNAUT_LANG_ARGUMENTS_STRING_HPP_
#define WYNAUT_LANG_ARGUMENTS_STRING_HPP_

#include <string>

#include "../Argument.hpp"

namespace lang {
    class String : public Argument {
    public:
        String(const char *value);

        virtual ~String();

        virtual bool isString();

    protected:
        std::string data_;
    };
}

#endif /* WYNAUT_LANG_ARGUMENTS_STRING_HPP_ */