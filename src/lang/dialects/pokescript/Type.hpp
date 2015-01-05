#ifndef WYNAUT_LANG_POKESCRIPT_TYPE_HPP_
#define WYNAUT_LANG_POKESCRIPT_TYPE_HPP_

#include "../../Type.hpp"

namespace lang {
    namespace pokescript {
        class Type : public lang::Type {
        public:
            enum Types {
                Variable,
                Bank,
                Buffer,
                Pointer,
                HiddenVar,
                Flag
            };

            Type(Types type, int value);

            virtual Types getType();

        protected:
            Types type_;
        };
    }
}

#endif /* WYNAUT_LANG_POKESCRIPT_TYPE_HPP_ */