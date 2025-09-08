#include <Cell.h>
#include <MovementStrategy.h>

class DiagonalMovementStrategy : public MovementStrategy{
    public:
    bool canMove(Cell& start, Cell& end, ChessBoard& board) {
        return true;
    }
};