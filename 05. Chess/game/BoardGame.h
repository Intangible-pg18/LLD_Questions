#include <queue>
#include <Board.h>
#include <Player.h>


class BoardGame {
    protected:
    unique_ptr<Board> board;
    queue<unique_ptr<Player>> players;

    BoardGame(unique_ptr<Board> board, queue<unique_ptr<Player>>&& players) {
        this->board = move(board);
        this->players = move(players);
    }

    public:
    virtual void showBoard() = 0;

    virtual bool isGameOver() = 0;

    void startGame() {
        while(true) {
            unique_ptr<Player>& currentPlayerPtr = players.front();
            Move playerMove = currentPlayerPtr->makeMove();
            this->board->applyMove(playerMove); 

            if(isGameOver()) {
                cout<<"Game Over"<<endl;
                cout<<currentPlayerPtr->getName() + " wins"<<endl;
                break;
            }
            players.push(move(currentPlayerPtr)); 
            players.pop();
        }
    }
};