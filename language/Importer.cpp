#include "Importer.hpp"

lang::Importer::Importer(ImporterContext &context) : context_(context) {
}

lang::Importer::~Importer() {
}

lang::Module *lang::Importer::import(std::string const &name) {
    return nullptr;
}

lang::Importer *lang::Importer::create(lang::ImporterContext &context) {
    return new lang::Importer(context);
}
