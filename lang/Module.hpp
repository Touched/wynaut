#ifndef WYNAUT_LANGUAGE_MODULE_HPP_
#define WYNAUT_LANGUAGE_MODULE_HPP_

#include <map>
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

        virtual const char *getName();

        virtual bool exists(std::string const &key);

        virtual lang::Function *operator[](std::string const &key);

    protected:
        std::string name_;

        void add(lang::Function *fn);

        std::map<std::string, lang::Function*> functions_;
    };
}

#endif