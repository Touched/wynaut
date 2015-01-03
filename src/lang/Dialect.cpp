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

#include "Dialect.hpp"

lang::Type *lang::Dialect::createType(const char *name, int value) {
}

lang::Dialect::Dialect() {
}

void lang::Dialect::gotoFragment(compiler::Fragment *where, compiler::Fragment *to) {

}

void lang::Dialect::conditionalJump(compiler::Fragment *where, lang::Condition when, compiler::Fragment *to) {

}

lang::ImportHandler *lang::Dialect::importer(lang::ImporterContext &context) {
    // TODO: Change path to be read from an import handler

    return new ImportHandler(this, context);
}

const char *lang::Dialect::getName() const {
    return "default";
}
