#include <Player.h>
#include <PieceName.h>
#include <IChessPiece.h>
#include <ChessBoard.h>
#include <string>
#include <Player.h>
#include <unordered_map>
#include <stdexcept>

class ChessPlayer : public Player {
    PieceColor color;
    ChessBoard& board;
    vector<IChessPiece*> activePieces; 

public:
    ChessPlayer(string name, PieceColor color, ChessBoard& board) 
        : Player(name), color(color), board(board)
    {
        updateActivePieces();
    }

    void updateActivePieces() {
        activePieces.clear();
        auto& boardData = board.getBoard(); 
        for (auto& row : boardData) {
            for (auto& cell : row) {
                if (cell->hasPiece()) {
                    IChessPiece* piece = cell->getPiece();
                    if (piece->getColor() == this->color) {
                        activePieces.push_back(piece);
                    }
                }
            }
        }
    }

    vector<IChessPiece*>& getActivePieces() {
        return activePieces;
    }

    PieceColor getColor() {
        return color;
    }

    ChessBoard& getBoard() {
        return board;
    }
};