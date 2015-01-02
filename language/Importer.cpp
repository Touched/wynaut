#include "Importer.hpp"

lang::Importer::Importer(const char *path, ImporterContext &context) : context_(context), path_(path) {
}

lang::Importer::~Importer() {
}

lang::Module *lang::Importer::import(std::string const &name) {
    return nullptr;
}

lang::Importer *lang::Importer::create(const char *path, lang::ImporterContext &context) {
    return new lang::Importer(path, context);
}
