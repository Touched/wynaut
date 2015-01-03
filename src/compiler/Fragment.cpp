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

#include "Fragment.hpp"

compiler::Fragment::Fragment() {

}

compiler::Fragment::~Fragment() {
    for (std::deque<compiler::Piece *>::iterator it = pieces_.begin(); it != pieces_.end(); ++it) {
        delete *it;
    }
}

compiler::Piece *compiler::Fragment::front() {
    return pieces_.front();
}

compiler::Piece *compiler::Fragment::back() {
    return pieces_.back();
}

void compiler::Fragment::push_back(compiler::Piece *val) {
    pieces_.push_back(val);
}

void compiler::Fragment::push_front(compiler::Piece *val) {
    pieces_.push_front(val);
}

compiler::Piece *compiler::Fragment::pop_front() {
    compiler::Piece *p = pieces_.front();
    pieces_.pop_front();
    return p;
}

compiler::Piece *compiler::Fragment::pop_back() {
    compiler::Piece *p = pieces_.back();
    pieces_.pop_back();
    return p;
}
