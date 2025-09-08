#pragma once
#include "models/pieces/IChessPiece.h"
#include "models/pieces/AbstractChessPiece.h"
#include "models/pieces/PieceName.h"
#include "models/pieces/PieceColor.h"
#include "exception/InvalidPieceMoveException.h"
#include "strategy/KnightMovementStrategy.h"

class Knight : public AbstractChessPiece{
    public:
        Knight(PieceName name, PieceColor color, string symbol) : AbstractChessPiece(name, color, symbol) {
            this->movementStrategies = {make_unique<KnightMovementStrategy>()};
        }
        void listPossibleMoves(Cell& currentCell, ChessBoard& board) override {}
};