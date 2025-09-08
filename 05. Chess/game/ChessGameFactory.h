#pragma once

#include "IGameFactory.h"
#include "ChessGame.h" 

class ChessGameFactory : public IGameFactory {
public:
    unique_ptr<BoardGame> createGame() override {
        return ChessGame::create();
    }
};