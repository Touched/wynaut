#include "ImportHandler.hpp"
#include "ImportError.hpp"

std::vector<lang::ImportHandler::ImporterFactory> lang::ImportHandler::registered_importers_;

void lang::ImportHandler::registerImporter(ImporterFactory method) {
    // Add an importer factory method
    registered_importers_.push_back(method);
}

lang::ImportHandler::ImportHandler(const char *path, lang::ImporterContext &context) {
    // Create new importers using the given context
    for (std::vector<ImporterFactory>::iterator fn = registered_importers_.begin(); fn != registered_importers_.end(); ++fn) {
        importers_.push_back((*fn)(path, context));
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

        if (found) {
            // The current importer returned a valid module, so stop searching
            return found;
        }
    }

    // No module found
    throw lang::ImportError(name);
}
