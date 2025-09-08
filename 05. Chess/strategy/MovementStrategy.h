#include <Cell.h>

class MovementStrategy {
    public:
    virtual bool canMove(Cell& startingCell, Cell& endingCell, ChessBoard& board) = 0;
};