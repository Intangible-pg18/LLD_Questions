#pragma once
#include <models/pieces/IChessPiece.h>
#include <utility>
#include <optional>
#include <memory>

using namespace std;

class Cell {
    pair<int,char> position;
    unique_ptr<IChessPiece> piece;
    public:
        Cell(pair<int,char> position, unique_ptr<IChessPiece> optPiece = nullptr) : position(position), piece(move(optPiece)) {}
        
        IChessPiece* getPiece() { return piece.get(); }
        
        unique_ptr<IChessPiece> takePiece() { return move(piece); }

        void removePiece() { piece.reset(); }

        void setPiece(unique_ptr<IChessPiece> newPiece) { piece = move(newPiece); }
        
        pair<int,char> getPosition() { return position; }
        
        int getX() { return position.first; }
        
        char getY() { return position.second; }
        
        bool hasPiece() { return piece != nullptr; }

        int getVerticalDistance(Cell& cell) { return abs(this->position.first - cell.position.first); }

        int getHorizontalDistance(Cell& cell) { return abs((this->position.second-'a') - (cell.position.second-'a')); }
};