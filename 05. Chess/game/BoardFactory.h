#include <PieceColor.h>
#include <unordered_map>
#include <Board.h>
#include <BoardGame.h>
#include <ChessBoard.h>
#include <IChessPiece.h>
#include <PieceColor.h>
#include <PieceName.h>
#include <ChessPlayer.h>
#include <Pawn.h>
#include <Rook.h>
#include <Queen.h>
#include <King.h>
#include <Knight.h>
#include <Bishop.h>



class BoardFactory {

    public:
        static unordered_map<PieceName, unique_ptr<IChessPiece>> whitePieces;
        static unordered_map<PieceName, unique_ptr<IChessPiece>> blackPieces;

        static unordered_map<PieceName, unique_ptr<IChessPiece>> prepareWhitePieces() {
            whitePieces = getPieces(PieceColor::WHITE);
            return whitePieces;
        }

        static unordered_map<PieceName, unique_ptr<IChessPiece>> prepareBlackPieces() {
            blackPieces = getPieces(PieceColor::BLACK);
            return blackPieces;
        }

        static void prepareBoardByPlacingPieces(ChessBoard& board) {
            placePawns(board, whitePieces, PieceColor::WHITE); 
            placePawns(board, blackPieces, PieceColor::BLACK);
            placeRooks(board, whitePieces, PieceColor::WHITE);
            placeRooks(board, blackPieces, PieceColor::BLACK); 
            placeBishops(board, whitePieces, PieceColor::WHITE); 
            placeBishops(board, blackPieces, PieceColor::BLACK); 
            placeQueen(board, whitePieces, PieceColor::WHITE);
            placeQueen(board, blackPieces, PieceColor::BLACK); 
            placeKing(board, whitePieces, PieceColor::WHITE); 
            placeKing(board, blackPieces, PieceColor::BLACK); 
            placeKnights(board, whitePieces, PieceColor::WHITE); 
            placeKnights(board, blackPieces, PieceColor::BLACK); 
        }

        static unordered_map<PieceName, unique_ptr<IChessPiece>> getPieces(PieceColor color) {
            unordered_map<PieceName, unique_ptr<IChessPiece>> pieces;

            pieces[PieceName::PAWN1] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P1");
            pieces[PieceName::PAWN2] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P2");
            pieces[PieceName::PAWN3] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P3");
            pieces[PieceName::PAWN4] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P4");
            pieces[PieceName::PAWN5] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P5");
            pieces[PieceName::PAWN6] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P6");
            pieces[PieceName::PAWN7] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P7");
            pieces[PieceName::PAWN8] = make_unique<Pawn>(PieceName::PAWN1, color, toString(color).substr(0, 1) + "P8");
            pieces[PieceName::ROOK1] = make_unique<Rook>(PieceName::ROOK1, color, toString(color).substr(0, 1) + "R1");
            pieces[PieceName::ROOK2] = make_unique<Rook>(PieceName::ROOK2, color, toString(color).substr(0, 1) + "R2");
            pieces[PieceName::KNIGHT1] = make_unique<Knight>(PieceName::KNIGHT1, color, toString(color).substr(0, 1) + "N1");
            pieces[PieceName::KNIGHT2] = make_unique<Knight>(PieceName::KNIGHT2, color, toString(color).substr(0, 1) + "N2");
            pieces[PieceName::BISHOP1] = make_unique<Bishop>(PieceName::BISHOP1, color, toString(color).substr(0, 1) + "B1");
            pieces[PieceName::BISHOP2] = make_unique<Bishop>(PieceName::BISHOP2, color, toString(color).substr(0, 1) + "B2");
            pieces[PieceName::QUEEN] = make_unique<Queen>(PieceName::QUEEN, color, toString(color).substr(0, 1) + "Q1");
            pieces[PieceName::KING] = make_unique<King>(PieceName::KING, color, toString(color).substr(0, 1) + "K1");

            return pieces;
        }
    private: 
        static void placePawns(ChessBoard& board, unordered_map<PieceName, unique_ptr<IChessPiece>> colorPieces, PieceColor color) {
            int row = (color == PieceColor::WHITE) ? 1 : 6;
            vector<PieceName> pawns = {PieceName::PAWN1, PieceName::PAWN2, PieceName::PAWN3, PieceName::PAWN4,
                    PieceName::PAWN5, PieceName::PAWN6, PieceName::PAWN7, PieceName::PAWN8};
            for(int col = 0; col < 8; col++) {
                board.setPiece(move(colorPieces[pawns[col]]), row, (char)('a' + col));
            }
        }

        static void placeRooks(ChessBoard& board, unordered_map<PieceName, unique_ptr<IChessPiece>> colorPieces, PieceColor color) {
            int row = (color== PieceColor::WHITE) ? 0 : 7;
            board.setPiece(move(colorPieces[PieceName::ROOK1]), row, 'a');
            board.setPiece(move(colorPieces[PieceName::ROOK2]), row, 'h');
        }

        static void placeBishops(ChessBoard& board, unordered_map<PieceName, unique_ptr<IChessPiece>> colorPieces, PieceColor color) {
            int row = (color== PieceColor::WHITE) ? 0 : 7;
            board.setPiece(move(colorPieces[PieceName::BISHOP1]), row, 'c');
            board.setPiece(move(colorPieces[PieceName::BISHOP2]), row, 'f');
        }

        static void placeQueen(ChessBoard& board, unordered_map<PieceName, unique_ptr<IChessPiece>> colorPieces, PieceColor color) {
            int row = (color== PieceColor::WHITE) ? 0 : 7;
            board.setPiece(move(colorPieces[PieceName::QUEEN]), row, 'd');
        }

        static void placeKing(ChessBoard& board, unordered_map<PieceName, unique_ptr<IChessPiece>> colorPieces, PieceColor color) {
            int row = (color== PieceColor::WHITE) ? 0 : 7;
            board.setPiece(move(colorPieces[PieceName::KING]), row, 'e');
        }

        static void placeKnights(ChessBoard& board, unordered_map<PieceName, unique_ptr<IChessPiece>> colorPieces, PieceColor color) {
            int row = (color== PieceColor::WHITE) ? 0 : 7;
            board.setPiece(move(colorPieces[PieceName::KNIGHT1]), row, 'b');
            board.setPiece(move(colorPieces[PieceName::KNIGHT2]), row, 'g');
        }
};