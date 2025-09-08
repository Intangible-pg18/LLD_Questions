#pragma once
#include "models/pieces/IChessPiece.h"
#include "models/pieces/PieceName.h"
#include "models/pieces/PieceColor.h"
#include "pieces/Move.h"
#include <vector>
#include <memory>
#include "Directions.h"
#include "strategy/MovementStrategy.h"
#include <ChessBoard.h>

class AbstractChessPiece : public IChessPiece{
    public:
        vector<unique_ptr<Move>> movesDone;
        PieceName pieceName;
        string pieceSymbol;
        vector<unique_ptr<MovementStrategy>> movementStrategies;
        bool killed;
        PieceColor pieceColor;


        AbstractChessPiece(PieceName pieceName, PieceColor pieceColor, string& symbol) : pieceName(pieceName), pieceColor(pieceColor), killed(false), pieceSymbol(symbol) {}
        
        PieceName getPieceName() {
            return pieceName;
        }

        bool isMovingForFirstTime() override {
            return movesDone.empty();
        }

        bool canMove(Cell& start, Cell& end, ChessBoard& board)  override {
            for(auto& strategy : movementStrategies) {
                if(strategy->canMove(start, end, board)) return true;
            }
            return false;
        }
        
        void makeMove(Cell& startingCell, Cell& endingCell, ChessBoard& board) override {
            unique_ptr<IChessPiece> pieceToMove = startingCell.takePiece();

            if (!pieceToMove) {
                return; 
            }

            if (endingCell.hasPiece()) {
                endingCell.getPiece()->setKilled(true);
            }

            endingCell.setPiece(move(pieceToMove));
        }

        PieceColor getColor() override {
            return pieceColor;
        }
        
        PieceName getPieceName() override {
            return pieceName;
        }

        string getColorSymbol() {
            return (this->pieceColor == PieceColor::BLACK) ? "B" : "W";
        }

        string getPieceSymbol() override {
            return this->pieceSymbol;
        }

        bool isKilled() override {
            return killed;
        }

        void setKilled(bool killed) override {
            this->killed = killed;
        }

        bool isMovingForTheFirstTime() { return movesDone.empty();}

        bool isMovingDiagonally(Cell& startingCell, Cell& endingCell) {
            return startingCell.getHorizontalDistance(endingCell) == 1 && startingCell.getVerticalDistance(endingCell) == 1;
        }

        bool isMovingHorizontally(Cell& startingCell, Cell& endingCell) {
            return startingCell.getHorizontalDistance(endingCell) == 1 && startingCell.getVerticalDistance(endingCell) == 0;
        }

        bool isMovingVertically(Cell& startingCell, Cell& endingCell) {
            return startingCell.getHorizontalDistance(endingCell) == 0 && startingCell.getVerticalDistance(endingCell) == 1;
        }

        Directions getMovementDirection(Cell& startingCell, Cell& endingCell) {
            int x = endingCell.getX() - startingCell.getX();
            int y = endingCell.getY() - startingCell.getY();
            if(x == 0 && y == 0) {
                return Directions::NONE;
            }
            if(x == 0) {
                return y > 0 ? Directions::FORWARD_Y : Directions::BACKWARD_Y;
            }
            if(y == 0) {
                return x > 0 ? Directions::FORWARD_X : Directions::BACKWARD_X;
            }
            if(x == 1 && y == 1) {
                return Directions::DIAGONAL_FORWARD_RIGHT;
            }
            if(x == 1 && y == -1) {
                return Directions::DIAGONAL_FORWARD_LEFT;
            }
            if(x == -1 && y == 1) {
                return Directions::DIAGONAL_BACKWARD_RIGHT;
            }
            if(x == -1 && y == -1) {
                return Directions::DIAGONAL_BACKWARD_LEFT;
            }
            return Directions::NONE;
        }
};