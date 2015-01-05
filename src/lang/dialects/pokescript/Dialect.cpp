#include <stdint-gcc.h>
#include "Dialect.hpp"
#include "../../../compiler/Blob.hpp"
#include "../../../compiler/Reference.hpp"
#include "../../Condition.hpp"

lang::pokescript::Dialect::~Dialect() {

}

lang::Type *lang::pokescript::Dialect::createType(const char *name, int value) {
    return new pokescript::Type(typeEnumFromString(name), value);
}

lang::ImportHandler *lang::pokescript::Dialect::importer(lang::ImporterContext &context) {
    return new ImportHandler(this, context);
}

void lang::pokescript::Dialect::gotoFragment(compiler::Fragment *where, compiler::Fragment *to) {
    // "goto" command has the index 0x5
    where->push_back(new compiler::Blob(5));

    // Reference target fragment
    where->push_back(new compiler::Reference(*to));
}

const char *lang::pokescript::Dialect::getName() const {
    return "pokescript";
}

void lang::pokescript::Dialect::conditionalJump(compiler::Fragment *where, lang::Condition *when, compiler::Fragment *to) {
    // Use the appropriate pokescript comparison function

    // Reverse the condition for easier comparison
    lang::Condition *inverse = when->opposite();

    char conditional = relationalOperatorFromEnum(when->getOperator());

    // Check the basic types of the lhs/rhs to use the appropriate comparison function
    if (when->lhs()->isIdentifier() && when->rhs()->isIdentifier()) {
        // Comparing two identifiers

        // Try LHS OP RHS
        if (!compare(where, when->lhs(), when->rhs())) {

            // Try the inverse comparison

            // Switch the operator
            conditional = relationalOperatorFromEnum(inverse->getOperator());
            if (!compare(where, when->rhs(), when->lhs())) {
                // TODO: Cannot compare these values
                throw "Error: Unsupported comparison";
            }
        }
    } else if (when->lhs()->isConstant() && when->rhs()->isConstant()) {
        // This can be done at compile time, using a goto command - here for the sake of completeness
        if (!compare(where, when->getOperator(), *when->lhs(), *when->rhs())) {
            // TODO: Cannot compare these values
            throw "Error: Unsupported comparison";
        }
    } else {
        // Comparing one identifier and one constant
        // Tries both ways

        if (when->lhs()->isIdentifier()) {
            if (!compare(where, when->lhs(), *when->rhs())) {
                throw "Error: Unsupported comparison";
            }
        } else {
            if (!compare(where, inverse->lhs(), *inverse->rhs())) {
                throw "Error: Unsupported comparison";
            }
        }
    }

    // We don't need the inverse object anymore
    delete inverse;

    // if1 command (if ... goto ...)
    // We don't use if2 (if ... call ...) as we don't want to overflow the call stack
    char if_binary[] = {7, conditional};
    where->push_back(new compiler::Blob(if_binary, sizeof(if_binary)));

    // Pointer to target piece
    where->push_back(new compiler::Reference(*to));
}

lang::pokescript::Type::Types lang::pokescript::Dialect::typeEnumFromString(std::string const &name) {
    if (name == "flag") return pokescript::Type::Flag;
    if (name == "var") return pokescript::Type::Variable;

    // TODO: ...

    // TODO: Throw exception (Unknown Identifier "name", or something)
    throw "Not a valid typename";
}

uint8_t lang::pokescript::Dialect::relationalOperatorFromEnum(lang::Condition::Operator op) {
    // Convert language operator enum to PokeScript enum

    switch (op) {
        case lang::Condition::Operator::EQ:
            return 1;
        case lang::Condition::Operator::NEQ:
            return 5;
        case lang::Condition::Operator::LT:
            return 0;
        case lang::Condition::Operator::LEQ:
            return 3;
        case lang::Condition::Operator::GT:
            return 2;
        case lang::Condition::Operator::GEQ:
            return 4;
        default:
            // TODO: Exception
            throw "Unable to compare";
    }
}

bool lang::pokescript::Dialect::compare(compiler::Fragment *where, lang::Expression *lhs, lang::Expression *rhs) {
    return false;
}

bool lang::pokescript::Dialect::compare(compiler::Fragment *where, lang::Expression *lhs, int rhs) {
    return false;
}

bool lang::pokescript::Dialect::compare(compiler::Fragment *where, lang::Condition::Operator op, int lhs, int rhs) {
    return false;
}
