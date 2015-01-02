#ifndef WYNAUT_LANGUAGE_IMPORTHANDLER_HPP_
#define WYNAUT_LANGUAGE_IMPORTHANDLER_HPP_

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

#endif /* WYNAUT_LANGUAGE_IMPORTHANDLER_HPP_ */
