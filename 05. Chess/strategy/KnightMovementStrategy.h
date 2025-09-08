#include <Cell.h>
#include <MovementStrategy.h>

class KnightMovementStrategy : public MovementStrategy{
    public:
    bool canMove(Cell& start, Cell& end, ChessBoard& board) {
        return true;
    }
};