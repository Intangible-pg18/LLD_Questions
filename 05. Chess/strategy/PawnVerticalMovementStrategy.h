#include <Cell.h>
#include <MovementStrategy.h>
#include <Pawn.h>

class PawnVerticalMovementStrategy : public MovementStrategy{
    unique_ptr<Pawn> pawn;

    public:
        PawnVerticalMovementStrategy(unique_ptr<Pawn> pawn) {
            this->pawn = move(pawn);
        }

        bool canMove(Cell& start, Cell& end, ChessBoard& board) {
            if(start.getY() != end.getY()){
                return false;
            }

            int step = (this->pawn->getColor() == PieceColor::WHITE) ? 1 : -1;
            int displacement = end.getX() - start.getX();

            if(this->pawn->isMovingForFirstTime() && displacement == 2 * step) {
                return !end.hasPiece() && !board.getBoard()[start.getX() + step][start.getY() - 'a']->hasPiece();
            }
            return displacement == step && (!end.hasPiece());
        }
};