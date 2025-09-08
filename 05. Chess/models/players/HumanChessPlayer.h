#include <ChessPlayer.h>

class HumanChessPlayer : public ChessPlayer {
    public:
        HumanChessPlayer(string name, PieceColor color, ChessBoard& board) : ChessPlayer(name, color, board) {}

        Move makeMove() override {
            this->getBoard().display();

            cout<<"Enter the row and column of the piece you want to move: "<<endl;
            int row;
            char col;
            cin>>row;
            cin>>col;

            if(!this->getBoard().getBoard()[row][col - 'a']->hasPiece()) {
                throw runtime_error("No piece found at this location");
            }

            cout<<"Enter the row and column of the destination: "<<endl;
            int destRow;
            char destCol;
            cin>>destRow;
            cin>>destCol;

            IChessPiece* pieceToMove = this->getBoard().getBoard()[row][col - 'a']->getPiece();
            if(!pieceToMove->canMove(*(this->getBoard().getBoard()[row][col - 'a']), *(this->getBoard().getBoard()[destRow][destCol - 'a']), this->getBoard())) {
                throw runtime_error("Invalid move");
            }

            // 7. Prepare the move object
            return Move(*(this->getBoard().getBoard()[row][col - 'a']), *(this->getBoard().getBoard()[destRow][destCol - 'a']));
        }
};