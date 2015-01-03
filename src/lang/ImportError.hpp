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

#ifndef WYNAUT_LANG_IMPORTERROR_HPP_
#define WYNAUT_LANG_IMPORTERROR_HPP_

#include <stdexcept>

namespace lang {
    /**
    * An exception to be thrown when a module cannot be found by any of the registered importers.
    */
    class ImportError : public std::runtime_error {
    public:
        /**
        * Construct a new exception with the missing module's name.
        */
        explicit ImportError(std::string const &module);

        virtual ~ImportError();

        virtual const char *what() const throw();

    protected:
        std::string module_;
    };
}

#endif /* WYNAUT_LANG_IMPORTERROR_HPP_ */