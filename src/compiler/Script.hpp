/*
This file is part of Wynaut.

Wynaut is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Wynaut is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wynaut.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef WYNAUT_COMPILER_SCRIPT_HPP_
#define WYNAUT_COMPILER_SCRIPT_HPP_

#include <map>
#include <string>
#include <stack>

#include "Fragment.hpp"
#include "../lang/Dialect.hpp"
#include "../lang/ImporterContext.hpp"
#include "../lang/ImportHandler.hpp"
#include "../lang/Arguments.hpp"
#include "../lang/Condition.hpp"

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

        lang::Type *resolveType(const char *identifier);

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