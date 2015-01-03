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

#ifndef WYNAUT_LANG_IMPORTHANDLER_HPP_
#define WYNAUT_LANG_IMPORTHANDLER_HPP_

#include <vector>
#include <string>

#include "Importer.hpp"

namespace lang {
    class Dialect;

    class ImportHandler {
    public:
        /**
        * Importer factory method function pointer
        */
        typedef lang::Importer *(*ImporterFactory)(lang::Dialect *dialect, lang::ImporterContext &);

        /**
        * Construct a new import handler given a context. It uses all the registered importers.
        */
        ImportHandler(lang::Dialect *dialect, lang::ImporterContext &context);

        virtual ~ImportHandler();

        /**
        * Register an importer for use. Uses the pointer to the imports static factory method to construct new importers
        * of the given type.
        */
        static void registerImporter(ImporterFactory method);

        /**
        * Attempts to import a module using all the importers registered to the handler.
        */
        lang::Module *import(std::string const &name);

    protected:
        static std::vector<ImporterFactory> registered_importers_;
        std::vector<lang::Importer *> importers_;
    };
};

#endif /* WYNAUT_LANG_IMPORTHANDLER_HPP_ */
