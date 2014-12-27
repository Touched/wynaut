#ifndef WYNAUT_LANGUAGE_MODULE_HPP_
#define WYNAUT_LANGUAGE_MODULE_HPP_

#include <unordered_map>
#include <string>

#include "Function.hpp"

namespace lang {
    class Importer;

    /**
    * Produced by an importer object.
    */
    class Module {
        friend class lang::Importer;

    public:
        /**
        * Construct a new module with the given name.
        */
        Module(const char *name);

        virtual ~Module();

        const char *getName();

        lang::Function const &operator[](std::string const &key);

    protected:
        std::string name_;

        void add(lang::Function &fn);

        std::unordered_map<std::string, lang::Function> functions_;
    };
}

#endif