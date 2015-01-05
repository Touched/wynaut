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

#include "Script.hpp"
#include "../lang/dialects/pokescript/Dialect.hpp"

compiler::Script::Script() : dialect_(nullptr) {
}

void compiler::Script::import(std::string const &name) {
    std::cout << "Importing " << name << std::endl;

    //modules_[name] = getImporter()->import(name);
    modules_[name] = new lang::Module("foo");
}

compiler::Script::~Script() {
    // Free up all fragments that we allocated
    for (std::vector<Fragment *>::iterator it = fragments_.begin(); it != fragments_.end(); ++it) {
        delete *it;
    }

    // Clean up symbols (allocated types)
    for (std::map<std::string, lang::Type *>::iterator it = symbols_.begin(); it != symbols_.end(); ++it) {
        delete it->second;
    }
}

void compiler::Script::declare(std::string const &name, std::string const &type, int value) {
    // Use the dialect as a Type factory
    std::cout << "Declaring " << name << " of type " << type << " with value " << value << std::endl;

    symbols_[name] = getDialect()->createType(type.c_str(), value);
}

int compiler::Script::resolveConstant(const char *identifier) {
    throw "Identifier is not a constant";
}

void compiler::Script::handleFunction(const char *module, const char *function, lang::Arguments &args) {
    std::cout << "Calling " << module << "::" << function << " with " << args.size() << " arguments" << std::endl;

    if (modules_.count(module)) {
        if (modules_[module]->exists(function)) {
            lang::Module &m = *modules_[module];
            m[function]->compile(this, args);
        } else {
            std::cout << "Function '" << function << "' is not a member of module '" << module << "'" << std::endl;
        }
    } else {
        std::cout << "Undefined module " << module << std::endl;
    }
}

void compiler::Script::handleFunction(const char *function, lang::Arguments &args) {
    std::cout << "Calling " << function << " with " << args.size() << " arguments" << std::endl;
}

void compiler::Script::handleIf(lang::Condition &condition) {
    // Store the current fragment to place branch statements inside it, and then jump to the new fragment
    if_fragment_.push(current_fragment_.top());

    // Don't need the old current fragment, as it was moved onto the if_fragment stack
    current_fragment_.pop();

    // Create a fragment to resume execution at; this will take the place of the old current fragment
    current_fragment_.push(newFragment());

    // Set a new fragment as the current fragment so we can put the body of the if inside it
    current_fragment_.push(newFragment());

    // Dialect will handle the actual IF part
    getDialect()->conditionalJump(if_fragment_.top(), &condition, current_fragment_.top());
}

void compiler::Script::handleElseIf(lang::Condition &condition) {
    // Pop the body fragment
    Fragment *body = current_fragment_.top();
    current_fragment_.pop();

    // Return the the continuation fragment
    getDialect()->gotoFragment(body, current_fragment_.top());

    // Replace IF body fragment with the ELSEIF body fragment
    current_fragment_.push(newFragment());

    // Create the jump to the current fragment if 'condition' is true
    getDialect()->conditionalJump(if_fragment_.top(), &condition, current_fragment_.top());
}

void compiler::Script::handleElse() {
    // Pop the body fragment
    Fragment *body = current_fragment_.top();
    current_fragment_.pop();

    // Return the the continuation fragment
    getDialect()->gotoFragment(body, current_fragment_.top());

    // Replace IF body fragment with the ELSE body fragment
    current_fragment_.push(newFragment());

    // Create the jump to the current fragment (unconditional jump)
    getDialect()->gotoFragment(if_fragment_.top(), current_fragment_.top());
}

void compiler::Script::handleEndIf() {
    // Finished adding the body of the IF, remove its fragment from the stack
    Fragment *body = current_fragment_.top();
    current_fragment_.pop();

    // Use the dialect to return the the appropriate fragment
    getDialect()->gotoFragment(body, current_fragment_.top());

    // Handle any conditons that fall through
    // TODO: Compiler Optimisation: Don't do this if the is an ELSE statement
    getDialect()->gotoFragment(if_fragment_.top(), current_fragment_.top());

    // Finished this IF block, so pop off the item from the stack
    if_fragment_.pop();
}

void compiler::Script::handleWhile(lang::Condition &condition) {

}

void compiler::Script::handleEndWhile() {

}

lang::Dialect *compiler::Script::getDialect() {
    if (dialect_ == nullptr) {
        // Allocate the default dialect - none was chosen
        dialect_ = new lang::pokescript::Dialect();
    }
    return dialect_;
}

compiler::Fragment *compiler::Script::newFragment() {
    fragments_.push_back(new Fragment());

    // Return the newly allocated fragment
    return fragments_.back();
}

void compiler::Script::handleSubroutine(const char *name, std::vector<std::string> *parameters) {
    // TODO: Does the dialect support parameters?
    // if (!getDialect()->supports(lang::Dialect::Feature::FunctionParameters)) throw "Dialect doesn't support this";

    current_fragment_.push(newFragment());
}

lang::ImportHandler *compiler::Script::getImporter() {
    if (importer_ == nullptr) {
        importer_ = getDialect()->importer(*context_);
    }
    return importer_;
}

compiler::Fragment *compiler::Script::current() {
    if (current_fragment_.size()) {
        return current_fragment_.top();
    }
    return nullptr;
}

lang::Type *compiler::Script::resolveType(const char *identifier) {
    // Throw exception if symbol is undefined

    // TODO: Catch and throw our own "Undefined Symbol" exception
    return symbols_.at(identifier);
}
