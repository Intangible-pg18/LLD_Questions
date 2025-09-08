#pragma once
#include "models/board/Cell.h"
#include "PieceColor.h"
#include <string>
#include <ChessBoard.h>
#include "PieceName.h"

class IChessPiece {
    public:
        virtual void makeMove(Cell& startingCell, Cell& endingCell, ChessBoard& board) = 0;
        virtual bool canMove(Cell& startingCell, Cell& endingCell, ChessBoard& board) = 0;
        virtual void setKilled(bool killed) = 0;
        virtual bool isKilled() = 0;
        virtual void listPossibleMoves(Cell& currentCell, ChessBoard& board) = 0;
        virtual bool isMovingForFirstTime() = 0;
        virtual PieceName getPieceName() = 0;
        virtual PieceColor getColor() = 0;
        virtual string getPieceSymbol() = 0;
};