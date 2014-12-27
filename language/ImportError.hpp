#ifndef WYNAUT_LANGUAGE_IMPORTERROR_HPP_
#define WYNAUT_LANGUAGE_IMPORTERROR_HPP_

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

#endif /* WYNAUT_LANGUAGE_IMPORTERROR_HPP_ */