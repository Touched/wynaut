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

#include <string.h>
#include <iomanip>
#include "Blob.hpp"

compiler::Blob::~Blob() {
}

size_t compiler::Blob::length() {
    return data_.size();
}

compiler::Blob::Blob(const char *data, size_t len) : data_(len) {
    memcpy(&data_[0], data, len);
}

compiler::Blob::Blob(int value) : data_(1) {
    memcpy(&data_[0], &value, 1);
}

compiler::Blob::Blob() {

}

compiler::Blob &compiler::Blob::operator<<(uint8_t i) {
    data_.push_back(i);
    return *this;
}

std::ostream &compiler::Blob::stream_out(std::ostream &out) const {
    out << "[ ";
    for (auto it = data_.begin(); it != data_.end(); ++it, out << " ") {
        out << "0x" << std::hex << std::setfill('0') << std::setw(2) << ((*it) & 0xFF);
    }
    return out << "]";
}
