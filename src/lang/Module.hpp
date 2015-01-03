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

#ifndef WYNAUT_LANG_MODULE_HPP_
#define WYNAUT_LANG_MODULE_HPP_

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

#endif /* WYNAUT_LANG_MODULE_HPP_ */