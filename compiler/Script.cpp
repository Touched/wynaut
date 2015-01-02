#include "Script.hpp"

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
}

void compiler::Script::declare(std::string const &name, std::string const &type, int value) {
    // Lookup type and get its factory method
}

int compiler::Script::resolveConstant(const char *identifier) {
    throw "Identifier is not a constant";
}

void compiler::Script::handleFunction(const char *module, const char *function, util::Arguments &args) {
    std::cout << "Calling " << module << "::" << function << " with " << args.size() << " arguments" << std::endl;

    if (modules_.count(module)) {
        if (modules_[module]->exists(function)) {

        } else {
            std::cout << "Function '" << function << "' is not a member of module '" << module << "'" << std::endl;
        }
    } else {
        std::cout << "Undefined module " << module << std::endl;
    }
}

void compiler::Script::handleFunction(const char *function, util::Arguments &args) {
    std::cout << "Calling " << function << " with " << args.size() << " arguments" << std::endl;
}

void compiler::Script::handleIf(util::Condition &condition) {
    // Store the current fragment to place branch statements inside it, and then jump to the new fragment
    if_fragment_.push(current_fragment_.top());

    // Don't need the old current fragment, as it was moved onto the if_fragment stack
    current_fragment_.pop();

    // Create a fragment to resume execution at; this will take the place of the old current fragment
    current_fragment_.push(newFragment());

    // Set a new fragment as the current fragment so we can put the body of the if inside it
    current_fragment_.push(newFragment());

    // Dialect will handle the actual IF part
    //getDialect()->conditionalJump(if_fragment_.top(), condition, current_fragment_.top());
}

void compiler::Script::handleElseIf(util::Condition &condition) {
    // Pop the body fragment
    Fragment *body = current_fragment_.top();
    current_fragment_.pop();

    // Return the the continuation fragment
    //getDialect()->gotoFragment(body, current_fragment_.top());

    // Replace IF body fragment with the ELSEIF body fragment
    current_fragment_.push(newFragment());

    // Create the jump to the current fragment if 'condition' is true
    //getDialect()->conditionalJump(if_fragment_.top(), condition, current_fragment_.top());
}

void compiler::Script::handleElse() {
    // Pop the body fragment
    Fragment *body = current_fragment_.top();
    current_fragment_.pop();

    // Return the the continuation fragment
    //getDialect()->gotoFragment(body, current_fragment_.top());

    // Replace IF body fragment with the ELSE body fragment
    current_fragment_.push(newFragment());

    // Create the jump to the current fragment (unconditional jump)
    //getDialect()->gotoFragment(if_fragment_.top(), current_fragment_.top());
}

void compiler::Script::handleEndIf() {
    // Finished adding the body of the IF, remove its fragment from the stack
    Fragment *body = current_fragment_.top();
    current_fragment_.pop();

    // Use the dialect to return the the appropriate fragment
    //getDialect()->gotoFragment(body, current_fragment_.top());

    // Handle any conditons that fall through
    // TODO: Compiler Optimisation: Don't do this if the is an ELSE statement
    //getDialect()->gotoFragment(if_fragment_.top(), current_fragment_.top());

    // Finished this IF block, so pop off the item from the stack
    if_fragment_.pop();
}

void compiler::Script::handleWhile(util::Condition &condition) {

}

void compiler::Script::handleEndWhile() {

}

lang::Dialect *compiler::Script::getDialect() {
    if (dialect_ == nullptr) {
        // Allocate the default dialect - none was chosen
        dialect_ = new lang::Dialect();
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
