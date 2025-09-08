#include <Cell.h>
#include <MovementStrategy.h>

class KingMovementStrategy : public MovementStrategy{
    public:
    bool canMove(Cell& start, Cell& end, ChessBoard& board) {
        return true;
    }
};