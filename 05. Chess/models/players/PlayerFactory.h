#pragma once

#include "ChessPlayer.h"
#include "HumanChessPlayer.h"
#include "PieceColor.h"
#include "ChessBoard.h"
#include <string>
#include <memory>

class PlayerFactory {
public:
    static unique_ptr<Player> createHumanPlayer(string& name, PieceColor color, ChessBoard& board) {
        return make_unique<HumanChessPlayer>(name, color, board);
    }
};