#include <iostream>
#include <cstring>
#include <algorithm>

#include "movement.hpp"

pokescript::Movement::Movement() : default_dir_(North), default_move_("walk") {
    clearState();
}

void pokescript::Movement::feed(int val) {
    quanitity_ = val;
}

void pokescript::Movement::feed(const char *val) {
    // Convert to lowercase
    std::string data(val);

    std::transform(data.begin(), data.end(), data.begin(), ::tolower);

    // We can't know whether this identifier is a direction or movement yet. Only the possible directions are known,
    // so check if it is one. If it isn't, it must be a movement.
    Direction tmp = hashDirection(data);

    if (tmp != None) {
        direction_ = tmp;
    } else {
        movement_ = data;
    }
}

void pokescript::Movement::end() {
    if (movement_ == "") {
        // Use Default movement type, as the user didn't specify one
        movement_ = default_move_;
    } else {
        // Possibly set the default movement
        setDefaultMove(movement_);
    }

    if (!needsDirection(movement_) && direction_ != None) {
        // TODO: Throw error
        throw "Don't specifiy a direction";
    }

    if (direction_ == None) {
        // No direction specified, use the default one
        direction_ = default_dir_;
    } else {
        // We specified a direction, set the default to this one
        default_dir_ = direction_;
    }

    // Do something
    handleMovement(quanitity_, direction_, movement_);

    // Clean up
    clearState();
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

    // TODO: ...

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

bool pokescript::Movement::needsDirection(std::string const &move) {
    if (move == "wait")
        return false;
    if (move == "exclamation")
        return false;

    // TODO: ...

    return true;
}
