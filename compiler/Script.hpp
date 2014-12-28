#ifndef WYNAUT_COMPILER_SCRIPT_HPP_
#define WYNAUT_COMPILER_SCRIPT_HPP_

#include <map>
#include <string>

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

        void add_fragment(Pieces &piece);

        template<class InputIterator>
        void add_fragment(InputIterator first, InputIterator last);

        void import(std::string const &name);

        void declare(std::string const &name, int value);

        // void handle_if(std::string const &lhs, T const &rhs);
        // void handle_while();
        // void handle_elif();
        // void handle_else();

        virtual ~Script();

    protected:
        lang::Dialect &dialect_;
        lang::ImporterContext *context_;

        std::stack<compiler::Fragment *> fragment_stack_;
        std::list<compiler::Fragment &> associated_fragments_;

        std::map<std::string, lang::Type *> symbols_;
        std::map<std::string, lang::Module *> modules_;
    };
}

#endif /* WYNAUT_COMPILER_SCRIPT_HPP_ */