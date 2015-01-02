#ifndef WYNAUT_UTIL_EXPRESSION_HPP_
#define WYNAUT_UTIL_EXPRESSION_HPP_

#include <string>

namespace lang {
    class Expression {
    public:
        Expression(int value);

        Expression(const char *identifier);

        bool isConstant();

        bool isIdentifier();

        operator int();

        const char *toString();

        virtual ~Expression();

    private:
        bool constant_;
        std::string str_value_;
        int int_value_;
    };
}

#endif /* WYNAUT_UTIL_EXPRESSION_HPP_ */