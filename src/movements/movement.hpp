#ifndef WYNAUT_MOVEMENTS_MOVEMENT_HPP_
#define WYNAUT_MOVEMENTS_MOVEMENT_HPP_

namespace pokescript {
    class Movement {
    public:
        enum Direction {
            None,
            North,
            South,
            East,
            West,
            NorthWest,
            SouthWest,
            NorthEast,
            SouthEast
        };

        Movement();

        void push(int val);

        void push(const char *val);

        void end();

    private:
        bool isDirection(const char *name);

        void handleMovement(int qty, Direction dir, std::string const &move);

        void setDefaultMove(std::string const &move);

        void clearState();

        Direction hashDirection(std::string const &dir);

        std::string movement_, default_move_;
        Direction direction_, default_dir_;

        int quanitity_;
    };
}

#endif /* WYNAUT_MOVEMENTS_MOVEMENT_HPP_ */