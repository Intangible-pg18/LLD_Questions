#pragma once

#include "BoardGame.h"
#include "ChessBoard.h"
#include "ChessPlayer.h"
#include "HumanChessPlayer.h"
#include "BoardFactory.h"
#include <memory>
#include <queue>

class ChessGame : public BoardGame {
private:
    ChessGame(unique_ptr<Board> board, queue<unique_ptr<Player>>&& players)
        : BoardGame(move(board), move(players)) {}

    IChessPiece* findPiece(Player* player, PieceName name) {
        ChessPlayer* chessPlayer = dynamic_cast<ChessPlayer*>(player);
        if (!chessPlayer) return nullptr;
        for (auto* piece : chessPlayer->getActivePieces()) {
            if (piece->getPieceName() == name) {
                        return piece;
            }
        }
        return nullptr;
    }

    static queue<unique_ptr<Player>> setupPlayers(ChessBoard& board) {
        queue<unique_ptr<Player>> players;
        players.push(make_unique<HumanChessPlayer>("White", PieceColor::WHITE, board));
        players.push(make_unique<HumanChessPlayer>("Black", PieceColor::BLACK, board));
        return players;
    }

public:
    static unique_ptr<ChessGame> create() {
        auto board = make_unique<ChessBoard>();
        BoardFactory::prepareBoardByPlacingPieces(*board);
        auto players = setupPlayers(*board);
        return unique_ptr<ChessGame>(new ChessGame(move(board), move(players)));
    }

    bool isGameOver() override {
        int kingCount = 0;
        ChessBoard* chessBoard = dynamic_cast<ChessBoard*>(board.get());
        if (chessBoard) {
            for (const auto& row : chessBoard->getBoard()) {
                for (const auto& cell : row) {
                    if (cell->hasPiece() && cell->getPiece()->getPieceName() == PieceName::KING) {
                        kingCount++;
                    }
                }
            }
        }
        return kingCount < 2;
    }

    void showBoard() override {
        this->board->display();
    }
};