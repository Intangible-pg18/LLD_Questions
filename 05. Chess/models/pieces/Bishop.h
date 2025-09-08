#pragma once
#include "models/pieces/IChessPiece.h"
#include "models/pieces/AbstractChessPiece.h"
#include "models/pieces/PieceName.h"
#include "models/pieces/PieceColor.h"
#include "exception/InvalidPieceMoveException.h"
#include "strategy/DiagonalMovementStrategy.h"

class Bishop : public AbstractChessPiece{
    public:
        Bishop(PieceName name, PieceColor color, string symbol) : AbstractChessPiece(name, color, symbol) {
            this->movementStrategies = {make_unique<DiagonalMovementStrategy>()};
        }
        void listPossibleMoves(Cell& currentCell, ChessBoard& board) override {}
};