#include <Cell.h>
#include <MovementStrategy.h>

class HorizontalMovementStrategy : public MovementStrategy{
    public:
    bool canMove(Cell& start, Cell& end, ChessBoard& board) {
        if(start.getX() != end.getX()){
            return false;
        }

        int step = (end.getY() > start.getY()) ? 1 : -1; 
        int currentColumn = start.getY() + step;

        while(currentColumn != end.getY() && currentColumn >=0 && currentColumn < 8) {
            if(board.getBoard()[start.getX()][currentColumn - 'a']->hasPiece()) {
                return false;
            }
            currentColumn += step;
        }
        return !end.hasPiece() || end.getPiece()->getColor() != start.getPiece()->getColor();
    }
};