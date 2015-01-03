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

#ifndef WYNAUT_LANG_DIALECT_HPP_
#define WYNAUT_LANG_DIALECT_HPP_

#include "Type.hpp"
#include "Module.hpp"
#include "../compiler/Fragment.hpp"
#include "Condition.hpp"
#include "ImporterContext.hpp"
#include "ImportHandler.hpp"

namespace lang {
    class Dialect {
    public:
        Dialect();

        // TODO: Make these all pure virtuals

        virtual Type *createType(const char *name, int value);

        lang::ImportHandler *importer(lang::ImporterContext &context);

        virtual void gotoFragment(compiler::Fragment *where, compiler::Fragment *to);

        virtual const char *getName() const;

        virtual void conditionalJump(compiler::Fragment *where, lang::Condition when, compiler::Fragment *to);

    protected:
    };
}

#endif /* WYNAUT_LANG_DIALECT_HPP_ */