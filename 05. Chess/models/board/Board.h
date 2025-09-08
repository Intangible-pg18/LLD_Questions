#include <Move.h>

class Board {
    public:
        virtual void display() = 0;
        virtual void applyMove(Move& move) = 0;
        virtual void setPiece(unique_ptr<IChessPiece> piece, int row, char col) = 0;
};