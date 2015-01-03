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

#include <sys/wait.h>
#include <printf.h>
#include <string.h>
#include "Blob.hpp"

compiler::Blob::~Blob() {
    delete[] data_;
}

size_t compiler::Blob::length() {
    return 0;
}

compiler::Blob::Blob(const char *data, size_t len) : length_(len) {
    data_ = new char[len];
    memcpy(data_, data, len);
}

std::ostream &compiler::Blob::operator<<(std::ostream &out) {
    return out;
}
