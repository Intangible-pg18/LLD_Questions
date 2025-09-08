#include <Board.h>
#include <vector>
#include <iostream>

class ChessBoard : public Board {

    int rc = 8;
    int cc = 8;
    vector<vector<unique_ptr<Cell>>> board;
    public:
        ChessBoard() {
            board.reserve(rc); 
            for (int i = 0; i < rc; i++) {
                vector<unique_ptr<Cell>> row;
                row.reserve(cc);
                for (int j = 0; j < cc; j++) {
                    row.push_back(make_unique<Cell>(i, (char)(j + 'a')));
                }
                board.push_back(move(row));
            }
        }

        void display() override {
            for(int r = 0; r < rc; r++) {
                for(int c = 0; c < cc; c++) {
                    if(board[r][c]->hasPiece()) {
                        cout<<board[r][c]->getPiece()->getPieceSymbol() + " | ";
                    } else {
                        cout<<"___ | ";
                    }
                }
                cout<<endl;
            }
        }

        void applyMove(Move& move) override {
            int startRow = move.getSource().getX();
            char startCol = move.getSource().getY();

            IChessPiece* piece = board[startRow][startCol - 'a']->getPiece();
            piece->makeMove(move.getSource(), move.getDestination(), *this);
        }

        void setPiece(unique_ptr<IChessPiece> piece, int row, char col) override {
            board[row][col - 'a']->setPiece(move(piece));
        }

        vector<vector<unique_ptr<Cell>>>& getBoard() {
            return board;
        }
};