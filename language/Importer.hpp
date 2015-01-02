#ifndef WYNAUT_LANGUAGE_IMPORTER_HPP_
#define WYNAUT_LANGUAGE_IMPORTER_HPP_

#include <string>
#include "ImporterContext.hpp"
#include "Module.hpp"
#include "Dialect.hpp"

namespace lang {
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

#endif /* WYNAUT_LANGUAGE_IMPORTER_HPP_ */