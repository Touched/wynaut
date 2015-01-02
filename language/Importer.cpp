#include "Importer.hpp"

lang::Importer::Importer(lang::Dialect *dialect, ImporterContext &context) : context_(context), dialect_(dialect) {
}

lang::Importer::~Importer() {
}

lang::Module *lang::Importer::import(std::string const &name) {
    return nullptr;
}

lang::Importer *lang::Importer::create(lang::Dialect *dialect, lang::ImporterContext &context) {
    return new lang::Importer(dialect, context);
}
