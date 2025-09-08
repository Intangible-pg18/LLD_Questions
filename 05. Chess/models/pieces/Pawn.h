#pragma once
#include "models/pieces/IChessPiece.h"
#include "models/pieces/AbstractChessPiece.h"
#include "models/pieces/PieceName.h"
#include "models/pieces/PieceColor.h"

using namespace std;

class Pawn : public AbstractChessPiece {
    public:
        Pawn(PieceName pieceName, PieceColor pieceColor, string symbol) : AbstractChessPiece(pieceName, pieceColor, symbol) {}
        void listPossibleMoves(Cell& currentCell, ChessBoard& board) override {}
};
