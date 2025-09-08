#include "BoardGame.h"
#include "ChessGameFactory.h"
int main() {
    unique_ptr<IGameFactory> gameFactory;

    cout << "What game do you want to play? (1 for Chess): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        gameFactory = make_unique<ChessGameFactory>();
    } 
    else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    if (gameFactory) {
        unique_ptr<BoardGame> game = gameFactory->createGame();
        
        if (game) {
            game->startGame();
        }
    }

    return 0;
}