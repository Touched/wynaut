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

#include "ImportHandler.hpp"
#include "ImportError.hpp"

std::vector<lang::ImportHandler::ImporterFactory> lang::ImportHandler::registered_importers_;

void lang::ImportHandler::registerImporter(ImporterFactory method) {
    // Add an importer factory method
    registered_importers_.push_back(method);
}

lang::ImportHandler::ImportHandler(lang::Dialect *dialect, lang::ImporterContext &context) {
    // Create new importers using the given context
    for (std::vector<ImporterFactory>::iterator fn = registered_importers_.begin(); fn != registered_importers_.end(); ++fn) {
        importers_.push_back((*fn)(dialect, context));
    }
}

lang::ImportHandler::~ImportHandler() {
    // Free all the handler's registered importers
    for (std::vector<Importer *>::iterator it = importers_.begin(); it != importers_.end(); ++it) {
        delete *it;
    }
}

lang::Module *lang::ImportHandler::import(std::string const &name) {
    lang::Module *found;
    for (std::vector<Importer *>::iterator it = importers_.begin(); it != importers_.end(); ++it) {
        // Attempt to import a module using this importer
        found = (*it)->import(name);

        if (found != nullptr) {
            // The current importer returned a valid module, so stop searching
            return found;
        }
    }

    // No module found
    throw lang::ImportError(name);
}
