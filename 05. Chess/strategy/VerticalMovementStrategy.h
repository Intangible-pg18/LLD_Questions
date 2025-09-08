#include <Cell.h>
#include <MovementStrategy.h>
#include <Pawn.h>

class VerticalMovementStrategy : public MovementStrategy{
    public:
        bool canMove(Cell& start, Cell& end, ChessBoard& board) {
            if(start.getY() != end.getY()){
            return false;
        }

            int step = (end.getX() > start.getX()) ? 1 : -1; 
            int currentRow = start.getX() + step;

            while(currentRow != end.getX() && currentRow >= 0 && currentRow < 8) {
                if(board.getBoard()[currentRow][start.getY() - 'a']->hasPiece()) {
                    return false;
                }
                currentRow += step;
            }

            return !end.hasPiece() || end.getPiece()->getColor() != start.getPiece()->getColor();
        }
};