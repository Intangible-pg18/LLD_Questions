#pragma once
#include "models/pieces/IChessPiece.h"
#include "models/pieces/AbstractChessPiece.h"
#include "models/pieces/PieceName.h"
#include "models/pieces/PieceColor.h"
#include "exception/InvalidPieceMoveException.h"
#include "strategy/HorizontalMovementStrategy.h"
#include "strategy/VerticalMovementStrategy.h"
#include "strategy/DiagonalMovementStrategy.h"

class Queen : public AbstractChessPiece{
    public:
        Queen(PieceName name, PieceColor color, string symbol) : AbstractChessPiece(name, color, symbol) {
            this->movementStrategies = {make_unique<HorizontalMovementStrategy>(), make_unique<VerticalMovementStrategy>(), make_unique<DiagonalMovementStrategy>()};
        }
        void listPossibleMoves(Cell& currentCell, ChessBoard& board) override {}
};