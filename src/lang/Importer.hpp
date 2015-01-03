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

#ifndef WYNAUT_LANG_IMPORTER_HPP_
#define WYNAUT_LANG_IMPORTER_HPP_

#include <string>
#include "ImporterContext.hpp"
#include "Module.hpp"

namespace lang {
    class Dialect;

    /**
    * Polymorphic base class for an importer - a factory which produces lang::Module objects given a string identifier
    * and a context.
    */
    class Importer {
    public:
        /**
        * Construct an importer within the given context.
        */
        Importer(lang::Dialect *dialect, lang::ImporterContext &context);

        virtual ~Importer();

        /**
        * Find a module with the given name. Should return nullptr if this importer cannot handle or find this module.
        */
        virtual lang::Module *import(std::string const &name);

        /**
        * Factory method for producing an importer.
        */
        static lang::Importer *create(lang::Dialect *dialect, lang::ImporterContext &context);

    protected:
        lang::ImporterContext &context_;
        lang::Dialect *dialect_;
    };
}

#endif /* WYNAUT_LANG_IMPORTER_HPP_ */