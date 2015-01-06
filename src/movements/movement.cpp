#include <iostream>
#include "movement.hpp"

pokescript::Movement::Movement() : default_dir_(North), default_move_("walk") {
    clearState();
}

void pokescript::Movement::push(int val) {
    quanitity_ = val;
}

void pokescript::Movement::push(const char *val) {
    if (isDirection(val)) {
        direction_ = hashDirection(val);
    } else {
        movement_ = val;
    }
}

void pokescript::Movement::end() {
    if (direction_ == None) {
        // No direction specified, use the default one
        direction_ = default_dir_;
    } else {
        // We specified a direction, set the default to this one
        default_dir_ = direction_;
    }

    if (movement_ == "") {
        // Use Default movement type, as the user didn't specify one
        movement_ = default_move_;
    } else {
        // Possibly set the default movement
        setDefaultMove(movement_);
    }

    // Do something
    handleMovement(quanitity_, direction_, movement_);

    // Clean up
    clearState();
}

bool pokescript::Movement::isDirection(const char *name) {
    return false;
}

pokescript::Movement::Direction pokescript::Movement::hashDirection(std::string const &dir) {
    if (dir == "north")
        return North;

    if (dir == "south")
        return South;

    if (dir == "east")
        return East;

    if (dir == "west")
        return West;

    if (dir == "up")
        return North;

    if (dir == "down")
        return South;

    if (dir == "left")
        return West;

    if (dir == "right")
        return East;

    // TODO: Throw exception
    return None;
}

void pokescript::Movement::clearState() {
    direction_ = None;
    movement_ = "";
    quanitity_ = 0;
}

void pokescript::Movement::handleMovement(int qty, pokescript::Movement::Direction dir, std::string const &move) {
    std::cout << dir << " " << move << " " << qty << std::endl;
}

void pokescript::Movement::setDefaultMove(std::string const &move) {
    // TODO: Set the default movement
    // However, we must ignore some cases (wait, exclamation (?), etc.)
}
