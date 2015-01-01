#ifndef WYNAUT_COMPILER_SCRIPT_HPP_
#define WYNAUT_COMPILER_SCRIPT_HPP_

#include <map>
#include <string>
#include <stack>

#include "Fragment.hpp"
#include "../language/Dialect.hpp"
#include "../language/ImporterContext.hpp"
#include "../language/ImportHandler.hpp"

namespace compiler {
    /**
    * Polymorphic base class for the immutable components of a script fragment.
    */
    class Script {
    public:
        Script();

        typedef std::vector<compiler::Piece> Pieces;

        void import(std::string const &name);

        //void call(std::string const &name, std::string const &type, Args);

        void declare(std::string const &name, std::string const &type, int value);

        int resolveConstant(const char *identifier);

        virtual ~Script();

        void handleIf();

        void handleElseIf();

        void handleElse();

        void handleWhile();

        void handleExpression();

        void handleFunction();

    protected:
        lang::Dialect *dialect_;
        lang::ImporterContext *context_;

        std::map<std::string, lang::Type *> symbols_;
        std::map<std::string, lang::Module *> modules_;
    };
}

#endif /* WYNAUT_COMPILER_SCRIPT_HPP_ */