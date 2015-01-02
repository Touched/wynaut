#ifndef WYNAUT_COMPILER_SCRIPT_HPP_
#define WYNAUT_COMPILER_SCRIPT_HPP_

#include <map>
#include <string>
#include <stack>

#include "Fragment.hpp"
#include "../language/Dialect.hpp"
#include "../language/ImporterContext.hpp"
#include "../language/ImportHandler.hpp"
#include "../language/Arguments.hpp"
#include "../language/Condition.hpp"

namespace compiler {
    /**
    * Polymorphic base class for the immutable components of a script fragment.
    */
    class Script {
    friend class lang::Function;

    public:
        Script();

        typedef std::vector<compiler::Piece> Pieces;

        void import(std::string const &name);

        //void call(std::string const &name, std::string const &type, Args);

        void declare(std::string const &name, std::string const &type, int value);

        int resolveConstant(const char *identifier);

        virtual ~Script();

        void handleSubroutine(const char *name, std::vector<std::string> *parameters);

        void handleIf(lang::Condition &condition);

        void handleElseIf(lang::Condition &condition);

        void handleElse();

        void handleEndIf();

        void handleWhile(lang::Condition &condition);

        void handleEndWhile();

        void handleFunction(const char *module, const char *function, lang::Arguments &args);

        void handleFunction(const char *function, lang::Arguments &args);

        Fragment *current();

    protected:
        lang::Dialect *dialect_;
        lang::ImporterContext *context_;

        lang::ImportHandler *importer_;

        std::vector<Fragment *> fragments_;

        // Fragment LIFO stacks - these track nested control flow statements
        std::stack<Fragment *> if_fragment_, current_fragment_;
        std::map<std::string, lang::Type *> symbols_;

        std::map<std::string, lang::Module *> modules_;

        // Wrapper for accessing the dialect (in case it isn't set)
        lang::Dialect *getDialect();

        // Importer access wrapper
        lang::ImportHandler *getImporter();

        // Wrapper for creating a new fragment (allows keeping track of all fragments)
        Fragment *newFragment();
    };
}

#endif /* WYNAUT_COMPILER_SCRIPT_HPP_ */